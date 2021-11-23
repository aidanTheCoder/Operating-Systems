#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void* thingForThreadToThreadThrough(void* unNamedPointer);

int main() {
  pthread_t thread = 0;
  int threadError = 0;
  printf("main thread here; pid is %d, tid is %lu \n",
         getpid(), pthread_self());
  threadError = pthread_create(&thread, NULL, 
                               &thingForThreadToThreadThrough, NULL);
  if (threadError) {
    printf("Uh-Oh: %s \n",strerror(threadError));
  } else {
    printf("main successfully created a new thread with TID of %lu \n",
           thread);
  }
  return 0;
}

void* thingForThreadToThreadThrough(void* unNamedPointer) {
  printf("New thread here. My TID is %lu, but my PID is %d \n",
         pthread_self(), getpid());
  return NULL;
}
