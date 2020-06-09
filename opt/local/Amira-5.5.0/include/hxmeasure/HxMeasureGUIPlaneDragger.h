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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_MEASURE_GUI_PLANE_DRAGGER
#define HX_MEASURE_GUI_PLANE_DRAGGER

#include <hxmeasure/HxMeasureWinDLLApi.h>
#include <hxmeasure/HxMeasureGUIDragger.h>

class SoGLRenderAction;

//Class drawing an annotation as a planeDragger (tabPlane or circle)
class HXMEASURE_API HxMeasureGUIPlaneDragger : public HxMeasureGUIDragger
{
public:

    enum ShapeType
    {
        BOX = 0,
        CIRCLE,
        NUM_SHAPES
    };

    /// Constructor
    HxMeasureGUIPlaneDragger ( ShapeType st );

    /// Destructor
    virtual ~HxMeasureGUIPlaneDragger();

    virtual void preRender(int viewerId);

    virtual void setPoint( const SoEvent* event,int pointId );

    /// Enable dragger callbacks
    virtual void enableDragger( SbBool enable);

    /// Set a radius point from 3D world point
    void setBorderPoint( SbVec3f &radiusPoint);

    /// set radius of dragger ( center point & radius point must have been set first)
    void setRadius(const float &radius );

    virtual void updateGuiPorts();

    virtual void updateFromGuiPorts();

    /// Set the center point from 3D world point and normal vector
    virtual void setFirstPoint( const SbVec3f &radiusPoint,const SbVec3f &normalVector );

    virtual void setPointSize (float size);

    virtual void setColor (const McColor& col);

    /// TCL
    virtual int parse(Tcl_Interp* t, int argc, char **argv); 

    /// save TCL command sequence that recreates us.
    virtual void saveTCL (FILE* fp, const char* prefix);

    /// set shape type
    void setShapeType( ShapeType st );

    /// Export internal shape
    virtual HxLineSet* exportShape( );

protected:

    //set to true is just changed offset transformation
    bool m_resetOffset;

    ShapeType m_shapeType;
};

#endif //HX_MEASURE_GUI_PLANE_DRAGGER

/// @}
