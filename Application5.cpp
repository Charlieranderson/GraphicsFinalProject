// Application5.cpp: implementation of the Application5 class.
//
//////////////////////////////////////////////////////////////////////

/*
 * application test code for homework assignment #5
*/

#include "stdafx.h"
#include "CS580HW.h"
#include "Application5.h"
#include "Gz.h"
#include "rend.h"
#include<fstream>
#include<sstream>
#include<vector>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INFILE  "ppot.asc"
#define OUTFILE "output.ppm"


extern int tex_fun(float u, float v, GzColor color); /* image texture function */
extern int ptex_fun(float u, float v, GzColor color); /* procedural texture function */
extern int GzFreeTexture();

struct vertex {
	float x, y, z;
};

struct uv {
	float x, y;
};

struct normal {
	float x, y, z;
};

struct triangle {
	std::string x, y, z;
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Application5::Application5()
{

}

Application5::~Application5()
{
	Clean();
}

int Application5::Initialize()
{
	GzCamera	camera;  
	int		    xRes, yRes;	/* display parameters */ 

	GzToken		nameListShader[9]; 	    /* shader attribute names */
	GzPointer   valueListShader[9];		/* shader attribute pointers */
	GzToken     nameListLights[10];		/* light info */
	GzPointer   valueListLights[10];
	int			shaderType, interpStyle;
	float		specpower;
	int		status; 
 
	status = 0; 

	/* 
	 * Allocate memory for user input
	 */
	m_pUserInput = new GzInput;

	/* 
	 * initialize the display and the renderer 
	 */ 
 	m_nWidth = 256;		// frame buffer and display width
	m_nHeight = 256;    // frame buffer and display height

	m_pRender = new GzRender(m_nWidth, m_nHeight);
	m_pRender->GzDefault();

	m_pFrameBuffer = m_pRender->framebuffer; 

/* Translation matrix */
GzMatrix	scale = 
{ 
	3.25,	0.0,	0.0,	0.0, 
	0.0,	3.25,	0.0,	-3.25, 
	0.0,	0.0,	3.25,	3.5, 
	0.0,	0.0,	0.0,	1.0 
}; 
 
GzMatrix	rotateX = 
{ 
	1.0,	0.0,	0.0,	0.0, 
	0.0,	.7071,	.7071,	0.0, 
	0.0,	-.7071,	.7071,	0.0, 
	0.0,	0.0,	0.0,	1.0 
}; 
 
GzMatrix	rotateY = 
{ 
	.866,	0.0,	-0.5,	0.0, 
	0.0,	1.0,	0.0,	0.0, 
	0.5,	0.0,	.866,	0.0, 
	0.0,	0.0,	0.0,	1.0 
}; 

#if 1 	/* set up app-defined camera if desired, else use camera defaults */
    camera.position[X] = -3;
    camera.position[Y] = -25;
    camera.position[Z] = -4;

    camera.lookat[X] = 7.8;
    camera.lookat[Y] = 0.7;
    camera.lookat[Z] = 6.5;

    camera.worldup[X] = -0.2;
    camera.worldup[Y] = 1.0;
    camera.worldup[Z] = 0.0;

    camera.FOV = 63.7;              /* degrees *              /* degrees */

	status |= m_pRender->GzPutCamera(camera); 
#endif 

	/* Start Renderer */
	status |= m_pRender->GzBeginRender();

	/* Lights. Should be redefined for world space */
	GzLight	light1 = { {-0.7071, 0.7071, 0}, {0.5, 0.5, 0.9} };
	GzLight	light2 = { {0, -0.7071, -0.7071}, {0.9, 0.2, 0.3} };
	GzLight	light3 = { {0.7071, 0.0, -0.7071}, {0.2, 0.7, 0.3} };
	GzLight	ambientlight = { {0, 0, 0}, {0.3, 0.3, 0.3} };

	/* Material property */
	GzColor specularCoefficient = { 0.3, 0.3, 0.3 };
	GzColor ambientCoefficient = { 0.1, 0.1, 0.1 };
	GzColor diffuseCoefficient = {0.7, 0.7, 0.7};

/* 
  renderer is ready for frame --- define lights and shader at start of frame 
*/

        /*
         * Tokens associated with light parameters
         */
        nameListLights[0] = GZ_DIRECTIONAL_LIGHT;
        valueListLights[0] = (GzPointer)&light1;
        nameListLights[1] = GZ_DIRECTIONAL_LIGHT;
        valueListLights[1] = (GzPointer)&light2;
        nameListLights[2] = GZ_DIRECTIONAL_LIGHT;
        valueListLights[2] = (GzPointer)&light3;
        status |= m_pRender->GzPutAttribute(3, nameListLights, valueListLights);

        nameListLights[0] = GZ_AMBIENT_LIGHT;
        valueListLights[0] = (GzPointer)&ambientlight;
        status |= m_pRender->GzPutAttribute(1, nameListLights, valueListLights);

        /*
         * Tokens associated with shading 
         */
        nameListShader[0]  = GZ_DIFFUSE_COEFFICIENT;
        valueListShader[0] = (GzPointer)diffuseCoefficient;

	/* 
	* Select either GZ_COLOR or GZ_NORMALS as interpolation mode  
	*/
        nameListShader[1]  = GZ_INTERPOLATE;
        //interpStyle = GZ_COLOR;         /* Gouraud shading */
        interpStyle = GZ_NORMALS;         /* Phong shading */
        valueListShader[1] = (GzPointer)&interpStyle;

        nameListShader[2]  = GZ_AMBIENT_COEFFICIENT;
        valueListShader[2] = (GzPointer)ambientCoefficient;
        nameListShader[3]  = GZ_SPECULAR_COEFFICIENT;
        valueListShader[3] = (GzPointer)specularCoefficient;
        nameListShader[4]  = GZ_DISTRIBUTION_COEFFICIENT;
        specpower = 32;
        valueListShader[4] = (GzPointer)&specpower;

        nameListShader[5]  = GZ_TEXTURE_MAP;
#if 0   /* set up null texture function or valid pointer */
        valueListShader[5] = (GzPointer)0;
#else
        //valueListShader[5] = (GzPointer)(ptex_fun);	/* or use ptex_fun */
        valueListShader[5] = (GzPointer)(tex_fun);	/* or use ptex_fun */
#endif
        status |= m_pRender->GzPutAttribute(6, nameListShader, valueListShader);


	status |= m_pRender->GzPushMatrix(scale);  
	status |= m_pRender->GzPushMatrix(rotateY); 
	status |= m_pRender->GzPushMatrix(rotateX); 

	if (status) exit(GZ_FAILURE); 

	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS); 
}

int Application5::Render() 
{
	GzToken		nameListTriangle[3]; 	/* vertex attribute names */
	GzPointer	valueListTriangle[3]; 	/* vertex attribute pointers */
	GzCoord		vertexList[3];	/* vertex position coordinates */ 
	GzCoord		normalList[3];	/* vertex normals */ 
	GzTextureIndex  	uvList[3];		/* vertex texture map indices */ 
	char		dummy[256]; 
	int			status; 


	/* Initialize Display */
	status |= m_pRender->GzDefault();  /* init for new frame */
	
	/* 
	* Tokens associated with triangle vertex values 
	*/ 
	nameListTriangle[0] = GZ_POSITION; 
	nameListTriangle[1] = GZ_NORMAL; 
	nameListTriangle[2] = GZ_TEXTURE_INDEX;  

	// I/O File open
	FILE *infile;
	if( (infile  = fopen( INFILE , "r" )) == NULL )
	{
         AfxMessageBox( "The input file was not opened\n" );
		 return GZ_FAILURE;
	}

	FILE *outfile;
	if( (outfile  = fopen( OUTFILE , "wb" )) == NULL )
	{
         AfxMessageBox( "The output file was not opened\n" );
		 return GZ_FAILURE;
	}

	/* 
	* Walk through the list of triangles, set color 
	* and render each triangle 
	*/ 




	//read the obj file

	std::ifstream file("benchObjModel.txt");
	std::string str;

	std::vector<vertex> verticesList;
	std::vector<uv> uvsList;
	std::vector<normal> normalsList;
	std::vector<triangle> triangles;

	while (getline(file, str))
	{
		std::istringstream in(str);
		std::string type;
		in >> type;
		if (type == "v") {
			float x, y, z;
			in >> x >> y >> z;
			verticesList.push_back({ x,y,z });

		}
		else if (type == "vt") {
			float x, y;
			in >> x >> y;
			uvsList.push_back({ x,y });
		}

		else if (type == "vn") {
			float x, y, z;
			in >> x >> y >> z;
			normalsList.push_back({ x,y,z });
		}
		else if (type == "f") {
			std::string x, y, z;
			in >> x >> y >> z;
			triangles.push_back({ x,y,z });
		}

	}

	//process read data and store these values in the variables that the HW uses

	//------------NOTE-------------------

	// vertexList (used by HW) | verticesList (defined by us to read the values)
	// uvList (used by HW) | uvsList (defined by us to read the values)
	// normalList (used by HW) | normalsList (defined by us to read the values)

	int n = verticesList.size();
	for (int i = 0; i < n; i++) {
		std::stringstream ss1(triangles[i].x);
		std::string token1;
		int ind = 0;
		while (getline(ss1, token1, '/')) {
			int x = 0;
			std::stringstream num(token1);
			num >> x;
			if (ind == 0) {
				vertexList[0][0] = verticesList[x - 1].x;
				vertexList[0][1] = verticesList[x - 1].y;
				vertexList[0][2] = verticesList[x - 1].z;
			}
			else if (ind == 1) {
				uvList[0][0] = uvsList[x - 1].x;
				uvList[0][1] = uvsList[x - 1].y;
			}
			else {
				normalList[0][0] = normalsList[x - 1].x;
				normalList[0][1] = normalsList[x - 1].y;
				normalList[0][2] = normalsList[x - 1].z;
			}
			ind++;

		}

		ind = 0;
		std::stringstream ss2(triangles[i].y);
		std::string token2;
		while (getline(ss2, token2, '/')) {
			int x = 0;
			std::stringstream num(token2);
			num >> x;
			if (ind == 0) {
				vertexList[0][0] = verticesList[x - 1].x;
				vertexList[0][1] = verticesList[x - 1].y;
				vertexList[0][2] = verticesList[x - 1].z;
			}
			else if (ind == 1) {
				uvList[0][0] = uvsList[x - 1].x;
				uvList[0][1] = uvsList[x - 1].y;
			}
			else {
				normalList[0][0] = normalsList[x - 1].x;
				normalList[0][1] = normalsList[x - 1].y;
				normalList[0][2] = normalsList[x - 1].z;
			}
			ind++;
		}
		ind = 0;
		std::stringstream ss3(triangles[i].z);
		std::string token3;
		while (getline(ss3, token3, '/')) {
			int x = 0;
			std::stringstream num(token3);
			num >> x;
			if (ind == 0) {
				vertexList[0][0] = verticesList[x - 1].x;
				vertexList[0][1] = verticesList[x - 1].y;
				vertexList[0][2] = verticesList[x - 1].z;
			}
			else if (ind == 1) {
				uvList[0][0] = uvsList[x - 1].x;
				uvList[0][1] = uvsList[x - 1].y;
			}
			else {
				normalList[0][0] = normalsList[x - 1].x;
				normalList[0][1] = normalsList[x - 1].y;
				normalList[0][2] = normalsList[x - 1].z;
			}
			ind++;
		}
	     valueListTriangle[0] = (GzPointer)vertexList; 
		 valueListTriangle[1] = (GzPointer)normalList; 
		 valueListTriangle[2] = (GzPointer)uvList; 

		 
		 //m_pRender->GzPutTriangle(3, nameListTriangle, valueListTriangle); 

		 //Convert triangles to worldspace
		 //Store in renderer tribuffer
	} 

	//Render img call here

	m_pRender->GzFlushDisplay2File(outfile); 	/* write out or update display to file*/
	m_pRender->GzFlushDisplay2FrameBuffer();	// write out or update display to frame buffer

	/* 
	 * Close file
	 */ 

	if( fclose( infile ) )
      AfxMessageBox(_T( "The input file was not closed\n" ));

	if( fclose( outfile ) )
      AfxMessageBox(_T( "The output file was not closed\n" ));
 
	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS); 
}

int Application5::Clean()
{
	/* 
	 * Clean up and exit 
	 */ 
	int	status = 0; 

	delete(m_pRender);
	status |= GzFreeTexture();
	
	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS);
}



