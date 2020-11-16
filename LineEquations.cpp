#include "StdAfx.h"
#include "LineEquations.h"
#include "MatrixEquations.h"
#include <iostream>

void LineEquations::OrderVerts(GzCoord ptr[3], GzCoord normalPtr[3]) {

	float* currentPtr, *nextVal;
	bool topBottomRelationship = false;
	float topBottomVal;
	float otherValue = 0;

	//Order verts by Y
	for (int i = 0; i < 2; i++) {
		for (int j = i+1; j < 3; j++) {
			currentPtr = (float*)ptr[i];
			currentPtr++; //set to Y val
			nextVal = (float*)ptr[j];
			nextVal++; //Set to yval
			//If current is larger than nextval, swap
			
			if (*currentPtr > *nextVal) {
				std::swap(ptr[i], ptr[j]);
				std::swap(normalPtr[i], normalPtr[j]);
			}
			else if (*currentPtr == *nextVal) {
				topBottomRelationship = true;
				topBottomVal = *currentPtr;
				float* findVal = (float*)ptr[0];
				findVal++;
				for (int h = 0; h < 3; h++) {
					if (*findVal != *currentPtr) {
						otherValue = *findVal;
						findVal += 3;
					}
				}
			}
			
		}
	}

	if (topBottomRelationship) {

		if (otherValue > topBottomVal) {
			currentPtr = (float*)ptr[0];
			nextVal = (float*)ptr[1];
			if (*nextVal > *currentPtr) {

				std::swap(ptr[0], ptr[1]);
				std::swap(normalPtr[0], normalPtr[1]);

			}
		}
		else {
			currentPtr = (float*)ptr[1];
			nextVal = (float*)ptr[2];
			if (*nextVal < *currentPtr) {

				std::swap(ptr[1], ptr[2]);
				std::swap(normalPtr[1], normalPtr[2]);

			}
		}
	}
	else {
		//Check LR relationship
		currentPtr = (float*)ptr[1];
		currentPtr++; //Set to yVal
		float y = *currentPtr; //Retain middle vert Y value
		currentPtr--; //Set to xVal
		float coefficients[3];
		GetLineCoefficients(ptr[0], ptr[2], coefficients);
		float xVal = -1 * (coefficients[1] * y + coefficients[2]) / coefficients[0];
		if (xVal > *currentPtr) {
			std::swap(ptr[0], ptr[1]);
			std::swap(normalPtr[0], normalPtr[1]);
		}
	}

}

//returns line coefficients
void LineEquations::GetLineCoefficients(float* tailVert, float* headVert, float* returnArray) {
	
	returnArray[0] = headVert[1] - tailVert[1]; //A = dY
	returnArray[1] = tailVert[0] - headVert[0]; //B = -(dX)
	returnArray[2] = (headVert[0] - tailVert[0]) * tailVert[1] - returnArray[0] * tailVert[0]; //C = (dX * Y) - (dY * X)
}

bool LineEquations::EvaluatePointByLine(float* lineCoefficients, int x, int y) {

	float val = lineCoefficients[0] * x + lineCoefficients[1] * y + lineCoefficients[2];
	if (val <= 0) return true; //need to do 0 check here.
	else { return false; }

}

inline float CalculateD(float* otherCoefficients, float* vert) {
	return -1 * (otherCoefficients[0] * vert[0] + otherCoefficients[1] * vert[1] + otherCoefficients[2] * vert[2]);
}

void LineEquations::GetPlaneCoefficients(float* coordOne, float* coordTwo, float* coordThree, float* returnVal) {
	GzCoord vecOne = { coordTwo[0] - coordOne[0], coordTwo[1] - coordOne[1], coordTwo[2] - coordOne[2] };
	GzCoord vecTwo = { coordThree[0] - coordTwo[0], coordThree[1] - coordTwo[1], coordThree[2] - coordTwo[2] };
	MatrixEquations::CrossProduct((float*)vecOne, (float*)vecTwo, returnVal);
	returnVal[3] = CalculateD(returnVal, coordOne);
}

float LineEquations::InterpolateZ(float* coefficients, int x, int y) {
	float returnVal = (-1 * (coefficients[0] * x + coefficients[1] * y + coefficients[3]) / coefficients[2]);
	return returnVal;
	//return (-1 * (coefficients[0] * x + coefficients[1] * y + coefficients[3]) / coefficients[2]);
}

float LineEquations::InterpolateZFloat(float* coefficients, float x, float y) {
	if (coefficients[2] == 0) {
		return 1;
	}
	float returnVal = (-1 * (coefficients[0] * x + coefficients[1] * y + coefficients[3]) / coefficients[2]);
	return returnVal;
	//return (-1 * (coefficients[0] * x + coefficients[1] * y + coefficients[3]) / coefficients[2]);
}

