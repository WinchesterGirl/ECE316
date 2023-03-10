#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>


#define M 55
#define K 56
#define N 57
int A[M][K];
int B[K][N];
int C[M][N];



struct timespec start, finish;
double elapsed;

void * thread_talk(void * thread_nr)

{




     int i,j,l;
     int *message;
     message = (int *) thread_nr;
     //printf("%d \n", *message);
    // for (i=0;i<M;i++){
         //for (j=0;j<N;j++){
    l=(*message);
    i=0;
    j=(*message);
    while(l>=N){
        l=l-N;
        i=i+1;
        j=j-N;

    }
     for (l=0;l<K;l++){
           C[i][j]=C[i][j]+((A[i][l])*(B[l][j]));
     }
         //}
    // }
     pthread_exit(NULL);         //exit from current thread
}

int main()
{
    for(int i=0;i<M;i++){
        for(int j=0;j<K;j++){
            A[i][j]=rand()%9;
        }
    }

    
    for(int i=0;i<K;i++){
        for(int j=0;j<N;j++){
            B[i][j]=rand()%9;
        }
    }

    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            C[i][j]=0;
        }
    }
    //clock_t start;
    float duration;
    int THREAD_NUM = M * N;
    int result[THREAD_NUM];
    //start = clock();
    clock_gettime(CLOCK_MONOTONIC, &start);
    pthread_t thread[THREAD_NUM];
    int temp_arg[THREAD_NUM] ;
  //  int A[M][K]={{1,4},{2,5},{3,6}};
    //int B[K][N]={{8,7,6,5},{4,3,2,1}};
    //int C[M][N]={{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int i,j,l;

    for(i=0;i<THREAD_NUM;i++){
        temp_arg[i]=i ;

        result[i] = pthread_create(&thread[i], NULL, thread_talk, &temp_arg[i]);

        if (result[i]!=0)
        {
            printf("Error creating thread %d. Return code: %ls\n",i,result);
        }

    }
    for(i=0;i<THREAD_NUM;i++){
      pthread_join( thread[i], NULL);
    }

    printf("A:\n");
    for (i=0;i<M;i++){
        for (j=0;j<K;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("B:\n");
    for (i=0;i<K;i++){
        for (j=0;j<N;j++){
            printf("%d ",B[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("C:\n");
    for (i=0;i<M;i++){
        for (j=0;j<N;j++){
            printf("%d ",C[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Duration = %f s\n",elapsed);
    return 0;
}

 

