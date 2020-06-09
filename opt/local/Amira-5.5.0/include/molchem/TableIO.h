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
#ifndef MOLCHEM_TABLE_H
#define MOLCHEM_TABLE_H

#include "MolChemWinDLLApi.h"
#include <mclib/McDArray.h>
#include <mclib/McString.h>

class McFilename;

namespace molchem {
    
    /** \brief Reader for File-Tables
    *
    *   TableIO provides easy interface to
    *   read in configuration parameter files which 
    *   need to comply to the following file-format:
    *   - each token must be seperated by tabs ('\t')
    *   - 1. line names of the parameter columns
    *   - 2. line types of the parameter columns 
    *   (int,float,char, or string)
    *   - remainder of file: parameter columns
    */

    class MOLCHEM_API TableIO {
    public:
        ///
        TableIO();
        ///
        ~TableIO();

        /// clears Table
        void clear();

        /// returns number of columns
        int getNumColumns() const;

        /// returns number of rows
        int getNumRows() const;

        /// return type of data in column columnIx
        McPrimType getColumnType(int columnIx) const;

        /** return whether given types of columns match table.
        note: make sure to always call checkType after having called
        getColumnIx for type safety */
        bool checkType(int columnIx,const char* type) const;

        /** return whether given types of columns match table.
        note: make sure to always call checkType after having called
        getColumnIx for type safety */
        bool checkType(const McDArray<int>& columnIx,McDArray<McPrimType>& type) const;

        /** return whether given types of columns match table.
        note: make sure to always call checkType after having called
        getColumnIx for type safety */
        bool checkType(const McDArray<int>& columnIx,const char* type[]) const;

        /** will return index of column with name columnName.
        returns -1 if no such column is existant */
        int getColumnIndex(const McString& columnName) const;

        /** will return indices of columns with names columnName.
        columnIx will contain -1 for each nonexistant column.
        if there is any such row false will be returned */
        bool getColumnIndex(const McDArray<McString>& columnName,
            McDArray<int>& columnIx) const;

        /** will return indices of columns with names columnName.
        columnIx will contain -1 for each nonexistant column. 
        if there is any such row false will be returned */
        bool getColumnIndex(const char* columnName[],int numColumns,
            McDArray<int>& columnIx) const;

        /** returns data of column of index columnIx. 
        memory safe */
        void getColumn(int columnIx,McDArray<int>& columnData) const; 
        void getColumn(int columnIx,McDArray<float>& columnData) const;
        void getColumn(int columnIx,McDArray<McString>& columnData) const;
        void getColumn(int columnIx,McDArray<char>& columnData) const;

        void getParameter(int colIx, int rowIx, int& dat) const;
        void getParameter(int colIx, int rowIx, McString& dat) const;
        void getParameter(int colIx, int rowIx, char& dat) const;
        void getParameter(int colIx, int rowIx, float& dat) const;

        /**
        note: utmost care should be used when using 
        this class to build up tables via the methods
        that directly copy internal data to externally allocated memory
        as no type checking, checking of bounds etc will be done

        note: while strings are handled as simple char*
        internally they are respresented as McString objects
        externally
        */

        /** return specific table entry.
        note: pointers to chars (strings) will point to memory location under 
        managment of Table thus after destruction of Table object these pointers 
        will loose validity, you need to use MC_strdup or a McString to make it save*/
        void* getParameter(int columnIx, int rowIx,void* data) const;

        /** return data of column of index columnIx by copying data 
        to @c data. data has to point ot allocated memory of size 
        getColumnSize(columnIx)*byte 
        note: copied pointers to chars (strings) will point to memory location under 
        managment of Table thus after destruction of Table object these pointers 
        will loose validity, you need to use MC_strdup or a McString to make it safe*/

        void* getColumn(int columnIx,void* dat) const;

        /** methods that return memory size needed to externally store table data
        (size of any char* will be replaced by size of McString) */

        /// return memory (in bytes) needed to save data of column @c columnIx
        int getColumnSize(int columnIx) const;

        /// returns name of the column
        const char* getColumnName(int columnIx) const { return columnName[columnIx].getString();}

        /** stream io methods */

        /// print table to stream
        void print(ostream& os) const;

        /// print parameter defined by columnIx,rowIx to stream os
        void printParameter(int columnIx, int rowIx, ostream& os) const; 

        /** will read parameter table from file filename */
        void read(const McFilename& filename);

    private:
        McDArray<McDArray<char> > data;
        McDArray<McString> columnName;
        McDArray<McPrimType> columnType;
    };
}

#endif


/// @}
