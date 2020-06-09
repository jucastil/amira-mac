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

/// @addtogroup hxtetra hxtetra
/// @{
#ifndef HX_INTERSECT_H
#define HX_INTERSECT_H

#include <mclib/McBitfield.h>
#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortColorList.h>
#include <hxsurface/HxSurface.h>
#include <hxfield/HxTetraGrid.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>
#include <hxtetra/HxTetraWinDLLApi.h>

class HxLineSet;

/** This class intersects a triangular surface or tetrahedral grid 
    with a cutting plane. The boundaries of the intersected triangles
    are displayed on top of the cutting plane. */
class HXTETRA_API HxOverlayGrid : public HxOverlayModule {

  HX_HEADER(HxOverlayGrid);

  public:
    /// Constructor.
    HxOverlayGrid(GraphicalRepMgtType graphicalRepMgtType = MANAGED_BY_BACKGROUND_MOD);

    /// Line width of boundaries.
    HxPortMultiMenu portLineWidth;

    /// Line color of boundaries
    HxPortColorList portColor;

    /// Modify list of displayed intersections
    HxPortButtonMenu portSelection;

    /// Display mode: 0=tissue boundaries only, 1=all boundaries
    HxPortToggleList portMode;

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Create line set from rendered shape
    HxLineSet* createLineSet();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// 
    virtual void savePorts(FILE* fp);

    /// Automatically establish connection to surface or tetragrid
    int autoConnect(HxObject* primary);
  protected:
    virtual ~HxOverlayGrid();

    HxSurface*          surf;
    HxTetraGrid*        grid;
    McBitfield    	faceId;
    int			matTable[128];

    SoShapeKit*		shape;
    SoLineSet*	    	lineSet;

    McDArray<int>       iTris; // triangles at intersections

    void makeOverlay();
    void extractBoundary();
    int getTransform(SbMatrix& mat);

    bool useClipping;
    void getBoundingBox(McBox3f& bbox);
    void computeFacesInBBox();

    /// Hide displayed geometries.
    virtual void removeOverlay();
};

#endif

/// @}
