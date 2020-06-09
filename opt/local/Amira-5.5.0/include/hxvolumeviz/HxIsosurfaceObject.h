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
#ifndef HX_ISOSURFACE_OBJECT_H
#define HX_ISOSURFACE_OBJECT_H

#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <mclib/McDArray.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoMaterial.h>
#include <VolumeViz/nodes/SoVolumeRender.h>
#include <VolumeViz/nodes/SoVolumeIsosurface.h>
#include <VolumeViz/nodes/SoVolumeData.h>

#include <hxvolumeviz/SoMovingComplexity.h>
#include <hxvolumeviz/HxGeometryPriority.h>

// @TOBEREVIEWED_ALL
class HxIsosurfaceRender;
class HxSelectROILDM;
class HxIsosurfaceObject : public McHandable
{
  public:
    /// Constructor
    HxIsosurfaceObject(SoVolumeData* vdata);

    virtual ~HxIsosurfaceObject();

    void addIsovalueRender(HxIsosurfaceRender * render);
    void removeIsovalueRender(HxIsosurfaceRender * render);
    void updateIsoValues();

    SoGroup* getScenegraph() {return m_scene;};

    void setNumSlices(int numSlices);
    void setROI(HxSelectROILDM* selectRoi);
    const int getNumAllSlices() const{ return m_volDepth; }
    const int getNumSlices() const{ return m_volumeRender->numSlices.getValue(); }
    const HxSelectROILDM * getROI() const{ return m_selectROI; }
    
    bool isDisplayed() const {return m_isDisplayed;};
    void setDisplayed(bool state) {m_isDisplayed = state;};
    
    void moveLowResolution(bool state);
  protected:
    McHandle<SoSeparator>           m_scene;
    McHandle<SoMovingComplexity>    m_complexity;
    McHandle<SoSwitch>              m_switch;
    McHandle<SoVolumeRender>        m_volumeRender;
    McHandle<SoMaterial>            m_material;    
    McHandle<SoVolumeIsosurface>    m_volIsosurface;
    McHandle<SoVolumeData>          m_volData;
    McDArray<HxIsosurfaceRender*>   m_isoRenderList;
    HxSelectROILDM*                 m_selectROI;


  private:
    int                m_isoIndex;
    SoGroup*           m_ROIGroup;
    bool               m_isDisplayed;
    int32_t            m_volDepth;
    HxGeometryPriority m_geometryPriority;
};

#endif

/// @}
