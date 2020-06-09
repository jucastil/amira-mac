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
#ifndef _TAG_SomeType
#define _TAG_SomeType

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else 
#include <iostream.h>
#endif

#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <mclib/McDArray.h>
#include "ZMFWinDLLApi.h"

#include "ZMFExceptions.h"

class StreamData;
class InStreamDataFile;
class ZIBMolFileWriter;

///
class ZMF_API SomeTypeWriter : public McHandable 
{
private:
    ///
    virtual void doWrite(ZIBMolFileWriter & writer, const McDArray<int> & indexPath) = 0;

public:
    ///
    void write(ZIBMolFileWriter & zmfw, const McDArray<int> & indexPath) { 
        doWrite(zmfw, indexPath);
    }
};

/** Base type for all abstract types. */
class ZMF_API SomeType : public McHandable 
{
    ///
    virtual void doWrite(ZIBMolFileWriter & zmfw, McDArray<int> & indexPath)
    {
        assert(mWriter);
        mWriter->write(zmfw, indexPath);
    }
    
public:
    /// Constructor called from derived classes
    SomeType() : fixedSize(-1) {}

    /// Virtual destructor
    virtual ~SomeType() {}

    /// Name of the type
    virtual const char *typeName() { return "undef"; }

    /// Print a type
    void print(ostream &os,int indent = 0) { print_(os,indent); }

    /// Print a type - client function
    virtual void print_(ostream &os,int indent = 0) {}

    ///
    void write(ZIBMolFileWriter & zmfw, McDArray<int> & indexPath) {
        doWrite(zmfw, indexPath);
    }

    ///
    virtual StreamData * getStreamData(InStreamDataFile * F, long off) = 0;

    ///
    void setWriter(SomeTypeWriter * writer)
    {
        mWriter=writer;
    }
    
    /// Get entry type by index
    virtual SomeType *entryType(int i)
    { 
        throw ForkTypeExpected(typeName());
        return 0;
    }

    /// Number of fields.
    virtual int numEntries()
    { 
        throw ForkTypeExpected(typeName());
        return 0;
    }

    
protected:
    int fixedSize;

protected:
    McHandle<SomeTypeWriter> mWriter;
};

#endif

/// @}
