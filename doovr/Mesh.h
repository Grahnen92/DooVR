#include "Utilities.h"
#include "linAlg.h"
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

	//dilate/erode based modelling
	void sculpt(float* p, float lp[3], float rad, bool but);
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

	//! updates the changed vertecies normal and checks if retriangulation is needed.
	void updateArea(int* changeList, int listSize);
	//! adds a vertex in the middle between the vertexpoints pA and pB.
	/*! pA is the position of currVert, edge is the edge that is to long*/
	void edgeSplit(float* vPoint, float* vec, halfEdge* &edge);
	//! removes the vertexpoint nVert and moves currVert halfway towards nVert.
	/*! vPoint is the position of currVert, vec is the vector between the vertecies that are to close to each other,
	and edge is a pointer to the edge that is to short*/
	void edgeCollapse(float* vPoint, float* vec, halfEdge* &edge);

	//! subdivides the surface into a sphere
	void edgeSubdivide(float* pA, float* vecA2B, halfEdge* &edge, bool update, float rad);

	const int ROWS = 100;
	const int COLS = 100;


	const float MAX_LENGTH = 0.025f *0.2f; // 0.08f*0.1f;
	const float MIN_LENGTH = 0.01f *0.2f;

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