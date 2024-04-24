/*
 * Control critical section, alternate. For N threads.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

volatile int s = 0; /* shared variable */
volatile int order = 3; /* order thread to enter the critical section */

void* f_thread(void *v) {
  int thr_id = *(int*)v;
  int i;

  for (i = 0; i < 5; i++) {
    while (order != thr_id); /* wait for order, to be equal thread id */
  
    s = thr_id;
    printf("Thread %d, s = %d.\n", thr_id, s); 
  
    order = (thr_id + 1)%N; /* pass the order to other thread */
  }
  return NULL;
}

int main() {

  pthread_t thr[N];
  int id[N], i;

  for (i = 0; i < N; i++) {
    id[i] = i;
    pthread_create(&thr[i], NULL, f_thread, &id[i]);
  }

  for (i = 0; i < N; i++) 
    pthread_join(thr[i], NULL); 

  return 0;
}

