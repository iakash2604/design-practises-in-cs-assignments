#include "Boid.h"
#include "Flock.h"

//!< to get the number of boids in the flock
int Flock::getSize()
{
    return flock.size();
}


//!< to get a boid at index i
Boid Flock::getBoid(int i)
{
    return flock[i];
}

//!< to add a boid b
void Flock::addBoid(Boid b)
{
    flock.push_back(b);
}

/*! Runs the run function for every boid in the flock checking against the flock
 itself. Which in turn applies all the rules to the flock. */
void Flock::flocking() 
{
    for (int i = 0; i < flock.size(); i++)
        flock[i].run(flock);
}