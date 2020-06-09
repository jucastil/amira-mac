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

/// @addtogroup hxmulticomp hxmulticomp
/// @{
#ifndef HX_FILTERBYSPREADSHEET_H
#define HX_FILTERBYSPREADSHEET_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxfield/HxUniformLabelField3.h>
#include <hxstatistics/HxSpreadsheetFilter.h>

#include "HxMultiCompWinDLLApi.h"

/// Module for creating a label object from a spreadsheet.
class HXMULTICOMP_API HxFilterBySpreadsheet : public HxCompModule
{
    HX_HEADER(HxFilterBySpreadsheet);
  public:
    HxFilterBySpreadsheet();
      
    /// Restrict computation based on connected label
    HxConnection portInputSheet;

    /// Allows to select a table in case the spreadsheet has more than one table.
    HxPortMultiMenu portTable;

    /// Allows to select the material value column.
    HxPortMultiMenu portValue;
    
    /// Starts computation.
    HxPortDoIt portDoIt;

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    //The Label functions  
    /// Creates a label object from a spreadsheet.
    /// @param spreadsheet spreadsheet input
    /// @param image the labelfield input
    /// @param result the labelfield object output
    /// @param table the index of the table in the spreadsheet
    /// Spreadsheet columns of type STRING will be converted to float implicitly.
    /// Need the createLabelColumns before calling this function
    template<class S>
    void createVolume(HxSpreadSheet *spreadsheet, int table, HxUniformScalarField3* image, HxUniformScalarField3* result);    
    HxUniformScalarField3* updateResult(HxUniformScalarField3 *input, HxUniformScalarField3 *oldResult);
    void  pushLabelsParameters(HxSpreadSheet *spreadsheet, int table, HxUniformScalarField3* result, HxUniformScalarField3* image);

protected:
    // Internal functions      
    int  getTableIndex();
    bool isExteriorMaterial( HxParamBundle* im_param);

    // Virtual class functions
    virtual int canCreateData(HxData* data, McString& createCmd);
};
#endif // HX_FILTERBYSPREADSHEET_H

/// @}
