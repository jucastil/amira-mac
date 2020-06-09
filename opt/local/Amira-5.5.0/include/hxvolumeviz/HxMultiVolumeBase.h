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
#ifndef HX_MULTI_VOLUME_BASE_H
#define HX_MULTI_VOLUME_BASE_H

#include <hxcore/HxModule.h>
#include <hxcore/HxPlanarMod.h>

#include <hxvolumeviz/HxVolumeData.h>
#include <hxvolumeviz/HxMultiChannelMgr.h>

#include <Inventor/nodes/SoSeparator.h> 

// @TOBEREVIEWED_ALL

class HXVOLUMEVIZ_API HxMultiVolumeBase : public HxModule, public HxMultiChannelMgr
{
    HX_ABSTRACT_HEADER(HxMultiVolumeBase);

public:

    virtual SoGroup* getScenegraph() {return NULL;};    

    virtual void setViewerMask(int mask, int masterMask=0xffffffff);

    virtual void showGeom(SoNode *node);
protected:
    HxMultiVolumeBase();
    /// This constructor leaves type list of portData empty.
    HxMultiVolumeBase(const McTypeInfo* dataType, McInterfaceOwner* owner = 0);
    virtual ~HxMultiVolumeBase();
    HxVolumeData*        m_hxVolData;

    virtual void updateTransform();
private:
    void checkIntersection();
    bool checkIntersection(const McDArray<HxMultiVolumeBase*> & lst);
    static McDArray<HxMultiVolumeBase*> m_renderObjectList;
};

#endif

/// @}
