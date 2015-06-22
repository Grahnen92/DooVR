#include "math.h"
#include <iostream>

namespace linAlg {

	//! Multiplies two 4x4 matrices, the resulting matrix is Mout
	void matrixMult(float* M1, float* M2, float* Mout);
	//! Invers a 4x4 matrix, the resulting matrix is invOut
	void invertMatrix(float* m, float* invOut);
	//! Transpose a 4x4 matrix, the resulting matrix is out
	void transpose(float* m, float* out);
	//! Multiplies a 4x4 matrix by a 4x1 vector, the resulting vector is Vout
	void vectorMatrixMult(float* M1, float* V, float* Vout);
	//! Multiplies two 3x3 matrices, the resulting matrix is Mout
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
	//! Calculates the dot product of the two vectors
	float dotProd(float vec1[3], float vec2[3]);


}