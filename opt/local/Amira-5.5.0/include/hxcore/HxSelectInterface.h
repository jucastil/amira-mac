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
#ifndef HX_SELECT_INTERFACE_H
#define HX_SELECT_INTERFACE_H

#include <mclib/McString.h>
#include <mclib/McBitfield.h>
#include <mclib/McInterface.h>
#include "HxAmiraWinDLLApi.h"

class HxData;
class HxParamBundle;

/** Interface for modules providing an element selection mechanism.
    Many display modules allow to select different elements like
    triangles, quads, tetrahedrons, hexahedrons, points, or lines
    individually. If such modules provide the HxSelectInterface
    selection of individual elements can be performed in a transparent
    way, for example using the HxGrouping module. */

class HXCORE_API HxSelectInterface : public McInterface {

  MC_ABSTRACT_HEADER(HxSelectInterface);

  public:
    HxSelectInterface (McInterfaceOwner* owner);
  
    /// Modes for unsetting, setting, and toggling selection bits.
    enum BitMode {
	/// Bit should be unset.
	UNSET_BIT=0,
	/// Bit should be set.
	SET_BIT=1,
	/// Bit should be toggled.
	TOGGLE_BIT=2
    };

    /// Returns the number of elements.
    virtual int selectinterface_getNum() const = 0;

    /// Check whether element i is selected.
    virtual int selectinterface_isSelected(int i) const = 0;

    /// Change selection bit of element i.
    virtual void selectinterface_select(int i, int mode = SET_BIT) = 0;

    /// Change selection bit of all elements.
    virtual void selectinterface_selectAll(int mode = SET_BIT) = 0;

    /// Returns selected elements in bitfield.
    virtual void selectinterface_getSelected(McBitfield& bitfield) = 0;

    /// Causes a redraw (should be called after any modification).
    virtual void selectinterface_touch() = 0;

    /// Returns parameter bundle where groups should be stored.
    virtual HxParamBundle* selectinterface_bundle(int create=0) = 0;

    /// Utility function, compiles compressed ascii string from a bitfield.
    static void selectinterface_encode(const McBitfield&, McString&);

    /// Utility function, decodes bitfield from compressed ascii string.
    static void selectinterface_decode(const char*, McBitfield&);

    /// Utility function for implementation of selectinterface_bundle().
    static HxParamBundle* selectinterface_bundle(HxData*, const char* name, int create);
};

template<class PROXY>
class HxSelectInterfaceImplTemplate : public HxSelectInterface 
{
    MC_ABSTRACT_TEMPLATE_HEADER (HxSelectInterfaceImplTemplate <PROXY>);
  
  public:
    HxSelectInterfaceImplTemplate (McInterfaceOwner* owner, PROXY* p) : HxSelectInterface (owner),  proxy(p) {}

    HxSelectInterfaceImplTemplate (McInterface* iface, PROXY* p) 
            : HxSelectInterface (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId()))) 
            ,  proxy(p) {}

    virtual int selectinterface_getNum() const {
        return proxy->selectinterface_getNum(); 
    }

    virtual int selectinterface_isSelected(int i) const {
        return proxy->selectinterface_isSelected(i);
    }

    virtual void selectinterface_select(int i, int mode) {
        proxy->selectinterface_select(i, mode);
    }

    virtual void selectinterface_selectAll(int mode) {
        proxy->selectinterface_selectAll(mode);
    }

    virtual void selectinterface_getSelected(McBitfield& bitfield) {
        proxy->selectinterface_getSelected(bitfield);
    }

    virtual void selectinterface_touch() {
        proxy->selectinterface_touch();
    }

    virtual HxParamBundle* selectinterface_bundle(int create) {
        return proxy->selectinterface_bundle(create);
    }

  protected:
    PROXY* proxy;
};

#endif

/// @}
