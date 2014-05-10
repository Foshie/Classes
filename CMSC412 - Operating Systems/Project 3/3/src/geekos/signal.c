/*************************************************************************/
/*
 * GeekOS master source distribution and/or project solution
 * Copyright (c) 2001,2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * Copyright (c) 2003 Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 *
 * This file is not distributed under the standard GeekOS license.
 * Publication or redistribution of this file without permission of
 * the author(s) is prohibited.
 */
/*************************************************************************/
/*
 * Signals
 * $Rev $
 * 
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "COPYING".
 */

#include <geekos/kassert.h>
#include <geekos/defs.h>
#include <geekos/screen.h>~/
#include <geekos/int.h>
#include <geekos/mem.h>
#include <geekos/symbol.h>
#include <geekos/string.h>
#include <geekos/kthread.h>
#include <geekos/malloc.h>
#include <geekos/user.h>
#include <geekos/signal.h>
#include <geekos/projects.h>


/* Called when signal handling is complete. */
void Complete_Handler(struct Kernel_Thread *kthread,
                      struct Interrupt_State *state) {
    KASSERT(kthread);
    KASSERT(state);
    
    kthread->userContext->curr_sig = 0;
    struct User_Interrupt_State *userS = (struct User_Interrupt_State *) state;
    userS->espUser += sizeof(ulong_t);
    
    Copy_From_User(kthread->esp, userS->espUser, sizeof(struct Interrupt_State));

    userS->espUser+= sizeof(struct Interrupt_State);
}



#if 1
void Print_IS(struct Interrupt_State *esp) {
    void **p;
    Print("esp=%x:\t", (unsigned int)esp);
    Print("  gs=%x\t", (unsigned int)esp->gs);
    Print("  fs=%x\t", (unsigned int)esp->fs);
    Print("  es=%x\t", (unsigned int)esp->es);
    Print("  ds=%x\t", (unsigned int)esp->ds);
    Print("  ebp=%x\t", (unsigned int)esp->ebp);
    Print("  edi=%x\t", (unsigned int)esp->edi);
    Print("  esi=%x\t", (unsigned int)esp->esi);
    Print("  edx=%x\t", (unsigned int)esp->edx);
    Print("  ecx=%x\t", (unsigned int)esp->ecx);
    Print("  ebx=%x\t", (unsigned int)esp->ebx);
    Print("  eax=%x\t", (unsigned int)esp->eax);
    Print("  intNum=%x\t", (unsigned int)esp->intNum);
    Print("  errorCode=%x\t", (unsigned int)esp->errorCode);
    Print("  eip=%x\t", (unsigned int)esp->eip);
    Print("  cs=%x\t", (unsigned int)esp->cs);
    Print("  eflags=%x\t", (unsigned int)esp->eflags);
    p = (void **)(((struct Interrupt_State *)esp) + 1);
    Print("esp+n=%x\t", (unsigned int)p);
    Print("esp+n[0]=%x\t", (unsigned int)p[0]);
    Print("esp+n[1]=%x\n", (unsigned int)p[1]);
}

void dump_stack(unsigned int *esp, unsigned int ofs) {
    int i;
    Print("Setup_Frame: Stack dump\n");
    for (i = 0; i < 25; i++) {
        Print("[%x]: %x;  ", (unsigned int)&esp[i] + ofs, esp[i]);
    }
}
#endif


int Send_Signal(struct Kernel_Thread *kthread, int sig_num){
  if(!IS_SIGNUM(sig_num))
    return -1;
  if(kthread == NULL)
    return -1;
  if(kthread->userContext == NULL)
    return -1;
  //check kernels, signums, kthread==null
  kthread->userContext->pending[sig_num-1] = 1;
  return 0;
}

int Check_Pending_Signal(struct Kernel_Thread *kthread,
                         struct Interrupt_State *state) {
    int i;
    KASSERT(kthread);
    KASSERT(state);

	for(i = 0; i < MAXSIG; i++){
		if(kthread->userContext->pending[i] != 0){
			if(state->cs != KERNEL_CS){
				if(kthread->userContext->curr_sig != 1)
					return 1;
			}
		}
	}	
    return 0;
}

int Set_Handler(signal_handler sig, int sig_num, struct Kernel_Thread *kthread){

	if(sig_num > MAXSIG)
	  return -1;
	
	kthread->userContext->sig_h[sig_num-1] = sig;
	return 0;
}

void Setup_Frame(struct Kernel_Thread *kthread, struct Interrupt_State *state) {
  signal_handler sig;
  int i;
  struct User_Interrupt_State *user;
  KASSERT(kthread);
  KASSERT(state);

  if(kthread->userContext == NULL)
    Exit(-1);
  //get pending process
  for(i= 0; i < MAXSIG;i++){
    if(kthread->userContext->pending[i] == 1){
      break;
    }
  }
  //set up a user process's user stack and kernel stack
  //execute the correct signal handler
  //invoke the Sys_ReturnSignal system call to go back to what it was doing
  //IF instead the process is relying on SIG_IGN or SIG_DFL, handle the signal within the kernel. 
  if(kthread->userContext->sig_h[i]== SIG_DFL){
    Print("Terminated %d.\n", g_currentThread->pid);
    Exit(-1);
  }else if(kthread->userContext->sig_h[i] == SIG_IGN){
    return;
  }else{
    kthread->userContext->curr_sig = i+1;
    kthread->userContext->pending[i] = 0;
    user  = (struct User_Interrupt_State*) state;
    //	Choose the correct handler to invoke.
    sig = kthread->userContext->sig_h[i];
    //	Acquire the pointer to the top of the user stack. This is below the saved interrupt state stored on the kernel stack as shown in the figure above.
    
    user->espUser = user->espUser - sizeof(struct Interrupt_State);
    Copy_To_User(user->espUser, kthread->esp, sizeof(struct Interrupt_State));



    //Signum
    user->espUser = user->espUser - sizeof(ulong_t);
    Copy_To_User(user->espUser, &i, sizeof(ulong_t));
    
    //Trampoline function
    user->espUser = user->espUser - sizeof(ulong_t);
    Copy_To_User(user->espUser, &kthread->userContext->tramp, sizeof(ulong_t));

    
    state->eip = kthread->userContext->sig_h[i];
  }
  

}
