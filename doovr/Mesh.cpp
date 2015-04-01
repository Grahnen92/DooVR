#include "Mesh.h"
#include "time.h"
#include "math.h"
#include <algorithm>
#include <iterator>

using namespace std;

void normVec(float* vec) {
	float lenght = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	vec[0] = vec[0] / lenght;
	vec[1] = vec[1] / lenght;
	vec[2] = vec[2] / lenght;
}

float* crossProd(float* vec1, float* vec2) {
	float newVertex[3];
	newVertex[0] = (vec1[1] * vec2[2] - vec1[2] * vec2[1]);
	newVertex[1] = -(vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	newVertex[2] = (vec1[0] * vec2[1] - vec1[1] * vec2[0]);

	return newVertex;
}

Mesh::Mesh() {
	triangle tempT;
	vertex tempV;

	tempV.y = 0.0f;

	vertexArray.reserve(100000);
	indexArray.reserve(100000);

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




	triangle * indexP;
	vertex * vertexP;

	rows = 100;
	cols = 100;

	float scaleF = 0.0f;

	scaleF = 1.0f / (rows / 4);

	
	// Place vertices
	for (int i = -rows / 2; i < rows / 2; i++) {
		cout << fmod(i, sqrt(0.75f) * 2) << endl;

		for (int j = -cols / 2; j < cols / 2; j++) {
			
			if (fmod(i, 2) != 0){
				tempV.x = ((float)(j) + 0.5f)*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			} else {
				tempV.x = ((float)(j))*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			}
			tempV.nx = 0.0f;
			tempV.ny = -1.0f;
			tempV.nz = 0.0f;
			tempV.adjacentFace = nullptr;
			vertexArray.push_back(tempV);
		}
	}
	
	face* handledFace1 = nullptr;
	face* handledFace2 = nullptr;
	face* handledFace3 = nullptr;
	face* handledFace4 = nullptr;
	face* previousFace = nullptr;

	// set triangle indecies and bind faces
	for (int i = 1; i < rows-2; i = i + 2) {
		for (int j = 0; j < cols-1; j++) {
			//CREATE FIRST TRIANGLE IN SEQUENCE
			tempT.index1 = i * rows + j;
			tempT.index2 = (i + 1) * rows + (j + 1);
			tempT.index3 = (i + 1) * rows + j;
			indexArray.push_back(tempT);
			handledFace1  = new face;
			handledFace1->vertices[0] = &vertexArray[i * rows + j];
			handledFace1->vertices[1] = &vertexArray[(i + 1) * rows + (j + 1)];
			handledFace1->vertices[2] = &vertexArray[(i + 1) * rows + j];

			//CREATE SECOND TRIANGLE IN SEQUENCE
			tempT.index1 = i * rows + j;
			tempT.index2 = i * rows + j + 1;
			tempT.index3 = (i + 1) * rows + (j + 1);
			indexArray.push_back(tempT);
			handledFace2  = new face;
			handledFace2->vertices[0] = &vertexArray[i * rows + j];
			handledFace2->vertices[1] = &vertexArray[i * rows + j + 1];
			handledFace2->vertices[2] = &vertexArray[(i + 1) * rows + (j + 1)];

			//CREATE THIRD TRIANGLE IN SEQUENCE
			tempT.index1 = i * rows + j;
			tempT.index2 = (i - 1) * rows + (j + 1);
			tempT.index3 = i * rows + (j + 1);
			indexArray.push_back(tempT);
			handledFace3  = new face;
			handledFace3->vertices[0] = &vertexArray[i * rows + j];
			handledFace3->vertices[1] = &vertexArray[(i - 1) * rows + (j + 1)];
			handledFace3->vertices[2] = &vertexArray[i * rows + (j + 1)];

			//CREATE FOURTH TRIANGLE IN SEQUENCE
			tempT.index1 = i * rows + j;
			tempT.index2 = (i - 1) * rows + j;
			tempT.index3 = (i - 1) * rows + (j + 1);
			indexArray.push_back(tempT);
			handledFace4  = new face;
			handledFace4->vertices[0] = &vertexArray[i * rows + j];
			handledFace4->vertices[1] = &vertexArray[(i - 1) * rows + j];
			handledFace4->vertices[2] = &vertexArray[(i - 1) * rows + (j + 1)];

			//INTERNAL FACE BINDINGS IN TRIANGLE SEQUENCE
			handledFace1->nFace[0] = handledFace2;

			handledFace2->nFace[0] = handledFace1;
			handledFace2->nFace[1] = handledFace3;

			handledFace3->nFace[0] = handledFace2;
			handledFace3->nFace[1] = handledFace4;

			handledFace4->nFace[0] = handledFace3;

			//FACE BINDINGS BETWEEN TRIANGLE SEQUENCES/////////////////////////////////////////////////////
			/*
			//FIRST TRIANGLE SEQUENCE IN MESH
			if (i == 1 && j == 0 ) {
				vertexArray[(i + 1) * rows + j].adjacentFace = handledFace1;
				vertexArray[i * rows + j].adjacentFace = handledFace2;
				vertexArray[i* rows + (j + 1)].adjacentFace = handledFace3;
				vertexArray[(i - 1)* rows + (j + 1)].adjacentFace = handledFace4;
				
			}
			//TRIANGLE SEQUENCE IN FIRST COLUMN OF MESH
			else if (j == 0 && i != 0) {
				vertexArray[(i + 1) * rows + j].adjacentFace = handledFace1;
				vertexArray[i * rows + j].adjacentFace = handledFace2;
				vertexArray[i* rows + (j + 1)].adjacentFace = handledFace3;

				previousFace = vertexArray[(i - 1)*rows + j].adjacentFace;
				handledFace4->nFace[1] = previousFace;
				previousFace->nFace[1] = handledFace4;
			}
			//TRIANGLE SEQUENCE IN FIRST ROW OF MESH
			else if ( i == 1 && j !=0) {
				vertexArray[(i + 1) * rows + j].adjacentFace = handledFace1;
				vertexArray[i * rows + (j + 1)].adjacentFace = handledFace3;
				vertexArray[(i - 1) * rows + (j + 1)].adjacentFace = handledFace4;

				previousFace = vertexArray[i * rows + j].adjacentFace->nFace[0];
				handledFace1->nFace[1] = previousFace;
				previousFace->nFace[2] = handledFace1;

				previousFace = vertexArray[i * rows + j].adjacentFace;
				handledFace4->nFace[1] = previousFace;
				previousFace->nFace[2] = handledFace4;
			}
			*/
			//TRIANGLE SEQUENCE WHEN NOT IN FIRST ROW AND NOT IN FIRST COLUMN
			//else {
				vertexArray[(i + 1) * rows + j + 1].adjacentFace = handledFace1;
				vertexArray[i * rows + (j + 1)].adjacentFace = handledFace3;

				
				if (i != 1 && j !=0)
				{

					previousFace = vertexArray[i * rows + j].adjacentFace->nFace[0];
					handledFace1->nFace[1] = previousFace;
					previousFace->nFace[2] = handledFace1;

					previousFace = vertexArray[i * rows + j].adjacentFace;
					handledFace4->nFace[1] = previousFace;
					previousFace->nFace[2] = handledFace4;

					previousFace = vertexArray[(i - 1) * rows + j + 1].adjacentFace;
					handledFace4->nFace[2] = previousFace;
					previousFace->nFace[2] = handledFace4;
				}
			//}
			/////////////////////////////////////////////////////////////////////////////////////
		}
	}

	vertexP = &vertexArray[0];
	indexP = &indexArray[0];
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
		 vertexArray.size()*sizeof(vertex), vertexP, GL_STREAM_DRAW);

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
						  6 * sizeof(GLfloat) + sizeof(face*), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
						  6 * sizeof(GLfloat) + sizeof(face*), (void*)(3 * sizeof(GLfloat))); // normals

	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex indices to OpenGL
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 3 * indexArray.size()*sizeof(GLuint), indexP, GL_STREAM_DRAW);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the buffers while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh(void) {

}

// function for testing buffer mapping, dilates

void Mesh::updateVertexArray(float* p, bool but) {
	vertex tempV;

	face* faceP;

	tempV.z = 0;
	vertex point;
	point.x = p[0] - position[0];
	point.y = p[1] - position[1];
	point.z = p[2] - position[2];

	glm::vec4 tempvec;

	tempvec = glm::transpose(glm::make_mat4(orientation)) * glm::vec4(point.x, point.y, point.z, 1.0f);


	point.x = tempvec.x;
	point.y = tempvec.y;
	point.z = tempvec.z;
	float rad = 0.4f;


	triangle * indexP;
	vertex * vertexP;

	bool success = false;	

	int startRow = -1;
	int endRow = -1;
	int prevRow = -1;
	vector<int> startCol;	// first edited column on row
	vector<int> endCol;		// last edited column on row

	for (int i = 0; i < vertexArray.size(); i++) {
		if (vectorLength(point, vertexArray[i]) < rad) {
			
			if (but == true)
				vertexArray[i].y += 0.001f;
			else
				vertexArray[i].y -= 0.001f;
			
			if ( ((i - (i % rows))/cols) % 2 != 0 ) {
				faceP = vertexArray[i].adjacentFace;
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);
				//cout << "hej";

				faceP = faceP->nFace[0];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);
				faceP = faceP->nFace[0];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);
				faceP = faceP->nFace[1];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);
				faceP = faceP->nFace[1];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);
			}
			else {
				faceP = vertexArray[i].adjacentFace;
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				//updateNormal(faceP);

				faceP = faceP->nFace[0];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
			//	updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
			//	updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
			//	updateNormal(faceP);

				faceP = faceP->nFace[1];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
			//	updateNormal(faceP);
			}
			
			success = true;

			if (startRow == -1) {
				startRow = (i - (i % rows)) / rows;
				endRow = startRow; // first element is also last element as yet
			} else {
				prevRow = endRow;
				endRow = (i - (i % rows)) / rows;
			}

			if (startCol.size() != 0 && endRow == prevRow) {		//  check if the last added column is on the same row, endRow will always be the current row
				endCol.pop_back();									//  if it is the same row it is the last element as yet, 20 elements on each row
				endCol.push_back(i - endRow * rows);
				//endCol.push_back(i % 20);
			} else {												// first element on row
				//startCol.push_back(i % 20);
				startCol.push_back(i - endRow * rows);
				//endCol.push_back(i % 20);
				endCol.push_back(i - endRow * rows);
			}
		}
	}
	
	if (success == true) {

		vertexP = &vertexArray[0];
		indexP = &indexArray[0];

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		int currentRow = startRow;
		int range = 0;
		int o = 0;
		int beginning = 0;
		// update the buffer where if has changed
		for (int j = 0; currentRow <= endRow && j < endCol.size() && j < startCol.size(); j++, currentRow++) {
			range = endCol[j] + 1 - startCol[j];
			beginning = currentRow * rows + startCol[j];

			// Present our vertex coordinates to OpenGL
			vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, beginning*sizeof(vertex), sizeof(vertex)*range,
												GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

			for (int i = beginning; i < range + beginning, o < range; i++, o++) {
				vertexP[o].x = vertexArray[i].x;
				vertexP[o].y = vertexArray[i].y;
				vertexP[o].z = vertexArray[i].z;
				vertexP[o].nx = vertexArray[i].nx;
				vertexP[o].ny = vertexArray[i].ny;
				vertexP[o].nz = vertexArray[i].nz;
				vertexP[o].adjacentFace = vertexArray[i].adjacentFace;
			}
			o = 0;
			glUnmapBuffer(GL_ARRAY_BUFFER);

		}

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
							  6 * sizeof(GLfloat) + sizeof(face*), (void*)0); // xyz coordinates
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
							  6 * sizeof(GLfloat) + sizeof(face*), (void*)(3 * sizeof(GLfloat))); // normals

		// Activate the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		// Present our vertex <indices to OpenGL
		indexP = (triangle*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangle) * indexArray.size(),
											 GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		for (int i = 0; i < indexArray.size(); i++) {
			indexP[i].index1 = indexArray[i].index1;
			indexP[i].index2 = indexArray[i].index2;
			indexP[i].index3 = indexArray[i].index3;
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

// Function for testing the facebased data structure
void Mesh::moveThroughMesh(int it) {

	triangle * indexP;
	vertex * vertexP;

	if (it < vertexArray.size()) {

		vertexArray[it].adjacentFace->vertices[0]->y += 0.1f;
		vertexArray[it].adjacentFace->vertices[1]->y += 0.1f;
		vertexArray[it].adjacentFace->vertices[2]->y += 0.1f;

		vertexArray[it].adjacentFace->nFace[0]->vertices[0]->y += 0.1f;
		vertexArray[it].adjacentFace->nFace[0]->vertices[1]->y += 0.1f;
		vertexArray[it].adjacentFace->nFace[0]->vertices[2]->y += 0.1f;

		vertexArray[it].adjacentFace->nFace[0]->nFace[1]->vertices[0]->y += 0.1f;
		vertexArray[it].adjacentFace->nFace[0]->nFace[1]->vertices[1]->y += 0.1f;
		vertexArray[it].adjacentFace->nFace[0]->nFace[1]->vertices[2]->y += 0.1f;
		 
		vertexArray[it].adjacentFace->nFace[0]->nFace[1]->nFace[1]->vertices[0]->y += 0.1f;
		vertexArray[it].adjacentFace->nFace[0]->nFace[1]->nFace[1]->vertices[1]->y += 0.1f;
		vertexArray[it].adjacentFace->nFace[0]->nFace[1]->nFace[1]->vertices[2]->y += 0.1f;
	}

	vertexP = &vertexArray[0];
	indexP = &indexArray[0];

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Present our vertex coordinates to OpenGL
	vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertex)*vertexArray.size(),
										GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

	for (int i = 0; i < vertexArray.size(); i++) {
		vertexP[i].x = vertexArray[i].x;
		vertexP[i].y = vertexArray[i].y;
		vertexP[i].z = vertexArray[i].z;
		vertexP[i].nx = vertexArray[i].nx;
		vertexP[i].ny = vertexArray[i].ny;
		vertexP[i].nz = vertexArray[i].nz;
		vertexP[i].adjacentFace = vertexArray[i].adjacentFace;
	}

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
						  6 * sizeof(GLfloat) + sizeof(face*), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
						  6 * sizeof(GLfloat) + sizeof(face*), (void*)(3 * sizeof(GLfloat))); // normals

	glUnmapBuffer(GL_ARRAY_BUFFER);

	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex <indices to OpenGL
	indexP = (triangle*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangle) * indexArray.size(),
										 GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

	for (int i = 0; i < indexArray.size(); i++) {
		indexP[i].index1 = indexArray[i].index1;
		indexP[i].index2 = indexArray[i].index2;
		indexP[i].index3 = indexArray[i].index3;
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the buffers while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::dilate(double x, double y) {
	vertex tempV;

	face* faceP;

	tempV.z = 0;
	vertex point;
	point.x = 0.0f;
	point.y = 0.0f;
	point.z = 0.0f;

	float rad = 0.5f;

	triangle * indexP;
	vertex * vertexP;

	bool success = false;

	int startRow = -1;
	int endRow = -1;
	int prevRow = -1;
	vector<int> startCol;	// first edited column on row
	vector<int> endCol;		// last edited column on row

	for (int i = 0; i < vertexArray.size(); i++) {
		if (vectorLength(point, vertexArray[i]) < rad) {

			vertexArray[i].x += 0.001f*vertexArray[i].nx;
			vertexArray[i].y += 0.001f*vertexArray[i].ny;
			vertexArray[i].z += 0.001f*vertexArray[i].nz;

			if (((i - (i % rows)) / cols) % 2 != 0) {
				faceP = vertexArray[i].adjacentFace;
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);
				//cout << "hej";

				faceP = faceP->nFace[0];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);
				faceP = faceP->nFace[0];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);
				faceP = faceP->nFace[1];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);
				faceP = faceP->nFace[1];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);
			} else {
				faceP = vertexArray[i].adjacentFace;
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);

				faceP = faceP->nFace[0];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);

				faceP = faceP->nFace[2];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);

				faceP = faceP->nFace[1];
				//faceP->vertices[0];
				//faceP->vertices[1];
				//faceP->vertices[2];
				updateNormal(faceP);
			}

			success = true;

			if (startRow == -1) {
				startRow = (i - (i % rows)) / rows;
				endRow = startRow; // first element is also last element as yet
			} else {
				prevRow = endRow;
				endRow = (i - (i % rows)) / rows;
			}

			if (startCol.size() != 0 && endRow == prevRow) {		//  check if the last added column is on the same row, endRow will always be the current row
				endCol.pop_back();									//  if it is the same row it is the last element as yet, 20 elements on each row
				endCol.push_back(i - endRow * rows);
				//endCol.push_back(i % 20);
			} else {												// first element on row
				//startCol.push_back(i % 20);
				startCol.push_back(i - endRow * rows);
				//endCol.push_back(i % 20);
				endCol.push_back(i - endRow * rows);
			}
		}
	}

	if (success == true) {

		vertexP = &vertexArray[0];
		indexP = &indexArray[0];

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		int currentRow = startRow;
		int range = 0;
		int o = 0;
		int beginning = 0;
		// update the buffer where if has changed
		for (int j = 0; currentRow <= endRow; j++, currentRow++) {
			range = endCol[j] + 1 - startCol[j];
			beginning = currentRow * rows + startCol[j];

			// Present our vertex coordinates to OpenGL
			vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, beginning*sizeof(vertex), sizeof(vertex)*range,
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

			for (int i = beginning; i < range + beginning, o < range; i++, o++) {
				vertexP[o].x = vertexArray[i].x;
				vertexP[o].y = vertexArray[i].y;
				vertexP[o].z = vertexArray[i].z;
				vertexP[o].nx = vertexArray[i].nx;
				vertexP[o].ny = vertexArray[i].ny;
				vertexP[o].nz = vertexArray[i].nz;
				vertexP[o].adjacentFace = vertexArray[i].adjacentFace;
			}
			o = 0;
			glUnmapBuffer(GL_ARRAY_BUFFER);

		}

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
							  6 * sizeof(GLfloat) + sizeof(face*), (void*)0); // xyz coordinates
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
							  6 * sizeof(GLfloat) + sizeof(face*), (void*)(3 * sizeof(GLfloat))); // normals

		// Activate the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		// Present our vertex <indices to OpenGL
		indexP = (triangle*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangle) * indexArray.size(),
											 GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

		for (int i = 0; i < indexArray.size(); i++) {
			indexP[i].index1 = indexArray[i].index1;
			indexP[i].index2 = indexArray[i].index2;
			indexP[i].index3 = indexArray[i].index3;
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

	glDrawElements(GL_TRIANGLES, 3 * indexArray.size() * sizeof(GLuint), GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}

//! Calculates the vector lenght
float Mesh::vectorLength(vertex vertex1, vertex vertex2) {
	vertex vector;

	vector.x = vertex1.x - vertex2.x;
	vector.y = vertex1.y - vertex2.y;
	vector.z = vertex1.z - vertex2.z;

	return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

//! Sorts vertecies by the x coordinate into ascending order
bool Mesh::sortByXCord(const vertex &a, const vertex &b) {
	return a.x < b.x;
}

void Mesh::updateNormal(face* faceP)
{
	
	float tempVert1[3];
	float tempVert2[3];
	float* tempNorm1;
	float tempNorm2[3];

	//tempVec1 = glm::vec3(faceP->vertices[1]->x - faceP->vertices[0]->x, faceP->vertices[1]->y - faceP->vertices[0]->y, faceP->vertices[1]->z - faceP->vertices[0]->z);
	//tempVec2 = glm::vec3(faceP->vertices[2]->x - faceP->vertices[0]->x, faceP->vertices[2]->y - faceP->vertices[0]->y, faceP->vertices[2]->z - faceP->vertices[0]->z);
	//tempNorm1 = glm::normalize(glm::cross(tempVec2, tempVec1));

	//tempNorm2 = glm::vec3(faceP->vertices[0]->nx, faceP->vertices[0]->ny, faceP->vertices[0]->nz);
	//tempNorm3 = glm::normalize((tempNorm1 + tempNorm2) / 2.0f);

	tempVert1[0] = faceP->vertices[1]->x - faceP->vertices[0]->x;
	tempVert1[1] = faceP->vertices[1]->y - faceP->vertices[0]->y;
	tempVert1[2] = faceP->vertices[1]->z - faceP->vertices[0]->z;

	tempVert2[0] = faceP->vertices[2]->x - faceP->vertices[0]->x;
	tempVert2[1] = faceP->vertices[2]->y - faceP->vertices[0]->y;
	tempVert2[2] = faceP->vertices[2]->z - faceP->vertices[0]->z;

	tempNorm1 = crossProd(tempVert1, tempVert2);

	normVec(tempNorm1);
	
	tempNorm2[0] = faceP->vertices[0]->nx;
	tempNorm2[1] = faceP->vertices[0]->ny;
	tempNorm2[2] = faceP->vertices[0]->nz;

	tempNorm1[0] = (tempNorm1[0] + tempNorm2[0]) / 2.0f;
	tempNorm1[1] = (tempNorm1[1] + tempNorm2[1]) / 2.0f;
	tempNorm1[2] = (tempNorm1[2] + tempNorm2[2]) / 2.0f;

	normVec(tempNorm1);

	faceP->vertices[0]->nx = tempNorm1[0];
	faceP->vertices[0]->ny = tempNorm1[1];
	faceP->vertices[0]->nz = tempNorm1[2];
	/////////////////////////////////////////////////////////////////////////////////////////////////

	tempNorm2[0] = faceP->vertices[1]->nx;
	tempNorm2[1] = faceP->vertices[1]->ny;
	tempNorm2[2] = faceP->vertices[1]->nz;

	tempNorm1[0] = (tempNorm1[0] + tempNorm2[0]) / 2.0f;
	tempNorm1[1] = (tempNorm1[1] + tempNorm2[1]) / 2.0f;
	tempNorm1[2] = (tempNorm1[2] + tempNorm2[2]) / 2.0f;

	normVec(tempNorm1);

	faceP->vertices[1]->nx = tempNorm1[0];
	faceP->vertices[1]->ny = tempNorm1[1];
	faceP->vertices[1]->nz = tempNorm1[2];
	//////////////////////////////////////////////////////////////////////////////////////////////////
	tempNorm2[0] = faceP->vertices[2]->nx;
	tempNorm2[1] = faceP->vertices[2]->ny;
	tempNorm2[2] = faceP->vertices[2]->nz;

	tempNorm1[0] = (tempNorm1[0] + tempNorm2[0]) / 2.0f;
	tempNorm1[1] = (tempNorm1[1] + tempNorm2[1]) / 2.0f;
	tempNorm1[2] = (tempNorm1[2] + tempNorm2[2]) / 2.0f;

	normVec(tempNorm1);

	faceP->vertices[2]->nx = tempNorm1[0];
	faceP->vertices[2]->ny = tempNorm1[1];
	faceP->vertices[2]->nz = tempNorm1[2];


	/*
	faceP->vertices[0]->nx = (tempNorm.x );
	faceP->vertices[0]->ny = (tempNorm.y);
	faceP->vertices[0]->nz = (tempNorm.z );

	faceP->vertices[1]->nx = (tempNorm.x );
	faceP->vertices[1]->ny = (tempNorm.y );
	faceP->vertices[1]->nz = (tempNorm.z );

	faceP->vertices[2]->nx = (tempNorm.x );
	faceP->vertices[2]->ny = (tempNorm.y );
	faceP->vertices[2]->nz = (tempNorm.z );
	*/
}
