#pragma once
#include "Entity.h"
#include "Utilities.h"
#include <vector>
#include "Mesh.h"

//! Data structure containing the coordinates and normal coordinates of a vertex, aswell as a pointer to an adjacent face
struct planeVertexData {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	GLfloat u;
	GLfloat v;
	//int arrayIndex;
};

class Plane :
	public Entity
{

public:
	Plane()
	{
		vao = 0;
		vertexbuffer = 0;
		indexbuffer = 0;
		nverts = 0;
		ntris = 0;
	};

	Plane(float x, float y, float z, float dX, float dZ);
	~Plane(void);

	void render();

private:
	GLuint vao;          // Vertex array object, the main handle for geometry
	int nverts;			 // Number of vertices in the vertex array
	int ntris;			 // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER

	vector<planeVertexData> vertexArray;	   // Vertex array on interleaved format: x y z nx ny nz u v
	vector<triangle> indexArray;   // Element index array

};
