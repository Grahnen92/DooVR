#include "Passive3D.h"


Passive3D::Passive3D()
{
}


Passive3D::~Passive3D()
{
}

void Passive3D::wand3dCallback(wand3d::WandData data) {
	std::cout << data << std::endl;
}
