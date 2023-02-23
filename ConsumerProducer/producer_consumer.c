// Operating Systems - CS444
// Spring 2023
// Sophia Carlone
// Producer-Consumer Problem
// Solving the producer-consumer problem using pthreads and mutexes
// 2/23/23
// https://youtu.be/cZL_VWgDNX0


/* includes */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

/* Defines */
#define MAX 50 //number of items placed in the buffer to be consumed

/* Global variables */
int buffer = 0; //Critical Region
pthread_mutex_t mutex; //mutex shared by all threads
pthread_cond_t p_cond, c_cond; //making signals telling who can wake up 

/* Functions */
void *Producer(void *arg);
void *Consumer(void *arg);

/* Main */
int main(){
pthread_t producer, consumer; //create threads
pthread_mutex_init(&mutex, 0); //initialize the mutex with default attribute
pthread_cond_init(&p_cond, 0); //initialize the signal for the producer to wake with default attribute
pthread_cond_init(&c_cond, 0); //initialize the signal for the consumer to wake with default attribute

//start threads off
pthread_create(&consumer, NULL, Consumer, NULL);
pthread_create(&producer, NULL, Producer, NULL);

//join threads
pthread_join(producer, NULL);
pthread_join(consumer, NULL);

//clean up
pthread_cond_destroy(&p_cond);
pthread_cond_destroy(&c_cond);
pthread_mutex_destroy(&mutex);
}

//function for the producer to add to the buffer when applicable 
void *Producer(void *arg){
    for(int i = 1; i < MAX; i++){
        pthread_mutex_lock(&mutex); //get solo access to buffer
        
        while(buffer != 0)
            pthread_cond_wait(&p_cond, &mutex); //telling the produce to sleep to remove data
        
        buffer = i; //awake and adding data
        fprintf(stderr, "from Producer, buffer is %d\n", buffer);
        
        pthread_mutex_unlock(&mutex); //letting go of the buffer
        pthread_cond_signal(&c_cond); //telling the consumer it has data to interact with

    }
    pthread_exit(0);
}

//function for the consumer to consume from the buffer when applicable
void *Consumer(void *arg){
    for(int i = 1; i < MAX; i++){
        pthread_mutex_lock(&mutex); //get solo access to buffer
        
        while(buffer == 0)
            pthread_cond_wait(&c_cond, &mutex); //telling the consumer to sleep while data is added
        
        buffer = 0; //acting like all data was consumed
        fprintf(stderr, "from Consumer, buffer is %d\n", buffer);
        
        pthread_mutex_unlock(&mutex); //letting go of the buffer
        pthread_cond_signal(&p_cond); //telling the producer to refill

    }
    pthread_exit(0);
}

//end program