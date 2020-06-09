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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_TYPED_ELEMENT_H
#define MC_TYPED_ELEMENT_H

#include "McWinDLLApi.h"
#include "McPrimType.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "McAssert.h"
#include "McMalloc.h"

/** This class represents a data element with nDataVar values of type McPrimType. Operations are defined as with vectors. */

class MCLIB_API McTypedElement
{
 public:

	 /// Default constructor (e.g. so McTypedElement can be used in McDArrays)
	 McTypedElement() {
		toFree = 0;
		data = 0;
	 }
    
     /// Copy constructor
     McTypedElement(const McTypedElement& v) {
        toFree = 0;
        myPrimType = v.primType();
        myNDataVar = v.nDataVar();
        init();
        setValue(v);   
     }

    /// Constructor. Memory is allocated when d=0.
     McTypedElement(McPrimType p, int n, void* d=0) :
        myPrimType(p), 
        myNDataVar(n) 
     {
         toFree = 0;
         init(d);
     }

     /// Destructor
    ~McTypedElement() {
        if (toFree) {
            mcfree(toFree);
            toFree = 0;
        }
    }
    
    /// Sets the value by copying form inData
    void setValue(const void* inData) {
        mcassert (inData);
        memcpy(data, inData, myPrimType.size()*myNDataVar);
    }

    /// Copies value from other McTypedElement. Primtype and nDataVar must be equal.
    void setValue(const McTypedElement& e) {
        mcassert(myNDataVar == e.nDataVar());
        mcassert(myPrimType == e.primType());
        memcpy(data, e.dataPtr(), myPrimType.size()*myNDataVar);
    }

    /// Copies the value to outData
    void getValue(void* outData) const {
        mcassert(outData);
        memcpy(outData, data, myPrimType.size()*myNDataVar);
    }

    /// Returns the data pointer.
    void* dataPtr() const {
        return data;
    }

    /// Returns number of values
    int nDataVar() const {
        return myNDataVar;
    }

    /// Returns the type of the data.
    McPrimType primType() const {
        return myPrimType;
    }

    /// Computes the per element sum.
    McTypedElement& operator+=(const McTypedElement& v);

    /// Computes the per element difference.
    McTypedElement& operator-=(const McTypedElement& v);

    /// Assignment operator
    McTypedElement& operator=(const McTypedElement& v);

    bool isEqual(const McTypedElement& v, const float eps=0.0001f) const;

    /// Returns the vector length of the element
    double length() const;

protected:
    void* data;
    void* toFree; // if toFree==0, memory is managed externally
    McPrimType myPrimType;
    int myNDataVar;

    void init(void* d=0) {
        if (d) {
            toFree = 0;
            data = d;
        }
        else {
            if (toFree) {
                mcfree(toFree);
                toFree = 0;
            }
            toFree = mcmalloc(myPrimType.size()*myNDataVar);
            data = toFree;
        }
    }
};

#endif

/// @}
