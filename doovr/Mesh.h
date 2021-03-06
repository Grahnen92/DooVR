#include "Utilities.h"
#include <vector>

typedef struct vertex vertex;

//! Data structure containing the coordinates and normal coordinates of a vertex, aswell as a pointer to an adjacent face
struct vertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	//int arrayIndex;
};

struct vertexInf
{
	int vertexNeighbors[8];
	int triangleNeighbors[8];
};
//! Data structure containing three indices of the vertexArray that make a certain triangle
struct triangle {
	GLuint index1;
	GLuint index2;
	GLuint index3;
};


//! A class representing a modifiable 3D mesh 
class Mesh {
  public:
	Mesh();
	~Mesh();

	//void updateVertexArray(float* p, bool but);

	void dilate(float* p, float lp[3], float rad, bool but);

	//void moveThroughMesh(int it);
	void render();

	void updateArea(int currVert);

	vertex* getVertexList();
	triangle* getIndexList();

	float* getPosition(){ return position; };
	float* getOrientation(){ return orientation; };

	void setPosition(float* p) { position[0] = p[0]; position[1] = p[1]; position[2] = p[2]; }
	void setOrientation(float* o) { std::copy(o, o + 16, orientation); }

	bool getisMoved() { return isMoved; }
	void setisMoved(bool b) { isMoved = b; }

  private:
	//! Calculates the vector lenght between two vertex
	float vectorLength(vertex vertex1, vertex vertex2);
	//! Calculates the lenght of a vector
	float vecLenght(float vec[3]);
	//! Sorts vertecies by the x coordinate into ascending order
	bool sortByXCord(const vertex &a, const vertex &b);
	//! Calculates the vector between to points a and b and returns a pointer to the vec
	void calculateVec(float* newVec, float a[3], float b[3]);

	int rows;
	int cols;

	GLuint vao;          // Vertex array object, the main handle for geometry
	
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	//vector<GLfloat> vertexArray; // Vertex array on interleaved format: x y z nx ny nz s t
	//vector<GLuint> indexArray;   // Element index array

	std::vector<triangle> indexArray;
	std::vector<vertex> vertexArray;
	std::vector<vertexInf> vertexInfo;

	float position[3];
	float orientation[16];

	bool isMoved = false;
};