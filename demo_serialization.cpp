//
// Example from: http://www.amparo.net/ce155/sem-ex.c
//
// Adapted using some code from Downey's book on semaphores
//
// Compilation:
//
//       g++ serialization.cpp -lpthread -o serial -lm
//
//
//
/* Includes */

#include "semaphore_class.h"


int Total = 0;

/* prototype for thread routine */
void *threadC ( void *ptr );
void *threadB ( void *ptr );
void *threadA ( void *ptr );


/* global vars */
/* semaphores are declared global so they can be accessed
 in main() and in thread routine. */
Semaphore B_Done(0);

Semaphore A_Done(0);


Semaphore Mutex(1);   // mutual exclusion lock


int main()
{
    int i[3];
    pthread_t thread_a;
    pthread_t thread_b;
    pthread_t thread_c;

    i[0] = 0; /* argument to threads */
    i[1] = 1;
    i[2] = 2;

    
    /* Note: you can check if thread has been
     successfully created by checking return value of
     pthread_create */
    pthread_create (&thread_a, NULL, threadA, (void *) &i[0]);
    pthread_create (&thread_b, NULL, threadB, (void *) &i[1]);
 //   pthread_create (&thread_c, NULL, threadC, (void *) &i[2]);

    
    // Join threads
    (void) pthread_join(thread_a, NULL);
    (void) pthread_join(thread_b, NULL);
 //   (void) pthread_join(thread_c, NULL);
    
    /* exit */
    exit(0);
    
} /* main() */


void *threadA ( void *ptr )
{
    int x;
    x = *((int *) ptr);
    
    
 /*   B_Done.wait();   // Blocks itself if this thread runs first than Thread B.

    printf("Thread %d: Statement A: Must run after Statement B. \n", x);
    fflush(stdout);
    
    A_Done.signal();
    
    //sleep(5);
 */
    
    
    Mutex.wait();
        Total = Total + 10;
        std::cout << "A second common use for semaphores is to enforce mutual exclusion. We have already seen one use for mutual exclusion, controlling concurrent access to shared variables. The mutex guarantees that only one thread accesses the shared variable at a time. "
            << std::endl << "Total = " << Total << std::endl;
    Mutex.signal();
    
    
    
    
    
    
    pthread_exit(0); /* exit thread */
}

void *threadB ( void *ptr )
{
    int x;
    x = *((int *) ptr);
    
    
    
    // There is no wait. This thread is free to continue and print the statement.
//    sleep(4);
    
    
//    printf("Thread %d: Statement B: Must run before Statement A. \n", x);
//    fflush(stdout);
    //sleep(2);

    
    
//    B_Done.signal();
    
    
    
    Mutex.wait();
        Total = Total - 10;
        std::cout << "A second common use for semaphores is to enforce mutual exclusion. We have already seen one use for mutual exclusion, controlling concurrent access to shared variables. The mutex guarantees that only one thread accesses the shared variable at a time. "
        << std::endl << "Total = " << Total << std::endl;
    Mutex.signal();

    
    pthread_exit(0); /* exit thread */
}

void *threadC ( void *ptr )
{
    int x;
    x = *((int *) ptr);
    
    //A_Done.wait();
    
    
    
    printf("Thread %d: Statement C: Must run after Statement A. \n", x);
    fflush(stdout);
    
    //B_Done.signal();
    
    
    pthread_exit(0); /* exit thread */
}

