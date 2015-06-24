#include "Passive3D.h"
#include "linAlg.h"

using namespace wand3d;

Passive3D::Passive3D()
{
	try {
		wand = new Wand3d("COM4"); // usb port
	}
	catch (Wand3dSerialException error) {
		std::cout << error.what() << std::endl;
	}
	Wand3dObserver* observer = this;
	wand->addObserver(observer);

	wand->start();
}

Passive3D::~Passive3D() {
	wand->removeObserver(this);
	delete wand;
}

void Passive3D::wand3dCallback(WandData data) {
	//std::cout << data << std::endl;
	float Orientation[16];
	//float finalM[16];
	setWandPosition(data.position);
	utils::getGLRotMatrix(data, wandOrientation);
	float rotZX[16] = { -1.f, 0.f, 0.f, 0.f,
						 0.f, 0.f, 1.f, 0.f,
						 0.f, 1.f, 0.f, 0.f,
						 0.f, 0.f, 0.f, 1.0f };
	//linAlg::matrixMult(rotZX, Orientation, wandOrientation);
	/*
	wandOrientation[0] = finalM[0];
	wandOrientation[1] = finalM[1];
	wandOrientation[2] = finalM[2];
	wandOrientation[3] = 0.0f;
	wandOrientation[4] = finalM[3];
	wandOrientation[5] = finalM[4];
	wandOrientation[6] = finalM[5];
	wandOrientation[7] = 0.0f;
	wandOrientation[8] = finalM[6];
	wandOrientation[9] = finalM[7];
	wandOrientation[10] = finalM[8];
	wandOrientation[11] = 0.0f;
	wandOrientation[12] = 0.0f;
	wandOrientation[13] = 0.0f;
	wandOrientation[14] = 0.0f;
	wandOrientation[15] = 1.0f;
	*/
}

void Passive3D::setWandPosition(double* t) {
	// Change the coordinatesystem to match Oculus x->x, y->z, z->-y
	wandPosition[0] = (float) -t[0];
	wandPosition[1] = (float) t[2] - 0.935f;
	wandPosition[2] = (float) t[1];
}

void Passive3D::setWandOrientation(double* o) {

	std::copy(o, o + 16, wandOrientation);
}

void Passive3D::setWandTransform(float* T)
{
	std::copy(T, T + 16, transformMatrix);
}