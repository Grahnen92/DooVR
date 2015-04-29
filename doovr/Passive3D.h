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

class Passive3D : public wand3d::Wand3dObserver
{
public:
	Passive3D();
	~Passive3D();


	void wand3dCallback(wand3d::WandData data);

private:




};

