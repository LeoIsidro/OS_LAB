/*
 * Dijkstra algorithm(modified, for similarity with previous examples)
 *
 * Sleeps to cause starvation.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

volatile int s = 0; /* Shared variable */
volatile int order = -1; /* which thread has priority to access the critical section */
volatile int interested[N] = {0, 0, 0, 0, 0}; /* vector of interested threads in the critical section *//

volatile int timesexecuted[ N ] = { 0, 0, 0, 0, 0 };

volatile int counterResources = 50;

int exist_other_th_interested(int thr_id) {
  int i;
  for (i = 0; i < N; i++) 
    if (i != thr_id && interested[i])
      return 1;
  return 0;
}

void* f_thread(void *v) {
  int thr_id = *(int*)v;

  while ( 1 ) {
    interested[thr_id] = 1; /* Marca que esta thread está interessada */
    
    /* Here we synchronize all the threads. Security: all threads have interest*/
    sleep(1);
	  
    while (exist_other_th_interested(thr_id)){
      if (order != thr_id) {
	  
	/* all th sleep, for all enter the "blocking"/*/
	sleep( 1 );
	
	interested[thr_id] = 0; 
	while (order != -1);
         /*Always: thread 1 will be the first to gain order*/
	if( thr_id == 1 ) 
	  sleep( 1 );
	else
	  sleep( 2 );
	order = thr_id;
	/*sync again all threads*/
	if( thr_id == 1 ) 
	  sleep( 2 );
	else
	  sleep( 1 );
	interested[thr_id] = 1;
	sleep(1);	
      }
    }

    if( counterResources <= 0 ) {
      order = -1;
      interested[thr_id] = 0;
      return NULL;
    }    
		
    s = thr_id;
    printf("Thread %d, s = %d.\n", thr_id, s);
    timesexecuted[ thr_id ] ++;
    counterResources --;
    
    order = -1;
    interested[thr_id] = 0;  /* marks thread leaving critical section */
    
    
    sleep(1); /* allows the other thread to execute */

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

  for( i = 0; i < N; i ++ ) {
		printf( "Thread %d executed %d times\n", i, timesexecuted[ i ] );
  }
  
  return 0;
}

