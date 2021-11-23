#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void* thingForThreadToThreadThrough(void* pointerToUndefinedType);

int shareableBetweenThreads = 0;

int main() {
  pthread_t thread = 0;
  int threadStatus = 0;
  printf("Main: PID is %d \n", getpid());
  if((threadStatus = pthread_create(&thread, NULL, 
                           &thingForThreadToThreadThrough, NULL))) {
    printf("Damn: %s", strerror(threadStatus));
    return 1;
  } else {
    printf("Main: Successfully created thread with TID of %lu \n",
           thread);
  }
  printf("Main: Enter a non-zero integer so that the other \
         \n\rthread can get out of its sping loop: ");
  scanf("%d", &shareableBetweenThreads);
  while(shareableBetweenThreads != 0)
    ;
  printf("Main: Second thread has re-zeroed the shared variable, \
         \n\rso I'm done. \n");
  return 0;
}

void* thingForThreadToThreadThrough(void* pointerToUndefinedType) {
  printf("\nSecond thread: My TID is %lu, still in process %d;\n",
         pthread_self(), getpid());
  printf("I'm About ot spin until main enters a non-zero \
         \n\rvalue into the shared variable. \n");
  while(shareableBetweenThreads == 0)
    ;
  printf("Second thread: Main set the shared variable to %d; \
         \n\rI'll set it back to zero and then I'm done. \n",
         shareableBetweenThreads);
  shareableBetweenThreads = 0;
  return NULL;
}
