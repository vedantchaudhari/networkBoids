#include "Boid.h"

Boid::Boid() {
	// Set boid x & y pos randomly
	pos[0] = rand() % 100 + WIDTH / 2;
	pos[1] = rand() % 100 + HEIGHT / 2;

	// Set random x & y velocity
	velocity[0] = (100 - (rand() % 200)) / 100.0;
	velocity[1] = (100 - (rand() % 200)) / 100.0;
}

Boid::Boid(float x, float y) {
	pos[0] = x;
	pos[1] = y;

	// Set random x & y velocity
	velocity[0] = (100 - (rand() % 200)) / 100.0;
	velocity[1] = (100 - (rand() % 200)) / 100.0;
}

void Boid::update() {

}

void Boid::render() {

}

void Boid::addToTargetPosBuffer(float x, float y) {
	targetPosBuffer[0] += x;
	targetPosBuffer[1] += y;
}

void Boid::clearBuffers() {
	numOfNeighbors = 0;

	targetPosBuffer[0] = 0;
	targetPosBuffer[1] = 0;
}

