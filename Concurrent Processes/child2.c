
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Process %d now running program 'child2.exe'\n\
          \rMy parent's PID is %d \n", getpid(), getppid());
  return 0;
}
