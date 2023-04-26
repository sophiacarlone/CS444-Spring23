//Sophia Carlone

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
//includes
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> //sleep

//defines
#define PHILOSOPHERS 5
#define FORKS 5

#define FULL 4      //state of thinking for philosopher (not eating)
#define HUNGRY 3    //state of starting to eat for the philosopher
#define STARVING 2  //state when the philosopher needs to eat
#define DEAD 1      //game over

#define CYCLE 10    //amount of time in each cycle

//Created types
typedef struct philosopher_info
{
    int state;
    int num_of_forks;
    int id;
} philosopher_info;

//global variables
int forks_in_use[FORKS]; //array to symbolize which and how many forks are in use

//functions
void *PhilosopherActions(void *args);
void print_info(int id, int state);

int main(){
    int status; // pthread creation check variable
    srand(time(0)); //Seed for random status fill

    pthread_t philosophers[PHILOSOPHERS]; //each philosopher has its own thread
    philosopher_info info[PHILOSOPHERS]; //information for each philosopher

    for(int i = 0; i < PHILOSOPHERS; i++){
        info[i].state = HUNGRY + (rand() % (FULL+1-HUNGRY)); //random state between hungry and full
        info[i].num_of_forks = 0;
        info[i].id = i; 
        status = pthread_create(&philosophers[i], NULL, PhilosopherActions, (void *)&info[i]);
        if(status){
            fprintf(stderr, "issue with thread\n");
            exit(1); //checking all threads are fine
        }
        sleep(2); //used to avoid conflict when using fprintf()
    }

    //return 0;
}

//thread function that works to symbolize all states and actions of the philosophers
void *PhilosopherActions(void *args){
    fprintf(stderr, "hit1\n");
    philosopher_info *data = (philosopher_info *)args;

    print_info(data->id, data->state);
}

//print the random states
void print_info(int id, int state){
    fprintf(stderr, "Philosopher %d is in state %d\n", id, state);
}
