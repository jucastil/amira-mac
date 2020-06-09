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

/// @addtogroup hxmeshviz hxmeshviz
/// @{
#ifndef HX_PO_MESH_SKIN_H
#define HX_PO_MESH_SKIN_H

#include "hxmeshvizAPI.h"

#include <hxsurface/HxTriBase.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonMenu.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransparencyType.h>
#include <MeshViz/nodes/PoNonLinearDataMapping2.h>
#include <MeshViz/nodes/PoNonLinearDataMapping.h>
#include <Inventor/nodes/SoSwitch.h>
#include <MeshViz/3Ddata/PoMeshSkin.h>

//-----------------------------------------------------------------------------
class HXMESHVIZ_API HxPoMeshSkin : public HxTriBase
{
    HX_HEADER(HxPoMeshSkin);

public:

    /// Constructor
    HxPoMeshSkin();

    /// Update method
    virtual void update();
 
    /// Compute method
    virtual void compute();
 
    /// Allows that modules can be connected to grids and scalar fields.
    virtual int autoConnect(HxObject* primary);

    /// Modify list of displayed materials
    HxPortButtonMenu portSelection;
    
    /// Color mode to be used.
    HxPortMultiMenu portColorMode;

    /** This is called when SoSurface parameters have been changed via
	the <em> more options</em> menu of HxPortDrawStyle. */
    virtual void drawStyleChanged(DrawStyleParameters what);

    /// Create a HxSurface containing all selected triangles.
    virtual void createSurfaceData();

protected:
    virtual ~HxPoMeshSkin();

    static void preRebuildCB(void *userData, PoBase *base);
    static void postRebuildCB(void *userData, PoBase *base);

    static const SbColor* colorDataMappingCB(void *userData, float value);
    static float transparencyDataMappingCB(void *userData, float value);

    static int colorFieldSourceCheck(void* userData, HxObject* src);

    static void triangleCB(void *data, SoCallbackAction *action, 
        const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2, const SoPrimitiveVertex *v3);

    McHandle<SoSeparator>               m_scene;
    McHandle<SoTransparencyType>        m_transparencyType;
    McHandle<PoNonLinearDataMapping2>   m_gridDataMapping;
    McHandle<PoNonLinearDataMapping>    m_fieldDataMapping;
    McDArray< McHandle<SoSwitch> >      m_switchs;
    McHandle<PoMeshSkin>                m_skin;
};

#endif

/// @}
