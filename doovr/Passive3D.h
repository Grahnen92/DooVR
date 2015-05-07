#pragma once

#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define SLEEP(c) Sleep(c*1000)
#else
#include <unistd.h>
#define SLEEP(c) sleep(c)
#endif

#include "wand3d/wand3d.h"
#include "wand3d/wand3d_exception.h"
#include "wand3d/wand3d_observer.h"
#include "wand3d/wand3d_utils.h"


//#include "Utilities.h"

class Passive3D : public wand3d::Wand3dObserver
{
public:
	Passive3D();
	~Passive3D();


	void wand3dCallback(wand3d::WandData data);

	void start();

	//! Get position vector of the device position
	float* getWandPosition();
	//! Get the rotation matrix for the device
	float* getWandOrientation();

	void setWandPosition(double* t);
	//! Set the rotation matrix for the device to a variable
	void setWandOrientation(double* o);

private:
	//! Saved variable from setTrackerPosition
	float wandPosition[3];
	//! Saved variable from setTrackerRotation
	float wandOrientation[16];

	wand3d::Wand3d* wand;

};

