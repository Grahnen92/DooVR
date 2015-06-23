#include "Box.h"

Box::Box(float x, float y, float z, float dX, float dY, float dZ)
{
	oType = 'B';
	position[0] = x;
	position[1] = y;
	position[2] = z;
	createBox(dX, dY, dZ);
}


Box::~Box(void)
{
	cout << "A box has died." << endl;
}

void Box::createBox(float xSize, float ySize, float zSize)
{

	GLfloat vertex_array_data[] = {
		//		Vertex								Normals										Texture  
		-xSize / 2.0f, -ySize / 2.0f,		 zSize / 2.0f, 0.0f, 0.0f, 1.0f,			 0.0f, 1.0f, //1 - 0
		xSize / 2.0f, -ySize / 2.0f,		 zSize / 2.0f, 0.0f, 0.0f, 1.0f,			 0.0f, 0.0f, //2 - 1
		xSize / 2.0f, ySize / 2.0f,			 zSize / 2.0f, 0.0f, 0.0f, 1.0f,			 1.0f, 0.0f, //3 - 2
		-xSize / 2.0f, ySize / 2.0f,		 zSize / 2.0f, 0.0f, 0.0f, 1.0f,			 1.0f, 1.0f, //4 - 3 

		-xSize / 2.0f, -ySize / 2.0f,		 -zSize / 2.0f, 0.0f, 0.0f, -1.0f,			 0.0f, 1.0f, //5 - 4 
		xSize / 2.0f, -ySize / 2.0f,		 -zSize / 2.0f, 0.0f, 0.0f, -1.0f,			 0.0f, 0.0f, //6 - 5
		xSize / 2.0f, ySize / 2.0f,			 -zSize / 2.0f, 0.0f, 0.0f, -1.0f,			 1.0f, 0.0f, //7 - 6 
		-xSize / 2.0f, ySize / 2.0f,		 -zSize / 2.0f, 0.0f, 0.0f, -1.0f,			 1.0f, 1.0f, //8 - 7


		-xSize / 2.0f, -ySize / 2.0f,		 zSize / 2.0f, 0.0f, -1.0f, 0.0f,			 0.0f, 1.0f, //1 - 8
		xSize / 2.0f, -ySize / 2.0f,		 zSize / 2.0f, 0.0f, -1.0f, 0.0f,			 0.0f, 0.0f, //2 - 9
		xSize / 2.0f, ySize / 2.0f,			 zSize / 2.0f, 0.0f, 1.0f, 0.0f,			 1.0f, 0.0f, //3 - 10
		-xSize / 2.0f, ySize / 2.0f,		 zSize / 2.0f, 0.0f, 1.0f, 0.0f,			 1.0f, 1.0f, //4 - 11

		-xSize / 2.0f, -ySize / 2.0f,		 -zSize / 2.0f, 0.0f, -1.0f, 0.0f,			 1.0f, 0.0f, //5 - 12
		xSize / 2.0f, -ySize / 2.0f,		 -zSize / 2.0f, 0.0f, -1.0f, 0.0f,			 1.0f, 1.0f, //6 - 13
		xSize / 2.0f, ySize / 2.0f,			 -zSize / 2.0f, 0.0f, 1.0f, 0.0f,			 0.0f, 0.0f, //7 - 14
		-xSize / 2.0f, ySize / 2.0f,		 -zSize / 2.0f, 0.0f, 1.0f, 0.0f,			 0.0f, 1.0f, //8 - 15


		-xSize / 2.0f, -ySize / 2.0f,		 zSize / 2.0f, -1.0f, 0.0f, 0.0f,			 1.0f, 1.0f, //1 - 16
		xSize / 2.0f, -ySize / 2.0f,		 zSize / 2.0f, 1.0f, 0.0f, 0.0f,			 0.0f, 0.0f, //2 - 17
		xSize / 2.0f, ySize / 2.0f,			 zSize / 2.0f, 1.0f, 0.0f, 0.0f,			 1.0f, 0.0f,  //3 - 18
		-xSize / 2.0f, ySize / 2.0f,		 zSize / 2.0f, -1.0f, 0.0f, 0.0f,			 0.0f, 1.0f,  //4 - 19

		-xSize / 2.0f, -ySize / 2.0f,		 -zSize / 2.0f, -1.0f, 0.0f, 0.0f,			 1.0f, 0.0f, //5 - 20
		xSize / 2.0f, -ySize / 2.0f,		 -zSize / 2.0f, 1.0f, 0.0f, 0.0f,			 0.0f, 1.0f, //6 - 21
		xSize / 2.0f, ySize / 2.0f,			 -zSize / 2.0f, 1.0f, 0.0f, 0.0f,			 1.0f, 1.0f, //7 - 22
		-xSize / 2.0f, ySize / 2.0f,		 -zSize / 2.0f, -1.0f, 0.0f, 0.0f,			 0.0f, 0.0f, //8 - 23
	};

	static const GLuint index_array_data[] = {
		0, 1, 2, //Z-positiv/nära
		0, 2, 3, //
		7, 5, 4, //Z-negativ/borta
		7, 6, 5, //
		8, 12, 9, //Y-negativ/vänster
		13, 9, 12, //
		10, 14, 11, //Y-positiv/höger
		11, 14, 15, //
		17, 21, 18, //X-positiv/ovan
		18, 21, 22, //
		16, 19, 23, //X-negativ/under // 0 3 7
		20, 16, 23, //  
	};
	nverts = 24;
	ntris = 12;

	vertexarray = new GLfloat[8 * nverts];
	indexarray = new GLuint[3 * ntris];
	for (int i = 0; i<8 * nverts; i++) {
		vertexarray[i] = vertex_array_data[i];
	}
	for (int i = 0; i<3 * ntris; i++) {
		indexarray[i] = index_array_data[i];
	}

	// Generate one vertex array object (VAO) and bind it
	glGenVertexArrays(1, &(vao));
	glBindVertexArray(vao);

	// Generate two buffer IDs
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &indexbuffer);

	// Activate the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Present our vertex coordinates to OpenGL
	glBufferData(GL_ARRAY_BUFFER,
		8 * nverts * sizeof(GLfloat), vertexarray, GL_STATIC_DRAW);
	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
	glEnableVertexAttribArray(1); // Normals
	glEnableVertexAttribArray(2); // Texture coordinates
	


	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 floats (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3 or 6 floats (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // texcoords
	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex indices to OpenGL
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		3 * ntris*sizeof(GLuint), indexarray, GL_STATIC_DRAW);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the index buffer while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Box::render()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3 * ntris, GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}