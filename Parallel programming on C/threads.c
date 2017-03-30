#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;
pthread_t thread5;


#define max_vector_length 30

int vector[max_vector_length];
int count_overflowing = 0;
int count = 0;

FILE* log_file;

pthread_mutex_t MCR1 = PTHREAD_MUTEX_INITIALIZER;

/* double semaphore for synchronization */
sem_t Sem1;
sem_t Sem2;

/* valued semaphore for prevention overflowing vector  */
sem_t SCR1;


/*------------------------------------------------------------------*/

void* thread_producer(void* arg)
{
	int num = *(int*)arg;
	fprintf(log_file, "In producer thread %d\n", num);
	printf("In producer thread %d\n", num);
	int sem_value;
	while (1) {
		if (count_overflowing >= 4)
				break;
		if (num == 5){
			sem_post(&Sem2);
			sem_wait(&Sem1);
		}
		sem_getvalue(&SCR1,&sem_value);
		if ((count_overflowing == 0) && (sem_value >= max_vector_length - 1))
			count_overflowing++;
		else if ((count_overflowing == 1) && (sem_value <= 0))
			count_overflowing++;
		else if ((count_overflowing == 2) && (sem_value >= max_vector_length - 1))
			count_overflowing++;
		else if ((count_overflowing == 3) && (sem_value <= 0)){
			count_overflowing++;
			break;
		}

		pthread_mutex_lock(&MCR1);
		sem_getvalue(&SCR1,&sem_value);
		if (sem_value < max_vector_length){
			vector[sem_value] = count;
			count++;
			fprintf(log_file, "Producer thread %d: semaphore=%d; element %d CREATED; Overflow count: %d\n",
                    num,sem_value, count - 1, count_overflowing);
			printf("Producer thread %d: semaphore=%d; element %d CREATED; Overflow count: %d\n",
					                        num,sem_value, count - 1, count_overflowing);
			sem_post(&SCR1);
		}
		pthread_mutex_unlock (&MCR1);
		usleep(6);
	}
	fprintf(log_file, "Producer thread %d  stopped !!!\n",num);
	printf("Producer thread %d  stopped !!!\n",num);
	return NULL;
}

/*------------------------------------------------------------------*/

void* thread_consumer (void* arg)
{
	int num = *(int*)arg;
	fprintf(log_file, "In consumer thread %d\n", num);
	printf("In consumer thread %d\n", num);
	int *curr_elem=NULL;
	int sem_value;
	while (1) {

		if (num == 1){
			sem_post(&Sem1);
			while(!sem_trywait(&Sem2)) {
						//commented this row because log file can be very big
						//printf("Consumer thread%d does some useful work (waiting for P5)\n",num); 
				}
		}

		sem_getvalue(&SCR1,&sem_value);

		if (count_overflowing >= 4 && sem_value == 0)
						break;

		pthread_mutex_lock (&MCR1);
		if ( sem_trywait (&SCR1) == 0 ) {
			sem_getvalue(&SCR1,&sem_value);
			curr_elem = vector[sem_value];
			fprintf(log_file, "Consumer thread %d: semaphore=%d; element %d TAKEN; Overflow count: %d\n",
                    num,sem_value, count - 1, count_overflowing);
			printf("Consumer thread %d: semaphore=%d; element %d TAKEN; Overflow count: %d\n",
					                        num,sem_value, count - 1, count_overflowing);
		}
		else {
			commented this row because log file can be very big
			//printf("Consumer thread%d does some useful work\n",num);
		}
		pthread_mutex_unlock (&MCR1);
	}
	fprintf(log_file, "Consumer thread %d  stopped !!!\n",num);
	printf("Consumer thread %d  stopped !!!\n",num);
    return NULL;
}

/*------------------------------------------------------------------*/

int main()
{
	sem_init (&SCR1, 0, 0);
	sem_init (&Sem1, 0, 0);
	sem_init (&Sem2, 0, 0);

	log_file = fopen("log_file.txt", "w");

	int sem_value;
	sem_getvalue(&SCR1,&sem_value);
	fprintf(log_file, "semaphore=%d\n",sem_value);
	printf("semaphore=%d\n",sem_value);

	int length_at_start=5;
	int i;

  	for(i = 0; i < length_at_start; i++) {
  		sem_getvalue(&SCR1,&sem_value);
  		vector[sem_value] = count;
  		count++;
		sem_post(&SCR1);
  	}

	fprintf(log_file, "Queue with elements from 0-th to %d-th has been created !!!\n",length_at_start-1);
	printf("Queue with elements from 0-th to %d-th has been created !!!\n",length_at_start-1);
	sem_getvalue(&SCR1,&sem_value);
	fprintf(log_file, "semaphore=%d\n",sem_value);

	int thread1_number=1;
	int thread2_number=2;
	int thread3_number=3;
	int thread4_number=4;
	int thread5_number=5;

	pthread_create (&thread1,NULL,&thread_consumer,(void*)&thread1_number);
	pthread_create (&thread2,NULL,&thread_producer,(void*)&thread2_number);
	pthread_create (&thread3,NULL,&thread_producer,(void*)&thread3_number);
	pthread_create (&thread4,NULL,&thread_consumer,(void*)&thread4_number);
	pthread_create (&thread5,NULL,&thread_producer,(void*)&thread5_number);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	pthread_join(thread4,NULL);
	pthread_join(thread5,NULL);

	fprintf(log_file, "All threads stopped !!!\n");
	printf("All threads stopped !!!\n");
	fclose(log_file);
	printf("Done!");

	return 0;
}
