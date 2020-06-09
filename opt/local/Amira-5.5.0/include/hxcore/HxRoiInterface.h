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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_ROI_H
#define HX_ROI_H

#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>
#include <mclib/McInterface.h>
#include <mclib/McMat4f.h>

#include "HxAmiraWinDLLApi.h"

/** Interface for objects providing a region of interest
    information (a box). */

class HXCORE_API HxRoiInterface : public McInterface {

  MC_ABSTRACT_HEADER(HxInterface);

  public:
    HxRoiInterface (McInterfaceOwner* owner);

    /** Returns ROI.
        The values are stored in the following order:
        minX, maxX, minY, maxY, minZ, maxZ.
      */
    virtual void getRoi(float bbox[6]) const;

    /// returns transformation of ROI
    virtual void getTransformation( McMat4f & outTrans ) const;

    /// returns an axis aligned box representing the ROI
    McBox3f getRoiBox() const;

    /// Computes bounding box of data object.
    McVec3f getRoiSize() const;

    /// Computes bounding box of data object.
    McVec3f getRoiCenter() const;

    /// returns the lower, left corner.
    McVec3f getRoiOrigin () const;

    // FIXME: was never used, SP
//    virtual int parse(Tcl_Interp* t, int argc, char **argv);
};

template <class PROXY>
class HxRoiInterfaceProxyTemplate : public HxRoiInterface {
    MC_ABSTRACT_TEMPLATE_HEADER (HxRoiInterfaceProxyTemplate<PROXY>);
    public:
        HxRoiInterfaceProxyTemplate (McInterfaceOwner* owner, PROXY* p) : HxRoiInterface (owner),  proxy(p) {}

        HxRoiInterfaceProxyTemplate (McInterface* iface, PROXY* p)
                : HxRoiInterface (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId())))
                ,  proxy(p) {}

        void getRoi(float bbox[6]) const {
            proxy->getRoi (bbox);
        }

        /// returns transformation of ROI
        virtual void getTransformation( McMat4f & outTrans ) const
        {
            proxy->getTransformation( outTrans );
        }

    protected:
        PROXY* proxy;
};

#endif

/// @}
