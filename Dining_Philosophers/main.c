//Sophia Carlone

/* RULES

You must have 5 philosophers and 5 forks on the table
Each fork is shared between two adjacent philosophers (critical regions)
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