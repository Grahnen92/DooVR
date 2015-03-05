#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "glm\glm.hpp"

#include "Utilities.h"

using namespace std;

class Entity
{
	public:

		// Do we really need these "calculate"-functions? Aren't the calculations
		// done by a physics handler class that does all calculations and then calls
		// the setter-functions of the physics object?
		void calculatePosition();
		void calculateVelocity();
		void calculateAcceleration();
		
		void caluclateOrientation();
		void calculateAngularVelocity();
		void calculateAngularAcceleration();

		//getters
		float getMass(){return mass;}
		float getInertia(){return inertia;}
		bool getStatic() { return isStatic; }
		glm::vec3 getCenterOfMass(){ return centerOfMass; }
		char getOtype(){ return oType; }

		glm::vec3 getPosition(){ return position; }
		glm::vec3 getVelocity(){ return velocity; }
		glm::vec3 getAcceleration(){ return acceleration; }

		glm::vec3 getOrientation(){ return orientation; }
		glm::vec3 getRotAxis(){ return rotAxis; }
		float getAngularPosition(){ return angularPosition; }
		float getAngularVelocity(){ return angularVelocity; }
		float getAngularAcceleration(){ return angularAcceleration; }

		glm::vec3 getColor(){ return color; }
		float getColorR(){ return color.x; }
		float getColorG(){ return color.y; }
		float getColorB(){ return color.z; }

		//setters
		void setMass(float m){ mass = m; }
		void setInertia(float i){ inertia = i; }
		void setCenterOfMass(glm::vec3 c){ centerOfMass = c; }

		void setPosition(glm::vec3 p){ position = p; }
		void setVelocity(glm::vec3 v){ velocity = v; }
		void setAcceleration(glm::vec3 a){ acceleration = a; }

		void setOrientation(glm::vec3 o){ orientation = o; }
		void setRotAxis(glm::vec3 _rotAxis){ rotAxis = _rotAxis; }
		void setAngularPosition(float a){ angularPosition = a; }
		void setAngularVelocity(float a){ angularVelocity = a; }
		void setAngularAcceleration(float a){ angularAcceleration = a; }

		// To print
		friend ostream& operator<<(ostream &os, const Entity &E);

		virtual void render() = 0; // Calls the TriangleSoup function to render the geometry

	protected:

		bool isStatic;
		float mass;
		float inertia;
		glm::vec3 centerOfMass;
		char oType; 



		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		
		glm::vec3 orientation;
		glm::vec3 rotAxis;
		float angularPosition;
		float angularVelocity;
		float angularAcceleration;
		
		glm::vec3 color;

		virtual void display(ostream& os) const = 0;
};