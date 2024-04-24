/*
 * Simple critical section control by changing order
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int s = 0; /* shared variable */
volatile int order = 0; /* defines the order to enter the critical section */

void* f_thread_0(void *v) {
  int i;

  for (i = 0; i < 5; i++) {
    while (order != 0); /* wait for thread order */
  
    s = 0;
    printf("Thread 0, s = %d.\n", s); 
  
    order = 1; /* pass the order to the other thread */
    sleep(1);    
  }
  return NULL;
}

void* f_thread_1(void *v) {
  int i;

  for (i = 0; i < 5; i++) {
    while (order != 1); /* wait for thread order */
  
  s = 1;
  printf("Thread 1, s = %d.\n", s); 
  
  order = 0; /* pass the order to the other thread */
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

