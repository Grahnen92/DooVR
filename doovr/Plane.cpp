#include "Plane.h"
#include "time.h"
#include "math.h"

float vectorLength(vertex vertex1, vertex vertex2)
{
	vertex vector;

	vector.x = vertex1.x - vertex2.x;
	vector.y = vertex1.y - vertex2.y;
	vector.z = vertex1.z - vertex2.z;

	return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

Plane::Plane(glm::vec3 _pos, float _mass, glm::vec2 _dim)
{
	position = _pos;
	mass = _mass;
	dim = _dim;
	centerOfMass = position; // The center of mass is in the objects origin as default
	inertia = 1; // tempVorary

	oType = 'P';

	normal = { 0, 1, 0 };
	velocity = { 0, 0, 0 };
	acceleration = { 0, 0, 0 };
	orientation = { 0.f, 1.0f, 0.f };
	angularVelocity = 2.0f;
	angularAcceleration = 0.0f;

	color.x = 0.7f;
	color.y = 0.7f;
	color.z = 0.7f;

	GLfloat vertex_array_data[] = {_dim.x / 2.0f, 0.0f, _dim.y / 2.0f, 0.0f, 1.0f, 0.0f,
									-_dim.x / 2.0f, 0.0f, -_dim.y / 2.0f, 0.0f, 1.0f, 0.0f,
									-_dim.x / 2.0f, 0.0f, _dim.y / 2.0f, 0.0f, 1.0f, 0.0f,
									_dim.x / 2.0f, 0.0f, -_dim.y / 2.0f, 0.0f, 1.0f, 0.0f };

	static const GLuint index_array_data[] = {0, 1, 2,
											  0, 3, 1 };
	nverts = 15;
	ntris = nverts/3;

	triangle tempT;

	vertex tempV;
	tempV.x = 0.0f;
	tempV.y = 1.0f;
	tempV.z = 0.0f;
	vVertexArray.push_back(tempV);
	tempV.x = 1.0f;
	tempV.y = 0.2f;
	tempV.z = 0.0f;
	vVertexArray.push_back(tempV);
	tempV.x = -1.0f;
	tempV.y = 0.2f;
	tempV.z = 0.0f;
	vVertexArray.push_back(tempV);
	tempV.x = -0.5f;
	tempV.y = -1.0f;
	tempV.z = 0.0f;
	vVertexArray.push_back(tempV);
	tempV.x = 0.5f;
	tempV.y = -1.0f;
	tempV.z = 0.0f;
	vVertexArray.push_back(tempV);


	triangle * indexP;
	vertex * vertexP;

	//vertexP = vVertexArray;

	int index1 = 0, index2 = 0;
	vertex handledVert, vert1, vert2;

	float length = 0, currentLength1 = 100.0f, currentLength2 = 100.0f;

	for (int i = 0; i < vVertexArray.size(); i++)
	{
		handledVert = vVertexArray[i];

		for (int j = 0; j < vVertexArray.size(); j++)
		{
			if (j != i)
			{
				vert1 = vVertexArray[j];

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
		vIndexArray.push_back(tempT);

		currentLength2 = 100.0f;
		currentLength1 = 100.0f;
	}

	/*for (int i = 0; i <= nverts - 3 ; i = i + 3)
	{
		handledVert = glm::vec3(vertexarray[i], vertexarray[i + 1], vertexarray[i + 2]);
		
		for (int j = 0; j <= nverts -3 ; j = j + 3)
		{
			if ( j != i)
			{
				
				length = glm::sqrt(glm::dot(handledVert - glm::vec3(vertexarray[j], vertexarray[j + 1], vertexarray[j + 2]), handledVert - glm::vec3(vertexarray[j], vertexarray[j + 1], vertexarray[j + 2])));
				if (length < currentLength1)
				{
					currentLength2 = currentLength1;
					currentLength1 = length;
					
					index2 = index1;
					index1 = j/3;
				}
				else if (length < currentLength2)
				{
					currentLength2 = length;
					index2 = j/3;
				}
			}
		}

		
		//vIndexArray[i] = i;
		//vIndexArray[i + 1] = index1;
		//vIndexArray[i + 2] = index2;
		

		vIndexArray.push_back(i/3);
		vIndexArray.push_back(index1);
		vIndexArray.push_back(index2);

		cout << i/3 << " " << index1 << " " << index2 << endl;

		currentLength2 = 100.0f;
		currentLength1 = 100.0f;
	}*/


	vertexP = &vVertexArray[0];
	indexP = &vIndexArray[0];
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
		3*vVertexArray.size()*sizeof(GLfloat), vertexP, GL_STATIC_DRAW);
	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
	//glEnableVertexAttribArray(1); // Normals
	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3, 6 (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void*)0); // xyz coordinates
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
	//	6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals
	

	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex indices to OpenGL
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		3* vIndexArray.size()*sizeof(GLuint), indexP, GL_STATIC_DRAW);

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
	glDrawElements(GL_TRIANGLES, 3*vIndexArray.size()*sizeof(GLuint), GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}
	
void Plane::updateVertexArray() {

	triangle tempT;

	vertex tempV;

	triangle * indexP;
	vertex * vertexP;
	
	int index1 = 0, index2 = 0;
	vertex handledVert, vert1, vert2;

	float length = 0, currentLength1 = 100.0f, currentLength2 = 100.0f;

	for (int i = 0; i < vVertexArray.size(); i++)
	{
		handledVert = vVertexArray[i];

		for (int j = 0; j < vVertexArray.size(); j++)
		{
			if (j != i)
			{
				vert1 = vVertexArray[j];

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
		vIndexArray.push_back(tempT);

		currentLength2 = 100.0f;
		currentLength1 = 100.0f;
	}

	vertexP = &vVertexArray[0];
	indexP = &vIndexArray[0];

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Present our vertex coordinates to OpenGL
	glBufferData(GL_ARRAY_BUFFER,
		3*vVertexArray.size(), vertexP, GL_STREAM_DRAW);
	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
//	glEnableVertexAttribArray(1); // Normals
	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3, 6 (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void*)0); // xyz coordinates
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
	//	6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // normals


	// Activate the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	// Present our vertex indices to OpenGL
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		3*vIndexArray.size(), indexP, GL_STREAM_DRAW);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the buffers while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}


void Plane::display(ostream& os) const {
	os << "Shape: Plane" << endl;
	os << "Dimensions: " << dim.x << ", " << dim.y << " ,"  << endl;
	os << endl;

	os << "Mass: " << mass << endl;
	os << "Center of mass: " << centerOfMass.x << ", " << centerOfMass.y << ", " << centerOfMass.z << endl;
	os << "Inertia: " << inertia << endl;
	os << endl;

	os << "Position: " << position.x << ", " << position.y << ", " << position.z << endl;
	os << "Velocity: " << velocity.x << ", " << velocity.y << ", " << velocity.z << endl;
	os << "Acceleration: " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << endl;
	os << endl;

	os << "Orientation: " << orientation.x << ", " << orientation.y << ", " << orientation.z << endl;
	//os << "Angular velocity: " << angularVelocity.x << ", " << angularVelocity.y << ", " << angularVelocity.z << endl;
	//os << "Angular acceleration: " << angularAcceleration.x << ", " << angularAcceleration.y << ", " << angularAcceleration.z << endl;
	os << endl;

	os << "" << endl;
}