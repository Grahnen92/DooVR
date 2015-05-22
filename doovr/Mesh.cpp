#include "Mesh.h"
#include "time.h"
#include "math.h"
#include <algorithm>
#include <iterator>

using namespace std;
#define M_PI 3.14159265358979323846



Mesh::Mesh(float rad) {
	triangle tempT;
	vertex tempV;
	halfEdge* tempE1;
	halfEdge* tempE2;
	halfEdge* tempE3;

	float tempP1[3]; float tempP2[3]; float tempVec[3];
	int tempSize = 0;

	vertexArray.reserve(1000000);
	indexArray.reserve(1000000);

	vertexEPtr.reserve(1000000);
	triEPtr.reserve(1000000);
	vertexEPtr.resize(6);
	triEPtr.resize(8);
	position[0] = 0.0f;
	position[1] = -0.75f;
	position[2] = -0.75f;

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

	triEPtr[0]->nextEdge = new halfEdge; triEPtr[0]->nextEdge->vertex = 3; triEPtr[0]->nextEdge->triangle = 0;
	triEPtr[0]->nextEdge->nextEdge = new halfEdge; triEPtr[0]->nextEdge->nextEdge->vertex = 5; triEPtr[0]->nextEdge->nextEdge->triangle = 0;
	triEPtr[0]->nextEdge->nextEdge->nextEdge = triEPtr[0];

	vertexEPtr[0] = triEPtr[0]->nextEdge->nextEdge;

	//second tri
	tempE1 = new halfEdge;	tempE1->vertex = 0; tempE1->triangle = 1;
	triEPtr[1] = tempE1;
	
	triEPtr[1]->nextEdge = new halfEdge; triEPtr[1]->nextEdge->vertex = 5; triEPtr[1]->nextEdge->triangle = 1;
	triEPtr[1]->nextEdge->nextEdge = new halfEdge; triEPtr[1]->nextEdge->nextEdge->vertex = 2; triEPtr[1]->nextEdge->nextEdge->triangle = 1;
	triEPtr[1]->nextEdge->nextEdge->nextEdge = triEPtr[1];

	vertexEPtr[5] = triEPtr[1];

	//third tri
	tempE1 = new halfEdge;	tempE1->vertex = 0; tempE1->triangle = 2;
	triEPtr[2] = tempE1;

	triEPtr[2]->nextEdge = new halfEdge; triEPtr[2]->nextEdge->vertex = 2; triEPtr[2]->nextEdge->triangle = 2;
	triEPtr[2]->nextEdge->nextEdge = new halfEdge; triEPtr[2]->nextEdge->nextEdge->vertex = 4; triEPtr[2]->nextEdge->nextEdge->triangle = 2;
	triEPtr[2]->nextEdge->nextEdge->nextEdge = triEPtr[2];

	vertexEPtr[2] = triEPtr[2];

	//fourth tri
	tempE1 = new halfEdge;	tempE1->vertex = 0; tempE1->triangle = 3;
	triEPtr[3] = tempE1;

	triEPtr[3]->nextEdge = new halfEdge; triEPtr[3]->nextEdge->vertex = 4; triEPtr[3]->nextEdge->triangle = 3;
	triEPtr[3]->nextEdge->nextEdge = new halfEdge; triEPtr[3]->nextEdge->nextEdge->vertex = 3; triEPtr[3]->nextEdge->nextEdge->triangle = 3;
	triEPtr[3]->nextEdge->nextEdge->nextEdge = triEPtr[3];

	vertexEPtr[4] = triEPtr[3];

	//BOTTOM
	//fifth tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 4;
	triEPtr[4] = tempE1;

	triEPtr[4]->nextEdge = new halfEdge; triEPtr[4]->nextEdge->vertex = 5; triEPtr[4]->nextEdge->triangle = 4;
	triEPtr[4]->nextEdge->nextEdge = new halfEdge; triEPtr[4]->nextEdge->nextEdge->vertex = 3; triEPtr[4]->nextEdge->nextEdge->triangle = 4;
	triEPtr[4]->nextEdge->nextEdge->nextEdge = triEPtr[4];

	vertexEPtr[1] = triEPtr[4]->nextEdge->nextEdge;

	//sixth tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 5;
	triEPtr[5] = tempE1;
	
	triEPtr[5]->nextEdge = new halfEdge; triEPtr[5]->nextEdge->vertex = 2; triEPtr[5]->nextEdge->triangle = 5;
	triEPtr[5]->nextEdge->nextEdge = new halfEdge; triEPtr[5]->nextEdge->nextEdge->vertex = 5; triEPtr[5]->nextEdge->nextEdge->triangle = 5;
	triEPtr[5]->nextEdge->nextEdge->nextEdge = triEPtr[5];

	//seventh tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 6;
	triEPtr[6] = tempE1;
	
	triEPtr[6]->nextEdge = new halfEdge; triEPtr[6]->nextEdge->vertex = 4; triEPtr[6]->nextEdge->triangle = 6;
	triEPtr[6]->nextEdge->nextEdge = new halfEdge; triEPtr[6]->nextEdge->nextEdge->vertex = 2; triEPtr[6]->nextEdge->nextEdge->triangle = 6;
	triEPtr[6]->nextEdge->nextEdge->nextEdge = triEPtr[6];

	//seventh tri
	tempE1 = new halfEdge;	tempE1->vertex = 1; tempE1->triangle = 7;
	triEPtr[7] = tempE1;
	
	triEPtr[7]->nextEdge = new halfEdge; triEPtr[7]->nextEdge->vertex = 3; triEPtr[7]->nextEdge->triangle = 7;
	triEPtr[7]->nextEdge->nextEdge = new halfEdge; triEPtr[7]->nextEdge->nextEdge->vertex = 4; triEPtr[7]->nextEdge->nextEdge->triangle = 7;
	triEPtr[7]->nextEdge->nextEdge->nextEdge = triEPtr[7];

	vertexEPtr[3] = triEPtr[7];

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
	/*
	// create sphere by subdivision
	for (int i = 0; i < 1; i++) {
		//tempSize = vertexArray.size();
		for (int j = 0; j < vertexArray.size(); j++) {
			tempE1 = vertexEPtr[j];

			tempP1[0] = vertexArray[j].x;
			tempP1[1] = vertexArray[j].y;
			tempP1[2] = vertexArray[j].z;

			tempP2[0] = vertexArray[tempE1->vertex].x;
			tempP2[1] = vertexArray[tempE1->vertex].y;
			tempP2[2] = vertexArray[tempE1->vertex].z;

			linAlg::calculateVec(tempVec, tempP2, tempP1);
			if (vecLength(tempVec) > MAX_LENGTH) {
				edgeSubdivide(tempP1, tempVec, tempE1);
			}

			tempE1 = tempE1->nextEdge->sibling;
			while (tempE1 != vertexEPtr[j]) {
				tempP1[0] = vertexArray[tempE1->sibling->vertex].x;
				tempP1[1] = vertexArray[tempE1->sibling->vertex].y;
				tempP1[2] = vertexArray[tempE1->sibling->vertex].z;

				tempP2[0] = vertexArray[tempE1->vertex].x;
				tempP2[1] = vertexArray[tempE1->vertex].y;
				tempP2[2] = vertexArray[tempE1->vertex].z;

				linAlg::calculateVec(tempVec, tempP2, tempP1);

				if (vecLength(tempVec) > MAX_LENGTH) {
					edgeSubdivide(tempP1, tempVec, tempE1);
				}

				tempE1 = tempE1->nextEdge->sibling;
			}
		}
	}
	*/
	
	//////
	for (int i = 0; i < 10; i++)
	{
		tempSize = vertexArray.size();
		for (int j = 0; j < tempSize; j++)
		{
			tempE1 = vertexEPtr[j];

			tempP1[0] = vertexArray[j].x;
			tempP1[1] = vertexArray[j].y;
			tempP1[2] = vertexArray[j].z;

			tempP2[0] = vertexArray[tempE1->vertex].x;
			tempP2[1] = vertexArray[tempE1->vertex].y;
			tempP2[2] = vertexArray[tempE1->vertex].z;

			linAlg::calculateVec(tempVec, tempP2, tempP1);

			if (!(i % 2))
			{
				if (!tempE1->needsUpdate)
				{
					if (linAlg::vecLength(tempVec) > MAX_LENGTH)
						edgeSubdivide(tempP1, tempVec, tempE1);
					
					tempE1->needsUpdate = true;
					tempE1->sibling->needsUpdate = true;
					triEPtr[triEPtr.size() - 1]->needsUpdate = true;
					triEPtr[triEPtr.size() - 1]->sibling->needsUpdate = true;

				}
			}
			else
			{
				if (tempE1->needsUpdate)
				{
					if (linAlg::vecLength(tempVec) > MAX_LENGTH)
						edgeSubdivide(tempP1, tempVec, tempE1);

					tempE1->needsUpdate = false;
					tempE1->sibling->needsUpdate = false;
				}
			}

			tempE1 = tempE1->nextEdge->sibling;
			while (tempE1 != vertexEPtr[j])
			{

				tempP1[0] = vertexArray[tempE1->sibling->vertex].x;
				tempP1[1] = vertexArray[tempE1->sibling->vertex].y;
				tempP1[2] = vertexArray[tempE1->sibling->vertex].z;

				tempP2[0] = vertexArray[tempE1->vertex].x;
				tempP2[1] = vertexArray[tempE1->vertex].y;
				tempP2[2] = vertexArray[tempE1->vertex].z;

				linAlg::calculateVec(tempVec, tempP2, tempP1);

				if (!(i % 2))
				{
					if (!tempE1->needsUpdate)
					{
						if (linAlg::vecLength(tempVec) > MAX_LENGTH)
							edgeSubdivide(tempP1, tempVec, tempE1);
						tempE1->needsUpdate = true;
						tempE1->sibling->needsUpdate = true;
						triEPtr[triEPtr.size() - 1]->needsUpdate = true;
						triEPtr[triEPtr.size() - 1]->sibling->needsUpdate = true;
					}
				}
				else
				{
					if (tempE1->needsUpdate)
					{
						if (linAlg::vecLength(tempVec) > MAX_LENGTH)
							edgeSubdivide(tempP1, tempVec, tempE1);
						tempE1->needsUpdate = false;
						tempE1->sibling->needsUpdate = false;
					}
				}
				tempE1 = tempE1->nextEdge->sibling;
			}
		}
	}
	
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
	halfEdge* tempEdge;

	bool success = false;

	int startRow = -1;
	int endRow = -1;
	int prevRow = -1;
	vector<int> startCol;	// first edited column on row
	vector<int> endCol;		// last edited column on row

	//MOVEMENT BETWEEN LAST FRAME AND THIS FRAME
	float mLength = 0.0f;
	float pMove[3];
	float normal[4];
	pMove[0] = (p[0] - lp[0]);
	pMove[1] = (p[1] - lp[1]);
	pMove[2] = (p[2] - lp[2]);
	mLength = linAlg::vecLength(pMove);

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
		
		if (linAlg::vecLength(tempVec1) < rad) {

			//normVec(tempVec1);

			vertexArray[i].x -= vertexArray[i].nx * 0.005f;
			vertexArray[i].y -= vertexArray[i].ny * 0.005f;
			vertexArray[i].z -= vertexArray[i].nz * 0.005f;
			changedVertices.push_back(i);

			// mark the vertex edges as needUpdate
			vertexEPtr[i]->needsUpdate = true;
			tempEdge = vertexEPtr[i]->nextEdge->sibling;
			while (tempEdge != vertexEPtr[i]) {
				tempEdge->needsUpdate = true;
				tempEdge = tempEdge->nextEdge->sibling;
			}

			changeCount++;

			success = true;
		}
	}

	changeCount = 0;
	if (changedVertices.size() > 0)
		updateArea(&changedVertices[0], changedVertices.size());

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


void Mesh::updateArea(int* changeList, int listSize) {

	static float vPoint1[3], vPoint2[3], vPoint3[3], vPoint4[3];
	static float tempVec1[3], tempVec2[3], tempVec3[3];
	static float tempNorm1[3] = { 0.0f, 0.0f, 0.0f };
	static float tempNorm2[3] = { 0.0f, 0.0f, 0.0f };
	halfEdge* tempEdge;
	int vert1, vert2; 
	static float edgeLength;

	for (int i = 0; i < listSize; i++) {

		
		vPoint1[0] = vertexArray[changeList[i]].x;
		vPoint1[1] = vertexArray[changeList[i]].y;
		vPoint1[2] = vertexArray[changeList[i]].z;

		 // Retriangulation //////////////////////////////////////////////////////////////////////////////////////////
		 // check if edge needs update
		if (vertexEPtr[changeList[i]] != nullptr)
			tempEdge = vertexEPtr[changeList[i]];
		else
			continue;

		 do {
			 if (tempEdge->needsUpdate == true){
				tempEdge->needsUpdate = false;
				tempEdge->sibling->needsUpdate = false;

				// calculate edge lenght
				vert1 = tempEdge->vertex;

				vPoint2[0] = vertexArray[vert1].x;
				vPoint2[1] = vertexArray[vert1].y;
				vPoint2[2] = vertexArray[vert1].z;
				 
				linAlg::calculateVec(tempVec1, vPoint2, vPoint1);
				edgeLength = linAlg::vecLength(tempVec1);

				// check if edge is to long/short
				if (edgeLength < MIN_LENGTH) {
					edgeSplit(vPoint1, tempVec1, tempEdge);
					tempEdge = tempEdge->sibling->nextEdge->nextEdge;
					//edge already incremented, something needs to be done.
				} else if (edgeLength > MAX_LENGTH) {
					edgeSplit(vPoint1, tempVec1, tempEdge);
				}

			 }
			
			tempEdge = tempEdge->nextEdge->sibling;

		 } while (tempEdge != vertexEPtr[changeList[i]]);

		 // Update normal /////////////////////////////////////////////////////////////////////////////
		 tempEdge = vertexEPtr[changeList[i]];
		 // loop through the rest of the edges
		 do {
			 vert1 = tempEdge->vertex;
			 vert2 = tempEdge->nextEdge->nextEdge->vertex;

			 vPoint2[0] = vertexArray[vert1].x;
			 vPoint2[1] = vertexArray[vert1].y;
			 vPoint2[2] = vertexArray[vert1].z;

			 vPoint3[0] = vertexArray[vert2].x;
			 vPoint3[1] = vertexArray[vert2].y;
			 vPoint3[2] = vertexArray[vert2].z;

			 linAlg::calculateVec(tempVec1, vPoint2, vPoint1);
			 linAlg::calculateVec(tempVec2, vPoint3, vPoint1);

			 linAlg::crossProd(tempNorm1, tempVec2, tempVec1);

			 linAlg::normVec(tempNorm1);

			 tempNorm2[0] += tempNorm1[0];
			 tempNorm2[1] += tempNorm1[1];
			 tempNorm2[2] += tempNorm1[2];


			 tempEdge = tempEdge->nextEdge->sibling;
		 } while (tempEdge != vertexEPtr[changeList[i]]);

		 edgeLength = linAlg::vecLength(tempNorm2);

		 tempNorm2[0] = tempNorm2[0] / edgeLength;
		 tempNorm2[1] = tempNorm2[1] / edgeLength;
		 tempNorm2[2] = tempNorm2[2] / edgeLength;

		 linAlg::normVec(tempNorm2);

		 vertexArray[changeList[i]].nx = tempNorm2[0];
		 vertexArray[changeList[i]].ny = tempNorm2[1];
		 vertexArray[changeList[i]].nz = tempNorm2[2];
	}
}

void Mesh::edgeSplit(float* vPoint, float* vec, halfEdge* &edge) {

	vertex tempV;
	triangle tempT;
	halfEdge* tempE;
	static int vert1;
	static int vert2;
	static float temp[3];
	static float temp2[3];
	static float temp3[3];
	static float tempNorm1[3]; static float tempNorm2[3];
	static float tempVec1[3]; static float tempVec2[3];

	halfEdge* tempE2;
	
	vert1 = edge->nextEdge->nextEdge->vertex;
	vert2 = edge->sibling->nextEdge->nextEdge->vertex;

	temp[0] = vertexArray[vert1].x;
	temp[1] = vertexArray[vert1].y;
	temp[2] = vertexArray[vert1].z;

	temp2[0] = vertexArray[vert2].x;
	temp2[1] = vertexArray[vert2].y;
	temp2[2] = vertexArray[vert2].z;
	linAlg::calculateVec(temp3, temp, temp2);
	
	/*if (vecLength(temp3) < MAX_LENGTH) {
		for (int i = 0; i < 3; i++) {
			if (indexArray[edge->triangle].index[i] == edge->vertex)
				indexArray[edge->triangle].index[i] = vert2;

			if (indexArray[edge->sibling->triangle].index[i] == edge->sibling->vertex)
				indexArray[edge->sibling->triangle].index[i] = vert1;
		}
		// rebind triangles
		edge->sibling->nextEdge->nextEdge->triangle = edge->triangle;
		edge->nextEdge->nextEdge->triangle = edge->sibling->triangle;
		////
		edge->sibling->nextEdge->nextEdge->nextEdge = edge->nextEdge;
		edge->nextEdge->nextEdge->nextEdge = edge->sibling->nextEdge;
		////
		
		tempE = edge->nextEdge->nextEdge;
		edge->nextEdge->nextEdge = edge;

		tempE2 = edge->sibling->nextEdge->nextEdge;
		edge->sibling->nextEdge->nextEdge = edge->sibling;

		edge->sibling->nextEdge = tempE;
		edge->nextEdge = tempE2;

		edge->vertex = edge->sibling->nextEdge->vertex;
		edge->sibling->vertex = edge->nextEdge->vertex;

		vertexEPtr[edge->nextEdge->nextEdge->vertex] = edge->nextEdge;
		vertexEPtr[edge->sibling->nextEdge->nextEdge->vertex] = edge->sibling->nextEdge;

		//pass on
		edge = edge->nextEdge;

	}
	else
	{*/
	
		// create new vertex point
		tempV.x = vPoint[0] + (vec[0] / 2.0f);
		tempV.y = vPoint[1] + (vec[1] / 2.0f);
		tempV.z = vPoint[2] + (vec[2] / 2.0f);
		
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

		triEPtr.push_back(new halfEdge);
		vert1 = triEPtr.size() - 1;
		vertexEPtr.push_back(triEPtr[vert1]);

		triEPtr[vert1]->vertex = edge->vertex;
		triEPtr[vert1]->triangle = vert1;
		triEPtr[vert1]->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->vertex = vertexArray.size() - 1;
		triEPtr[vert1]->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->sibling = edge->nextEdge->nextEdge;
		triEPtr[vert1]->nextEdge->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->nextEdge->vertex = edge->nextEdge->nextEdge->vertex;
		triEPtr[vert1]->nextEdge->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->nextEdge->nextEdge = triEPtr[vert1];
		triEPtr[vert1]->nextEdge->nextEdge->sibling = edge->nextEdge->nextEdge->sibling;
		//rebind sibling of existing triangle
		edge->nextEdge->nextEdge->sibling->sibling = triEPtr[vert1]->nextEdge->nextEdge;
		//rebind sibling of old triangle
		edge->nextEdge->nextEdge->sibling = triEPtr[vert1]->nextEdge;

		triEPtr.push_back(new halfEdge);
		vert1 = triEPtr.size() - 1;

		triEPtr[vert1]->sibling = triEPtr[vert1 - 1];
		//bind sibling of first newEdge
		triEPtr[vert1 - 1]->sibling = triEPtr[vert1];
		//continue
		triEPtr[vert1]->vertex = vertexArray.size() - 1;
		triEPtr[vert1]->triangle = vert1;
		triEPtr[vert1]->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->vertex = edge->vertex;
		triEPtr[vert1]->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->sibling = edge->sibling->nextEdge->sibling;
		//rebind sibling of existing triangle
		edge->sibling->nextEdge->sibling->sibling = triEPtr[vert1]->nextEdge;
		triEPtr[vert1]->nextEdge->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->nextEdge->vertex = edge->sibling->nextEdge->nextEdge->vertex;
		triEPtr[vert1]->nextEdge->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->nextEdge->sibling = edge->sibling->nextEdge; // =======
		//rebind sibling of old triangle
		edge->sibling->nextEdge->sibling = triEPtr[vert1]->nextEdge->nextEdge;
		triEPtr[vert1]->nextEdge->nextEdge->nextEdge = triEPtr[vert1];


		// rebind old edge vertex
		vertexEPtr[edge->vertex] = triEPtr[vert1];

		edge->vertex = vertexArray.size() - 1;
		edge->sibling->nextEdge->vertex = vertexArray.size() - 1;
	//}

	// Update normal /////////////////////////////////////////////////////////////////////////////
	tempE = vertexEPtr[vertexEPtr.size() - 1];
	temp[0] = vertexArray[tempE->sibling->vertex].x;
	temp[1] = vertexArray[tempE->sibling->vertex].y;
	temp[2] = vertexArray[tempE->sibling->vertex].z;
	// loop through the edges
	do {
		vert1 = tempE->vertex;
		vert2 = tempE->nextEdge->nextEdge->vertex;

		temp2[0] = vertexArray[vert1].x;
		temp2[1] = vertexArray[vert1].y;
		temp2[2] = vertexArray[vert1].z;

		temp3[0] = vertexArray[vert2].x;
		temp3[1] = vertexArray[vert2].y;
		temp3[2] = vertexArray[vert2].z;

		linAlg::calculateVec(tempVec1, temp2, temp);
		linAlg::calculateVec(tempVec2, temp3, temp);

		linAlg::crossProd(tempNorm1, tempVec2, tempVec1);

		linAlg::normVec(tempNorm1);

		tempNorm2[0] += tempNorm1[0];
		tempNorm2[1] += tempNorm1[1];
		tempNorm2[2] += tempNorm1[2];
		

		tempE = tempE->nextEdge->sibling;
	} while (tempE != vertexEPtr[vertexEPtr.size() - 1]);

	static float vecLenght = linAlg::vecLength(tempNorm2);
	tempNorm2[0] = tempNorm2[0] / vecLenght;
	tempNorm2[1] = tempNorm2[1] / vecLenght;
	tempNorm2[2] = tempNorm2[2] / vecLenght;

	linAlg::normVec(tempNorm2);
	vertexArray[vertexEPtr.size() - 1].nx = tempNorm2[0];
	vertexArray[vertexEPtr.size() - 1].ny = tempNorm2[1];
	vertexArray[vertexEPtr.size() - 1].nz = tempNorm2[2];

}

void Mesh::edgeCollapse(float* vPoint, float* vec, halfEdge* &edge) {
	
	halfEdge* tempE;
	static int currVert; 
	static int nVert;
	currVert = edge->sibling->vertex;
	nVert = edge->vertex;

	// move currVert
	vertexArray[currVert].x = vPoint[0] + (vec[0] / 2.0f);
	vertexArray[currVert].y = vPoint[1] + (vec[1] / 2.0f);
	vertexArray[currVert].z = vPoint[2] + (vec[2] / 2.0f);

	// rebind edges that point to nVert
	tempE = edge->nextEdge->nextEdge->sibling;
	while (tempE != edge->sibling->nextEdge)
	{
		tempE->vertex = currVert;

		// rebind the triangle containing nVert as index
		for (int i = 0; i < 3; i++) {
			if (indexArray[tempE->triangle].index[i] == nVert) {
				indexArray[tempE->triangle].index[i] = currVert;
				break;
			}
		}
		tempE = tempE->nextEdge->nextEdge->sibling;
		cout << "hej";
	}
	tempE = edge->nextEdge->sibling;

	// rebind edges
	edge->nextEdge->sibling->sibling = edge->nextEdge->nextEdge->sibling;
	edge->nextEdge->nextEdge->sibling->sibling = edge->nextEdge->sibling;

	edge->sibling->nextEdge->sibling->sibling = edge->sibling->nextEdge->nextEdge->sibling;
	edge->sibling->nextEdge->nextEdge->sibling->sibling = edge->sibling->nextEdge->sibling;

	// rebind vertex pointer
	vertexEPtr[currVert] = edge->nextEdge->sibling;

	//reset the removed triangles
	indexArray[edge->triangle].index[0] = 0;
	indexArray[edge->triangle].index[1] = 0;
	indexArray[edge->triangle].index[2] = 0;
	indexArray[edge->sibling->triangle].index[0] = 0;
	indexArray[edge->sibling->triangle].index[1] = 0;
	indexArray[edge->sibling->triangle].index[2] = 0;
	
	// reset the removed vertex
	vertexArray[nVert].x = -1000;
	vertexArray[nVert].y = -1000;
	vertexArray[nVert].z = -1000;
	vertexArray[nVert].nx = 0;
	vertexArray[nVert].ny = 0;
	vertexArray[nVert].nz = 0;

	// reset edge pointers
	vertexEPtr[nVert] = nullptr;
	triEPtr[edge->triangle] = nullptr;
	triEPtr[edge->sibling->triangle] = nullptr;

	// delete the removed edges
	delete edge->sibling->nextEdge->nextEdge;
	delete edge->sibling->nextEdge;
	delete edge->sibling;
	delete edge->nextEdge->nextEdge;
	delete edge->nextEdge;
	delete edge;

	// move edge to so that it points to an existing edge
	edge = tempE;
}


void Mesh::edgeSubdivide(float* pA, float* vecA2B, halfEdge* &edge) {

	vertex tempV;
	triangle tempT;
	halfEdge* tempE;
	int vert1;
	int vert2;
	float temp[3];
	float temp2[3];
	float temp3[3];

	halfEdge* tempE2;

	vert1 = edge->nextEdge->nextEdge->vertex;
	vert2 = edge->sibling->nextEdge->nextEdge->vertex;

	temp[0] = vertexArray[vert1].x;
	temp[1] = vertexArray[vert1].y;
	temp[2] = vertexArray[vert1].z;

	temp2[0] = vertexArray[vert2].x;
	temp2[1] = vertexArray[vert2].y;
	temp2[2] = vertexArray[vert2].z;
	linAlg::calculateVec(temp3, temp, temp2);
	
	if (linAlg::vecLength(temp3) < MAX_LENGTH) {
		// flip edges
		for (int i = 0; i < 3; i++) {
			if (indexArray[edge->triangle].index[i] == edge->vertex)
				indexArray[edge->triangle].index[i] = vert2;

			if (indexArray[edge->sibling->triangle].index[i] == edge->sibling->vertex)
				indexArray[edge->sibling->triangle].index[i] = vert1;
		}
		// rebind triangles
		edge->sibling->nextEdge->nextEdge->triangle = edge->triangle;
		edge->nextEdge->nextEdge->triangle = edge->sibling->triangle;
		////
		edge->sibling->nextEdge->nextEdge->nextEdge = edge->nextEdge;
		edge->nextEdge->nextEdge->nextEdge = edge->sibling->nextEdge;
		////

		tempE = edge->nextEdge->nextEdge;
		edge->nextEdge->nextEdge = edge;

		tempE2 = edge->sibling->nextEdge->nextEdge;
		edge->sibling->nextEdge->nextEdge = edge->sibling;

		edge->sibling->nextEdge = tempE;
		edge->nextEdge = tempE2;

		edge->vertex = edge->sibling->nextEdge->vertex;
		edge->sibling->vertex = edge->nextEdge->vertex;

		vertexEPtr[edge->nextEdge->nextEdge->vertex] = edge->nextEdge;
		vertexEPtr[edge->sibling->nextEdge->nextEdge->vertex] = edge->sibling->nextEdge;

		//pass on
		edge = edge->nextEdge;
	}
	else {

		temp[0] = pA[0] + (vecA2B[0] / 2.0f);
		temp[1] = pA[1] + (vecA2B[1] / 2.0f);
		temp[2] = pA[2] + (vecA2B[2] / 2.0f);

		linAlg::normVec(temp);
		tempV.nx = temp[0];
		tempV.ny = temp[1];
		tempV.nz = temp[2];

		temp[0] = 0.5f*temp[0];
		temp[1] = 0.5f*temp[1];
		temp[2] = 0.5f*temp[2];

		tempV.x = temp[0];
		tempV.y = temp[1];
		tempV.z = temp[2];
		/*
		// create new vertex point
		tempV.x = pA[0] + (vecA2B[0] / 2.0f);
		tempV.y = pA[1] + (vecA2B[1] / 2.0f);
		tempV.z = pA[2] + (vecA2B[2] / 2.0f);
		*/
		//tempV.nx = vertexArray[edge->vertex].nx; tempV.ny = vertexArray[edge->vertex].ny; tempV.nz = vertexArray[edge->vertex].nz;
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

		triEPtr.push_back(new halfEdge);
		vert1 = triEPtr.size() - 1;
		vertexEPtr.push_back(triEPtr[vert1]);

		triEPtr[vert1]->vertex = edge->vertex;
		triEPtr[vert1]->triangle = vert1;
		triEPtr[vert1]->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->vertex = vertexArray.size() - 1;
		triEPtr[vert1]->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->sibling = edge->nextEdge->nextEdge;
		triEPtr[vert1]->nextEdge->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->nextEdge->vertex = edge->nextEdge->nextEdge->vertex;
		triEPtr[vert1]->nextEdge->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->nextEdge->nextEdge = triEPtr[vert1];
		triEPtr[vert1]->nextEdge->nextEdge->sibling = edge->nextEdge->nextEdge->sibling;
		//rebind sibling of existing triangle
		edge->nextEdge->nextEdge->sibling->sibling = triEPtr[vert1]->nextEdge->nextEdge;
		//rebind sibling of old triangle
		edge->nextEdge->nextEdge->sibling = triEPtr[vert1]->nextEdge;

		triEPtr.push_back(new halfEdge);
		vert1 = triEPtr.size() - 1;

		triEPtr[vert1]->sibling = triEPtr[vert1 - 1];
		//bind sibling of first newEdge
		triEPtr[vert1 - 1]->sibling = triEPtr[vert1];
		//continue
		triEPtr[vert1]->vertex = vertexArray.size() - 1;
		triEPtr[vert1]->triangle = vert1;
		triEPtr[vert1]->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->vertex = edge->vertex;
		triEPtr[vert1]->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->sibling = edge->sibling->nextEdge->sibling;
		//rebind sibling of existing triangle
		edge->sibling->nextEdge->sibling->sibling = triEPtr[vert1]->nextEdge;
		triEPtr[vert1]->nextEdge->nextEdge = new halfEdge;

		triEPtr[vert1]->nextEdge->nextEdge->vertex = edge->sibling->nextEdge->nextEdge->vertex;
		triEPtr[vert1]->nextEdge->nextEdge->triangle = vert1;
		triEPtr[vert1]->nextEdge->nextEdge->sibling = edge->sibling->nextEdge;
		//rebind sibling of old triangle
		edge->sibling->nextEdge->sibling = triEPtr[vert1]->nextEdge->nextEdge;
		triEPtr[vert1]->nextEdge->nextEdge->nextEdge = triEPtr[vert1];

		// rebind old edge vertex
		vertexEPtr[edge->vertex] = triEPtr[vert1];

		edge->vertex = vertexArray.size() - 1;
		edge->sibling->nextEdge->vertex = vertexArray.size() - 1;
	}
	
}

