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
#ifndef HX_MEASURE_GUI_DRAGGER
#define HX_MEASURE_GUI_DRAGGER

#include <hxmeasure/HxMeasureWinDLLApi.h>
#include <hxmeasure/HxMeasureGUIOIVElem.h>

#include <mclib/McVec3f.h>

#include <Inventor/SbLinear.h>

class SoDragger;
class SoSeparator;
class SoTransform;

//This class handle a GUI "annotation" drawn as an OIV dragger
class HXMEASURE_API HxMeasureGUIDragger : public HxMeasureGUIOIVElem
{
public:

    // Constructor
    HxMeasureGUIDragger () ;

    // Destructor
    virtual ~HxMeasureGUIDragger();

    //special event handling when selected : apply the SoHandleEventAction
    virtual bool guiHandleEventWhenSelected( const SoEvent* event );

    //disable font size button
    virtual bool canHandleFontSize() const {return false;}

    //set point during dragger creation. 
    //pointId is the id of the clicked point
    virtual void setPoint( const SoEvent* event, int pointId){}

    //enable dragger callbacks
    virtual void enableDragger( SbBool enable);

    // Set the center point from 3D world point and normal vector
    virtual void setFirstPoint( const SbVec3f &radiusPoint,const SbVec3f &normalVector );

    // Set the center point from SoEvent
    void setFirstPoint( const SoEvent* evt );

    // Update transformation
    void setRotation( const SbVec3f &normalVector, const SbVec3f &rotationCenter );

    bool getPickedPoint(  const SoEvent* event, SbVec3f& point );

    // HxMeasureGuiElem states

    virtual int isFullyInitialized();

    virtual void setSelected( bool s );

    virtual void setPointSize (float size){}

    virtual void setColor (const McColor& col){}

    virtual void setLocked( bool l );

    /// handle an Inventor event.
    virtual int handleEvent (const SoEvent* event, int viewerId);

    /// TCL
    virtual int parse(Tcl_Interp* t, int argc, char **argv); 

    /// save TCL command sequence that recreates us.
    virtual void saveTCL (FILE* fp, const char* prefix);

protected:

    /// Say if box is built
    bool m_built;

    /// Say if box is built( first clic)
    bool m_init;

    //Matrix from 3D space to dragger space
    SbMatrix m_inverseTransfoMatrix;

    //Associated dragger matrix
    SbMatrix m_transfoMatrix;

    //Open Inventor dragger
    SoDragger* m_dragger;

    //Center for rotation
    SbVec3f m_rotationCenter;

    //Normal vector
    SbVec3f m_normalVector;

    /// Applied transfo
    SoTransform* m_transform;

    // Offset transform because PolygonOffset doesn't work well!
    SoTransform* m_offsetTransform;

    SoSeparator* m_sep;

    //The first selected 3D point
    SbVec3f m_firstPoint;

    //The first mouse location on screen
    SbVec2s m_firstMouseLocation;

    /**
    *  Construct OIV SG basis.
    */
    void buildGeom();
};

#endif //HX_MEASURE_GUI_DRAGGER

/// @}
