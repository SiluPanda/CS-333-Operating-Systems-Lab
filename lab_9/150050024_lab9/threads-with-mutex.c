#include <pthread.h>
#include <stdio.h>

#define NTHREADS 100

long int counter = 0;

//	The thread starter function

pthread_mutex_t lock; //define a mutex variable


void *myThread()
{

	pthread_mutex_lock(&lock);//lock the mutex
	for(int i=0; i<1000; i++){
		counter++;
	}
	pthread_mutex_unlock(&lock);//unlock the mutex
}

int main()
{
	// Create space for pthread variables
	pthread_t tid[NTHREADS];
	pthread_mutex_init(&lock, NULL);

	if (pthread_mutex_init(&lock, NULL)) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 

	for(int i=0; i<NTHREADS; i++)
	{
		//	Create a thread with default attributes and no arguments
		pthread_create(&tid[i], NULL, myThread, NULL);
	}

	for(int i=0; i<NTHREADS; i++)
	{
		//	Wait for all threads to finish
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&lock);

	printf("Counter: %ld \n", counter);

	return 0;
}
