/*
 * N threads vector of interest.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

volatile int s = 0; /* shared variable */
volatile int interest[N] = {0, 0, 0, 0, 0}; /* which threads are interested in the critical section */

int exist_other_thread_interested(int i) {
  int k;
  for (k = 0; k < N; k++) 
    if (k != i && interest[k])
      return 1;
  return 0;
}

void* f_thread(void *v) {
  int i = *(int*)v;
  int k;

  for (k = 0; k < 5; k++) {
    interest[i] = 1; /* mark thread as interested */
    while (exist_other_thread_interested(i));
  
    s = i;
    printf("Thread %d, s = %d.\n", i, s); 
  
    interest[i] = 0;  /* mark thread leaving critical section */
  }
  return NULL;
}

int main() {

  pthread_t thr[N];
  int id[N], k;

  for (k = 0; k < N; k++) {
    id[k] = k;
    pthread_create(&thr[k], NULL, f_thread, &id[k]);
  }

  for (k = 0; k < N; k++) 
    pthread_join(thr[k], NULL); 

  return 0;
}

