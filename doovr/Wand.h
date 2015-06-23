#pragma once
#include "Utilities.h"

class Wand
{
public:
	Wand();
	~Wand();

	virtual float* getWandPosition() { return nullptr; }
	virtual float* getWandOrientation() { return nullptr; }
	virtual float* getTransformMatrix() { return nullptr; }

	virtual void setWandPosition(double* t) = 0;
	virtual void setWandOrientation(double* o) = 0;
	virtual void setTransformMatrix(float* T) = 0;

protected:

	float wandPosition[3];
	float wandOrientation[16];
	float transformMatrix[16];

};

