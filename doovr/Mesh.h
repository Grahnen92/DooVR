#include "Utilities.h"
#include <vector>

typedef struct face face;
typedef struct vertex vertex;

struct face {
	face * nFace[3];
	vertex *vertices[3];
};

struct vertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	face *adjacentFace;
};

struct triangle {
	GLuint index1;
	GLuint index2;
	GLuint index3;
};

/*
struct halfEdge{
	vertex* pVertex;
	face* bFace;
	halfEdge* nEdge;
	halfEdge* oEdge;
};
*/


class Mesh {
  public:
	Mesh();
	~Mesh();

	void updateVertexArray(double x, double y);
	void updateVertexArray2(double x, double y);
	void moveThroughMesh(int it);
	void render();

	vertex* getVertexList();
	triangle* getIndexList();

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