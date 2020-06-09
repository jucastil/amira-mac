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

/// @addtogroup molecule molecule
/// @{
#ifndef MTGROUPINGLEVEL_H
#define MTGROUPINGLEVEL_H

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#else
#include <iostream.h>
#endif

#include "MtGroup.h"
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>

#include "MoleculeWinDLLApi.h"
#include "MtGroupAttribute.h"

class MolTopology;
class MtGroup;
class MtGroupAttribute;
class MtDynamicGroup;

/// Description of a level in the hierarchy
class MOLECULE_API MtGroupingLevel
{
    friend class MolTopology;

public:
    /// Constructor
    MtGroupingLevel();

    /// Constructor
    MtGroupingLevel(const MtGroupingLevel& gl);

    /// Destructor
    ~MtGroupingLevel();

    inline const char* getName() const;

    /***********************************************************
                     Groups
     ***********************************************************/
  
    /// Get number of Groups in level @c levelIx
    inline int getNumGroups() const;    

    /** Prepare the dynamic array holding the level for containing
        @c size elements, this saves reallocations of memory */
    inline void remax(int size);

    /// return whether groups of level are of fixed size
    inline bool hasFixedGroups() const;

    /// Returns group size of group @c g
    inline int getFixedGroupSize() const;

    /// return the index of the level that groups of level levelIx are referencing
    inline int getReferenceLevelIx() const;


    /***********************************************************
        Methods to access group content */

    /// Returns group size of group @c g
    inline int getGroupSize(int groupIx) const;

    /// Returns group size of group @c g
    inline void resizeGroup(int groupIx, int size);
   
    /// Return the @c ix'th elements of group @c g
    inline int getGroupElement(int groupIx, int elementIx) const;

    /// Get all elements of group @c g
    inline void getGroupElements(int groupIx,McDArray<int>&) const;

    /// Append element @el to the group @c g, will only work if level is not of fixed size
    inline void addGroupElement(int groupIx, int elIx);

    /// Removes the element @c elIx from the group @c groupIx
    inline void removeGroupElement(int groupIx, int elIx);

    /// Set the ix'th element of group @c g to @c el
    inline void setGroupElement(int groupIx, int entryIx, int elIx);

    /// Sets the elements of group @c g to elements, group will not be resized
    inline void setGroupElements(int groupIx, const McDArray<int>& elements);

    /// Sets the elements of group @c g to elements, group will not be resized
    inline void setGroupElements(int groupIx, int nElements, const int* elements);
    

 
   /***********************************************************
         Names */

    /// Find named group in this level, -1 if not found
    int findGroup(const char *name) const;

    /** Find @c named group in this level, -1 if not found
        This function should be used if it is more likely
        that the group is found at the end of the list
    **/
    int findGroupBackward(const char *name) const;

    /// return name of ix'th group, 0 if there is no name
    const char* getGroupName(int ix) const;

    /// return whether any groups of the levels are names
    bool hasGroupNames() const;// { return (nameAttribute != 0); }

    /// set the name of the ix'th group to name
    void setGroupName(int ix, const char * name);



   /***********************************************************
                     Attributes
     ***********************************************************/

   /***********************************************************
         Information*/

    /// Return number of Attributes
    inline int getNumAttributes() const;

    /// Returns name of ix'th attribute
    inline const char * getAttributeName(int attrIx) const;

   /***********************************************************
         Adding/Deleting */

    /** Adds Attribute. If existant, returns existant one. If existant of wrong type, return 0 */

    MtStringAttribute* addStringAttribute(const char* name);

    MtFloatAttribute* addFloatAttribute(const char* name);

    MtIntegerAttribute* addIntegerAttribute(const char* name);

    /** removes attribute of index  */
    bool removeAttribute(int attrIx);
    bool removeAttribute(const char* name);

    /***********************************************************
         Getting */

    /// Return index of attribute with given level and name. -1 if not found
    inline int getAttributeIx(const char *name) const;     

    inline MtGroupAttribute* getAttribute(const char* name);
    inline const MtGroupAttribute* getAttribute(const char* name) const;
    
    MtGroupAttribute* getAttribute(int attrIx);
    const MtGroupAttribute* getAttribute(int attrIx) const;
    
    /// the following methods return 0 if attribute is of wrong type
    inline MtIntegerAttribute* getIntegerAttribute(int attrIx);     
    inline const MtIntegerAttribute* getIntegerAttribute(int attrIx) const;     
    
    inline MtFloatAttribute* getFloatAttribute(int attrIx);     
    inline const MtFloatAttribute* getFloatAttribute(int attrIx) const;     
    
    inline MtStringAttribute* getStringAttribute(int attrIx);
    inline const MtStringAttribute* getStringAttribute(int attrIx) const;

    inline MtIntegerAttribute* getIntegerAttribute(const char* name);     
    inline const MtIntegerAttribute* getIntegerAttribute(const char* name) const;     
    
    inline MtFloatAttribute* getFloatAttribute(const char* name);     
    inline const MtFloatAttribute* getFloatAttribute(const char* name) const;     
    
    inline MtStringAttribute* getStringAttribute(const char* name);
    inline const MtStringAttribute* getStringAttribute(const char* name) const;

    /***********************************************************
                     Misc
     ***********************************************************/

private:
    void makeGroupDynamic(int groupIx);
    void resize(int size);
    
    char * name;

    int addGroup(MtGroup* g);

    /// Groups in this level
    McDArray<MtGroup *> theGroups;    
    /// Attributes in this level
    McDArray<McHandle<MtGroupAttribute> > theAttributes;
    ///
    McHandle<MtStringAttribute> nameAttribute;
    ///
    McHandle<MtIndexAttribute> indexAttribute;
    /// level index that groups of this level are referencing
    int referenceLevelIx;
    /// level index
    int levelIx;
    /// if flag fixed group size is set this var will contain the size
    int groupSize;  



///###-{

/// ---------- legacy support, do not use any longer !!!

public:

    /// Groups in this level
    McDArray<MtGroup *> & groups() const { return ((MtGroupingLevel*)this)->theGroups; }

    /// Unique name
              

//     ///
//     void addAtomsToRest(int * atoms, int len);
        
//     ///
//     void removeAtomsFromRest(int * atoms, int len);

    ///
    int insertGroup(MtGroup * group, int addBefore);

    ///
    int insertGroupSorted(MtGroup * group, 
                          int (*compare)( MtGroup * const & t1, 
                                          MtGroup * const & t2));
    void removeGroup(int ix)    ;


    ///
    enum FindingBehaviour {SEARCH, ADD};

    /// Find @c named type in this level
    MtIntegerAttribute * integerAttribute(const char *name, 
                                          FindingBehaviour b = SEARCH,
                                          bool caseSensitive = true);     
    /// Find @c named type in this level
    MtFloatAttribute * floatAttribute(const char *name, 
                                      FindingBehaviour b = SEARCH,
                                      bool caseSensitive = true);     
    /// Find @c named type in this level
    MtStringAttribute * stringAttribute(const char *name, 
                                        FindingBehaviour b = SEARCH,
                                        bool caseSensitive = true);     

    ///
    MtGroupAttribute * getAttribute(const char *name, bool caseSensitive);     


    ///
    bool addAttribute(MtGroupAttribute *);
    
    ///
    bool attributeIsSelfSubstituting(int ix);

    /// Print this level to an @c ostream
    void list(ostream &os);


    // /// Find an element of this level by name
    //  int findNamedGroup(const char *name);

    /** Attributes
    FIXED_GOUPS is stored directly in the integer variable (-1: no, >=0 yes)*/
    enum { 
        ///
        IS_SEGMENTATION=0x1,
        /// true = level shall be viewable
        IS_VIEWED=0x2,
        ///
        RANGE_GROUPS=0x10,
        ///
        USERDEFINED=0x20
    };
    /// 
    char flags;
    /// Set the specified flag 
    void setAttributes(char mask) { flags |= mask; }
    /// Unset the specified flag 
    void unsetAttributes(char mask) { flags &= ~mask; }
    /// Check the specified flag 
    bool checkAttributes(char mask) const { return (flags & mask) != 0; }
    /// Update IS_SEGMENTATION flag.
    bool updateSegmentationFlag(MolTopology* topo, int level);

    ///
    int touchflags;
    /// touch flags
    enum  {
        NEW_GROUPS            = 0x0100, // groups of this level deleted or new
        NEW_GROUPSETS         = 0x0200, // groups of this level have changed set of subgroups
        NEW_ATTRIBUTE         = 0x0400, // attribute new or deleted
        NEW_ATTRIBUTEVALUE    = 0x0800  // value of an attribute has changed
    };
    /// set touch flags, if no parameter is given all touch flags will be set
    void touch(int mask=0xffff) {
        touchflags |= mask;
    }
    /** unsets touch flags, if no parameter is given all touch flags
        will be set should be called at end of update method of
        HxMolecule **/
    void untouch(int mask=0xffff) {
        touchflags &= ~mask;
    }
    /// returns whether touchflags mask are set
    bool isNew(int mask=0xffff) {
        return (touchflags & mask) != 0;
    }
    
//     ///
//     const MtRestGroup * rest() { 
//         return ( theRestGroup.elements.size() ? &theRestGroup : 0 ); 
//     }


//     ///
//     MtRestGroup theRestGroup;
///###-}
};

#include "MtGroupingLevel_inline.h"

#endif

/// @}
