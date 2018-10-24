#include "Flock.h"

Flock::Flock(int numOfBoids) {
	this->count = numOfBoids;

	for (int iter = 0; iter < count; iter++) {
		Boid tempBoid = Boid();	// Incase you need to set properties later on
		boids.push_back(tempBoid);
	}
}

float Flock::getDistance(Boid boidA, Boid boidB) {
	return sqrt((boidB.pos[0] - boidA.pos[0]) * (boidB.pos[0] - boidA.pos[0])
		+ (boidB.pos[1] - boidA.pos[1]) * (boidB.pos[1] - boidA.pos[1]));
}

void Flock::update() {
	for (int iter = 0; iter < count; iter++)
		boids[iter].clearBuffers();

	// Cohesion
	for (int iter = 0; iter < count; iter++) {
		for (int iter2 = iter + 1; iter2 < count; iter2++) {
			if (getDistance(boids[iter], boids[iter2]) < BOID_RADIUS) {
				boids[iter].numOfNeighbors++;
				boids[iter2].numOfNeighbors++;
				boids[iter].addToTargetPosBuffer(boids[iter2].pos[0], boids[iter2].pos[1]);
				boids[iter2].addToTargetPosBuffer(boids[iter].pos[0], boids[iter].pos[1]);
			}
		}
	}
	for (int iter = 0; iter < count; iter++) {
		if (boids[iter].numOfNeighbors > 0) {
			boids[iter].cohesionTargetPos[0] = boids[iter].targetPosBuffer[0] / boids[iter].numOfNeighbors;
			boids[iter].cohesionTargetPos[1] = boids[iter].targetPosBuffer[1] / boids[iter].numOfNeighbors;
		}
		else {
			boids[iter].cohesionTargetPos[0] = boids[iter].pos[0];
			boids[iter].cohesionTargetPos[1] = boids[iter].pos[1];
		}
	}

	// Separation
	for (int iter = 0; iter < count; iter++)
		boids[iter].clearBuffers();

	for (int iter = 0; iter < count; iter++) {
		for (int iter2 = iter + 1; iter2 < count; iter2++) {
			if (getDistance(boids[iter], boids[iter2]) < SEPERATION_RADIUS) {
				boids[iter].numOfNeighbors++;
				boids[iter2].numOfNeighbors++;
				boids[iter].addToTargetPosBuffer(boids[iter2].pos[0], boids[iter2].pos[1]);
				boids[iter2].addToTargetPosBuffer(boids[iter].pos[0], boids[iter].pos[1]);
			}
		}
	}
	for (int iter = 0; iter < count; iter++) {
		if (boids[iter].numOfNeighbors > 0) {
			if (boids[iter].targetPosBuffer[0] / boids[iter].numOfNeighbors
				!= boids[iter].pos[0]) {
				boids[iter].separationTargetPos[0] = boids[iter].pos[0] - 1000
					/ (boids[iter].targetPosBuffer[0] / boids[iter].numOfNeighbors - boids[iter].pos[0]);
			}
			if (boids[iter].targetPosBuffer[1] / boids[iter].numOfNeighbors
				!= boids[iter].pos[1]) {
				boids[iter].separationTargetPos[1] = boids[iter].pos[0] - 1000
					/ (boids[iter].targetPosBuffer[1] / boids[iter].numOfNeighbors - boids[iter].pos[1]);
			}
		}
		else {
			boids[iter].separationTargetPos[0] = boids[iter].pos[0];
			boids[iter].separationTargetPos[1] = boids[iter].pos[1];
		}
	}

	// Alignment
	for (int iter = 0; iter < count; iter++) {
		boids[iter].clearBuffers();
		boids[iter].sumofNeighborsTheta = 0;
	}
	for (int iter = 0; iter < count; iter++) {
		for (int iter2 = iter + 1; iter2 < count; iter2++) {
			if (getDistance(boids[iter], boids[iter2]) < BOID_RADIUS) {
				boids[iter].numOfNeighbors++;
				boids[iter2].numOfNeighbors++;
				boids[iter].sumofNeighborsTheta += boids[iter].theta;
				boids[iter2].sumofNeighborsTheta += boids[iter2].theta;
			}
		}
	}
	for (int iter = 0; iter < count; iter++) {
		if (boids[iter].numOfNeighbors > 0) {
			boids[iter].alignmentTargetPos[0] = boids[iter].pos[0] + cos(boids[iter].sumofNeighborsTheta
				/ boids[iter].numOfNeighbors);
			boids[iter].alignmentTargetPos[1] = boids[iter].pos[1] + cos(boids[iter].sumofNeighborsTheta
				/ boids[iter].numOfNeighbors);
		}
		else {
			boids[iter].alignmentTargetPos[0] = boids[iter].pos[0];
			boids[iter].alignmentTargetPos[1] = boids[iter].pos[1];
		}
	}

	// Update Boids
	for (int iter = 0; iter < count; iter++)
		boids[iter].update();
}

void Flock::render() {
	for (int iter = 0; iter < count; iter++)
		boids[iter].render();
}