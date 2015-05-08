#include "hexBox.h"

hexBox::hexBox(glm::vec3 _pos, glm::vec3 _dim)
{
	position[0] = _pos.x;
	position[1] = _pos.y;
	position[2] = _pos.z;
	dim = _dim;

	createhexBox(_dim.x, _dim.y, _dim.z);
}


hexBox::~hexBox(void)
{
	cout << "A box has died." << endl;
}

void hexBox::createhexBox(float xSize, float ySize, float zSize)
{

	GLfloat vertex_array_data[] = {
		//		Vertex								Normals										Texture  
		//top
		-0.05f, 0.5f, 0.086f,					0.0f, 1.0f, 0.0f,							0.3f , 0.06f,
		0.05f, 0.5f, 0.086f,					0.0f, 1.0f, 0.0f,							0.7f, 0.06f,
		0.10f, 0.5f, 0.0f,						0.0f, 1.0f, 0.0f,							0.9f, 0.2f,
		0.05f, 0.5f, -0.086f,					0.0f, 1.0f, 0.0f,							0.7f, 0.38f,
		-0.05f, 0.5f, -0.086f,					0.0f, 1.0f, 0.0f,							0.3f, 0.38f,
		-0.1f, 0.5f, 0.0f,						0.0f, 1.0f, 0.0f,							0.09f, 0.22f,
		0.0f, 0.5f, 0.0f,						0.0f, 1.0f, 0.0f,							0.5f, 0.22f,
		//bottom
		-0.05f, -0.5f, 0.086f,					0.0f, -1.0f, 0.0f,							0.3f, 0.65f,
		0.05f, -0.5f, 0.086f,					0.0f, -1.0f, 0.0f,							0.7f, 0.65f,
		0.10f, -0.5f, 0.0f,						0.0f, -1.0f, 0.0f,							0.9f, 0.81f,
		0.05f, -0.5f, -0.086f,					0.0f, -1.0f, 0.0f,							0.7f, 0.97f,
		-0.05f, -0.5f, -0.086f,					0.0f, -1.0f, 0.0f,							0.3f, 0.97f,
		-0.1f, -0.5f, 0.0f,						0.0f, -1.0f, 0.0f,							0.09f, 0.81f,
		0.0f, -0.5f, 0.0f,						0.0f, -1.0f, 0.0f,							0.5f, 0.81f
		//sides
		- 0.05f, 0.5f, 0.086f,					0.0f, 0.0f, 1.0f,							0.3f, 0.06f,
		0.05f, 0.5f, 0.086f,					0.0f, 0.0f, 1.0f,							0.7f, 0.06f,
		0.10f, 0.5f, 0.0f,						1.0f, 0.0f, 0.0f,							 0.9f, 0.2f,
		0.05f, 0.5f, -0.086f,					0.0f, 0.0f, -1.0f,							0.7f, 0.38f,
		-0.05f, 0.5f, -0.086f,					0.0f, 0.0f, -1.0f,							0.3f, 0.38f,
		-0.1f, 0.5f, 0.0f,						-1.0f, 0.0f, 0.0f,							0.09f, 0.22f,

		-0.05f, -0.5f, 0.086f,					0.0f, 0.0f, 1.0f,							0.3f, 0.65f,
		0.05f, -0.5f, 0.086f,					0.0f, 0.0f, 1.0f,							0.7f, 0.65f,
		0.10f, -0.5f, 0.0f,						1.0f, 0.0f, 0.0f,							0.9f, 0.81f,
		0.05f, -0.5f, -0.086f,					0.0f, 0.0f, -1.0f,							0.7f, 0.97f,
		-0.05f, -0.5f, -0.086f,					0.0f, 0.0f, -1.0f,							0.3f, 0.97f,
		-0.1f, -0.5f, 0.0f,						-1.0f, 0.0f, 0.0f,							0.09f, 0.81f,
	};

	static const GLuint index_array_data[] = {
		//top
		6, 1, 0,
		6, 2, 1,
		6, 3, 2,
		6, 4, 3,
		6, 5, 4,
		6, 0, 5,
		//bottom
		13, 7, 8,
		13, 8, 9,
		13, 9, 10,
		13, 10, 11,
		13, 11, 12,
		13, 12, 7,
		//sides
		11, 10, 4,
		4, 10, 3,

		12, 11, 5,
		5, 11, 4,

		7, 12, 0,
		0, 12, 5,

		8, 7, 1,
		1, 17, 0,

		9, 8, 2,
		2, 8, 1,

		10, 9, 3,
		3, 9, 2,
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

void hexBox::render()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3 * ntris, GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}

void hexBox::display(ostream& os) const
{
	os << "Shape: Box" << endl;
	os << "Dimensions: " << dim.x << ", " << dim.y << " ," << dim.z << endl;
}