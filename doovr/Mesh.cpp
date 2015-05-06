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

void crossProd(float normal[3], float* vec1, float* vec2) {
	normal[0] = (vec1[1] * vec2[2] - vec1[2] * vec2[1]);
	normal[1] = -(vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	normal[2] = (vec1[0] * vec2[1] - vec1[1] * vec2[0]);
}

Mesh::Mesh() {
	triangle tempT;
	vertex tempV;
	vertexInf tempVI;

	vertexArray.reserve(10000000);
	indexArray.reserve(10000000);

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

	float scaleF = 0.0f;

	scaleF = 1.0f / (ROWS * 2) * 4.0f;

	tempV.y = 0.0f;
	tempV.nx = 0.0f;
	tempV.ny = 1.0f;
	tempV.nz = 0.2f;

	// Place vertices
	for (int i = -ROWS / 2; i < ROWS / 2; i++) {

		for (int j = -COLS / 2; j < COLS / 2; j++) {

			if (i % 2 != 0){
				tempV.x = ((float)(j)+0.5f)*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			}
			else {
				tempV.x = ((float)(j))*scaleF;
				tempV.z = ((float)(i))*0.86602540378f*scaleF;
			}

			vertexArray.push_back(tempV);
			vertexInfo.push_back(tempVI);
		}
	}

	// set triangle indecies and bind faces
	for (int i = 1; i < ROWS - 1; i++) {
		for (int j = 1; j < COLS - 1; j++) {

			//if (i != 0 && j !=0 && i != ROWS - 1 && j != COLS - 1) {
			if (i % 2 == 0) {

				vertexInfo[i * ROWS + j].vertexNeighbors.push_back(i * ROWS + j - 1);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i - 1) * ROWS + j);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i - 1) * ROWS + j - 1);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i + 1) * ROWS + j);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i + 1) * ROWS + j - 1);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back(i * ROWS + j + 1);

				if (i > 1 && j > 1 && i < ROWS - 2 && j < COLS - 2) {
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 2) + (i - 1) * 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 1) + (i - 1) * 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2) + (i - 1) * 2 * (COLS - 2));

					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 3) + (i)* 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 2) + (i)* 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 1) + (i)* 2 * (COLS - 2));
				}

				tempT.index[0] = (i - 1)*ROWS + j - 1;
				tempT.index[1] = (i)*ROWS + j - 1;
				tempT.index[2] = i*ROWS + j;
				indexArray.push_back(tempT);

				tempT.index[0] = (i - 1)*ROWS + j;
				tempT.index[1] = (i - 1)*ROWS + j - 1;
				tempT.index[2] = i * ROWS + j;
				indexArray.push_back(tempT);


			}
			else { // uneven row

				vertexInfo[i * ROWS + j].vertexNeighbors.push_back(i * ROWS + j - 1);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i - 1) * ROWS + j);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i - 1) * ROWS + j + 1);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i + 1) * ROWS + j);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back((i + 1) * ROWS + j + 1);
				vertexInfo[i * ROWS + j].vertexNeighbors.push_back(i * ROWS + j + 1);

				if (i > 1 && j > 1 && i < ROWS - 1 && j < COLS - 2) {
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 2) + (i - 1) * 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 1) + (i - 1) * 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2) + (i - 1) * 2 * (COLS - 2));

					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 - 1) + (i)* 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2) + (i)* 2 * (COLS - 2));
					vertexInfo[i * ROWS + j].triangleNeighbors.push_back((j * 2 + 1) + (i)* 2 * (COLS - 2));
				}

				tempT.index[0] = (i - 1)*ROWS + j;
				tempT.index[1] = (i)*ROWS + j - 1;
				tempT.index[2] = i*ROWS + j;
				indexArray.push_back(tempT);

				tempT.index[0] = (i - 1)*ROWS + j + 1;
				tempT.index[1] = (i - 1)*ROWS + j;
				tempT.index[2] = i*ROWS + j;
				indexArray.push_back(tempT);

			}

			//	}

			/////////////////////////////////////////////////////////////////////////////////////
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
		(vertexArray.size() + 10000)*sizeof(vertex), vertexP, GL_STREAM_DRAW);

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
		(indexArray.size() + 10000)*sizeof(triangle), indexP, GL_STREAM_DRAW);

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
			/*
			// get range of changed vertices
			if (startRow == -1) {
			startRow = (i - (i % ROWS)) / ROWS;
			endRow = startRow; // first element is also last element as yet
			}
			else {
			prevRow = endRow;
			endRow = (i - (i % ROWS)) / ROWS;
			}
			if (startCol.size() != 0 && endRow == prevRow) {		//  check if the last added column is on the same row, endRow will always be the current row
			endCol.pop_back();									//  if it is the same row it is the last element as yet, 20 elements on each row
			endCol.push_back(i - endRow * ROWS);
			//endCol.push_back(i % 20);
			}
			else {												// first element on row
			//startCol.push_back(i % 20);
			startCol.push_back(i - endRow * ROWS);
			//endCol.push_back(i % 20);
			endCol.push_back(i - endRow * ROWS);
			}
			*/
		}
	}

	changeCount = 0;
	if (changedVertices.size() > 0)
		updateArea(&changedVertices[0], changedVertices.size());

	if (success == true) {

		vertexP = &vertexArray[0];


		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		/*
		int currentRow = startRow;
		int range = 0;
		int o = 0;
		int beginning = 0;
		// update the buffer where if has changed
		for (int j = 0; currentRow <= endRow && j < endCol.size() && j < startCol.size(); j++, currentRow++) {
		range = endCol[j] + 1 - startCol[j];
		beginning = currentRow * ROWS + startCol[j];
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
		range = oldArraySize - vertexArray.size();
		vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, beginning*sizeof(vertex), sizeof(vertex)*range,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
		for (int i = oldArraySize; i < range ; i++)
		{
		vertexP[o].x = vertexArray[i].x;
		vertexP[o].y = vertexArray[i].y;
		vertexP[o].z = vertexArray[i].z;
		vertexP[o].nx = vertexArray[i].nx;
		vertexP[o].ny = vertexArray[i].ny;
		vertexP[o].nz = vertexArray[i].nz;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		*/
		/*
		int nBufferSize = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nBufferSize);
		int originalVertexArraySize = ( nBufferSize / sizeof(float) );
		*/

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
			/*
			// get range of changed vertices
			if (startRow == -1) {
			startRow = (i - (i % ROWS)) / ROWS;
			endRow = startRow; // first element is also last element as yet
			}
			else {
			prevRow = endRow;
			endRow = (i - (i % ROWS)) / ROWS;
			}
			if (startCol.size() != 0 && endRow == prevRow) {		//  check if the last added column is on the same row, endRow will always be the current row
			endCol.pop_back();									//  if it is the same row it is the last element as yet, 20 elements on each row
			endCol.push_back(i - endRow * ROWS);
			//endCol.push_back(i % 20);
			}
			else {												// first element on row
			//startCol.push_back(i % 20);
			startCol.push_back(i - endRow * ROWS);
			//endCol.push_back(i % 20);
			endCol.push_back(i - endRow * ROWS);
			}
			*/
		}
	}

	updateArea(&changedVertices[0], changedVertices.size());

	//if (vertexArray.size() > 5053)
	//{
	/*
		glLineWidth(2.0);
		for (int i = 0; i < vertexInfo[5053].vertexNeighbors.size() ; i++)
		{
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.7f, 0.5f);
			glVertex3f(vertexArray[5053].x, vertexArray[5053].y+ 0.01f, vertexArray[5053].z);
		
				//indexArray[vertexInfo[5053].triangleNeighbors[i]].index[1]
				//indexArray[vertexInfo[5053].triangleNeighbors[i]].index[2]
			glVertex3f((vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[0]].x + vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[1]].x + vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[2]].x) / 3.0f,
				((vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[0]].y + vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[1]].y + vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[2]].y) / 3.0f) + 0.01f,
				(vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[0]].z + vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[1]].z + vertexArray[indexArray[vertexInfo[5053].triangleNeighbors[i]].index[2]].z) / 3.0f);
		
			glEnd();

			glLineWidth(3.0);
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.7f, 0.5f);
			glVertex3f(vertexArray[5053].x, vertexArray[5053].y + 0.01f, vertexArray[5053].z);
			glVertex3f(vertexArray[vertexInfo[5053].vertexNeighbors[i]].x, vertexArray[vertexInfo[5053].vertexNeighbors[i]].y + 0.01f, vertexArray[vertexInfo[5053].vertexNeighbors[i]].z);
			glEnd();
		}
		//vertexInfo[4951].vertexNeighbors[]

		glLineWidth(1.0);
		*/
	//}
		
		glLineWidth(2.0);
		for (int i = 0; i < vertexInfo[vNR].vertexNeighbors.size(); i++)
		{
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.7f, 0.5f);
			glVertex3f(vertexArray[vNR].x, vertexArray[vNR].y + 0.01f, vertexArray[vNR].z);

			//indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[1]
			//indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[2]
			glVertex3f((vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[0]].x + vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[1]].x + vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[2]].x) / 3.0f,
				((vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[0]].y + vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[1]].y + vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[2]].y) / 3.0f) + 0.01f,
				(vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[0]].z + vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[1]].z + vertexArray[indexArray[vertexInfo[vNR].triangleNeighbors[i]].index[2]].z) / 3.0f);

			glEnd();

			glLineWidth(3.0);
			glBegin(GL_LINES);
			glColor3f(0.0f, 0.7f, 0.5f);
			glVertex3f(vertexArray[vNR].x, vertexArray[vNR].y + 0.01f, vertexArray[vNR].z);
			glVertex3f(vertexArray[vertexInfo[vNR].vertexNeighbors[i]].x, vertexArray[vertexInfo[vNR].vertexNeighbors[i]].y + 0.01f, vertexArray[vertexInfo[vNR].vertexNeighbors[i]].z);
			glEnd();
		}
		
	if (success == true) {

		vertexP = &vertexArray[0];


		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		/*
		int currentRow = startRow;
		int range = 0;
		int o = 0;
		int beginning = 0;
		// update the buffer where if has changed
		for (int j = 0; currentRow <= endRow && j < endCol.size() && j < startCol.size(); j++, currentRow++) {
		range = endCol[j] + 1 - startCol[j];
		beginning = currentRow * ROWS + startCol[j];
		// Present our vertex coordinates to OpenGL
		vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, beginning*sizeof(vertex), sizeof(vertex)*e,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
		for (int i = beginning; i < range + beginning, o < range; i++, o++) {
		vertexP[o].x = vertexArray[i].x;
		vertexP[o].y = vertexArray[i].y;
		vertexP[o].z = vertexArray[i].z;rang
		vertexP[o].nx = vertexArray[i].nx;
		vertexP[o].ny = vertexArray[i].ny;
		vertexP[o].nz = vertexArray[i].nz;
		}
		o = 0;
		glUnmapBuffer(GL_ARRAY_BUFFER);
		}
		range = oldArraySize - vertexArray.size();
		vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, beginning*sizeof(vertex), sizeof(vertex)*range,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
		for (int i = oldArraySize; i < range; i++)
		{
		vertexP[o].x = vertexArray[i].x;
		vertexP[o].y = vertexArray[i].y;
		vertexP[o].z = vertexArray[i].z;
		vertexP[o].nx = vertexArray[i].nx;
		vertexP[o].ny = vertexArray[i].ny;
		vertexP[o].nz = vertexArray[i].nz;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		*/
		/////////////////BRA ATT MINNAS 
		/*
		int nBufferSize = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nBufferSize);
		int originalVertexArraySize = ( nBufferSize / sizeof(float) );
		*/

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
				if (vertexInfo[currVert].vertexNeighbors.size() == 2)
				{
					tmpIndex2 = vertexInfo[currVert].triangleNeighbors[0];
					tmpIndex3 = vertexInfo[currVert].triangleNeighbors[1];

					for (int i = 0; i < 3; i++)
					{
						tmpIndex1 = indexArray[tmpIndex2].index[i];

						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex2), vertexInfo[tmpIndex1].triangleNeighbors.end());
						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex3), vertexInfo[tmpIndex1].triangleNeighbors.end());

						vertexInfo[tmpIndex1].vertexNeighbors.erase(remove(vertexInfo[tmpIndex1].vertexNeighbors.begin(), vertexInfo[tmpIndex1].vertexNeighbors.end(), currVert), vertexInfo[tmpIndex1].vertexNeighbors.end());
						
					}
					indexArray[tmpIndex2].index[0] = 0;
					indexArray[tmpIndex2].index[1] = 0;
					indexArray[tmpIndex2].index[2] = 0;

					indexArray[tmpIndex3].index[0] = 0;
					indexArray[tmpIndex3].index[1] = 0;
					indexArray[tmpIndex3].index[2] = 0;

					vertexArray[currVert].x = -1000;
					vertexArray[currVert].y = -1000;
					vertexArray[currVert].z = -1000;
					vertexInfo[currVert].triangleNeighbors.clear();
					vertexInfo[currVert].vertexNeighbors.clear();

					break;
				}
				else if (vertexInfo[nVert].vertexNeighbors.size() == 2)
				{
					tmpIndex2 = vertexInfo[nVert].triangleNeighbors[0];
					tmpIndex3 = vertexInfo[nVert].triangleNeighbors[1];

					for (int i = 0; i < 3; i++)
					{
						tmpIndex1 = indexArray[tmpIndex2].index[i];

						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex2), vertexInfo[tmpIndex1].triangleNeighbors.end());
						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex3), vertexInfo[tmpIndex1].triangleNeighbors.end());

						vertexInfo[tmpIndex1].vertexNeighbors.erase(remove(vertexInfo[tmpIndex1].vertexNeighbors.begin(), vertexInfo[tmpIndex1].vertexNeighbors.end(), nVert), vertexInfo[tmpIndex1].vertexNeighbors.end());

					}
					indexArray[tmpIndex2].index[0] = 0;
					indexArray[tmpIndex2].index[1] = 0;
					indexArray[tmpIndex2].index[2] = 0;

					indexArray[tmpIndex3].index[0] = 0;
					indexArray[tmpIndex3].index[1] = 0;
					indexArray[tmpIndex3].index[2] = 0;

					vertexArray[nVert].x = -1000;
					vertexArray[nVert].y = -1000;
					vertexArray[nVert].z = -1000;
					vertexInfo[nVert].triangleNeighbors.clear();
					vertexInfo[nVert].vertexNeighbors.clear();
					cT--;
					continue;
				}
				else{
					//////////////////////////////////////////////////////////////////////////////////////

					//remove bad triangles and vertex
					for (int k = 0; k < vertexInfo[currVert].triangleNeighbors.size(); k++) {
						for (int j = 0; j < vertexInfo[nVert].triangleNeighbors.size(); j++) {
							if (vertexInfo[currVert].triangleNeighbors[k] == vertexInfo[nVert].triangleNeighbors[j]) {
								sharedTriNeighbor.push_back(vertexInfo[currVert].triangleNeighbors[k]);
							}
						}
					}
					if (sharedTriNeighbor.size() > 2) {
						for (int i = 0; i < sharedTriNeighbor.size(); i++) {
							for (int j = 0; j < 3; j++) {
								if (vertexInfo[indexArray[sharedTriNeighbor[i]].index[j]].vertexNeighbors.size() == 2) {
									sharedTriNeighbor.push_back(sharedTriNeighbor[i]);
									sharedTriNeighbor.erase(sharedTriNeighbor.begin() + i);
									tmpIndex1 = indexArray[sharedTriNeighbor[i]].index[j];
								}
							}
						}

						for (int i = 0; i < 3; i++)
						{
							tmpIndex2 = indexArray[sharedTriNeighbor[2]].index[i];

							vertexInfo[tmpIndex2].triangleNeighbors.erase(remove(vertexInfo[tmpIndex2].triangleNeighbors.begin(), vertexInfo[tmpIndex2].triangleNeighbors.end(), sharedTriNeighbor[2]), vertexInfo[tmpIndex2].triangleNeighbors.end());
							vertexInfo[tmpIndex2].triangleNeighbors.erase(remove(vertexInfo[tmpIndex2].triangleNeighbors.begin(), vertexInfo[tmpIndex2].triangleNeighbors.end(), sharedTriNeighbor[3]), vertexInfo[tmpIndex2].triangleNeighbors.end());

							vertexInfo[tmpIndex2].vertexNeighbors.erase(remove(vertexInfo[tmpIndex2].vertexNeighbors.begin(), vertexInfo[tmpIndex2].vertexNeighbors.end(), tmpIndex1), vertexInfo[tmpIndex2].vertexNeighbors.end());

						}

						indexArray[sharedTriNeighbor[2]].index[0] = 0;
						indexArray[sharedTriNeighbor[2]].index[1] = 0;
						indexArray[sharedTriNeighbor[2]].index[2] = 0;

						indexArray[sharedTriNeighbor[3]].index[0] = 0;
						indexArray[sharedTriNeighbor[3]].index[1] = 0;
						indexArray[sharedTriNeighbor[3]].index[2] = 0;

						vertexArray[tmpIndex1].x = -1000;
						vertexArray[tmpIndex1].y = -1000;
						vertexArray[tmpIndex1].z = -1000;

						vertexInfo[tmpIndex1].triangleNeighbors.clear();
						vertexInfo[tmpIndex1].vertexNeighbors.clear();
					}

					iSharedTriNeighbor[0] = sharedTriNeighbor[0];
					iSharedTriNeighbor[1] = sharedTriNeighbor[1];

					rmVertex(vPoint1, vPoint2, tempVec1, currVert, nVert, iSharedTriNeighbor, &cT);
					cT--;

				}
				
			}
			else if (vecLength(tempVec1) > MAX_LENGTH) {

				if (vertexInfo[currVert].vertexNeighbors.size() == 2)
				{
					tmpIndex2 = vertexInfo[currVert].triangleNeighbors[0];
					tmpIndex3 = vertexInfo[currVert].triangleNeighbors[1];

					for (int i = 0; i < 3; i++)
					{
						tmpIndex1 = indexArray[tmpIndex2].index[i];

						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex2), vertexInfo[tmpIndex1].triangleNeighbors.end());
						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex3), vertexInfo[tmpIndex1].triangleNeighbors.end());

						vertexInfo[tmpIndex1].vertexNeighbors.erase(remove(vertexInfo[tmpIndex1].vertexNeighbors.begin(), vertexInfo[tmpIndex1].vertexNeighbors.end(), currVert), vertexInfo[tmpIndex1].vertexNeighbors.end());

					}
					indexArray[tmpIndex2].index[0] = 0;
					indexArray[tmpIndex2].index[1] = 0;
					indexArray[tmpIndex2].index[2] = 0;

					indexArray[tmpIndex3].index[0] = 0;
					indexArray[tmpIndex3].index[1] = 0;
					indexArray[tmpIndex3].index[2] = 0;

					vertexArray[currVert].x = -1000;
					vertexArray[currVert].y = -1000;
					vertexArray[currVert].z = -1000;
					vertexInfo[currVert].triangleNeighbors.clear();
					vertexInfo[currVert].vertexNeighbors.clear();

					break;
				}
				else if (vertexInfo[nVert].vertexNeighbors.size() == 2)
				{
					tmpIndex2 = vertexInfo[nVert].triangleNeighbors[0];
					tmpIndex3 = vertexInfo[nVert].triangleNeighbors[1];

					for (int i = 0; i < 3; i++)
					{
						tmpIndex1 = indexArray[tmpIndex2].index[i];

						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex2), vertexInfo[tmpIndex1].triangleNeighbors.end());
						vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), tmpIndex3), vertexInfo[tmpIndex1].triangleNeighbors.end());

						vertexInfo[tmpIndex1].vertexNeighbors.erase(remove(vertexInfo[tmpIndex1].vertexNeighbors.begin(), vertexInfo[tmpIndex1].vertexNeighbors.end(), nVert), vertexInfo[tmpIndex1].vertexNeighbors.end());

					}
					indexArray[tmpIndex2].index[0] = 0;
					indexArray[tmpIndex2].index[1] = 0;
					indexArray[tmpIndex2].index[2] = 0;

					indexArray[tmpIndex3].index[0] = 0;
					indexArray[tmpIndex3].index[1] = 0;
					indexArray[tmpIndex3].index[2] = 0;

					vertexArray[nVert].x = -1000;
					vertexArray[nVert].y = -1000;
					vertexArray[nVert].z = -1000;
					vertexInfo[nVert].triangleNeighbors.clear();
					vertexInfo[nVert].vertexNeighbors.clear();
					cT--;
					continue;
				}
				else{

					//remove bad triangles and vertex
					for (int k = 0; k < vertexInfo[currVert].triangleNeighbors.size(); k++) {
						for (int j = 0; j < vertexInfo[nVert].triangleNeighbors.size(); j++) {
							if (vertexInfo[currVert].triangleNeighbors[k] == vertexInfo[nVert].triangleNeighbors[j]) {
								sharedTriNeighbor.push_back(vertexInfo[currVert].triangleNeighbors[k]);
							}
						}
					}
					if (sharedTriNeighbor.size() > 2) {
						for (int i = 0; i < sharedTriNeighbor.size(); i++) {
							for (int j = 0; j < 3; j++) {
								if (vertexInfo[indexArray[sharedTriNeighbor[i]].index[j]].vertexNeighbors.size() == 2) {
									sharedTriNeighbor.push_back(sharedTriNeighbor[i]);
									sharedTriNeighbor.erase(sharedTriNeighbor.begin() + i);
									tmpIndex1 = indexArray[sharedTriNeighbor[i]].index[j];
								}
							}
						}
						//remove bad triangles from the bad triangles indices
						for (int i = 0; i < 3; i++)
						{
							tmpIndex2 = indexArray[sharedTriNeighbor[2]].index[i];

							vertexInfo[tmpIndex2].triangleNeighbors.erase(remove(vertexInfo[tmpIndex2].triangleNeighbors.begin(), vertexInfo[tmpIndex2].triangleNeighbors.end(), sharedTriNeighbor[2]), vertexInfo[tmpIndex2].triangleNeighbors.end());
							vertexInfo[tmpIndex2].triangleNeighbors.erase(remove(vertexInfo[tmpIndex2].triangleNeighbors.begin(), vertexInfo[tmpIndex2].triangleNeighbors.end(), sharedTriNeighbor[3]), vertexInfo[tmpIndex2].triangleNeighbors.end());

							vertexInfo[tmpIndex2].vertexNeighbors.erase(remove(vertexInfo[tmpIndex2].vertexNeighbors.begin(), vertexInfo[tmpIndex2].vertexNeighbors.end(), tmpIndex1), vertexInfo[tmpIndex2].vertexNeighbors.end());

						}

						indexArray[sharedTriNeighbor[2]].index[0] = 0;
						indexArray[sharedTriNeighbor[2]].index[1] = 0;
						indexArray[sharedTriNeighbor[2]].index[2] = 0;

						indexArray[sharedTriNeighbor[3]].index[0] = 0;
						indexArray[sharedTriNeighbor[3]].index[1] = 0;
						indexArray[sharedTriNeighbor[3]].index[2] = 0;

						vertexArray[tmpIndex1].x = -1000;
						vertexArray[tmpIndex1].y = -1000;
						vertexArray[tmpIndex1].z = -1000;

						vertexInfo[tmpIndex1].triangleNeighbors.clear();
						vertexInfo[tmpIndex1].vertexNeighbors.clear();
					}

					iSharedTriNeighbor[0] = sharedTriNeighbor[0];
					iSharedTriNeighbor[1] = sharedTriNeighbor[1];

					addVertex(vPoint1, vPoint2, tempVec1, currVert, nVert, iSharedTriNeighbor, &cT);
				}
			}
			sharedTriNeighbor.clear();
		}

	}
}

void Mesh::addVertex(float* pA, float* pB, float* vecA2B, int currVert, int nVert, int* sharedTriNeighbor, int* counter) {

	float newVertPos[3]; float tempPoint1[3]; float tempPoint2[3];  float tempVec1[3]; float tempVec2[3]; float tempVec3[3];
	//vector <int> sharedNeighbor;
	//sharedNeighbor.reserve(4);
	//int sharedTriNeighbor[2] = { -1, -1 };

	int tmpIndex1 = -1; int tmpIndex2 = -1; int tmpIndex3 = -1;
	vertex tmpV;
	vertexInf tmpVI;
	triangle tmpT;

	newVertPos[0] = pA[0] + vecA2B[0] / 2.0f;
	newVertPos[1] = pA[1] + vecA2B[1] / 2.0f;
	newVertPos[2] = pA[2] + vecA2B[2] / 2.0f;

	/*
	// find shared triangle neighbors between currVert and nVert
	for (int k = 0; k < vertexInfo[currVert].vertexNeighbors.size(); k++) {
		for (int j = 0; j < vertexInfo[nVert].vertexNeighbors.size(); j++) {
			if (vertexInfo[currVert].triangleNeighbors[k] == vertexInfo[nVert].triangleNeighbors[j]) {
				if (sharedTriNeighbor[0] == -1)
					sharedTriNeighbor[0] = vertexInfo[currVert].triangleNeighbors[k];
				else
					sharedTriNeighbor[1] = vertexInfo[currVert].triangleNeighbors[k];
			}
		}
	}
	*/
	//create new vertex
	tmpV.x = newVertPos[0];
	tmpV.y = newVertPos[1];
	tmpV.z = newVertPos[2];
	tmpV.nx = vertexArray[nVert].nx;
	tmpV.ny = vertexArray[nVert].ny;
	tmpV.nz = vertexArray[nVert].nz;
	vertexArray.push_back(tmpV);

	//create new vertexInfo
	tmpVI.triangleNeighbors.push_back(sharedTriNeighbor[0]);
	tmpVI.triangleNeighbors.push_back(sharedTriNeighbor[1]);
	tmpVI.triangleNeighbors.push_back(indexArray.size());
	tmpVI.triangleNeighbors.push_back(indexArray.size() + 1);
	tmpVI.vertexNeighbors.push_back(currVert);
	tmpVI.vertexNeighbors.push_back(nVert);

	//create new triangles
	for (int i = 0; i < 3; i++)
	{
		tmpIndex1 = indexArray[sharedTriNeighbor[0]].index[i];
		if ( tmpIndex1 == currVert)
			tmpT.index[i] = vertexArray.size() - 1;
		else if (tmpIndex1 == nVert){
			tmpT.index[i] = tmpIndex1;
		}
		else{
			tmpT.index[i] = tmpIndex1;
			//bind newVert to sharedneighbor
			tmpVI.vertexNeighbors.push_back(tmpIndex1);
			//bind sharedNeighbor to the new triangle
			vertexInfo[tmpIndex1].triangleNeighbors.push_back(indexArray.size());
			//bind sharedNeighbor the the newVert
			vertexInfo[tmpIndex1].vertexNeighbors.push_back(vertexArray.size() - 1);
		}
			
	}
	indexArray.push_back(tmpT);

	for (int i = 0; i < 3; i++)
	{
		tmpIndex1 = indexArray[sharedTriNeighbor[1]].index[i];
		if (tmpIndex1 == currVert)
			tmpT.index[i] = vertexArray.size() - 1;
		else if (tmpIndex1 == nVert){
			tmpT.index[i] = tmpIndex1;
		}
		else{
			tmpT.index[i] = tmpIndex1;
			//bind newVert to sharedneighbor
			tmpVI.vertexNeighbors.push_back(tmpIndex1);
			//bind sharedNeighbor to the new triangle
			vertexInfo[tmpIndex1].triangleNeighbors.push_back(indexArray.size());
			//bind sharedNeighbor the the newVert
			vertexInfo[tmpIndex1].vertexNeighbors.push_back(vertexArray.size() - 1);
		}
			
	}
	indexArray.push_back(tmpT);
	vertexInfo.push_back(tmpVI);

	//rebind nvert to new triangles and replace currvertneighbor with newVert
	for (int i = 0; i < vertexInfo[nVert].triangleNeighbors.size(); i++) {
		if (vertexInfo[nVert].triangleNeighbors[i] == sharedTriNeighbor[0])
			vertexInfo[nVert].triangleNeighbors[i] = indexArray.size() - 2;
		else if (vertexInfo[nVert].triangleNeighbors[i] == sharedTriNeighbor[1])
			vertexInfo[nVert].triangleNeighbors[i] = indexArray.size() - 1;
	}
	for (int i = 0; i < vertexInfo[nVert].vertexNeighbors.size(); i++) {
		if (vertexInfo[nVert].vertexNeighbors[i] == currVert)
			vertexInfo[nVert].vertexNeighbors[i] = vertexArray.size() - 1;
	}

	//replace nvert in currverts neighbors with newVert
	for (int i = 0; i < vertexInfo[currVert].vertexNeighbors.size(); i++) {
		if (vertexInfo[currVert].vertexNeighbors[i] == nVert)
			vertexInfo[currVert].vertexNeighbors[i] = vertexArray.size() - 1;
	}

	//fix old triangles
	for (int i = 0; i < 3; i++)
	{
		if (indexArray[sharedTriNeighbor[0]].index[i] == nVert)
			indexArray[sharedTriNeighbor[0]].index[i] = vertexArray.size() - 1;

		if (indexArray[sharedTriNeighbor[1]].index[i] == nVert)
			indexArray[sharedTriNeighbor[1]].index[i] = vertexArray.size() - 1;
	}


}
//STILL NEED TO USE COUNTER DONT FORGET
bool Mesh::rmVertex(float* pA, float* pB, float* vecA2B, int currVert, int nVert, int* sharedTriNeighbor, int* counter) {
	
	//vector <int> sharedNeighbor;
	//sharedNeighbor.reserve(4);
	//int sharedTriNeighbor[2] = { -1, -1 };
	int tmpIndex1 = -1; int tmpIndex2 = -1;

	vertexArray[currVert].x = pA[0] + vecA2B[0] / 2.0f;
	vertexArray[currVert].y = pA[1] + vecA2B[1] / 2.0f;
	vertexArray[currVert].z = pA[2] + vecA2B[2] / 2.0f;
	/*
	// find shared trinagle neighbors between currVert and nVert
	for (int k = 0; k < vertexInfo[currVert].vertexNeighbors.size(); k++) {
		for (int j = 0; j < vertexInfo[nVert].vertexNeighbors.size(); j++){
			if (vertexInfo[currVert].triangleNeighbors[k] == vertexInfo[nVert].triangleNeighbors[j]){
				if (sharedTriNeighbor[0] == -1)
					sharedTriNeighbor[0] = vertexInfo[currVert].triangleNeighbors[k];
				else
					sharedTriNeighbor[1] = vertexInfo[currVert].triangleNeighbors[k];
				
			}
		}
	}
	*/
	// remove the triangle bindings from the vertecies
	for (int i = 0; i < 3; i++) {

		tmpIndex1 = indexArray[sharedTriNeighbor[0]].index[i];
		vertexInfo[tmpIndex1].triangleNeighbors.erase(remove(vertexInfo[tmpIndex1].triangleNeighbors.begin(), vertexInfo[tmpIndex1].triangleNeighbors.end(), sharedTriNeighbor[0]), vertexInfo[tmpIndex1].triangleNeighbors.end());

		tmpIndex2 = indexArray[sharedTriNeighbor[1]].index[i];
		vertexInfo[tmpIndex2].triangleNeighbors.erase(remove(vertexInfo[tmpIndex2].triangleNeighbors.begin(), vertexInfo[tmpIndex2].triangleNeighbors.end(), sharedTriNeighbor[1]), vertexInfo[tmpIndex2].triangleNeighbors.end());
	}

	// add vertexNeighbors to currVert
	for (int i = 0; i < vertexInfo[nVert].vertexNeighbors.size(); i++) {
		
		tmpIndex1 = vertexInfo[nVert].vertexNeighbors[i];
		if (tmpIndex1 != currVert && find(vertexInfo[tmpIndex1].vertexNeighbors.begin(), vertexInfo[tmpIndex1].vertexNeighbors.end(), currVert) == vertexInfo[tmpIndex1].vertexNeighbors.end()) {
			vertexInfo[currVert].vertexNeighbors.push_back(tmpIndex1);
			
			// replace nVert with currVert
			for (int j = 0; j < vertexInfo[tmpIndex1].vertexNeighbors.size(); j++) {
				if (vertexInfo[tmpIndex1].vertexNeighbors[j] == nVert)
					vertexInfo[tmpIndex1].vertexNeighbors[j] = currVert;
			}
		}
		// remove nVert from the vertex neighbors if currVert is a neighbor
		else {
			vertexInfo[tmpIndex1].vertexNeighbors.erase(remove(vertexInfo[tmpIndex1].vertexNeighbors.begin(), vertexInfo[tmpIndex1].vertexNeighbors.end(), nVert), vertexInfo[tmpIndex1].vertexNeighbors.end());
		}
	}

	// update nVerts triangle neighbors to use currVert instead of nVert and add them to currVerts neighbors
	for (int i = 0; i < vertexInfo[nVert].triangleNeighbors.size(); i++) {
		tmpIndex1 = vertexInfo[nVert].triangleNeighbors[i];
		
		for (int j = 0; j < 3; j++)
		{
			if (indexArray[tmpIndex1].index[j] == nVert)
				indexArray[tmpIndex1].index[j] = currVert;
		}
		vertexInfo[currVert].triangleNeighbors.push_back(tmpIndex1);
	}

	indexArray[sharedTriNeighbor[0]].index[0] = 0;
	indexArray[sharedTriNeighbor[0]].index[1] = 0;
	indexArray[sharedTriNeighbor[0]].index[2] = 0;

	indexArray[sharedTriNeighbor[1]].index[0] = 0;
	indexArray[sharedTriNeighbor[1]].index[1] = 0;
	indexArray[sharedTriNeighbor[1]].index[2] = 0;

	vertexArray[nVert].x = -1000;
	vertexArray[nVert].y = -1000;
	vertexArray[nVert].z = -1000;
	vertexInfo[nVert].triangleNeighbors.clear();
	vertexInfo[nVert].vertexNeighbors.clear();

	return true;
}


void Mesh::calculateVec(float* newVec, float* a, float* b) {
	newVec[0] = a[0] - b[0];
	newVec[1] = a[1] - b[1];
	newVec[2] = a[2] - b[2];
}