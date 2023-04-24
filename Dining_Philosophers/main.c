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