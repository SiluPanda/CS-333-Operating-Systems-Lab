#include <pthread.h>
#include <stdio.h>

long long int counter[10];
pthread_mutex_t lock[10];

void *myThread(void *arg)
{
	int *p = (int *) arg;
	int id = *p;
	
	pthread_mutex_lock(&lock[id]);//lock the mutex
	for(int i=0; i<1000; i++){
		counter[id]++;
	}
	pthread_mutex_unlock(&lock[id]);//unlock the mutex
}

int main()
{
	// Create space for pthread variables
	pthread_t tid[10];



	for (int i = 0; i < 10; ++i)
	{
		pthread_mutex_init(&lock[i], NULL);
	

 	


	
		
		pthread_create(&tid[i], NULL, myThread, (void*)&i);
	


	//join
	
		//	Wait for all threads to finish
		pthread_join(tid[i], NULL);
	



	//destroy
	
		pthread_mutex_destroy(&lock[i]);
	}

	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			counter[j]++;
		}
	}



	//print
	for (int i = 0; i < 10; ++i)
	{
		
	
		printf("Counter: %lld \n", counter[i]);
	}

	return 0;
}