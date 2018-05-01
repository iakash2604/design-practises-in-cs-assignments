#include "Pvector.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

#ifndef BOID_H_
#define BOID_H_

/*!The Boid Class*/

class Boid {
public:
    //!< bool predator: flag that specifies whether a given boid is a predator.
    int predator;
    //!< bool killed: flag that specifies whether a given boid is alive.
    int killed;
    //!< Pvector location: Vector that specifies a boid's location.
    Pvector location;
    //!< Pvector velocity: Vector that specifies a boid's current velocity.
    Pvector velocity;
    //!< Pvector acceleration: Vector that specifies a boid's current acceleration.
    Pvector acceleration;
    //!< float maxSpeed: Limits magnitude of velocity vector.
    float maxSpeed;
    //!< float maxForce: Limits magnitude of acceleration vector. (F = m*a!)
    float maxForce;
    //!< boid constructor
    Boid() {}
    Boid(float x, float y);
    Boid(float x, float y, int predCheck);
    //!<   applyForce(Pvector force): Adds the given vector to acceleration
    void applyForce(Pvector force);
    //!< Three Laws that boids follow
    /*! Pvector Separation(vector<Boid> Boids): If any other boids are within a
      given distance, Separation computes a a vector that distances the
      current boid from the boids that are too close.*/
    Pvector Separation(vector<Boid> Boids);
    /*!Pvector Alignment(vector<Boid> Boids): Computes a vector that causes the
      velocity of the current boid to match that of boids that are nearby.*/
    Pvector Alignment(vector<Boid> Boids);

    /*!Pvector Cohesion(vector<Boid> Boids): Computes a vector that causes the
      current boid to seek the center of mass of nearby boids.*/
    Pvector Cohesion(vector<Boid> Boids);
    //!< Functions involving SFML and visualisation linking
    Pvector seek(Pvector v);
    void run(vector <Boid> v);
    void update();
    void flock(vector <Boid> v);
    void borders();
    float angle(Pvector v);
};

#endif
