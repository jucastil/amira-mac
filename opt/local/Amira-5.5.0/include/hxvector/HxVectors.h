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

/// @addtogroup hxvector hxvector
/// @{
#ifndef HX_VECTORS_H
#define HX_VECTORS_H

#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxField3.h>
#include <hxfield/TetraCut.h>
#include <hxvector/HxVectorWinDLLApi.h>

class SbProjection;
class SoProjection;
class SoShapeKit;
class SoLineSet;
class SoPointSet;
class SoCoordinate3;
class SoMaterial;
class SoVertexProperty;
class SoDrawStyle;
class SoSeparator;
class SoPackedColor;
class SoMaterialBinding;
class HxField;
class HxTetraGrid;
class HxVertexSet;

/// Produces an arrow plot of a vector field in an arbitrary plane.
class HXVECTOR_API HxVectors : public HxOverlayModule {

  HX_HEADER(HxVectors);

  public:
    /// Constructor.
    HxVectors();

    // ???
    //    virtual void fire();

    /// Update method (show/hide ports).
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// save port and other settings to file
    virtual void savePorts(FILE* fp);

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    HxVectors(SoType type); // for use by derived classes
    virtual ~HxVectors();

    //Projection stuffs
    bool m_transformGeodetic;

    //to store position
    float m_storedPos[3];
    SoProjection* m_projNode;
    SbProjection* m_proj;

    HxPortColormap	    portColormap;
    HxConnection        portSeeds;
    HxPortFloatTextN	portResolution;
    HxPortFloatSlider   portScaleSize;
    HxPortFloatSlider   portScaleZ;
    HxPortToggleList	portMode;
    HxPortMultiMenu 	portColorize;
    HxPortAnimatedFloat	portProjection;

    HxField3*		field;
    HxField*           field4;
    HxTetraGrid*	grid;

    HxVertexSet* m_seeds;
    
    SoSeparator*	lineShape;
    SoLineSet*	    	lineSet;
    SoDrawStyle*        lineStyle;
    SoPackedColor*      lineColor;
    SoMaterialBinding*  lineMatBinding;

    SoPointSet*	    	pointSet;
    SoShapeKit*	    	pointShape;
    int			nCoords;
    float		commonScale;
    SbBool		doProjection;
    SbBool		doNoScaling;
    SbBool		doDrawArrows;
    SbBool		doLogScale;
    int			  colorMode;
    SbVec3f		orig;
    SbVec3f		norm;
    SbVec3f		uVec;
    SbVec3f		vVec;
    float		  maxMagnitude;
    TetraCut	tetraCut;

    void commonInit();
    virtual void drawVectors();
    void doIntersection();
    void doGeneric(FILE* fp=0);

	// added by hauke
    void saveVectorsToFile(char *filename);

    unsigned int* colorPtr;
    SbVec3f* vertexPtr;
    SbVec3f* pointPtr;

    virtual void removeOverlay();

    virtual void computeInputBBox();

    void render(const float* pos, const float* vec, FILE* fp=0);
    static void render_vx(int, int, TetraCut::Vertex& res);
    static void render_vre(int, int, TetraCut::Vertex& res);
    static void render_vce(int, int, TetraCut::Vertex& res);
    static void intersection_vre(int k, TetraCut::Polygon& p);
    static void intersection_vce(int k, TetraCut::Polygon& p);
};

#endif

/// @}
