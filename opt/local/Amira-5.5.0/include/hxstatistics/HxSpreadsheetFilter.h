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
#ifndef HX_SPREADSHEET_FILTER_H
#define HX_SPREADSHEET_FILTER_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRangeSlider.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortToggleList.h>

#include <anna/AnnaExpression.h>

#include <mclib/McVec3i.h>
#include <mclib/McVec2f.h>

#include <hxstatistics/HxSpreadSheet.h>

#include <limits>

#include "HxStatisticsWinDLLApi.h"

class HxUniformScalarField3;

class HXSTATISTICS_API HxSpreadsheetFilter : public HxCompModule
{
    // This macro is required for all modules and data objects
    HX_HEADER(HxSpreadsheetFilter);

    /*
     A filter element manages all information needed to filter with a single column: the currently
     selected column, a histogram, some statistics, and whether this columns should be used
     for the expression based filtering.
    */
    class FilterElement {
    public:
        enum FilterType {None, Histogram, Expression};

        FilterElement(HxObject *object, int num);
        float getValue(int row);
        void setSpreadsheet(HxSpreadSheet *sprsheet);
        void setTable(int value);
        void setColumn(int value);
        void updateInfo();
        void updateColumnEntries();
        void setPreferredColumn(McString label);
        bool selectPreferredColumn();
        bool hasColumnValidType();
        int getColumn();
        float getMinValue();
        float getMaxValue();
        const McString& getColumnLabel();
        bool filterRow(int i);
        void updateHistogram();
        const McString& getVarName();
        FilterType getFilterType();
        bool update();

        HxPortGeneric portSelect;
        HxPortRangeSlider portFilter;
        float mean;
        float standardDeviation;
    protected:
        typedef float(HxSpreadsheetFilter::FilterElement::*TGetValue)(int row);
        float getValueFloat(int row);
        float getValueInt(int row);
        void createHistogram();
        void clearHistogram();
          
        TGetValue getValuePtr;

        HxSpreadSheet *spreadsheet;
        int table;
        int column;
        HxSpreadSheet::Column *columnPtr;
        float min;
        float max;
        
        float scaleFactor;
        McString preferredColumn;
        FilterType filterType;
        McString varName;
    };

  public:
    HxSpreadsheetFilter();

    ~HxSpreadsheetFilter();

    virtual void update();

    virtual void compute();

    /// Displays number of regions found.
    HxPortInfo portInfo;
    /// Selected table;
    HxPortMultiMenu portTable;
    /// Port expression
    HxPortText portExpr;
  
    /// Restrict computation to sub-region of interest
    HxConnection portROI;
    /// Restrict computation to sub-region of interest
    HxConnection portLabels;
    /// Starts computation.
    HxPortDoIt portDoIt;

    /// Filter Elements Array
    McDArray<FilterElement*> filterElements;

public:
    /// Column mapping stores and manages the columns needed for a single output 
    /// operations. Columns are identified via their labels.
    class HXSTATISTICS_API ColumnMapping
    {
    public:
        ColumnMapping();
        void append(const McString &label);
        void append(const McString &label0, const McString &label1, const McString &label2);
        bool findMatchingColumns(HxSpreadSheet *spreadsheet, int table=0);
        float getValue(int column, int row);
        McString getLabel(int col);
        McVec3f getVec3f(int col0, int col1, int col2, int row);
        bool isValid();
        int getColumnsSize();
        int findRow(int col, float value);
       
    protected:
        struct Column {
            Column() : mLabel(""), mColumn(-1), columnPtr(0)
            {}
            Column(const McString &label) : 
                mLabel(label), mColumn(-1), columnPtr(0)
            {}
            McString mLabel;
            int mColumn;
            HxSpreadSheet::Column *columnPtr;
            typedef float(HxSpreadsheetFilter::ColumnMapping::Column::*TGetValue)(int row);
            float getValueFloat(int row);
            float getValueInt(int row);
            float getValue(int row);
            TGetValue getValuePtr;
        };
        McDArray<Column> columns;
        bool mValid;
    };

 protected:  

    void computeStatistics(HxSpreadSheet *spreadsheet, int table);
    void computeMeanDirection(HxSpreadSheet *spreadsheet, int table);
    bool isFiltered(int row);
    void createSpreadsheet(HxSpreadSheet *spreadsheet, int table);
    void updateInfo(HxSpreadSheet *spreadsheet, int table);
    void updateExpression(); 
    virtual int canCreateData(HxData* data, McString& createCmd);
    virtual void savePorts(FILE* fp);


    // Use to compute Statistics
    ColumnMapping centerColumns;
    ColumnMapping meanDirectionColumns;
    
    AnnaExpression expr;
    bool mExpressionIsValid;

    McVec3f orientation;   // directional cosine
    double RL, SV;         // resultant length, spherical variance

    bool isUpToDate;
};

#endif // HX_SPREADSHEET_FILTER_H

/// @}
