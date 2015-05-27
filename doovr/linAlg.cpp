#include "linAlg.h"

void linAlg::matrixMult(float* M1, float* M2, float* Mout) {
	// Compute result in a local variable to avoid conflicts
	// with overwriting if Mout is the same variable as either
	// M1 or M2.
	float Mtemp[16];
	int i, j;
	// Perform the multiplication M3 = M1*M2
	// (i is row index, j is column index)
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			Mtemp[i + j * 4] = M1[i] * M2[j * 4] + M1[i + 4] * M2[1 + j * 4]
				+ M1[i + 8] * M2[2 + j * 4] + M1[i + 12] * M2[3 + j * 4];
		}
	}
	// Copy the result to the output variable
	for (i = 0; i<16; i++) {
		Mout[i] = Mtemp[i];
	}
}

void linAlg::matrixMultTHREE(float* M1, float* M2, float* Mout) {
	// Compute result in a local variable to avoid conflicts
	// with overwriting if Mout is the same variable as either
	// M1 or M2.
	float Mtemp[9];
	int i, j;
	// Perform the multiplication M3 = M1*M2
	// (i is row index, j is column index)
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			Mtemp[3*i + j] = M1[i*3] * M2[j] + 
							   M1[i*3 + 1] * M2[3 + j] + 
							   M1[i*3 + 2] * M2[6 + j];
		}
	}
	// Copy the result to the output variable
	for (i = 0; i<9; i++) {
		Mout[i] = Mtemp[i];
	}
}

void linAlg::vectorMatrixMult(float* M1, float* V, float* Vout) {
	float Mtemp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	int i, j;
	// Perform the multiplication M3 = M1*M2
	// (i is row index, j is column index)
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			Mtemp[i] += M1[j+4*i] * V[j];
		}
	}
	// Copy the result to the output variable
	for (i = 0; i<4; i++) {
		Vout[i] = Mtemp[i];
	}
}

void linAlg::transpose(float* m, float* out)
{
	for (int i = 0; i < 16; i++) {
		if (i == 1 || i == 2 || i == 3)
			out[i] = m[4 * i];
		else
			out[i] = m[i];
	}
	out[9] = m[6];
	out[13] = m[7];
	out[14] = m[11];
}

void linAlg::makeUniform(float* m)
{
	for (int i = 0; i < 16; i++) {
		if (i == 0 || i == 5 || i == 10 || i == 15)
			m[i] = 1.0f;
		else 
			m[i] = 0.0f;
	}
}

void linAlg::invertMatrix(float* m, float* invOut)
{
	float inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0) {
		std::cout << "inverseMatrix: Determinant = 0. Cannot inverse." << std::endl;
	}
	else {
		det = 1.0 / det;
		for (i = 0; i < 16; i++)
			invOut[i] = inv[i] * det;
	}
}

void linAlg::calculateVec(float* newVec, float* a, float* b) {
	newVec[0] = a[0] - b[0];
	newVec[1] = a[1] - b[1];
	newVec[2] = a[2] - b[2];
}

void linAlg::normVec(float* vec) {
	float length = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

	if (length != 0) {
		vec[0] = vec[0] / length;
		vec[1] = vec[1] / length;
		vec[2] = vec[2] / length;
	}
}

void linAlg::crossProd(float normal[3], float* vec1, float* vec2) {
	normal[0] = (vec1[1] * vec2[2] - vec1[2] * vec2[1]);
	normal[1] = -(vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	normal[2] = (vec1[0] * vec2[1] - vec1[1] * vec2[0]);
}

float linAlg::vecLength(float vec[3]) {
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}
