#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "glm/glm.hpp"

#include "Utilities.h"

#include "structs.h"


using namespace std;

class Entity
{
	public:
		//getters
		char getOtype(){ return oType; }



		glm::vec3 getColor(){ return color; }
		float getColorR(){ return color.x; }
		float getColorG(){ return color.y; }
		float getColorB(){ return color.z; }

		float* getPosition(){ return position; }
		void setPosition(float p[3]) { position[0] = p[0]; position[1] = p[1]; position[2] = p[2]; }

		float* getOrientation(){ return orientation; }
		void setOrientation(float o[3]) { std::copy(o, o + 16, orientation); }

		// To print
		friend ostream& operator<<(ostream &os, const Entity &E);

		virtual void render() = 0; // Calls the TriangleSoup function to render the geometry

	protected:

		char oType; 
		float position[3];	
		float orientation[16];
		glm::vec3 color;

		virtual void display(ostream& os) const = 0;
};