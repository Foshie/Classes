/*
 * Paging-based user mode implementation
 * Copyright (c) 2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * $Revision: 1.51 $
 * 
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "COPYING".
 */

#include <geekos/int.h>
#include <geekos/mem.h>
#include <geekos/paging.h>
#include <geekos/malloc.h>
#include <geekos/string.h>
#include <geekos/argblock.h>
#include <geekos/kthread.h>
#include <geekos/range.h>
#include <geekos/vfs.h>
#include <geekos/user.h>


int userDebug = 0;
#define Debug(args...) if (userDebug) Print("uservm: " args)

/* ----------------------------------------------------------------------
 * Private functions
 * ---------------------------------------------------------------------- */


/* ----------------------------------------------------------------------
 * Public functions
 * ---------------------------------------------------------------------- */

/*
 * Destroy a User_Context object, including all memory
 * and other resources allocated within it.
 */
void Destroy_User_Context(struct User_Context *context) {
    /*
     * Hints:
     * - Free all pages, page tables, and page directory for
     *   the process (interrupts must be disabled while you do this,
     *   otherwise those pages could be stolen by other processes)
     * - Free semaphores, files, and other resources used
     *   by the process
     */ 
  KASSERT(context->refCount == 0);
  
  /* Free the context's LDT descriptor */
  Free_Segment_Descriptor(context->ldtDescriptor);
  
    /* Free the context's memory */
  Disable_Interrupts();
  //Free(context->memory);
  Free(context);
  Enable_Interrupts();
}

static struct User_Context *Create_User_Context(){
  struct User_Context *context;
  int index;
  context = (struct User_Context *) Malloc(sizeof(*context));

  if(context == 0)
    return NULL;
  //****** what do i set this to?
  context->memory = USER_VM_START;
  
  context->size = USER_VM_SIZE;
  /* Allocate an LDT descriptor for the user context */
  context->ldtDescriptor = Allocate_Segment_Descriptor();
  if (context->ldtDescriptor == 0)
    return NULL;
  if (userDebug)
    Print("Allocated descriptor %d for LDT\n",
	  Get_Descriptor_Index(context->ldtDescriptor));
  Init_LDT_Descriptor(context->ldtDescriptor, context->ldt,
		      NUM_USER_LDT_ENTRIES);
  index = Get_Descriptor_Index(context->ldtDescriptor);
  context->ldtSelector = Selector(KERNEL_PRIVILEGE, true, index);
  
  /* Initialize code and data segments within the LDT */
  Init_Code_Segment_Descriptor(&context->ldt[0],(ulong_t) context->memory,context->size / PAGE_SIZE, USER_PRIVILEGE);
  Init_Data_Segment_Descriptor(&context->ldt[1], (ulong_t) context->memory,context->size / PAGE_SIZE, USER_PRIVILEGE);
  context->csSelector = Selector(USER_PRIVILEGE, false, 0);
  context->dsSelector = Selector(USER_PRIVILEGE, false, 1);
  
  /* Nobody is using this user context yet */
  context->refCount = 0;
  
  /* Success! */
  return context;
}

int Make_Page_Table(pde_t *pageDir, ulong_t vaddr, void **p_Table){
  void *pageTable;
  int pdi = PAGE_DIRECTORY_INDEX(vaddr);
  //If page table entry in the page directory is not present, creates the entry and stores into directory
  if(pageDir[pdi].present == 0){
    pageTable = (pte_t *) Alloc_Page();
    if(pageTable == 0)
      return -1;
    memset(pageTable, '\0', PAGE_SIZE);
    pageDir[pdi].pageTableBaseAddr = (uint_t) PAGE_ALIGNED_ADDR(pageTable);
    pageDir[pdi].present = 1;
    pageDir[pdi].flags = VM_USER | VM_WRITE;
    *p_Table = pageTable;
  }
  return 0;
}
int Make_Pageable_Page(pte_t *pageTable, ulong_t vaddr, void **page){
  void * newPage;
  // Alloc segment for new page
  int pti = PAGE_TABLE_INDEX(vaddr);
  newPage = Alloc_Pageable_Page(&pageTable[pti], vaddr);
  if(newPage == 0)
    return -1;
  memset(newPage, '\0', PAGE_SIZE);
  pageTable[pti].pageBaseAddr = (uint_t) PAGE_ALIGNED_ADDR(newPage);
  //	Print(" pdi:%d, pti:%d\tbase addr: %d\tmemory: %x\t",pdi,pti, pageTable[pti].pageBaseAddr, vaddr);
  pageTable[pti].present = 1;
  pageTable[pti].flags = VM_USER|VM_WRITE;
  *page = newPage;
  return 0;
}
/* 
 * Project Deets:
 * Setting up paging for user processes occurs in Load_User_Program, and takes two steps.  
 * First, you need to allocate a page directory for the process. 
 * You should copy all of the entries from the kernel page directory for the physical pages at the bottom of the address space.
 *
 * Next, allocate page table entries for the user process's text, data, and stack regions.  
 * Each of these regions will consist of some number of pages allocated by the routine Alloc_Pageable_Page.  
 * This routine differs from Alloc_Page in that the allocated page it returns will have a special flag PAGE_PAGEABLE set in the 
 * flags field of its entry in the struct Page data structure (see mem.h).  
 * This marks the page as eligible for being stolen and paged out to disk by the kernel when a page of memory is needed elsewhere, 
 * but no free pages are available. 
 * All pages (but not page directories and page tables) for a user space process should be allocated using this routine.
 */
/*
 * Load a user executable into memory by creating a User_Context
 * data structure.
 * Params:
 * exeFileData - a buffer containing the executable to load
 * exeFileLength - number of bytes in exeFileData
 * exeFormat - parsed ELF segment information describing how to
 *   load the executable's text and data segments, and the
 *   code entry point address
 * command - string containing the complete command to be executed:
 *   this should be used to create the argument block for the
 *   process
 * pUserContext - reference to the pointer where the User_Context
 *   should be stored
 *
 * Returns:
 *   0 if successful, or an error code (< 0) if unsuccessful
 */
int Load_User_Program(char *exeFileData, ulong_t exeFileLength,
                      struct Exe_Format *exeFormat, const char *command,
                      struct User_Context **pUserContext) {
    /*
     * Hints:
     * - This will be similar to the same function in userseg.c
     * - Determine space requirements for code, data, argument block,
     *   and stack
     * - Allocate pages for above, map them into user address
     *   space (allocating page directory and page tables as needed)
     * - Fill in initial stack pointer, argument block address,
     *   and code entry point fields in User_Context
     */
  int i, numPages, count, countPages, pti, pdi;
  struct User_Context *context = NULL;
  ulong_t maxva = 0;
  unsigned numArgs;
  ulong_t argBlockSize;
  ulong_t argBlockAddr, start, end, diff, curr;
  size_t size;
  pde_t *user_dir,*origPDBR;
  pte_t *p_table;
  void *new_Page, *arg_Page, *stack_Page;
  struct Page *temp;
  
  //Allocate memory for the user context
  context = Create_User_Context();
  if(context == NULL)
    goto fail;
  
  //Allocate a page for the user's page directory
  user_dir = (pde_t *) Alloc_Page();
  if(user_dir == 0)
    goto fail;
  memset((void *) user_dir, '\0', PAGE_SIZE);
  context->pageDir = user_dir;
  
  /* Copy all of the mappings from the kernel mode page directory for 
   * those memory regions in the low range of memory
   */
  memcpy((void *) user_dir, (const void *) p_dir, (size_t)(PAGE_SIZE/2));
  origPDBR = Get_PDBR();
  Set_PDBR(context->pageDir);
    /* Find maximum virtual address */
  for (i = 0; i < exeFormat->numSegments; ++i) {
    struct Exe_Segment *segment = &exeFormat->segmentList[i];
    ulong_t topva = segment->startAddress + segment->sizeInMemory;  /* FIXME: range check */
    
    if (topva > maxva)
      maxva = topva;
  }
  context->dataEnd = Round_Up_To_Page(maxva) + USER_VM_START;

  /* //Version 1 */
  /* Load segment data into memory */
  for(i = 0; i < exeFormat->numSegments; i++){
    start = Round_Down_To_Page(exeFormat->segmentList[i].startAddress + USER_VM_START);
    diff = USER_VM_START + exeFormat->segmentList[i].startAddress - start;
    end = exeFormat->segmentList[i].startAddress + exeFormat->segmentList[i].sizeInMemory + USER_VM_START;
    for(curr = start; curr < end; curr += PAGE_SIZE){
      //Makes a new pageable page.  if page table is not present,then that is made too.
      if(Make_Page_Table(user_dir, curr, &p_table) < 0)
	goto fail;
      if(Make_Pageable_Page(p_table, curr, &new_Page) < 0)
	goto fail;
      
      /* copies a whole page of the current segement data.  offset deals with just the first case if the start address does not point at something at a page address.
       * keeps copying pages of this amount of data until curr % PAGE_SIZE != 0.  end - curr < PAGE_SIZE, there is less than a page_size worth of data left to copy.
       */
      if(end - curr >= PAGE_SIZE){
	size = (size_t) (PAGE_SIZE - diff);
      }else{
	//copy remainder of data left to final page.
	size = (size_t)(end - curr - diff);
      }
      memcpy((void *)(new_Page + diff), (const void*)(exeFileData + exeFormat->segmentList[i].offsetInFile + curr- start), (size_t)(size));
      diff = 0;
    }
  }

  //Version 2
   /* Find maximum virtual address */
/*   for (i = 0; i < exeFormat->numSegments; ++i) { */
/*     struct Exe_Segment *segment = &exeFormat->segmentList[i]; */
/*     ulong_t topva = segment->startAddress + segment->sizeInMemory;  /\* FIXME: range check *\/ */
    
/*     if (topva > maxva) */
/*       maxva = topva; */
/*   } */
/*   size = Round_Up_To_Page(maxva); */
/*   numPages = size/PAGE_SIZE; */
/*   countPages = 0; */
/*   //Alloc all pages needed for size */
/*   for(count = 0; count < NUM_PAGE_DIR_ENTRIES; count++){ */
/*     p_table = Alloc_Page(); */
/*     if(p_table == 0) */
/*       goto fail; */

/*     pdi = PAGE_DIRECTORY_INDEX(USER_VM_START + count * PAGE_SIZE * NUM_PAGE_TABLE_ENTRIES); */
/*     p_table[0].present = 0; */
    
/*     user_dir[pdi].pageTableBaseAddr = PAGE_ALIGNED_ADDR(p_table); */
/*     user_dir[pdi].present = 1; */
/*     user_dir[pdi].flags = VM_USER|VM_WRITE; */

/*     for(pti = 1; pti < NUM_PAGE_TABLE_ENTRIES; pti++){ */
/*       new_Page = Alloc_Pageable_Page(&p_table[pti], USER_VM_START + pti*PAGE_SIZE); */
/*       if(new_Page == 0) */
/* 	goto fail; */
/*       countPages ++; */
/*       p_table[pti].present =1; */
/*       p_table[pti].flags = VM_USER|VM_WRITE; */
/*       p_table[pti].pageBaseAddr = PAGE_ALIGNED_ADDR(new_Page); */
/*       if(countPages == numPages) */
/* 	break; */
/*     } */
/*     if(countPages == numPages) */
/*       break; */
/*   } */

/*    /\* Load segment data into memory *\/ */
/*     for (i = 0; i < exeFormat->numSegments; ++i) { */
/*         struct Exe_Segment *segment = &exeFormat->segmentList[i]; */

/*         memcpy(context->memory + segment->startAddress, */
/*                exeFileData + segment->offsetInFile, segment->lengthInFile); */
/*     } */

  /* Allocate two pages of memory at the end of the virtual address range 
   * (i.e., the last two entries in the last page table, as shown in the figure above). 
   * One is for the arguments, the other one is for stack. 
   */
  curr = Round_Down_To_Page(USER_VM_ARGS);
  Get_Argument_Block_Size(command, &numArgs, &argBlockSize);
  if(argBlockSize > PAGE_SIZE)
    goto fail;
  //Creates a pageable page for the arguments block
  if(Make_Page_Table(user_dir, curr, &p_table) < 0)
    goto fail;
  if(Make_Pageable_Page(p_table, curr, &arg_Page) < 0)
    goto fail;
  // Format argument 
  context->argBlockAddr = USER_VM_STACK - USER_VM_START;
  /* Format argument block */
  temp = Get_Page((ulong_t) arg_Page);
  Format_Argument_Block(context->memory + context->argBlockAddr, numArgs, context->argBlockAddr, command);


  curr = Round_Down_To_Page(USER_VM_STACK -1);
  if(Make_Page_Table(user_dir, curr, &p_table) < 0)
    goto fail;
  if(Make_Pageable_Page(p_table, curr, &stack_Page) < 0)
    goto fail;

  temp = Get_Page((ulong_t) stack_Page);
  //********* what should this be?
  context->stackPointerAddr = USER_VM_STACK- USER_VM_START;

  /* Fill in code entry point */
  context->entryAddr =exeFormat -> entryAddr;
   *pUserContext = context;
  Set_PDBR(origPDBR);
  return 0;

  fail:
    /* We failed; release any allocated memory */
    if (context != 0) {
      Destroy_User_Context(context);
    }
    Print("Fail Load_User_Context()");
   return -1;
}

/*
 * Copy data from user buffer into kernel buffer.
 * Returns true if successful, false otherwise.
 */
bool Copy_From_User(void *destInKernel, ulong_t srcInUser, ulong_t numBytes) {
    /*
     * Hints:
     * - Make sure that user page is part of a valid region
     *   of memory
     * - Remember that you need to add 0x80000000 to user addresses
     *   to convert them to kernel addresses, because of how the
     *   user code and data segments are defined
     * - User pages may need to be paged in from disk before being accessed.
     * - Before you touch (read or write) any data in a user
     *   page, **disable the PAGE_PAGEABLE bit**.
     *
     * Be very careful with race conditions in reading a page from disk.
     * Kernel code must always assume that if the struct Page for
     * a page of memory has the PAGE_PAGEABLE bit set,
     * IT CAN BE STOLEN AT ANY TIME.  The only exception is if
     * interrupts are disabled; because no other process can run,
     * the page is guaranteed not to be stolen.
     */
  struct User_Context *current = g_currentThread->userContext;

    if (!Validate_User_Memory(current, srcInUser, numBytes))
        return false;
    memcpy(destInKernel, User_To_Kernel(current, srcInUser), numBytes);

    return true;
}

/*
 * Copy data from kernel buffer into user buffer.
 * Returns true if successful, false otherwise.
 */
bool Copy_To_User(ulong_t destInUser, void *srcInKernel, ulong_t numBytes) {
    /*
     * Hints:
     * - Same as for Copy_From_User()
     * - Also, make sure the memory is mapped into the user
     *   address space with write permission enabled
     */
        struct User_Context *current = g_currentThread->userContext;

    if (!Validate_User_Memory(current, destInUser, numBytes))
        return false;
    memcpy(User_To_Kernel(current, destInUser), srcInKernel, numBytes);

    return true;
}
/*
 * Switch to user address space.
 */
void Switch_To_Address_Space(struct User_Context *userContext) {
    /*
     * - If you are still using an LDT to define your user code and data
     *   segments, switch to the process's LDT
     * - 
     */
      ushort_t ldtSelector;

    /* Switch to the LDT of the new user context */
    ldtSelector = userContext->ldtSelector;
    __asm__ __volatile__("lldt %0"::"a"(ldtSelector)
        );
    Set_PDBR(userContext->pageDir);
}


void *User_To_Kernel(struct User_Context *userContext, ulong_t userPtr) {
    uchar_t *userBase = (uchar_t *) userContext->memory;

    return (void *)(userBase + userPtr);
}

bool Validate_User_Memory(struct User_Context * userContext,
                          ulong_t userAddr, ulong_t bufSize) {
    ulong_t avail;

    if (userAddr >= userContext->size)
        return false;

    avail = userContext->size - userAddr;
    if (bufSize > avail)
        return false;

    return true;
}
