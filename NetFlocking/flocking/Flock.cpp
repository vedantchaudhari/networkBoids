#include "Flock.h"

Flock::Flock(int numOfBoids) {
	this->count = numOfBoids;

	for (int iter = 0; iter < count; iter++) {
		Boid tempBoid = Boid();	// Incase you need to set properties later on
		boids.push_back(tempBoid);
	}
}

float Flock::getDistance(Boid boidA, Boid boidB) {
	float result;
}