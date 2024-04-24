/*
 * Use sleep to control program output */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int s = 0; /* shared variable */


void* f_thread_0(void *v) {

  s = 0;
  printf("Thread 0, s = %d.\n", s); 
  
  return NULL;
}

void* f_thread_1(void *v) {
  s = 1;
  sleep(3);
  printf("Thread 1, s = %d.\n", s); 
  
  return NULL;
}

int main() {

  pthread_t thr0, thr1;

  pthread_create(&thr1, NULL, f_thread_1, NULL);
  pthread_create(&thr0, NULL, f_thread_0, NULL);


  pthread_join(thr0, NULL); 
  pthread_join(thr1, NULL);
  
  return 0;
}

