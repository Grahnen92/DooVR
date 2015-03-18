#include "Utilities.h"
#include <vector>


struct vertex{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	int index;
};

struct triangle{
	GLuint index1;
	GLuint index2;
	GLuint index3;
};

struct face{
	face*  f[3];
	vertex* v[3];
};

class Mesh
{
public:


	Mesh();

	~Mesh();

	void updateVertexArray(double x, double y);

	void render();

private:

	GLuint vao;          // Vertex array object, the main handle for geometry
	
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	//vector<GLfloat> vertexArray; // Vertex array on interleaved format: x y z nx ny nz s t
	//vector<GLuint> indexArray;   // Element index array

	std::vector<triangle> indexArray;
	std::vector<vertex> vertexArray;
	//std::vector <int[]> triangleList;
};