
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

#define MAX_DEPTH	5

Ray GetReflection(Ray &ray, GzCoord normal, GzCoord hitPoint);
Ray GetRefraction(Ray &ray, GzCoord normal, GzCoord hitPoint);
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

	//GzCoord vert1, vert2, vert3, v1, v2, v3;
	//GzCoord norm1, norm2, norm3, n1, n2, n3;
	//GzCoord intersection, minIntersectPoint;
	//GzCoord edge1, edge2, edge3,C0,C1,C2;
	//float t;
	//GzPlane plane;
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
	int GzPutCamera(GzCamera camera, GzMatrix translation);
	int GzPushMatrix(GzMatrix	matrix, GzMatrix* target, short &counter, bool normalizeMatrix);
	int GzPopMatrix(int counter);
	int GzDefaultCamera();

	//HW4 - Created methods
	void GzGouraudShading(int* pixels, int &size, GzCoord* vertPtr, GzCoord* normals, float* zPlaneCoefficients, GzTextureIndex* uvList);
	void GzFlatShading(int*, int&, float*);
	//Bool return sets whether it should be occluded
	void CalculateColor(float[3], float returnColor[3]);
	void CalculatePhongColor(float intersectionPoint[3], float normal[3], float returnColor[3], float newKd[3], float newKa[3]);
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
	void ConvertPixelToWorldSpace(int x, int y, GzCoord worldSpacePixel); /* Converts screenspace pixel to worldspace */
	int ConvertTri(GzToken* nameList, GzPointer* valueList); /* Should take tri data, convert to world space, store it as GZ_TRIDATA */
	bool CheckRay(Ray&, GzCoord, GzTridata&);

	// help function for Camera
	Ray getRay(GzCoord px, GzCoord cam);

	float FindIntersection(Ray ray, GzCoord vert0, GzCoord vert1, GzCoord vert2, GzCoord intersection, GzPlane &plane);
};
#endif