//Sophia Carlone

//includes
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> //sleep

//defines
#define PHILOSOPHERS 5
#define CHOPSTICKS 5

#define FULL 4      //state of thinking for philosopher (not eating)
#define HUNGRY 3    //state of starting to eat for the philosopher
#define STARVING 2  //state when the philosopher needs to eat
#define DEAD 1      //game over

#define CYCLE 10    //amount of time in each cycle

//Created types
typedef struct philosopher_info
{
    int state;
    int id;
} philosopher_info;

//global variables
pthread_mutex_t chopsticks_in_use[CHOPSTICKS]; //array to symbolize which and how many forks are in use
philosopher_info info[PHILOSOPHERS]; //information for each philosopher
pthread_cond_t chopstick_cond[CHOPSTICKS];
// time_t alarm;

//functions
void *PhilosopherActions(void *args);
void print_info(int id, int state);


int main(){
    int status; // pthread creation check variable
    srand(time(0)); //Seed for random status fill
    // time(alarm);

    pthread_t philosophers[PHILOSOPHERS]; //each philosopher has its own thread

    for(int i = 0; i < CHOPSTICKS; i++){
        pthread_mutex_init(&chopsticks_in_use[i], 0); //initialize the mutex with default attribute
        pthread_cond_init(&chopstick_cond[i], 0);
    }

    for(int i = 0; i < PHILOSOPHERS; i++){
        info[i].state = HUNGRY + (rand() % (FULL+1-HUNGRY)); //random state between hungry and full
        info[i].id = i; 
        status = pthread_create(&philosophers[i], NULL, PhilosopherActions, (void *)&info[i]);
        if(status){
            fprintf(stderr, "issue with thread\n");
            exit(1); //checking all threads are fine
        }
    }
    for (int i = 0; i < PHILOSOPHERS; i++){
        pthread_join( philosophers[i], NULL);
    }
    
}

//TODO: pthread conditions
//TODO: Cycle
//QUESTION: why is it not running forever?


//thread function that works to symbolize all states and actions of the philosophers
void *PhilosopherActions(void *args){
    philosopher_info *data = (philosopher_info *)args;

    //representing chopsticks to each side 
    int left_chopstick = data->id;
    int right_chopstick = (data->id + 1) % CHOPSTICKS;

    //representing philosophers to either side
    int left_partner = (data->id - 1) % PHILOSOPHERS;
    int right_partner = (data->id + 1) % PHILOSOPHERS;  

    //how many chopsticks owned (used for HUNGRY case)
    int owns_left_chopsticks = 0;
    int owns_right_chopsticks = 0;

    while(1){
        switch (data->state){
        case FULL:
            pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
            pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
            // pthread_cond_signal(&chopstick_cond[left_chopstick]);
            // pthread_cond_signal(&chopstick_cond[right_chopstick]);
            data->state -= 1; //will be getting hungry
            print_info(data->id, FULL);

            // fprintf(stderr, "hit3\n"); //confirmed good
            sleep(10); //wait for cycle to be over
            // break;
        
        case HUNGRY:
            //check left
            // fprintf(stderr, "hit4\n");

            if( (info[left_partner].state == STARVING) ){
                pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
                // pthread_cond_signal(&chopstick_cond[left_chopstick]);
                owns_left_chopsticks = 0;
            }
            else{
                // fprintf(stderr, "hit5\n");

                pthread_mutex_lock(&chopsticks_in_use[left_chopstick]); //picking up chopstick
                // fprintf(stderr, "hit6\n");

                // pthread_cond_wait(&chopstick_cond[left_chopstick], &chopsticks_in_use[left_chopstick]); 
                // fprintf(stderr, "hit7\n");

                owns_left_chopsticks = 1;

            }
            //check right

            if(info[right_partner].state == STARVING){
                pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
                // pthread_cond_signal(&chopstick_cond[right_chopstick]);
                owns_right_chopsticks = 0;
            }
            else{
                pthread_mutex_lock(&chopsticks_in_use[left_chopstick]); //picking up chopstick
                // pthread_cond_wait(&chopstick_cond[right_chopstick], &chopsticks_in_use[right_chopstick]); 
                owns_right_chopsticks = 1;
            }

            if(owns_left_chopsticks && owns_right_chopsticks) //conditions to eat
                data->state += 1; //can eat
            else
                data->state -= 1;

            print_info(data->id, HUNGRY);

            sleep(10);
            // break;

        case STARVING:
            fprintf(stderr, "starving\n");
            pthread_mutex_lock(&chopsticks_in_use[left_chopstick]); //get chopstick
            pthread_mutex_lock(&chopsticks_in_use[right_chopstick]); //get chopstick
            // pthread_cond_wait(&chopstick_cond[left_chopstick], &chopsticks_in_use[left_chopstick]); 
            // pthread_cond_wait(&chopstick_cond[right_chopstick], &chopsticks_in_use[right_chopstick]); 
            data->state += 1;
            sleep(10);
            // break;

        case DEAD:
            fprintf(stderr, "GAME OVER");
            exit(1);
            // break;

        default:
            fprintf(stderr, "fell to default");
            break;
        }
        sleep(10);
    }
    fprintf(stderr, "outside the while loop");
}

//print the random states
void print_info(int id, int state){
    fprintf(stderr, "Philosopher %d is in state %d\n", id, state);
}