#include "stdafx.h"
#include "MatrixEquations.h"




inline float ComputeMagThree(float vector[3]) {
	return sqrt(pow(vector[0], 2)  + pow(vector[1],2) + pow(vector[2],2));
}

void MatrixEquations::MultMatrices(GzMatrix matOne, GzMatrix matTwo, GzMatrix target) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			target[i][j] = DotProduct(matOne, matTwo, i,j);
		}
	}
}


float MatrixEquations::DotProduct(float* arrayOne, float* arrayTwo, int size) {
	float val = 0;
	for (int i = 0; i < size; i++) {
		val += arrayOne[i] * arrayTwo[i];
	}
	return val;
}

float MatrixEquations::DotProduct(GzMatrix matOne, GzMatrix matTwo, int i, int j) {
	return (matOne[i][0] * matTwo[0][j]) + (matOne[i][1] * matTwo[1][j]) + (matOne[i][2] * matTwo[2][j]) + (matOne[i][3] * matTwo[3][j]);
}

void MatrixEquations::FillMatrix(GzMatrix mat,
	float one, float two, float three, float four,
	float five, float six, float seven, float eight,
	float nine, float ten, float eleven, float twelve,
	float thirteen, float fourteen, float fifteen, float sixteen) {

	mat[0][0] = one;
	mat[0][1] = two;
	mat[0][2] = three;
	mat[0][3] = four;

	mat[1][0] = five;
	mat[1][1] = six;
	mat[1][2] = seven;
	mat[1][3] = eight;

	mat[2][0] = nine;
	mat[2][1] = ten;
	mat[2][2] = eleven;
	mat[2][3] = twelve;

	mat[3][0] = thirteen;
	mat[3][1] = fourteen;
	mat[3][2] = fifteen;
	mat[3][3] = sixteen;
}

void MatrixEquations::NormalizeVectorThree(float vector[]) {
	float mag = ComputeMagThree(vector);
	vector[0] /= mag;
	vector[1] /= mag;
	vector[2] /= mag;
}

//takes a gzcoord, sets value 4 to 1, does vector/matrix mult, converts to 3D space.
void MatrixEquations::MatrixVectorMult(GzMatrix mat, GzCoord coord) {

	float tempArray[4];

	for (int i = 0; i < 4; i++) {
		//Fourth term W is set to 1
		tempArray[i] = (mat[i][0] * coord[X]) + (mat[i][1] * coord[Y]) + (mat[i][2] * coord[Z]) + (mat[i][3]);
	}

	coord[X] = tempArray[X] / tempArray[3];
	coord[Y] = tempArray[Y] / tempArray[3];
	coord[Z] = tempArray[Z] / tempArray[3];


}

void MatrixEquations::MatrixVectorMult(GzMatrix mat, Point &p) {
	float tempArray[4];

	for (int i = 0; i < 4; i++) {
		//Fourth term W is set to 1
		tempArray[i] = (mat[i][0] * p.x) + (mat[i][1] * p.y) + (mat[i][2] * p.z) + (mat[i][3]);
	}

	p.x = tempArray[X] / tempArray[3];
	p.y = tempArray[Y] / tempArray[3];
	p.z = tempArray[Z] / tempArray[3];
}

//Assumes size 3 vector
 void MatrixEquations::CrossProduct(float* vecOne, float* vecTwo, float* returnVal) {
	returnVal[0] = vecOne[1] * vecTwo[2] - vecOne[2] * vecTwo[1];
	returnVal[1] = vecOne[2] * vecTwo[0] - vecOne[0] * vecTwo[2];
	returnVal[2] = vecOne[0] * vecTwo[1] - vecOne[1] * vecTwo[0];
}


 void MatrixEquations::NormalizeMatrix(GzMatrix matrix) {
	 float scaleFactor = sqrt( pow(matrix[0][0], 2) + pow(matrix[0][1], 2) + pow(matrix[0][2], 2));
	 matrix[0][0] /= scaleFactor;
	 matrix[0][1] /= scaleFactor;
	 matrix[0][2] /= scaleFactor;

	 matrix[1][0] /= scaleFactor;
	 matrix[1][1] /= scaleFactor;
	 matrix[1][2] /= scaleFactor;

	 matrix[2][0] /= scaleFactor;
	 matrix[2][1] /= scaleFactor;
	 matrix[2][2] /= scaleFactor;
 }