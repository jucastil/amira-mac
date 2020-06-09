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
#ifndef _TAG_MtSelfSubtitutingAttribute_h_
#define _TAG_MtSelfSubtitutingAttribute_h_

#include <mclib/McHandle.h>

#include <mclib/McString.h>
#include "MoleculeWinDLLApi.h"
#include "MtGroupAttribute.h"

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::cerr;
#else 
#include <iostream.h>
#endif

///
class MOLECULE_API MtGroupAttributeProvider : virtual public McHandable
{
public:
    ///
    virtual ~MtGroupAttributeProvider() {}
    ///
    virtual MtGroupAttribute * getGroupAttribute(const char * name,
                                                 const char * internalName, 
                                                 const char * levelName,
                                                 MtIntegerAttribute * typeId) = 0;
};


///
class MOLECULE_API MtSelfSubstitutingAttribute : public MtGroupAttribute
{
    ///
    McHandle<MtGroupAttributeProvider> theProvider;

    ///
    McString iName, theLevelName;

    ///
    McHandle<MtIntegerAttribute> typeId;

public:
    ///
    MtSelfSubstitutingAttribute(const char * name, const char * internalName,
                                const char * levelName,
                                MtIntegerAttribute * tId,
                                MtGroupAttributeProvider * prov) 
        : theProvider(prov), iName(internalName), theLevelName(levelName), typeId(tId)
    { 
        setName(name);
    }

    ///
    MtGroupAttribute * clone() const { 
        return new MtSelfSubstitutingAttribute(*this); 
    }
    
    MtGroupAttribute * cloneEmpty() const { 
        return new MtSelfSubstitutingAttribute(*this); 
    }    
    ///
    MtGroupAttribute * substitute()
    { 
        return theProvider->getGroupAttribute(getName(), iName, theLevelName, typeId); 
    }
    
    /// Return the number of different attribute values
    virtual int getNumDifferentValues() const { assert(0); return 0; }
    virtual int getNumEntries() const {assert(0);return 0;}

    /// Prepare the topology for containing @c num atom types 
    virtual void remax(int n) { }
    ///
    virtual void resize(int n) {  }
    ///
    virtual void insertSpace (int before, int len) { }
    ///
    virtual void remove (int before, int len) { }
    ///
    virtual int getSize() const { assert(0); return 0; }
    /// Return the attribute index of the @c ixth entry
    virtual int getValueIxOfEntry(int entry) const { assert(0); return 0; }
    /// set the index of the value for a group
    virtual void setValueIxOfEntry(int groupIx,int valueIx) {assert(0);} 
    ///
    virtual bool hasDefaultValue(int entry) const { assert(0); return false;}
    ///
    virtual void printValueOfEntry(int entry, ostream &) const { assert(0); }
    
    /** returns all entries that have the attribute value
        value[ix] in the list entryList **/
    virtual void getEntriesOfValueIx(int ix,McDArray<int>& entryList) const
    { assert(0); }

    virtual void moveGroup(int groupIx,int newGroupIx) {assert(0);}
    ///
    virtual void printValue(int ix, ostream&) const { assert(0); }

    ///
    virtual bool match(int ix, const char * candidate) const { return false; }
    virtual void transferAttributeValue(int srcIx, MtGroupAttribute* dst, 
        int dstIx) const {assert(0);}
};

#endif

/// @}
