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
#ifndef HX_BASE_POOL_H
#define HX_BASE_POOL_H

#include <mclib/McHashTable.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <hxcore/HxBase.h>

class HxBase;

/** This class is for internal use only. It provides an array of pointers
    to all HxBase objects. It is used for creating unique labels
    for new objects. In addition, a list of forbidden object names is
    stored. In this list the names of standard Tcl commands are inserted. */

class HxBasePool {

  public:
    
    /** Adds a pointer to an HxBase object. If necessary, the label
        of the object is modified so that it is unique. */
    void add(HxBase *baseObject);

    /// Removes a pointer to an HxBase object.
    void remove(const HxBase *baseObject);

    /// Removes all pointers to HxBase objects.
    void removeAll();

    /// Looks for an object in the base pool.
    HxBase* find(const char* label);

    /// Returns 0 if there is already such a label.
    int isLabelUnique(HxBase* object, const char* label);

    /// Creates a unique label by appending a number
    void setUniqueLabel(HxBase* object, const char* label);

    /// Adds a forbidden label, stores a copy of the string.
    void addForbiddenLabel(const char *forbiddenLabel);

    /// Removes a forbidden label.
    void removeForbiddenLabel(const char *forbiddenLabel);

    /// Removes all forbidden labels.
    void removeAllForbiddenLabels();

    /// Returns the number of objects in the base pool.
    int size() const { return basePool.size(); }

    /// Returns i-th object.
    HxBase* get(int i) const;

    static HxBasePool* getTheBasePool();
  protected:
    /// Constructor
    HxBasePool();

    /// Destructor
    virtual ~HxBasePool();
  private:
    McDArray<HxBase*> basePool;
	McHashTable<McString,bool> m_forbiddenLabels;
};

#define theBasePool (HxBasePool::getTheBasePool())

#endif

/// @}
