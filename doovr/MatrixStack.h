#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utilities.h"

// A linked list implementing a matrix stack
struct Matrix {
  float m[16];
  Matrix *previous;
};

class MatrixStack {

public:
    Matrix *currentMatrix;

    /* Constructor: Create one matrix and set it to identity */
    MatrixStack();

    /* Destructor: Delete all elements from the stack */
    ~MatrixStack();

    // Get the pointer to the topmost (current) matrix array
    float* getCurrentMatrix();

    // Set the topmost (current) matrix to the identity matrix
    void init();

    // Multiply the topmost (current) matrix with a rotation around X
    void rotX(float angle);

    // Multiply the topmost (current) matrix with a rotation around Y
    void rotY(float angle);

    // Multiply the topmost (current) matrix with a rotation around Z
    void rotZ(float angle);

	void rotAxis(float* axis, float a);

    // Multiply the topmost (current) matrix with a uniform scaling
    void scale(float s);

    // Multiply the topmost (current) matrix with a translation
    void translate(float pos[3]);

	void multiply(float M[]);
	//void multiply(float **M);

    // Add a new level on the stack, making a copy of the topmost matrix
    void push();

    // Remove one element from the stack, exposing the element below
    void pop();

    // Remove all elements except the last one from the stack
    void flush();

    // Count the number of elements on the stack
    int depth();

    // Print the entire contents of the stack (for debugging purposes)
    void print();

private:
    // These functions should not be used outside of the class.
    void matrixMult(float M1[], float M2[], float Mout[]);
    void matrixPrint(float M[]);
};
