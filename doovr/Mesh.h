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
};

//! Data structure containing three indices of the vertexArray that make a certain triangle. Points to one edge in the triangle
struct triangle {
	GLuint index[3];
};

//! Data structure halfEdge pointing to the next edge in the triangle counter clockwise.
struct halfEdge {
	halfEdge* nextEdge;
	halfEdge* sibling;
	int triangle;
	int vertex;
	bool needsUpdate = false;
};


//! A class representing a modifiable 3D mesh 
class Mesh {
  public:
	Mesh(float rad);
	~Mesh();

	void dilate(float* p, float lp[3], float rad, bool but);
	void test(float bRad, int vNR, bool plus);

	void render();

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
	float vecLength(float vec[3]);
	//! Sorts vertecies by the x coordinate into ascending order
	bool sortByXCord(const vertex &a, const vertex &b);
	//! Calculates the vector between to points a and b and returns a pointer to the vec
	void calculateVec(float* newVec, float a[3], float b[3]);

	//! updates the changed vertecies normal and checks if retriangulation is needed.
	void updateArea(int* changeList, int listSize);
	//! adds a vertex in the middle between the vertexpoints pA and pB.
	/*! pA is the position of currVert, pB is the position of nVert,
		currVert and nVert are the indecies of the vertecies in the vertexArray,
		counter is the number of changed vertecies */
	void addVertex(float* pA, float* pB, float* vecA2B, halfEdge* &edge);
	//! removes the vertexpoint nVert and moves currVert halfway to nVert.
	/*! pA is the position of currVert, pB is the position of nVert, 
		currVert and nVert are the indecies of the vertecies in the vertexArray,
		counter is what element in the changedCounter we are in */
	bool rmVertex(float* pA, float* pB, float* vecA2B, int currVert, int nVert, int* sharedTriNeighbor, int* counter);

	const int ROWS = 100;
	const int COLS = 100;

	const float MAX_LENGTH = 0.08f*0.1f;
	const float MIN_LENGTH = 0.0399f*0.1f;

	GLuint vao;          // Vertex array object, the main handle for geometry
	
	GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
	GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
	//vector<GLfloat> vertexArray; // Vertex array on interleaved format: x y z nx ny nz s t
	//vector<GLuint> indexArray;   // Element index array

	std::vector<triangle> indexArray;
	std::vector<vertex> vertexArray;

	std::vector<halfEdge*> vertexEPtr;
	std::vector<halfEdge*> triEPtr;

	float position[3];
	float orientation[16];

	bool isMoved = false;
};