#pragma once

#include <vector>

#include "RakNet/DS_List.h"
#include "Boid.h"

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

	/*Flock operator=(const Flock b)
	{
		count = b.count;
		boids = b.boids;
		return this;
	}*/
};