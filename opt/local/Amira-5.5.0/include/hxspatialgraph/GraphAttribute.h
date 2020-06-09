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

/// @addtogroup hxspatialgraph hxspatialgraph
/// @{
#ifndef GRAPH_ATTRIBUTE_H
#define GRAPH_ATTRIBUTE_H

#include "hxspatialgraphAPI.h"

#include <mclib/McPrimType.h>
#include <mclib/McTypedPointer.h>
#include <mclib/McHandable.h>
#include <mclib/McString.h>

class HxSpatialGraph;

class HXSPATIALGRAPH_API GraphAttribute : public McHandable
{
    GraphAttribute();

public:

    virtual ~GraphAttribute();

    /// Returns primitive data type.
    McPrimType primType() const { return mPrimType; }

    /// Returns the number of data variables per element.
    int nDataVar() const { return mNumDataVar; }

    /// Attribute name
    void setName(const char* name) { mName = name; }
    const char* getName() const { return mName.getString(); }

    /// Returns the number of elements pointed to by dataPtr().
    virtual int size() const=0;

    int elementSize() const { return mSizeElement; }

    int getId() const { return mId; }

    virtual const void* dataPtr() const=0;

protected:

    GraphAttribute(HxSpatialGraph *owner, const char* attributeName, McPrimType type, int nDataVar=1);

    virtual void* dataPtr()=0;

    HxSpatialGraph *mOwner;
    McPrimType  mPrimType;
    int         mNumDataVar;
    McString    mName;
    int         mSizeElement; // size of a single element in bytes

    friend class HxSpatialGraph;

    // unique id
    int mId;

    static int sId;
};

#endif

/// @}
