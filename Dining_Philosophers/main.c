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

#define THINKING 4      //state of thinking for philosopher (not eating)
#define EATING 3    //state of starting to eat for the philosopher
#define HUNGRY 2  //state when the philosopher needs to eat
#define DEAD 1      //game over

#define CYCLE 3    //amount of time in each cycle

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
struct tm *start_time;


//functions
void *PhilosopherActions(void *args);
void print_info(int id, int state, int cycle);


int main(){
    int status; // pthread creation check variable
    int count; //count cycle
    srand(time(0)); //Seed for random status fill
    time_t rawtime;
 
    time(&rawtime);
    start_time = gmtime(&rawtime ); /* Get GMT time */

    pthread_t philosophers[PHILOSOPHERS]; //each philosopher has its own thread

    for(int i = 0; i < CHOPSTICKS; i++){
        pthread_mutex_init(&chopsticks_in_use[i], 0); //initialize the mutex with default attribute
        pthread_cond_init(&chopstick_cond[i], 0);
    }

    for(int i = 0; i < PHILOSOPHERS; i++){
        info[i].state = EATING + (rand() % (THINKING+1-EATING)); //random state between hungry and full
        info[i].id = i; 
        status = pthread_create(&philosophers[i], NULL, PhilosopherActions, (void *)&info[i]);
        if(status){
            fprintf(stderr, "issue with thread\n");
            exit(1); //checking all threads are fine
        }
    }

    while (1){
        fprintf(stderr, "______________________________________\n");
        for(int i = 0; i < PHILOSOPHERS; i++){
            print_info(i, info[i].state, count);
        }
        count += 1;
        sleep(CYCLE);
    }
    
    //You need this for threads to run forever apparently
    for (int i = 0; i < PHILOSOPHERS; i++){
        pthread_join( philosophers[i], NULL);
    }
    
}


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

    int cycle_count = 0;

    while(1){

        switch (data->state){
        case THINKING:
            pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
            pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
            data->state -= 1; //will be getting hungry
            // print_info(data->id, data->state, cycle_count);
            break;
        
        case EATING:
            //check to the left
            if( (info[left_partner].state == HUNGRY) ){
                pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
                pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
                owns_left_chopsticks = 0;
                owns_right_chopsticks = 0;
            }
            else{
                pthread_mutex_lock(&chopsticks_in_use[left_chopstick]); //picking up chopstick
                owns_left_chopsticks = 1;
            }

            //check right
            if(info[right_partner].state == HUNGRY){
                pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
                pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
                owns_left_chopsticks = 0;
                owns_right_chopsticks = 0;
            }
            else{
                pthread_mutex_lock(&chopsticks_in_use[right_chopstick]); //picking up chopstick
                owns_right_chopsticks = 1;
            }

            //Owns all the chopsticks to eat?
            if(owns_left_chopsticks && owns_right_chopsticks) //conditions to eat
                data->state += 1; //can eat
            else
                data->state -= 1;
            // print_info(data->id, data->state, cycle_count);
            break;

        case HUNGRY:
            if (pthread_mutex_trylock(&chopsticks_in_use[left_chopstick]) != 0 ){
                pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
                data->state -=1;
                break;
            } //get chopstick
            if (pthread_mutex_trylock(&chopsticks_in_use[right_chopstick]) != 0 ){
                pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
                data->state -=1;
                break;
            }
            data->state += 1;
            // print_info(data->id, data->state, cycle_count);
            break;

        case DEAD:
            // print_info(data->id, data->state, cycle_count);
            fprintf(stderr, "GAME OVER");
            exit(1);
            break;

        default:
            fprintf(stderr, "fell to default");
            break;
        }

        cycle_count += 1; //done with cycle
        sleep(CYCLE); //waiting for everyone
    }
    fprintf(stderr, "outside the while loop");
}

//print the philosophers information
void print_info(int id, int state, int cycle){
    fprintf(stderr, "Philosopher %d is in state %d on cycle %d\n", id, state, cycle);
}