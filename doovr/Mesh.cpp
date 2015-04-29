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

	vertexArray.reserve(1000000);
	indexArray.reserve(1000000);

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

	scaleF = 1.0f / (rows * 2)* 10.0f;

	tempV.y = 0.0f;
	tempV.nx = 0.0f;
	tempV.ny = 1.0f;
	tempV.nz = 0.2f;

	// Place vertices
	for (int i = -rows / 2; i < rows / 2; i++) {
		//cout << fmod(i, sqrt(0.75f) * 2) << endl;

		for (int j = -cols / 2; j < cols / 2; j++) {

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
	for (int i = 1; i < rows - 1; i++) {
		for (int j = 1; j < cols - 1; j++) {

			//if (i != 0 && j !=0 && i != rows - 1 && j != cols - 1) {
			if (i % 2 == 0) {

				vertexInfo[i * rows + j].vertexNeighbors.push_back(i * rows + j - 1);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i - 1) * rows + j);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i - 1) * rows + j - 1);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i + 1) * rows + j);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i + 1) * rows + j - 1);
				vertexInfo[i * rows + j].vertexNeighbors.push_back(i * rows + j + 1);

				if (i > 1 && j > 1 && i < rows - 2 && j < cols - 2) {
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 2) + (i - 1) * 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 1) + (i - 1) * 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2) + (i - 1) * 2 * (cols - 2));

					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 3) + (i)* 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 2) + (i)* 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 1) + (i)* 2 * (cols - 2));
				}

				tempT.index[0] = (i - 1)*rows + j - 1;
				tempT.index[1] = (i)*rows + j - 1;
				tempT.index[2] = i*rows + j;
				indexArray.push_back(tempT);

				tempT.index[0] = (i - 1)*rows + j;
				tempT.index[1] = (i - 1)*rows + j - 1;
				tempT.index[2] = i * rows + j;
				indexArray.push_back(tempT);


			}
			else { // uneven row

				vertexInfo[i * rows + j].vertexNeighbors.push_back(i * rows + j - 1);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i - 1) * rows + j);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i - 1) * rows + j + 1);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i + 1) * rows + j);
				vertexInfo[i * rows + j].vertexNeighbors.push_back((i + 1) * rows + j + 1);
				vertexInfo[i * rows + j].vertexNeighbors.push_back(i * rows + j + 1);

				if (i > 1 && j > 1 && i < rows - 1 && j < cols - 2) {
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 2) + (i - 1) * 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 1) + (i - 1) * 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2) + (i - 1) * 2 * (cols - 2));

					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 - 1) + (i)* 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2) + (i)* 2 * (cols - 2));
					vertexInfo[i * rows + j].triangleNeighbors.push_back((j * 2 + 1) + (i)* 2 * (cols - 2));
				}

				tempT.index[0] = (i - 1)*rows + j;
				tempT.index[1] = (i)*rows + j - 1;
				tempT.index[2] = i*rows + j;
				indexArray.push_back(tempT);

				tempT.index[0] = (i - 1)*rows + j + 1;
				tempT.index[1] = (i - 1)*rows + j;
				tempT.index[2] = i*rows + j;
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
		(vertexArray.size() + 1000)*sizeof(vertex), vertexP, GL_STREAM_DRAW);

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

	vector<int> changedVertices;
	changedVertices.reserve(100);
	int changeCount = 0;

	int oldArraySize = vertexArray.size();
	int oldIndArraySize = indexArray.size();
	//MOVEMENT BETWEEN LAST FRAME AND THIS FRAME
	float pMove[3];
	pMove[0] = (p[0] - lp[0]);
	pMove[1] = (p[1] - lp[1]);
	pMove[2] = (p[2] - lp[2]);

	tempvec = glm::transpose(glm::make_mat4(orientation)) * glm::vec4(pMove[0], pMove[1], pMove[2], 1.0f);
	pMove[0] = tempvec.x;
	pMove[1] = tempvec.y;
	pMove[2] = tempvec.z;


	//cout << pMove[0] << " " << pMove[1] << " " << pMove[2] << endl;

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


	triangle* indexP;
	vertex* vertexP;

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

			changedVertices.push_back(i);
			changeCount++;

			success = true;
			/*
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
			*/
		}
	}

	changeCount = 0;

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

	//cout << pMove[0] << " " << pMove[1] << " " << pMove[2] << endl;

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
		beginning = currentRow * rows + startCol[j];
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

float Mesh::vecLenght(float vec[3]) {
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

bool Mesh::sortByXCord(const vertex &a, const vertex &b) {
	return a.x < b.x;
}

void Mesh::updateArea(int* changeList, int listSize) {
	//DECLARE VARIABLES
	float tempNorm1[3] = { 0.0f, 0.0f, 0.0f };
	float tempNorm2[3] = { 0.0f, 0.0f, 0.0f };

	static const float MIN_LENGTH = 0.03;
	static const float MAX_LENGTH = 0.01;

	float tempVec1[3], tempVec2[3], tempVec3[3];

	vertex tempV; vertexInf tempVI; triangle tempT;

	float vPoint1[3], vPoint2[3], vPoint3[3], vPoint4[3];

	int currVert = -1; int nVert = -1; int nTri = -1;

	int sharedNeighbor[2] = {-1, -1};
	//while (changeCount < listSize)

	//c == loop that handles current vertex of the vertexes that need updating
	for (int c = 0; c < listSize; c++) {
		currVert = changeList[c];

		//UPDATE NORMAL //////////////////////////////////////////////////////////////////////////////////////////////
		vertexArray[currVert].nx = 0.0f; vertexArray[currVert].ny = 0.0f; vertexArray[currVert].nz = 0.0f;
		//while (uN < vertexInfo[currVert].vertexNeighbors.size()) {
		//uN == loop that updates the normal of the current vertex
		for (int uN = 0; uN < vertexInfo[currVert].vertexNeighbors.size(); uN++) {

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

		

		//nT == loop that checks if the neighbors to currvert have any links other than the link to current vertex that are too long
		for (int nT = 0; nT < vertexInfo[currVert].vertexNeighbors.size(); nT++) {
			nVert = vertexInfo[currVert].vertexNeighbors[nT];

			

			for (int k = 0; k < vertexInfo[currVert].vertexNeighbors.size(); k++) {
				for (int j = 0; j < vertexInfo[nVert].vertexNeighbors.size(); j++){
					if (vertexInfo[currVert].vertexNeighbors[k] == vertexInfo[nVert].vertexNeighbors[j]){
						if (sharedNeighbor[0] == -1)
							sharedNeighbor[0] = vertexInfo[currVert].vertexNeighbors[k];
						else
							sharedNeighbor[1] = vertexInfo[currVert].vertexNeighbors[k];
					}
				}
			}

			vPoint1[0] = vertexArray[sharedNeighbor[0]].x;
			vPoint1[1] = vertexArray[sharedNeighbor[0]].y;
			vPoint1[2] = vertexArray[sharedNeighbor[0]].z;

			vPoint2[0] = vertexArray[sharedNeighbor[1]].x;
			vPoint2[1] = vertexArray[sharedNeighbor[1]].y;
			vPoint2[2] = vertexArray[sharedNeighbor[1]].z;

			vPoint3[0] = vertexArray[nVert].x;
			vPoint3[1] = vertexArray[nVert].y;
			vPoint3[2] = vertexArray[nVert].z;

			calculateVec(tempVec1, vPoint1, vPoint3);
			calculateVec(tempVec2, vPoint2, vPoint3);


			if (vecLenght(tempVec1) < MIN_LENGTH)
			{
				rmVertex(vPoint3, vPoint1, tempVec1, nVert, sharedNeighbor[0], currVert, &nT);
			}
			/*maybe if*/else if (vecLenght(tempVec2) < MIN_LENGTH)
			{
				rmVertex(vPoint3, vPoint1, tempVec2, nVert, sharedNeighbor[1], currVert, &nT);
			}
			sharedNeighbor[0] = -1;
			sharedNeighbor[1] = -1;
		}

		//cT = loop that checks if any of current vertex's links to its neighbors are too long
		for (int cT = 0; cT < vertexInfo[currVert].vertexNeighbors.size(); cT++){

		}


	}
}

void Mesh::addVertex(float* pA, float* pB, float* vecA2B, int currVert, int nVert, int currVertP, int* counter) {



}
//STILL NEED TO USE COUNTER DONT FORGET
bool Mesh::rmVertex(float* pA, float* pB, float* vecA2B, int currVert, int nVert, int currVertP, int* counter) {
	
	//vector<int>::iterator sharedNeighbor[2];
	int sharedNeighbor[2] = { -1, -1 };
	//vector<int>::iterator sharedTriNeighbor[2];
	int sharedTriNeighbor[2] = { -1, -1 };

	vertexArray[currVert].x = pA[0] + vecA2B[0];
	vertexArray[currVert].y = pA[1] + vecA2B[1];
	vertexArray[currVert].z = pA[2] + vecA2B[2];

	// find shared neighbors between currVert and nVert
	for (int k = 0; k < vertexInfo[currVert].vertexNeighbors.size(); k++) {
		for (int j = 0; j < vertexInfo[nVert].vertexNeighbors.size(); j++){
			if (vertexInfo[currVert].vertexNeighbors[k] == vertexInfo[nVert].vertexNeighbors[j]){
				if (sharedNeighbor[0] == -1)
					sharedNeighbor[0] = vertexInfo[currVert].vertexNeighbors[k];
				else
					sharedNeighbor[1] = vertexInfo[currVert].vertexNeighbors[k];
			}
			
			if (vertexInfo[currVert].triangleNeighbors[k] == vertexInfo[nVert].triangleNeighbors[j]){
				if (sharedTriNeighbor[0] == -1)
					sharedTriNeighbor[0] = vertexInfo[currVert].triangleNeighbors[k];
				else
					sharedTriNeighbor[1] = vertexInfo[currVert].triangleNeighbors[k];
			}
		}
	}
	
	
	// REMOVE THE TRIANGLES
	// remove the triangles from the first shared neighbor
	vertexInfo[sharedNeighbor[0]].triangleNeighbors.erase(remove(vertexInfo[sharedNeighbor[0]].triangleNeighbors.begin(), 
																  vertexInfo[sharedNeighbor[0]].triangleNeighbors.end(), 
																  sharedTriNeighbor[0]), vertexInfo[sharedNeighbor[0]].triangleNeighbors.end());

	vertexInfo[sharedNeighbor[0]].triangleNeighbors.erase(remove(vertexInfo[sharedNeighbor[0]].triangleNeighbors.begin(),
																  vertexInfo[sharedNeighbor[0]].triangleNeighbors.end(),
																  sharedTriNeighbor[1]), vertexInfo[sharedNeighbor[0]].triangleNeighbors.end());

	// remove the triangles from the second shared neighbor
	vertexInfo[sharedNeighbor[1]].triangleNeighbors.erase(remove(vertexInfo[sharedNeighbor[1]].triangleNeighbors.begin(),
														   vertexInfo[sharedNeighbor[1]].triangleNeighbors.end(),
														   sharedTriNeighbor[0]), vertexInfo[sharedNeighbor[1]].triangleNeighbors.end());

	vertexInfo[sharedNeighbor[1]].triangleNeighbors.erase(remove(vertexInfo[sharedNeighbor[1]].triangleNeighbors.begin(),
																  vertexInfo[sharedNeighbor[1]].triangleNeighbors.end(),
																  sharedTriNeighbor[1]), vertexInfo[sharedNeighbor[1]].triangleNeighbors.end());

	// remove the triangles from currVert
	vertexInfo[currVert].triangleNeighbors.erase(remove(vertexInfo[currVert].triangleNeighbors.begin(),
																  vertexInfo[currVert].triangleNeighbors.end(),
																  sharedTriNeighbor[0]), vertexInfo[currVert].triangleNeighbors.end());

	vertexInfo[currVert].triangleNeighbors.erase(remove(vertexInfo[currVert].triangleNeighbors.begin(),
														vertexInfo[currVert].triangleNeighbors.end(),
														sharedTriNeighbor[1]), vertexInfo[currVert].triangleNeighbors.end());

	// remove the triangles from nVert
	vertexInfo[nVert].triangleNeighbors.erase(remove(vertexInfo[nVert].triangleNeighbors.begin(),
														vertexInfo[nVert].triangleNeighbors.end(),
														sharedTriNeighbor[0]), vertexInfo[nVert].triangleNeighbors.end());

	vertexInfo[nVert].triangleNeighbors.erase(remove(vertexInfo[nVert].triangleNeighbors.begin(),
													 vertexInfo[nVert].triangleNeighbors.end(),
													 sharedTriNeighbor[1]), vertexInfo[nVert].triangleNeighbors.end());

	// remove the triangles from IndexArray
	indexArray[sharedTriNeighbor[0]].index[0] = 0;
	indexArray[sharedTriNeighbor[0]].index[1] = 0;
	indexArray[sharedTriNeighbor[0]].index[2] = 0;

	indexArray[sharedTriNeighbor[1]].index[0] = 0;
	indexArray[sharedTriNeighbor[1]].index[1] = 0;
	indexArray[sharedTriNeighbor[1]].index[2] = 0;

	// insert remaining triangles in nVert in currVert
	vertexInfo[currVert].triangleNeighbors.insert(vertexInfo[currVert].triangleNeighbors.end(), 
												  vertexInfo[nVert].triangleNeighbors.begin(), 
												  vertexInfo[nVert].triangleNeighbors.end());

	// insert non-shared neighbors in currVert
	for (int i = 0; i < vertexInfo[nVert].vertexNeighbors.size(); i++) {
		if (vertexInfo[nVert].vertexNeighbors[i] != currVert && vertexInfo[nVert].vertexNeighbors[i] != sharedNeighbor[0] && vertexInfo[nVert].vertexNeighbors[i] != sharedNeighbor[1])
		{
			//add nVerts neighbors to currverts neighbors
			vertexInfo[currVert].vertexNeighbors.push_back(vertexInfo[nVert].vertexNeighbors[i]);

			for (int j = 0; j < vertexInfo[vertexInfo[nVert].vertexNeighbors[i]].vertexNeighbors.size(); j++) {
				if (vertexInfo[vertexInfo[nVert].vertexNeighbors[i]].vertexNeighbors[j] == nVert) {
					vertexInfo[vertexInfo[nVert].vertexNeighbors[i]].vertexNeighbors[j] = currVert;

				}

			}
			//replace nVert in nVerts neighbors with currvert
			/*vertexInfo[vertexInfo[nVert].vertexNeighbors[i]].vertexNeighbors[
						*find(vertexInfo[vertexInfo[nVert].vertexNeighbors[i]].vertexNeighbors.begin(),
						vertexInfo[vertexInfo[nVert].vertexNeighbors[i]].vertexNeighbors.end(), nVert)] = currVert;*/
		}
	}

	// remove nVert from vertexNeighbors and currVert
	vertexInfo[currVert].vertexNeighbors.erase(remove(vertexInfo[currVert].vertexNeighbors.begin(), vertexInfo[currVert].vertexNeighbors.end(), nVert), vertexInfo[currVert].vertexNeighbors.end());
	vertexInfo[sharedNeighbor[0]].vertexNeighbors.erase(remove(vertexInfo[sharedNeighbor[0]].vertexNeighbors.begin(), vertexInfo[sharedNeighbor[0]].vertexNeighbors.end(), nVert), vertexInfo[sharedNeighbor[0]].vertexNeighbors.end());
	vertexInfo[sharedNeighbor[1]].vertexNeighbors.erase(remove(vertexInfo[sharedNeighbor[1]].vertexNeighbors.begin(), vertexInfo[sharedNeighbor[1]].vertexNeighbors.end(), nVert), vertexInfo[sharedNeighbor[1]].vertexNeighbors.end());

	// replace the nVert index in the triangleNeighbors of nVert with currVert 
	for (int i = 0; i < vertexInfo[nVert].triangleNeighbors.size(); i++) {
		for (int j = 0; j < 3; j++) {
			if (indexArray[vertexInfo[nVert].triangleNeighbors[i]].index[j] == nVert)
				indexArray[vertexInfo[nVert].triangleNeighbors[i]].index[j] = currVert;
		}
	}
	
	vertexArray[nVert].x = -1000;
	vertexArray[nVert].y = -1000;
	vertexArray[nVert].z = -1000;
	vertexInfo[nVert].triangleNeighbors.clear();
	vertexInfo[nVert].vertexNeighbors.clear();


	for (int i = 0; i < 2; i++) {

		if (vertexInfo[sharedNeighbor[i]].vertexNeighbors.size() < 3) {
			vertexInfo[vertexInfo[sharedNeighbor[i]].vertexNeighbors[0]].vertexNeighbors[
				*find(vertexInfo[vertexInfo[sharedNeighbor[i]].vertexNeighbors[0]].vertexNeighbors.begin(),
					  vertexInfo[vertexInfo[sharedNeighbor[i]].vertexNeighbors[0]].vertexNeighbors.end(), sharedNeighbor[i])] = vertexInfo[sharedNeighbor[i]].vertexNeighbors[1];

			vertexInfo[vertexInfo[sharedNeighbor[i]].vertexNeighbors[1]].vertexNeighbors[
				*find(vertexInfo[vertexInfo[sharedNeighbor[i]].vertexNeighbors[1]].vertexNeighbors.begin(),
					vertexInfo[vertexInfo[sharedNeighbor[i]].vertexNeighbors[1]].vertexNeighbors.end(), sharedNeighbor[i])] = vertexInfo[sharedNeighbor[i]].vertexNeighbors[0];

				if (sharedNeighbor[i] == currVertP)
					return false;
		}
	}

	return true;
}


void Mesh::calculateVec(float* newVec, float* a, float* b) {
	newVec[0] = a[0] - b[0];
	newVec[1] = a[1] - b[1];
	newVec[2] = a[2] - b[2];
}