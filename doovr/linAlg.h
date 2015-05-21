#include "math.h"
#include <iostream>

namespace linAlg {

	void normVec(float* vec);
	void crossProd(float* normal, float* vec1, float* vec2);
	void matrixMult(float* M1, float* M2, float* Mout);
	void invertMatrix(float* m, float* invOut);
	void transpose(float* m, float* out);
	void vectorMatrixMult(float* M1, float* V, float* Vout);
	void matrixMultTHREE(float* M1, float* M2, float* Mout);
	void makeUniform(float* m);
}