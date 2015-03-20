#include "Utilities.h"
#include <vector>



typedef struct face face;
typedef struct vertex vertex;

//! Data structure containing all necessary information regarding a facetrianglepolygon
struct face {
	//! Pointer to adjacent faces
	face * nFace[3];
	//! Pointer to the faces vertecies
	vertex *vertices[3];
};
//! Data structure containing the coordinates and normal coordinates of a vertex, aswell as a pointer to an adjacent face
struct vertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	face *adjacentFace;
};
//! Data structure containing three indices of the vertexArray that make a certain triangle
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

//! A class representing a modifiable 3D mesh 
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
	float vectorLength(vertex vertex1, vertex vertex2);
	bool sortByXCord(const vertex &a, const vertex &b);

	GLuint vao;          // Vertex array object, the main handle for geometry
	
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	//vector<GLfloat> vertexArray; // Vertex array on interleaved format: x y z nx ny nz s t
	//vector<GLuint> indexArray;   // Element index array

	std::vector<triangle> indexArray;
	std::vector<vertex> vertexArray;
};