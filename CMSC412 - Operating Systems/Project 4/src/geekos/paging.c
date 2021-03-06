/*
 * Paging (virtual memory) support
 * Copyright (c) 2003, Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 * Copyright (c) 2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * $Revision: 1.56 $
 * 
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "COPYING".
 */

#include <geekos/string.h>
#include <geekos/int.h>
#include <geekos/idt.h>
#include <geekos/kthread.h>
#include <geekos/kassert.h>
#include <geekos/screen.h>
#include <geekos/mem.h>
#include <geekos/malloc.h>
#include <geekos/gdt.h>
#include <geekos/segment.h>
#include <geekos/user.h>
#include <geekos/vfs.h>
#include <geekos/crc32.h>
#include <geekos/paging.h>

/* ----------------------------------------------------------------------
 * Public data
 * ---------------------------------------------------------------------- */
pde_t * p_dir;
/* ----------------------------------------------------------------------
 * Private functions/data
 * ---------------------------------------------------------------------- */

#define SECTORS_PER_PAGE (PAGE_SIZE / SECTOR_SIZE)

/*
 * flag to indicate if debugging paging code
 */
int debugFaults = 0;
#define Debug(args...) if (debugFaults) Print(args)


/*
 * Print diagnostic information for a page fault.
 */
static void Print_Fault_Info(uint_t address, faultcode_t faultCode) {
    extern uint_t g_freePageCount;

    Print("Pid %d, Page Fault received, at address %x (%d pages free)\n",
          g_currentThread->pid, address, g_freePageCount);
    if (faultCode.protectionViolation)
        Print("   Protection Violation, ");
    else
        Print("   Non-present page, ");
    if (faultCode.writeFault)
        Print("Write Fault, ");
    else
        Print("Read Fault, ");
    if (faultCode.userModeFault)
        Print("in User Mode\n");
    else
        Print("in Supervisor Mode\n");
}

/*
 * Handler for page faults.
 * You should call the Install_Interrupt_Handler() function to
 * register this function as the handler for interrupt 14.
 */
/*static*/ void Page_Fault_Handler(struct Interrupt_State *state) {
    ulong_t address;
    faultcode_t faultCode;

    KASSERT(!Interrupts_Enabled());

    /* Get the address that caused the page fault */
    address = Get_Page_Fault_Address();
    Debug("Page fault @%lx\n", address);

    /* Get the fault code */
    faultCode = *((faultcode_t *) & (state->errorCode));

    /* rest of your handling code here */
    Print("Unexpected Page Fault received\n");
    Print_Fault_Info(address, faultCode);
    Dump_Interrupt_State(state);
    /* user faults just kill the process */
    if (!faultCode.userModeFault)
        KASSERT(0);

    /* For now, just kill the thread/process. */
    Exit(-1);
}

/* ----------------------------------------------------------------------
 * Public functions
 * ---------------------------------------------------------------------- */

/*
 * Initialize virtual memory by building page tables
 * for the kernel and physical memory.
 */
/* Project Deets:
 *
 * To set up page tables, you will need to allocate a page directory (via Alloc_Page) 
 * and then allocate page tables for the entire region that will be mapped into this memory context. 
 * You will do this in the Init_VM in paging.c. You will need to fill out the appropriate fields in the page tables and page directories.
 * The definition of paging tables and directories are found in paging.h (structs pte_t and pde_t).
 * Finally, as mentioned earlier, GeekOS does not use paging by default, so to enable it,
 * you will need to call the routine Enable_Paging which is already defined for you in lowlevel.asm. 
 * It takes the base address of your page directory as a parameter.
 *
 * The final step of this function is to add a handler for page faults. Currently, a page fault can occur only when a user program attempts to access an invalid address.
 * Therefore, we have provided a default handler, Page_Fault_Handler in paging.c, to terminate a user program that does this. 
 * You should register it for the page fault interrupt, interrupt 14, by calling Install_Interrupt_Handler.
 * You should then add a call the Init_VM function from your main.c (after Init_Interrupts).
 *
 * You should be able to complete this part and test it by temporarily giving user mode access to these pages by setting the flags field in the page table entries to include VM_USER.
 * This allows user programs complete access to the pages referenced by the table.
 * Refer to item 1 in the grading criteria to understand how to test what you should have running at this point.  
 * You can then submit this as your intermediate submission.
 */
void Init_VM(struct Boot_Info *bootInfo) {
    /*
     * Hints:
     * - Build kernel page directory and page tables
     * - Call Enable_Paging() with the kernel page directory
     * - Install an interrupt handler for interrupt 14,
     *   page fault
     * - Do not map a page at address 0; this will help trap
     *   null pointer references
     */
  int i,j, count = 1, numPages = (bootInfo->memSizeKB)>>2;
  pte_t *pageTable;
  pte_t t_entry;
  pde_t d_entry;
  p_dir = Alloc_Page();
  
  d_entry.present = 1;
  d_entry.flags = VM_USER | VM_WRITE;
  
  
  t_entry.present = 1;
  t_entry.flags = VM_USER | VM_WRITE;
  
  
  for(i = 0; i <  NUM_PAGE_DIR_ENTRIES; i++){
    pageTable = Alloc_Page();
    d_entry.pageTableBaseAddr = PAGE_ALIGNED_ADDR(pageTable); 
    p_dir[i] = d_entry;
    
    for(j = 0; j < NUM_PAGE_TABLE_ENTRIES; j++){
      if(i==0 && j == 0)
				j++;
      t_entry.pageBaseAddr = count;
      pageTable[j] = t_entry;
      
      if(count == numPages){
				break;
      }
      
      count++;
    }
    if(count == numPages){
      break;
    }
  }
  
  checkPaging(); 
  Enable_Paging(p_dir);
  checkPaging();
  
  Install_Interrupt_Handler(14, Page_Fault_Handler);
}

/**
 * Initialize paging file data structures.
 * All filesystems should be mounted before this function
 * is called, to ensure that the paging file is available.
 */
void Init_Paging(void) {
    TODO("Initialize paging file data structures");
}

/**
 * Find a free bit of disk on the paging file for this page.
 * Interrupts must be disabled.
 * @return index of free page sized chunk of disk space in
 *   the paging file, or -1 if the paging file is full
 */
int Find_Space_On_Paging_File(void) {
    KASSERT(!Interrupts_Enabled());
    TODO("Find free page in paging file");
}

/**
 * Free a page-sized chunk of disk space in the paging file.
 * Interrupts must be disabled.
 * @param pagefileIndex index of the chunk of disk space
 */
void Free_Space_On_Paging_File(int pagefileIndex) {
    KASSERT(!Interrupts_Enabled());
    TODO("Free page in paging file");
}

/**
 * Write the contents of given page to the indicated block
 * of space in the paging file.
 * @param paddr a pointer to the physical memory of the page
 * @param vaddr virtual address where page is mapped in user memory
 * @param pagefileIndex the index of the page sized chunk of space
 *   in the paging file
 */
void Write_To_Paging_File(void *paddr, ulong_t vaddr, int pagefileIndex) {
    struct Page *page = Get_Page((ulong_t) paddr);
    KASSERT(!(page->flags & PAGE_PAGEABLE));    /* Page must be locked! */
    TODO("Write page data to paging file");
}

/**
 * Read the contents of the indicated block
 * of space in the paging file into the given page.
 * @param paddr a pointer to the physical memory of the page
 * @param vaddr virtual address where page will be re-mapped in
 *   user memory
 * @param pagefileIndex the index of the page sized chunk of space
 *   in the paging file
 */
void Read_From_Paging_File(void *paddr, ulong_t vaddr, int pagefileIndex) {
    struct Page *page = Get_Page((ulong_t) paddr);
    KASSERT(!(page->flags & PAGE_PAGEABLE));    /* Page must be locked! */
    TODO("Read page data from paging file");
}
