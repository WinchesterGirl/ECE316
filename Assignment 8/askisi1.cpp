#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include <unistd.h>
#include <queue>
#include <semaphore.h>

using namespace std;

#define NUM_THREADS 3

condition_variable c0,c1,c2;
mutex mtx,mtx0,mtx1,mtx2;
unique_lock <mutex> lck0(mtx0),lck1(mtx1),lck2(mtx2);

int counter=0;

void *print0(void *arg){
	int id;
	
	id = *((int *)arg);
	while (counter<20){
		if (counter!=0)
			c0.wait(lck0);
		if (counter>20){
			c1.notify_one();
			pthread_exit(NULL);
		}
	cout<<"Thread " << id << " Counter " << counter << endl;
	c1.notify_one();
	mtx.lock();
	counter++;
	mtx.unlock();
	}
pthread_exit(NULL);
}

void *print1(void *arg){
	int id;
	
	id = *((int *)arg);
	while (counter<20){
		c1.wait(lck1);
		if (counter>20){
			c2.notify_one();
			pthread_exit(NULL);
		}
	cout<<"Thread " << id << " Counter " << counter << endl;
	c2.notify_one();
	mtx.lock();
	counter++;
	mtx.unlock();
	}
pthread_exit(NULL);
}

void *print2(void *arg){
	int id;
	
	id = *((int *)arg);
	while (counter<20){
		c2.wait(lck2);
		if (counter>20){
			c0.notify_one();
			pthread_exit(NULL);
		}
	cout<<"Thread " << id << " Counter " << counter << endl;
	c0.notify_one();
	mtx.lock();
	counter++;
	mtx.unlock();
	}
pthread_exit(NULL);
}

int main(){
	int i, tmp;
	int arg[NUM_THREADS] = {0,1,2};
	
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
	
	for (i=0; i<NUM_THREADS;i++){
		if (i==0)
			tmp = pthread_create(&thread[i], &attr, print0, (void *)&arg[i]);
		if (i==1)
			tmp = pthread_create(&thread[i], &attr, print1, (void *)&arg[i]);
		if (i==2)
			tmp = pthread_create(&thread[i], &attr, print2, (void *)&arg[i]);
		if ( tmp != 0 ){
			cout<<"Creating thead"<<i<<"failed"<<endl;
			return 1;
		}
	}
	
	for (i=0;i<NUM_THREADS;i++){
		tmp = pthread_join(thread[i],NULL);
		if (tmp !=0){
			cout <<"Joining thead"<<i<<"failed"<<endl;
			return 1;
		}
	}
	
	return 0;
}
