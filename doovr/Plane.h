#pragma once
#include "Entity.h"
#include "Utilities.h"
#include <vector>

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

	Plane(glm::vec3 _pos, glm::vec2 _dim);
	~Plane(void);

	glm::vec3 getNormal() { return normal; }
	void setNormal(glm::vec3 n){ normal = n;}

	void updateVertexArray(double x, double y );

	void render();
	glm::vec2 getDim(){ return dim; }

private:
	GLuint vao;          // Vertex array object, the main handle for geometry
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER

	GLfloat *vertexarray; // Vertex array on interleaved format: x y z nx ny nz s t
	GLuint *indexarray;   // Element index array

	glm::vec2 dim;
	glm::vec3 normal;

	void display(ostream& os) const;
};
