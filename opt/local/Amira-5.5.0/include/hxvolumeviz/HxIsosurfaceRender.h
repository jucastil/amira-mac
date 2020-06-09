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

/// @addtogroup hxvolumeviz hxvolumeviz
/// @{
#ifndef HX_ISOSURFACE_RENDER_H
#define HX_ISOSURFACE_RENDER_H

#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>

#include <hxcolor/HxPortColormap.h>

#include "HxMultiVolumeBase.h"
#include "HxVolumeVizAPI.h"

// @TOBEREVIEWED_ALL
class HxIsosurfaceObject;

class HXVOLUMEVIZ_API HxIsosurfaceRender : public HxMultiVolumeBase
{
    MC_HEADER(HxIsosurfaceRender);

  public:
    /// Constructor
    HxIsosurfaceRender();

    /// Compute method
    void compute();

    /// Options
    HxPortToggleList    portOptions;
    enum { M_MOVE_LOW_RES=0};

    /// Input port for region of interest.
    HxConnection        portROI;

    /// Colormap defines transfer function.
    HxPortColormap      portColormap;

    /// Number of slices to be used in 3D mode.
    HxPortIntSlider     portSlices;

    /// Threshold of the isosurface.
    HxPortFloatSlider  portThreshold;

    /** Add a geometry node to the viewers. This function will use the
        transformation of the currently connected data-object. If this
        is not desired, HxBase::showGeom(SoNode*) should be used. */
    virtual void showGeom(SoNode *node);

    /** Removes geometry from the viewers. The reference count of @c node
        is decreased by one. */
    void hideGeom(SoNode *node);

    /** Defines in which viewer geometry is visible. The viewer mask
        of Amira objects can be modified interactively using the orange
        viewer toggles displayed in the work area. Each bit of the mask
        is associated with a particular viewer. Note, that even if the
        viewer mask is set an object may be invisible because the master
        viewer mask is not set. The master viewer mask is changed whenever
        the viewer mask of an upstream data object is modified. */
    void setViewerMask(int mask, int master);

    virtual SoGroup* getScenegraph(){ return m_isoSurfaceObject ? m_isoSurfaceObject->getScenegraph() : 0; }
  protected:
    virtual ~HxIsosurfaceRender();  
    McHandle<HxIsosurfaceObject>    m_isoSurfaceObject;

};

#endif

/// @}
