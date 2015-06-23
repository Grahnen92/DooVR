#include "math.h"
#include <iostream>

namespace linAlg {

	//! Multiplise two 4x4 matricies the resulting matrix is placed in Mout
	void matrixMult(float* M1, float* M2, float* Mout);
	//! inverts matrix m and places the result in invOut
	void invertMatrix(float* m, float* invOut);
	//! Transpose matrix
	void transpose(float* m);
	//! Multiplise a 4x4 matrix with a column vector. The resulting vector is placed in Vout
	void vectorMatrixMult(float* M1, float* V, float* Vout);
	//! Multiplise two 3x3 matricies the resulting matrix is placed in Mout
	void matrixMultTHREE(float* M1, float* M2, float* Mout);
	void makeUniform(float* m);

	//! calcualte vector from b to a, the resulting vector is placed in newVec
	void calculateVec(float* newVec, float* a, float* b);
	//! normalize vector
	void normVec(float* vec);
	// takes the crossproduct between vec1 and vec2 and places the resulting vector in normal
	void crossProd(float normal[3], float* vec1, float* vec2);
	//! Calculates the vector lenght
	float vecLength(float vec[3]);
	//! Calculates the dot product
	float dotProd(float vec1[3], float vec2[3]);
}