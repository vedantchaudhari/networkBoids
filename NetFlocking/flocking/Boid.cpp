#include "Boid.h"

Boid::Boid() {
	// Set boid x & y pos randomly
	pos[0] = rand() % 100 + WIDTH / 2;
	pos[1] = rand() % 100 + HEIGHT / 2;

	// Set random x & y velocity
}

Boid::Boid(float x, float y) {

}