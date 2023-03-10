#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>



#define NUM_R 3
#define NUM_W 3
#define MAX_SIZE 10

sem_t sem_full;
sem_t sem_empty;
pthread_mutex_t lock;
pthread_cond_t full, empty;
int count;
int test_count;
void *Writter(void * thread_nr) {
	srand( (long)time(NULL) );
	int i=1;
	int *message;
	message = (int *) thread_nr;
	while(i<=MAX_SIZE) {
		pthread_mutex_lock(&lock);
		while(count == (MAX_SIZE*NUM_W)){
			pthread_mutex_unlock(&lock);
			printf("Writer %d failed \n",*message);
			sem_wait(&sem_empty);
			pthread_mutex_lock(&lock);
		//	printf("1::%d\n",*message);
		}
		//while(count < MAX_SIZE){
				count++;

				if(count!=(NUM_W*MAX_SIZE)+1){
					printf("Writer %d writes line %d , try %d\n",*message, count-1,i);
					//usleep(1000000+(rand() % 1500000));
				}
				//printf("Writer %d writes line %d , try %d\n",*message, count-1,i);
				/*if(count==(NUM_W*MAX_SIZE)){
					//printf("1w\n");
					 //pthread_exit(NULL);
					 //printf("2w\n");
					return 0;
					
				}*/
	//	}
		//pthread_cond_signal(&full);
		sem_post(&sem_full);
		pthread_mutex_unlock(&lock);
		usleep(1000000+(rand() % 1500000));
		i++;
	}
	 pthread_exit(NULL);

}

void *Reader(void * thread_nr){
	srand( (long)time(NULL) );
	int i=1;
	int test=1;
	int *message;

	message = (int *) thread_nr;
	while(test==1) {
		//printf("1\n");
		pthread_mutex_lock(&lock);
		//printf("2\n");
				if(count==(NUM_W*MAX_SIZE)){
					//printf("1r\n");
					sem_post(&sem_empty);
					pthread_mutex_unlock(&lock);
					pthread_exit(NULL);
					//printf("2r\n");
					return 0;
				}
		while(count == 0){
			pthread_mutex_unlock(&lock);
			if(test_count==(MAX_SIZE * NUM_W)){
			if(NUM_R==1){
				//printf("2\n");
				 pthread_exit(NULL);
			}
			else{
			//	printf("1\n");
				sem_post(&sem_full);
				 pthread_exit(NULL);
			}
			}
			printf("Reader %d failed \n",*message);
			sem_wait(&sem_full);
			pthread_mutex_lock(&lock);
		//	printf("2::%d\n",*message);
		}
		if(count > 0){
				test_count++;
			 // printf("test_count=%d\n",test_count );
			 	int random=rand()%count;

				 if(count!=(NUM_W*MAX_SIZE)+1){
					 printf("Reader %d reads from line %d , try %d\n",*message, random,i);
				 }
				
				//printf("Reader %d reads from line %d , try %d\n",*message, random,i);
				//usleep(2000000+(rand() % 1500000));


		}
		//pthread_cond_signal(&empty);
		sem_post(&sem_empty);
		pthread_mutex_unlock(&lock);
		usleep(2000000+(rand() % 1500000));
		i++;
	}
	 pthread_exit(NULL);
}

int main() {
	pthread_t p[NUM_W];
  pthread_t c[NUM_R];
  int i;
	int result;
	count = 0;
	test_count=0;
	int THREAD_NUM=NUM_W+NUM_R;
	int temp_arg[THREAD_NUM] ;
	sem_init(&sem_full, 0, 1);
	sem_init(&sem_empty, 0, 1);
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&full, NULL);
	for(i=0;i<NUM_R;i++){
		temp_arg[i]=i ;
		 result=pthread_create(&c[i], NULL,Reader,&temp_arg[i]);
	}
  for(i=0;i<NUM_W;i++){
		temp_arg[i]=i ;
	   result=pthread_create(&p[i], NULL,Writter,&temp_arg[i]);
  }

	for(i=0;i<NUM_W;i++){
		pthread_join( p[i], NULL);
	}

	for(i=0;i<NUM_R;i++){
		pthread_join(c[i], NULL);
	}

	return 0;
}
