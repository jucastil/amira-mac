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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef MC_TABLE_H
#define MC_TABLE_H

#include <mclib/McDArray.h>
#include <mclib/McString.h>

#include <memory.h>

#ifdef HX_OS_WIN
// workaround. see http://support.microsoft.com/default.aspx?scid=kb%3Ben-us%3B309801
//
// Visual Studio .NET automatically exports the appropriate template instantiation 
// for the template class that you derive from. However, when you import the class, 
// Visual Studio .NET sometimes does not correctly import that instantiation.
//
// McString instanciates McDArray<char> and therefore this instanciation is exported
// by mclib.
template class __declspec(dllimport) McDArray<char>;
#endif // HX_OS_WIN


// toggle debug stuff
#ifdef NDEBUG
    #define CMT2_INSERTTABLEID      0
    #define CMT2_CHECK_ALWAYS       0
    #define CMT2_CHECK_ROWPOINTERS  0
    #define CMT2_CHECK_ASSERT       0
#else
    #define CMT2_INSERTTABLEID      0
    #define CMT2_CHECK_ALWAYS       0
    #define CMT2_CHECK_ROWPOINTERS  0
    #define CMT2_CHECK_ASSERT       0
#endif

#define CMT2_MAX_COLUMNS   16
#define CMT2_MAX_COLUMN_ID 16
#define CMT2_MAX_ROW_WITH  512


#define CMT2_ID_DEL_FLAG             0
#define CMT2_ID_TABLEID              1

#if CMT2_INSERTTABLEID
#define CMT2_ID_OFF                  2
#else
#define CMT2_ID_OFF                  1
#endif



#if CMT2_CHECK_ROWPOINTERS
    #ifdef NDEBUG
        #define CMT2CHECK_PTR(EXP) do{ if (!(EXP)){fprintf(stderr,"CMT2CHECK failed in %s line %d: [%s]\n", __FILE__, __LINE__, #EXP);} }while(0)
    #else
        #define CMT2CHECK_PTR(EXP) assert(EXP)
    #endif
#else
    #define CMT2CHECK_PTR(EXP) ((void)0)
#endif


#if CMT2_CHECK_ASSERT
    #ifdef NDEBUG
        #define CMT2ASSERT(EXP) do{ if (!(EXP)){fprintf(stderr,"CMT2ASSERT failed in %s line %d: [%s]\n", __FILE__, __LINE__, #EXP);assert(0);} }while(0)
    #else
        #define CMT2ASSERT(EXP) assert(EXP)
    #endif
#else
    #define CMT2ASSERT(EXP) ((void)0)
#endif


class McTable;


////////////////////////////////////////////////////////////////////////////////
class McDataBase
{
    friend class McTable;

public:

    McDataBase();
    ~McDataBase();


    McTable * table( int inTableID );

    int createTable();

    bool check();

    int numTables();

    void clone( McDataBase & outDB );

    // debug stuff
    void skipCheck();
    void unskipCheck();

private:

    McDArray<McTable*>  mTables;
    int                 mTableIdNext;

    // debug stuff
    int                 mSkipCheckCount;
};


////////////////////////////////////////////////////////////////////////////////
class McTable
{
    friend class McDataBase;

public:

    enum ColumnType
    {
        T_Data,
        T_1to1,
        T_1toN
    };


private:

     McTable( int inTableID, McDataBase * inDataBase );

    ~McTable();


public:

    /** Returns the ID of that table. This id is unique for all tables of the same McDataBase.
        \return 
                Unique table ID.
    */
    int id();


    char * name();

    void setName( char * inName );

    /** Delete all rows.
    */
    void clear();

    /** set.
    */
    void clone( McTable & outTable );

    /** Append a new row to the table. If there is not enough space for the row
        in the row data array this array is expanded. If this happens, the rows 
        of that table move and relation pointers with this table as target change. 
        Algorithms using the table must take care of this. To append an amount of 
        rows without auto-expansion one should invoke rowReserve() before.
        \return 
                Pointer to the appended row.
    */
    char * rowAdd();

    /** Make sure that there is enough space in the table to add a specific number
        of rows to the table without auto-expansion.
        \param  inRowCount
                Number of rows that should be enough space for.
        \return 
                Fields offset from the begin of a row in bytes.
    */
    int rowReserve( int inRowCount );

    /** Delete a row. The row actually gets marked as deleted and added to a free-list.
        \param  inRow
                Pointer to the row to be deleted.
    */
    void rowDelete( char * inRow );

//    void      rowDeleteUnlinked( McTable & linkTab );


    /** Get number of bytes per row.
        \return 
                Number of bytes per row.
    */
    int rowWidth();

    /** Get number of rows including deleted rows.
        \return 
                Number of rows.
    */
    int rowAllCount();

    /** Get number of deleted rows that are still allocated.
        \return 
                Number of rows.
    */
    int rowFreeCount();

    /** Get number of rows that are allocated and not marked as deleted.
        \return 
                Number of rows.
    */
    int rowUsedCount();

    /** Set number of rows that should fit into the initially allocated
        data array.
        \param  inRowCount
                Number rows for that initially is memory allocated for.
    */
    void rowSetInitialSpace( int inRowCount );


    ////////////////////////////////////////////////////////////
    // Column stuff
    ////////////////////////////////////////////////////////////

    /** Append a new field or column to the table. Existing rows are enlarged.
        \param  inColId
                ID of the column. If the column with that ID was already added, 
                the method doesn't change the table.
        \param  inType
                Type of the column.
        \param  inWidth
                Width of this column in bytes.
        \param  inTargetId
                In case of a relation field (T_1to1 or T_1toN), this is the ID of the target 
                table.
        \return 
                Fields offset from the beginning of a row in bytes.
    */
    int columnAdd( int inColId, ColumnType inType, int inWidth, McTable * inTarget = 0 );

    /** Get columns offset from the beginning of each row.
        \param  inColId
                ID of the column.
        \return 
                Fields offset from the begin of a row in bytes or -1 if table has no 
                column of that ID.
    */
    int columnIdToOffset( int inColId );

    /** Get columns zero based field index from its offset from the beginning of each row.
        \param  inColOffset
                Row offset of the column.
        \return 
                Fields zero based index or -1 if table has no column with that offset.
    */
    int columnOffsetToIndex( int inColOffset );

    /** Set target table for a particular relation-column.
        \param  inColId
                ID of the relation column.
        \param  inTargetTableId
                The target table.
    */
    void columnSetTarget( int inColId, McTable * inTargetTable );

    /** Get the target table of a relation-column.
        \param  inColId
                ID of the column.
        \return 
                Target table.
    */
    McTable * columnTarget( int inColId );


    ////////////////////////////////////////////////////////////
    // Relations stuff
    ////////////////////////////////////////////////////////////

    /** Add a relation to the relation-field of a row of this table to another row of the 
        relation-columns target table.
        \param  inRowSrc
                Pointer to the source row a new relation is added to.
        \param  inColOff
                Byte offset of the relation-column the relation is added to (offset from rows head).
        \param  inRowDst
                Pointer to the destination row of the relation-columns target table.
    */
    void relationAdd( char * inRowSrc, int inColOff, char * inRowDst );

    /** internal helper */
    void relationDelInternal( char * inRowSrc, int inColOff, char *** ppC );


    /** Delete a relation from the relation-field of a row of this table to another row of the 
        relation-columns target table.
        \param  inRowSrc
                Pointer to the source row a new relation is removed from.
        \param  inColOff
                Byte offset of the relation-column the relation is removed from (offset from rows head).
        \param  inRowDst
                Pointer to the destination row of the relation-columns target table.
    */
    void relationDel( char * inRowSrc, int inColOff, char * inRowDst );

    /** Remove all relations from the relation-field of a row of this table.
        \param  inRowSrc
                Pointer to the source row all relations are removed from.
        \param  inColOff
                Byte offset of the relation-column all relations are removed from (offset from rows head).
    */
    void relationRemoveAll( char * inRowSrc, int inColOff );

    /** Get number of relations of a rows relation-field.
        \param  inRowSrc
                Pointer to the source row all relations counted from.
        \param  inColOff
                Byte offset of the relation-column all relations are counted from (offset from rows head).
        \return 
                Number of relations of the addressed relation-field.
    */
    int relationGetCount( char * inRowSrc, int inColOff );

    /** Check if there are relations or not ( less expensive that relationGetCount() )
        \param  inRowSrc
                Pointer to the source row that the relations are checked of.
        \param  inColOff
                Byte offset of the relation-column (offset from rows head).
        \return 
                TRUE, if there is at least one relationship, FALSE else.
    */
    bool relationEmpty( char * inRowSrc, int inColOff );

    /** Repair relations of all tables that point to this table after
        the rows of this table have changed their positions due to
        auto-expansion of the data array. 
    */
    void relationsRepair();

    /** Expand relation array of a column of type 1:N-relation.
        \param  inMaxRelCount
                Number of relations the new array should be able to hold.
        \param  inColOffset
                Byte offset of the relation-column (offset from rows head).
        \param  ioRelArray
                Relation array that gets expanded.
    */
    void relationExpand( int inMaxRelCount, int inColOffset, McDArray<char*> * ioRelArray );

    /** Expand relation array of a column of type 1:N-relation.
        \param  inRelCount
                Number of relations that should be appendable without 
                auto-growing of the relations array.
        \param  inColOffset
                Byte offset of the relation-column (offset from rows head).
    */
    void relationReserve( int inRelCount, int inColOffset );

    /** Get pointer to the first row.
        \return 
                Pointer to the first row. Zero if there are no rows.
    */
    char * data();

    /** Get pointer to the last row.
        \return 
                Pointer to the last row. Zero if there are no rows.
    */
    char * last();

    /** Expand row-data array that it can hold the specified number of rows.
        \param  inMaxRowCount
                Number of rows that the target array can hold.
        \param  inOffset
                Byte offset between the rows in the new array. 
                (End of a row to the begin of the next)
        \return 
                Byte offset between the old and the new position of the 
                first row in memory.
    */
    int expand( int inMaxRowCount, int inOffset = 0 );


    ////////////////////////////////////////////////////////////
    // observed pointers stuff
    ////////////////////////////////////////////////////////////

    void      pointerObserve( char ** ptr );
    void      pointerIgnore( char ** ptr );
    bool      pointerIsObserved( char ** ptr );
    int       pointerCount( );


    ////////////////////////////////////////////////////////////
    // debugging stuff
    ////////////////////////////////////////////////////////////

    /** Check integrity of the table.
        \return FALSE, if the table is damaged.
    */
    bool check();

    /** Check if a given pointer is a valis row pointer for that table.
        \param  inRow
                Potentially row pointer.
        \return 
                FALSE if inRow is nonzero and not a valid row pointer. 
    */
    bool checkRowPointer( char * inRow );
    

    void lockRows();
    void unlockRows();
    void lockRelation( int inRelFieldOffset );
    void unlockRelation( int inRelFieldOffset );
    
    void skipCheck();
    void unskipCheck();

    /** Check 1:N relation field
    \param  row
            Pointer to the source row
    \param  offset
            Byte offset of the relation-column
    \param  targetTable
            target table of the relation
    \param  nListIn
            Start of the valid range into the ColNList (1:N pointer chain table)
    \param  nListOut
            End of the valid range into the ColNList (1:N pointer chain table)
    \return 
            TRUE if relations are valid
    */
    static bool checkRelations( char * row, int offset, McTable * targetTable, char * nListIn, char * nListOut );


//private:
public:

    McDataBase                        * mDataBase;

    // table ID    
    int                                 mTableId;

    // name
    McString                            mTableName;

    // column data
    int                                 mColCount;
    ColumnType                          mColType      [CMT2_MAX_COLUMNS];  // column type
    int                                 mColWidth     [CMT2_MAX_COLUMNS];  // width of the column in bytes 
    int                                 mColOffset    [CMT2_MAX_COLUMNS];  // byte offset from record start
    McTable                           * mColTarget    [CMT2_MAX_COLUMNS];  // target table for relation columns

    // initial count of rows to have space for without growing
    int                                 mRowSpaceInitial;
    // with of the whole row
    int                                 mRowWidth;
    // column-id to column-index
    int                                 mColIdToColIdx  [CMT2_MAX_COLUMN_ID];
    // column-id to column-offset
    int                                 mColIdToColOff  [CMT2_MAX_COLUMN_ID];

    // 1:n relations
    McDArray<char*>                   * mColNList     [CMT2_MAX_ROW_WITH];  // arrays that store pointers for 1:N relations
    char                             ** mColNData     [CMT2_MAX_ROW_WITH];
    McDArray<char*>                   * mColNFreeList [CMT2_MAX_ROW_WITH];

    // row data
    McDArray<char>                      mRowData;       // holds all the user data
    char                              * mRowDataP;
    McDArray<char*>                     mRowFreeList;   // holds free rows

    // watched pointers
    McDArray<char**>                    mPointers;


    ////////////////////////////////////////
    // debug stuff
    ////////////////////////////////////////
    int                                 mSkipCheckCount;
    int                                 mColLockCount [CMT2_MAX_COLUMNS];  //
    int                                 mLockRowCount;
};

#define CMT2_ID( pointerToRow ) (*(int*)((pointerToRow)+(sizeof(int))))


#define CMT2_INT_SET( pointerToRow, columnOffset, value ) (*(int*)((pointerToRow)+(columnOffset)) = (value))
#define CMT2_INT_GET( pointerToRow, columnOffset )                (*(int*)((pointerToRow)+(columnOffset)))
#define CMT2_1to1_SET( pointerToRow, columnOffset, targetAddress ) (*(char**)((pointerToRow)+(columnOffset)) = (targetAddress))
#define CMT2_1to1_GET( pointerToRow, columnOffset )                (*(char**)((pointerToRow)+(columnOffset)))
#define CMT2_ROW_DELETED( pointerToRow ) (*(int*)(pointerToRow)!=0)
#define CMT2_1toN_SWAP( pointerToRow0, pointerToRow1, columnOffset)                                                     \
{                                                                                                                       \
    char * tmp = *(char**)((pointerToRow0)+(columnOffset));                                                             \
    *(char**)((pointerToRow0)+(columnOffset)) = *(char**)((pointerToRow1)+(columnOffset));                              \
    *(char**)((pointerToRow1)+(columnOffset)) = tmp;                                                                    \
    tmp = *(char**)((pointerToRow0)+(columnOffset)+sizeof(char*));                                                      \
    *(char**)((pointerToRow0)+(columnOffset)+sizeof(char*)) = *(char**)((pointerToRow1)+(columnOffset)+sizeof(char*));  \
    *(char**)((pointerToRow1)+(columnOffset)+sizeof(char*)) = tmp;                                                      \
}


// helper class for locking and unlocking table rows
class McTableRowLocker
{
public:
    McTable * mTable;

    McTableRowLocker( McTable * inTable )
    :   mTable ( inTable )
    {
        if (mTable)
            mTable->lockRows();
    }

    ~McTableRowLocker()
    {
        if (mTable)
            mTable->unlockRows();
    }
};


// helper class for locking and unlocking table relations
class McTableRelLocker
{
public:
    McTable   * mTable;
    int         mFieldOffset;

    McTableRelLocker( McTable * inTable, int inFieldOffset )
    :   mTable          ( inTable )
    ,   mFieldOffset    ( inFieldOffset )
    {
        if (mTable)
            mTable->lockRelation(mFieldOffset);
    }

    ~McTableRelLocker()
    {
        if (mTable)
            mTable->unlockRelation(mFieldOffset);
    }
};


// helper class for skipping table checks
class McTableSkipper
{
public:
    McTable * mTable;

    McTableSkipper( McTable * inTable )
    :   mTable ( inTable )
    {
        if (mTable)
            mTable->skipCheck();
    }

    ~McTableSkipper()
    {
        if (mTable)
            mTable->unskipCheck();
    }
};


// helper class for skipping database checks
class McDBSkipper
{
public:
    McDataBase * mDB;

    McDBSkipper( McDataBase * inDB )
    :   mDB ( inDB )
    {
        if (mDB)
            mDB->skipCheck();
    }

    ~McDBSkipper()
    {
        if (mDB)
            mDB->unskipCheck();
    }
};



//    McTable * tableSrc
//    int       relationOffset
//    char    * rowPointerSrc
//    char    * rowPointerDst
#define CMT2_ITER_BEGIN( tableSrc, relationOffset, rowPointerSrc, tableDst, rowPointerDst )     \
{                                                                                               \
    McTableRowLocker rowLocker_(tableSrc);                                                      \
    McTableRelLocker relLocker_(tableSrc,relationOffset);                                       \
    char ** rowPointerSrc##PP;                                                                  \
    bool    rowPointerDst##Del = false;                                                         \
    for (   rowPointerSrc##PP = (char**)*(char**)( (char*)rowPointerSrc + (int)relationOffset ) \
        ;   rowPointerSrc##PP != 0                                                              \
        ;   rowPointerSrc##PP = (char**)*((char**)rowPointerSrc##PP + 1)                        \
        )                                                                                       \
    {                                                                                           \
        if (rowPointerDst##Del)                                                                 \
        {                                                                                       \
            tableSrc->relationDel( rowPointerSrc, relationOffset, rowPointerDst ),              \
            tableDst->rowDelete( rowPointerDst );                                               \
            rowPointerDst##Del = false;                                                         \
        }                                                                                       \
        rowPointerDst = *rowPointerSrc##PP;

#define CMT2_ITER_UNHOOK_AND_DEL_CURR(rowPointerDst)   rowPointerDst##Del = true

#define CMT2_ITER_END( tableSrc, relationOffset, rowPointerSrc, tableDst, rowPointerDst )   \
    }                                                                                       \
    if (rowPointerDst##Del)                                                                 \
    {                                                                                       \
        tableSrc->relationDel( rowPointerSrc, relationOffset, rowPointerDst );              \
        tableDst->rowDelete( rowPointerDst );                                               \
    }                                                                                       \
}


////////////////////////////////////////////////////////////////////////////////
inline McTable * McDataBase::table( int inTableID )
{
    for ( int i=mTables.size() ; i-- ; )
        if ( mTables[i]->id() == inTableID )
            return mTables[i];
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
inline int McDataBase::numTables()
{
    return mTables.size();
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::id()
{
    return mTableId;
}


////////////////////////////////////////////////////////////////////////////////
inline char * McTable::name()
{
    return mTableName;
}


////////////////////////////////////////////////////////////////////////////////
inline void McTable::setName( char * inName )
{
    mTableName = inName;
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::rowAllCount( )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    if ( mRowWidth )
        return mRowData.size() / mRowWidth;
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::rowFreeCount( )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    return mRowFreeList.size();
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::rowUsedCount()
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    return rowAllCount() - rowFreeCount();
}


////////////////////////////////////////////////////////////////////////////////
inline void McTable::rowSetInitialSpace( int inRowCount )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    mRowSpaceInitial = inRowCount;
}


////////////////////////////////////////////////////////////////////////////////
inline char * McTable::rowAdd( )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    // 1st data
    if ( (int)mRowData.getMax() < mRowWidth * mRowSpaceInitial )
    {   // -- initial data array size (fixed at this time)
        CMT2ASSERT( mRowDataP==0 );
        mRowData.remax( mRowWidth * mRowSpaceInitial );
        mRowDataP = mRowData.dataPtr();
    }

    char * ret = 0;

    // check the free-list
    int s = mRowFreeList.size();
    if ( s > 0 ) 
    {   // -- get one from free list
        mRowFreeList.pop(ret); // the last free entry
        CMT2ASSERT( ret>=mRowData.dataPtr() && ret<(mRowData.dataPtr()+mRowData.size()) );
    }
    else
    {
        // grow data array if needed
        if ( mRowData.size() == mRowData.getMax() )
            expand( mRowData.size() / mRowWidth * 2 ); // quatdratic growing

        s = mRowData.size();
        mRowData.resize( s + mRowWidth );

        CMT2ASSERT( mRowDataP == mRowData.dataPtr() );

        ret = mRowDataP + s;

        CMT2ASSERT( ret>=mRowData.dataPtr() && ret<(mRowData.dataPtr()+mRowData.size()) );
    }

    memset( ret, 0, mRowWidth );

#if CMT2_INSERTTABLEID
    *(int*)(ret + mColIdToColOff[CMT2_ID_TABLEID]) = id();
#endif

#if CMT2_CHECK_ALWAYS
check();
#endif

    return ret;
}


////////////////////////////////////////////////////////////////////////////////
inline void McTable::rowDelete( char * inRow )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    CMT2ASSERT( mRowDataP );
    CMT2ASSERT( inRow >= mRowDataP && (inRow-mRowDataP < (signed)mRowData.size()) );
    CMT2ASSERT( *(int*)inRow != 1 ); // row is not deleted
    CMT2ASSERT( CMT2_ID(inRow)==mTableId );

    // remove relations
    for ( int i = mColCount ; i-- ; )
        if ( mColType[i] == T_1toN )
            relationRemoveAll( inRow , mColOffset[i] );

    // set mem
    memset( inRow+CMT2_ID_OFF*sizeof(int), 0, mRowWidth - CMT2_ID_OFF*sizeof(int) );

    // mark as deleted
    *(int*)inRow = 1;


    if ( (inRow - mRowDataP + mRowWidth) == (int)mRowData.size() )
        // that was the last row in the table - there is no need to insert it to the freelist
        mRowData.resize( mRowData.size()-mRowWidth );
    else
        // insert into freeList
        mRowFreeList.append( inRow );

#if CMT2_CHECK_ALWAYS
check();
#endif
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::columnIdToOffset( int inColId )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    CMT2ASSERT( inColId >= 0 && inColId < CMT2_MAX_COLUMNS );
    return mColIdToColOff[inColId];
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::columnOffsetToIndex( int inColOffset )
{
#if CMT2_CHECK_ALWAYS
check();
#endif
    
    for ( int i=mColCount ; i-- ; )
        if ( mColOffset[i]==inColOffset )
            return i;
    return -1;
}


////////////////////////////////////////////////////////////////////////////////
inline McTable * McTable::columnTarget ( int inColId )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    CMT2ASSERT( inColId >= 0 && inColId < CMT2_MAX_COLUMNS );
    CMT2ASSERT( mColType[mColIdToColIdx[inColId]] != T_Data );

    return mColTarget[mColIdToColIdx[inColId]];
}


////////////////////////////////////////////////////////////////////////////////
inline void McTable::columnSetTarget ( int inColId, McTable * inTarget )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    CMT2ASSERT( inColId >= 0 && inColId < CMT2_MAX_COLUMNS );
    CMT2ASSERT( mColType[mColIdToColIdx[inColId]] != T_Data );
    CMT2ASSERT( rowAllCount() == 0 );

    mColTarget[mColIdToColIdx[inColId]] = inTarget;

#if CMT2_CHECK_ALWAYS
check();
#endif
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::rowWidth()
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    return mRowWidth;
}


////////////////////////////////////////////////////////////////////////////////
inline char * McTable::data()
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    return mRowDataP;
}


////////////////////////////////////////////////////////////////////////////////
inline char * McTable::last()
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    if ( rowUsedCount() )
    {
        char * ret = mRowDataP + (rowAllCount()-1) * mRowWidth;
        while ( *(int*)ret )
        {
            ret -= mRowWidth; // skip deleted rows
            CMT2ASSERT( ret>=mRowDataP );
        }
        return ret;
    }
    else
        return 0;
}


////////////////////////////////////////////////////////////////////////////////
inline void McTable::pointerObserve( char ** ptr )
{
    CMT2ASSERT( !pointerIsObserved(ptr) );

//    *ptr = 0;
    mPointers.append( ptr );
}


////////////////////////////////////////////////////////////////////////////////
inline void McTable::pointerIgnore( char ** ptr )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    CMT2ASSERT( pointerIsObserved(ptr) );

    *ptr = 0;

    for ( int i=mPointers.size() ; i-- ; )
    {
        if ( mPointers[i] == ptr )
        {
            mPointers[i] = mPointers.last();
            mPointers.pop_back();
            return;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
inline bool McTable::pointerIsObserved( char ** ptr )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    for ( int i=mPointers.size() ; i-- ; )
    {
        if ( mPointers[i] == ptr )
            return true;
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
inline int McTable::pointerCount( )
{
#if CMT2_CHECK_ALWAYS
check();
#endif

    return (int)mPointers.size();
}


////////////////////////////////////////////////////////////////////////////////
inline bool McTable::relationEmpty( char * inRowSrc, int inColOff )
{
#if CMT2_CHECK_ALWAYS
    mDataBase->check();
#endif

    CMT2ASSERT( inRowSrc );
    CMT2ASSERT( inColOff < mRowWidth );
    CMT2ASSERT( mColNList[inColOff] );
    CMT2ASSERT( CMT2_ID(inRowSrc)==mTableId );

#if CMT2_CHECK_ROWPOINTERS
    int colIdx;
    for ( colIdx=mColCount ; colIdx-- ; )
        if ( mColOffset[colIdx]==inColOff )
            break;
#endif 
    
    char ** p = (char**)(inRowSrc + inColOff);

#if CMT2_CHECK_ALWAYS
    mDataBase->check();
#endif

    return *p==0;
}



#endif // MC_TABLE_H

/// @}
