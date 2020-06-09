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
#ifndef HX_VOLUME_DATA_H
#define HX_VOLUME_DATA_H

#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/nodes/SoVolumeIsosurface.h>

#include <hxcore/HxObject.h>

#include <mclib/McHandle.h>
#include <mclib/McInterface.h>

#include "HxVolumeVizAPI.h"
#include "HxIsosurfaceObject.h"

class VRSlot;

/** This class provides an SoVolumeData object. VolumeViz-based
    display modules should take an HxVolumeData object as input.
    HxVolumeData is an interface class. It is provided by the
    HxVolumeDataObject (a standard Amira data object), and the
    HxLatticeToHxVolumeData (a class which maps an HxInterface to
    an HxVolumeData). */

class HXVOLUMEVIZ_API HxVolumeData : public McInterface
{
    MC_ABSTRACT_HEADER(HxVolumeData);

  public:
    HxVolumeData(McInterfaceOwner* owner);

    virtual SoVolumeData* volumeData() { return m_volumeData; }

    SbVec3i32 getSize();

    const SbBox3f& getVolumeDimensions() {return volumeData()->extent.getValue();}

    bool getMinMax(float &min, float &max);
    
    McPrimType primType();

    void setFileReader(SoVolumeReader &reader);
    SoVolumeReader* getReader();

    const char* getFileName();

    HxIsosurfaceObject* getIsoSufaceObject();

  protected:
    virtual ~HxVolumeData();

    // never access directly to this member, always use the accessor volumeData(), except in constructor/destructor
    // because derived classes override the accessor to initialize the member.
    McHandle<SoVolumeData> m_volumeData;

    McHandle<HxIsosurfaceObject> m_isosurfaceObject;

    VRSlot* m_vrSlot;
};

#endif

/// @}
