/* Josh Fann
   jfann 109901918
   Project 4
*/

/*
  This project implements a simple shell, much like the putty shell has
  have been using for all your work on the Linux Grace machines. You will 
  use your knowledge of file operations and process control to effect file
  redirection, backgrounding, and program pipelines.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "wait.h"
#include "execute.h"

#define EXECERR printf("Error executing command\n"); exit(-1);

void execute_command_line(Command_line *cmd) {

  int fd[2], pid, par_id, i;
  if(cmd == NULL){
    EXECERR;
  }
  /* Fork parent process */
  par_id= fork();
  if(par_id < 0){
    EXECERR;
  }
  if(par_id){
    wait(NULL);
  }else{
    
    
    /*Backgrounding: if a command line ends with an ampersand ("&"), 
      then the shell should execute the program(s) and immediately return to 
      the shell prompt, not waiting for the backgrounded program/pipeline to 
      terminate. The backgrounded program/pipeline should continue to print its 
      output to standard output/error as if it were not backgrounded. If 
      standard input is not redirected from a file, then the process should 
      have its standard input closed before exec'ing (this is different from 
      normal shell behavior; however, normal shells provide foregrounding 
      capabilities, which we are not requiring in this project). This means
      that some programs will have errors when run in the background, but that 
      is the user's fault for not handling input properly, not yours.
    */
    if(cmd->bg){
      /*Fork child process.  Child process exits.  Grandchild executes.*/
      pid = fork();
      if(pid < 0){
	EXECERR;
      }
      if(pid){ /*Child process*/
	if(cmd->infile == NULL)
	  close(STDIN_FILENO);
	exit(-1);
      }
    }/* Grandchild process runs rest of code*/

    /* Redirection*/
  /* File redirection: by using the <, >, and >> tokens, a user should be able 
     to redirect standard input and output in the same manner as is done in the 
     tcsh and bash shells (i.e., redirect standard input, redirect standard 
     output with truncation, and redirect standard output by appending, 
     respectively).

     The proper permission mask for doing that is defined in the execute.h file.
     In the case of a multi-program pipeline, file input redirection must be 
     applied to the first program (before the first pipe character), and file 
     output redirection be applied to the final program.
  */
    /*Input Redirection*/
    if(cmd->infile){
      fd[0] = open(cmd->infile, O_RDONLY);
      if(fd[0] == -1){
	EXECERR;
      }
      if(dup2(fd[0], STDIN_FILENO) < 0){
	EXECERR;
      }
      close(fd[0]);      
    }

  /* Output Redirection*/
  /* If a file is created by output redirection, the file should be created 
     readable and writable for all users.
  */
    if(cmd->outfile){
      if(cmd->append){
	fd[1] = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, DEF_MODE);
	if(fd[1] == -1){
	  EXECERR;
	}
      }
      else{
	fd[1] = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, DEF_MODE);
	if(fd[1] == -1){
	  EXECERR;
	}
      }  
      if(dup2(fd[1], STDOUT_FILENO) < 0){
	EXECERR;
      }
      close(fd[1]);
    }



   /*Piping: if programs are separated by pipe characters ("|") on a command
      line, then the standard output of the program to the left of the pipe
      character is to be connected to the standard input of the program to the 
      right of the pipe character, creating a pipeline. Notice that when running
      a pipeline in a shell such as tcsh or bash, the shell does not return to 
      the prompt until the entire pipeline is completed (unless the pipeline is 
      backgrounded). You will need to determine how to fork processes and then 
      wait for them to cause similar behavior in your shell.
    */
    if(cmd->num_progs > 1){
      for(i = 1; i < cmd->num_progs; i++){
	if(pipe(fd) == -1){
	  EXECERR;
	}
	pid = fork();
	if(pid < 0){
	  EXECERR;
	}
	/* Child Code */
	else if(pid){
	  wait(NULL);
	  close(fd[1]);
	  
	  if(dup2(fd[0], STDIN_FILENO) < 0){
	    EXECERR;
	  }
	  if(i == cmd->num_progs - 1){
	    execvp(cmd->argvs[i][0], cmd->argvs[i]);
	    EXECERR;
	  }
	}
	/* G-Child Code */
	else{
	  
	  close(fd[0]);
	  if(dup2(fd[1], STDOUT_FILENO) < 0){
	    EXECERR;
	  }
	  execvp(cmd->argvs[i-1][0], cmd->argvs[i-1]);
	  EXECERR;
	}
      }
    }
    else{
      execvp(cmd->argvs[0][0], cmd->argvs[0]);
      EXECERR;
    }
  }
}
