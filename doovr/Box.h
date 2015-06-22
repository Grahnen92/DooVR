#pragma once
#include "Entity.h"

class Box : public Entity {
  public:
	Box() {
		vao = 0;
		vertexbuffer = 0;
		indexbuffer = 0;
		vertexarray = NULL;
		indexarray = NULL;
		nverts = 0;
		ntris = 0;
	};

	Box(float _pos[3], float _dim[3]);
	~Box(void);

	void createBox(float xSize, float ySize, float zSize);

	void render();
	float* getDim() { return dim; }

  private:
	GLuint vao;          // Vertex array object, the main handle for geometry
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	GLfloat *vertexarray; // Vertex array on interleaved format: x y z nx ny nz s t
	GLuint *indexarray;   // Element index array
	float dim[3];

	void display(ostream& os) const;
};