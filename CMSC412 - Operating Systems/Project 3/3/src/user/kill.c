#include <conio.h>
#include <process.h>
#include <string.h>
#include <signal.h>

void testHandle(){
  Print("Handler reached\n");
}

int main(int argc, char **argv) {
  int pid, ret, i = 1;
  Signal(&testHandle, 2);
  Signal(SIG_DFL, 2);
  while(i < argc){
    pid = atoi(argv[i]);
    ret = Kill(pid, 2);
    if(ret < 0) //error killing process, exit
      return ret;
    i++;
  }
  return 0;
}
