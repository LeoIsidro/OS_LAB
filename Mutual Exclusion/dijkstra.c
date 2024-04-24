/*
 * Dijkstra algorithm(modified, for similarity with previous examples)
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

volatile int s = 0; /* shared variable */
volatile int order = -1; /* which thread has priority to access the critical section */
volatile int interest[N] = {0, 0, 0, 0, 0}; /* vector of interested threads in the critical section */


int exist_other_th_interested(int thr_id) {
  int i;
  for (i = 0; i < N; i++) 
    if (i != thr_id && interest[i])
      return 1;
  return 0;
}

void* f_thread(void *v) {
  int thr_id = *(int*)v;
  int i;

  for (i = 0; i < 10; i++) {
    interest[thr_id] = 1; /* mark the thread as interested */
    while (exist_other_th_interested(thr_id)){
      if (order != thr_id) {
	interest[thr_id] = 0; 
	while (order != -1);
	order = thr_id;
	if (thr_id == 2)
	  sleep(4);	
	interest[thr_id] = 1; 
      }
    }
    
    s = thr_id;
    printf("Thread %d, s = %d.\n", thr_id, s); 
  
    order = -1;
    interest[thr_id] = 0;  /* mark the thread leaving the critical section */
    
    sleep(1); /* Allows the other thread to execute */

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

