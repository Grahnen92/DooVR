#include "Mesh.h"
#include "time.h"
#include "math.h"
#include <algorithm>
#include <iterator>

using namespace std;

void normVec(float* vec) {
	float length = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	vec[0] = vec[0] / length;
	vec[1] = vec[1] / length;
	vec[2] = vec[2] / length;
}

void crossProd(float* vec1, float* vec2, float normal[3]) {
	normal[0] = (vec1[1] * vec2[2] - vec1[2] * vec2[1]);
	normal[1] = -(vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	normal[2] = (vec1[0] * vec2[1] - vec1[1] * vec2[0]);
}

Mesh::Mesh() {
	triangle tempT;
	vertex tempV;

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

	triangle* indexP;
	vertex * vertexP;

	rows = 100;
	cols = 100;

	float scaleF = 0.0f;

	scaleF = 1.0f / (rows *2);

	tempV.y = 0.0f;
	tempV.nx = 0.0f;
	tempV.ny = 1.0f;
	tempV.nz = 0.0f;
	
	
	// Place vertices
	for (int i = -rows / 2; i < rows / 2; i++) {
		//cout << fmod(i, sqrt(0.75f) * 2) << endl;

		for (int j = -cols / 2; j < cols / 2; j++) {
			
			if (fmod(i, 2) != 0){
				tempV.x = ((float)(j) + 0.5f)*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			} else {
				tempV.x = ((float)(j))*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			}
		
			vertexArray.push_back(tempV);
		}
	}
	
	face* handledFace1 = nullptr;
	face* handledFace2 = nullptr;
	face* handledFace3 = nullptr;
	face* handledFace4 = nullptr;
	face* previousFace = nullptr;

	// set triangle indecies and bind faces
	for (int i = 1; i < rows - 1; i++) {
		for (int j = 1; j < cols - 1; j++) {

			//if (i != 0 && j !=0 && i != rows - 1 && j != cols - 1) {
			vertexArray[i * rows + j].vertexNeighbors[0] = i * rows + j - 1;
			vertexArray[i * rows + j].vertexNeighbors[1] = (i - 1) * rows + j;
			vertexArray[i * rows + j].vertexNeighbors[2] = (i - 1) * rows + j + 1;
			vertexArray[i * rows + j].vertexNeighbors[3] = (i + 1) * rows + j;
			vertexArray[i * rows + j].vertexNeighbors[4] = (i + 1) * rows + j + 1;
			vertexArray[i * rows + j].vertexNeighbors[5] = i * rows + j + 1;

			if (i > 1 && j > 1 && i < rows - 2 && j < cols - 2) {
				if ( i % 2 == 0) {
					vertexArray[i * rows + j].triangleNeighbors[0] = (j*2 - 2) + (i - 1) * 2 * (cols -2) ;
					vertexArray[i * rows + j].triangleNeighbors[1] = (j*2 - 1) + (i - 1) * 2 * (cols - 2);
					vertexArray[i * rows + j].triangleNeighbors[2] = (j*2) + (i - 1) * 2 * (cols - 2);

					vertexArray[i * rows + j].triangleNeighbors[3] = (j*2 - 3) + (i) * 2 * (cols - 2);
					vertexArray[i * rows + j].triangleNeighbors[4] = (j*2 - 2) + (i) * 2 * (cols - 2);
					vertexArray[i * rows + j].triangleNeighbors[5] = (j*2 - 1) + (i) * 2 * (cols - 2);
				}
				else {
					vertexArray[i * rows + j].triangleNeighbors[0] = (j * 2 - 2) + (i - 1) * 2 * (cols - 2);
					vertexArray[i * rows + j].triangleNeighbors[1] = (j * 2 - 1) + (i - 1) * 2 * (cols - 2);
					vertexArray[i * rows + j].triangleNeighbors[2] = (j * 2) + (i - 1) * 2 * (cols - 2);

					vertexArray[i * rows + j].triangleNeighbors[3] = (j * 2 - 1) + (i) * 2 * (cols - 2);
					vertexArray[i * rows + j].triangleNeighbors[4] = (j * 2 ) + (i) * 2 * (cols - 2);
					vertexArray[i * rows + j].triangleNeighbors[5] = (j * 2 + 1) + (i) * 2 * (cols - 2);
				}
			}

			tempT.index1 = i*rows + j;
			tempT.index2 = i*rows + j - 1;
			tempT.index3 = (i-1)*rows + j;
			indexArray.push_back(tempT);

			tempT.index1 = i*rows + j;
			tempT.index2 = (i-1)*rows + j;
			tempT.index3 = (i - 1)*rows + j + 1;
			indexArray.push_back(tempT);

		//	}
			

			/////////////////////////////////////////////////////////////////////////////////////
		}
	}

	vector<triangle> tempList;
	triangle tempTri;

	for (int i = 0; i < indexArray.size(); i++)
	{
		tempTri.index1 = indexArray[i].index1;
		tempTri.index2 = indexArray[i].index2;
		tempTri.index3 = indexArray[i].index3;
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
				 indexArray.size()*sizeof(triangle), indexP, GL_STREAM_DRAW);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the buffers while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh(void) {

}
/*
void Mesh::dilate(float* p, float lp[3], float rad, bool but) {
	glm::vec4 tempvec;
	vertex tempV;
	face* lastFace;
	face* currFace;
	face* nextFace;
	face* startFace;
	int currVert;
	int fNr = 1;

	//MOVEMENT BETWEEN LAST FRAME AND THIS FRAME
	float pMove[3];
	pMove[0] = (p[0] - lp[0]);
	pMove[1] = (p[1] - lp[1]);
	pMove[2] = (p[2] - lp[2]);

	tempvec = glm::transpose(glm::make_mat4(orientation)) * glm::vec4(pMove[0], pMove[1], pMove[2], 1.0f);
	pMove[0] = tempvec.x;
	pMove[1] = tempvec.y;
	pMove[2] = tempvec.z;


	cout << pMove[0] << " " << pMove[1] << " " << pMove[2] << endl;

	tempV.z = 0;
	vertex point;
	point.x = p[0] - position[0];
	point.y = p[1] - position[1];
	point.z = p[2] - position[2];

	tempvec = glm::transpose(glm::make_mat4(orientation)) * glm::vec4(point.x, point.y, point.z, 1.0f);
	point.x = tempvec.x;
	point.y = tempvec.y;
	point.z = tempvec.z;
	//float radius = rad;


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

			if (but == true) {
				vertexArray[i].x += pMove[0];
				vertexArray[i].y += pMove[1];
				vertexArray[i].z += pMove[2];
			}
			
			// find all faces that belongs to the changed vertexpoint
			currVert = i;

			startFace = vertexArray[i].adjacentFace;
			updateFace(startFace);			

			fNr = 1;

			nextFace = startFace->nFace[0];
			// check the faces neighbouring faces one at a time until the face that has the changed vertex is found
			while ((nextFace->index1 != currVert && nextFace->index2 != currVert && nextFace->index3 != currVert) ) {
				nextFace = startFace->nFace[fNr];
				fNr++;
			}

			lastFace = startFace;
			currFace = nextFace;
			fNr = 1;
			
			while (currFace != startFace) {
				updateFace(currFace);

				nextFace = currFace->nFace[0];
				// check the faces neighbouring faces one at a time until the face that has the changed vertex is found
				while ( (nextFace->index1 != currVert && nextFace->index2 != currVert && nextFace->index3 != currVert) || (nextFace == lastFace) ) {
					nextFace = currFace->nFace[fNr];
					fNr++;
				}
				lastFace = currFace;
				currFace = nextFace;
				fNr = 1;
			}
		
			success = true;

			// get range of changed vertices
			if (startRow == -1) {
				startRow = (i - (i % rows)) / rows;
				endRow = startRow; // first element is also last element as yet
			}
			else {
				prevRow = endRow;
				endRow = (i - (i % rows)) / rows;
			}

			if (startCol.size() != 0 && endRow == prevRow) {		//  check if the last added column is on the same row, endRow will always be the current row
				endCol.pop_back();									//  if it is the same row it is the last element as yet, 20 elements on each row
				endCol.push_back(i - endRow * rows);
				//endCol.push_back(i % 20);
			}
			else {												// first element on row
				//startCol.push_back(i % 20);
				startCol.push_back(i - endRow * rows);
				//endCol.push_back(i % 20);
				endCol.push_back(i - endRow * rows);
			}
		}
	}

	if (success == true) {

		vertexP = &vertexArray[0];

		//vector<triangle> tempList[100000];
		////tempList.reserve(100000);
		//indexP = &tempList[0];

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
*/

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
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}

float Mesh::vectorLength(vertex vertex1, vertex vertex2) {
	vertex vector;

	vector.x = vertex1.x - vertex2.x;
	vector.y = vertex1.y - vertex2.y;
	vector.z = vertex1.z - vertex2.z;

	return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

float Mesh::vecLenght(float vec[3]) {
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

bool Mesh::sortByXCord(const vertex &a, const vertex &b) {
	return a.x < b.x;
}

void Mesh::updateFace(face* faceP)
{
	/*
	float maxRad = 0.01;
	float minRad = 0.005;

	// CALCULATE NORMAL USING GLM
	glm::vec3 tempV1;
	glm::vec3 tempV2;
	glm::vec3 tempV3;
	glm::vec3 tempV4;
	glm::vec3 tempN1;
	glm::vec3 tempN2;

	tempV1.x = vertexArray[faceP->index2].x - vertexArray[faceP->index1].x;
	tempV1.y = vertexArray[faceP->index2].y - vertexArray[faceP->index1].y;
	tempV1.z = vertexArray[faceP->index2].z - vertexArray[faceP->index1].z;

	tempV2.x = vertexArray[faceP->index3].x - vertexArray[faceP->index1].x;
	tempV2.y = vertexArray[faceP->index3].y - vertexArray[faceP->index1].y;
	tempV2.z = vertexArray[faceP->index3].z - vertexArray[faceP->index1].z;
	//tempV2.x = faceP->vertices[2]->x - faceP->vertices[0]->x;
	
	tempN1 = glm::cross(tempV1, tempV2);

	glm::normalize(tempN1);

	tempN2.x = vertexArray[faceP->index1].nx;
	tempN2.y = vertexArray[faceP->index1].ny;
	tempN2.z = vertexArray[faceP->index1].nz;

	tempN2 = (tempN1 + tempN2) / 2.0f;

	glm::normalize(tempN2);

	vertexArray[faceP->index1].nx = tempN2.x;
	vertexArray[faceP->index1].ny = tempN2.y;
	vertexArray[faceP->index1].nz = tempN2.z;
	/////////////////////////////////////////////////////////////////////////////////////////////////
	tempN2.x = vertexArray[faceP->index2].nx;
	tempN2.y = vertexArray[faceP->index2].ny;
	tempN2.z = vertexArray[faceP->index2].nz;

	tempN2 = (tempN1 + tempN2) / 2.0f;

	glm::normalize(tempN2);

	vertexArray[faceP->index2].nx = tempN2.x;
	vertexArray[faceP->index2].ny = tempN2.y;
	vertexArray[faceP->index2].nz = tempN2.z;
	//////////////////////////////////////////////////////////////////////////////////////////////////
	tempN2.x = vertexArray[faceP->index3].nx;
	tempN2.y = vertexArray[faceP->index3].ny;
	tempN2.z = vertexArray[faceP->index3].nz;

	tempN2 = (tempN1 + tempN2) / 2.0f;

	glm::normalize(tempN2);

	vertexArray[faceP->index3].nx = tempN2.x;
	vertexArray[faceP->index3].ny = tempN2.y;
	vertexArray[faceP->index3].nz = tempN2.z;

	// CHECK IF RETRIANGULATION IS NEEDED
	///////////////////////////////////////////////////////////////////////////////////////
	
	tempV1.x = vertexArray[faceP->index1].x;
	tempV1.y = vertexArray[faceP->index1].y;
	tempV1.z = vertexArray[faceP->index1].z;

	tempV1.x = vertexArray[faceP->index2].x;
	tempV1.y = vertexArray[faceP->index2].y;
	tempV1.z = vertexArray[faceP->index2].z;

	tempV1.x = vertexArray[faceP->index3].x;
	tempV1.y = vertexArray[faceP->index3].y;
	tempV1.z = vertexArray[faceP->index3].z;

	tempV4 = (tempV1 + tempV2 + tempV3) / 3.0f;

	tempV1 = tempV1 - tempV4;
	tempV2 = tempV2 - tempV4;
	tempV3 = tempV3 - tempV4;

	if (glm::length(tempV1) > maxRad || glm::length(tempV2) > maxRad || glm::length(tempV3) > maxRad)
	{
		//vertexArray.push_back(vertex());
		//vertexArray.push_back(vertex());
		//vertexArray.push_back(vertex());
		//indexArray.erase(indexArray.begin() + index - 1 );
		//delete faceP;

		//indexArray.push_back();
		//indexArray.push_back();
		//indexArray.push_back();
		//indexArray.push_back();

		//for (3)
	//	if (glm::length(tempV1) > maxRad || glm::length(tempV2) > maxRad || glm::length(tempV3) > maxRad)
			//while

	}
	else if (glm::length(tempV1) < minRad && glm::length(tempV2) < minRad && glm::length(tempV3) < minRad)
	{

	}
	*/

	//CALCULATE THE NEW FACE NORMAL NOT USING GLM

	float tempVert1[3];
	float tempVert2[3];
	float tempNorm1[3];
	float tempNorm2[3];

	float vPoint1[3];
	float vPoint2[3];
	float vPoint3[3];
	//float middlePoint[3];
	//const float MAX_RADIUS = 0.01f;
	//const float MIN_RADIUS = 0.005f;
	//float* point2Mid1;
	//float* point2Mid2;
	//float* point2Mid3;
	const float MAX_LENGTH = 0.02f;
	const float MIN_LENGTH = 0.01f;
	float* faceVec1;
	float* faceVec2;
	float* faceVec3;

	// calculate vector between two points
	tempVert1[0] = vertexArray[faceP->index2].x - vertexArray[faceP->index1].x;
	tempVert1[1] = vertexArray[faceP->index2].y - vertexArray[faceP->index1].y;
	tempVert1[2] = vertexArray[faceP->index2].z - vertexArray[faceP->index1].z;

	tempVert2[0] = vertexArray[faceP->index3].x - vertexArray[faceP->index1].x;
	tempVert2[1] = vertexArray[faceP->index3].y - vertexArray[faceP->index1].y;
	tempVert2[2] = vertexArray[faceP->index3].z - vertexArray[faceP->index1].z;

	//calcualte the cross prod of the two vectors (normal)
	crossProd(tempVert1, tempVert2, tempNorm1);

	normVec(tempNorm1);
	
	// insert the face's existing normal into tempvert
	tempNorm2[0] = vertexArray[faceP->index1].nx;
	tempNorm2[1] = vertexArray[faceP->index1].ny;
	tempNorm2[2] = vertexArray[faceP->index1].nz;

	// calculate the new normal for the first vertex point
	tempNorm2[0] = (tempNorm1[0] + tempNorm2[0]) / 2.0f;
	tempNorm2[1] = (tempNorm1[1] + tempNorm2[1]) / 2.0f;
	tempNorm2[2] = (tempNorm1[2] + tempNorm2[2]) / 2.0f;

	normVec(tempNorm2);

	vertexArray[faceP->index1].nx = tempNorm2[0];
	vertexArray[faceP->index1].ny = tempNorm2[1];
	vertexArray[faceP->index1].nz = tempNorm2[2];
	//////////////// SECOND VERTEX POINT NORMAL /////////////////////////////////////////////////////

	tempNorm2[0] = vertexArray[faceP->index2].nx;
	tempNorm2[1] = vertexArray[faceP->index2].ny;
	tempNorm2[2] = vertexArray[faceP->index2].nz;

	// calculate the new normal
	tempNorm2[0] = (tempNorm1[0] + tempNorm2[0]) / 2.0f;
	tempNorm2[1] = (tempNorm1[1] + tempNorm2[1]) / 2.0f;
	tempNorm2[2] = (tempNorm1[2] + tempNorm2[2]) / 2.0f;

	normVec(tempNorm2);

	vertexArray[faceP->index2].nx = tempNorm2[0];
	vertexArray[faceP->index2].ny = tempNorm2[1];
	vertexArray[faceP->index2].nz = tempNorm2[2];

	////////////////////////////// THIRD VERTEX POINT NORMAL //////////////////////////////////////////

	tempNorm2[0] = vertexArray[faceP->index3].nx;
	tempNorm2[1] = vertexArray[faceP->index3].ny;
	tempNorm2[2] = vertexArray[faceP->index3].nz;

	// calculate the new normal
	tempNorm2[0] = (tempNorm1[0] + tempNorm2[0]) / 2.0f;
	tempNorm2[1] = (tempNorm1[1] + tempNorm2[1]) / 2.0f;
	tempNorm2[2] = (tempNorm1[2] + tempNorm2[2]) / 2.0f;

	normVec(tempNorm2);

	vertexArray[faceP->index3].nx = tempNorm2[0];
	vertexArray[faceP->index3].ny = tempNorm2[1];
	vertexArray[faceP->index3].nz = tempNorm2[2];

	/////////////////////////////////////////////////////////////////////////////////////
	// CHECK IF RETRIANGULATION IS NEEDED
	vPoint1[0] = vertexArray[faceP->index1].x;
	vPoint1[1] = vertexArray[faceP->index1].y;
	vPoint1[2] = vertexArray[faceP->index1].z;

	vPoint2[0] = vertexArray[faceP->index2].x;
	vPoint2[1] = vertexArray[faceP->index2].y;
	vPoint2[2] = vertexArray[faceP->index2].z;

	vPoint3[0] = vertexArray[faceP->index3].x;
	vPoint3[1] = vertexArray[faceP->index3].y;
	vPoint3[2] = vertexArray[faceP->index3].z;

	/* // USING RADIUS AND MIDDLE POINT
	// Calculate a point placed in the middle of the face
	middlePoint[0] = (vPoint1[0] + vPoint2[0] + vPoint3[0]) / 3;
	middlePoint[1] = (vPoint1[1] + vPoint2[1] + vPoint3[1]) / 3;
	middlePoint[2] = (vPoint1[2] + vPoint2[2] + vPoint3[2]) / 3;

	// calculate between the point in the middle and the vertecies and check if they are to long or to short
	point2Mid1 = calculateVec(vPoint1, middlePoint);
	point2Mid2 = calculateVec(vPoint2, middlePoint);
	point2Mid3 = calculateVec(vPoint3, middlePoint);

	// the face is to big
	if (vecLenght(point2Mid1) > MAX_RADIUS || 
		vecLenght(point2Mid2) > MAX_RADIUS || 
		vecLenght(point2Mid3) > MAX_RADIUS) { 

	} 
	// the face is to small
	else if (vecLenght(point2Mid1) < MIN_RADIUS ||
			 vecLenght(point2Mid2) < MIN_RADIUS || 
			 vecLenght(point2Mid3) < MIN_RADIUS) {
	}
	*/

	faceVec1 = calculateVec(vPoint2, vPoint1);
	faceVec2 = calculateVec(vPoint3, vPoint2);
	faceVec3 = calculateVec(vPoint1, vPoint3);

	// the face is to big
	if (vecLenght(faceVec1) > MAX_LENGTH 
		|| vecLenght(faceVec2) > MAX_LENGTH 
		|| vecLenght(faceVec3) > MAX_LENGTH) {
		
		vertex newPoint1;
		vertex newPoint2;
		vertex newPoint3;

		// insert the first new vertex
		newPoint1.x = (faceVec1[0] / 2) + vPoint1[0];
		newPoint1.y = (faceVec1[1] / 2) + vPoint1[1];
		newPoint1.z = (faceVec1[2] / 2) + vPoint1[2];
		newPoint1.nx = vertexArray[faceP->index1].nx;
		newPoint1.ny = vertexArray[faceP->index1].ny;
		newPoint1.nz = vertexArray[faceP->index1].nz;
		// insert the second new vertex
		newPoint2.x = (faceVec2[0] / 2) + vPoint2[0];
		newPoint2.y = (faceVec2[1] / 2) + vPoint2[1];
		newPoint2.z = (faceVec2[2] / 2) + vPoint2[2];
		newPoint2.nx = vertexArray[faceP->index2].nx;
		newPoint2.ny = vertexArray[faceP->index2].ny;
		newPoint2.nz = vertexArray[faceP->index2].nz;

		// insert the third new vertex
		newPoint3.x = (faceVec3[0] / 2) + vPoint3[0];
		newPoint3.y = (faceVec3[1] / 2) + vPoint3[1];
		newPoint3.z = (faceVec3[2] / 2) + vPoint3[2];
		newPoint3.nx = vertexArray[faceP->index3].nx;
		newPoint3.ny = vertexArray[faceP->index3].ny;
		newPoint3.nz = vertexArray[faceP->index3].nz;

		/*
		// Calculate the new vertecies normals
		


		// rebind the faces



		// push back the new vertecies
		vertexArray.push_back(newPoint1);
		*/
	}

	// the face is to small
	else if (vecLenght(faceVec1) < MIN_LENGTH ||
			 vecLenght(faceVec2) < MIN_LENGTH ||
			 vecLenght(faceVec3) < MIN_LENGTH) {

	}

}


float* Mesh::calculateVec(float a[3], float b[3]) {
	float vec[3];
	vec[0] = a[0] - b[0];
	vec[1] = a[1] - b[1];
	vec[2] = a[2] - b[2];

	return &vec[0];
}
