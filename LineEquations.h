#pragma once
#include "gz.h"
#include "MatrixEquations.h"

class LineEquations
{
public:
	GzCoord coord;

	//Order vertices
	static void OrderVerts(GzCoord* ptr, GzCoord* normalPtr, GzTextureIndex* uvList);

	//Gets line coefficients based on vert points. verts are size 2 arrays, returnArray size 3
	static void GetLineCoefficients(float* tailVert, float* headVert, float* returnArray);

	//Evaluates index by LEE
	static bool EvaluatePointByLine(float* lineCoefficients, int x, int y);

	//Finds plane coefficients given vertex points (assumes ordered verts)
	static void GetPlaneCoefficients(float* coordOne, float* coordTwo, float* coordThree, float* returnVal);

	//Takes in a float[4], finds z value based on plane coefficients.
	static float InterpolateZ(float* coefficients, int x, int y);

};

