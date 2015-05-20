#include "Plane.h"
#include "time.h"
#include "math.h"

Plane::Plane(glm::vec3 _pos, glm::vec2 _dim) {
	oType = 'P';
	planeVertexData tempV;
	triangle tempT;

	planeVertexData* vertexP;
	triangle* indexP;

	tempV.y = 0.0f;
	tempV.nx = 0.0f;
	tempV.ny = 1.0f;
	tempV.nz = 0.0f;
//	tempV.adjacentFace = nullptr;

	position[0] = _pos.x;
	position[1] = _pos.y;
	position[2] = _pos.z;

	dim = _dim;

	color.x = 0.1f;
	color.y = 0.7f;
	color.z = 0.1f;

	for (float i = -_dim.x/2.0f; i < _dim.x/2.0f; i++) {
		for (float j = -_dim.y/2.0f ; j < _dim.y / 2.0f; j++) {
			tempV.x = i;
			tempV.z = j;
			vertexArray.push_back(tempV);

			if (fmod(j,2) == 0 && fmod(i,2) == 0) { // om j är jämn o i jämn
				tempV.u = 0.0f;
				tempV.v = 0.0f;
			}
			else if (fmod(j, 2) == 0 && fmod(i, 2) != 0) { // om j är jämn o i ojämn
				tempV.u = 1.0f;
				tempV.v = 0.0f;
			}
			else if (fmod(j, 2) != 0 && fmod(i, 2) != 0) { // om j är ojämn o i ojämn
				tempV.u = 1.0f;
				tempV.v = 1.0f;
			}
			else if (fmod(j, 2) != 0 && fmod(i, 2) == 0) { // om j är ojämn o i jämn
				tempV.u = 0.0f;
				tempV.v = 1.0f;
			}
			
		}
	}
	
	for (int i = 0; i < _dim.x - 1 ; i++) {
		for (int j = 0; j < _dim.y - 1; j++) { 

			tempT.index[0] = i*_dim.x + j; 
			tempT.index[1] = i*_dim.x + j + 1;
			tempT.index[2] = (i + 1)*_dim.x + j;

			indexArray.push_back(tempT);

			tempT.index[0] = (i + 1)*_dim.x + j;
			tempT.index[1] = i*_dim.x + j + 1;
			tempT.index[2] = (i + 1)*_dim.x + j + 1;

			indexArray.push_back(tempT);
		}
	}
	
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
	glBufferData(GL_ARRAY_BUFFER, vertexArray.size()*sizeof(vertex),
				 vertexP, GL_STREAM_DRAW);

	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
	glEnableVertexAttribArray(1); // Normals
	glEnableVertexAttribArray(2); // Texture
	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3, 6 (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
						  8 * sizeof(GLfloat), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
						  8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // texture


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

Plane::~Plane(void) {
	cout << "A box has died." << endl;
}

void Plane::render() {
	glBindVertexArray(vao);
	//glColor3f(color.x, color.y, color.z);

	glDrawElements(GL_TRIANGLES, 3 * indexArray.size()*sizeof(GLuint), GL_UNSIGNED_INT, (void*)0);

	
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}

void Plane::display(ostream& os) const {
	os << "Shape: Plane" << endl;
	os << "Dimensions: " << dim.x << ", " << dim.y << " ," << endl;
	os << endl;
}