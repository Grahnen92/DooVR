#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "glm/glm.hpp"

#include "Utilities.h"


using namespace std;

class Entity
{
	public:
		//getters
		char getOtype(){ return oType; }

		glm::vec3 getPosition(){ return position; }

		glm::vec3 getColor(){ return color; }
		float getColorR(){ return color.x; }
		float getColorG(){ return color.y; }
		float getColorB(){ return color.z; }

		// To print
		friend ostream& operator<<(ostream &os, const Entity &E);

		virtual void render() = 0; // Calls the TriangleSoup function to render the geometry

	protected:

		char oType; 
		glm::vec3 position;	
		glm::vec3 color;

		virtual void display(ostream& os) const = 0;
};