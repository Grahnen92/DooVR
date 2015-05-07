#include "Mesh.h"
#include "time.h"
#include "math.h"
#include <algorithm>
#include <iterator>

using namespace std;

Mesh::Mesh() {
	triangle tempT;
	vertex tempV;
	vertexInf tempVI;
	for (int i = 0; i < 8; i++)
	{
		tempVI.triangleNeighbors[i] = -1;
		tempVI.vertexNeighbors[i] = -1;
	}

	vertexArray.reserve(100000);
	indexArray.reserve(100000);

	position[0] = 0.0f;
	position[1] = -0.2f;
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
	tempV.nz = 0.2f;
	


	
	// Place vertices
	for (int i = -rows / 2; i < rows / 2; i++) {

		for (int j = -cols / 2; j < cols / 2; j++) {
			
			if (fmod(i, 2) != 0){
				tempV.x = ((float)(j) + 0.5f)*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			} else {
				tempV.x = ((float)(j))*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			}
		
			vertexArray.push_back(tempV);
			vertexInfo.push_back(tempVI);
		}
	}

	// set triangle indecies and bind faces
	for (int i = 1; i < rows - 1; i++) {
		for (int j = 1; j < cols - 1; j++) {

			//if (i != 0 && j !=0 && i != rows - 1 && j != cols - 1) {
			vertexInfo[i * rows + j].vertexNeighbors[0] = i * rows + j - 1;
			vertexInfo[i * rows + j].vertexNeighbors[1] = (i - 1) * rows + j;
			vertexInfo[i * rows + j].vertexNeighbors[2] = (i - 1) * rows + j + 1;
			vertexInfo[i * rows + j].vertexNeighbors[3] = (i + 1) * rows + j;
			vertexInfo[i * rows + j].vertexNeighbors[4] = (i + 1) * rows + j + 1;
			vertexInfo[i * rows + j].vertexNeighbors[5] = i * rows + j + 1;


			
			if ( i % 2 == 0) {
				if (i > 1 && j > 1 && i < rows - 2 && j < cols - 2) {
					vertexInfo[i * rows + j].triangleNeighbors[0] = (j * 2 - 2) + (i - 1) * 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[1] = (j * 2 - 1) + (i - 1) * 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[2] = (j * 2) + (i - 1) * 2 * (cols - 2);

					vertexInfo[i * rows + j].triangleNeighbors[3] = (j * 2 - 3) + (i)* 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[4] = (j * 2 - 2) + (i)* 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[5] = (j * 2 - 1) + (i)* 2 * (cols - 2);
				}

				tempT.index1 = (i + 1)*rows + j - 1;
				tempT.index2 = (i+1)*rows + j;
				tempT.index3 = i*rows + j;
				indexArray.push_back(tempT);

				tempT.index1 = i * rows + j;
				tempT.index2 = (i - 1)*rows + j;
				tempT.index3 = (i - 1)*rows + j - 1;
				indexArray.push_back(tempT);

			}
			else {
				if (i > 1 && j > 1 && i < rows - 2 && j < cols - 2) {
					vertexInfo[i * rows + j].triangleNeighbors[0] = (j * 2 - 2) + (i - 1) * 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[1] = (j * 2 - 1) + (i - 1) * 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[2] = (j * 2) + (i - 1) * 2 * (cols - 2);

					vertexInfo[i * rows + j].triangleNeighbors[3] = (j * 2 - 1) + (i)* 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[4] = (j * 2) + (i)* 2 * (cols - 2);
					vertexInfo[i * rows + j].triangleNeighbors[5] = (j * 2 + 1) + (i)* 2 * (cols - 2);
				}

				tempT.index1 = (i + 1)*rows + j;
				tempT.index2 = (i + 1)*rows + j + 1;
				tempT.index3 = i*rows + j;
				indexArray.push_back(tempT);

				tempT.index1 = (i - 1)*rows + j + 1;
				tempT.index2 = (i - 1)*rows + j;
				tempT.index3 = i*rows + j;
				indexArray.push_back(tempT);
			}
			



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
						  6 * sizeof(GLfloat) , (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
						  6 * sizeof(GLfloat) , (void*)(3 * sizeof(GLfloat))); // normals

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

void Mesh::dilate(float* p, float lp[3], float rad, bool but) {
	glm::vec4 tempvec;
	vertex tempV;

	int changedVertices[10000] = { 0 };
	int changeCount = 0;

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

			vertexArray[i].x += pMove[0];
			vertexArray[i].y += pMove[1];
			vertexArray[i].z += pMove[2];			
			
			changedVertices[changeCount] = i;
			changeCount++;
		
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

	changeCount = 0;

	while (changedVertices[changeCount] != 0)
	{
		updateArea(changedVertices[changeCount]);
		changeCount++;
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
							  6 * sizeof(GLfloat), (void*)0); // xyz coordinates
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
							  6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals

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

void Mesh::updateArea(int currVert)
{

	//CALCULATE THE NEW FACE NORMAL NOT USING GLM

	float tempNorm1[3] = { 0.0f, 0.0f, 0.0f };
	float tempNorm2[3] = { 0.0f, 0.0f, 0.0f };

	float tempVec1[3];
	float tempVec2[3];

	float vPoint1[3];
	float vPoint2[3];
	float vPoint3[3];

	const float MAX_LENGTH = 0.02f;
	const float MIN_LENGTH = 0.01f;

	int triPos;

	int count = 0;

	triPos = vertexInfo[currVert].triangleNeighbors[count];

	vertexArray[currVert].nx = 0.0f;
	vertexArray[currVert].ny = 0.0f;
	vertexArray[currVert].nz = 0.0f;


	while (count < 8-1 && triPos != -1)
	{

		vPoint1[0] = vertexArray[indexArray[triPos].index1].x;
		vPoint1[1] = vertexArray[indexArray[triPos].index1].y;
		vPoint1[2] = vertexArray[indexArray[triPos].index1].z;

		vPoint2[0] = vertexArray[indexArray[triPos].index2].x;
		vPoint2[1] = vertexArray[indexArray[triPos].index2].y;
		vPoint2[2] = vertexArray[indexArray[triPos].index2].z;

		vPoint3[0] = vertexArray[indexArray[triPos].index3].x;
		vPoint3[1] = vertexArray[indexArray[triPos].index3].y;
		vPoint3[2] = vertexArray[indexArray[triPos].index3].z;

		calculateVec(tempVec1, vPoint2, vPoint1);
		calculateVec(tempVec2, vPoint3, vPoint1);

		Utilities::crossProd(tempNorm1, tempVec1, tempVec2);

		Utilities::normVec(tempNorm1);

		tempNorm2[0] += tempNorm1[0];
		tempNorm2[1] += tempNorm1[1];
		tempNorm2[2] += tempNorm1[2];

		count++;

		triPos = vertexInfo[currVert].triangleNeighbors[count];
	}
	tempNorm2[0] = tempNorm2[0] / (count - 1);
	tempNorm2[1] = tempNorm2[1] / (count - 1);
	tempNorm2[2] = tempNorm2[2] / (count - 1);

	vertexArray[currVert].nx = tempNorm2[0];
	vertexArray[currVert].ny = tempNorm2[1];
	vertexArray[currVert].nz = tempNorm2[2];

	//cout << " x: "<< vertexArray[currVert].nx  << " y: "<< vertexArray[currVert].ny << " z: " << vertexArray[currVert].nz  << endl;
}


void Mesh::calculateVec(float* newVec, float* a, float* b) {
	newVec[0] = a[0] - b[0];
	newVec[1] = a[1] - b[1];
	newVec[2] = a[2] - b[2];
}
