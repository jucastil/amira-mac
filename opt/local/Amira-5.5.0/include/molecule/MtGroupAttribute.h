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
#ifndef _TAG_MtGroupAttribute_h_
#define _TAG_MtGroupAttribute_h_

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
#else
#include <iostream.h>
#endif

#include "MoleculeWinDLLApi.h"
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>

class MtGroupRefTranslator;
class MtIndexAttribute;
class MtFloatAttribute;
class MtStringAttribute;
class MtIntegerAttribute;

// ------------------------------------------------------------
//
//               MtGroupAttribute
//
// ------------------------------------------------------------

///
class MOLECULE_API MtGroupAttribute : public McHandable
{
    friend class MtGroupingLevel;
    friend class MolTopology;
    friend class Molecule;
public:

    /// Get the name of the attribute
    const char* getName() const;

    /// return the number of entries (groups)
    virtual int getNumEntries() const = 0;

    /// Return the number of different attribute values
    virtual int getNumDifferentValues() const = 0;

    /***********************************************************
                     Accessing Values
     ***********************************************************/

    /// Return the attribute index of the @c ixth entry
    virtual int getValueIxOfEntry(int entry) const = 0;
    
    ///
    virtual bool hasDefaultValue(int entry) const = 0;

    /** returns all entries that have the attribute value
        value[ix] in the list entryList **/
    virtual void getEntriesOfValueIx(int valueIx,McDArray<int>& entryList) const = 0;

    /***********************************************************
                     Misc
     ***********************************************************/

    /// Print a value
    virtual void printValue(int valueIx, ostream&) const = 0;

    /// Print the value of an entry
    virtual void printValueOfEntry(int entry, ostream &) const = 0;

    /// Return whether an entry matches the value given in a string
    virtual bool match(int entryIx, const char * candidate) const = 0;

    /// if group of index groupIx was moved to newGroupIx, updates attributes in this range
    virtual void moveGroup(int groupIx,int newGroupIx) =0;


//###private

    /// Constructor
    MtGroupAttribute();

    /// Copy Constructor
    MtGroupAttribute(const MtGroupAttribute & ga);

    /// Duplicate this attribute incl. all data
    virtual MtGroupAttribute * clone() const = 0;

    /// Duplicate this attribute without data
    virtual MtGroupAttribute * cloneEmpty() const = 0;

    /// Destructor
    virtual ~MtGroupAttribute();
    /// Prepare the topology for containing @c num atom types 
    virtual void remax(int n)=0;
    
    ///
    virtual void resize(int n)=0;
    
    /// inserts @c len default values ahead of index @c before
    virtual void insertSpace(int before,int len=1)=0;
    
    /// removes @c len entries starting at position @c pos 
    virtual void remove(int pos, int len=1)=0;

    void setName(const char* name);
    ///
    virtual void transferAttribute(MtGroupRefTranslator * t, 
                                   int lIx, int N, int * sizes, 
                                   McDArray<MtGroupAttribute*>&) const;
    
    ///
    virtual void transferAttributeValue(int srcIx, MtGroupAttribute* dst, 
                                        int dstIx) const = 0 ;

protected:

    char * theName;


};

// ------------------------------------------------------------
//
//               MtIntegerAttribute
//
// ------------------------------------------------------------

///
class MOLECULE_API MtIntegerAttribute : public MtGroupAttribute
{
    friend class MtGroupingLevel;
    friend class MolTopology;
    friend class Molecule;
    
public:

    /// Return the number of different attribute values
    int getNumDifferentValues() const;
    
    ///
    int getNumEntries() const;

    /***********************************************************
                     Accessing Values
     ***********************************************************/

    /// Return the value of an entry
    int getValue(int entryIx) const;

    /// Set the value of an entry
    void setValue(int entryIx, int value);

    /// Return the minimum and maximum values
    void getMinMax(int & min, int & max) const;

    /// Find the index of a value
    int findValueIx(int value) const; 

    /// Return a value
    int getValueByIx(int ix) const;

    /// returns a list of all entries that index a certain value
    void getEntriesOfValueIx(int valueIx,McDArray<int>& entryList) const;

    /// returns first entry that has a certain value, -1 if none
    int getFirstEntryOfValue(int value) const;

    /// Return the index of the value indexed by an entry
    int getValueIxOfEntry(int entryIx) const;

    /// Returns whether value of entry has already been set
    bool hasDefaultValue(int entryIx) const;

    /***********************************************************
                     Misc
     ***********************************************************/

    /// Print Value of an entry
    void printValueOfEntry(int entry, ostream&) const;
    
    /// Print Value
    void printValue(int ix, ostream&) const;
    
    /// Return whether an entry matches the value given as a string
    bool match(int entryIx, const char * candidate) const;

    virtual void moveGroup(int groupIx,int newGroupIx);
//###private

    /// Prepare the topology for containing @c num atom types 
    void remax(int n);
    ///
    void resize(int n);
    /// inserts @c len default values ahead of index @c before
    void insertSpace(int before,int len=1);
    /// removes @c len entries starting at position @c pos 
    void remove(int pos, int len=1);
    ///
    void transferAttributeValue(int srcIx, MtGroupAttribute* dst, 
                                int dstIx) const;
    ///
    MtIntegerAttribute(int defaultValue = 0);    
    ///
    MtGroupAttribute * clone() const;
    ///
    MtGroupAttribute * cloneEmpty() const;    
    
    void setValues(const McDArray<int>& value);
    void getValues(McDArray<int>& value) const;
private:
    ///
    McDArray<int> values;
    ///
    McDArray<int> entries;
    
    ///
    int theDefaultValue;
    
    /// 
    int theMinValue, theMaxValue;


};


// ------------------------------------------------------------
//
//               MtFloatAttribute
//
// ------------------------------------------------------------

///
class MOLECULE_API MtFloatAttribute : public MtGroupAttribute
{
    friend class MtGroupingLevel;
    friend class MolTopology;
    friend class Molecule;

public:

    int getNumDifferentValues() const;

    int getNumEntries() const;

    /***********************************************************
                     Accessing Values
     ***********************************************************/
    ///
    float getValue(int entryIx) const;

    ///
    void setValue(int entryIx, float valueIx);
    
    ///
    void getMinMax(float & min, float & max) const;
    
    ///
    float getValueByIx(int valueIx) const;

    /// 
    int findValueIx(float name) const; 
    
    ///
    void getEntriesOfValueIx(int ix,McDArray<int>& entryList) const;
    
    ///
    int getValueIxOfEntry(int entry) const;

    ///
    bool hasDefaultValue(int entry) const;
    /// returns first entry that has a certain value, -1 if none
    int getFirstEntryOfValue(float value) const;

    /***********************************************************
                     Accessing Values
     ***********************************************************/

    ///
    void printValueOfEntry(int entry, ostream &) const;
    ///
    void printValue(int entry, ostream &) const;
    ///
    bool match(int ix, const char * candidate) const;

    virtual void moveGroup(int groupIx, int newGroupIx);
    
    
//###private
    ///
    void transferAttributeValue(int srcIx, MtGroupAttribute* dst, 
                                int dstIx) const;

    /// Prepare the topology for containing @c num atom types 
    virtual void remax(int n);
    ///
    virtual void resize(int n);
    /// inserts @c len default values ahead of index @c before
    virtual void insertSpace(int before,int len=1);
    /// removes @c len entries starting at position @c pos 
    virtual void remove(int pos, int len=1);
    /// Return the attribute index of the @c ixth entry

    ///
    MtFloatAttribute(float defaultValue=0.0);
    ///
    MtGroupAttribute * clone() const;
    
    ///
    MtGroupAttribute * cloneEmpty() const;

    void setValues(const McDArray<float>& value);
    void getValues(McDArray<float>& value) const;
private:
    
    ///
    McDArray<float> values;

    ///
    McDArray<int> entries;
    
    ///
    float theDefaultValue;
    
    ///
    float theMinValue, theMaxValue;

};

// ------------------------------------------------------------
//
//               MtStringAttribute
//
// ------------------------------------------------------------


///
class MOLECULE_API MtStringAttribute : public MtGroupAttribute
{
    friend class MtGroupingLevel;
    friend class MolTopology;
    friend class Molecule;

public:
    /// Return the number of different attribute values
    int getNumDifferentValues() const;

    int getNumEntries() const;

    /***********************************************************
                     Accessing Values
     ***********************************************************/


    ///
    void setValue(int entry, const char * value);
    
    ///
    const char * getValue(int entry) const;

    ///
    const char * getValueByIx(int valueIx) const;
    
    /// Find the index of a @c named attribute value
    int findValueIx(const char * value) const; 
    ///
    int getValueIxOfEntry(int entry) const;
    ///
    void getEntriesOfValueIx(int valueIx,McDArray<int>& entryList) const;
    ///
    bool hasDefaultValue(int entry) const;
    ///
    void printValueOfEntry(int entry, ostream&) const;
    /// returns first entry that has a certain value, -1 if none
    int getFirstEntryOfValue(const char* value) const;


    /***********************************************************
                     Misc
     ***********************************************************/

    ///
    void printValue(int valueIx, ostream&) const;
    ///
    bool match(int ix, const char * candidate) const;

    ///
    bool matchWildcard(int ix, const char * pattern) const;
    
    virtual void moveGroup(int groupIx,int newGroupIx);
//###private

    /// Prepare the topology for containing @c num atom types 
    void remax(int n);
    ///
    void resize(int n);
    /// inserts @c len default values ahead of index @c before
    void insertSpace(int before,int len=1);
    /// removes @c len entries starting at position @c pos 
    void remove(int pos, int len=1);

    ///
    void transferAttributeValue(int srcIx, MtGroupAttribute* dst, 
                                int dstIx) const;

    ///
    MtStringAttribute(const char * defaultValue="");
    
    ///
    MtStringAttribute(const MtStringAttribute & a);
    
    ///
    ~MtStringAttribute();
    ///
    MtGroupAttribute * clone() const;
    ///
    MtGroupAttribute * cloneEmpty() const;

    void setValues(const McDArray<const char*>& value);
    void getValues(McDArray<const char*>& value) const;
private:
    

    static bool _match(const char * pattern, const char * string);
    ///
    McDArray<const char *> values;
    
    ///
    McDArray<int> entries;

    ///
    char * theDefaultValue;

};

// ------------------------------------------------------------
//
//               MtIndexAttribute
//
// ------------------------------------------------------------

///
class MOLECULE_API MtIndexAttribute : public MtGroupAttribute
{
    friend class MtGroupingLevel;
    friend class MolTopology;
    friend class Molecule;

public:
    /// Return the number of different attribute values
    int getNumDifferentValues() const;
    
    ///
    int getNumEntries() const;

    /***********************************************************
                     Accessing Values
     ***********************************************************/

    ///
    int getValue(int entryIx) const;

    ///
    int getValueByIx(int valueIx) const;
    
    void getEntriesOfValueIx(int ix,McDArray<int>& entryList) const;
    
    int getValueIxOfEntry(int entryIx) const;
    ///
    bool hasDefaultValue(int entryIx) const;

    /***********************************************************
                     Misc
     ***********************************************************/

    ///
    void printValueOfEntry(int entry, ostream & os) const;
    ///
    void printValue(int valueIx, ostream & os) const;

    bool match(int ix, const char * candidate) const;

    virtual void moveGroup(int groupIx,int newGroupIx) {}
//###private

    /// Prepare the topology for containing @c num atom types 
    void remax(int n);
    ///
    void resize(int n);
    /// inserts @c len default values ahead of index @c before
    void insertSpace(int before,int len=1);
    /// removes @c len entries starting at position @c pos 
    void remove(int pos, int len=1);
    /// Return the attribute index of the @c ixth entry
    MtIndexAttribute();
    
    ///
    MtGroupAttribute * clone() const;
    
    ///
    MtGroupAttribute * cloneEmpty() const;
    int theSize;
    ///
    void transferAttributeValue(int srcIx, MtGroupAttribute* dst, 
                                int dstIx) const;
    ///


private:


};
    

#endif

/// @}
