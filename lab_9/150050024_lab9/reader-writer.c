#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


struct read_write_lock
{	
	pthread_mutex_t mutex;
	int r_ac;
	int w_ac;
	int w_wait;
	pthread_cond_t reader;
	pthread_cond_t writer;
}rwlock;

long int data = 0;			//	Shared data variable

void InitalizeReadWriteLock(struct read_write_lock * rw)
{

		pthread_mutex_init(&rw->mutex,NULL);

		rw->r_ac=0;
		rw->w_ac=0;
		rw->w_wait=0;

		pthread_cond_init(&rw->reader,NULL);
		pthread_cond_init(&rw->writer,NULL);
}


// The pthread based reader lock
void ReaderLock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);
	while(rw->w_ac!=0 || rw->w_wait > 0)


	{
		pthread_cond_wait(&rw->reader,&rw->mutex);
	}
	rw->r_ac+=1;

	pthread_mutex_unlock(&rw->mutex);
}	

// The pthread based reader unlock
void ReaderUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);



	rw->r_ac--;


	if(rw->r_ac==0){
		pthread_cond_signal(&rw->writer);
	}

	pthread_mutex_unlock(&rw->mutex);
}

// The pthread based writer lock
void WriterLock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);
	rw->w_wait+=1;
	while(rw->w_ac > 0  || rw->r_ac > 0){
		pthread_cond_wait(&rw->writer,&rw->mutex);
	}
	rw->w_wait--;
	rw->w_ac+=1;
	pthread_mutex_unlock(&rw->mutex);
}

// The pthread based writer unlock
void WriterUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);

	rw->w_ac--;

	pthread_cond_signal(&rw->writer);
	pthread_cond_broadcast(&rw->reader);
	pthread_mutex_unlock(&rw->mutex);

}

//	Call this function to delay the execution by 'delay' ms
void delay(int delay)
{
	struct timespec wait;

	if(delay <= 0)
		return;

	wait.tv_sec = delay / 1000;
	wait.tv_nsec = (delay % 1000) * 1000 * 1000;
	nanosleep(&wait, NULL);
}
struct argument_t{
	int thread_id;
	int delay;
};
// The pthread reader start function
void *ReaderFunction(void *args)
{

	struct argument_t *arguments = (struct argument_t *) args;
	delay(arguments->delay);
	ReaderLock(&rwlock);
	printf("\tReader  %d, data: %ld\n",arguments->thread_id,data);
	delay(1);
	ReaderUnlock(&rwlock);
}




// The pthread writer start function
void *WriterFunction(void *args)
{
	struct argument_t *arguments = (struct argument_t *) args;
	delay(arguments->delay);
	WriterLock(&rwlock);
	data++;
	printf("Writer  %d, data: %ld\n",arguments->thread_id,data);
	delay(1);
	WriterUnlock(&rwlock);
	
	
}

int main(int argc, char *argv[])
{
	pthread_t *threads;
	struct argument_t *arg;
	
	long int reader_number = 0;
	long int writer_number = 0;
	long int thread_number = 0;
	long int total_threads = 0;	
	
	int count = 0;			// Number of 3 tuples in the inputs.	Assume maximum 10 tuples 
	int rws[10];			
	int nthread[10];
	int delay[10];

	//	Verifying number of arguments
	if(argc<4 || (argc-1)%3!=0)
	{
		printf("reader-writer <r/w> <no-of-threads> <thread-arrival-delay in ms> ...\n");		
		printf("Any number of readers/writers can be added with repetitions of above mentioned 3 tuple \n");
		exit(1);
	}

	//	Reading inputs
	for(int i=0; i<(argc-1)/3; i++)
	{
		char rw[2];
		strcpy(rw, argv[(i*3)+1]);

		if(strcmp(rw, "r") == 0 || strcmp(rw, "w") == 0)
		{
			if(strcmp(rw, "r") == 0)
				rws[i] = 1;					// rws[i] = 1, for reader
			else
				rws[i] = 2;					// rws[i] = 2, for writer
			
			nthread[i] = atol(argv[(i*3)+2]);		
			delay[i] = atol(argv[(i*3)+3]);

			count ++;						//	Number of tuples
			total_threads += nthread[i];	//	Total number of threads
		}
		else
		{
			printf("reader-writer <r/w> <no-of-threads> <thread-arrival-delay in ms> ...\n");
			printf("Any number of readers/writers can be added with repetitions of above mentioned 3 tuple \n");
			exit(1);
		}
	}

	InitalizeReadWriteLock(&rwlock);
	pthread_t pthread[total_threads];
	for (int j = 0; j < count; ++j)
	{
		for (int i = 0; i < nthread[j]; ++i)
		{
			
			 if(rws[j]==1){
			 	reader_number++;
			 	struct argument_t *arg= malloc(sizeof(struct argument_t));
			 	arg->thread_id=reader_number;
			 	arg->delay=delay[j];
			 	pthread_create(&pthread[thread_number], NULL, ReaderFunction,arg);
			 }
			 else{
			 	writer_number++;
			 	struct argument_t *arg= malloc(sizeof(struct argument_t));
			 	arg->thread_id=writer_number;
			 	arg->delay=delay[j];
			 	pthread_create(&pthread[thread_number], NULL, WriterFunction,arg);
			 }
			 thread_number++;
		}
		
	}
	for(int i=0; i<total_threads; i++)
	{
		//	Wait for all threads to finish
		pthread_join(pthread[i], NULL);
	}

	//	Create reader/writer threads based on the input and read and write.

	//  Clean up threads on exit

	exit(0);
}
