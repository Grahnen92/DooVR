#include "math.h"
#include <iostream>

namespace linAlg {

	void matrixMult(float* M1, float* M2, float* Mout);
	void invertMatrix(float* m, float* invOut);
	void transpose(float* m, float* out);
	void vectorMatrixMult(float* M1, float* V, float* Vout);
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

	float dotProd(float vec1[3], float vec2[3]);


}