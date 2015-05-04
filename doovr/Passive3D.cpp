#include "Passive3D.h"


Passive3D::Passive3D()
{
	try {
		wand = new wand3d::Wand3d("COM4"); // usb port
	}
	catch (wand3d::Wand3dSerialException error) {
		std::cout << error.what() << std::endl;
	}
	wand->addObserver(this);
}


Passive3D::~Passive3D() {
	wand->removeObserver(this);
	delete wand;
	delete this;
}

void Passive3D::wand3dCallback(wand3d::WandData data) {
	//std::cout << data << std::endl;
	setWandPosition(data.position);
	wand3d::utils::getGLRotMatrix(data, wandOrientation);
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
	for (int i = 0; i < 16; i++) {
		wandOrientation[i] = o[i];
	}
}
