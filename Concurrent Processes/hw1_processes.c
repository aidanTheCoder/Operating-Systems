#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid = 0;
  int count = 0;
  const int PARENTPID = getpid();
  for (count = 1; count <= 3; ++count) {
    if(PARENTPID == getpid()) {
      pid = fork();
      if(pid < 0) {
        printf("Fork Failed \n");
      } else if((pid == 0)) {
        printf("I am child #%d, my pid is %d; my parent's \
                \n\rpid is %d \n", count, getpid(), getppid());
        if (count == 2) {
          execv("newChild2.exe", (char* const*)"Hello World!");
        }
      } else {
        printf("Parent, my pid is %d: Spawned child #%d \
                \n\rwhose pid is %d \n", getpid(), count, pid);
      }
    }
  }
  return 0;
}
