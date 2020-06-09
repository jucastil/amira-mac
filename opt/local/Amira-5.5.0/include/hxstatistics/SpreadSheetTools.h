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
#ifndef __SPREAD_SHEET_TOOLS_H__
#define __SPREAD_SHEET_TOOLS_H__

#include <hxcore/HxPortMultiMenu.h>
#include <hxstatistics/HxSpreadsheetFilter.h>

#include "HxStatisticsWinDLLApi.h"

class  HXSTATISTICS_API SpreadSheetTools{
public:
    /// Updating a port with the available tables from a spreadsheet
    /// @param spreadsheet The Spreadsheet
    /// @param portTable the  port which will be updated
     static void updatingPortTable(HxSpreadSheet *spreadsheet, HxPortMultiMenu &portTable);

    /// Update a 1 dimension Multimenu port with the available columns of a table from a spreadsheet
    /// @param index index of the Table in the Spreadsheet
    /// @param spreadsheet The Spreadsheet
    /// @param multimenu the port which will be updated (multimenu has 1 column)
    /// @param columnName the spreadsheet column name used to set the multimenu values
    static void updatePortValue(int index, HxSpreadSheet *spreadsheet, HxPortMultiMenu &multimenu, const char * columnName);

    /// Update a 3 dimension Multimenu port with the available columns of a table from a spreadsheet
    /// @param index index of the Table in the Spreadsheet
    /// @param spreadsheet The Spreadsheet
    /// @param multimenu the port which will be updated (multimenu has 3 columns)
    /// @param columnName1 the spreadsheet column name used to set the multimenu 1st column values
    /// @param columnName2 the spreadsheet column name used to set the multimenu 2nd column values
    /// @param columnName2 the spreadsheet column name used to set the multimenu 3rd column values
    static void updatePortVectors(int index, HxSpreadSheet *spreadsheet, HxPortMultiMenu &multimenu, const char * columnName1,const char * columnName2,const char * columnName3);

    /// Verify if a spreadsheet contains String column type (e.g. HxSpreadSheet::Column::STRING)
    /// @param spreadsheet The Spreadsheet
    /// The spreadsheet table
    static bool hasString(HxSpreadSheet *spreadsheet, int table);
}; 
#endif //__SPREADSHEETTOOLS_H__

/// @}
