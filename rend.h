
#ifndef GZRENDER_
#define GZRENDER_
#include	"gz.h"
#include	"Ray.h"
#include	<vector>

/* Camera defaults */
#define	DEFAULT_FOV		35.0
#define	DEFAULT_IM_Z	(-10.0)  /* world coords for image plane origin */
#define	DEFAULT_IM_Y	(5.0)    /* default look-at point = 0,0,0 */
#define	DEFAULT_IM_X	(-10.0)

#define	DEFAULT_AMBIENT	{0.1, 0.1, 0.1}
#define	DEFAULT_DIFFUSE	{0.7, 0.6, 0.5}
#define	DEFAULT_SPECULAR	{0.2, 0.3, 0.4}
#define	DEFAULT_SPEC		32

#define	MATLEVELS	100		/* how many matrix pushes allowed */
#define	MAX_LIGHTS	10		/* how many lights allowed */

void GetReflection(Ray* ray, GzCoord normal, GzCoord hitPoint, Ray* reflection);
void GetRefraction(Ray* ray, GzCoord normal, GzCoord hitPoint, Ray* refraction);
class GzRender{			/* define a renderer */
  

public:
	unsigned short	xres;
	unsigned short	yres;
	GzPixel		*pixelbuffer;		/* frame buffer array */
	char* framebuffer;
	std::vector<GzTridata> tribuffer;
	GzMatrix		Xwi;

	GzCamera		m_camera;
	short		    matlevel;	        /* top of stack - current xform */
	short			normMatLevel;
	GzMatrix		Ximage[MATLEVELS];	/* stack of xforms (Xsm) */
	GzMatrix		Xnorm[MATLEVELS];	/* xforms for norms (Xim) */
	GzColor		flatcolor;          /* color state for flat shaded triangles */
	int			interp_mode;
	int			numlights;
	GzLight		lights[MAX_LIGHTS];
	GzLight		ambientlight;
	GzColor		Ka, Kd, Ks;
	float		    spec;		/* specular power */
	GzTexture		tex_fun;    /* tex_fun(float u, float v, GzColor color) */

  	// Constructors
	GzRender(int xRes, int yRes);
	~GzRender();

	// Function declaration

	// HW1: Display methods
	int GzDefault();
	int GzBeginRender();
	int GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z);
	int GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth	*z);

	int GzFlushDisplay2File(FILE* outfile);
	int GzFlushDisplay2FrameBuffer();

	// HW2: Render methods
	int GzPutAttribute(int numAttributes, GzToken *nameList, GzPointer *valueList);

	// HW3
	int GzPutCamera(GzCamera camera);
	int GzPushMatrix(GzMatrix	matrix, GzMatrix* target, int counter, bool normalizeMatrix);
	int GzPopMatrix(int counter);
	int GzDefaultCamera();

	//HW4 - Created methods
	void GzGouraudShading(int* pixels, int &size, GzCoord* vertPtr, GzCoord* normals, float* zPlaneCoefficients, GzTextureIndex* uvList);
	void GzPhongShading(int* pixels, int &size, GzCoord* vertPtr, GzCoord* normals, float* zPlaneCoefficients, GzTextureIndex* uvList);
	void GzFlatShading(int*, int&, float*);
	//Bool return sets whether it should be occluded
	void CalculateColor(float[3], float returnColor[3]);
	void CalculatePhongColor(float normal[3], float returnColor[3], float newKd[3], float newKa[3]);
	void CalculateGouraudColor(float normal[3], float returnColor[3]);
	void CalculateColorRaytrace(Ray ray, int depth, float returnColor[3]);

	// Extra methods: NOT part of API - just for general assistance */
	inline int ARRAY(int x, int y){return (x+y*xres);}	/* simplify fbuf indexing */
	inline short	ctoi(float color) {return(short)((int)(color * ((1 << 12) - 1)));}		/* convert float color to GzIntensity short */
	bool CheckBounds(const int &i, const int &j) const;
	inline void FindPixelsInTri(GzCoord* ptr, GzCoord* normalPtr, GzTextureIndex* uvList, int* pixels, int &size);

	// Object Translation
	int GzRotXMat(float degree, GzMatrix mat);
	int GzRotYMat(float degree, GzMatrix mat);
	int GzRotZMat(float degree, GzMatrix mat);
	int GzTrxMat(GzCoord translate, GzMatrix mat);
	int GzScaleMat(GzCoord scale, GzMatrix mat);

	//Raytracing
	int RenderImg(); /*Render the image*/
	int Raycast(); /*Raycasts. Change return to the correct intersection*/
	void ConvertPixelToWorldSpace(int x, int y, GzCoord worldSpacePixel); /* Converts screenspace pixel to worldspace */
	int ConvertTri(GzCoord point1, GzCoord point2, GzCoord point3, GzCoord normal1, GzCoord normal2, GzCoord normal3); /* Should take tri data, convert to world space, store it as GZ_TRIDATA */

	// help function for Camera
	Ray getRay(float s, float t, GzCamera cam);
	int CameraUpdate(GzCamera cam);
};
#endif