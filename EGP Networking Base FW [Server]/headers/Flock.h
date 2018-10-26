#pragma once

#include <vector>

#include "Boid.h"

class Flock {
private:
	int count;

public:
	std::vector<Boid> boids;

	Flock(int numOfBoids);

	// Steering behaviors

	float getDistance(Boid boidA, Boid boidB);

	void update();
	void render();

	/*Flock operator=(const Flock& b)
	{
		count = b.count;
		boids = b.boids;
		return *this;
	}*/
};