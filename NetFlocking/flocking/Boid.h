#pragma once

class Boid {
private:

public:
	Boid();
	Boid(float x, float y);

	// Vector 2 Data
	float pos[2] = { 0, 0 };
	float alignmentTargetPos[2] = { 0, 0 };
	float cohesionTargetPos[2] = { 0, 0 };
	float separationTargetPos[2] = { 0, 0 };
};