#include "Utilities.h"
#include <vector>



typedef struct face face;
typedef struct vertex vertex;

//! Data structure containing all necessary information regarding a facetrianglepolygon
struct face {

	//! Pointer to adjacent faces
	face * nFace[3];
	int indexindex;

	//! Pointer to the faces vertecies
	vertex *vertices[3];
	int vertexindex[3];
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


	void updateVertexArray(float* p, bool but);

	void dilate(float* p, float lp[3], float rad, bool but);

	void moveThroughMesh(int it);
	void render();

	void updateNormal(face* fp);

	vertex* getVertexList();
	triangle* getIndexList();

	float* getPosition(){ return position; };
	float* getOrientation(){ return orientation; };

	void setPosition(float* p) { position[0] = p[0]; position[1] = p[1]; position[2] = p[2]; }
	void setOrientation(float* o) { std::copy(o, o + 16, orientation); }

  private:
	float vectorLength(vertex vertex1, vertex vertex2);
	bool sortByXCord(const vertex &a, const vertex &b);

	int rows;
	int cols;

	GLuint vao;          // Vertex array object, the main handle for geometry
	
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	//vector<GLfloat> vertexArray; // Vertex array on interleaved format: x y z nx ny nz s t
	//vector<GLuint> indexArray;   // Element index array

	std::vector<triangle> indexArray;
	std::vector<vertex> vertexArray;

	float position[3];
	float orientation[16];
};