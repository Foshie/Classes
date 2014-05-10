#include <geekos/syscall.h>
#include <geekos/errno.h>
#include <geekos/kthread.h>
#include <geekos/int.h>
#include <geekos/elf.h>
#include <geekos/malloc.h>
#include <geekos/screen.h>
#include <geekos/keyboard.h>
#include <geekos/string.h>
#include <geekos/user.h>
#include <geekos/timer.h>
#include <geekos/vfs.h>
#include <geekos/signal.h>
#include <geekos/sem.h>
#include <geekos/projects.h>

//List of all semaphores existing in the system.
static struct All_Sem_List allSemList;
//List of all semaphore names of allSemList.
static struct All_Sem_Name allSemName;
//Keep track of total number of semaphores
int numSems=0;
/*
 * Create or find a semaphore.
 * Params:
 *   state->ebx - user address of name of semaphore
 *   state->ecx - length of semaphore name
 *   state->edx - initial semaphore count
 * Returns: the global semaphore id
 */
int Sys_Open_Semaphore(struct Interrupt_State *state) {
	struct Semaphore *sem, *curr, *next;
	struct SemName *semName, *temp;
	char blankName[25] = "\0";
	bool int_en = false, is_Member = false;
	semName = Malloc(sizeof(struct SemName));
	if(semName == NULL)
	  return ENOMEM;
	
	memset(semName->name, '\0',25);
	
	if(state->ecx > 25)
		return ENAMETOOLONG;
	if(!Copy_From_User(blankName, (char *) (state->ebx), state->ecx))
		return -1; //unused errno
		
	strncpy(semName->name, blankName,25);

	if(Interrupts_Enabled()){
		Disable_Interrupts();
		int_en = true;
	}
	//Instr: If semaphore exists
	for(temp = Get_Front_Of_All_Sem_Name(&allSemName);temp!=NULL;temp=Get_Next_In_All_Sem_Name(temp)){
	  if(strcmp(temp->name, semName->name) == 0){
	    is_Member = true;
	    break;
	  }
	}
	if(is_Member){
		//Instr: If semaphore has not been destroyed returns back semID, ignore ival.
		//Note: Get semaphore from list.
		
		//List will never be empty if this gets in here.
		for(sem = Get_Front_Of_All_Sem_List(&allSemList); sem!=NULL; sem = Get_Next_In_All_Sem_List(sem)){
		  if(strcmp(sem->semName->name, semName->name)==0)
				break;
		}
		
		if(sem == NULL){
			if(int_en){
			Enable_Interrupts();
			}
			return -1;//Bizarre error, cannot find it.
		}		
		
		//Increment refcount.  Add semaphore to current thread
		sem->refCount++;
		
		g_currentThread->userContext->semaphores[sem->sem_ID-1]++;

	}else{
		//If there are no semaphores left (i.e., there were N semaphores with unique names already given)
		//, ENOSPACE must be returned indicating an error
		if(numSems >= 20){
			if(int_en)
				Enable_Interrupts();
			return ENOSPACE;
		}
		//will search for first available spot in semaphore list. List will be ordered so if something destroys a semaphore, then
		//there will be an open spot between the semaphore before and after.  open semaphore will look for a place to insert.
		//or it will just append to the end of the list.
		sem = Malloc(sizeof(struct Semaphore));
		if(sem==NULL){
		  if(int_en)
		    Enable_Interrupts();
		  return ENOMEM;
		}
		Clear_Thread_Queue(&sem->blockedThreads);
		sem->val = state->edx;
		sem->refCount =1;
		sem->semName = semName;
		curr = Get_Front_Of_All_Sem_List(&allSemList);
		numSems++;
		Add_To_Back_Of_All_Sem_Name(&allSemName, semName);
		
		if(curr == NULL){	//list is empty, just add semaphore
			if(int_en)
				Enable_Interrupts();
			sem->sem_ID = 1;
			Add_To_Back_Of_All_Sem_List(&allSemList, sem);
		}else{
			next = Get_Next_In_All_Sem_List(curr);
			while(next != NULL){
				//Looks for first chance to insert.
				if(curr->sem_ID +1 != next->sem_ID){
					sem->sem_ID = curr->sem_ID +1;
					Insert_Into_All_Sem_List(&allSemList, curr, sem); 
				}
				curr = next;
				next=  Get_Next_In_All_Sem_List(curr);
			}
			
			if(next== NULL){
				sem->sem_ID = curr->sem_ID+1;
				Add_To_Back_Of_All_Sem_List(&allSemList, sem);
			}	
		}
		g_currentThread->userContext->semaphores[sem->sem_ID-1]= 1;
	}
	if(int_en){
	Enable_Interrupts();
	}
	//increment refCount of sem.
	
	return sem->sem_ID;
}

/*
 * Acquire a semaphore.
 * Assume that the process has permission to access the semaphore,
 * the call will block until the semaphore count is >= 0.
 * Params:
 *   state->ebx - the semaphore id
 *
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 *
 * Project Details:
 * The P(sem) system call is used to decrement the value of the semaphore associated with sempahore ID sem.  
 * This operation is referred to as wait() in the text.  
 *
 * As you know, when P() is invoked using a semaphore ID whose associated semaphore's count is less than or equal to 0, 
 *	the invoking process must block.  
 * To block a thread, you can use the Wait function in the kernel. 
 * Each semaphore data structure will contain a thread queue for its blocked threads. 
 * Look at kthread.h and kthread.c to see how it is declared and used.
 *
 * A process may only legally invoke P(sem) if sem was returned by a call to Open_Semaphore for that process 
 *	(and the semaphore has not been subsequently destroyed).  
 * If this is not the case, these routines should return EINVALID.
 */
int Sys_P(struct Interrupt_State *state) {
	bool int_en = false;
	struct Semaphore *sem;
	int sem_ID = state->ebx;
	if(sem_ID < 1 || sem_ID >20)
		return EINVALID;
	if(g_currentThread->userContext->semaphores[sem_ID-1] == 0)
		return EINVALID;
	
	
	if(Interrupts_Enabled()){
		Disable_Interrupts();
		int_en = true;
	}
	
	//Get Thread
	for(sem = Get_Front_Of_All_Sem_List(&allSemList); sem != NULL && sem->sem_ID != sem_ID; sem = Get_Next_In_All_Sem_List(sem)){}
	sem->val--;
	//add to wait/block.
	if(sem->val < 0){
		Wait(&sem->blockedThreads);
	}
	
	if(int_en)
		Enable_Interrupts();
	
	return 0;
}

/*
 * Release a semaphore.
 * Params:
 *   state->ebx - the semaphore id
 *

 * Returns: 0 if successful, error code (< 0) if unsuccessful
 */
int Sys_V(struct Interrupt_State *state) {
  bool int_en = false;
	struct Semaphore *sem;
	int sem_ID = state->ebx;
	
	if(sem_ID < 1 || sem_ID > 20)
	  return EINVALID;

	if(g_currentThread->userContext->semaphores[sem_ID-1] == 0)
		return EINVALID;
	
	
	if(Interrupts_Enabled()){
		Disable_Interrupts();
		int_en = true;
	}
	
	//Get Thread
	for(sem = Get_Front_Of_All_Sem_List(&allSemList); sem != NULL && sem->sem_ID != sem_ID; sem = Get_Next_In_All_Sem_List(sem)){}
	
	sem->val++;
	//add to wait/block.
	if(sem->val <= 0){
		Wake_Up_One(&sem->blockedThreads);
	}
	
	if(int_en)
		Enable_Interrupts();
	
	return 0;
}

/*
 * Destroy our reference to a semaphore.
 * Params:
 *   state->ebx - the semaphore id
 *
 * Returns: 0 if successful, error code (< 0) if unsuccessful
 * 
 * Project Details:
 * Close_Semaphore(sem) should be called when a process is done using a semaphore;
 * subsequent calls to P(sem) and V(sem) (and additional calls to Close_Semaphore(sem) by this process) will return EINVALID.
 * 
 * Once all processes using the semaphore associated with a given semaphore ID have called Close_Semaphore, the kernel datastructure for that semaphore can be destroyed. 
 * A simple way to keep track of when this should happen is to use a reference count. 
 * In particular, each semaphore can contain a count field, and each time a new process calls Open_Semaphore, the count is incremented. 
 * 		-When Close_Semaphore is called, the count is decremented.  
 *		-When the count reaches 0, the semaphore can be destroyed.
 *
 * When a thread exits, the kernel should close any semaphores that the thread still has open. 
 * In your code, both the Sys_Close_Semaphore() function and at least some function involved in terminating user threads 
 * 	should be able to invoke the "real" semaphore-closing function.
 
 //Should I wake up all threads when i destroy the semaphore?
 */
int Sys_Close_Semaphore(struct Interrupt_State *state) {
    bool int_en = false;
	struct Semaphore *sem;
	int sem_ID = state->ebx;
	
	return Close_Semaphore(sem_ID);

}

int Close_Semaphore(int sem_ID){
	struct Semaphore *sem;
	bool int_en = false;
	
	if(sem_ID < 1 || sem_ID > 20)
	  return EINVALID;
	if(g_currentThread->userContext->semaphores[sem_ID-1] == 0)
		return EINVALID;
		
	if(Interrupts_Enabled()){
		Disable_Interrupts();
		int_en = true;
	}
	//Get semaphore
	for(sem = Get_Front_Of_All_Sem_List(&allSemList); sem != NULL && sem->sem_ID != sem_ID; sem = Get_Next_In_All_Sem_List(sem)){}
	
	//decrement current thread's semaphore counter and semaphores refcount
	g_currentThread->userContext->semaphores[sem_ID-1]--;
	sem->refCount--;
 
	//DESTROYYYYYYYYYYYYY
	if(sem->refCount == 0){
		Remove_From_All_Sem_Name(&allSemName, sem->semName);
		Free(sem->semName);
		Remove_From_All_Sem_List(&allSemList, sem);
		Free(sem);
		numSems--;
	}	
	if(int_en)
		Enable_Interrupts();
	return 0;
}
