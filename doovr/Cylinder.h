#pragma once
#include "Entity.h"
#include "Utilities.h"

class Cylinder : public Entity {
public:

	// Creates a Cylinder  
	Cylinder(float* _pos, float _rad);
	~Cylinder(void);

	Cylinder() {
		vao = 0;
		vertexbuffer = 0;
		indexbuffer = 0;
		vertexarray = NULL;
		indexarray = NULL;
		nverts = 0;
		ntris = 0;
	};

	void createCylinder(float radius, int segments);
	void render();

	float getRadius(){ return radius; }

private:
	GLuint vao;          // Vertex array object, the main handle for geometry
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	GLfloat *vertexarray; // Vertex array on interleaved format: x y z nx ny nz s t
	GLuint *indexarray;   // Element index array

	float radius;
	void display(ostream& os) const;
};