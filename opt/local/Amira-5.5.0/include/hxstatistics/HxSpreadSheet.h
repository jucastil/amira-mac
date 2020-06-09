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

/// @addtogroup hxstatistics hxstatistics
/// @{
#ifndef HX_SPREADSHEET_H
#define HX_SPREADSHEET_H

#include <mclib/McVec3f.h>
#include <hxcore/HxData.h>
#include <hxcore/HxPortButtonList.h>
#include <hxstatistics/HxStatisticsWinDLLApi.h>

class AmiraMesh;

class QxSpreadSheetDialog;

template<class T>
class QPointer;

typedef QPointer<QxSpreadSheetDialog> QxSpreadSheetDialogPtr;

/** This data class represents a simple spreadsheet containing an
    arbitrary number of tables where each table contains an arbitrary number columns.
    Each column can contain data of type float, int or string.
    Additionally a built-in spreadsheet viewer is provided.
*/
class HXSTATISTICS_API HxSpreadSheet : public HxData {

  HX_HEADER(HxSpreadSheet);

  public:

    /// Auxiliary class representing a single data column.
    struct HXSTATISTICS_API Column {
        /// The column's data type.
        enum DataType {
            /// Values are strings
            STRING =0,
            /// Values are floating point numbers
            FLOAT  =1,
            /// 
            INT    =2
        };

        /// Default constructor.
        Column();

        /// Copy constructor.
        Column(const Column& other) {
            type = other.type;
            name = other.name;
            sval = other.sval;
            fval = other.fval;
            ival = other.ival;
            format = other.format;
        }

        /// Constructor.
        Column(const char* name, int type, int nRows=0);

        /// Assignment operator.
        Column& operator=(const Column& other) {
            type = other.type;
            name = other.name;
            sval = other.sval;
            fval = other.fval;
            ival = other.ival;
            format = other.format;
            return *this;
        }

        /// Can be used to access int values.
        int& intValue(int index) { return ival[index]; }
        const int intValue(int index) const { return ival[index]; }

        /// Can be used to access float values.
        float& floatValue(int index) { return fval[index]; }
        const float floatValue(int index) const { return fval[index]; }

        /// Can be used to access string values.
        McString& stringValue(int index) { return sval[index]; }
        McString stringValue(int index) const { return sval[index]; }

        /// Returns number of elements of column, i.e., number of rows.
        int size() const;

        /// Adjusts number of rows.
        void resize(int n);

        /// Set a string value, uses atof() if data type isn't STRING.
        void setValue(int index, const char* value);

        /// Set a float value, uses sprintf() if data type isn't FLOAT.
        void setValue(int index, float value);

        void setValueInt(int index, int value);

        /// Returns the width of the column in characters.
        int getWidth() const;

        /// Valid only for string type columns
        int findRow(const char* value) const;

        /// Prints j-th element into a string.
        void print(int j, McString& s) const;

        /// Tries to automatically find a suitable format string.
        void autoFormat();

        /// The name of the data column.
        McString name;

        /// The columns tooltip
        McString toolTip;

        /// Stores the column's data type (0=STRING, 1=FLOAT, 2=INT).
        int type;

        /// printf-style format string used for FLOAT values, default is "%.9g".
        McString format;

        /// Internal array for STRING-type elements.
        McDArray<McString> sval;

        /// Internal array for FLOAT-type elements.
        McDArray<float> fval;

        /// Internal array for INT-type elements.
        McDArray<int> ival;
    };

private:
    /// helper class representing a table
    struct HXSTATISTICS_API Table : public McHandable {
        /// Default constructor.
        Table() {
            name    = "Table1";
            numRows = 0;
        }

        /// Copy constructor.
        Table(const Table& other) {
            name     = other.name;
            numRows  = other.numRows;
            tColumns = other.tColumns;
        }

        /// Constructor.
        Table(const char* inName) {
            name    = inName;
            numRows = 0;
        }

        ~Table() {}

        /// Assignment operator.
        Table& operator=(const Table& other) {
            name     = other.name;
            tColumns = other.tColumns;
            numRows  = other.numRows;
            return *this;
        }

        /// the table columns
        McDArray<Column> tColumns;

        /// the table name
        McString name;

        /// number of rows per table
        int numRows;
    };

public:

    /// Default constructor.
    HxSpreadSheet();

    /// Destructor.
    ~HxSpreadSheet();

    HxSpreadSheet* duplicate() const;

    /// Update method checks show button.
    void update();

    /// Prints number of columns and rows.
    void info();

    /// Calls autoFormat() for every column.
    void autoFormat(int table=0);

    /// Provides button for activating the text viewer.
    HxPortButtonList portShow;

    /// Comma separated value output using the given separator.
    int saveCsv(const char* filename,char separator=',');

    /// Comma separated value output using commas.
    int saveCsvComma(const char* filename);

    /// Comma separated value output using semicolons.
    int saveCsvSemicolon(const char* filename);

    /// Comma separated value output using tabulators.
    int saveCsvTabulator(const char* filename);

    /// Text output including a table with row and column delimiters.
    int saveText(const char* filename);

    /// Microsoft XML Spreadsheet 2003 output.
    int saveXml(const char* filename);

    /// AmiraMesh ascii output (default output method).
    int saveAmiraMeshAscii(const char* filename);

    /// AmiraMesh binary output.
    int saveAmiraMeshBinary(const char* filename);

    /// Actual AmiraMesh export (ascii or binary).
    int saveAmiraMesh(const char* filename, int ascii);

    /// AmiraMesh reader
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Prints whole spreadsheet into character string.
    void print(McString& text, int table=0) const;

    /// sets number of rows \a n for table \a table
    /// concerns all future columns to be added to this table \a table
    /// returns false if table doesn't exist
    bool setNumRows(int n, int table=0);

    /// dims of table \a table
    /// returns 0 if table \a table doesn't exist
    int nRows(int table=0) const;
    int nCols(int table=0) const;

    /// adds a column with name \a name and type \a type to table \a table
    /// the column row size will be set to the current value of nRows(table)
    /// returns false if the column couldn't be added e.g. the table index 
    /// \a table is out of range.
    ///
    /// Nevertheless if a column with name \a name already exists a
    /// new column with the same name \a name will be added. It is highly
    /// recommended to use unique column names, otherwise @see removeColumn
    /// and @see findColumn will remove or return the first column with
    /// a matching name \a name 
    bool addColumn(const char* name, int type, int table=0);

    /// removes first column matching name \a name and type \a type of table \a table
    /// returns false if column or table doesn't exist
    bool removeColumn(const char* name, int type, int table=0);

    /// remove column with index \a icol of table \a table
    /// returns false if column or table doesn't exist
    bool removeColumn(int icol, int table=0);

    /// returns idx of first column matching name \a name and type \a type of table \a table
    /// returns -1 if column matching \a name and \a type could not be found
    int findColumn(const char* name, int type, int table=0) const;

    /// returns pointer to column struct or NULL if column \a icol
    /// or table \a table do not exist
    Column* column(int icol, int table=0);

    const Column* column(int icol, int table=0) const;

    /// adds a table with name \a name
    /// returns false if table couldn't be added
    bool addTable(const char* name);

    /// remove table with name \a name
    /// returns false if table doesn't exist
    /// Note: the table with the name \a name with refers to index 0 cannot be removed
    /// because of the reference to tables[0]->columns which is needed
    /// for legacy reasons
    bool removeTable(const char* name);

    /// remove table with index \a iTable
    /// returns false if table doesn't exist
    /// Note: the table with index \a iTable == 0 cannot be removed
    /// because of the reference to tables[0]->columns which is needed
    /// for legacy reasons
    bool removeTable(int iTable);

    /// removes all columns of table \a name
    /// resets numRows of table \a name
    /// returns false if table could not be found
    bool clearTable(const char* name);

    /// removes all columns of table with index \a iTable
    /// resets numRows of table with index \a iTable
    /// returns false if table could not be found
    bool clearTable(int iTable);

    /// returns idx of table with name \a name
    /// or -1 if table couldn't be found
    int findTable(const char* name) const;

    /// returns number of tables 
    int nTables() const { return tables.size(); }

    /// returns table name or null if table doesn't exist
    const char* getTableName(int iTable=0) const;
    bool setTableName(const char* name, int table=0);

    /// removes all tables
    /// Note: the first table cannot be removed
    /// because of the reference to tables[0]->columns which is needed
    /// for legacy reasons
    void clear();

    /// tcl interface
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Get values of three columns as vector
    /// returns empty result if table \a table does not exist or the column size of 
    /// \a table does not match c1, c2,c3
    void getValues(McDArray<McVec3f>& result, int c1, int c2, int c3, int table=0) const;

    QxSpreadSheetDialog* getDialog();

private:

    static int readAmiraMeshLegacy(AmiraMesh* m, const char* filename);
    QxSpreadSheetDialogPtr* mDialogPtr;
    static char decimalPoint;

    McDArray< McHandle<Table> > tables;
    
    /// defaultTable has to be declared before columns (see below)
    /// because it needs to be initialized first via the constructor
    /// initialization list in order to set the columns reference member to it.
    McHandle<Table> defaultTable;

public:

    /// NOTE: do not access public member \a columns directly
    /// use column(...) instead
    McDArray<Column>& columns;

};

#endif

/// @}
