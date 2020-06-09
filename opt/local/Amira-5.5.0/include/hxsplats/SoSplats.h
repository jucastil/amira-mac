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

/// @addtogroup hxsplats hxsplats
/// @{
#ifndef SO_SPLATS_H
#define SO_SPLATS_H

#include <mcgl/mcgl.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <mclib/McVec2f.h>
#include <mclib/McMat4f.h>

#include <mclibthreaded/McMutex.h>

/// Stand-alone Inventor splatting node.
class SoSplats : public SoShape {

    SO_NODE_HEADER(SoSplats);

  public:
    /// Constructor.
    SoSplats();

    /// Vertices of tetrahedral cells.
    SoMFVec3f point;

    /// Contains for each tetrahedral cell 4 indices into vertex array.
    SoMFInt32 pointIndex;

    /// Contains base opacity for each tetrahedral cell or node.
    SoMFFloat alpha;

    /// If true, a valid 2D opacity texture must have been defined !
    SoSFBool linear;

    /// Specifies maximum thickness of a tetrahedron
    SoSFFloat maxThickness;

    /// Specifies color of splats.
    SoSFColor color;

    /// Specify the faces between tetras (connectivity)
    SoMFVec4f faces;

    /// Lower Tetras of planes.
    SoMFInt32 lowerTetras;

    /// Upper tetras of planes
    SoMFInt32 upperTetras;

    /// boundary tetras.
    SoMFInt32 boundaryTetras;

    /// Specifies the optical model
    SoSFEnum opticalModel;

    /// 
    SoSFBool visibilitySort;

    enum OpticalModel {
        EMESSIVE,
        EMESSIVE_AND_ABSORPTIVE,
        ABSORPTIVE
    };

    SoSFEnum colorMode;
    enum ColorMode {
        CONSTANT,
        COLORED
    };

    SoMFUInt32 colors;

    /// Sets up the texture.
    void setTexture(int internalformat, int nx, int ny, int format, int type , void* data);

  SoEXTENDER public:
    virtual void generatePrimitives(SoAction *action);
    virtual void GLRender(SoGLRenderAction *action);

  SoINTERNAL public:
    static void	initClass();

  protected:
    ~SoSplats();
    unsigned int textureName;

    void* textureData;
    int   textureSize[2];
    int   textureInternalFormat;
    int   textureFormat;
    int   textureType;

    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);

    /**
        Actually computes the splatting of the tetrahedrons.
        @param splatsRenderer does the rendering, associates values with vertices etc.
        @param idMap determines the order of the tetrahedrons that gets rendered. Lookup is done by operator[].
        @param spoint vertices of the tetrahedrons in normalalized device coordinates (after aplqing the current ModelViewProjection matrix).
        @param MVPInverse the inverse of the current ModelViewProjection matrix.
    */
	template<class SplatsRenderer>
	inline void GLRenderSplats(SplatsRenderer splatsRenderer, McDArray<int> *idMap,const McDArray<McVec3f>& spoint, const McMat4f& MVPInverse);

    /**
        Calculates the 2D local coordinates (barycentrics) of b in triangle (0,a1,a2).
        The third components of the vectors are ignored.
    */
    inline void calcUV(float& u, float& v, 
                       const McVec3f& a1,
                       const McVec3f& a2,
                       const McVec3f& b)
    {
		float det_rcp = 1.0f / a1.cross(a2).z;
		u = b.cross(a2).z*det_rcp;
		v = a1.cross(b).z*det_rcp;
    }

    /**
        Given a triangle (vs1,vs2,vs3) and local coordinates (u,v) within the 
        triangle. The points world coordinates (p) are calculated by applying the 
        given matrix BI. Then the thickness from that point to v0, multiplied 
        with a given scaling factor (thickscale) is returned in thickness and 
        the middle point between p and v0 is retured in p.
    */
    inline void calcPointAndThickness3(McVec3f& p, float& thickness,
                                       const McMat4f& BI,
                                       const float thickScale,
                                       float u, float v,
                                       const McVec3f& vs1,
                                       const McVec3f& vs2,
                                       const McVec3f& vs3,
                                       const McVec3f& v0)
    {
	    p = (1-u-v)*vs1 + u*vs2 + v*vs3;
        McVec3f q;
	    BI.multVecMatrix(p,q);
	    thickness = (q-v0).length()*thickScale;
	    p = 0.5*(q+v0);
    }

    inline void calcPointAndThickness4(McVec3f& p, float& thickness,
                                       const McMat4f& BI,
                                       const float thickScale,
                                       float u, float v,
                                       const McVec3f& vs1,
                                       const McVec3f& vs2,
                                       const McVec3f& vs3,
                                       const McVec3f& vs4)
    {
        McVec3f q1;
        McVec3f q2;

        BI.multVecMatrix(vs1 + u*(vs3-vs1),q1);
	    BI.multVecMatrix(vs2 + v*(vs4-vs2),q2);
	    thickness = (q1-q2).length()*thickScale;
	    p = 0.5*(q1+q2);

    }

};

class IdMapperIdentity {
public:
    inline int operator[](int iTetraId) {
        return iTetraId;
    };
};




#endif

/// @}
