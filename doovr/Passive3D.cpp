#include "Passive3D.h"

using namespace wand3d;

Passive3D::Passive3D()
{
	try {
		wand = new Wand3d("COM4"); // usb port
	} catch (Wand3dSerialException error) {
		std::cout << error.what() << std::endl;
	}
	wand->addObserver(this);
}


Passive3D::~Passive3D() {
	wand->removeObserver(this);
	delete wand;
}

void Passive3D::wand3dCallback(WandData data) {
	//std::cout << data << std::endl;
	setWandPosition(data.position);
	utils::getGLRotMatrix(data, wandOrientation);
}

void Passive3D::start() {
	wand->start();
}


float* Passive3D::getWandPosition() {
	return wandPosition;
}

float* Passive3D::getWandOrientation() {
	return wandOrientation;
}

void Passive3D::setWandPosition(double* t) {
	wandPosition[0] = t[0];
	wandPosition[1] = t[1];
	wandPosition[2] = t[2];
}

void Passive3D::setWandOrientation(double* o) {
	std::copy(o, o + 16, wandOrientation);
}
