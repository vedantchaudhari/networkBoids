#pragma once

#include <vector>

#include "Boid.h"
#include "RakNet/DS_List.h"

class Flock {
private:
	int count;

public:
	//std::vector<Boid> boids;
	DataStructures::List<Boid> boidsList;

	Flock(int numOfBoids);

	// Steering behaviors

	float getDistance(Boid boidA, Boid boidB);

	void update();
	void render();

	Flock operator=(const Flock& b)
	{
		count = b.count;
		boidsList = b.boidsList;
		return *this;
	}
};