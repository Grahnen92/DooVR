#pragma once
#include "Utilities.h"
#include <iostream>

class Wand
{
public:
	Wand();
	~Wand();


	//! Get position vector of the device position
	float* getWandPosition() { return wandPosition; }
	//! Get the rotation matrix for the device
	float* getWandOrientation() { return wandOrientation; }
	//! Get co-register transform matrix
	float* getTransformMatrix() { return transformMatrix; };

	virtual void setWandPosition(double* t) = 0;
	//! Set the rotation matrix for the device to a variable
	virtual void setWandOrientation(double* o) = 0;
	//!  Set the transform matrix
	void setTransformMatrix(float* T) { std::copy(T, T + 16, transformMatrix); }

	//! Print transform
	void print_transformMatrix();

protected:
	//! Saved variable from setTrackerPosition
	float wandPosition[3];
	//! Saved variable from setTrackerRotation
	float wandOrientation[16];
	//! Saved transform from co-register function
	float transformMatrix[16];
};

