/*
 * Alternate with interest.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int s = 0; /* shared variable */
volatile int order = 1; /* which thread enters the critical section */
volatile int interested[2] = {0, 0}; /* which threads are interested in accesing the critical section */

void* f_thread_0(void *v) {
  int i;

  for (i = 0; i < 10; i++) {
    interested[0] = 1; /* marks thread as interested */
    while (interested[1] && order != 0); 

    s = 0;
    printf("Thread 0, s = %d.\n", s); 
  
    order = 1;           /* pass order to the other thread */
    interested[0] = 0;  /* marks thread leaves the critical sectioon */
    sleep(1);
  }
  return NULL;
}

void* f_thread_1(void *v) {
  int i;

  for (i = 0; i < 10; i++) {
    interested[1] = 1; /* marks thread as interested */
    while (interested[0] && order != 1);

    s = 1;
    printf("Thread 1, s = %d.\n", s); 
  
    order = 0;           /* pass order to the other thread */
    interested[1] = 0;  /* marks thread leaves the critical sectioon */
    sleep(2);
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

