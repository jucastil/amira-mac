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
#ifndef MCTYPE_INFO_H
#define MCTYPE_INFO_H

#include "McWinDLLApi.h"
#include "McDArray.h"
#include "McAssert.h"

#include <stdio.h>

class McTypedObject;

/** This class provides dynamic type information. The following features
    are supported:


    @li type checking by means of method @c isOfType(McTypeInfo)
    @li creation of class instances using @c createInstance()
    @li maintenance of a global type database allowing one to lookup
	  a type given the corresponding ascii type name


    The last two features are not supported by the native C++ typing
     facilities. The functionality of this class is very similar to
    Inventor's @c SoType. However, in contrast to @c SoType no manual
    type initialization is necessary with @c McTypeInfo.

    In order to use @c McTypeInfo your class should be derived from
    McTypedObject. In addition, you must use two macros, one in
    the class declaration and one in its definition, e.g.,

    @code
    class A : public McTypedObject {
	MC_HEADER(A);
	public:
	    A() { } // default constructor
    };

    MC_INIT_CLASS(A,McTypedObject);
    @endcode

    The default constructor is required in order to be able to use
    @c createInstance().
*/

class MCLIB_API McTypeInfo
{
  public:
    /// Constructor initializes type.
    McTypeInfo(const char* className, McTypedObject* (*createInstance)(),
               const McTypeInfo* parent);

    /// Destructor removes type from global type database.
    ~McTypeInfo();

    /// Gets ascii class name from type.
    const char* getName() const { return className; }

    /// Returns 1 if type is derived from argument.
    int isOfType(const McTypeInfo* t) const;

    /// Returns 1 if  type knows how to create an instance.
    int canCreateInstance() const { return (_create != 0); }

    /** Creates an instance of this type. If type does not know how to
        create an instance, 0 is returned. */
    McTypedObject* createInstance() const { return _create ? _create() : 0; }

    /// Returns the number of parent classes.
    int getNumParents() const { return mParent != 0; }

    /// Returns a particular base class.
    const McTypeInfo* getParent() const { return mParent; }

    /// Gets type from ascii class name.
    static const McTypeInfo* fromName(const char* className);

    ///
    static void removeType(const char* className);
  private:
    const char* className;
    McTypedObject* (*_create)();
    const McTypeInfo* mParent;

    McTypeInfo(const char* className);

    static McDArray<McTypeInfo*>& allTypes();
};

#endif

/// @}
