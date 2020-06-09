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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_DATACONTAINER_H
#define MOLCHEM_DATACONTAINER_H

#include "MolChemWinDLLApi.h"

template <class T1, class T2> class McHashTable;
template <class T> class McHandle;
class McString;

namespace molchem {

    class ChemData;

    /** \brief Container for arbitrary data

        Data-Handling is implemented via a HashTable which allows fast lookup
        of data by property name. However, setting data is expensive
        and table is memory inefficient. If using many different data items,
        try to encapsulate them.
    */

    class MOLCHEM_API DataContainer {
    public:
        /** */
        DataContainer();
        /** */
        ~DataContainer();
        /** ChemData is ref'ed. */
        void setData(const char* name, const ChemData* t);
        /** Returns data item of given name, or 0 if not found.
            You should assign it to a McHandle.
        */
        const ChemData* getData(const char* name) const;
        /** Associated ChemData is unref'ed. */
        void deleteData(const char* name);
        /** Returns number of data items. */
        int getNumData() const;
        /** Reset the internal iterator over the data items. */
        void resetDataIter();
        /** Get the next data item in regard to internal iterator. 
            Returns false if there are no more. */
        bool nextData(McString& name,McHandle<ChemData>& data);
        /** Removes all data entries */
        void clearData();
    private:
        McHashTable<McString,ChemData*>* table;
    };
}

#endif


/// @}
