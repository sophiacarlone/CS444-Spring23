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

//functions
void *PhilosopherActions(void *args);
void print_info(int id, int state);


int main(){
    int status; // pthread creation check variable
    srand(time(0)); //Seed for random status fill

    pthread_t philosophers[PHILOSOPHERS]; //each philosopher has its own thread

    for(int i = 0; i < CHOPSTICKS; i++){
        pthread_mutex_init(&chopsticks_in_use[i], 0); //initialize the mutex with default attribute
    }

    for(int i = 0; i < PHILOSOPHERS; i++){
        info[i].state = HUNGRY + (rand() % (FULL+1-HUNGRY)); //random state between hungry and full
        info[i].id = i; 
        status = pthread_create(&philosophers[i], NULL, PhilosopherActions, (void *)&info[i]);
        if(status){
            fprintf(stderr, "issue with thread\n");
            exit(1); //checking all threads are fine
        }
        sleep(2); //used to avoid conflict when using fprintf()
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

    fprintf(stderr, "hit1\n");

    while(1){
    fprintf(stderr, "hit2\n");

        switch (data->state){
        case FULL:
            fprintf(stderr, "hit3\n");
            pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
            pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
            data->state -= 1; //will be getting hungry
            print_info(data->id, FULL);
            sleep(10); //wait for cycle to be over
            break;
        
        case HUNGRY:
            fprintf(stderr, "hit4\n");
            //check left
            if( (info[left_partner].state == STARVING) ){
                pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the chopstick
                owns_left_chopsticks = 0;
            }
            else{
                pthread_mutex_lock(&chopsticks_in_use[left_chopstick]); //picking up chopstick
                owns_left_chopsticks = 1;
            }
            //check right
            if(info[right_partner].state == STARVING){
                pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the chopstick
                owns_right_chopsticks = 0;
            }
            else{
                pthread_mutex_lock(&chopsticks_in_use[left_chopstick]); //picking up chopstick
                owns_right_chopsticks = 1;
            }

            if(owns_left_chopsticks && owns_right_chopsticks) //conditions to eat
                data->state += 1; //can eat
            else
                data->state -= 1;

            print_info(data->id, HUNGRY);

            sleep(10);
            break;

        case STARVING:
            pthread_mutex_lock(&chopsticks_in_use[left_chopstick]); //get chopstick
            pthread_mutex_lock(&chopsticks_in_use[right_chopstick]); //get chopstick
            data->state += 1;
            sleep(10);
            break;

        case DEAD:
            fprintf(stderr, "GAME OVER");
            exit(1);
            break;

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







/*~~~~~~~~~~~~~~~~~~~~~~~~GARBAGE~~~~~~~~~~~~~~~~~~~~~~~~*/

        
        // if (data->state == FULL){
        //     pthread_mutex_unlock(&chopsticks_in_use[left_chopstick]); //letting go of the buffer
        //     pthread_mutex_unlock(&chopsticks_in_use[right_chopstick]); //letting go of the buffer
        //     sleep(10);
        // }
        //else state - 1


/* RULES

You must have 5 philosophers and 5 forks on the table
Each fork is shared between two adjacent philosophers (critical regions)
Only one philosopher can use a fork, and multiple can be eating at the same time
Philosophers have four states
    Thinking: hunger status is full and the philosopher is idle thinking, not eating
    Eating: hunger status is not full and triggers philosopher to eat until thinking can resume
    Hungry: Philsopher can no longer think due to junger and needs to commence eating before starving
    Dead: philosopher is in the great beyond

Each philosopher should have a hunger meter tracking how close they are to death
    cli status updates
    timer based. Each cycle in which a philosopher doesnt eat causes more hunger. decide on how many cycles before hunger

No deadlocks. Can ideally go on forever

*/

/* ideas:

You can assume that every philosopher comes to the table full, but then things will turn sour
Instead, randomize each philosopher at the beginning to have a state of 3 or 4 (Eating or Thinking)
Odd fork out should be randomly place to someone who is not eating
Move forks separately

When someone is full, they should not need the fork
When someone is at 2, they should get the highest priority

*/