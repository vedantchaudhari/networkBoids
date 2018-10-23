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

	void update();
	void render();

	float getDistance(Boid boidA, Boid boidB);
};