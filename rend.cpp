/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
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
	normMatLevel = 0;
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

//Compute Xiw inverse here
void ComputeXwi(GzMatrix target, GzCamera &cam) {
	
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
		xVec[X], yVec[X], zVec[X], cam.position[X],
		xVec[Y], yVec[Y], zVec[Y], cam.position[Y],
		xVec[Z], yVec[Z], zVec[Z], cam.position[Z],
		0, 0, 0, 1);
}

//Initialize renderer
int GzRender::GzBeginRender()
{
	
	//Computes Xwi, stored in GzRender class
	ComputeXwi(Xwi, m_camera);
	//Need to store and convert lights, camera, etc

	return GZ_SUCCESS;
}

int GzRender::GzPutCamera(GzCamera camera, GzMatrix translation)
{
	/* HW 3.8
	/*- overwrite renderer camera structure with new camera definition
	*/

	m_camera.FOV = camera.FOV;
	m_camera.aspect = yres / xres;
	memcpy(m_camera.lookat, camera.lookat, sizeof(GzCoord));
	memcpy(m_camera.worldup, camera.worldup, sizeof(GzCoord));
	memcpy(m_camera.position, camera.position, sizeof(GzCoord));
	memcpy(m_camera.CameraTranslation, translation, sizeof(GzMatrix));

	return GZ_SUCCESS;
}

int GzRender::GzPushMatrix(GzMatrix	matrix, GzMatrix* target, short &counter, bool normalizeMatrix)
{
	/* HW 3.9
	- push a matrix onto the Ximage stack
	- check for stack overflow
	*/
	if (counter > 20) {
		//Capped at 20
		return GZ_FAILURE;
	}

	if (normalizeMatrix) {
		MatrixEquations::NormalizeMatrix(matrix);
		matrix[0][3] = 0;
		matrix[1][3] = 0;
		matrix[2][3] = 0;
	}


	if (counter == 0) {
		memcpy(target[0], matrix, sizeof(GzMatrix));
	}
	else {
		MatrixEquations::MultMatrices(target[counter - 1], matrix, target[counter]);
	}

	counter++;

	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix(int counter)
{
	/* HW 3.10
	- pop a matrix off the Ximage stack
	- check for stack underflow
	*/

	if (counter == 0) {
		//Tried to pop too far.
		return GZ_FAILURE;
	}
	counter--;

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

			//Convert lights from image space to worldspace
			MatrixEquations::MatrixVectorMult(Xwi, lights[numlights].direction);

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

/*EXAMPLE ON HOW TO USE LEE IN THIS CODE
*/
void GzRender::FindPixelsInTri(GzCoord* ptr, GzCoord* normalPtr, GzTextureIndex* uvList, int* pixels, int &size) {

	//Sort verts
	//LineEquations::OrderVerts(ptr, normalPtr, uvList); //Normals added to keep in sync

	////LR evaluation here.
	////Line data:
	//float* tail = (float*)ptr;
	//float* head = (float*)(ptr + 1);
	//float coefficients[3];
	//float coefficientsTwo[3];
	//float coefficientsThree[3];
	//LineEquations::GetLineCoefficients(tail, head, coefficients);
	//tail = head;
	//head = (float*)(ptr + 2);
	//LineEquations::GetLineCoefficients(tail, head, coefficientsTwo);
	//tail = head;
	//head = (float*)ptr;
	//LineEquations::GetLineCoefficients(tail, head, coefficientsThree);
	//int curIndex = 0;
	//int x, y;

	////DOESN'T INCLUDE ON THE LINE PIXEL EDGE CASE, ADD LATER
	//for (int i = 0; i < size; i++) {
	//	x = pixels[i] % yres;
	//	y = pixels[i] / xres;
	//	if (LineEquations::EvaluatePointByLine(coefficients, x, y)
	//		&& LineEquations::EvaluatePointByLine(coefficientsTwo, x, y)
	//		&& LineEquations::EvaluatePointByLine(coefficientsThree, x, y))
	//	{
	//		pixels[curIndex] = pixels[i];
	//		curIndex++;
	//	}
	//}

	//size = curIndex; //Set new size
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


void GetNormalCoefficients(GzCoord vertA, GzCoord vertB, GzCoord vertC, GzCoord normA, GzCoord normB, GzCoord normC, float xValueCoefficients[4], float yValueCoefficients[4], float zValueCoefficients[4]) {

	//Create normal coefficients

	float normalXOne[3] = { vertA[0], vertA[1],normA[0] };
	float normalXTwo[3] = { vertB[0], vertB[1], normB[0] };
	float normalXThree[3] = { vertC[0], vertC[1], normC[0] };
	LineEquations::GetPlaneCoefficients(normalXOne, normalXTwo, normalXThree, xValueCoefficients);

	float normalYOne[3] = { vertA[0], vertA[1], normA[1] };
	float normalYTwo[3] = { vertB[0], vertB[1], normB[1] };
	float normalYThree[3] = { vertC[0], vertC[1], normC[1] };
	LineEquations::GetPlaneCoefficients(normalYOne, normalYTwo, normalYThree, yValueCoefficients);

	float normalZOne[3] = { vertA[0], vertA[1], normA[2] };
	float normalZTwo[3] = { vertB[0], vertB[1], normB[2] };
	float normalZThree[3] = { vertC[0],vertC[1], normC[2] };
	LineEquations::GetPlaneCoefficients(normalZOne, normalZTwo, normalZThree, zValueCoefficients);
}

float dotProduct(Point a, Point b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
float DProduct(GzCoord a, GzCoord b)
{
	return (a[X] * b[X]) + (a[Y] * b[Y]) + (a[Z] * b[Z]);
}

bool crossProduct(const GzCoord v1, const GzCoord v2, GzCoord result)
{
	if (v1 == NULL || v2 == NULL)
		return false;

	if (result == NULL)
		return false;

	// X = (Y x Z) = i (Yy Zz - Yz Zy) + j (Yz Zx - Yx Zz) + k (Yx Zy - Yy Zx) 
	result[X] = ((v1[Y] * v2[Z]) - (v1[Z] * v2[Y]));
	result[Y] = ((v1[Z] * v2[X]) - (v1[X] * v2[Z]));
	result[Z] = ((v1[X] * v2[Y]) - (v1[Y] * v2[X]));

	return true;
}
void cp(GzCoord v1, GzCoord v2, GzCoord result)
{
	result[X] = ((v1[Y] * v2[Z]) - (v1[Z] * v2[Y]));
	result[Y] = ((v1[Z] * v2[X]) - (v1[X] * v2[Z]));
	result[Z] = ((v1[X] * v2[Y]) - (v1[Y] * v2[X]));
}
float vecMagnitude(GzCoord v)
{
	return sqrt(pow(v[X], 2) + pow(v[Y], 2) + pow(v[Z], 2));
}

bool within01Range(float v)
{
	return (0 <= v && v <= 1);
}


void GzRender::CalculatePhongColor(float intersectionPoint[3], float normal[3], float returnColor[3], float newKd[3], float newKa[3]) {

	float specularComponentR = 0;
	float specularComponentG = 0;
	float specularComponentB = 0;
	float diffuseComponentR = 0;
	float diffuseComponentG = 0;
	float diffuseComponentB = 0;
	float eVec[3] = { 0,0,-1 };


	//Specular Component calculation
	for (int i = 0; i < numlights; i++) {
		
		Point dir = { -lights[i].direction[0], -lights[i].direction[1], -lights[i].direction[2] };
		//Point pos = { intersectionPoint[0] + dir.x, intersectionPoint[1] + dir.y, intersectionPoint[2] + dir.z };
		Point pos = { intersectionPoint[0], intersectionPoint[1], intersectionPoint[2]};

		Ray shadowRay(pos, dir);

		GzTridata data;
		GzCoord minIntersect;

		//Check for occlusion
		if (CheckRay(shadowRay, minIntersect, data)) {
			continue;
		}


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
	//returnColor[RED] = specularComponentR * Ks[RED] + diffuseComponentR * newKd[RED] + ambientlight.color[RED] * newKa[RED];
	//returnColor[GREEN] = specularComponentG * Ks[GREEN] + diffuseComponentG * newKd[GREEN] + ambientlight.color[GREEN] * newKa[GREEN];
	//returnColor[BLUE] = specularComponentB * Ks[BLUE] + diffuseComponentB * newKd[BLUE] + ambientlight.color[BLUE] * newKa[BLUE];

	returnColor[RED] = specularComponentR * Ks[RED] + diffuseComponentR * newKd[RED];
	returnColor[GREEN] = specularComponentG * Ks[GREEN] + diffuseComponentG * newKd[GREEN];
	returnColor[BLUE] = specularComponentB * Ks[BLUE] + diffuseComponentB * newKd[BLUE];

}


//RAYTRACING CONTENT STARTING HERE. Comments in rend.h

int GzRender::ConvertTri(GzToken* nameList, GzPointer* valueList)
{
	
	GzCoord* verts;
	GzCoord* normals;

	for (int i = 0; i < 3; i++) {
		if (nameList[i] == GZ_POSITION) {

			verts = (GzCoord*)valueList[i];
		}
		else if (nameList[i] == GZ_NORMAL) {

			normals = (GzCoord*)valueList[i];
		}
	}


	//GzTridata data1;
	//memcpy(data1.vertOne, verts[0], sizeof(GzCoord));
	//memcpy(data1.vertTwo, verts[1], sizeof(GzCoord));
	//memcpy(data1.vertThree, verts[2], sizeof(GzCoord));
	//memcpy(data1.normOne, normals[0], sizeof(GzCoord));
	//memcpy(data1.normTwo, normals[1], sizeof(GzCoord));
	//memcpy(data1.normThree, normals[2], sizeof(GzCoord));

	//tribuffer.push_back(data1);

	MatrixEquations::MatrixVectorMult(Ximage[matlevel-1], verts[0]);
	MatrixEquations::MatrixVectorMult(Ximage[matlevel - 1], verts[1]);
	MatrixEquations::MatrixVectorMult(Ximage[matlevel - 1], verts[2]);

	MatrixEquations::MatrixVectorMult(Xnorm[normMatLevel - 1], normals[0]);
	MatrixEquations::MatrixVectorMult(Xnorm[normMatLevel - 1], normals[1]);
	MatrixEquations::MatrixVectorMult(Xnorm[normMatLevel - 1], normals[2]);


	//put data into gztridata
	GzTridata data;
	memcpy(data.vertOne, verts[0], sizeof(GzCoord));
	memcpy(data.vertTwo, verts[1], sizeof(GzCoord));
	memcpy(data.vertThree, verts[2], sizeof(GzCoord));
	memcpy(data.normOne, normals[0], sizeof(GzCoord));
	memcpy(data.normTwo, normals[1], sizeof(GzCoord));
	memcpy(data.normThree, normals[2], sizeof(GzCoord));

	//store in tribuffer
	tribuffer.push_back(data); 

	return GZ_SUCCESS;
}


void GzRender::ConvertPixelToWorldSpace(int x, int y, GzCoord worldSpacePixel) {

	float imageAspectRatio = xres / yres;

	worldSpacePixel[0] = (2 * ((x + 0.5) / xres) - 1) * tan(m_camera.FOV / 2 * PI / 180) * imageAspectRatio;
	worldSpacePixel[1] = (1 - 2 * ((y + 0.5) / yres)) * tan(m_camera.FOV / 2 * PI / 180);
	worldSpacePixel[2] = -1;
}


float GzRender::FindIntersection(Ray ray, GzCoord vert0, GzCoord vert1, GzCoord vert2, GzCoord returnIntersection, GzPlane &plane)
{
	float t;
	float planeCoefficients[4];
	LineEquations::GetPlaneCoefficients(vert0, vert1, vert2, planeCoefficients);
	Point planeNormal = { planeCoefficients[0], planeCoefficients[1], planeCoefficients[2] };
	plane.normal = planeNormal;
	plane.d = planeCoefficients[3];

	// from plane: ax + by + cz + d = 0
	Point n = plane.normal;          // (a, b, c)
	float d = plane.d;               // constant term of plane

	// dot products
	float dot1 = dotProduct(n, ray.direction);             // a*Vx + b*Vy + c*Vz
	float dot2 = dotProduct(n, ray.origin);             // a*x1 + b*y1 + c*z1

	// if denominator=0, no intersect
	if (dot1 == 0)
		return INT_MAX;

	// find t = -(a*x1 + b*y1 + c*z1 + d) / (a*Vx + b*Vy + c*Vz)
    t = -(dot2 + d) / dot1;

	// find intersection point
	returnIntersection[X] = ray.origin.x + (t * ray.direction.x);
	returnIntersection[Y] = ray.origin.y + (t * ray.direction.y);
	returnIntersection[Z] = ray.origin.z + (t * ray.direction.z);

	return t;
}


bool GzRender::CheckRay(Ray &ray, GzCoord minIntersectionPoint, GzTridata &intersectedTriangle) {

	float smallestTValue = INT_MAX;
	float t = INT_MAX;
	//need a loop to iterate through all world space triangles
	//Check intersections
	GzCoord intersection, edge1, edge2, edge3, C0, C1, C2;
	for (int k = 0; k < tribuffer.size(); k++)
	{
		GzTridata singleTriangle = tribuffer[k];
		GzCoord v1, v2, v3, n1, n2, n3;
		memcpy(v1, singleTriangle.vertOne, sizeof(GzCoord));
		memcpy(v2, singleTriangle.vertTwo, sizeof(GzCoord));
		memcpy(v3, singleTriangle.vertThree, sizeof(GzCoord));
		memcpy(n1, singleTriangle.normOne, sizeof(GzCoord));
		memcpy(n2, singleTriangle.normTwo, sizeof(GzCoord));
		memcpy(n3, singleTriangle.normThree, sizeof(GzCoord));

		GzPlane plane;
		plane.normal = { 0,0,0 };
		plane.d = 0;
		t = FindIntersection(ray, v1, v2, v3, intersection, plane);

		// Ray does not intersect or is behind the triangle
		if (t == INT_MAX || t <= 0.1)
			continue;

		edge1[X] = v2[X] - v1[X];
		edge1[Y] = v2[Y] - v1[Y];
		edge1[Z] = v2[Z] - v1[Z];

		edge2[X] = v3[X] - v2[X];
		edge2[Y] = v3[Y] - v2[Y];
		edge2[Z] = v3[Z] - v2[Z];

		edge3[X] = v1[X] - v3[X];
		edge3[Y] = v1[Y] - v3[Y];
		edge3[Z] = v1[Z] - v3[Z];

		C0[X] = intersection[X] - v1[X];
		C0[Y] = intersection[Y] - v1[Y];
		C0[Z] = intersection[Z] - v1[Z];

		C1[X] = intersection[X] - v2[X];
		C1[Y] = intersection[Y] - v2[Y];
		C1[Z] = intersection[Z] - v2[Z];

		C2[X] = intersection[X] - v3[X];
		C2[Y] = intersection[Y] - v3[Y];
		C2[Z] = intersection[Z] - v3[Z];

		GzCoord temp1, temp2, temp3;
		crossProduct(edge1, C0, temp1);
		crossProduct(edge2, C1, temp2);
		crossProduct(edge3, C2, temp3);
		GzCoord Pnormal;
		Pnormal[X] = plane.normal.x;
		Pnormal[Y] = plane.normal.y;
		Pnormal[Z] = plane.normal.z;

		float dProduct1 = DProduct(Pnormal, temp1);
		float dProduct2 = DProduct(Pnormal, temp2);
		float dProduct3 = DProduct(Pnormal, temp3);

		if ((dProduct1 < 0 && dProduct2 < 0 && dProduct3 < 0) || (dProduct1 > 0 && dProduct2 > 0 && dProduct3 > 0))
		{
			if (t <= smallestTValue)
			{
				smallestTValue = t;
				memcpy(minIntersectionPoint, intersection, sizeof(GzCoord));
				memcpy(intersectedTriangle.vertOne, v1, sizeof(GzCoord));
				memcpy(intersectedTriangle.vertTwo, v2, sizeof(GzCoord));
				memcpy(intersectedTriangle.vertThree, v3, sizeof(GzCoord));
				memcpy(intersectedTriangle.normOne, n1, sizeof(GzCoord));
				memcpy(intersectedTriangle.normTwo, n2, sizeof(GzCoord));
				memcpy(intersectedTriangle.normThree, n3, sizeof(GzCoord));

			}
		}
	}

	if (smallestTValue < INT_MAX) {
		return true;
	}
	return false;

}


void GzRender::CalculateColorRaytrace(Ray ray, int depth, float returnColor[3]) {

	GzCoord minIntersectionPoint;
	GzTridata intersectedTriangle;


	//Check intersections
	bool intersection = CheckRay(ray, minIntersectionPoint, intersectedTriangle);
	GzColor intensity;

	if (intersection)
	{

			//Recursively search for rays and reflection/refraction ray
		Ray reflec, refrac;
		GzColor spec, diff;
		spec[0] = 0;
		spec[1] = 0;
		spec[2] = 0;

		diff[0] = 0;
		diff[1] = 0;
		diff[2] = 0;

		GzColor Kr, Kt;
		//Kr[RED] = 0.3;
		//Kr[GREEN] = 0.3;
		//Kr[BLUE] = 0.3;
		Kr[RED] = .5;
		Kr[GREEN] = .5;
		Kr[BLUE] = .5;

		Kt[RED] = .3;
		Kt[GREEN] = .3;
		Kt[BLUE] = .3;
		

		float xValueCoefficients[4];
		float yValueCoefficients[4];
		float zValueCoefficients[4];

		GetNormalCoefficients(intersectedTriangle.vertOne, intersectedTriangle.vertTwo, intersectedTriangle.vertThree, 
			intersectedTriangle.normOne, intersectedTriangle.normTwo, intersectedTriangle.normThree, 
			xValueCoefficients, yValueCoefficients, zValueCoefficients);

		float normal[3] = { LineEquations::InterpolateZFloat(xValueCoefficients, minIntersectionPoint[X], minIntersectionPoint[Y]),
							LineEquations::InterpolateZFloat(yValueCoefficients, minIntersectionPoint[X], minIntersectionPoint[Y]),
							LineEquations::InterpolateZFloat(zValueCoefficients, minIntersectionPoint[X], minIntersectionPoint[Y]), };

		if (normal[0] == 1 && normal[1] == 1 && normal[2] == 1) {
			normal[0] = 0;
			normal[1] = 1;
			normal[2] = 0;
		}
		CalculatePhongColor(minIntersectionPoint, normal, intensity, Kd, Ka);
		if (Kr[RED] > 0 || Kr[BLUE] > 0 || Kr[GREEN] > 0)
		{
			reflec = GetReflection(ray, normal, minIntersectionPoint);

			if (depth <= MAX_DEPTH) {
				CalculateColorRaytrace(reflec, depth + 1, spec);
				for (int i = 0; i < 3; ++i) {
					spec[i] *= Kr[i] / depth;
				}
			}
			else {
				for (int i = 0; i < 3; ++i) {
					spec[i] *= 0;
				}
			}
		}

		if (Kt[RED] > 0 || Kt[BLUE] > 0 || Kt[GREEN] > 0)
		{
			refrac = GetRefraction(ray, normal, minIntersectionPoint);

			if (depth <= MAX_DEPTH) {
				CalculateColorRaytrace(refrac, depth + 1, diff);
				for (int i = 0; i < 3; ++i) {
					diff[i] *= Kt[i] / depth;
				}
			}
			else {
				for (int i = 0; i < 3; ++i) {
					diff[i] *= 0;
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			intensity[i] = spec[i] + diff[i] + intensity[i];
		}
	}
	else {
		if (depth > 1) {
			intensity[0] = 0;
			intensity[1] = 0;
			intensity[2] = 0;
		}
		else {
			intensity[0] = 0;
			intensity[1] = .3;
			intensity[2] = .3;
		}
	}
	memcpy(returnColor, intensity, sizeof(GzColor));

}

Ray GetReflection(Ray &ray, GzCoord normal, GzCoord hitPoint)
{
	Point new_origin;
	Point new_dir;
	float RdotN;
	Point normal_;
	normal_.x = normal[0];
	normal_.y = normal[1];
	normal_.z = normal[2];
	RdotN = dotProduct(normal_, ray.direction);
	if (RdotN > 0) {
		for (int i = 0; i < 3; ++i)
			normal[i] *= -1;

	}
	new_dir.x = ray.direction.x - (2 * abs(RdotN)* normal[X]);
	new_dir.y = ray.direction.y - (2 * abs(RdotN)* normal[Y]);
	new_dir.z = ray.direction.z - (2 * abs(RdotN)* normal[Z]);
	ray.Normalize(new_dir);
	new_origin.x = hitPoint[X];
	new_origin.y = hitPoint[Y];
	new_origin.z = hitPoint[Z];
	return Ray(new_origin, new_dir);
}

Ray GetRefraction(Ray &ray, GzCoord normal, GzCoord hitPoint)
{
	Point new_origin = { 0, 0, 0 };
	Point new_dir = { 0, 0, 0 };
	Point normal_;
	normal_.x = normal[0];
	normal_.y = normal[1];
	normal_.z = normal[2];

	float eta = .9;
	float cosi = dotProduct(normal_, ray.direction);
	//float o = (i * eta - n * (-cosi + eta * cosi));

	new_dir.x = eta * ray.direction.x - ((-cosi + eta * cosi) * normal_.x);
	new_dir.y = eta * ray.direction.y - ((-cosi + eta * cosi) * normal_.y);
	new_dir.z = eta * ray.direction.z - ((-cosi + eta * cosi) * normal_.z);
	
	new_origin.x = hitPoint[X];
	new_origin.y = hitPoint[Y];
	new_origin.z = hitPoint[Z];

	return Ray(new_origin, new_dir);
	
}

int GzRender::RenderImg() {

	//for every px
		//intersection = Raycast();
		//Calculate color at loc
		//Write to pixelbuffer
	for(int i = 0; i < xres * yres; i++){

			int x = i / xres;
			int y = i % xres;
			GzCoord worldSpacePixel;
			ConvertPixelToWorldSpace(x, y, worldSpacePixel); //World space pixel

			float origin[3] = { m_camera.position[0], m_camera.position[1], m_camera.position[2] };
			MatrixEquations::MatrixVectorMult(m_camera.CameraTranslation, worldSpacePixel);
			MatrixEquations::MatrixVectorMult(m_camera.CameraTranslation, origin);

			Ray ray = getRay(worldSpacePixel, origin);

			GzColor color = { 0,0,0 };
			CalculateColorRaytrace(ray, 1, color);
			GzPut(x, y, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, 0);
	
		
	}

	return GZ_SUCCESS;
}


Ray GzRender::getRay(GzCoord worldSpacePixel, GzCoord origin)
{
	Point Pos, Dir;
	Pos.x = origin[0];
	Pos.y = origin[1];
	Pos.z = origin[2];

	Dir.x = worldSpacePixel[X] - origin[X];
	Dir.y = worldSpacePixel[Y] - origin[Y];
	Dir.z = worldSpacePixel[Z] - origin[Z];


	return Ray(Pos, Dir);

}