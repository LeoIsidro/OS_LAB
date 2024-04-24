/*
 * Vector of interest with sleep. 
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int s = 0; /* shared variable */
volatile int interest[2] = {0, 0}; /* which threads are interested? */

void* f_thread_0(void *v) {
  int i;

  for (i = 0; i < 10; i++) {
    interest[0] = 1; /* Mark interested thread */
    while (interest[1]) {
      interest[0] = 0;
      sleep(1);
      interest[0] = 1;
    }
  
    s = 0;
    printf("Thread 0, s = %d.\n", s); 
  
    interest[0] = 0;  /* Mark it leaves the critsec */
  }
  return NULL;
}

void* f_thread_1(void *v) {
  int i;

  for (i = 0; i < 10; i++) {
    interest[1] = 1; /* Mark interested thread */
    while (interest[0]) {
      interest[1] = 0;
      sleep(1);
      interest[1] = 1;
    }
  
    s = 1;
    printf("Thread 1, s = %d.\n", s); 
  

    interest[1] = 0;  /* Mark it leaves the critsec */
  }
  return NULL;
}

int main() {

  pthread_t thr0, thr1;

  pthread_create(&thr0, NULL, f_thread_0, NULL);
  pthread_create(&thr1, NULL, f_thread_1, NULL);

  pthread_join(thr0, NULL); 
  pthread_join(thr1, NULL);
  
  return 0;
}

