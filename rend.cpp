/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"Ray.h"
#include	"rend.h"
#include "LineEquations.h"
#include "MatrixEquations.h"

#define PI (float) 3.14159265358979323846

inline float ConvertToRadians(float degree) {
	return degree * (PI / 180.0);
}

int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
	/* HW 3.1
	// Create rotate matrix : rotate along x axis
	// Pass back the matrix using mat value
	*/
	float radian = ConvertToRadians(degree);

	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = cos(radian);
	mat[1][2] = -1 * sin(radian);
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = sin(radian);
	mat[2][2] = cos(radian);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}

int GzRender::GzRotYMat(float degree, GzMatrix mat)
{
	/* HW 3.2
	// Create rotate matrix : rotate along y axis
	// Pass back the matrix using mat value
	*/
	float radian = ConvertToRadians(degree);
	mat[0][0] = cos(radian);
	mat[0][1] = 0;
	mat[0][2] = sin(radian);
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = -1 * sin(radian);
	mat[2][1] = 0;
	mat[2][2] = cos(radian);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}

int GzRender::GzRotZMat(float degree, GzMatrix mat)
{
	/* HW 3.3
	// Create rotate matrix : rotate along z axis
	// Pass back the matrix using mat value
	*/
	float radian = ConvertToRadians(degree);
	mat[0][0] = cos(radian);
	mat[0][1] = -1 * sin(radian);
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = sin(radian);
	mat[1][1] = cos(radian);
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}

int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat)
{
	/* HW 3.4
	// Create translation matrix
	// Pass back the matrix using mat value
	*/
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = translate[0];

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = translate[1];

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = translate[2];

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}


int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
	/* HW 3.5
	// Create scaling matrix
	// Pass back the matrix using mat value
	*/

	mat[0][0] = scale[0];
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = scale[1];
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = scale[2];
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}

int GzRender::GzDefaultCamera() {

	m_camera.lookat[0] = 0;
	m_camera.lookat[1] = 0;
	m_camera.lookat[2] = 0;

	m_camera.position[0] = DEFAULT_IM_X;
	m_camera.position[1] = DEFAULT_IM_Y;
	m_camera.position[2] = DEFAULT_IM_Z;

	m_camera.worldup[0] = 0;
	m_camera.worldup[1] = 1;
	m_camera.worldup[2] = 0;

	m_camera.FOV = DEFAULT_FOV;

	return GZ_SUCCESS;
}

GzRender::GzRender(int xRes, int yRes) : xres(xRes), yres(yRes)
{
	/* HW1.1 create a framebuffer for MS Windows display:
	 -- set display resolution
	 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
	 -- allocate memory for pixel buffer
	 */
	framebuffer = new char[xRes*yRes * 3];
	pixelbuffer = new GzPixel[xRes * yRes]; //Allocate Pixelbuffer memory
	//tribuffer = new Gz_Tridata[???] //Allocate tri memory


/* HW 3.6
- setup Xsp and anything only done once
- init default camera
*/
//Initialize variables
	matlevel = 0;
	numlights = 0;

	//Initialize camera
	GzDefaultCamera();

}

GzRender::~GzRender()
{
	/* HW1.2 clean up, free buffer memory */
	delete[] framebuffer;
	delete[] pixelbuffer;
}

int GzRender::GzDefault()
{
	/* HW1.3 set pixel buffer to some default values - start a new frame */
			/* HW1.3 set pixel buffer to some default values - start a new frame */
	GzIntensity defaultVal = 2500;
	GzPixel p = { 0, defaultVal, defaultVal, 1, INT_MAX };

	for (int i = 0; i < xres * yres; i++) {
		pixelbuffer[i] = p;
	}
	return GZ_SUCCESS;
}

//Clamps max and min values
inline void ClampIntensity(GzIntensity &val) {
	if (val > 4095) {
		val = 4095;
	}
	else if (val < 0) {
		val = 0;
	}
}

//Checks bounds on i and j against xres and yres
bool GzRender::CheckBounds(const int &i, const int &j) const {
	if (i >= xres || i < 0 || j >= yres || j < 0) {
		return false;
	}
	return true;
}

void ComputeXiw(GzMatrix target, GzCamera &cam) {
	float zVec[] = { cam.lookat[X] - cam.position[X],
			cam.lookat[Y] - cam.position[Y],
			cam.lookat[Z] - cam.position[Z] };
	MatrixEquations::NormalizeVectorThree(zVec);

	float uPZDot = MatrixEquations::DotProduct(cam.worldup, zVec, 3);
	float yVec[] = { cam.worldup[X] - zVec[X] * uPZDot,
					cam.worldup[Y] - zVec[Y] * uPZDot,
					cam.worldup[Z] - zVec[Z] * uPZDot };
	MatrixEquations::NormalizeVectorThree(yVec);

	float xVec[3];
	MatrixEquations::CrossProduct(yVec, zVec, xVec);

	MatrixEquations::FillMatrix(target,
		xVec[X], xVec[Y], xVec[Z], -1 * MatrixEquations::DotProduct(xVec, cam.position, 3),
		yVec[X], yVec[Y], yVec[Z], -1 * MatrixEquations::DotProduct(yVec, cam.position, 3),
		zVec[X], zVec[Y], zVec[Z], -1 * MatrixEquations::DotProduct(zVec, cam.position, 3),
		0, 0, 0, 1);

}

//Compute Xiw inverse here
void ComputeXwi(GzMatrix target) {

}

//Initialize renderer
int GzRender::GzBeginRender()
{
	//Used for renderer intialization. No longer need transformations past world space.
	//Use this for other initialization.
	GzMatrix Xwi =
	{
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	};

	ComputeXwi(Xwi);
	//Need to store and convert lights, camera, etc

	return GZ_SUCCESS;
}

int GzRender::GzPutCamera(GzCamera camera)
{
	/* HW 3.8
	/*- overwrite renderer camera structure with new camera definition
	*/
	m_camera.FOV = camera.FOV;
	memcpy(m_camera.lookat, camera.lookat, sizeof(GzCoord));
	memcpy(m_camera.worldup, camera.worldup, sizeof(GzCoord));
	memcpy(m_camera.position, camera.position, sizeof(GzCoord));

	return GZ_SUCCESS;
}

int GzRender::GzPushMatrix(GzMatrix	matrix)
{
	/* HW 3.9
	- push a matrix onto the Ximage stack
	- check for stack overflow
	*/

	if (matlevel > 20) {
		//Capped at 20
		return GZ_FAILURE;
	}

	if (matlevel == 0) {
		memcpy(Ximage[0], matrix, sizeof(GzMatrix));
	}
	else {
		MatrixEquations::MultMatrices(Ximage[matlevel - 1], matrix, Ximage[matlevel]);
	}

	/* HW 4 */
	if (matlevel < 2) {
		GzMatrix identity = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
		memcpy(Xnorm[matlevel], identity, sizeof(GzMatrix));
	}
	else {
		MatrixEquations::NormalizeMatrix(matrix);
		matrix[0][3] = 0;
		matrix[1][3] = 0;
		matrix[2][3] = 0;
		MatrixEquations::MultMatrices(Xnorm[matlevel - 1], matrix, Xnorm[matlevel]);
	}
	matlevel++;

	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix()
{
	/* HW 3.10
	- pop a matrix off the Ximage stack
	- check for stack underflow
	*/

	if (matlevel == 0) {
		//Tried to pop too far.
		return GZ_FAILURE;
	}
	matlevel--;

	return GZ_SUCCESS;
}

int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
	/* HW1.4 write pixel values into the buffer */
	if (CheckBounds(i, j)) {

		//Clamp intensity
		ClampIntensity(r);
		ClampIntensity(g);
		ClampIntensity(b);
		ClampIntensity(a);

		GzPixel p = { r, g, b, a, z };

		pixelbuffer[ARRAY(i, j)] = p;
	}
	return GZ_SUCCESS;
}

int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
	/* HW1.5 retrieve a pixel information from the pixel buffer */
	if (CheckBounds(i, j)) {

		GzPixel p = pixelbuffer[ARRAY(i, j)];
		*r, *g, *b, *a, *z = p.red, p.green, p.blue, p.alpha, p.z;
	}
	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
	/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	fprintf(outfile, "P6 %d %d 255\r", xres, yres);

	int pixelIndex;
	int size = 3;
	char colorBuffer[3];

	//Need to iterate through pixelbuffer to set values
	//This probably has more computational overhead but saves on space
	for (int i = 0; i < xres*yres * 3; i += 3) {

		pixelIndex = i / 3;

		colorBuffer[0] = pixelbuffer[pixelIndex].red >> 4;
		colorBuffer[1] = pixelbuffer[pixelIndex].green >> 4;
		colorBuffer[2] = pixelbuffer[pixelIndex].blue >> 4;
		fwrite(colorBuffer, sizeof(char), sizeof(char)*size, outfile);
	}
	return GZ_SUCCESS;
}

int GzRender::GzFlushDisplay2FrameBuffer()
{
	/* HW1.7 write pixels to framebuffer:
		- put the pixels into the frame buffer
		- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red
		- NOT red, green, and blue !!!
	*/
	int pixelIndex;

	for (int i = 0; i < xres*yres * 3; i += 3) {

		pixelIndex = i / 3;

		framebuffer[i] = pixelbuffer[pixelIndex].blue >> 4;
		framebuffer[i + 1] = pixelbuffer[pixelIndex].green >> 4;
		framebuffer[i + 2] = pixelbuffer[pixelIndex].red >> 4;

	}
	return GZ_SUCCESS;
}


int GzRender::GzPutAttribute(int numAttributes, GzToken	*nameList, GzPointer *valueList)
{
	/* HW 2.1
	-- Set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
	-- In later homeworks set shaders, interpolaters, texture maps, and lights
	*/


	for (int i = 0; i < numAttributes; i++) {
		//Get token
		int tokenType = nameList[i];

		switch (tokenType) {
			//If token is color token
		case GZ_RGB_COLOR:
			flatcolor[0] = ctoi(((float*)valueList[i])[0]);
			flatcolor[1] = ctoi(((float*)valueList[i])[1]);
			flatcolor[2] = ctoi(((float*)valueList[i])[2]);
			break;
		case GZ_INTERPOLATE:
			interp_mode = ((int*)valueList[i])[0];
			break;
		case GZ_DIRECTIONAL_LIGHT:
		{
			GzLight* lightPtr = (GzLight*)valueList[i];
			lights[numlights].direction[0] = lightPtr->direction[0];
			lights[numlights].direction[1] = lightPtr->direction[1];
			lights[numlights].direction[2] = lightPtr->direction[2];
			lights[numlights].color[0] = lightPtr->color[0];
			lights[numlights].color[1] = lightPtr->color[1];
			lights[numlights].color[2] = lightPtr->color[2];
			numlights++;
		}
		break;
		case GZ_AMBIENT_LIGHT:
		{
			//Ignore direction on purpose
			GzLight* ambientLightPtr = (GzLight*)valueList[i];
			ambientlight.color[0] = ambientLightPtr->color[0];
			ambientlight.color[1] = ambientLightPtr->color[1];
			ambientlight.color[2] = ambientLightPtr->color[2];
		}
		break;
		case GZ_AMBIENT_COEFFICIENT:
		{
			float* ambientCE = (float*)valueList[i];
			Ka[0] = ambientCE[0];
			Ka[1] = ambientCE[1];
			Ka[2] = ambientCE[2];
		}
		break;
		case GZ_DIFFUSE_COEFFICIENT:
		{
			float* diffuseCE = (float*)valueList[i];
			Kd[0] = diffuseCE[0];
			Kd[1] = diffuseCE[1];
			Kd[2] = diffuseCE[2];
		}
		break;
		case GZ_SPECULAR_COEFFICIENT:
		{
			float* specCE = (float*)valueList[i];
			Ks[0] = specCE[0];
			Ks[1] = specCE[1];
			Ks[2] = specCE[2];
		}
		break;
		case GZ_DISTRIBUTION_COEFFICIENT:
		{
			float* distCE = (float*)valueList[i];
			spec = *distCE;
		}
		break;
		
		case GZ_TEXTURE_MAP:
		{
			tex_fun = (GzTexture) valueList[i];
		}
		break;
		}

	}

	return GZ_SUCCESS;
}


/*Creates an array of pixels to be tested. Sets size of array*/
int* GzRender::GetTestablePixels(GzCoord* ptr, int &size) {

	float lowestX, highestX, lowestY, highestY;
	float *vertOne = (float*)ptr[0];

	float *vertTwo = (float*)ptr[1];

	float *vertThree = (float*)ptr[2];

	float xVals[3] = { vertOne[0], vertTwo[0], vertThree[0] };
	float yVals[3] = { vertOne[1], vertTwo[1], vertThree[1] };



	auto eval = [](float vals[3], float &returnVal, bool highest) {
		returnVal = vals[0];
		if (highest) {
			if (returnVal < vals[1]) {
				returnVal = vals[1];
			}

			if (returnVal < vals[2]) {
				returnVal = vals[2];
			}
		}
		else {
			if (returnVal > vals[1]) {
				returnVal = vals[1];
			}

			if (returnVal > vals[2]) {
				returnVal = vals[2];
			}
		}

	};

	eval(xVals, lowestX, false);
	eval(yVals, lowestY, false);
	eval(xVals, highestX, true);
	eval(yVals, highestY, true);

	//Ceiling only because of less than eval in for loop
	int lowestIntX = ceil(lowestX);
	int lowestIntY = ceil(lowestY);
	int highestIntX = ceil(highestX);
	int highestIntY = ceil(highestY);

	//Set size for return
	size = (highestIntY - lowestIntY)*(highestIntX - lowestIntX);

	int* pixelsToBeTested = new int[size];
	int index = 0;
	for (int i = lowestIntX; i < highestIntX; i++) {
		for (int j = lowestIntY; j < highestIntY; j++) {
			pixelsToBeTested[index] = ARRAY(i, j);
			index++;
		}
	}


	return pixelsToBeTested;

}

/*Evaluate pixels to see if they are in tri. If they are, write value over unused
pixel indexes, set new size.
*/
void GzRender::FindPixelsInTri(GzCoord* ptr, GzCoord* normalPtr, GzTextureIndex* uvList, int* pixels, int &size) {

	//Sort verts
	LineEquations::OrderVerts(ptr, normalPtr, uvList); //Normals added to keep in sync

	//LR evaluation here.
	//Line data:
	float* tail = (float*)ptr;
	float* head = (float*)(ptr + 1);
	float coefficients[3];
	float coefficientsTwo[3];
	float coefficientsThree[3];
	LineEquations::GetLineCoefficients(tail, head, coefficients);
	tail = head;
	head = (float*)(ptr + 2);
	LineEquations::GetLineCoefficients(tail, head, coefficientsTwo);
	tail = head;
	head = (float*)ptr;
	LineEquations::GetLineCoefficients(tail, head, coefficientsThree);
	int curIndex = 0;
	int x, y;

	//DOESN'T INCLUDE ON THE LINE PIXEL EDGE CASE, ADD LATER
	for (int i = 0; i < size; i++) {
		x = pixels[i] % yres;
		y = pixels[i] / xres;
		if (LineEquations::EvaluatePointByLine(coefficients, x, y)
			&& LineEquations::EvaluatePointByLine(coefficientsTwo, x, y)
			&& LineEquations::EvaluatePointByLine(coefficientsThree, x, y))
		{
			pixels[curIndex] = pixels[i];
			curIndex++;
		}
	}

	size = curIndex; //Set new size
}

int GzRender::GzPutTriangle(int	numParts, GzToken *nameList, GzPointer *valueList)
/* numParts - how many names and values */
{
	/* HW 2.2
	-- Pass in a triangle description with tokens and values corresponding to
		  GZ_NULL_TOKEN:		do nothing - no values
		  GZ_POSITION:		3 vert positions in model space
	-- Invoke the rastrizer/scanline framework
	-- Return error code
	*/
	/* use position stuff to edit pixelbuffer directly to draw it*/

	GzCoord* normalPtr;
	GzCoord* valuePtr;
	GzTextureIndex* uvList;
	//Convert normals to image space
	for (int j = 0; j < numParts; j++) {
		if (nameList[j] == GZ_NORMAL) {
			normalPtr = (GzCoord*)valueList[j];
			MatrixEquations::MatrixVectorMult(Xnorm[matlevel - 1], (float*)normalPtr);
			MatrixEquations::MatrixVectorMult(Xnorm[matlevel - 1], (float*)normalPtr[1]);
			MatrixEquations::MatrixVectorMult(Xnorm[matlevel - 1], (float*)normalPtr[2]);

			//Can normalize matrices when pushed instead for large computational gain
			MatrixEquations::NormalizeVectorThree((float*)normalPtr[0]);
			MatrixEquations::NormalizeVectorThree((float*)normalPtr[1]);
			MatrixEquations::NormalizeVectorThree((float*)normalPtr[2]);

		}
	}

	for (int j = 0; j < numParts; j++) {
		if (nameList[j] == GZ_TEXTURE_INDEX) {
			uvList = (GzTextureIndex*)valueList[j]; //Size 3 uvList
		}
	}

	//Find pixels, write color and write to FB
	for (int j = 0; j < numParts; j++) {
		//evaluate Tokens
		if (nameList[0] == GZ_POSITION) {

			valuePtr = (GzCoord*)valueList[0];

			//Convert model coords to screen coords
			bool onScreen = MatrixEquations::MatrixVectorMult(Ximage[matlevel - 1], (float*)valuePtr) &&
				MatrixEquations::MatrixVectorMult(Ximage[matlevel - 1], (float*)valuePtr[1]) &&
				MatrixEquations::MatrixVectorMult(Ximage[matlevel - 1], (float*)valuePtr[2]);

			//Check if Z val is behind screen
			if (!onScreen) {
				return GZ_SUCCESS;
			}

			//Get pixels to test
			int size;
			int* pixels = GetTestablePixels(valuePtr, size);

			//Test and get the pixels in the tri
			FindPixelsInTri(valuePtr, normalPtr, uvList, pixels, size);

			//Get A,B,C coefficients for a plane for Z interp
			float planeCoefficients[4];
			LineEquations::GetPlaneCoefficients((float*)(valuePtr[0]), (float*)(valuePtr[1]), (float*)(valuePtr[2]), planeCoefficients);

			if (interp_mode == GZ_FLAT) {
				GzFlatShading(pixels, size, planeCoefficients);
			}
			else if (interp_mode == GZ_COLOR) {
				GzGouraudShading(pixels, size, valuePtr, normalPtr, planeCoefficients, uvList);
			}
			else if (interp_mode == GZ_NORMALS) {
				GzPhongShading(pixels, size, valuePtr, normalPtr, planeCoefficients, uvList);
			}

			delete[] pixels;

		}
	}


	return GZ_SUCCESS;
}

void GzRender::CalculateColor(float normal[3], float returnColor[3]) {

	float specularComponentR = 0;
	float specularComponentG = 0;
	float specularComponentB = 0;
	float diffuseComponentR = 0;
	float diffuseComponentG = 0;
	float diffuseComponentB = 0;
	float eVec[3] = { 0,0,-1 };

	//Specular Component calculation
	for (int i = 0; i < numlights; i++) {

		//Calc R
		float NLDot = MatrixEquations::DotProduct(normal, lights[i].direction, 3);
		float NEDot = MatrixEquations::DotProduct(normal, eVec, 3);
		float testingSigns = NLDot * NEDot;

		if (testingSigns < 0) {
			//Light and eye vec are on different sides
			continue;
		}
		//Reliant on testing signs, this means that both dot prods are negative. Flip normal
		if (NLDot < 0) {
			normal[0] *= -1;
			normal[1] *= -1;
			normal[2] *= -1;

			NLDot = MatrixEquations::DotProduct(normal, lights[i].direction, 3);
		}

		float rVec[3] = {
			2 * NLDot*normal[0] - lights[i].direction[0],
			2 * NLDot*normal[1] - lights[i].direction[1],
			2 * NLDot*normal[2] - lights[i].direction[2]
		};

		MatrixEquations::NormalizeVectorThree(rVec);

		float REDot = MatrixEquations::DotProduct(rVec, eVec, 3);
		if (REDot > 1) { REDot = 1; }
		else if (REDot < 0) { REDot = 0; }

		REDot = pow(REDot, spec);

		specularComponentR += lights[i].color[RED] * REDot;
		specularComponentG += lights[i].color[GREEN] * REDot;
		specularComponentB += lights[i].color[BLUE] * REDot;

		//Diffuse
		diffuseComponentR += lights[i].color[RED] * NLDot;
		diffuseComponentG += lights[i].color[GREEN] * NLDot;
		diffuseComponentB += lights[i].color[BLUE] * NLDot;

	}

	//Spec
	returnColor[RED] = specularComponentR * Ks[RED] + diffuseComponentR * Kd[RED] + ambientlight.color[RED] * Ka[RED];
	returnColor[GREEN] = specularComponentG * Ks[GREEN] + diffuseComponentG * Kd[GREEN] + ambientlight.color[GREEN] * Ka[GREEN];
	returnColor[BLUE] = specularComponentB * Ks[BLUE] + diffuseComponentB * Kd[BLUE] + ambientlight.color[BLUE] * Ka[BLUE];

}

void GzRender::CalculateGouraudColor(float normal[3], float returnColor[3]) {

	float specularComponentR = 0;
	float specularComponentG = 0;
	float specularComponentB = 0;
	float diffuseComponentR = 0;
	float diffuseComponentG = 0;
	float diffuseComponentB = 0;
	float eVec[3] = { 0,0,-1 };

	//Specular Component calculation
	for (int i = 0; i < numlights; i++) {

		//Calc R
		float NLDot = MatrixEquations::DotProduct(normal, lights[i].direction, 3);
		float NEDot = MatrixEquations::DotProduct(normal, eVec, 3);
		float testingSigns = NLDot * NEDot;

		if (testingSigns < 0) {
			//Light and eye vec are on different sides
			continue;
		}
		//Reliant on testing signs, this means that both dot prods are negative. Flip normal
		if (NLDot < 0) {
			normal[0] *= -1;
			normal[1] *= -1;
			normal[2] *= -1;

			NLDot = MatrixEquations::DotProduct(normal, lights[i].direction, 3);
		}

		float rVec[3] = {
			2 * NLDot*normal[0] - lights[i].direction[0],
			2 * NLDot*normal[1] - lights[i].direction[1],
			2 * NLDot*normal[2] - lights[i].direction[2]
		};

		MatrixEquations::NormalizeVectorThree(rVec);

		float REDot = MatrixEquations::DotProduct(rVec, eVec, 3);
		if (REDot > 1) { REDot = 1; }
		else if (REDot < 0) { REDot = 0; }

		REDot = pow(REDot, spec);

		specularComponentR += lights[i].color[RED] * REDot;
		specularComponentG += lights[i].color[GREEN] * REDot;
		specularComponentB += lights[i].color[BLUE] * REDot;

		//Diffuse
		diffuseComponentR += lights[i].color[RED] * NLDot;
		diffuseComponentG += lights[i].color[GREEN] * NLDot;
		diffuseComponentB += lights[i].color[BLUE] * NLDot;

	}

	//Spec
	returnColor[RED] = specularComponentR + diffuseComponentR + ambientlight.color[RED];
	returnColor[GREEN] = specularComponentG + diffuseComponentG + ambientlight.color[GREEN];
	returnColor[BLUE] = specularComponentB + diffuseComponentB + ambientlight.color[BLUE];

}

void ColorOverflowCorrection(float colorValue[3]) {
	//Color overflow correction
	if (colorValue[RED] > 1)
	{
		colorValue[RED] = 1;
	}
	if (colorValue[GREEN] > 1)
	{
		colorValue[GREEN] = 1;
	}
	if (colorValue[BLUE] > 1)
	{
		colorValue[BLUE] = 1;
	}
}

//Flat shading using a constant flat color
void GzRender::GzFlatShading(int* pixels, int &size, float* planeCoefficients) {
	//Write to pixelbuffer with the data (while Z testing)
	GzPixel p = { flatcolor[0], flatcolor[1], flatcolor[2], 1, 0 };

	int x, y, z;

	for (int i = 0; i < size; i++) {
		int index = pixels[i];

		//Value not on screen
		if (index > yres*xres || index < 0) {
			continue;
		}
		x = index % yres;
		y = index / xres;
		z = (int)LineEquations::InterpolateZ(planeCoefficients, x, y);
		if (pixelbuffer[index].z < z) {
			continue;
		}
		p.z = (GzDepth)z;
		pixelbuffer[index] = p;

	}
}

void GetUVCoefficients(GzTextureIndex* uvList, GzCoord* vertPtr, float uValueCoefficients[4], float vValueCoefficients[4]) {
	
	float uPerspective[3];
	float vPerspective[3];
	float vPrime;

	for (int i = 0; i < 3; i++) {
		vPrime = vertPtr[i][2] / (MAXINT - vertPtr[i][2]);
		uPerspective[i] = uvList[i][0] / (vPrime + 1);
		vPerspective[i] = uvList[i][1] / (vPrime + 1);
	}
	
	float uOne[3] = { vertPtr[0][0], vertPtr[0][1], uPerspective[0] };
	float uTwo[3] = { vertPtr[1][0], vertPtr[1][1], uPerspective[1] };
	float uThree[3] = { vertPtr[2][0], vertPtr[2][1], uPerspective[2] };
	LineEquations::GetPlaneCoefficients(uOne, uTwo, uThree, uValueCoefficients);

	float vOne[3] = { vertPtr[0][0], vertPtr[0][1], vPerspective[0] };
	float vTwo[3] = { vertPtr[1][0], vertPtr[1][1], vPerspective[1] };
	float vThree[3] = { vertPtr[2][0], vertPtr[2][1], vPerspective[2] };
	LineEquations::GetPlaneCoefficients(vOne, vTwo, vThree, vValueCoefficients);

}

//Render the pixel with Gouraud Shading
void GzRender::GzGouraudShading(int* pixels, int &size, GzCoord* vertPtr, GzCoord* normals, float* zPlaneCoefficients, GzTextureIndex* uvList) {

	//Calculate color at verts
	float vertColorOne[3];
	float vertColorTwo[3];
	float vertColorThree[3];
	if (tex_fun != 0) {
		CalculateGouraudColor((float*)normals, vertColorOne);
		CalculateGouraudColor((float*)(normals[1]), vertColorTwo);
		CalculateGouraudColor((float*)(normals[2]), vertColorThree);
	}
	else {
		CalculateColor((float*)normals, vertColorOne);
		CalculateColor((float*)(normals[1]), vertColorTwo);
		CalculateColor((float*)(normals[2]), vertColorThree);
	}



	//Create plane equation based on colors for each val
	float rPlaneCoefficients[4];
	float gPlaneCoefficients[4];
	float bPlaneCoefficients[4];

	float rColorInterpOne[3] = { vertPtr[0][0], vertPtr[0][1], vertColorOne[0] };
	float rColorInterpTwo[3] = { vertPtr[1][0], vertPtr[1][1], vertColorTwo[0] };
	float rColorInterpThree[3] = { vertPtr[2][0], vertPtr[2][1], vertColorThree[0] };
	LineEquations::GetPlaneCoefficients(rColorInterpOne, rColorInterpTwo, rColorInterpThree, rPlaneCoefficients);

	float gColorInterpOne[3] = { vertPtr[0][0], vertPtr[0][1], vertColorOne[1] };
	float gColorInterpTwo[3] = { vertPtr[1][0], vertPtr[1][1], vertColorTwo[1] };
	float gColorInterpThree[3] = { vertPtr[2][0], vertPtr[2][1], vertColorThree[1] };
	LineEquations::GetPlaneCoefficients(gColorInterpOne, gColorInterpTwo, gColorInterpThree, gPlaneCoefficients);

	float bColorInterpOne[3] = { vertPtr[0][0], vertPtr[0][1], vertColorOne[2] };
	float bColorInterpTwo[3] = { vertPtr[1][0], vertPtr[1][1], vertColorTwo[2] };
	float bColorInterpThree[3] = { vertPtr[2][0], vertPtr[2][1], vertColorThree[2] };
	LineEquations::GetPlaneCoefficients(bColorInterpOne, bColorInterpTwo, bColorInterpThree, bPlaneCoefficients);

	float uValueCoefficients[4];
	float vValueCoefficients[4];
	GetUVCoefficients(uvList, vertPtr, uValueCoefficients, vValueCoefficients);

	//Interp and write each pixel val
	GzPixel p = { 0, 0, 0, 1, 0 };

	int x, y, z;

	for (int i = 0; i < size; i++) {
		int index = pixels[i];

		//Value not on screen
		if (index > yres*xres || index < 0) {
			continue;
		}
		x = index % yres;
		y = index / xres;
		float zInterp = LineEquations::InterpolateZ(zPlaneCoefficients, x, y);
		z = (int)zInterp;
		if (pixelbuffer[index].z < z) {
			continue;
		}

		float color[3];

		if (tex_fun != 0) {

			float uVal = LineEquations::InterpolateZ(uValueCoefficients, x, y);
			float vVal = LineEquations::InterpolateZ(vValueCoefficients, x, y);

			////Return u,v to image space
			float vPrime = zInterp / (MAXINT - zInterp);
			uVal = uVal * (vPrime + 1);
			vVal = vVal * (vPrime + 1);

			GzColor textureColor;
			tex_fun(uVal, vVal, textureColor);

			color[RED] = LineEquations::InterpolateZ(rPlaneCoefficients, x, y) * textureColor[RED];
			color[GREEN] = LineEquations::InterpolateZ(gPlaneCoefficients, x, y) * textureColor[GREEN];
			color[BLUE] = LineEquations::InterpolateZ(bPlaneCoefficients, x, y) * textureColor[BLUE];
		}
		else {
			color[RED] = LineEquations::InterpolateZ(rPlaneCoefficients, x, y);
			color[GREEN] = LineEquations::InterpolateZ(gPlaneCoefficients, x, y);
			color[BLUE] = LineEquations::InterpolateZ(bPlaneCoefficients, x, y);
		}


		ColorOverflowCorrection(color);

		p.red =  color[RED] * 4095;
		p.green = color[GREEN] * 4095;
		p.blue = color[BLUE] * 4095;

		p.z = (GzDepth)z;
		pixelbuffer[index] = p;

	}

}


void GetNormalCoefficients(GzCoord* vertPtr, GzCoord* normals, float xValueCoefficients[4], float yValueCoefficients[4], float zValueCoefficients[4]) {

	//Create normal coefficients

	float normalXOne[3] = { vertPtr[0][0], vertPtr[0][1], normals[0][0] };
	float normalXTwo[3] = { vertPtr[1][0], vertPtr[1][1], normals[1][0] };
	float normalXThree[3] = { vertPtr[2][0], vertPtr[2][1], normals[2][0] };
	LineEquations::GetPlaneCoefficients(normalXOne, normalXTwo, normalXThree, xValueCoefficients);

	float normalYOne[3] = { vertPtr[0][0], vertPtr[0][1], normals[0][1] };
	float normalYTwo[3] = { vertPtr[1][0], vertPtr[1][1], normals[1][1] };
	float normalYThree[3] = { vertPtr[2][0], vertPtr[2][1], normals[2][1] };
	LineEquations::GetPlaneCoefficients(normalYOne, normalYTwo, normalYThree, yValueCoefficients);

	float normalZOne[3] = { vertPtr[0][0], vertPtr[0][1], normals[0][2] };
	float normalZTwo[3] = { vertPtr[1][0], vertPtr[1][1], normals[1][2] };
	float normalZThree[3] = { vertPtr[2][0], vertPtr[2][1], normals[2][2] };
	LineEquations::GetPlaneCoefficients(normalZOne, normalZTwo, normalZThree, zValueCoefficients);
}

void GzRender::CalculatePhongColor(float normal[3], float returnColor[3], float newKd[3], float newKa[3]) {

	float specularComponentR = 0;
	float specularComponentG = 0;
	float specularComponentB = 0;
	float diffuseComponentR = 0;
	float diffuseComponentG = 0;
	float diffuseComponentB = 0;
	float eVec[3] = { 0,0,-1 };

	//Specular Component calculation
	for (int i = 0; i < numlights; i++) {

		//Calc R
		float NLDot = MatrixEquations::DotProduct(normal, lights[i].direction, 3);
		float NEDot = MatrixEquations::DotProduct(normal, eVec, 3);
		float testingSigns = NLDot * NEDot;

		if (testingSigns < 0) {
			//Light and eye vec are on different sides
			continue;
		}
		//Reliant on testing signs, this means that both dot prods are negative. Flip normal
		if (NLDot < 0) {
			normal[0] *= -1;
			normal[1] *= -1;
			normal[2] *= -1;

			NLDot = MatrixEquations::DotProduct(normal, lights[i].direction, 3);
		}

		float rVec[3] = {
			2 * NLDot*normal[0] - lights[i].direction[0],
			2 * NLDot*normal[1] - lights[i].direction[1],
			2 * NLDot*normal[2] - lights[i].direction[2]
		};

		MatrixEquations::NormalizeVectorThree(rVec);

		float REDot = MatrixEquations::DotProduct(rVec, eVec, 3);
		if (REDot > 1) { REDot = 1; }
		else if (REDot < 0) { REDot = 0; }

		REDot = pow(REDot, spec);

		specularComponentR += lights[i].color[RED] * REDot;
		specularComponentG += lights[i].color[GREEN] * REDot;
		specularComponentB += lights[i].color[BLUE] * REDot;

		//Diffuse
		diffuseComponentR += lights[i].color[RED] * NLDot;
		diffuseComponentG += lights[i].color[GREEN] * NLDot;
		diffuseComponentB += lights[i].color[BLUE] * NLDot;

	}

	//Spec
	returnColor[RED] = specularComponentR * Ks[RED] + diffuseComponentR * newKd[RED] + ambientlight.color[RED] * newKa[RED];
	returnColor[GREEN] = specularComponentG * Ks[GREEN] + diffuseComponentG * newKd[GREEN] + ambientlight.color[GREEN] * newKa[GREEN];
	returnColor[BLUE] = specularComponentB * Ks[BLUE] + diffuseComponentB * newKd[BLUE] + ambientlight.color[BLUE] * newKa[BLUE];

}

//Render with Phong Shading
void GzRender::GzPhongShading(int* pixels, int &size, GzCoord* vertPtr, GzCoord* normals, float* zPlaneCoefficients, GzTextureIndex* uvList) {

	float xValueCoefficients[4];
	float yValueCoefficients[4];
	float zValueCoefficients[4];
	GetNormalCoefficients(vertPtr, normals, xValueCoefficients, yValueCoefficients, zValueCoefficients);

	float uValueCoefficients[4];
	float vValueCoefficients[4];
	GetUVCoefficients(uvList, vertPtr, uValueCoefficients, vValueCoefficients);

	//Interp and write each pixel val
	GzPixel p = { 0, 0, 0, 1, 0 };

	int x, y, z;

	for (int i = 0; i < size; i++) {
		int index = pixels[i];

		//Value not on screen
		if (index > yres*xres || index < 0) {
			continue;
		}
		x = index % yres;
		y = index / xres;
		float zInterp = LineEquations::InterpolateZ(zPlaneCoefficients, x, y);
		z = (int)zInterp;
		if (pixelbuffer[index].z < z) {
			continue;
		}

		//Color calculation
		float colorValue[3];

		//Interp normal
		float pixelNormal[3] = { LineEquations::InterpolateZ(xValueCoefficients, x, y),
								LineEquations::InterpolateZ(yValueCoefficients, x, y),
								LineEquations::InterpolateZ(zValueCoefficients, x, y), };
		
		//If there is a texture function set
		if (tex_fun != 0) {
			//Interp uv values
			float uVal = LineEquations::InterpolateZ(uValueCoefficients, x, y);
			float vVal = LineEquations::InterpolateZ(vValueCoefficients, x, y);

			////Return u,v to image space
			float vPrime = zInterp / (MAXINT - zInterp);
			uVal = uVal * (vPrime + 1);
			vVal = vVal * (vPrime + 1);

			GzColor textureColor;
			tex_fun(uVal, vVal, textureColor);
			CalculatePhongColor(pixelNormal, colorValue, textureColor, textureColor);
		}
		else {
			CalculateColor(pixelNormal, colorValue);
		}

		//Color overflow correction
		ColorOverflowCorrection(colorValue);

		//Set color value
		p.red = colorValue[0] * 4095;
		p.green = colorValue[1] * 4095;
		p.blue = colorValue[2] * 4095;

		p.z = (GzDepth)z;
		pixelbuffer[index] = p;

	}
}



//RAYTRACING CONTENT STARTING HERE. Comments in rend.h

int GzRender::ConvertTri(float val1, float val2, float val3, float val4, float val5, float val6) {
	return GZ_SUCCESS;
}

int RayCast() {
	
	return GZ_SUCCESS;
}

int GzRender::RenderImg() {

	//for every px
		//intersection = Raycast();
		//Calculate color at loc
		//Write to pixelbuffer
	return GZ_SUCCESS;
}

float dotProduct(Point a, Point b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

int FindIntersection(Ray ray, GzCoord vert0, GzCoord vert1, GzCoord vert2, GzCoord intersectingPoint)
{
	float a1 = vert1[X] - vert0[X]; //x2 - x1
	float b1 = vert1[Y] - vert0[Y]; //y2 - y1
	float c1 = vert1[Z] - vert0[Z]; //z2 - z1
	float a2 = vert2[X] - vert0[X]; //x3 - x1
	float b2 = vert2[Y] - vert0[Y]; //y3 - y1
	float c2 = vert2[Z] - vert0[Z]; //z3 - z1
	float planeConstantA = (b1 * c2) - (b2 * c1);
	float planeConstantB = (a2 * c1) - (a1 * c2);
	float planeConstantC = (a1 * b2) - (b1 * a2);
	float planeConstantD = (-planeConstantA * (vert0[X]) - planeConstantB * (vert0[Y]) - planeConstantC * (vert0[Z])); // -aX1 - bY1 - cZ1

	Point planeNormal;
	planeNormal.x = planeConstantA;
	planeNormal.y = planeConstantB;
	planeNormal.z = planeConstantC;

	GzLine line;
	line.direction = ray.getDirection();
	line.point = ray.getOrigin();

	GzPlane plane;
	plane.normal = planeNormal;
	plane.d = planeConstantD;

	// from line = p + t * v
	Point p = line.point;            // (x1, y1, z1)
	Point v = line.direction;        // (Vx, Vy, Vz)

	// from plane: ax + by + cz + d = 0
	Point n = plane.normal;          // (a, b, c)
	float d = plane.d;               // constant term of plane

	// dot products
	float dot1 = dotProduct(n, v);             // a*Vx + b*Vy + c*Vz
	float dot2 = dotProduct(n, p);             // a*x1 + b*y1 + c*z1

	// if denominator=0, no intersect
	if (dot1 == 0)
		return GZ_FAILURE;

	// find t = -(a*x1 + b*y1 + c*z1 + d) / (a*Vx + b*Vy + c*Vz)
	float t = -(dot2 + d) / dot1;

	// find intersection point
	intersectingPoint[X] = p.x + (t * v.x);
	intersectingPoint[Y] = p.y + (t * v.y);
	intersectingPoint[Z] = p.z + (t * v.z);

	return GZ_SUCCESS;
}