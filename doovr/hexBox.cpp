#include "hexBox.h"

hexBox::hexBox(glm::vec3 _pos, float r, float h)
{
	oType = 'H';
	function = -1;
	position[0] = _pos.x;
	position[1] = _pos.y;
	position[2] = _pos.z;
	height = h;
	radius = r;


	GLfloat vertex_array_data[] = {
		//						Vertex																Normals										Texture  
		//top
		-radius/2.0f + _pos.x,		height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, 1.0f, 0.0f,								 0.3f, 0.65f,
		radius/2.0f + _pos.x,		height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, 1.0f, 0.0f,								 0.7f, 0.65f,
		radius + _pos.x,			height/2.0f + _pos.y,	0.0f + _pos.z,					 0.0f, 1.0f, 0.0f,								 0.9f, 0.81f,
		radius/2.0f + _pos.x,		height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, 1.0f, 0.0f,								 0.7f, 0.97f,
		-radius/2.0f + _pos.x,		height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, 1.0f, 0.0f,								 0.3f, 0.97f,
		-radius + _pos.x,			height/2.0f + _pos.y,	0.0f + _pos.z,					 0.0f, 1.0f, 0.0f,								 0.09f, 0.81f,
		0.0f + _pos.x,				height/2.0f + _pos.y,	0.0f + _pos.z,					 0.0f, 1.0f, 0.0f,								 0.5f, 0.81f,
		//bottom
		-radius/2.0f + _pos.x,		-height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, -1.0f, 0.0f,								 0.3f, 0.65f,
		0.05f + _pos.x,				-height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, -1.0f, 0.0f,								 0.7f, 0.65f,
		radius + _pos.x,			-height/2.0f + _pos.y,	0.0f + _pos.z,					 0.0f, -1.0f, 0.0f,								 0.9f, 0.81f,
		0.05f + _pos.x,				-height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, -1.0f, 0.0f,								 0.7f, 0.97f,
		-0.05f + _pos.x,			-height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, -1.0f, 0.0f,								 0.3f, 0.97f,
		-0.1f + _pos.x,				-height/2.0f + _pos.y,	0.0f + _pos.z,					 0.0f, -1.0f, 0.0f,								 0.09f, 0.81f,
		0.0f + _pos.x,				-height/2.0f + _pos.y,	0.0f + _pos.z,					 0.0f, -1.0f, 0.0f,								 0.5f, 0.81f,
		//sides+
		-radius/2.0f + _pos.x,		height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, 0.0f, 1.0f,								 0.0f, 0.6f,		// bak ruta
		radius/2.0f + _pos.x,		height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, 0.0f, 1.0f,								 1.0f, 0.6f,
		radius + _pos.x,			height/2.0f + _pos.y,	0.0f + _pos.z,					 1.0f, 0.0f, 0.0f,								 0.0f, 0.4f,
		radius/2.0f + _pos.x,		height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, 0.0f, -1.0f,								 0.0f, 0.6f,		//framruta
		-radius/2.0f + _pos.x,		height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, 0.0f, -1.0f,								 1.0f, 0.6f,
		-radius + _pos.x,			height/2.0f + _pos.y,	0.0f + _pos.z,					 -1.0f, 0.0f, 0.0f,								 0.0f, 0.4f,

		-radius/2.0f + _pos.x,		-height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, 0.0f, 1.0f,								 0.4f, 0.6f,		// bak ruta
		radius/2.0f + _pos.x,		-height/2.0f + _pos.y,	radius*0.86f + _pos.z,			 0.0f, 0.0f, 1.0f,								 1.0f, 0.4f,
		radius + _pos.x,			-height/2.0f + _pos.y,	0.0f + _pos.z,					 1.0f, 0.0f, 0.0f,								 1.0f, 0.6f,
		radius/2.0f + _pos.x,		-height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, 0.0f, -1.0f,								 0.0f, 0.6f,		// fram ruta
		-radius/2.0f + _pos.x,		-height/2.0f + _pos.y,	-radius*0.86f + _pos.z,			 0.0f, 0.0f, -1.0f,								 1.0f, 0.4f,
		-radius + _pos.x,			-height/2.0f + _pos.y,	0.0f + _pos.z,					 -1.0f, 0.0f, 0.0f,								 1.0f, 0.6f,


	};

	static const GLuint index_array_data[] = {
		//top
		0, 1, 6,
		1, 2, 6,

		2, 3, 6,
		3, 4, 6,

		4, 5, 6,
		5, 0, 6,
		//bottom
		8, 7, 13,
		9, 8, 13,

		10, 9, 13,
		11, 10, 13,

		12, 11, 13,
		7, 12, 13,
		//sides
		//// normal --> positiv z
		//14, 21, 20,
		//14, 15, 21,
		//
		//// normal --> negatiz z
		//18, 24, 23,
		//18, 23, 17, 

		//sides
		24, 18, 23,
		18, 17, 23,

		25, 19, 24,
		19, 18, 24,

		20, 14, 25, // 20, 25, 14 == 25, 14, 20, == 14, 20, 25
		14, 19, 25,

		21, 15, 20,
		15, 14, 20, // 1, 3, 0

		22, 16, 21,
		16, 15, 21,

		23, 17, 22,
		17, 16, 22,
		
	};
	nverts = 26;
	ntris = 24;

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


hexBox::~hexBox(void)
{
	//cout << "A hexbox has died." << endl;
}


void hexBox::move(float f)
{
	f = f - vertexarray[1];
	for (int i = 1; i < 56; i = i + 8)
	{
		if (vertexarray[i] < f)
			vertexarray[i] += 0.01f*(f - vertexarray[i]);
		else
			vertexarray[i] -= 0.01f*(vertexarray[i] - f);
	}
	for (int i = 113; i < 160; i = i + 8)
	{
		if (vertexarray[i] < f)
			vertexarray[i] += 0.01f*(f - vertexarray[i]);
		else
			vertexarray[i] -= 0.01f*(vertexarray[i] - f);
	}
//	height = vertexarray[1] - vertexarray[57];

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
	os << "Radius: " << radius << ", Height: " << height << endl;
}