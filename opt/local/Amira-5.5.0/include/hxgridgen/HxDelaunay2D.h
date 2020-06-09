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

/// @addtogroup hxgridgen hxgridgen
/// @{
#ifndef HX_RANGE_TRIANG_H
#define HX_RANGE_TRIANG_H

#include <hxgridgen/HxGridGenWinDLLApi.h>
#include <mclib/McVec2f.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPort3DPointList.h> 
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxVertexSet.h>
#include <hxsurface/HxSurface.h>

/// 2D delaunay triangulation.

class HXGRIDGEN_API HxDelaunay2D : public HxCompModule {

  HX_HEADER(HxDelaunay2D);
  
  public:
    /// Constructor.
    HxDelaunay2D();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();
	enum  { PLANE, CYLINDER, CLOSED_CYLINDER, SPHERE, CLOSED_SPHERE };
    /// Projection: 0=plane, 1=cylinder (open), 2=cylinder (closed)
    HxPortMultiMenu portProjection;

    /// Determines plane on which to project points (0=xy, 1=xz, 2=yz).
    HxPortRadioBox portPlane;

    /// Determines cylinder on which to project points
    HxPortRadioBox portAxis;

    HxPort3DPointList  portProjectionCenter;
    HxPortButtonList portResetCenter;
    /// Scaling factor
    HxPortFloatTextN portOptions;
    enum { SCALING=0, MAX_EDGE_LENGTH };

    /// Action: 0=do it
    HxPortDoIt portAction;

    /// Compute method
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    ~HxDelaunay2D();

    int iScale;
    int noInput;
    int debugMode;
    /// 0: oiv MeshViz Delaunay, 1: McDelaunay
    int oivTriangulator;
    McDArray<int> pidx;
    McDArray<McVec2f> coords2D;
    void projectOntoPlane(HxVertexSet* data);
    void projectOntoCylinderOrSphere(HxVertexSet* data);
    void createFields(HxSurface*);
	void updateProjectionCenter(HxVertexSet* data, 
		bool resetToPointsCenter);
};

#endif

/// @}
