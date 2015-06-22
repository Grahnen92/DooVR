#pragma once
#include "Entity.h"

class hexBox :
	public Entity
{
public:
	hexBox()
	{
		vao = 0;
		vertexbuffer = 0;
		indexbuffer = 0;
		vertexarray = NULL;
		indexarray = NULL;
		nverts = 0;
		ntris = 0;
	};

	hexBox(float x, float y, float z, float tX, float tY);
	~hexBox(void);

	void setFunction(int f) { function = f; }
	int getFunction() { return function; }

	void move(float h);
	void moveInstant(float h);
	void GLcalls();
	

	void render();

private:
	GLuint vao;          // Vertex array object, the main handle for geometry
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	GLfloat *vertexarray; // Vertex array on interleaved format: x y z nx ny nz s t
	GLuint *indexarray;   // Element index array
	int function;
	void display(ostream& os) const;
};