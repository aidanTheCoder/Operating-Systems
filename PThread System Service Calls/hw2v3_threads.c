#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void* thingForThreadToThreadThrough(void* unNamedPointer);

int main() {
  pthread_t thread = 0;
  int threadError = 0;
  int joinError = 0;
  printf("main thread here; pid is %d, tid is %lu \n",
         getpid(), pthread_self());
  if((threadError = pthread_create(&thread, NULL, 
                               &thingForThreadToThreadThrough,
                               (char*)'B'))) {
    printf("Uh-Oh: %s \n",strerror(threadError));
  } else {
    printf("main successfully created a new thread with TID of %lu \n",
           thread);
    if((joinError = pthread_join(thread, NULL))) {
      printf("Error joining thread: %s \n", strerror(joinError));
    }
  }
  printf("main thread has terminated, main will now exit. \n"); 
  return 0;
}

void* thingForThreadToThreadThrough(void* unNamedPointer) {
  printf("New thread here. My TID is %lu, but my PID is %d \n",
         pthread_self(), getpid());
  if(unNamedPointer != NULL) {
    printf("I received a '%c' when I was created. \n",
           (char*)unNamedPointer); 
  }
  return NULL;
}
