/*
 * Similar to Dekker, but ...!!!
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int s = 0; /* shared variable */
volatile int order = 0; /* thread which has priority enters the critical section */
volatile int interested[2] = {0, 0}; /* which threads are interested in acces the critical section */

void* f_thread_0(void *v) {
  int i;

  for (i = 0; i < 10; i++) {
    interested[0] = 1; /* marks threads as interested */
    sleep(1);
    while (interested[1]) { /* ..while the other thread is in the critical region */  
      interested[0] = 0;
      while (order != 0);  /* wait for its turn */
      interested[0] = 1;
    }
  
    s = 0;
    printf("Thread 0, s = %d.\n", s); 
  
    order = 1;           /* pass the order to the other thread */
    interested[0] = 0;  /* marks it leaves the critical section */
  }
  return NULL;
}

void* f_thread_1(void *v) {
  int i;

  for (i = 0; i < 10; i++) {
    interested[1] = 1; /* marks threads as interested */
    while (interested[0]) {
      interested[1] = 0;
      while (order != 1);
      sleep(1);
      interested[1] = 1;
    }
  
    s = 1;
    printf("Thread 1, s = %d.\n", s); 
  
    order = 0;           /* pass the order to the other thread */
    interested[1] = 0;  /* marks it leaves the critical section */
    sleep(1);
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

