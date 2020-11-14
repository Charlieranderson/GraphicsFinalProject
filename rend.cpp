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

int GzRender::GzPutCamera(GzCamera camera)
{
	/* HW 3.8
	/*- overwrite renderer camera structure with new camera definition
	*/

	//Move the camera to worldspace.
	MatrixEquations::MatrixVectorMult(Xwi, camera.lookat);
	MatrixEquations::MatrixVectorMult(Xwi, camera.position);
	MatrixEquations::MatrixVectorMult(Xwi, camera.worldup);


	m_camera.FOV = camera.FOV;
	m_camera.aspect = yres / xres;
	memcpy(m_camera.lookat, camera.lookat, sizeof(GzCoord));
	memcpy(m_camera.worldup, camera.worldup, sizeof(GzCoord));
	memcpy(m_camera.position, camera.position, sizeof(GzCoord));

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
	RenderImg();
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

int GzRender::ConvertTri(GzToken* nameList, GzPointer* valueList)
{
	
	GzCoord* verts;
	GzCoord* normals;

	for (int i = 0; i < 3; i++) {
		if (nameList[i] == GZ_POSITION) {
			//point1 = (GzCoord*)valueList[i][0];
			//point2 = (GzCoord*)valueList[i][1];
			//point3 = (GzCoord*)valueList[i][2];
			verts = (GzCoord*)valueList[i];
		}
		else if (nameList[i] == GZ_NORMAL) {
			//normal1 = (GzCoord*)valueList[i][0];
			//normal2 = (GzCoord*)valueList[i][1];
			//normal3 = (GzCoord*)valueList[i][2];
			normals = (GzCoord*)valueList[i];
		}
	}


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

int GzRender::Raycast() {
	
	return GZ_SUCCESS;
}


void GzRender::ConvertPixelToWorldSpace(int x, int y, GzCoord worldSpacePixel) {

	float imageAspectRatio = xres / yres;

	worldSpacePixel[0] = (2 * ((x + 0.5) / xres) - 1) * tan(DEFAULT_FOV / 2 * PI / 180) * imageAspectRatio;
	worldSpacePixel[1] = (1 - 2 * ((y + 0.5) / yres)) * tan(DEFAULT_FOV / 2 * PI / 180);
	worldSpacePixel[2] = -1;
}

float dotProduct(Point a, Point b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
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

float vecMagnitude(GzCoord v)
{
	return sqrt(pow(v[X], 2) + pow(v[Y], 2) + pow(v[Z], 2));
}

bool within01Range(float v)
{
	return (0 <= v && v <= 1);
}

float FindIntersection(Ray ray, GzCoord vert0, GzCoord vert1, GzCoord vert2, GzCoord intersectingPoint)
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
		return INT_MAX;

	// find t = -(a*x1 + b*y1 + c*z1 + d) / (a*Vx + b*Vy + c*Vz)
	float t = -(dot2 + d) / dot1;

	// find intersection point
	intersectingPoint[X] = p.x + (t * v.x);
	intersectingPoint[Y] = p.y + (t * v.y);
	intersectingPoint[Z] = p.z + (t * v.z);

	return t;
}

void GzRender::CalculateColorRaytrace(Ray ray, int depth, float returnColor[3]) {
	//Recursively search for rays and reflection/refraction ray
	Ray reflec, refrac;
	GzColor spec, diff;
	GzColor Kr, Kt;
	Kr[RED] = 0.5;
	Kr[GREEN] = 0.5;
	Kr[BLUE] = 0.5;

	Kt[RED] = 0.1;
	Kt[GREEN] = 0.1;
	Kt[BLUE] = 0.1;
	GzColor intensity;
	//Something = FindIntersecion
	GzCoord intersection, minIntersectPoint;
	float smallestTValue = INT_MAX;
	//need a loop to iterate through all world space triangles
	//Check intersections
	GzCoord normA, normB, normC, pA, pB, pC;
	for (int k = 0; k < tribuffer.size(); k++)
	{
		GzTridata singleTriangle = tribuffer[k];
		GzCoord pointA, pointB, pointC, vecAB, vecAC, vecPA, vecPB, vecPC, ABcrossAC, PBcrossPC, PCcrossPA;
		memcpy(pointA, singleTriangle.vertOne, sizeof(GzCoord));
		memcpy(pointB, singleTriangle.vertTwo, sizeof(GzCoord));
		memcpy(pointC, singleTriangle.vertThree, sizeof(GzCoord));

		float t = FindIntersection(ray, pointA, pointB, pointC, intersection);

		// Ray does not intersect
		if (t == INT_MAX)
			continue;

		// Note "intersection" is point P
		// We find barycentric coords alpha, beta, gamma
		// https://math.stackexchange.com/questions/4322/check-whether-a-point-is-within-a-3d-triangle/28552#28552
		// Compute vectors AB, AC, PA, PB, PC
		for (int c = 0; c < 3; c++)
		{
			vecAB[c] = pointB[c] - pointA[c];
			vecAC[c] = pointC[c] - pointA[c];
			vecPA[c] = pointA[c] - intersection[c];
			vecPB[c] = pointB[c] - intersection[c];
			vecPC[c] = pointC[c] - intersection[c];
		}

		crossProduct(vecAB, vecAC, ABcrossAC);
		crossProduct(vecPB, vecPC, PBcrossPC);
		crossProduct(vecPC, vecPA, PCcrossPA);

		float areaABC = vecMagnitude(ABcrossAC) / 2;
		float alpha = (vecMagnitude(PBcrossPC)) / (2 * areaABC);
		float beta = (vecMagnitude(PCcrossPA)) / (2 * areaABC);
		float gamma = 1.0f - alpha - beta;

		// Point lies within triangle
		if (within01Range(alpha) == true && within01Range(beta) == true && within01Range(gamma) == true)
		{
			// Check for smallest t value
			if (t <= smallestTValue)
			{
				smallestTValue = t;
				memcpy(minIntersectPoint, intersection, sizeof(GzCoord));
				memcpy(normA, singleTriangle.normOne, sizeof(GzCoord));
				memcpy(normB, singleTriangle.normTwo, sizeof(GzCoord));
				memcpy(normC, singleTriangle.normThree, sizeof(GzCoord));
				memcpy(pA, singleTriangle.vertOne, sizeof(GzCoord));
				memcpy(pB, singleTriangle.vertTwo, sizeof(GzCoord));
				memcpy(pC, singleTriangle.vertThree, sizeof(GzCoord));
			}
		}
	}
	//float xValueCoefficients[4];
	//float yValueCoefficients[4];
	//float zValueCoefficients[4];
	//GetNormalCoefficients(vertPtr, normals, xValueCoefficients, yValueCoefficients, zValueCoefficients);
	//supposseed to interpolate but will just be flat for now
	GzCoord normal = { 0,0,0 };
	memcpy(normal, normA, sizeof(GzCoord));
	if (smallestTValue < INT_MAX) {
		CalculatePhongColor(normal, intensity, Kd, Ka);
		if (Kr[RED] > 0 || Kr[BLUE] > 0 || Kr[GREEN] > 0)
		{
			GetReflection(&ray, normal, intersection, &reflec);

			if (depth <= 5) {
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
			GetRefraction(&ray, normal, intersection, &refrac);

			if (depth <= 5) {
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
		for (int i = 0; i < 3; ++i) {
			intensity[i] = 0;
		}
	}
	memcpy(returnColor, intensity, sizeof(GzColor));


}

void GetReflection(Ray* ray, GzCoord normal, GzCoord hitPoint, Ray* reflection)
{
	Point new_origin;
	Point new_dir;
	float RdotN;
	Point normal_;
	normal_.x = normal[0];
	normal_.y = normal[1];
	normal_.z = normal[2];
	RdotN = dotProduct(normal_, ray->getDirection());
	if (RdotN > 0) {
		for (int i = 0; i < 3; ++i)
			normal[i] *= -1;

	}
	new_dir.x = ray->getDirection().x - (2 * abs(RdotN)* normal[X]);
	new_dir.y = ray->getDirection().y - (2 * abs(RdotN)* normal[Y]);
	new_dir.z = ray->getDirection().z - (2 * abs(RdotN)* normal[Z]);
	ray->Normalize(new_dir);
	new_origin.x = hitPoint[X] + 1 * new_dir.x;
	new_origin.y = hitPoint[Y] + 1 * new_dir.y;
	new_origin.z = hitPoint[Z] + 1 * new_dir.z;
	reflection = &Ray(new_origin, new_dir);
	return;
}

void GetRefraction(Ray* ray, GzCoord normal, GzCoord hitPoint, Ray* refraction)
{
	refraction = &Ray(ray->PointAt(1), ray->getDirection());
	return;
}
int GzRender::RenderImg() {

	//for every px
		//intersection = Raycast();
		//Calculate color at loc
		//Write to pixelbuffer
	for (int row = yres - 1; row >= 0; --row)
	{
		for (int col = 0; col < xres; ++col)
		{
			float x = col / xres;
			float y = row / yres;
			GzCoord worldSpacePixel;
			ConvertPixelToWorldSpace(x, y, worldSpacePixel); //World space pixel

			//TODO: Create ray with m_camera position, worldspacePixel position
			CameraUpdate(m_camera);
			Ray ray = getRay(x, y, m_camera);
			GzColor color = { 0,0,0 };
			CalculateColorRaytrace(ray, 0, color);
			GzPut(row, col, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 1, 0);
			/*
			GzCoord intersection, minIntersectPoint;
			float smallestTValue = INT_MAX;
			//need a loop to iterate through all world space triangles
			//Check intersections
			for (int k = 0; k < tribuffer.size(); k++)
			{
				GzTridata singleTriangle = tribuffer[k];
				GzCoord pointA, pointB, pointC, vecAB, vecAC, vecPA, vecPB, vecPC, ABcrossAC, PBcrossPC, PCcrossPA;
				memcpy(pointA, singleTriangle.vertOne, sizeof(GzCoord));
				memcpy(pointB, singleTriangle.vertTwo, sizeof(GzCoord));
				memcpy(pointC, singleTriangle.vertThree, sizeof(GzCoord));

				float t = FindIntersection(ray, pointA, pointB, pointC, intersection);

				// Ray does not intersect
				if (t == INT_MAX)
					continue;

				// Note "intersection" is point P
				// We find barycentric coords alpha, beta, gamma
				// https://math.stackexchange.com/questions/4322/check-whether-a-point-is-within-a-3d-triangle/28552#28552
				// Compute vectors AB, AC, PA, PB, PC
				for (int c = 0; c < 3; c++)
				{
					vecAB[c] = pointB[c] - pointA[c];
					vecAC[c] = pointC[c] - pointA[c];
					vecPA[c] = pointA[c] - intersection[c];
					vecPB[c] = pointB[c] - intersection[c];
					vecPC[c] = pointC[c] - intersection[c];
				}

				crossProduct(vecAB, vecAC, ABcrossAC);
				crossProduct(vecPB, vecPC, PBcrossPC);
				crossProduct(vecPC, vecPA, PCcrossPA);

				float areaABC = vecMagnitude(ABcrossAC) / 2;
				float alpha = (vecMagnitude(PBcrossPC)) / (2 * areaABC);
				float beta = (vecMagnitude(PCcrossPA)) / (2 * areaABC);
				float gamma = 1.0f - alpha - beta;

				// Point lies within triangle
				if (within01Range(alpha) == true && within01Range(beta) == true && within01Range(gamma) == true)
				{
					// Check for smallest t value
					if (t <= smallestTValue)
					{
						smallestTValue = t;
						memcpy(minIntersectPoint, intersection, sizeof(GzCoord));
					}
				}
			}

			// Use variable "minIntersectPoint" in computing color, reflections, etc
			//Calculate color, reflections, occlusion for the nearest intersected triangle
			*/
		}
	}

	return GZ_SUCCESS;
}

//camera
int GzRender::CameraUpdate(GzCamera cam)
{
	
	// frustum.
	float theta = cam.FOV;
	float half_height = tan(theta * 0.5f);
	float half_width = cam.aspect * half_height;

	// camera coordinate system.
	for (int i = 0; i < 3; i++) 
	{
		cam.m_axisZ[i] = cam.position[i] - cam.lookat[i];
	}
	MatrixEquations::NormalizeVectorThree(cam.m_axisZ);
	MatrixEquations::CrossProduct(cam.worldup, cam.m_axisZ, cam.m_axisX);
	MatrixEquations::NormalizeVectorThree(cam.m_axisX);
	MatrixEquations::CrossProduct(cam.m_axisZ, cam.m_axisX, cam.m_axisY);
	MatrixEquations::NormalizeVectorThree(cam.m_axisY);

	// view port.
	for (int i = 0; i < 3; i++)
	{
	    cam.lowerLeftCorner[i] = cam.position[i] - cam.m_axisX[i] * half_width - cam.m_axisY[i] * half_height - cam.m_axisZ[i];
		cam.horizontal[i] = cam.m_axisX[i] * 2.0f * half_width;
		cam.vertical[i] = cam.m_axisY[i] * 2.0f * half_height;
	}

	return GZ_SUCCESS;
}
Ray GzRender::getRay(float s, float t, GzCamera cam)
{
	Point Pos, Dir;
	Pos.x = cam.position[0];
	Pos.y = cam.position[1];
	Pos.z = cam.position[2];

	Dir.x = cam.lowerLeftCorner[0] + cam.horizontal[0] * s + cam.vertical[0] * t - cam.position[0];
	Dir.y = cam.lowerLeftCorner[1] + cam.horizontal[1] * s + cam.vertical[1] * t - cam.position[1];
	Dir.z = cam.lowerLeftCorner[2] + cam.horizontal[2] * s + cam.vertical[2] * t - cam.position[2];

	return Ray(Pos, Dir);
}