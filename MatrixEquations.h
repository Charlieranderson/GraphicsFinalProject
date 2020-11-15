#pragma once
#include "gz.h"
#include "Ray.h"


class MatrixEquations
{
public:
	static void FillMatrix(GzMatrix loc,
		float, float, float, float,
		float, float, float, float,
		float, float, float, float,
		float, float, float, float);

	static void MultMatrices(GzMatrix matOne, GzMatrix matTwo, GzMatrix target);

	//Dot product of two vectors with variable entries.
	static float DotProduct(float*, float*, int size);

	//Used for 4x4 matrices
	static float DotProduct(GzMatrix, GzMatrix, int indexOne, int indexTwo);

	
	static void NormalizeVectorThree(float vector[]);
	
	//Return is in GzCoord
	static void MatrixVectorMult(GzMatrix, GzCoord);

	//I don't want to talk about it
	static void MatrixVectorMult(GzMatrix, Point &p);

	//Calculates the cross product
	static void CrossProduct(float* vecOne, float* vecTwo, float* returnVal);

	static void NormalizeMatrix(GzMatrix);

private:
	MatrixEquations(); //Dont' construct
};

