/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxfastLIC hxfastLIC
/// @{
#ifndef HX_SURFACELIC
#define HX_SURFACELIC

#include <hxfastLIC/HxFastLICWinDLLApi.h>
#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxScalarField3.h>
#include <hxfield/HxVectorField3.h>
#include <hxfieldx/HxField.h>
#include <hxsurface/HxSurface.h>
#include <hxsurftools/HxSurfaceScalarField.h>
#include <hxsurftools/HxSurfaceVectorField.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/engines/SoTimeCounter.h>

/// Fast LIC module.
class HXFASTLIC_API HxSurfaceLIC : public HxModule {

  HX_HEADER(HxSurfaceLIC);

  public:
    /// Constructor.
    HxSurfaceLIC();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Auto connect method.
    int autoConnect(HxObject* primary);

    /// Connection to vector field.
    HxConnection portVectorField;

    /// Connection to optional scalar field (used for color coding).
    HxConnection portScalarField;

    /// Connection to optional scalar field (used for color coding).
    HxConnection portScalarField2;

    /// Connection to a ROI port for choosing a subset of triangles for the LIC.
    HxConnection portROI;

    /// Colormap.
    HxPortColormap portColormap;

    /// Colormap2.
    HxPortColormap portColormap2;

    /// Color coding: 0=none, 1=magnitude, 2=scalar field
    HxPortMultiMenu portColorMode;

    /// Type of texture interpolation (0=constant 1=bilinear)
    HxPortRadioBox portInterpol;

    /// Contrast adjustment
    HxPortFloatTextN portContrast;

    /// Options: 0=filter length in pixels, 1=texture resolution.
    HxPortIntTextN portOptions;
    enum { FILTERLENGTH=0, RESOLUTION=1 };

    /// DoIt button
    HxPortDoIt portDoIt;

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  public:
    struct UnitVector { // per triangle in world coords
	float u[3];
	float v[3];
    };

    struct Pixel {
	int hitCount;
	int accum;
    };

    struct Triangle {
	int points[3];
	int neighbours[3];
	int nx,ny,inverted; // ,val;
	Pixel* buffer;
	float u1,u2,v2; // natural coordinates (u0=v0=v1=0)

	int isInverted() { return inverted; }
    };

    class HXFASTLIC_API Packer {
      public:
	Packer(HxSurfaceLIC* slic, float ps);
	~Packer() { }
	int pack(int t, float* texCoord[3]);
	void setBuffer(int nx, int ny, unsigned char* buffer);
	int writePGM(const char* filename);

      protected:
	float pixelSize;
	int currentRow;
	int currentHeight;
	McDArray<int> currentPos;
	int bufferWidth;
	int bufferHeight;
	unsigned char* buffer;
	HxSurfaceLIC* surfaceLIC;
    };
    friend class Packer;
  protected:
    virtual ~HxSurfaceLIC();    


    int noise(float x, float y, float z);
    int isOutside(float b[3]) { return (b[0]<0)||(b[1]<0)||(b[2]<0); }
    void getPhysicalCoords(int t, const float b[3], float x[3]);
    void getLocalCoords(int t, const float x[3], float u[2]);
    void getVector3D(int t, HxLocation3* loc, float vec[2]);
    void getVector(int t, const float b[3], float vec[2]);
	void getVectorFromIFace(int t, float* x, float vec[2]);
    void sampleStreamline(int t, float u[2], float b[3]);
    void sampleOneway(int t, float u[2], float b[3], float x[3], int);
    Pixel* getPixel(int t, const float u[2]);
    unsigned char getValue(int t, int i, int j);
    int moveToNeighbour(int&, float p[2], float q[2], float b[3], int&, int);
    void fixOrientation(float res[3], float vec[2]);
    void fillEmptyPixels();
    void brighten();

    void getBarycentricCoords(int t, const float u[2], float b[3]) {
	const Triangle& tri = triangles[t];
        b[2] = u[1]/tri.v2;
	b[1] = (u[0]-tri.u2*b[2])/tri.u1;
	b[0] = 1-b[1]-b[2];
    }

    void doIt();
    void colorize();
    void initTriangles();
    void initUnitVectors();
    void initPixelBuffers();
    void processTriangles();
    int writeTriangle(const char* filename, Triangle& tri);
    void createAnimation(int filterShift, int increment);

    void createGeometry();
    void setupGeometry(SoGroup*, McVec3f* normals);
    void createNormals(McVec3f* normals);
    void blend(SoTexture2* tex1, SoTexture2* tex2, float u);

    float pixelSize;		// width of a pixel in world coordinates
    float objectSize;		// object dimension: diagonal / sqrt(3)
    int filterLength;		// length of box filter in Euler steps
    int streamlineLength;	// length of a field line
    int filterShift;
    float noiseResolution;	// noise granularity in pixel widths (def 1.5)
    float noiseFactor;		// = 1.0/(noiseResolution*pixelSize)
    Pixel** samplePix;		// contains pixel addresses of samples
    int* sampleVal;		// contains sampled noise values
    float lastVec[3];
    float creaseAngle;

    HxSurface* surface;		// the surface to be LICed
 
    /**
        All the triangles that actually should be LICed. Converted to an internal format.
    */
    McDArray<Triangle> triangles;

    /**
        A mapping from the @c triangles array indices to the original surface triangles. If empty, mapping is the identity.
    */
    McDArray<int> m_idxSurface;

    /**
        Mapping from the surface triangle index to the index in @c triangles. If empty, the mapping is the identity.
    */
    McDArray<int> m_idxTriangles;

    /**
        A mapping from the @c triangles array indices to the original surface triangles.
    */
    int getIdxSurface(int idxTriangle)
    {
        if (m_idxSurface.size() == 0) return idxTriangle;
        else return m_idxSurface[idxTriangle];
    }

    /**
        Mapping from the surface triangle index to the index in @c triangles.
    */
    int getIdxTriangles(int idxSurfaceTriangle)
    {
        if (m_idxTriangles.size() == 0) return idxSurfaceTriangle;
        else return m_idxTriangles[idxSurfaceTriangle];
    }


    UnitVector* unitVectors;
    Pixel* pixelBuffer;
    SoSeparator* geometry;
    SoEventCallback* eventCB;
    SoComplexity* complexity;
    int contrastCenter;
    int contrastFactor;
    SoMaterialBinding* matBinding;
    McHandle<SoMaterial> material;
    McHandle<SoSwitch> texSwitch;
    McHandle<SoTimeCounter> counter;

    HxSurfaceVectorField* vectorField;
    HxVectorField3* vectorField3D;
    HxLocation3* location;

    /**
        The maximum number of pixels in one axis dimension over all triangles. The texture size must be (approx) at least twice
        as large as this number.
    */
    int m_maxTriangleAxisPixels;

	HxField* field;
	HxFieldEvaluatorX* fieldEval;
	const float* fieldEvalBuffer;
	const float* fieldEvalAlphaBuffer;

    static float _pixelSize;
    static Triangle* _triangles;
    static int heightCompare(const void*, const void*);
    static void selectionCB(void *userData, SoEventCallback *eventCB);
};

#endif

/// @}
