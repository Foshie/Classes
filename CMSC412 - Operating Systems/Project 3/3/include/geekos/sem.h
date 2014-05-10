#ifndef _INCLUDED_SEM_H
#define _INCLUDED_SEM_H
#ifdef GEEKOS
/*Project 3 Semaphores: Edit begin*/
struct Semaphore;
struct SemName;
#define SEM_NAME_LENGTH 25

//List which includes all threads
DEFINE_LIST(All_Sem_List, Semaphore);
DEFINE_LIST(All_Sem_Name, SemName);
//Semaphore data structure.

struct SemName {
	char name[SEM_NAME_LENGTH];
	DEFINE_LINK(All_Sem_Name, SemName);
};
struct Semaphore {
	int sem_ID; //semaphore's id
	/*structure to store semaphore name.
	 *Easier to keep track of which semaphores exist currently.
	 */
	struct SemName *semName; 
	//Keep track of threads waiting on semaphore
	struct Thread_Queue blockedThreads;
	DEFINE_LINK(All_Sem_List, Semaphore);
	int val;	//semaphore count
	
	int refCount; //Increment when a new process calls open_Semaphore., decrement when close semaphore is called on sem.
};
/*
 * Define All_Sem_List and All_Sem_Name access and manipulation functions.
 */
IMPLEMENT_LIST(All_Sem_Name, SemName);
IMPLEMENT_LIST(All_Sem_List, Semaphore);

int Close_Semaphore(int sem_ID);

int Sys_Open_Semaphore(struct Interrupt_State *state);
int Sys_P(struct Interrupt_State *state);
int Sys_V(struct Interrupt_State *state);
int Sys_Close_Semaphore(struct Interrupt_State *state);
#endif
#endif
