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

/// @addtogroup hxisl hxisl
/// @{
#ifndef  SO_IllumLines
#define  SO_IllumLines

#include "HxISLWinDLLApi.h"
#include <hxcore/hxgl.h>
#include <Inventor/SbBox.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFString.h>
#include <mclib/McDArray.h>
#include "ParticleSet.h"
#include "Particle.h"

/// Inventor node for rendering illuminated streamlines.

class SbProjection;

class HXISL_API SoIllumLines : public SoShape {

    SO_NODE_HEADER(SoIllumLines);

  public:
    /// Constructor.
    SoIllumLines();

    /** The sample points. */
    SoMFVec3f points;

    /** The tangents, used to calculate the illumination. */
    SoMFVec3f tangents;

    /** The colors for each point. */
    SoMFUInt32 colors ;

    /** Number of points for each trace. */
    SoMFUInt32 traces;
    
    /** Call this method after each manipulation of <em> points</em>, <em>
	tangents</em>, <em> lengths</em>, or <em> traces</em>. The method copies
	the field data into an internal fragment list. The fragments
	are sorted for fast depth-ordered rendering. */
    void update(int autoComputeTangents=0);
        
    /** Call this method after manipulating <em> colors</em>. */
    void updateColors();

    /// which blend function, 0=blend, 1=add
    SoSFUInt32	blendfunc;

    /// whether texture hardware or soft-normals are used
    SoSFUInt32	withTexture;

    /// whether ligthing or flat shading is done.
    SoSFUInt32	doLighting;

    /// whether directionally encoded colors are used.
    SoSFUInt32	doDEC;

    /// whether color information is used
    SoSFUInt32	useColor;

    /// whether DLists are used or not
    SoSFUInt32	withDLists;

    /// whether the whole path or only the komet is shown
    SoSFUInt32	showall;
    
    /// specifies the komet's relative position along the path
    SoSFFloat	time;

    /// ???
    SoSFFloat	factor;

    /// ???
    SoSFFloat	baseTransparency;

    /// 
    SoSFFloat	lineWidth;
    
    /// 
    SoSFBool	lineSmooth;

    SoSFFloat	polygonOffsetFactor;

    SoSFFloat	polygonOffsetUnits;

    /// if set to non zero, this light dir is used for lighting. Direction is given world coords.
    SoSFVec3f   customLightDir;

    /// reads vector field and initializes komets
    void initInstance(HxVectorField3 *field);

    void setBoundingBox(const float bb[6]);

    void setPolygonOffset(float factor, float units);

  SoEXTENDER public:
    // Implements actions
    virtual void GLRender(SoGLRenderAction *action);

    // get light, ...
    virtual void getLight(SoGLRenderAction *action,SbVec3f &light);

    
  SoINTERNAL public:
    static void	initClass();

    void deleteDLists();
    
    SbVec3f specularColor,diffuseColor,ambientColor;
    float shininess;
    void computeTexture();
    int timeIncrement;
    int updateCalled;

  // protected:
    virtual ~SoIllumLines();

    // Generates triangles representing faces
    virtual void generatePrimitives(SoAction *action);

    // Handles bounding box computation
    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);

    //check if a point must be projected before rendered
    void checkProjectedPoint( float* point );

    void updateAlpha();
    void computeTangents();
    void initTexture(SbVec3f& light);
    void renderHair(SbVec3f& light);

    void renderKomets(SbVec3f&, float, int);

    /**
        Computes the shading without using textures. 
        @param viewDir view direction. Used for display line segments sorted.
        @param lightDir direction of the light source.
    */
    void renderHairSoftNormals(const SbVec3f& viewDir, SbVec3f& light);

/**
        Computes the shading without using textures. 
        @param viewDir view direction. Used for display line segments sorted.
        @param lightDir direction of the light source.
    */
    void renderKometsSoftNormals(const SbVec3f& viewDir, SbVec3f&, float, int);

    int theTime;
    int animationPeriod;
    float theTransFactor;
    float transTable[512];

    McDArray<Fragment> fragments;
    McDArray<Fragment*> sortx,sorty,sortz;

    int uptodate[6];		// Up-to-date flag for the 6 display lists
    int listoffset;		// Id of first display list
    SbBox3f boundingBox;	// Bounding box is computed in update()
    GLubyte* texture1D;		// 1D Phong texture
    GLubyte* texture2D;		// 2D Phong texture

    //current projection if any
    SbProjection *m_proj;

  public:
    int textureDimension;       // 1 or 2D texture
    float lightTheta,lightPhi;  // Angles of light relative to camera
    SbVec3f lightDirection;

    struct {
	int isEnabled;
	int mode;
	float maxDist;
	float minDist;
	float color[4];
	float density;
    } fog;

    GLuint textureName;
};

extern SoIllumLines* theIllumLines;

#endif

/// @}
