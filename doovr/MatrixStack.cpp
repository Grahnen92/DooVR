#include "MatrixStack.h"
#include <math.h>

/* Constructor: Create one matrix and set it to identity */
MatrixStack::MatrixStack() {
    currentMatrix = new Matrix;
    init();
};

/* Destructor: Delete all elements from the stack */
MatrixStack::~MatrixStack() {
    flush();
};

// Get the pointer to the topmost (current) matrix array.
float *MatrixStack::getCurrentMatrix() {
    if(currentMatrix)
        return currentMatrix->m;
    else
        return NULL;
};

// Set the topmost (current) matrix to the identity matrix
// and make it the only element on the stack.
// This should be used with caution.
void MatrixStack::init() {
    currentMatrix->previous = NULL;
    currentMatrix->m[0]=1.0f;
    currentMatrix->m[1]=0.0f;
    currentMatrix->m[2]=0.0f;
    currentMatrix->m[3]=0.0f;
    currentMatrix->m[4]=0.0f;
    currentMatrix->m[5]=1.0f;
    currentMatrix->m[6]=0.0f;
    currentMatrix->m[7]=0.0f;
    currentMatrix->m[8]=0.0f;
    currentMatrix->m[9]=0.0f;
    currentMatrix->m[10]=1.0f;
    currentMatrix->m[11]=0.0f;
    currentMatrix->m[12]=0.0f;
    currentMatrix->m[13]=0.0f;
    currentMatrix->m[14]=0.0f;
    currentMatrix->m[15]=1.0f;
};

// Multiply the topmost (current) matrix with a rotation around X
void MatrixStack::rotX(float angle){
    float rx[16];
	rx[0]= 1.0f; rx[1]=0.0f; rx[2]=0.0f; rx[3]=0.0f;
	rx[4]= 0.0f; rx[5]=cosf(angle); rx[6]=sinf(angle); rx[7]= 0.0f;
	rx[8]= 0.0f; rx[9]=-sinf(angle); rx[10]=cosf(angle); rx[11]=0.0f;
	rx[12]=0.0f; rx[13]=0.0f; rx[14]=0.0f; rx[15]=1.0f;
    matrixMult(currentMatrix->m, rx, currentMatrix->m);
};

// Multiply the topmost (current) matrix with a rotation around Y
void MatrixStack::rotY(float angle){
    float ry[16];
    ry[0]= cosf(angle); ry[1]=0.0f; ry[2]=-sinf(angle); ry[3]=0.0f;
	ry[4]= 0.0f; ry[5]=1.0f; ry[6]=0.0f; ry[7]= 0.0f;
	ry[8]= sinf(angle); ry[9]=0.0f; ry[10]=cosf(angle); ry[11]=0.0f;
	ry[12]=0.0f; ry[13]=0.0f; ry[14]=0.0f; ry[15]=1.0f;
    matrixMult(currentMatrix->m, ry, currentMatrix->m);
};

// Multiply the topmost (current) matrix with a rotation around Z
void MatrixStack::rotZ(float angle) {
    float rz[16];
	rz[0]= cosf(angle); rz[1]=sinf(angle); rz[2]=0.0f; rz[3]=0.0f;
	rz[4]= -sinf(angle); rz[5]=cosf(angle); rz[6]=0.0f; rz[7]= 0.0f;
	rz[8]= 0.0f; rz[9]=0.0f; rz[10]=1.0f; rz[11]=0.0f;
	rz[12]=0.0f; rz[13]=0.0f; rz[14]=0.0f; rz[15]=1.0f;
    matrixMult(currentMatrix->m, rz, currentMatrix->m);
};

void MatrixStack::rotAxis(float* axis, float a) {

	//axis = glm::normalize(axis);

	float ra[16];

	//float ra[0] = axis[0]*axis[0] + 
	/*
	ra[0] = bg[0][0];
	ra[1] = bg[1][0];
	ra[2] = bg[2][0];
	ra[3] = bg[3][0];
	ra[4] = bg[0][1];
	ra[5] = bg[1][1];
	ra[6] = bg[2][1];
	ra[7] = bg[3][1];
	ra[8] = bg[0][2];
	ra[9] = bg[1][2];
	ra[10] = bg[2][2];
	ra[11] = bg[3][2];
	ra[12] = bg[0][3];
	ra[13] = bg[1][3];
	ra[14] = bg[2][3];
	ra[15] = bg[3][3];
	*/
	matrixMult(currentMatrix->m, ra, currentMatrix->m);
}

// Multiply the topmost (current) matrix with a uniform scaling
void MatrixStack::scale(float s) {
    float s_mtx[16] = {0};
    s_mtx[0] = s;
    s_mtx[5] = s;
    s_mtx[10] = s;
    s_mtx[15] = 1.0f;
    matrixMult(currentMatrix->m, s_mtx, currentMatrix->m);
};

// Multiply the topmost (current) matrix with a translation
void MatrixStack::translate(float pos[3]) {
    float t_mtx[16] = {0};
    t_mtx[0] = 1.0f;
    t_mtx[5] = 1.0f;
    t_mtx[10] = 1.0f;
    t_mtx[15] = 1.0f;
    t_mtx[12] = pos[0];
    t_mtx[13] = pos[1];
    t_mtx[14] = pos[2];
    matrixMult(currentMatrix->m, t_mtx, currentMatrix->m);
};

void MatrixStack::multiply(float M[]) {
	float t_mtx[16] = { 0 };
	t_mtx[0] =M[0];
	t_mtx[1] = M[1];
	t_mtx[2] = M[2];
	t_mtx[3] = M[3];
	t_mtx[4] = M[4];
	t_mtx[5] = M[5];
	t_mtx[6] = M[6];
	t_mtx[7] = M[7];
	t_mtx[8] = M[8];
	t_mtx[9] = M[9];
	t_mtx[10] = M[10];
	t_mtx[11] = M[11];
	t_mtx[12] = M[12];
	t_mtx[13] = M[13];
	t_mtx[14] = M[14];
	t_mtx[15] = M[15];
	matrixMult(currentMatrix->m, t_mtx, currentMatrix->m);
};
/*
void MatrixStack::multiply(float **M) {
	float t_mtx[16] = { 0 };
	t_mtx[0] = *M[0];
	t_mtx[1] = *M[1];
	t_mtx[2] = *M[2];
	t_mtx[3] = *M[3];
	t_mtx[4] = *M[4];
	t_mtx[5] = *M[5];
	t_mtx[6] = *M[6];
	t_mtx[7] = *M[7];
	t_mtx[8] = *M[8];
	t_mtx[9] = *M[9];
	t_mtx[10] = *M[10];
	t_mtx[11] = *M[11];
	t_mtx[12] = *M[12];
	t_mtx[13] = *M[13];
	t_mtx[14] = *M[14];
	t_mtx[15] = *M[15];
	matrixMult(currentMatrix->m, t_mtx, currentMatrix->m);
};
*/

// Add a new level on the stack, by making a copy of the current matrix and
// adding it to the top of the linked list, making it the new current matrix.
void MatrixStack::push() {
    Matrix *new_mtx;
    int i;

    new_mtx = new Matrix;

    for(i=0; i<16; i++) {
        new_mtx->m[i] = currentMatrix->m[i];
    }
    new_mtx->previous = currentMatrix;
    currentMatrix = new_mtx;
};

// Remove one element from the stack, exposing the element below.
void MatrixStack::pop() {
    Matrix *old_mtx;

    old_mtx = currentMatrix;

    if(old_mtx == NULL) {
        fprintf(stderr, "Stack underflow: Pop attemted on empty stack.\n");
        return;
    }
    currentMatrix = currentMatrix->previous;
    delete old_mtx;
};

// Remove all elements from the stack
void MatrixStack::flush() {
    while(currentMatrix != NULL) {
        pop();
    }
}

// Count the number of elements on the stack
int MatrixStack::depth() {
    Matrix *tmp_mtx;
    int i=0;

    tmp_mtx = currentMatrix;
    while(tmp_mtx != NULL) {
        i++;
        tmp_mtx = tmp_mtx->previous;
    }
    return i;
}

// Print the entire contents of a matrix stack (for debugging purposes)
void MatrixStack::print() {
    Matrix *tmp_mtx;

    tmp_mtx = currentMatrix;
    printf("Stack contents:\n");
    while(tmp_mtx != NULL) {
        matrixPrint(tmp_mtx->m);
        tmp_mtx = tmp_mtx->previous;
        printf("\n");
    }
}


// private:
// Print the contents of a matrix M to stdout.
void MatrixStack::matrixPrint(float M[]) {
	printf("%5.2f %5.2f %5.2f %5.2f\n", M[0],M[4],M[8],M[12]);
	printf("%5.2f %5.2f %5.2f %5.2f\n", M[1],M[5],M[9],M[13]);
	printf("%5.2f %5.2f %5.2f %5.2f\n", M[2],M[6],M[10],M[14]);
	printf("%5.2f %5.2f %5.2f %5.2f\n\n", M[3],M[7],M[11],M[15]);
}

// private:
// Multiply two matrices.
void MatrixStack::matrixMult(float M1[], float M2[], float Mout[]) {
    // Compute result in a local variable to avoid conflicts
    // with overwriting if Mout is the same variable as either
    // M1 or M2.
	float Mtemp[16];
	int i, j;
    // Perform the multiplication M3 = M1*M2
    // (i is row index, j is column index)
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			Mtemp[i+j*4] = M1[i]*M2[j*4] + M1[i+4]*M2[1+j*4]
				+ M1[i+8]*M2[2+j*4] + M1[i+12]*M2[3+j*4];
		}
	}
	// Copy the result to the output variable
	for(i=0; i<16; i++) {
		Mout[i] = Mtemp[i];
	}
}
