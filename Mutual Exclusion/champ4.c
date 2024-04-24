/* 
 * Champion for 4 threads.
 *
 * Homework: modify this code for N threads.
 *
 * Put a sleep in the following points:
 *   - between matches (battles);
 *   - between the atribution of variable s and the print of this variable value
 *   - outside the critical region.  
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Number of times a thread must enter the critical section. */
#define N_TIMES 15

/* Shared variable */
volatile int s = 0;

/* Control variables for the final battle. */
int last_final = 0;
int interest_final[2] = { 0, 0 };

/* Control variables for match between thread 0 and thread 1.      */
int last_01 = 0;
int interest_01[2] = { 0, 0 };

/* Control variables for match between thread 2 and thread 3.      */
int last_23 = 0;
int interest_23[2] = { 0, 0 };

/* Thread 0 function */
void* f_thread_0(void *v) {
  int i;
  
  for (i = 0; i < N_TIMES; i++) {

    interest_01[0] = 1;
    last_01 = 0;
    while (last_01 == 0 && interest_01[1]) ; 

    sleep(1); /* Sleep between matches */
     
    interest_final[0] = 1;
    last_final = 0;
    
    while (last_final == 0 && interest_final[1]) ; 

    s = 0;
    sleep(1); /* Sleep between atribution and print */    
    printf("Thread 0, s = %d.\n", s); 

    interest_final[0] = 0;    
    interest_01[0] = 0;

    sleep(1); /* Sleep out of critical section */
  }

  return NULL;
}

/*  thread 1 function */
void* f_thread_1(void *v) {
  int i;
  
  for (i = 0; i < N_TIMES; i++) {

    interest_01[1] = 1;
    last_01 = 1;
    while (last_01 == 1 && interest_01[0]) ; 

    sleep(1); /* Sleep between matches */
    
    interest_final[0] = 1;
    last_final = 1;
    
    while (last_final == 1 && interest_final[1]) ; 

    s = 1;
    sleep(1); /* Sleep between atribution and print */     
    printf("Thread 1, s = %d.\n", s); 

    interest_final[0] = 0;    
    interest_01[1] = 0;

    sleep(1); /* Sleep out of critical section*/    
  }

  return NULL;
}

/* thread 2 function */
void* f_thread_2(void *v) {
  int i;
  
  for (i = 0; i < N_TIMES; i++) {

    interest_23[0] = 1;
    last_23 = 2;
    while (last_23 == 2 && interest_23[1]) ; 

    sleep(1); /* Sleep between matches */
    
    interest_final[1] = 1;
    last_final = 2;
    while (last_final == 2 && interest_final[0]) ; 

    s = 2;
    sleep(1); /* Sleep between atribution and print */        
    printf("Thread 2, s = %d.\n", s); 

    interest_final[1] = 0;    
    interest_23[0] = 0;

    sleep(1); /* Sleep out of critical section */    
  }

  return NULL;
}

/* thread 3 function */
void* f_thread_3(void *v) {
  int i;
  
  for (i = 0; i < N_TIMES; i++) {

    interest_23[1] = 1;
    last_23 = 3;
    while (last_23 == 3 && interest_23[0]) ; 

    sleep(1); /* Sleep between matches */
    
    interest_final[1] = 1;
    last_final = 3;
    while (last_final == 3 && interest_final[0]) ; 

    s = 3;
    sleep(1);    
    printf("Thread 3, s = %d.\n", s); 

    interest_final[1] = 0;    
    interest_23[1] = 0;

    sleep(1); /* Sleep out of critical section */    
  }

  return NULL;
}

int main() {

  pthread_t thr0, thr1, thr2, thr3;

  pthread_create(&thr0, NULL, f_thread_0, NULL);
  pthread_create(&thr1, NULL, f_thread_1, NULL);
  pthread_create(&thr2, NULL, f_thread_2, NULL);
  pthread_create(&thr3, NULL, f_thread_3, NULL);

  pthread_join(thr0, NULL); 
  pthread_join(thr1, NULL); 
  pthread_join(thr2, NULL); 
  pthread_join(thr3, NULL); 

  return 0;
}

