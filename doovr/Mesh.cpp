#include "Mesh.h"
#include "time.h"
#include "math.h"
#include <algorithm>
#include <iterator>

using namespace std;
#define M_PI 3.14159265358979323846

void normVec(float* vec) {
	float length = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	vec[0] = vec[0] / length;
	vec[1] = vec[1] / length;
	vec[2] = vec[2] / length;
}

void crossProd(float normal[3], float* vec1, float* vec2) {
	normal[0] = (vec1[1] * vec2[2] - vec1[2] * vec2[1]);
	normal[1] = -(vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	normal[2] = (vec1[0] * vec2[1] - vec1[1] * vec2[0]);
}

Mesh::Mesh(float rad) {
	triangle tempT;
	vertex tempV;
	halfEdge* tempE1;
	halfEdge* tempE2;
	halfEdge* tempE3;

	vertexArray.reserve(1000000);
	indexArray.reserve(1000000);

	vertexEPtr.reserve(1000000);
	triEPtr.reserve(1000000);
	vertexEPtr.resize(8);
	triEPtr.resize(8);
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;

	orientation[0] = 1.0f;
	orientation[1] = 0.0f;
	orientation[2] = 0.0f;
	orientation[3] = 0.0f;

	orientation[4] = 0.0f;
	orientation[5] = 1.0f;
	orientation[6] = 0.0f;
	orientation[7] = 0.0f;

	orientation[8] = 0.0f;
	orientation[9] = 0.0f;
	orientation[10] = 1.0f;
	orientation[11] = 0.0f;

	orientation[12] = 0.0f;
	orientation[13] = 0.0f;
	orientation[14] = 0.0f;
	orientation[15] = 1.0f;

	triangle* indexP;
	vertex * vertexP;

	int vertexIndex;
	float scaleF = 1.0f / (ROWS * 2);
	
	// place vertecies
	// Y 0
	tempV.x = 0.0f;	tempV.y = rad;	tempV.z = 0.0f; 	tempV.nx = 0.0f;	tempV.ny = rad;	tempV.nz = 0.0f;
	vertexArray.push_back(tempV);

	tempV.x = 0.0f;	tempV.y = -rad;	tempV.z = 0.0f; 	tempV.nx = 0.0f;	tempV.ny = -rad;	tempV.nz = 0.0f;
	vertexArray.push_back(tempV);

	// X 2
	tempV.x = rad;	tempV.y = 0.0f;	tempV.z = 0.0f; 	tempV.nx = rad;	tempV.ny = 0.0f;	tempV.nz = 0.0f;
	vertexArray.push_back(tempV);

	tempV.x = -rad;	tempV.y = 0.0f;	tempV.z = 0.0f; 	tempV.nx = -rad;	tempV.ny = 0.0f;	tempV.nz = 0.0f;
	vertexArray.push_back(tempV);

	// Z 4
	tempV.x = 0.0f;	tempV.y = 0.0f;	tempV.z = -rad; 	tempV.nx = 0.0f;	tempV.ny = 0.0f;	tempV.nz = -rad;
	vertexArray.push_back(tempV);

	tempV.x = 0.0f;	tempV.y = 0.0f;	tempV.z = rad; 	tempV.nx = 0.0f;	tempV.ny = 0.0f;	tempV.nz = rad;
	vertexArray.push_back(tempV);

	// bind triangles
	tempT.index[0] = 0;	tempT.index[1] = 3; tempT.index[2] = 5;
	indexArray.push_back(tempT);

	tempT.index[0] = 0;	tempT.index[1] = 5; tempT.index[2] = 2;
	indexArray.push_back(tempT);

	tempT.index[0] = 0;	tempT.index[1] = 2;	tempT.index[2] = 4;
	indexArray.push_back(tempT);

	tempT.index[0] = 0;	tempT.index[1] = 4;	tempT.index[2] = 3;
	indexArray.push_back(tempT);

	tempT.index[0] = 1;	tempT.index[1] = 5;	tempT.index[2] = 3;
	indexArray.push_back(tempT);

	tempT.index[0] = 1;	tempT.index[1] = 2;	tempT.index[2] = 5;
	indexArray.push_back(tempT);

	tempT.index[0] = 1;	tempT.index[1] = 4; tempT.index[2] = 2;
	indexArray.push_back(tempT);

	tempT.index[0] = 1; tempT.index[1] = 3; tempT.index[2] = 4;
	indexArray.push_back(tempT);
	
	// Bind halfEdges
	//TOP
	//first tri
	tempE1 = new halfEdge;	tempE1->vertex = 0; tempE1->triangle = 0;
	triEPtr[0] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 3; tempE1->triangle = 0;
	triEPtr[0]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 5; tempE1->triangle = 0;
	triEPtr[0]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[0];

	vertexEPtr[0] = tempE1;

	//second tri
	tempE1 = new halfEdge;	tempE1->vertex = 0; tempE1->triangle = 1;
	triEPtr[1] = tempE1;
	vertexEPtr[5] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 5; tempE1->triangle = 1;
	triEPtr[1]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 2; tempE1->triangle = 1;
	triEPtr[1]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[1];

	//third tri
	tempE1 = new halfEdge;	tempE1->vertex = 0; tempE1->triangle = 2;
	triEPtr[2] = tempE1;
	vertexEPtr[2] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 2; tempE1->triangle = 2;
	triEPtr[2]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 4; tempE1->triangle = 2;
	triEPtr[2]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[2];

	//fourth tri
	tempE1 = new halfEdge;	tempE1->vertex = 0; tempE1->triangle = 3;
	triEPtr[3] = tempE1;
	vertexEPtr[4] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 4; tempE1->triangle = 3;
	triEPtr[3]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 3; tempE1->triangle = 3;
	triEPtr[3]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[3];

	//BOTTOM
	//fifth tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 4;
	triEPtr[4] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 5; tempE1->triangle = 4;
	triEPtr[4]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 3; tempE1->triangle = 4;
	triEPtr[4]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[4];

	vertexEPtr[1] = tempE1;

	//sixth tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 5;
	triEPtr[5] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 2; tempE1->triangle = 5;
	triEPtr[5]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 5; tempE1->triangle = 5;
	triEPtr[5]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[5];

	//seventh tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 6;
	triEPtr[6] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 4; tempE1->triangle = 6;
	triEPtr[6]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 2; tempE1->triangle = 6;
	triEPtr[6]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[6];

	//seventh tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 7;
	triEPtr[7] = tempE1;
	vertexEPtr[3] = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 3; tempE1->triangle = 7;
	triEPtr[7]->nextEdge = tempE1;
	tempE1 = new halfEdge;	tempE1->vertex = 4; tempE1->triangle = 7;
	triEPtr[7]->nextEdge->nextEdge = tempE1;
	tempE1->nextEdge = triEPtr[7];

	//TOP SIBLINGS
	triEPtr[0]->sibling = triEPtr[3]->nextEdge->nextEdge;
	triEPtr[3]->nextEdge->nextEdge->sibling = triEPtr[0];

	triEPtr[3]->sibling = triEPtr[2]->nextEdge->nextEdge;
	triEPtr[2]->nextEdge->nextEdge->sibling = triEPtr[3];

	triEPtr[2]->sibling = triEPtr[1]->nextEdge->nextEdge;
	triEPtr[1]->nextEdge->nextEdge->sibling = triEPtr[2];

	triEPtr[1]->sibling = triEPtr[0]->nextEdge->nextEdge;
	triEPtr[0]->nextEdge->nextEdge->sibling = triEPtr[1];

	//BOTTOM SIBLINGS
	triEPtr[4]->sibling = triEPtr[5]->nextEdge->nextEdge;
	triEPtr[5]->nextEdge->nextEdge->sibling = triEPtr[4];

	triEPtr[5]->sibling = triEPtr[6]->nextEdge->nextEdge;
	triEPtr[6]->nextEdge->nextEdge->sibling = triEPtr[5];

	triEPtr[6]->sibling = triEPtr[7]->nextEdge->nextEdge;
	triEPtr[7]->nextEdge->nextEdge->sibling = triEPtr[6];

	triEPtr[7]->sibling = triEPtr[4]->nextEdge->nextEdge;
	triEPtr[4]->nextEdge->nextEdge->sibling = triEPtr[7];

	//MIDDLE SIBLINGS
	triEPtr[0]->nextEdge->sibling = triEPtr[4]->nextEdge;
	triEPtr[4]->nextEdge->sibling = triEPtr[0]->nextEdge;
	
	triEPtr[1]->nextEdge->sibling = triEPtr[5]->nextEdge;
	triEPtr[5]->nextEdge->sibling = triEPtr[1]->nextEdge;

	triEPtr[2]->nextEdge->sibling = triEPtr[6]->nextEdge;
	triEPtr[6]->nextEdge->sibling = triEPtr[2]->nextEdge;

	triEPtr[3]->nextEdge->sibling = triEPtr[7]->nextEdge;
	triEPtr[7]->nextEdge->sibling = triEPtr[3]->nextEdge;

	vector<triangle> tempList;
	triangle tempTri;

	for (int i = 0; i < indexArray.size(); i++) {
		tempTri.index[0] = indexArray[i].index[0];
		tempTri.index[1] = indexArray[i].index[1];
		tempTri.index[2] = indexArray[i].index[2];
		tempList.push_back(tempTri);
	}

	vertexP = &vertexArray[0];
	indexP = &tempList[0];
	// Generate one vertex array object (VAO) and bind it
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate two buffer IDs
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &indexbuffer);

	// Activate the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Present our vertex coordinates to OpenGL
	glBufferData(GL_ARRAY_BUFFER,
		(vertexArray.size() + 100000)*sizeof(vertex), NULL, GL_STREAM_DRAW);

	vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertex)*vertexArray.size(),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

	for (int i = 0; i < vertexArray.size(); i++) {
		vertexP[i].x = vertexArray[i].x;
		vertexP[i].y = vertexArray[i].y;
		vertexP[i].z = vertexArray[i].z;
		vertexP[i].nx = vertexArray[i].nx;
		vertexP[i].ny = vertexArray[i].ny;
		vertexP[i].nz = vertexArray[i].nz;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);

	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
	glEnableVertexAttribArray(1); // Normals
	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3, 6 (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals

	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex indices to OpenGL
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		(indexArray.size() + 100000)*sizeof(triangle), NULL, GL_STREAM_DRAW);

	indexP = (triangle*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangle) * indexArray.size(),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

	for (int i = 0; i < indexArray.size(); i++) {
		indexP[i].index[0] = indexArray[i].index[0];
		indexP[i].index[1] = indexArray[i].index[1];
		indexP[i].index[2] = indexArray[i].index[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the buffers while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh(void) {

}

void Mesh::dilate(float* p, float lp[3], float rad, bool but) {
	glm::vec4 tempvec;
	vertex tempV;
	float tempVec1[3]; float tempVec2[3];
	float wPoint[3]; float vPoint[3];

	vector<int> changedVertices;
	changedVertices.reserve(100);
	int changeCount = 0;

	int oldArraySize = vertexArray.size();
	int oldIndArraySize = indexArray.size();

	triangle* indexP;
	vertex* vertexP;

	bool success = false;

	int startRow = -1;
	int endRow = -1;
	int prevRow = -1;
	vector<int> startCol;	// first edited column on row
	vector<int> endCol;		// last edited column on row

	//MOVEMENT BETWEEN LAST FRAME AND THIS FRAME
	float mLength = 0.0f;
	float pMove[3];
	pMove[0] = (p[0] - lp[0]);
	pMove[1] = (p[1] - lp[1]);
	pMove[2] = (p[2] - lp[2]);
	mLength = vecLength(pMove);

	tempvec = glm::transpose(glm::make_mat4(orientation)) * glm::vec4(pMove[0], pMove[1], pMove[2], 1.0f);
	pMove[0] = tempvec.x;
	pMove[1] = tempvec.y;
	pMove[2] = tempvec.z;

	tempV.z = 0;
	
	wPoint[0] = p[0] - position[0];
	wPoint[1] = p[1] - position[1];
	wPoint[2] = p[2] - position[2];

	tempvec = glm::transpose(glm::make_mat4(orientation)) * glm::vec4(wPoint[0], wPoint[1], wPoint[2], 1.0f);
	wPoint[0] = tempvec.x;
	wPoint[1] = tempvec.y;
	wPoint[2] = tempvec.z;

	for (int i = 0; i < vertexArray.size(); i++) {
		vPoint[0] = vertexArray[i].x;
		vPoint[1] = vertexArray[i].y;
		vPoint[2] = vertexArray[i].z;
		tempVec1[0] = vPoint[0] - wPoint[0];
		tempVec1[1] = vPoint[1] - wPoint[1];
		tempVec1[2] = vPoint[2] - wPoint[2];
		
		if ( vecLength(tempVec1) < rad) {

			normVec(tempVec1);

			tempVec2[0] = (tempVec1[0] + vertexArray[i].nx) / 2.0f;
			tempVec2[1] = (tempVec1[1] + vertexArray[i].ny) / 2.0f;
			tempVec2[2] = (tempVec1[2] + vertexArray[i].nz) / 2.0f;
			vertexArray[i].x += tempVec2[0]*mLength;
			vertexArray[i].y += tempVec2[1] * mLength;
			vertexArray[i].z += tempVec2[2] * mLength;

			changedVertices.push_back(i);
			changeCount++;

			success = true;
		}
	}

	changeCount = 0;
	if (changedVertices.size() > 0)
		//updateArea(&changedVertices[0], changedVertices.size());

	if (success == true) {

		vertexP = &vertexArray[0];


		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertex)*vertexArray.size(),
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		for (int i = 0; i < vertexArray.size(); i++) {
			vertexP[i].x = vertexArray[i].x;
			vertexP[i].y = vertexArray[i].y;
			vertexP[i].z = vertexArray[i].z;
			vertexP[i].nx = vertexArray[i].nx;
			vertexP[i].ny = vertexArray[i].ny;
			vertexP[i].nz = vertexArray[i].nz;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		// Specify how many attribute arrays we have in our VAO
		glEnableVertexAttribArray(0); // Vertex coordinates
		glEnableVertexAttribArray(1); // Normals

		// Specify how OpenGL should interpret the vertex buffer data:
		// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
		// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
		// Type GL_FLOAT
		// Not normalized (GL_FALSE)
		// Stride 8 (interleaved array with 8 floats per vertex)
		// Array buffer offset 0, 3, 6 (offset into first vertex)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(GLfloat), (void*)0); // xyz coordinates
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals

		// Activate the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

		const int testst = indexArray.size();

		//vector<triangle> tempList;
		//tempList.reserve(indexArray.size());
		//indexP = &tempList[0];


		//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		//	sizeof(triangle)*indexArray.size(), &indexArray, GL_STREAM_DRAW);

		// Present our vertex <indices to OpenGL
		indexP = (triangle*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangle) * indexArray.size(),
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		for (int i = 0; i < indexArray.size(); i++) {
			indexP[i].index[0] = indexArray[i].index[0];
			indexP[i].index[1] = indexArray[i].index[1];
			indexP[i].index[2] = indexArray[i].index[2];
		}

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

		// Deactivate (unbind) the VAO and the buffers again.
		// Do NOT unbind the buffers while the VAO is still bound.
		// The index buffer is an essential part of the VAO state.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Mesh::test(float bRad, int vNR, bool plus) {
	glm::vec4 tempvec;
	vertex tempV;

	vector<int> changedVertices;
	changedVertices.reserve(100);
	int changeCount = 0;

	int oldArraySize = vertexArray.size();
	int oldIndArraySize = indexArray.size();
	//MOVEMENT BETWEEN LAST FRAME AND THIS FRAME

	float test1[3] = { 0.0f, 0.0f, 0.0f };
	float test2[3] = { 1.0f, 1.0f, 1.0f };

	tempV.z = 0;
	vertex point;
	point.x = 0.0f;
	point.y = 0.0f;
	point.z = 0.0f;

	int testPoint = vNR;


	triangle* indexP;
	vertex* vertexP;

	bool success = false;


	int startRow = -1;
	int endRow = -1;
	int prevRow = -1;
	vector<int> startCol;	// first edited column on row
	vector<int> endCol;		// last edited column on row

	for (int i = 0; i < vertexArray.size(); i++) {
		//if (testPoint == i || testPoint == i + 1|| testPoint == i - 1|| testPoint == i + 100|| testPoint == i + 1 + 100|| testPoint == i - 1 + 100) {
		if (testPoint == i) {

			if (plus)
			{

			}
			else
				vertexArray[i].z += 0.0001f;

			changedVertices.push_back(5051);
			changeCount++;

			success = true;
		}
	}

	//updateArea(&changedVertices[0], changedVertices.size());
		
	if (success == true) {

		vertexP = &vertexArray[0];


		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertex)*vertexArray.size(),
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		for (int i = 0; i < vertexArray.size(); i++) {
			vertexP[i].x = vertexArray[i].x;
			vertexP[i].y = vertexArray[i].y;
			vertexP[i].z = vertexArray[i].z;
			vertexP[i].nx = vertexArray[i].nx;
			vertexP[i].ny = vertexArray[i].ny;
			vertexP[i].nz = vertexArray[i].nz;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		// Specify how many attribute arrays we have in our VAO
		glEnableVertexAttribArray(0); // Vertex coordinates
		glEnableVertexAttribArray(1); // Normals

		// Specify how OpenGL should interpret the vertex buffer data:
		// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
		// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
		// Type GL_FLOAT
		// Not normalized (GL_FALSE)
		// Stride 8 (interleaved array with 8 floats per vertex)
		// Array buffer offset 0, 3, 6 (offset into first vertex)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(GLfloat), (void*)0); // xyz coordinates
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals

		// Activate the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

		const int testst = indexArray.size();

		//vector<triangle> tempList;
		//tempList.reserve(indexArray.size());
		//indexP = &tempList[0];


		//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		//	sizeof(triangle)*indexArray.size(), &indexArray, GL_STREAM_DRAW);

		// Present our vertex <indices to OpenGL
		indexP = (triangle*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangle) * indexArray.size(),
			GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		for (int i = 0; i < indexArray.size(); i++) {
			indexP[i].index[0] = indexArray[i].index[0];
			indexP[i].index[1] = indexArray[i].index[1];
			indexP[i].index[2] = indexArray[i].index[2];
		}

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

		// Deactivate (unbind) the VAO and the buffers again.
		// Do NOT unbind the buffers while the VAO is still bound.
		// The index buffer is an essential part of the VAO state.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}


vertex* Mesh::getVertexList() {
	return &vertexArray[0];
}

triangle* Mesh::getIndexList() {
	return &indexArray[0];
}

void Mesh::render() {
	glBindVertexArray(vao);
	//glColor3f(color.x, color.y, color.z);

	glDrawElements(GL_TRIANGLES, indexArray.size() * sizeof(triangle), GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex uN, type, element array buffer offset)
	glBindVertexArray(0);
}

float Mesh::vectorLength(vertex vertex1, vertex vertex2) {
	vertex vector;

	vector.x = vertex1.x - vertex2.x;
	vector.y = vertex1.y - vertex2.y;
	vector.z = vertex1.z - vertex2.z;

	return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

float Mesh::vecLength(float vec[3]) {
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

bool Mesh::sortByXCord(const vertex &a, const vertex &b) {
	return a.x < b.x;
}
/*
void Mesh::updateArea(int* changeList, int listSize) {
	//DECLARE VARIABLES
	float tempNorm1[3] = { 0.0f, 0.0f, 0.0f };
	float tempNorm2[3] = { 0.0f, 0.0f, 0.0f };

	float tempVec1[3], tempVec2[3], tempVec3[3];

	vertex tempV; vertexInf tempVI; triangle tempT;

	float vPoint1[3], vPoint2[3], vPoint3[3], vPoint4[3];

	int currVert = -1; int nVert = -1; int nTri = -1;


	vector<int> sharedTriNeighbor;
	sharedTriNeighbor.reserve(3);

	vector<int> badTri;
	badTri.reserve(2);

	int iSharedTriNeighbor[2];
	int tmpIndex1 = -1; int tmpIndex2 = -1; int tmpIndex3 = -1; 
	//while (changeCount < listSize)

	//c == loop that handles current vertex of the vertexes that need updating
	for (int c = 0; c < listSize; c++) {
		currVert = changeList[c];

		//UPDATE NORMAL //////////////////////////////////////////////////////////////////////////////////////////////
		vertexArray[currVert].nx = 0.0f; vertexArray[currVert].ny = 0.0f; vertexArray[currVert].nz = 0.0f;
		//while (uN < vertexInfo[currVert].vertexNeighbors.size()) {
		//uN == loop that updates the normal of the current vertex
		//for (int uN = 0; uN < vertexInfo[currVert].vertexNeighbors.size(); uN++) {
		for (int uN = 0; uN < vertexInfo[currVert].triangleNeighbors.size(); uN++) {
			nTri = vertexInfo[currVert].triangleNeighbors[uN];

			vPoint1[0] = vertexArray[indexArray[nTri].index[0]].x;
			vPoint1[1] = vertexArray[indexArray[nTri].index[0]].y;
			vPoint1[2] = vertexArray[indexArray[nTri].index[0]].z;

			vPoint2[0] = vertexArray[indexArray[nTri].index[1]].x;
			vPoint2[1] = vertexArray[indexArray[nTri].index[1]].y;
			vPoint2[2] = vertexArray[indexArray[nTri].index[1]].z;

			vPoint3[0] = vertexArray[indexArray[nTri].index[2]].x;
			vPoint3[1] = vertexArray[indexArray[nTri].index[2]].y;
			vPoint3[2] = vertexArray[indexArray[nTri].index[2]].z;

			calculateVec(tempVec1, vPoint2, vPoint1);
			calculateVec(tempVec2, vPoint3, vPoint1);

			crossProd(tempNorm1, tempVec1, tempVec2);

			normVec(tempNorm1);

			tempNorm2[0] += tempNorm1[0];
			tempNorm2[1] += tempNorm1[1];
			tempNorm2[2] += tempNorm1[2];

		}

		tempNorm2[0] = tempNorm2[0] / (vertexInfo[currVert].vertexNeighbors.size() - 1);
		tempNorm2[1] = tempNorm2[1] / (vertexInfo[currVert].vertexNeighbors.size() - 1);
		tempNorm2[2] = tempNorm2[2] / (vertexInfo[currVert].vertexNeighbors.size() - 1);
		vertexArray[currVert].nx = tempNorm2[0];
		vertexArray[currVert].ny = tempNorm2[1];
		vertexArray[currVert].nz = tempNorm2[2];

		// RETRIANGULATION ////////////////////////////////////////////////////////////////////////////////////////
		//cT = loop that checks if any of current vertex's links to its neighbors are too long or short
		for (int cT = 0; cT < vertexInfo[currVert].vertexNeighbors.size(); cT++){
			
			nVert = vertexInfo[currVert].vertexNeighbors[cT];

			vPoint1[0] = vertexArray[currVert].x;
			vPoint1[1] = vertexArray[currVert].y;
			vPoint1[2] = vertexArray[currVert].z;

			vPoint2[0] = vertexArray[nVert].x;
			vPoint2[1] = vertexArray[nVert].y;
			vPoint2[2] = vertexArray[nVert].z;
			calculateVec(tempVec1, vPoint2, vPoint1);
			if (vecLength(tempVec1) < MIN_LENGTH) {
				//c
					//////////////////////////////////////////////////////////////////////////////////////

				//remove bad triangles and vertex
				for (int k = 0; k < vertexInfo[currVert].triangleNeighbors.size(); k++) {
					for (int j = 0; j < vertexInfo[nVert].triangleNeighbors.size(); j++) {
						if (vertexInfo[currVert].triangleNeighbors[k] == vertexInfo[nVert].triangleNeighbors[j]) {
							sharedTriNeighbor.push_back(vertexInfo[currVert].triangleNeighbors[k]);
						}
					}
				}
					

				iSharedTriNeighbor[0] = sharedTriNeighbor[0];
				iSharedTriNeighbor[1] = sharedTriNeighbor[1];

				rmVertex(vPoint1, vPoint2, tempVec1, currVert, nVert, iSharedTriNeighbor, &cT);
				cT--;

				
				
			}
			else if (vecLength(tempVec1) > MAX_LENGTH) {

				//remove bad triangles and vertex
				for (int k = 0; k < vertexInfo[currVert].triangleNeighbors.size(); k++) {
					for (int j = 0; j < vertexInfo[nVert].triangleNeighbors.size(); j++) {
						if (vertexInfo[currVert].triangleNeighbors[k] == vertexInfo[nVert].triangleNeighbors[j]) {
							sharedTriNeighbor.push_back(vertexInfo[currVert].triangleNeighbors[k]);
						}
					}
				}
					

				iSharedTriNeighbor[0] = sharedTriNeighbor[0];
				iSharedTriNeighbor[1] = sharedTriNeighbor[1];

				addVertex(vPoint1, vPoint2, tempVec1, currVert, nVert, iSharedTriNeighbor, &cT);
				
			}
			sharedTriNeighbor.clear();
		}

	}
}
*/
void Mesh::addVertex(float* pA, float* pB, float* vecA2B, halfEdge* edge) {

	vertex tempV;
	triangle tempT;
	halfEdge* tempE;

	// create new vertex point 
	tempV.x = pA[0] + (vecA2B[0] / 2.0f);
	tempV.y = pA[1] + (vecA2B[1] / 2.0f);
	tempV.z = pA[2] + (vecA2B[2] / 2.0f);

	tempV.nx = vertexArray[edge->vertex].nx; tempV.ny = vertexArray[edge->vertex].ny; tempV.nz = vertexArray[edge->vertex].nz;
	vertexArray.push_back(tempV);

	//copy triangles
	tempT.index[0] = indexArray[edge->triangle].index[0];
	tempT.index[1] = indexArray[edge->triangle].index[1];
	tempT.index[2] = indexArray[edge->triangle].index[2];
	indexArray.push_back(tempT);

	tempT.index[0] = indexArray[edge->sibling->triangle].index[0];
	tempT.index[1] = indexArray[edge->sibling->triangle].index[1];
	tempT.index[2] = indexArray[edge->sibling->triangle].index[2];
	indexArray.push_back(tempT);

	// rebind old triangles
	for (int i = 0; i < 3; i++) {
		if (indexArray[edge->triangle].index[i] == edge->vertex)
			indexArray[edge->triangle].index[i] = vertexArray.size() - 1;

		if (indexArray[edge->sibling->triangle].index[i] == edge->vertex)
			indexArray[edge->sibling->triangle].index[i] = vertexArray.size() - 1;
	}

	// rebind new triangles
	for (int i = 0; i < 3; i++) {
		if (indexArray[indexArray.size() - 2].index[i] == edge->sibling->vertex)
			indexArray[indexArray.size() - 2].index[i] = vertexArray.size() - 1;

		if (indexArray[indexArray.size() - 1].index[i] == edge->sibling->vertex)
			indexArray[indexArray.size() - 1].index[i] = vertexArray.size() - 1;
	}

	// rebind old edge vertex
	edge->vertex = vertexArray.size() - 1;
	edge->sibling->vertex = vertexArray.size() - 1;



}
//STILL NEED TO USE COUNTER DONT FORGET
bool Mesh::rmVertex(float* pA, float* pB, float* vecA2B, int currVert, int nVert, int* sharedTriNeighbor, int* counter) {
	
	
	return true;
}


void Mesh::calculateVec(float* newVec, float* a, float* b) {
	newVec[0] = a[0] - b[0];
	newVec[1] = a[1] - b[1];
	newVec[2] = a[2] - b[2];
}