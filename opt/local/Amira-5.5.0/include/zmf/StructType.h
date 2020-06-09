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

/// @addtogroup zmf zmf
/// @{
#ifndef _TAG_StructType_h
#define _TAG_StructType_h

#include "ZMFWinDLLApi.h"
#include "ForkType.h"

/** Structure type. */
class ZMF_API StructType : public ForkType {
public:
    ///
    StructType();

    ///
    ~StructType();

    const char *typeName() { return "struct"; }

    /// Number of fields.
    int numEntries() { return fields.size(); }

    /// Get field by index
    SomeType *entryType(int i) { 
        return fields[i].typ; 
    }
    
    ///
    SomeType * lastEntryType() {
        return fields.last().typ;
    }

    ///
    void setEntryType(int i, SomeType *typ);

    /// Get name of field with index @c i
    const char *entryName(int i) { 
        return fields[i].name; 
    }

    /// True if @c fieldname is in structure
    bool hasEntry(const char *fieldname);

    ///
    bool isOptional(int i) const { return fields[i].optional; }

    /// Index of field names @c fieldname
    int getEntryIndex(const char *fieldname);

    /// Get field by name
    SomeType *getEntryByName(const char *fieldname);

    /// Add a field
    int addEntry(const char *fieldname,SomeType *typ, bool isOptional=false);

    ///
    void print_(ostream &os,int indent = 0);

    ///
    StreamData * getStreamData(InStreamDataFile * F, long off);

private:
    ///
    virtual void doWrite(ZIBMolFileWriter & writer, McDArray<int> & indexPath);

    typedef struct {
        McString name;
        McHandle<SomeType> typ;
        bool optional;
    } FieldDesc;
    McDArray<FieldDesc> fields;
};

#endif

/// @}
