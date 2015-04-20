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

void crossProd( float normal[3], float* vec1, float* vec2) {
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

	scaleF = 1.0f / (rows *2)* 10.0f;

	tempV.y = 0.0f;
	tempV.nx = 0.0f;
	tempV.ny = 1.0f;
	tempV.nz = 0.2f;
	
	// Place vertices
	for (int i = -rows / 2; i < rows / 2; i++) {
		//cout << fmod(i, sqrt(0.75f) * 2) << endl;

		for (int j = -cols / 2; j < cols / 2; j++) {
			
			if (i%2 != 0){
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
		for (int j = 1; j < cols -1 ; j++) {

			//if (i != 0 && j !=0 && i != rows - 1 && j != cols - 1) {
			if ( i % 2 == 0) {

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
		(vertexArray.size() + 1000 )*sizeof(vertex), vertexP, GL_STREAM_DRAW);

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
				 (indexArray.size() + 1000)*sizeof(triangle), indexP, GL_STREAM_DRAW);

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
			
			changedVertices[changeCount] = i;
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

	while (changedVertices[changeCount] != 0) {
		updateArea(changedVertices[changeCount]);
		changeCount++;
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

void Mesh::test(float bRad) {
	glm::vec4 tempvec;
	vertex tempV;

	int changedVertices[10000] = { 0 };
	int changeCount = 0;

	int oldArraySize = vertexArray.size();
	int oldIndArraySize = indexArray.size();
	//MOVEMENT BETWEEN LAST FRAME AND THIS FRAME


	//cout << pMove[0] << " " << pMove[1] << " " << pMove[2] << endl;

	tempV.z = 0;
	vertex point;
	point.x = 0.0f;
	point.y = 0.0f;
	point.z = 0.0f;

	int testPoint = 5051;


	triangle* indexP;
	vertex* vertexP;

	bool success = false;


	int startRow = -1;
	int endRow = -1;
	int prevRow = -1;
	vector<int> startCol;	// first edited column on row
	vector<int> endCol;		// last edited column on row

	for (int i = 0; i < vertexArray.size(); i++) {
		if ( testPoint == i) {

			
			vertexArray[i].y += 0.001f;
			

			changedVertices[changeCount] = i;
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

	while (changedVertices[changeCount] != 0)
	{
		updateArea(changedVertices[changeCount]);
		changeCount++;
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

void Mesh::updateArea(int currVert) {
	//DECLARE VARIABLES
	int needsUpdate[8] = { -1, -1, -1, -1, -1, -1, -1, -1};

	float tempNorm1[3] = { 0.0f, 0.0f, 0.0f };
	float tempNorm2[3] = { 0.0f, 0.0f, 0.0f };


	float tempVec1[3], tempVec2[3];

	vertex tempV; vertexInf tempVI; triangle tempT;

	float vPoint1[3],  vPoint2[3], vPoint3[3];

	const float MAX_LENGTH = 0.1f;
	const float MIN_LENGTH = 0.01f;

	int neighbor1 = -1; int neighbor2 = -1;
	int neighborTri1 = -1; int neighborTri2 = -1;
	int neighborTri11 = -1; int neighborTri21 = -1;
	int neighborTri12 = -1; int neighborTri22 = -1;

	int triPos = -2;
	int vertPos;

	int count1 = 0; int count2 = 0;
	int t1 = 0; int t2 = 0;
	int erase11 = -1; int erase12 = -1;
	int erase21 = -1; int erase22 = -1;

	bool isNeighbor1Tri = false; // true if neighbor1 is part of neighbor triangle 1

	/*
	vertexArray[vertexInfo[currVert].vertexNeighbors[0]].y += 0.001f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[1]].y += 0.001f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[2]].y += 0.001f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[3]].y += 0.001f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[4]].y += 0.001f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[5]].y += 0.001f;

	vertexArray[vertexInfo[currVert].vertexNeighbors[0]].ny = 0.0f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[1]].ny = 0.0f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[2]].ny = 0.0f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[3]].ny = 0.0f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[4]].ny = 0.0f;
	vertexArray[vertexInfo[currVert].vertexNeighbors[5]].ny = 0.0f;
	*/

	//UPDATE NORMAL //////////////////////////////////////////////////////////////////////////////////////////////
	
	vertexArray[currVert].nx = 0.0f; vertexArray[currVert].ny = 0.0f; vertexArray[currVert].nz = 0.0f;

	while (count1 < vertexInfo[currVert].triangleNeighbors.size()  ) {
		triPos = vertexInfo[currVert].triangleNeighbors[count1];

		vPoint1[0] = vertexArray[indexArray[triPos].index[0]].x;
		vPoint1[1] = vertexArray[indexArray[triPos].index[0]].y;
		vPoint1[2] = vertexArray[indexArray[triPos].index[0]].z;

		vPoint2[0] = vertexArray[indexArray[triPos].index[1]].x;
		vPoint2[1] = vertexArray[indexArray[triPos].index[1]].y;
		vPoint2[2] = vertexArray[indexArray[triPos].index[1]].z;

		vPoint3[0] = vertexArray[indexArray[triPos].index[2]].x;
		vPoint3[1] = vertexArray[indexArray[triPos].index[2]].y;
		vPoint3[2] = vertexArray[indexArray[triPos].index[2]].z;

		calculateVec(tempVec1, vPoint2, vPoint1);
		calculateVec(tempVec2, vPoint3, vPoint1);

		crossProd(tempNorm1, tempVec1, tempVec2);

		normVec(tempNorm1);

		tempNorm2[0] += tempNorm1[0];
		tempNorm2[1] += tempNorm1[1];
		tempNorm2[2] += tempNorm1[2];

		count1++;

	}

	tempNorm2[0] = tempNorm2[0] / (count1 - 1);
	tempNorm2[1] = tempNorm2[1] / (count1 - 1);
	tempNorm2[2] = tempNorm2[2] / (count1 - 1);

	vertexArray[currVert].nx = tempNorm2[0];
	vertexArray[currVert].ny = tempNorm2[1];
	vertexArray[currVert].nz = tempNorm2[2];

	// CHECK IF RETRIANGULATION IS NEEDED
	count1 = 0;
	count2 = 0;
	//vertPos = vertexInfo[currVert].vertexNeighbors[count1];
	while (count1 < vertexInfo[currVert].vertexNeighbors.size()) {
		vertPos = vertexInfo[currVert].vertexNeighbors[count1];
		vPoint1[0] = vertexArray[currVert].x;
		vPoint1[1] = vertexArray[currVert].y;
		vPoint1[2] = vertexArray[currVert].z;

		vPoint2[0] = vertexArray[vertPos].x;
		vPoint2[1] = vertexArray[vertPos].y;
		vPoint2[2] = vertexArray[vertPos].z;

		calculateVec(tempVec1, vPoint2, vPoint1);

		if (vecLenght(tempVec1) > MAX_LENGTH) {
			//needsUpdate[count2] = vertPos;

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////TEST
			//FINDING SHARED VERTEX NEIGHBORS AND TRIANGLE NEIGHBORS
			for (int i = 0; i < vertexInfo[currVert].vertexNeighbors.size(); i++) {
				for (int j = 0; j < vertexInfo[vertPos].vertexNeighbors.size(); j++) {
					if (vertexInfo[currVert].vertexNeighbors[i] == vertexInfo[vertPos].vertexNeighbors[j]) {
						if (neighbor1 == -1){
							neighbor1 = vertexInfo[currVert].vertexNeighbors[i];
						} else {
							neighbor2 = vertexInfo[currVert].vertexNeighbors[i];
							//break;
						}
					}

					if (vertexInfo[currVert].triangleNeighbors[i] == vertexInfo[vertPos].triangleNeighbors[j]) {			
						if (neighborTri1 == -1){
							neighborTri1 = vertexInfo[currVert].triangleNeighbors[i];
						} else {
							neighborTri2 = vertexInfo[currVert].triangleNeighbors[i];
							//break;
						}
					}
				}
			}
			

			//CREATE NEW VERTEX AND TRIANGLES AND LINK THEM/////////////////////////////////////////////////////////
			tempV.x = vPoint1[0] + tempVec1[0] / 2.0f;
			tempV.y = vPoint1[1] + tempVec1[1] / 2.0f;
			tempV.z = vPoint1[2] + tempVec1[2] / 2.0f;
			tempV.nx = vertexArray[currVert].nx;
			tempV.ny = vertexArray[currVert].ny;
			tempV.nz = vertexArray[currVert].nz;
			vertexArray.push_back(tempV);

			/*
			tempT.index[0] = vertexArray.size() - 1;
			tempT.index[1] = neighbor1;
			tempT.index[2] = vertPos;
			indexArray.push_back(tempT);
			tempT.index[0] = vertexArray.size() - 1;
			tempT.index[1] = vertPos;
			tempT.index[2] = neighbor2;
			indexArray.push_back(tempT);
			*/

			tempT.index[0] = indexArray[neighborTri1].index[0];
			tempT.index[1] = indexArray[neighborTri1].index[1];
			tempT.index[2] = indexArray[neighborTri1].index[2];
			indexArray.push_back(tempT);
			tempT.index[0] = indexArray[neighborTri2].index[0];
			tempT.index[1] = indexArray[neighborTri2].index[1];
			tempT.index[2] = indexArray[neighborTri2].index[2];
			indexArray.push_back(tempT);

			// replace the vertPos index in the existing triangles
			for (int i = 0; i < 3; i++) {
				if (indexArray[neighborTri1].index[i] == vertPos) {
					indexArray[neighborTri1].index[i] = vertexArray.size() - 1;

				} else if (indexArray[neighborTri1].index[i] == neighbor1) {
					isNeighbor1Tri = true;
				}

				if (indexArray[neighborTri2].index[i] == vertPos)
					indexArray[neighborTri2].index[i] = vertexArray.size() - 1;

				if (indexArray[indexArray.size() - 2].index[i] == currVert)
					indexArray[indexArray.size() - 2].index[i] = vertexArray.size() - 1;

				if (indexArray[indexArray.size() - 1].index[i] == currVert)
					indexArray[indexArray.size() - 1].index[i] = vertexArray.size() - 1;

			}
			////////////////////////////////////////////////////////////////////////////////////////////

			//BINDING NEW VERTEX ///////////////////////////////////////////////////////////////////
			tempVI.triangleNeighbors.push_back(neighborTri1);
			tempVI.triangleNeighbors.push_back(neighborTri2);
			tempVI.triangleNeighbors.push_back(indexArray.size() - 1);
			tempVI.triangleNeighbors.push_back(indexArray.size() - 2);

			tempVI.vertexNeighbors.push_back(currVert);
			tempVI.vertexNeighbors.push_back(vertPos);
			tempVI.vertexNeighbors.push_back(neighbor1);
			tempVI.vertexNeighbors.push_back(neighbor2);

			vertexInfo.push_back(tempVI);
			tempVI.triangleNeighbors.clear();
			tempVI.vertexNeighbors.clear();
			////////////////////////////////////////////////////////////////////////////////////////////

			//UPDATING EXISTING VERTICES BINDINGS////////////////////////////////////////////////////////////////

			//current vertex
			vertexInfo[currVert].vertexNeighbors[count1] = vertexArray.size() - 1;

			//shared neighbors
			if (isNeighbor1Tri)	{
				vertexInfo[neighbor1].triangleNeighbors.push_back(indexArray.size() - 2);
				vertexInfo[neighbor1].vertexNeighbors.push_back(vertexArray.size() - 1);

				vertexInfo[neighbor2].triangleNeighbors.push_back(indexArray.size() - 1);
				vertexInfo[neighbor2].vertexNeighbors.push_back(vertexArray.size() - 1);
			} else {
				vertexInfo[neighbor1].triangleNeighbors.push_back(indexArray.size() - 1);
				vertexInfo[neighbor1].vertexNeighbors.push_back(vertexArray.size() - 1);

				vertexInfo[neighbor2].triangleNeighbors.push_back(indexArray.size() - 2);
				vertexInfo[neighbor2].vertexNeighbors.push_back(vertexArray.size() - 1);
			}

			//current neighbor

			for (int i = 0; i < vertexInfo[vertPos].triangleNeighbors.size(); i++) {
				if (vertexInfo[vertPos].triangleNeighbors[i] == neighborTri1) {
					vertexInfo[vertPos].triangleNeighbors[i] = indexArray.size() - 2;
				} else if (vertexInfo[vertPos].triangleNeighbors[i] == neighborTri2) {
					vertexInfo[vertPos].triangleNeighbors[i] = indexArray.size() - 1;
				}
			}

			for (int i = 0; i < vertexInfo[vertPos].vertexNeighbors.size(); i++) {
				if (vertexInfo[vertPos].vertexNeighbors[i] == currVert)
					vertexInfo[vertPos].vertexNeighbors[i] = vertexArray.size() - 1;
			}
		
			//count2++;
		}
		//EDGE TOO SMALL /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (vecLenght(tempVec1) < MIN_LENGTH) {

			//FINDING SHARED VERTEX NEIGHBORS
			for (int i = 0; i < vertexInfo[currVert].vertexNeighbors.size(); i++) {
				for (int j = 0; j < vertexInfo[vertPos].vertexNeighbors.size(); j++) {
					if (vertexInfo[currVert].vertexNeighbors[i] == vertexInfo[vertPos].vertexNeighbors[j]) {
						if (neighbor1 == -1){
							neighbor1 = vertexInfo[currVert].vertexNeighbors[i];
						}
						else {
							neighbor2 = vertexInfo[currVert].vertexNeighbors[i];
							//break;
						}
					}
				}
			}
			//FINDING SHARED TRIANGLE NEIGHBORS
			for (int i = 0; i < vertexInfo[currVert].triangleNeighbors.size(); i++) {
				for (int j = 0; j < vertexInfo[vertPos].triangleNeighbors.size(); j++) {
					if (vertexInfo[currVert].triangleNeighbors[i] == vertexInfo[vertPos].triangleNeighbors[j]) {
						if (neighborTri1 == -1){
							neighborTri1 = vertexInfo[currVert].triangleNeighbors[i];
							
							erase11 = i;//vertexInfo[currVert].triangleNeighbors.erase[i];
							erase12 = j;//vertexInfo[vertPos].triangleNeighbors.erase[j];
						}
						else {
							neighborTri2 = vertexInfo[currVert].triangleNeighbors[i];
							erase21 = i;//vertexInfo[currVert].triangleNeighbors.erase[i];
							erase22 = j;//vertexInfo[vertPos].triangleNeighbors.erase[j];
						}
					}
				}
			}

			if (erase11 > erase21){ 
				vertexInfo[currVert].triangleNeighbors.erase(vertexInfo[currVert].triangleNeighbors.begin() + erase11);
				vertexInfo[currVert].triangleNeighbors.erase(vertexInfo[currVert].triangleNeighbors.begin() + erase21);
			}
			else	{
				vertexInfo[currVert].triangleNeighbors.erase(vertexInfo[currVert].triangleNeighbors.begin() + erase21);
				vertexInfo[currVert].triangleNeighbors.erase(vertexInfo[currVert].triangleNeighbors.begin() + erase11);

			}
			if (erase12 > erase22) {
				vertexInfo[vertPos].triangleNeighbors.erase(vertexInfo[vertPos].triangleNeighbors.begin() + erase12);
				vertexInfo[vertPos].triangleNeighbors.erase(vertexInfo[vertPos].triangleNeighbors.begin() + erase22);
			}
			else
			{
				vertexInfo[vertPos].triangleNeighbors.erase(vertexInfo[vertPos].triangleNeighbors.begin() + erase22);
				vertexInfo[vertPos].triangleNeighbors.erase(vertexInfo[vertPos].triangleNeighbors.begin() + erase12);
			}
			

			/*
			//NEIGHBOR1 TRIANGLES THAT NEED CHANGING
			for (int i = 0; i < vertexInfo[neighbor1].triangleNeighbors.size(); i++) {
				for (int j = 0; j < vertexInfo[vertPos].triangleNeighbors.size(); j++) {
					if (vertexInfo[neighbor1].triangleNeighbors[i] == vertexInfo[vertPos].triangleNeighbors[j]) {
						neighborTri11 = vertexInfo[neighbor1].triangleNeighbors[i];
					}
				}
				for (int j = 0; j < vertexInfo[currVert].triangleNeighbors.size(); j++) {
					if (vertexInfo[neighbor1].triangleNeighbors[i] == vertexInfo[currVert].triangleNeighbors[j]) {
						neighborTri12 = vertexInfo[neighbor1].triangleNeighbors[i];
					}
				}
			}
			//NEIGHBOR2 TRIANGLES THAT NEED CHANGING
			for (int i = 0; i < vertexInfo[neighbor2].triangleNeighbors.size(); i++) {
				for (int j = 0; j < vertexInfo[vertPos].triangleNeighbors.size(); j++) {
					if (vertexInfo[neighbor2].triangleNeighbors[i] == vertexInfo[vertPos].triangleNeighbors[j]) {
						neighborTri21 = vertexInfo[neighbor2].triangleNeighbors[i];
					}
				}
				for (int j = 0; j < vertexInfo[currVert].triangleNeighbors.size(); j++) {
					if (vertexInfo[neighbor2].triangleNeighbors[i] == vertexInfo[currVert].triangleNeighbors[j]) {
						neighborTri22 = vertexInfo[neighbor2].triangleNeighbors[i];
					}
				}
			}
			*/

			vertexArray[currVert].x = vPoint1[0] + tempVec1[0] / 2.0f;
			vertexArray[currVert].y = vPoint1[1] + tempVec1[1] / 2.0f;
			vertexArray[currVert].z = vPoint1[2] + tempVec1[2] / 2.0f;
			
			indexArray[neighborTri1].index[0] = -1;
			indexArray[neighborTri1].index[1] = -1;
			indexArray[neighborTri1].index[2] = -1;

			indexArray[neighborTri2].index[0] = -1;
			indexArray[neighborTri2].index[1] = -1;
			indexArray[neighborTri2].index[2] = -1;

			cout << neighborTri2 << endl;
			
			for (int i = 0; i < vertexInfo[vertPos].triangleNeighbors.size(); i++)
			{
				vertexInfo[currVert].triangleNeighbors.push_back(vertexInfo[vertPos].triangleNeighbors[i]);

				for (int j = 0; j < 3; j++)
				{
					if (indexArray[vertexInfo[vertPos].triangleNeighbors[i]].index[j] == vertPos)
					{
						indexArray[vertexInfo[vertPos].triangleNeighbors[i]].index[j] = currVert;
					}
				}
			}

			for (int i = 0; i < vertexInfo[vertPos].vertexNeighbors.size(); i++)
			{
				if (vertexInfo[vertPos].vertexNeighbors[i] != neighbor1 && vertexInfo[vertPos].vertexNeighbors[i] != neighbor2 && vertexInfo[vertPos].vertexNeighbors[i] != currVert)
				{
					vertexInfo[currVert].vertexNeighbors.push_back(vertexInfo[vertPos].vertexNeighbors[i]);

					for (int j = 0; j < vertexInfo[vertexInfo[vertPos].vertexNeighbors[i]].vertexNeighbors.size(); j++ )
					{
						if (vertexInfo[vertexInfo[vertPos].vertexNeighbors[i]].vertexNeighbors[j] == vertPos)
						{
							vertexInfo[vertexInfo[vertPos].vertexNeighbors[i]].vertexNeighbors[j] = currVert;
						}
					}
				}
			}
			//REMOVE LINKS FROM NEIGHBOR1
			for (int i = 0; i < vertexInfo[neighbor1].vertexNeighbors.size(); i++)
			{
				if (vertexInfo[neighbor1].vertexNeighbors[i] == vertPos)
				{
					erase11 = i;
				}

				if (vertexInfo[neighbor1].triangleNeighbors[i] == neighborTri1)
				{
					erase22 = i;
				}
				else if (vertexInfo[neighbor1].triangleNeighbors[i] == neighborTri2)
				{
					erase22 = i;
				}
			}
			vertexInfo[neighbor1].vertexNeighbors.erase(vertexInfo[neighbor1].vertexNeighbors.begin() + erase11);
			vertexInfo[neighbor1].triangleNeighbors.erase(vertexInfo[neighbor1].triangleNeighbors.begin() + erase22);

			//REMOVE LINKS FROM NEIGHBOR2
			for (int i = 0; i < vertexInfo[neighbor2].vertexNeighbors.size(); i++)
			{
				if (vertexInfo[neighbor2].vertexNeighbors[i] == vertPos)
				{
					erase11 = i;
				}

				if (vertexInfo[neighbor2].triangleNeighbors[i] == neighborTri1)
				{
					erase22 = i;
				}
				else if (vertexInfo[neighbor2].triangleNeighbors[i] == neighborTri2)
				{
					erase22 = i;
				}
			}
			vertexInfo[neighbor1].vertexNeighbors.erase(vertexInfo[neighbor1].vertexNeighbors.begin() + erase11);
			vertexInfo[neighbor1].triangleNeighbors.erase(vertexInfo[neighbor1].triangleNeighbors.begin() + erase22);

			vertexArray[vertPos].x = 0;
			vertexArray[vertPos].y = 0;
			vertexArray[vertPos].z = 0;
			vertexArray[vertPos].nx = 0;
			vertexArray[vertPos].ny = 0;
			vertexArray[vertPos].nz = 0;
			vertexInfo[vertPos].triangleNeighbors.clear();
			vertexInfo[vertPos].vertexNeighbors.clear();

			vertexInfo[currVert].vertexNeighbors.erase(vertexInfo[currVert].vertexNeighbors.begin() + count1);
			count1--;
		}

		neighbor1 = -1;
		neighbor2 = -1;
		neighborTri1 = -1;
		neighborTri2 = -1;
		isNeighbor1Tri = false;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////TEST
		count1++;
		
	}

	///////////////////////////////TEST
	/*
	count2 = 0;

	while (needsUpdate[count2] != -1)
	{
		
		while (vertexInfo[currVert].vertexNeighbors[t1] != -1 && t1 < 8)
		{
			while (vertexInfo[needsUpdate[count2]].vertexNeighbors[t1] != -1 && t2 < 8)
			{
				if (vertexInfo[currVert].vertexNeighbors[t1] = vertexInfo[needsUpdate[count2]].vertexNeighbors[t1])
				{
					if (neighbor1 == -1)
						neighbor1 = vertexInfo[currVert].vertexNeighbors[t1];
					else
					{
						neighbor2 = vertexInfo[currVert].vertexNeighbors[t1];
						//break;
					}
				}

				t2++;
			}
			t2 = 0;
			t1++;
		}

		//FIRST EDGE THAT NEEDS UPDATE

		t2 = count2 - 1;
		if (count2 > 0)
		{
			while (t2 >= 0)
			{
				
				if (needsUpdate[t2] == neighbor1 || needsUpdate[t2] == neighbor2)
				{
					//NEIGHBORING VERTICES HAS BEEN UPDATED

				}
				else
				{
					//NO NEIGHBORING VERTICES HAS BEEN UPDATED
					vertexArray.push_back();
					vertexInfo.push_back();

				}
				t2--;

			}
		}
		else
		{
			//FIRST VERTEX BEING UPDATED

		}

		lastNeighbor1 = neighbor1;
		lastNeighbor2 = neighbor2;
		neighbor1 = -1;
		neighbor2 = -1;

		count2++;
	}
	*/

}


void Mesh::calculateVec(float* newVec, float* a, float* b) {
	newVec[0] = a[0] - b[0];
	newVec[1] = a[1] - b[1];
	newVec[2] = a[2] - b[2];
}
