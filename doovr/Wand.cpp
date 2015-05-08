#include "Wand.h"

Wand::Wand()
{
	Utilities::makeUniform(transformMatrix);
}


Wand::~Wand()
{
}

void Wand::print_transformMatrix() {

	for (int i = 0; i < 16; i++) {
		std::cout << std::fixed << std::setprecision(2);
		std::cout << "  " << transformMatrix[i] << "  ";
		if (i == 3 || i == 7 || i == 11)	std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;

}