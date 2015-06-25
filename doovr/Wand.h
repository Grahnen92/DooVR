#pragma once
#include "Utilities.h"

class Wand
{
public:
	Wand();
	~Wand();

	float* getWandPosition() { return wandPosition; }
	float* getWandOrientation() { return wandOrientation; }
	float* getTransformMatrix() { return wandTransform; }

	virtual void setWandPosition(double* t) = 0;
	virtual void setWandOrientation(double* o) = 0;
	virtual void setWandTransform(float* T) = 0;

protected:

	float wandPosition[3];
	float wandOrientation[16];
	float wandTransform[16];
};

