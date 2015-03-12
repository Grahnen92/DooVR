#include "Sphere.h"

Sphere::Sphere(glm::vec3 _pos, float _mass, float _rad)
{
	oType = 'S';

	position = _pos;
	mass = _mass;
	radius = _rad;
	centerOfMass = position; // The center of mass is in the objects origin as default
	inertia = 1; // temporary

	createSphere(_rad, 6);
	
	velocity = { 0, 0, 0 };
	acceleration = { 0, 0, 0 };
	orientation = { 0.0f, 1.0f, 0.0f };
	rotAxis = { 0.0f, 1.0f, 0.0f };
	angularPosition = 0.0f;
	angularVelocity = 0.0f;
	angularAcceleration = 0.0f;

	color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


void Sphere::render()
{
	glBindVertexArray(vao);
	glColor3f(color.x,color.y,color.z);
	glDrawElements(GL_TRIANGLES, 3 * ntris, GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);
}

Sphere::~Sphere(void)
{
	cout << "A sphere has died" << endl;
}


void Sphere::createSphere(float radius, int segments) {
	float M_PI = 3.14159265358979323846;
	int i, j, base, i0;
	float x, y, z, R;
	double theta, phi;
	int vsegs, hsegs;
	int stride = 8;

	// Delete any previous content in the TriangleSoup object

	vsegs = segments;
	if (vsegs < 2) vsegs = 2;
	hsegs = vsegs * 2;
	nverts = 1 + (vsegs - 1) * (hsegs + 1) + 1; // top + middle + bottom
	ntris = hsegs + (vsegs - 2) * hsegs * 2 + hsegs; // top + middle + bottom
	vertexarray = new float[nverts * 8];
	indexarray = new GLuint[ntris * 3];

	// The vertex array: 3D xyz, 3D normal, 2D st (8 floats per vertex)
	// First vertex: top pole (+z is "up" in object local coords)
	vertexarray[0] = 0.0f;
	vertexarray[1] = 0.0f;
	vertexarray[2] = radius;
	vertexarray[3] = 0.0f;
	vertexarray[4] = 0.0f;
	vertexarray[5] = 1.0f;
	vertexarray[6] = 0.5f;
	vertexarray[7] = 1.0f;
	// Last vertex: bottom pole
	base = (nverts - 1)*stride;
	vertexarray[base] = 0.0f;
	vertexarray[base + 1] = 0.0f;
	vertexarray[base + 2] = -radius;
	vertexarray[base + 3] = 0.0f;
	vertexarray[base + 4] = 0.0f;
	vertexarray[base + 5] = -1.0f;
	vertexarray[base + 6] = 0.5f;
	vertexarray[base + 7] = 0.0f;
	// All other vertices:
	// vsegs-1 latitude rings of hsegs+1 vertices each
	// (duplicates at texture seam s=0 / s=1)
	for (j = 0; j<vsegs - 1; j++) { // vsegs-1 latitude rings of vertices
		theta = (double)(j + 1) / vsegs*M_PI;
		z = cos(theta);
		R = sin(theta);
		for (i = 0; i <= hsegs; i++) { // hsegs+1 vertices in each ring (duplicate for texcoords)
			phi = (double)i / hsegs*2.0*M_PI;
			x = R*cos(phi);
			y = R*sin(phi);
			base = (1 + j*(hsegs + 1) + i)*stride;
			vertexarray[base] = radius*x;
			vertexarray[base + 1] = radius*y;
			vertexarray[base + 2] = radius*z;
			vertexarray[base + 3] = x;
			vertexarray[base + 4] = y;
			vertexarray[base + 5] = z;
			vertexarray[base + 6] = (float)i / hsegs;
			vertexarray[base + 7] = 1.0f - (float)(j + 1) / vsegs;
		}
	}

	// The index array: triplets of integers, one for each triangle
	// Top cap
	for (i = 0; i<hsegs; i++) {
		indexarray[3 * i] = 0;
		indexarray[3 * i + 1] = 1 + i;
		indexarray[3 * i + 2] = 2 + i;
	}
	// Middle part (possibly empty if vsegs=2)
	for (j = 0; j<vsegs - 2; j++) {
		for (i = 0; i<hsegs; i++) {
			base = 3 * (hsegs + 2 * (j*hsegs + i));
			i0 = 1 + j*(hsegs + 1) + i;
			indexarray[base] = i0;
			indexarray[base + 1] = i0 + hsegs + 1;
			indexarray[base + 2] = i0 + 1;
			indexarray[base + 3] = i0 + 1;
			indexarray[base + 4] = i0 + hsegs + 1;
			indexarray[base + 5] = i0 + hsegs + 2;
		}
	}
	// Bottom cap
	base = 3 * (hsegs + 2 * (vsegs - 2)*hsegs);
	for (i = 0; i<hsegs; i++) {
		indexarray[base + 3 * i] = nverts - 1;
		indexarray[base + 3 * i + 1] = nverts - 2 - i;
		indexarray[base + 3 * i + 2] = nverts - 3 - i;
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
	// Stride 8 (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3, 6 (offset into first vertex)
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
	// Do NOT unbind the buffers while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

};


void Sphere::display(ostream& os) const{
	os << "Shape: Sphere" << endl;
	os << "Radius: " << radius << endl; 
	os << endl;

	os << "Mass: " << mass << endl;
	os << "Center of mass: " << centerOfMass.x << ", " << centerOfMass.y << ", "<< centerOfMass.z << endl;
	os << "Inertia: " << inertia << endl;
	os << endl;

	os << "Position: " << position.x << ", " << position.y << ", "<< position.z << endl;
	os << "Velocity: " << velocity.x << ", " << velocity.y << ", "<< velocity.z << endl;
	os << "Acceleration: " << acceleration.x << ", " << acceleration.y << ", "<< acceleration.z << endl;
	os << endl;
	
	os << "Orientation: " << orientation.x << ", " << orientation.y << ", "<< orientation.z << endl;
//	os << "Angular velocity: " << angularVelocity.x << ", " << angularVelocity.y << ", "<< angularVelocity.z << endl;
//	os << "Angular acceleration: " << angularAcceleration.x << ", " << angularAcceleration.y << ", "<< angularAcceleration.z << endl;
	os << endl;

	os << "" << endl;
}