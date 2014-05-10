#include <geekos/user.h>
#include <geekos/syscall.h>
#include <string.h>
#include <stdlib.h>

int main(){
  struct Process_Info arr[50];
  int psSize = PS(arr, 50);
  int i = 0; 
  char status;
  Print("PID PPID PRIO STAT COMMAND\n");
  while(i < psSize){
    if(arr[i].status == 0)
      status = 'R';
    else if(arr[i].status == 1)
      status = 'B';
    else
      status = 'Z';
    Print("%3d %4d %4d %4c %s\n",arr[i].pid, arr[i].parent_pid, arr[i].priority, status, arr[i].name);
    i++;
  }
}
