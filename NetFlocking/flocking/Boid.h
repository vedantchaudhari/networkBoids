#pragma once

#include <iostream>
#include <math.h>

#include "Define.h"

class Boid {
private:

public:
	Boid();
	Boid(float x, float y);

	int numOfNeighbors = 0;

	// Vector 2 Data
	float pos[2] = { 0, 0 };
	float alignmentTargetPos[2] = { 0, 0 };
	float cohesionTargetPos[2] = { 0, 0 };
	float separationTargetPos[2] = { 0, 0 };

	float targetPosBuffer[2] = { 0, 0 };
	float velocity[2] = { 0, 0 };
	float theta = 0;

	float sumofNeighborsTheta = 0;

	void update();
	void render();

	void addToTargetPosBuffer(float x, float y);
	void clearBuffer();
	void steerTo(float x, float y);
};