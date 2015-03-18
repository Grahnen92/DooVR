#include "Mesh.h"
#include "time.h"
#include "math.h"
#include <algorithm>

using namespace std;

float vectorLength(vertex vertex1, vertex vertex2) {
	vertex vector;

	vector.x = vertex1.x - vertex2.x;
	vector.y = vertex1.y - vertex2.y;
	vector.z = vertex1.z - vertex2.z;

	return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}


bool sortByXCord(const vertex &a, const vertex &b) {
	return a.x < b.x;
}

Mesh::Mesh() {
	triangle tempT;
	vertex tempV;

	tempV.y = 0.0f;
	


	vertexArray.reserve(1000000);
	indexArray.reserve(1000000);
	//triangleList.reserve(1000000);

	/*
	for (float i = -5.f; i < 5; i++) {

	for (float j = -5.f; j < 5; j++) {

	tempV.x = i / 5.0f;
	tempV.y = j / 5.0f;
	vertexArray.push_back(tempV);

	}
	}
	*/
	
	triangle * indexP;
	vertex * vertexP;
	/*
	tempV.x = 1.0f;
	tempV.y = 1.0f;
	vertexArray.push_back(tempV);
	tempV.x = 1.0f;
	tempV.y = -1.0f;
	vertexArray.push_back(tempV);
	tempV.x = -1.0f;
	tempV.y = -1.0f;
	vertexArray.push_back(tempV);
	tempV.x = -1.0f;
	tempV.y = 1.0f;
	vertexArray.push_back(tempV);

	tempT.index1 = 1;
	tempT.index2 = 0;
	tempT.index3 = 3;
	indexArray.push_back(tempT);
	tempT.index1 = 3;
	tempT.index2 = 2;
	tempT.index3 = 1;
	indexArray.push_back(tempT);
	*/
	//hej
	
	for (int i = -10; i < 10; i++) {
		cout << fmod(i, sqrt(0.75f) * 2) << endl;

		for (int j = -10; j < 10; j++) {
			
			if (fmod(i, 2) != 0)
			{
				tempV.x = ((float)(j) + 0.5f)*0.2f;
				tempV.z = ((float)(i))*0.86602540378f*0.2f;
			}
			else
			{
				tempV.x = ((float)(j))*0.2f;
				tempV.z = ((float)(i))*0.86602540378f*0.2f;
			}
			tempV.nx = 0.0f;
			tempV.ny = 1.0f;
			tempV.nz = 0.0f;
			vertexArray.push_back(tempV);
		}
	}
	
	/*float i = -10.0f;
	float j = -10.0f;

	while (i < 10.0f)
	{
		while (j < 10.0f)
		{
			if (fmod(i, 2.0f) == 0)
			{
				tempV.x = i / 5.0f + 0.1f;
				tempV.z = j / 5.0f;

				j = 1.0f + 0.1f;
			}
			else
			{
				tempV.x = i / 5.0f;
				tempV.z = j / 5.0f;
			}
			tempV.nx = 0.0f;
			tempV.ny = 1.0f;
			tempV.nz = 0.0f;
			vertexArray.push_back(tempV);

			j = j + 1.0f;
		}
		i = i + 1.0f;
	}*/

	/*for (int i = 0; i < 19; i = i +1) {
		for (int j = 0; j < 19; j++) {

			tempT.index1 = i*20 + j;
			tempT.index2 = (i + 1) * 20 + j;
			tempT.index3 = i * 20 + (j + 1);
			indexArray.push_back(tempT);

			tempT.index1 = (i+1)*20 + j;
			tempT.index2 = (i + 2) * 20 + j;
			tempT.index3 = (i + 2) * 20 + (j + 1);
			indexArray.push_back(tempT); 

			tempT.index1 = (i + 1) * 20 + j;
			tempT.index2 = (i + 2) * 20 + j;
			tempT.index3 = (i + 2) * 20 + (j + 1);
			indexArray.push_back(tempT);

			tempT.index1 = (i + 1) * 20 + j;
			tempT.index2 = (i + 2) * 20 + j;
			tempT.index3 = (i + 2) * 20 + (j + 1);
			indexArray.push_back(tempT);
		}
	}*/

	for (int i = 1; i < 18; i = i + 2) {
		for (int j = 0; j < 19; j++) {

			tempT.index1 = i * 20 + j;
			tempT.index2 = (i - 1) * 20 + j;
				tempT.index3 =  (i - 1) * 20 + (j + 1);
			indexArray.push_back(tempT);

			tempT.index1 = i * 20 + j;
			tempT.index2 = (i + 1) * 20 + (j + 1);
			tempT.index3 = (i + 1) * 20 + j;
			indexArray.push_back(tempT);

			tempT.index1 = i * 20 + j;
			tempT.index2 = i * 20 + j + 1;
			tempT.index3 = (i + 1) * 20 + (j + 1) ;
			indexArray.push_back(tempT);

			tempT.index1 = i * 20 + j;
			tempT.index2 = (i - 1) * 20 + (j + 1);
			tempT.index3 = i * 20 + (j + 1);
			indexArray.push_back(tempT);
		}
	}


	//vertexP = vertexArray;
	/*
	int index1 = 0, index2 = 0;
	vertex handledVert, vert1, vert2;

	float length = 0, currentLength1 = 100.0f, currentLength2 = 100.0f;

	for (int i = 0; i < vertexArray.size(); i++)
	{
	handledVert = vertexArray[i];

	for (int j = 0; j < vertexArray.size(); j++)
	{
	if (j != i)
	{
	vert1 = vertexArray[j];

	length = vectorLength(handledVert, vert1);

	if (length < currentLength1)
	{
	currentLength2 = currentLength1;
	currentLength1 = length;

	index2 = index1;
	index1 = j;
	}
	else if (length < currentLength2)
	{
	currentLength2 = length;
	index2 = j;
	}
	}
	}

	tempT.index1 = i;
	tempT.index2 = index1;
	tempT.index3 = index2;
	indexArray.push_back(tempT);

	currentLength2 = 100.0f;
	currentLength1 = 100.0f;

	}

	*/

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
		6 * sizeof(GLfloat) + sizeof(int), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat) + sizeof(int), (void*)(3 * sizeof(GLfloat))); // normals


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


void Mesh::updateVertexArray(double x, double y) {
	triangle tempT;
	vertex tempV;

	tempV.z = 0;

	/*
	for (int i = -5; i <  5.0f; i++)
	{

	for (int j = dimNr; j < dimNr + 1.0f; j++)
	{
	tempV.x = i / 5.0f;
	tempV.y = j / 5.0f;
	vertexArray.push_back(tempV);

	}
	}

	dimNr = dimNr + 1.0f;
	*/
	triangle * indexP;
	vertex * vertexP;

	float xx = x;
	float yy = y;

	vertexArray[209].x = -xx;
	vertexArray[209].y = 2.0f;
	vertexArray[209].z = -yy;

	//std::sort(vertexArray.begin(), vertexArray.end(), sortByXCord);

	/*
	int index1 = 0, index2 = 0;
	vertex handledVert, vert1, vert2;

	float length = 0, currentLength1 = 100.0f, currentLength2 = 100.0f;

	indexArray.clear();

	for (int i = 0; i < vertexArray.size(); i++)
	{
	handledVert = vertexArray[i];

	for (int j = 0; j < vertexArray.size(); j++)
	{
	if (j != i)
	{
	vert1 = vertexArray[j];

	length = vectorLength(handledVert, vert1);

	if (length < currentLength1)
	{
	currentLength2 = currentLength1;
	currentLength1 = length;

	index2 = index1;
	index1 = j;
	}
	else if (length < currentLength2)
	{
	currentLength2 = length;
	index2 = j;
	}
	}
	}

	tempT.index1 = i;
	tempT.index2 = index1;
	tempT.index3 = index2;
	indexArray.push_back(tempT);

	currentLength2 = 100.0f;
	currentLength1 = 100.0f;
	}

	*/

	vertexP = &vertexArray[0];
	indexP = &indexArray[0];

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	//get buffer size
	int bufferSize; // offset in bytes
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	int sizeOfOriginalvertexArray = (bufferSize / sizeof(vertex));

	int addedVerticies = vertexArray.size() - sizeOfOriginalvertexArray;
	int offset = sizeOfOriginalvertexArray - 1;
	//cout << " added vertices: " << addedVerticies << " offset: " << offset << " size: " << sizeOfOriginalvertexArray << endl;

	// Present our vertex coordinates to OpenGL
	//glBufferData(GL_ARRAY_BUFFER, 
		//		 3*vertexArray.size() * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	

	 vertexP = (vertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertex)*vertexArray.size(),
										 GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

	 for (int i = 0; i < vertexArray.size(); i++) {
		 vertexP[i].x = vertexArray[i].x;
		 vertexP[i].y = vertexArray[i].y;
		 vertexP[i].z = vertexArray[i].z;
		 vertexP[i].nx = vertexArray[i].nx;
		 vertexP[i].ny = vertexArray[i].ny;
		 vertexP[i].nz = vertexArray[i].nz;
		 vertexP[i].index = i;
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
		6 * sizeof(GLfloat) + sizeof(int), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat) + sizeof(int), (void*)(3 * sizeof(GLfloat))); // normals

	glUnmapBuffer(GL_ARRAY_BUFFER);

	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex <indices to OpenGL
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	//	3 * indexArray.size()*sizeof(GLuint), indexP, GL_STREAM_DRAW);

	indexP = (triangle*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(triangle) * indexArray.size(), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

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

void Mesh::render() {
	glBindVertexArray(vao);
	//glColor3f(color.x, color.y, color.z);

	glDrawElements(GL_TRIANGLES, 3 * indexArray.size()*sizeof(GLuint), GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}
