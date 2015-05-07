#include "Passive3D.h"

using namespace wand3d;

Passive3D::Passive3D()
{
	try {
		wand = new Wand3d("COM4"); // usb port
	} catch (Wand3dSerialException error) {
		std::cout << error.what() << std::endl;
	}
	Wand3dObserver* observer = this;
	wand->addObserver(observer);
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

	// Change the coordinatesystem to match Oculus x->x, y->z, z->-y
	wandPosition[0] = (float) t[0]*5 +0.0f;
	wandPosition[1] = (float) t[2]*5 -0.75f;
	wandPosition[2] = (float) -t[1]*5 -0.5f;
}

void Passive3D::setWandOrientation(double* o) {
	std::copy(o, o + 16, wandOrientation);
}
