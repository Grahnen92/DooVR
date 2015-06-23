#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <stdio.h>  // For file input in soupReadOBJ()
#include <stdlib.h> // For malloc() and free()
#include <math.h>   // For sin() and cos() in soupCreateSphere()

#include "Utilities.h"


using namespace std;

class Entity
{
	public:
		//getters
		char getOtype(){ return oType; }

		float* getPosition(){ return position; }
		void setPosition(float* p) { position[0] = p[0]; position[1] = p[1]; position[2] = p[2]; }

		float* getOrientation(){ return orientation; }
		void setOrientation(float* o) { std::copy(o, o + 16, orientation); }

		// To print
		friend ostream& operator<<(ostream &os, const Entity &E);

		virtual void render() = 0; // Calls the TriangleSoup function to render the geometry

	protected:

		char oType; 
		float position[3];	
		float orientation[16];

};