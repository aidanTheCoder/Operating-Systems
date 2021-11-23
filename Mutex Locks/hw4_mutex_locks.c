#include <stdio.h>     
#include <pthread.h>       
#include <errno.h>      
#include <unistd.h>        
#include <string.h>    

void* second_thread(void*);     
                            
struct {                 
  int x;
  int y;                
} race_point = { 0, 0 };

pthread_mutex_t mutexLock = PTHREAD_MUTEX_INITIALIZER;                                                
                                                                                                               
int main() {           
    pthread_t new_tid_no = 0;    
    int errorCode = 0;     
    printf("\n Main:  Initially, race_point is [0,0]; \
           \n\rafter creating another thread, \
           \n\rmain will set it to [1,1]  \n");
    if(pthread_create(&new_tid_no, NULL, second_thread, NULL) == 0) {
        if((errorCode = pthread_mutex_lock(&mutexLock)) != 0) {
            printf("Uh-oh: %s \n", strerror(errorCode));
            return -1;
        }
        race_point.x = 1;     
        sleep(1);          
        race_point.y = 1;     
     if((errorCode = pthread_mutex_unlock(&mutexLock)) != 0) {
        printf("Uh-oh: %s \n", strerror(errorCode));
        return -1;
     }
     if((errorCode = pthread_join(new_tid_no, NULL)) != 0) {                                                          
	    printf("\n  Bad pthread_join: %s", strerror(errorCode));
	    return -1;
	 }
     printf("\n Main now done;");    
     if(race_point.x == race_point.y)
        printf("x = %d and y = %d so there was no race condition\n\n",
               race_point.x, race_point.y); 
     else
        printf(" but since x=%d  while y=%d. \
              \n\r there *HAS* been a race condition.\n\n",
              race_point.x, race_point.y); 
    } else 
        perror("\n No thread created ");    
   return 0;                                                                                                  
} 


void* second_thread(void* dummy) {
    int errorCode = 0;
    if((errorCode = pthread_mutex_lock(&mutexLock)) != 0) {
        printf("Uh-oh: %s \n", strerror(errorCode));
        return NULL;
    }                       
    race_point.x = 2;              
    race_point.y = 2;                        
    if((errorCode = pthread_mutex_unlock(&mutexLock)) != 0) {
        printf("Uh-oh: %s \n", strerror(errorCode));
        return NULL;
    }
    printf("\n   Second thread terminating after setting race_point to [2,2]  \n");
    return NULL;
} 
