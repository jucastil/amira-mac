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

/// @addtogroup hxplot hxplot
/// @{
#ifndef PZ_BASEGROUP
#define PZ_BASEGROUP

#include <mclib/McString.h>

#include <hxplot/PzPlotWinDLLApi.h>

class PzBaseObject;

/**
   Base Class for grouping of base objects (PzBaseObject).
   An instance of this class maintains a list of pointers to base object
   instances.
@author Olaf Paetsch
*/
class HXPLOT_API PzBaseGroup {

  private:

  protected:

    /// Constructor
    PzBaseGroup();

    /// Destructor
    virtual ~PzBaseGroup();

    McDArray<PzBaseObject*> objectList;

    int findObjectByName(const char* name);

    int findObjectByRef(PzBaseObject* refObj);

    int findObjectByType(int type);

  public:

    virtual const char* className() { return "PzBaseGroup"; }

    /// Adds (appends) an object to the end of the list.
    int addObject(PzBaseObject* obj); 

    /// Inserts an object at a given position within the list.
    void insertObject(PzBaseObject* obj, int before = 0);

    /** Inserts an object at a given position given as an object's name 
        within the list.
    */
    void insertObject(PzBaseObject* obj, const char* before);

    /** Inserts an object at a given position given as a pointer to an object
        within the list.
    */
    void insertObject(PzBaseObject* obj, PzBaseObject* before);

    /// Appends an object after a given position within the list.
    void appendObject(PzBaseObject* obj, int after = 0);

    /** Appends an object after a given position given as an object's name 
        within the list.
    */
    void appendObject(PzBaseObject* obj, const char* after);

    /** Appends an object after a given position given as a pointer to an object
        within the list.
    */
    void appendObject(PzBaseObject* obj, PzBaseObject* after);

    /// Exchanges oldObj by newObj and returns oldObj. Depth search!
    PzBaseObject* exchangeObject(PzBaseObject* oldObj, PzBaseObject* newObj);

    /// Removes object from the local list.
    PzBaseObject* removeObject(int index);

    /// Removes object from the local list.
    PzBaseObject* removeObject(const char *name);

    /// Removes object from the local list.
    PzBaseObject* removeObject(PzBaseObject *obj);

    /// Removes object from the tree. Depth removal!
    PzBaseObject* removeObjectFromTree(const char* name);

	///Removes all objects contained in the given list. Depth removal!
	int removeObjects(const McDArray< McString >& ObjectsToRemove, McDArray< PzBaseObject* >& oldObjects);

	///Removes all objects \b not contained in the given list. Depth removal!
	int removeObjectsNotInList(const McDArray< McString >& ObjectsToKeep, const bool bWithGroups, McDArray< PzBaseObject* >& oldObjects);

    /// Removes all objects. Depth removal!
    void clear();

    /// Returns number of local objects.
    int getNumObjects() { return objectList.size(); }

    ///
    PzBaseObject* getObject(int index);

    /// searches and returns an object. Depth search!
    PzBaseObject* findObject(const char* name);

    /// searches and returns an object of given type. Depth search!
    PzBaseObject* findObject(int type);

    /// searches and returns an object in current group.
    PzBaseObject* findObjectInGroup(const char* name);

    /// searches and returns an object of given type in current group.
    PzBaseObject* findObjectInGroup(int type);

    /// searches and returns a group where name belongs to. Depth search!
    PzBaseGroup* findGroupOfObject(const char* name);

    /** Adds pointers to all objects to the given list.
        The whole object tree is traversed and returned.
    */
    int getAllObjects(McDArray< PzBaseObject* >& objectlist, const bool bWithGroups = true);

    ///Returns the names of all objects in the object tree. Depth search!
    int getAllObjectNames(McDArray< McString >& objectNames, const bool bWithGroups = true);

    /// make name unique within the given group.
    static const char* makeUnique(PzBaseGroup* group, const char* name);
};

#endif /* PZ_BASEGROUP */

/// @}
