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
#ifndef MOL_TOPOLOGY_H
#define MOL_TOPOLOGY_H

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#include <mclib/McHandable.h>
#include <mclib/McDArray.h>

#include "MoleculeWinDLLApi.h"

#include "MtGroup.h"
#include "MtGroupRef.h"   
#include "MtGroupingLevel.h"

#include <mclib/McDataPointer.h>
#include <mclib/McString.h>
#include <mclib/McException.h>


template <class T1, class T2> class McHashTable;
class McBitfield;
class GroupRefTranslator;

/** \brief Data container that can be registerd in a topology. 

    Arbitrary data classes may be derived from MolData and registered
    in the topology with the setData method. Most Amira code, however, only considers the three types
    MolDataInt, MolDataFloat and MolDataString (if at all).
*/

class MolData {
    friend class MolTopology;
private:
    McString name;
public:
    MolData(const char* name) {this->name = name;}
    virtual ~MolData() {}
    /// Returns name of data object
    const char* getName() const { return name.getString(); }
    /// Deep copy of data object. To be implemented in derived classes.
    virtual MolData* duplicate() const = 0;
    /// Returns a data value as a string
    virtual void getValueAsString(McString& value) const { 
        McString str;str.printf("Error: String conversion of molecular data %s not possible.",getName());
        throw McException(str.getString());
    }
    /// sets a data value from a string
    virtual void setValueFromString(const char* s) { 
        McString str;str.printf("Error: String conversion of molecular data %s not possible.",getName());
        throw McException(str.getString());
    }
};

/** Template class for McDArray contained data. Type must be duplicatable by assignment.
    To use it with objects without valid (deep) copy constructors, or with pointers, override the
    setValue,duplicate,resize methods.
*/

template <class T> class TypedMolData : public MolData {
protected:
    T data;
public:
    TypedMolData(const char* name) : MolData(name) {}
    /// initialize with single data
    TypedMolData(const char* name,T value) : MolData(name) { setValue(value); }
    /** Initialize with data. Automatically resizes.*/
    virtual const T& getValue() const {return data;}
    /** Sets i'th element. No automatic resize, i must be within range.*/
    virtual void setValue(const T& val) {data=val;}
};

/** Child class of MolData for specific data types that are used to resolve polymorphism in the Amira code. 
    If you want your data to be handled by writers, only use these. */

class MolDataInt : public TypedMolData<int> {
public:
    MolDataInt(const char* name) : TypedMolData<int>(name) {}
    /// initialize with single data
    MolDataInt(const char* name,int value) : TypedMolData<int>(name,value) {}
    void getValueAsString(McString& s) const { s.printf("%i",getValue());}
    void setValueFromString(const char* s) { int v = atoi(s);setValue(v);}
    MolData* duplicate() const {return new MolDataInt(*this);}
};

class MolDataFloat : public TypedMolData<float> {
public:
    MolDataFloat(const char* name) : TypedMolData<float>(name) {}
    /// initialize with single data
    MolDataFloat(const char* name,float value) : TypedMolData<float>(name,value) {}
    void getValueAsString(McString& s) const {s.printf("%f",getValue());}
    void setValueFromString(const char* s) {  float v = (float)atof(s);setValue(v);}
    MolData* duplicate() const {return new MolDataFloat(*this);}
};

class MolDataString : public TypedMolData<McString> {
public:
    MolDataString(const char* name) : TypedMolData<McString>(name) {}
    /// initialize with single data
    MolDataString(const char* name,McString& value) : TypedMolData<McString>(name,value) {}
    void getValueAsString(McString& s) const { s=getValue();}
    void setValueFromString(const char* s) { return setValue(s);}
    void setValue(const char* s) {TypedMolData<McString>::setValue(McString(s));}
    MolData* duplicate() const {return new MolDataString(*this);}
};


//@SORT_MEMBER_DOCS 0
/** \brief  Molecule topology.

    Stores atoms, bonds between atoms, and arbitrary other groupings and
    their attributes (i.e. all non coordinate related data of a molecule).
    MolTopology contains the following data:
        - an array of MtGroupingLevels
    It contains methods for accessing the grouping levels.
    It also contains convenience functionality for certain groups
    (atoms, bonds) and specific offten recurring attributes.
    \nosubgrouping
*/

class MOLECULE_API MolTopology : public McHandable {
public:
    /// Constructor 
    MolTopology();
    
    /// Copy constructor 
    MolTopology(const MolTopology& T);

    /// Creates exact copy of the MolTopology
    MolTopology* duplicate() const;
    
    /// Constructor 
    ~MolTopology();
    
    
    /** \name Levels
    */
    //@{

    enum LEVEL_FLAGS {
        /// All groups are of the same size
        LF_FIXED_GROUP_SIZE       = 0x00000001,
        /// Level has not been read from the file reader but created by the user
        LF_USER_DEFINED           = 0x00000002,
        /// Are sets of atoms of each group disjunct?
        LF_ATOM_SEGMENTATION      = 0x00000004,
        LF_IS_VIEWED              = 0x00000008,
        LF_DEFAULT                = LF_ATOM_SEGMENTATION | LF_IS_VIEWED
    };

    /// Return number of levels contained in the topology
    inline int getNumLevels() const;
    
    /** Add a level. Return its index. If already existant, returns index of found level
        name must be valid. Make sure to call isValidLevelName() before calling addLevel.
        reference level must be valid or -1 (no reference level).
        Level Flags must be supplied. If level flag FIXED_GROUP_SIZE is given then fixedsize
        must contain the number of contained elements of each group.
        If level already exists and level flags don't match returns -1. */
    int addLevel(const char *name,int referenceLevel,int levelflags=LF_DEFAULT,int fixedsize=-1);

    /**  Sets level name.
         LevelIx must be valid. 
         name must be valid. Make sure to call isValidLevelName() first.
         Returns whether name change succeeded (level may not be atoms or 
         bonds and no other level with the same name may exist) */
    bool setLevelName(int levelIx, const char* name);

    /** returns whether level name has valid syntax. */
    static bool isValidLevelName(const char* name);
//@}
    /**
 * \defgroup IntVariables Global integer variables
 */
/*@{*/

    /** Returns the number of elements of each group of the level, if the level has a fixed 
        group size, else return -1.
        LevelIx must be valid. */
    inline int getFixedGroupSize(int levelIx) const;

    /** Sets the LF_FIXED_GROUP_SIZE flag and the groups size to size. 
        If the level already contains groups, returns false.
        LevelIx must be valid. */
    bool setFixedGroupSize(int levelIx,int size);
    
    /** Sets the LF_FIXED_GROUP_SIZE flag and the groups size to size. 
        If the level already contains groups which reference a different level returns false.
        LevelIx must be valid. RefLevelIx must be valid or -1 */
    bool setReferenceLevelIx(int levelIx,int reflevelIx);
    
    /** Removes a elvel. 
        levelIx must be valid.
        Returns false if level not removable (i.e. atom or bond level) */
    bool removeLevel(int levelIx);

    /** Clears all groups from level including dependant groups in other levels
        levelIx must be valid. */
    void clearLevel(int levelIx);
    
    /** Return index of level that groups of levelIx are referencing.
        levelIx must be valid. */
    int getReferenceLevelIx(int levelIx) const;

    /** Prepare the dynamic array holding the level for containing
        @c size elements, this saves reallocations of memory.
        levelIx must be valid. */
    void remaxLevel(int levelIx,int size);

    /** return whether groups of level are of fixed size.
        levelIx must be valid. */
    bool hasFixedGroups(int levelIx) const;

    /** returns the level name, levelIx may not be out of bounds.
        levelIx must be valid. */
    inline const char* getLevelName(int levelIx) const;
   
    /// level "atoms"
    inline int getAtomLevelIx() const;
    
    /// level "bonds"
    inline int getBondLevelIx() const;
    
    /// level "residues"
    inline int getResidueLevelIx() const;    

    /// level "strands"
    inline int getStrandLevelIx() const;    

    /// level "sites"
    inline int getSiteLevelIx() const;    

    /// level "secondary_structure"
    inline int getSecondaryStructureLevelIx() const;    

    /// level "chains"
    inline int getChainLevelIx() const;    

    /// level "angles" (i.e. Bond Angles)
    inline int getAngleLevelIx() const;   

    /// level "dihedrals"
    inline int getDihedralLevelIx() const;   

    /// get index of level with given name, returns -1 if not found. Lookup is case insensitive
    int getLevelIx(const char *name) const;
    
    //@}
    
    // ----------------------------------------------------------
    
    /* All functionality that potentially requires information
       about groups of other levels in in MolTopology
       Find the functionality to set/get elements of a group
       and its attributes in MtGroupingLevel */

    /** \name Groups
    */
    //@{
    
    /// Get number of Atoms
    inline int getNumAtoms() const;
    
    /// Get number of Bonds
    inline int getNumBonds() const;
    
    /// Get number of Groups in level @c levelIx
    inline int getNumGroups(int levelix) const;    

    
    /** Return index of the bond connecting the @c from'th with the 
        @c to'th atom. The order is irelevant. */
    int findBond(int from, int to) const;

    /// Find all atoms to which a bond from atom @c idx exists.
    void getBondedAtoms(int idx, McDArray<int> &atoms) const;
    
    /// Find for all atoms the list of bonds it belongs to.
    void buildAtomBondList(McDArray<McDArray<int> > &atomBondList) const;

    /// Find for all atoms the list of atoms it is bonded with
    void buildAtomBondTable(McDArray<McDArray<int> > &atomBondTable) const;    

    
    /** This will only add the atom but won't change the 
        number of coordinates in the molecule which are stored
        in the Moleule class.  set the coordinate afterward using the index. */
    int addAtom();
    
    /// add an empty bond
    int addBond();

    /// add a bond between the two atoms,  
    int addBond(int a1,int a2);

    /// Adds an empty new group. Returns index of group
    int addGroup(int level);

    /** Adds new group to level containing elements.
        Return index of group or -1 if failed.*/
    int addGroup(int level, const McDArray<int>& elements); 

    /** Add new Group to level containing elements, which must be a pointer
        to memory of nElements integer values. 
        Returns index of group or -1 if failed */
    int addGroup(int level, int nElements, const int* elements);

    /** Add new Group to level containing elements, which must be a pointer
        to memory of nGroups * getFixedGroupSize(level) integer values. 
        This method only works for levels which have a fixed group size.
        Returns index of first group or -1 if failed */
    int addGroups(int level, int nGroups, const int* elements);

    /** Moves a group to the new index. All indices of groups in the range  
        [newGroupIx,groupIx-1]  will increase by one. Attributes will be copied.
        Referenced group elements in dependant levels will also be updated. 
        Coordinates will not be updated. If you are moving atoms, you need to use the
        function MolObject::moveGroup which will additionally move coordinates for the atom level. */
    void moveGroup(int level,int groupIx, int newGroupIx);
    
    ///
    void removeGroup(int level,int gIx);

    /// Returns group size of group @c g
    inline int getGroupSize(int levelIx,int groupIx) const;

    /// Returns group size of group @c g
    inline void resizeGroup(int levelIx,int groupIx, int size);
   
    /// Return the @c ix'th elements of group @c g
    inline int getGroupElement(int levelIx,int groupIx, int elementIx) const;

    /// Get all elements of group @c g
    inline void getGroupElements(int levelIx,int groupIx,McDArray<int>&) const;

    /// Append element @el to the group @c g, will only work if level is not of fixed size
    inline void addGroupElement(int levelIx,int groupIx, int elIx);

    /// Removes @c entryIx'th element from group @c groupIx of level @c levelIx
    inline void removeGroupElement(int levelIx,int groupIx, int entryIx);

    /// Removes all elements from group @c groupIx of level @c levelIx
    inline void clearGroup(int levelIx,int groupIx);

    /// Set the ix'th element of group @c g to @c el
    inline void setGroupElement(int levelIx,int groupIx, int entryIx, int elIx);

    /// Sets the elements of group @c g to elements, group will be resized if neccessary
    inline void setGroupElements(int levelIx,int groupIx, const McDArray<int>& elements);

    /// Find named group in this level, -1 if not found
    inline int findGroup(int levelIx,const char *name) const;

    /** Find @c named group in this level, -1 if not found
        This function should be used if it is more likely
        that the group is found at the end of the list
    **/
    inline int findGroupBackward(int levelIx,const char *name) const;

    /// return name of ix'th group, 0 if there is no name
    inline const char* getGroupName(int levelIx,int ix) const;

    /// return whether any groups of the levels are names
    inline bool hasGroupNames(int levelIx) const;

    /// set the name of the ix'th group to name
    inline void setGroupName(int levelIx,int ix, const char * name);
    
    /** Return the first occurance of a group of level which 
        recursively contains atom atomIx. -1 if not found */
    int findAtomInLevel(int atomIx,int searchLevelIx) const;    
    
    /// Return list of groups of level which recursivly contain atom
    void findAtomInLevel(int atomIx,int searchLevelIx, McDArray<int> &list) const;

    /// Return list of groups in searchLevel which recursivly contain group
    void findGroupInLevel(int levelIx, int groupIx, int searchLevelIx,
                          McDArray<int> &list) const;
    
    /// Check wether referenced group contains the atom recursively
    bool isAtomInGroup(int atomIx,int searchLevelIx,int searchGroupIx ) const;
    
    /// Check whether referenced group contains another one
    bool isGroupInGroup(int levelIx,int groupIx,int searchLevelIx, int searchGroupIx) const;

    /** Get the atoms that belong recursivley to a group.
        Append their indices to array. */
    void getAtomsOfGroup(int levelIx,int groupIx,McDArray<int> &atoms) const;
    
    /** Get the atoms that belong recursivley to a group.
        Set their indices in bitifield. Bitfield will be only resized 
        and unset if its size is not equal to number of atoms in molecule. */
    void getAtomsOfGroup(int levelIx,int groupIx, McBitfield &atoms) const;

    //@}

    // ------------------------------------------------------------

    /** \name Attributes
    */
    //@{    

    /// Return number of attributes
    inline int getNumAttributes(int levelIx) const;

    /// Returns name of ix'th attribute
    inline const char * getAttributeName(int levelIx,int attrIx) const;
    
    /** Sets the name of an attribute. If such a name already exists for that
        level it won't be changed and false will be returned */
    bool setAttributeName(int levelIx,int attrIx,const char* name);
   
    ///
    static bool isValidAttributeName(const char*);

    ///
    static bool isValidStringAttributeValue(const char *);
    
    ///
    static bool isValidFloatAttributeValue(const char *);
    
    ///
    static bool isValidIntegerAttributeValue(const char *);
    ///
    MtStringAttribute* addStringAttribute(int levelIx,const char* name);

    ///
    MtFloatAttribute* addFloatAttribute(int levelIx,const char* name);

    ///
    MtIntegerAttribute* addIntegerAttribute(int levelIx,const char* name);

    ///
    bool removeAttribute(int levelIx, int attrIx);

    ///
    bool removeAttribute(int levelIx, const char* name);
    
    /// Get index by name. -1 if not found
    inline int getAttributeIx(int levelIx,const char *name) const;     

    /// Get attribute by index, 0 if index <0
    inline MtGroupAttribute* getAttribute(int levelIx,int attrIx);
    
    /// Get attribute by index, 0 if index <0
    inline const MtGroupAttribute* getAttribute(int levelIx,int attrIx) const;
    
    /// Get typed attribute by index. Returns 0 if attribute is of wrong type or not found
    inline MtIntegerAttribute* getIntegerAttribute(int levelIx,int attrIx);     
    /// Get typed attribute by index. Returns 0 if attribute is of wrong type or not found
    inline const MtIntegerAttribute* getIntegerAttribute(int levelIx,int attrIx) const;     
    /// Get typed attribute by index. Returns 0 if attribute is of wrong type or not found    
    inline MtFloatAttribute* getFloatAttribute(int levelIx,int attrIx);     
    /// Get typed attribute by index. Returns 0 if attribute is of wrong type or not found
    inline const MtFloatAttribute* getFloatAttribute(int levelIx,int attrIx) const;     
    /// Get typed attribute by index. Returns 0 if attribute is of wrong type or not found    
    inline MtStringAttribute* getStringAttribute(int levelIx,int attrIx);
    /// Get typed attribute by index. Returns 0 if attribute is of wrong type or not found
    inline const MtStringAttribute* getStringAttribute(int levelIx,int attrIx) const;

    /// Get attribute by name. Returns 0 if not found.
    inline MtGroupAttribute* getAttribute(int levelIx, const char* name);
    /// Get attribute by name. Returns 0 if not found.
    inline const MtGroupAttribute* getAttribute(int levelIx, const char* name) const;
    
    /// Get typed attribute by name. Returns 0 if wrong type or not found.
    inline MtIntegerAttribute* getIntegerAttribute(int levelIx,const char* name);
    /// see getIntegerAttribute()
    inline const MtIntegerAttribute* getIntegerAttribute(int levelIx,const char* name) const;     
    /// see getIntegerAttribute()
    inline MtFloatAttribute* getFloatAttribute(int levelIx,const char* name);
    /// see getIntegerAttribute()
    inline const MtFloatAttribute* getFloatAttribute(int levelIx,const char* name) const;     
    /// see getIntegerAttribute()
    inline MtStringAttribute* getStringAttribute(int levelIx,const char* name);
    /// see getIntegerAttribute()
    inline const MtStringAttribute* getStringAttribute(int levelIx,const char* name) const;
    
    
    ///
    enum FINDING_BEHAVIOUR {
        /// only search, return 0 if not found
        FB_SEARCH,
        /// add if not found
        FB_ADD
    };
    
    ///
    MtIntegerAttribute* getAtomAtomicNumberAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);
    ///
    MtFloatAttribute* getAtomRadiusAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);
    ///
    MtFloatAttribute* getAtomTemperatureAttribute(FINDING_BEHAVIOUR b = FB_SEARCH); 
    ///
    MtFloatAttribute* getAtomOccupancyAttribute(FINDING_BEHAVIOUR b = FB_SEARCH); 
    ///
    MtFloatAttribute* getAtomChargeAttribute(FINDING_BEHAVIOUR b = FB_SEARCH); 
    ///
    MtIntegerAttribute* getAtomFormalChargeAttribute(FINDING_BEHAVIOUR b = FB_SEARCH); 
    ///
    MtStringAttribute* getAtomTypeAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);
    ///
    MtStringAttribute* getAtomNameAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);

    ///
    MtIntegerAttribute* getBondTypeAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);
    ///
    MtStringAttribute* getBondNameAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);

    ///
    MtStringAttribute* getResTypeAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);
    ///
    MtStringAttribute* getResNameAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);

    ///
    MtStringAttribute* getSecStructTypeAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);
    ///
    MtStringAttribute* getSecStructNameAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);

    ///
    MtStringAttribute* getSiteNameAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);
    ///
    MtStringAttribute* getStrandNameAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);

    ///
    MtStringAttribute* getChainNameAttribute(FINDING_BEHAVIOUR b = FB_SEARCH);


    //@}    

    // -----------------------------------------------------------
   
    /** \name Data
    */
    //@{ 
    
    /** Sets a data object. The data will be owned by the MolTopology.
        If a data object of the same name already exists, the old one will
        be deleted and overwritten. */
    void setData(MolData* p);
    ///  Returns index of data object with given name
    int getDataIx(const char* name) const;    
    /// Deletes and removes given data object from list. Indices of data objects may change.
    void deleteData(const char* name);
    /// Deletes and removes given data object from list. Indices of data objects may change.
    void deleteData(int ix);
    /// Returns data object of given name
    const MolData* getData(const char* name) const;
    /// Returns data object of given index
    const MolData* getData(int ix) const;
    /// 
    MolData* getData(const char* name);
    ///
    MolData* getData(int ix);
    /// Returns number of data objects in MolTopology
    int getNumData() const;
    /** Renames data of given index. Does nothing and returns false if 
        such a name already exists for another MolData */
    bool setDataName(int ix,const char* newName);
    /// sets value of data entry 'name'
    void setName(const char * name);
    
    /// returns value of data entry 'name' or "" if it does not exist.
    const char *getName() const;

    //@}

    /** Does some basic valdity checks regarding conventions of the molecular data structure
        This should be called by all readers and after editing. If false is returned,
        the string will contain an error string.
        The following contracts will be checked:
        - level 'atoms' exists with index 0 reference level -1 and fixed group size 0
        - level 'bonds' exists with index 1 reference level 0 and of fixed group size 2.
           no bonds allowed that connect atom with itself or bonds that appear multiple times.
        - if 'residues' level exists, it has to have reference level 0
        - if 'seondary_structure' level exists, it has to have the residue level as the reference level
        - if the 'chains' level exists it has to have the residue level as the reference level.
    */
    bool checkValidity(McString& error) const;
    
    /// Editing

    void deleteGroups(
        const McDArray<MtGroupRef>& grList);
    void deleteGroups(
        int level, 
        const McBitfield& bf);
    
    /** deletes given groups incl. all dependant groups which
        become empty or cannot be translated (because of fixed size)
        
        the array contains one bitfield for each level which contains
        which groups are to be deleted, after function returns 
        all groups will be set in bitfield which have been deleted
        ( thus the groups originally set + groups which were deleted because
        of dependance on deleted groups)
        the array needs to be of size <number of levels> but bitfields
        of levels with no groups to be deleted can be kept empty
        they will be resized automatically if any groups of that level 
        need to be deleted due to dependance

        updates the GroupRefTranslator for all groups 
    */
    void deleteGroups(
        McDArray<McBitfield>& bfs,
        GroupRefTranslator* trans=NULL);
    

    /** copy all atoms wich are set in the bitfield from
        sourceTop to *this including all dependant groups 
        updates the GroupRefTranslator for the copied groups */
    void copyGroups(
        const MolTopology* sourceTop,
        const McBitfield& bf,
        GroupRefTranslator* trans=NULL);

    /** copies groups of level sourceLevelIx whose subgroups have a
       mapping entry in GroupRefTranslator
       from sourceTop to this Top
       updates the GroupRefTranslator for the copied groups
       note: atomLevel must be handled seperately
    */
    void copyGroupsOfLevelByTranslator(
        const MolTopology* sourceTop,
        int sourceLevelIx,
        GroupRefTranslator& trans);


    /** copies attributes of all groups in Level sourceLevelIx which have a
       mapping entry in GroupRefTranslator
       from sourceTop to this Top
    */
    void copyAttributesOfLevelByTranslator(
        const MolTopology* sourceTop,
        int sourceLevelIx,
        GroupRefTranslator& trans);
    
    /** copies all atoms from sourceTop to this top
       whose bitfield entry is set
       updates the GroupRefTranslator for the copied groups
    */
    void copyAtomsByBitfield(
        const MolTopology* sourceTop,
        const McBitfield& atomToBeCopied,
        GroupRefTranslator& trans);

    /// removes duplicate bonds and recursive bonds. Ensures that first atom index in bond is always smaller than 2nd
    void cleanBonds();


    protected:
        McHashTable<McString,int>* dataMap;
        McDArray<MolData*> dataValues;

private:
    McDArray<MtGroupingLevel *> levels;


    /** \name Deprecated 
    do not use any longer !!!
    */
    //@{
public:
    MtGroupingLevel* getLevel(int levelIx);
    const MtGroupingLevel* getLevel(int levelIx) const;
    void printRef(MtGroupRef r, ostream& os) const;
    //
    int refToLinIndex(MtGroupRef ) const;
    // Return the number of atoms contained in this topology
    // Prepare the topology for containing @c num atoms
    void prepNumAtoms(int num) 
    { prepLevelSize(MtGroupRef::atomLevel, num); }
    // Add an atom to the topology and return its @c MtGroupRef
    MtGroupRef addAtom(MtAtom * atom)
    { return addGroup(MtGroupRef::atomLevel, atom); }
    // Return the @c ixth atom 
    MtAtom & atom(int ix){
        return *(MtAtom*)levels[MtGroupRef::atomLevel]->groups()[ix];
    }
    // Remove all atoms
    void clearAtoms() { levels[MtGroupRef::atomLevel]->theGroups.clear(); }

    //
    MtGroupingLevel * atomLevel() { 
        return levels[MtGroupRef::atomLevel]; 
    }



    // Prepare the topology for containing @c num bonds
    void prepNumBonds(int num) { 
        prepLevelSize(MtGroupRef::bondLevel, num); 
    }
    
    // Add a bond to the topology and return its @c MtGroupRef
    MtGroupRef addBond(MtBond * bond);
    // Return the @c ixth bond
    MtBond & bond(int ix){
        return *(MtBond*)levels[MtGroupRef::bondLevel]->groups()[ix];
    }

    ///
    MtGroupingLevel * bondLevel() { 
        return levels[MtGroupRef::bondLevel]; 
    }

    // Add a group to the @c levelth level. 
    MtGroupRef addGroup(int level, MtGroup * group); 
    // Insert a group to the @c levelth level before index @c addBefore 
    MtGroupRef insertGroup(int level, MtGroup * group,int addBefore); 
    // Removes group @c ref
    void removeGroup(MtGroupRef& ref); 
    // Find the indexed atom in the @c levelth level. 
    MtGroupRef findAtomInLevelOld(int level,int atom_ix) const;
    // Return list of groups in which atom was found.
    void findAtomInLevel(int level,int atom_ix, 
                         McDArray<MtGroupRef> &list) const;
    // Return list of groups in which group was found.
    void findGroupInLevel(int level, MtGroupRef & gr, 
                          McDArray<MtGroupRef> &list) const;
    // Return the referenced group
    MtGroup& getGroup(MtGroupRef r) { 
        return getGroup(r.level, r.ix); 
    }
    // Return the referenced group
    MtGroup & getGroup(int level,int ix) { 
        return *levels[level]->groups()[ix]; 
    }
    // Define a new group (sets error_text)
    MtGroupRef defineGroup(const char *name, const char *spec,
                           const char *text);
    // Define a new group (sets error_text)
    MtGroupRef defineGroup(const char *name, McBitfield atoms,
                           const char *text);

    // Check wether referenced group contains the atom. 
    bool isAtomInGroup(MtGroupRef ref, int atom_ix) const;
    
    // Check whether referenced group @c ref contains the group @c gr. 
    bool isGroupInGroup(MtGroupRef ref, MtGroupRef gr) const;

    // Print a group's contents to an ostream.
    void listGroup(MtGroupRef obj, ostream &os) const;

    // Return the 
    MtGroupingLevel * level(int index) { 
        return levels[index]; 
    }

    /* Prepare the dynamic array holding the level for containing
        size elements */
    void prepLevelSize(int level, int size);

    // Map hierarchy level name (e.g. "RESIDUES") to level number
    bool getLevelIndex(const char *name, int &level) const;
    /** DEPRECATED. Use getLevelIx and addLevel instead */
    bool getLevelIndex(const char *name, int &level, 
                        bool append,bool caseSensitive=true);
    //     // Look for a group in all hierarchies
    //     MtGroupRef findInAllLevels(const char *name);
    // Print a levels contents to an ostream
    void listLevel(int level, ostream & os) const
    { levels[level]->list(os); }
    // Print the names of all levels to an ostream
    void listLevels(ostream &os) const;
    
    // Parse a group name (sets error_text)
    MtGroupRef parseGroup(const char *name, MtGroup * newValue = 0);
    
    // Parse a list of groups
    bool parseGroupList(const char *list_, McDArray<MtGroupRef> &T);
    //
    bool groupCmp(char* name1, char* name2) const;

    // Get the atoms that belong to a list of groups
    void getAtomsOfGroupList(const McDArray<MtGroupRef> &objlist,
                             McDArray<int> &r) const;
    
    void getAtomsOfGroupList(const McDArray<MtGroupRef> &objlist,
                             McBitfield &b) const;

    // Get the atoms that belong to a group
    void getAtomsOfGroup(const MtGroupRef &ref,McDArray<int> &r) const;
    void getAtomsOfGroup(const MtGroupRef &ref, McBitfield &b) const;

    //
    void untouch();
    
    
    void findPatternMatches(McDArray<MtGroupRef> & result,
                            const char * level, 
                            const char * attribute, 
                            const char * pattern) const; 
    void findStringMatches(McDArray<MtGroupRef> & result,
                           const char * level, 
                           const char * attribute, 
                           const char * value) const; 
    void findStringRangeMatches(McDArray<MtGroupRef> & result,
                                const char * level,
                                const char * attribute, 
                                const char * from, 
                                const char * to) const;
    //@} 
};


#include "MolTopology_inline.h"

#endif


/// @}
