#pragma once
#include "entity.h"
#include "Utilities.h"
#include <vector>

struct vertex{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
struct triangle{
	GLuint index1;
	GLuint index2;
	GLuint index3;
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

	Plane(glm::vec3 _pos, float _mass, glm::vec2 _dim);
	~Plane(void);

	glm::vec3 getNormal() { return normal; }
	void setNormal(glm::vec3 n){ normal = n;}

	void updateVertexArray();

	void render();
	glm::vec2 getDim(){ return dim; }

private:



	GLuint vao;          // Vertex array object, the main handle for geometry
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	//vector<GLfloat> vertexArray; // Vertex array on interleaved format: x y z nx ny nz s t
	//vector<GLuint> indexArray;   // Element index array

	std::vector<triangle> vIndexArray;
	std::vector<vertex> vVertexArray;

	glm::vec2 dim;
	glm::vec3 normal;

	void display(ostream& os) const;
};
