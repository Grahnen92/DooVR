#include "hexBox.h"

hexBox::hexBox(float x, float y, float z, float tX, float tY)
{
	oType = 'H';
	function = -1;
	position[0] = x;
	position[1] = y;
	position[2] = z;
	float radius = 0.0465f;


	GLfloat vertex_array_data[] = {
		//						Vertex									Normals										Texture  
		//top
		-radius/2.0f + x,		y,	radius*0.86f + z,			 0.0f, 1.0f, 0.0f,								 (147.0f/1024.0f)*tX + 45.0f/1024.0f, (86.0f/1024.0f)*tY + 82.0f/1024.0f,
		radius/2.0f + x,		y,	radius*0.86f + z,			 0.0f, 1.0f, 0.0f,								 (147.0f/1024.0f)*tX + 96.0f/1024.0f, (86.0f/1024.0f)*tY + 82.0f/1024.0f,
		radius + x,				y,	0.0f + z,					 0.0f, 1.0f, 0.0f,								 (147.0f/1024.0f)*tX + 121.0f/1024.0f,(86.0f/1024.0f)*tY + 127.0f/1024.0f,
		radius/2.0f + x,		y,	-radius*0.86f + z,			 0.0f, 1.0f, 0.0f,								 (147.0f/1024.0f)*tX + 96.0f/1024.0f, (86.0f/1024.0f)*tY + 172.0f/1024.0f,
		-radius/2.0f + x,		y,	-radius*0.86f + z,			 0.0f, 1.0f, 0.0f,								 (147.0f/1024.0f)*tX + 45.0f/1024.0f, (86.0f/1024.0f)*tY + 172.0f/1024.0f,
		-radius + x,			y,	0.0f + z,					 0.0f, 1.0f, 0.0f,								 (147.0f/1024.0f)*tX + 21.0f/1024.0f, (86.0f/1024.0f)*tY + 127.0f/1024.0f,
		0.0f + x,				y,	0.0f + z,					 0.0f, 1.0f, 0.0f,								 (147.0f/1024.0f)*tX + 70.0f/1024.0f, (86.0f/1024.0f)*tY + 127.0f/1024.0f,

		//sides+
		-radius/2.0f + x,		y,	radius*0.86f + z,			 0.0f, 0.0f, 1.0f,								49.0f/1024.0f, 0.51f,
		radius/2.0f + x,		y,	radius*0.86f + z,			 0.0f, 0.0f, 1.0f,								96.0f/1024.0f, 0.52f,
		radius + x,				y,	0.0f + z,					 1.0f, 0.0f, 0.0f,								 96.0f/1024.0f, 0.51f,
		radius/2.0f + x,		y,	-radius*0.86f + z,			 0.0f, 0.0f, -1.0f,								 49.0f/1024.0f, 0.52f,
		-radius/2.0f + x,		y,	-radius*0.86f + z,			 0.0f, 0.0f, -1.0f,								 96.0f/1024.0f, 0.51f,
		-radius + x,			y,	0.0f + z,					 -1.0f, 0.0f, 0.0f,								 49.0f/1024.0f, 0.52f,
		//sides-
		-radius/2.0f + x,		-3.0f,	radius*0.86f + z,		 0.0f, 0.0f, 1.0f,								49.0f/1024.0f, 0.51f,
		radius/2.0f + x,		-3.0f,	radius*0.86f + z,		 0.0f, 0.0f, 1.0f,								96.0f/1024.0f, 0.52f,
		radius + x,				-3.0f,	0.0f + z,				 1.0f, 0.0f, 0.0f,								 96.0f/1024.0f, 0.51f,
		radius/2.0f + x,		-3.0f,	-radius*0.86f + z,		 0.0f, 0.0f, -1.0f,								 49.0f/1024.0f, 0.52f,
		-radius/2.0f + x,		-3.0f,	-radius*0.86f + z,		 0.0f, 0.0f, -1.0f,								 96.0f/1024.0f, 0.51f,
		-radius + x,			-3.0f,	0.0f + z,				 -1.0f, 0.0f, 0.0f,								 49.0f/1024.0f, 0.52f,


	};

	static const GLuint index_array_data[] = {
		//top
		0, 1, 6,
		1, 2, 6,

		2, 3, 6,
		3, 4, 6,

		4, 5, 6,
		5, 0, 6,

		//sides -7
		17, 11, 16,
		11, 10, 16,

		18, 12, 17,
		12, 11, 17,

		13, 7, 18, // 20, 25, 14 == 25, 14, 20, == 14, 20, 25
		7, 12, 18,

		14, 8, 13,
		8, 7, 13, // 1, 3, 0

		15, 9, 14,
		9, 8, 14,

		16, 10, 15,
		10, 9, 15,
		
	};
	nverts = 19;
	ntris = 18;

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

	GLcalls();
}


hexBox::~hexBox(void)
{
	//cout << "A hexbox has died." << endl;
}


void hexBox::move(float f)
{
	for (int i = 1; i < 105; i = i + 8)
	{
		if (vertexarray[i] < f)
			vertexarray[i] += 0.04f*(f - vertexarray[i]);
		else
			vertexarray[i]-= 0.04f*(vertexarray[i] - f);
	}
	//position[0] = vertexarray[48];
	position[1] = f;
	//position[0] = vertexarray[50];
	GLcalls();
}

void hexBox::moveInstant(float f) 
{
	for (int i = 1; i < 105; i = i + 8)
	{
		vertexarray[i] = f;
	}
	//position[0] = vertexarray[48];
	position[1] = f;
	//position[0] = vertexarray[50];
	GLcalls();
}

void hexBox::GLcalls()
{
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
	os << "Shape: hexBox" << endl;
	os << position[1] << endl;

}