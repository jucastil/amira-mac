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
#ifndef HX_SPREADSHEET_TO_CLUSTER_H
#define HX_SPREADSHEET_TO_CLUSTER_H

#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortToggleList.h>
#include <hxstatistics/HxSpreadsheetFilter.h>

#include "HxMultiCompWinDLLApi.h"

class HxCluster;
class HxUniformScalarField3;

/// Module for creating a cluster object from a spreadsheet.
class HXMULTICOMP_API HxSpreadSheetToCluster : public HxCompModule
{
    HX_HEADER(HxSpreadSheetToCluster);

    /// Output Types BoundingBoxes, Cluster, and Tensors
    enum OutputType {OutBoundingBoxes = 0, OutCluster = 1};

    /// Tensor Types None, BoundingBoxes, Intertia
    enum TensorType {TensorNone = 0, TensorBoundingBoxes = 1, TensorInertia = 2};

public:
    /// Default constructor.
    HxSpreadSheetToCluster();
  
    /// Output: 0 = BoundingBox, 1 = Point Cluster
    HxPortToggleList portOutput;

    /// Tensor: 0 = None, 1 = Point Cluster, 2 = Cluster Tensor
    HxPortRadioBox portTensor;

    /// Allows to select a table in case the spreadsheet has more than one table.
    HxPortMultiMenu portTable;

    /// Allows to select the material value column.
    HxPortMultiMenu portValue;

    /// Specifies which spreadsheet column corresponds to the x, y and z coordinates.  
    /// of the cluster object
    HxPortMultiMenu portCoord;

    /// Specifies which spreadsheet column corresponds to the x, y and z of Eigen Vector 1.  
    HxPortMultiMenu portEVector1;

    /// Specifies which spreadsheet column corresponds to the x, y and z of Eigen Vector 2.  
    HxPortMultiMenu portEVector2;

    /// Specifies which spreadsheet column corresponds to the x, y and z of Eigen Vector 3.  
    HxPortMultiMenu portEVector3;

    /// Specifies which spreadsheet column corresponds to the x, y and z of Eigen Values.  
    HxPortMultiMenu portEValues;

    /// Specifies which spreadsheet column corresponds to the x, y and z of Extent Min.  
    HxPortMultiMenu portExtentMin;

    /// Specifies which spreadsheet column corresponds to the x, y and z of Extent Max.  
    HxPortMultiMenu portExtentMax;

    /// Starts computation.
    HxPortDoIt portDoIt;

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    // The Bounding Boxes functions
    /// Creates a lineset object from a spreadsheet.    
    /// Spreadsheet columns of type STRING will be converted to float implicitly.
    /// Need to call createBoundingBoxColumns before calling this function
    void createBoundingBoxes(HxSpreadSheet *spreadsheet, int table);

    /// Helper function whichs fill the HxSpreadsheetFilter::ColumnMapping variable
    /// This function prepare the variables before calling createBoundingBoxes
    void createBoundingBoxColumns(HxSpreadsheetFilter::ColumnMapping *boundingBoxColumns);
       
    /// Creates a tensor object from a spreadsheet created by shape analysis.
    /// Spreadsheet columns of type STRING will be converted to float implicitly.
    /// Need the createClusterColumns before calling this function
    void createCluster(HxSpreadSheet *spreadsheet, int table);

    /// Creates a tensor object from a simple spreadsheet.
    void createClusterTensor(HxSpreadSheet *input, int table);

    /// Creates a cluster object from a spreadsheet created by shape analysis
    /// All other remaning columns of the spreadsheet, will be copied to cluster data columns.
    /// Spreadsheet columns of type STRING will be converted to float implicitely.
    void createCluster(HxSpreadSheet *input, HxCluster *output, int columnX, int columnY, int columnZ);

    /// Helper function whichs fill the HxSpreadsheetFilter::ColumnMapping variable
    /// This function prepare the variables before calling createCluster
    void createClusterColumns(HxSpreadsheetFilter::ColumnMapping *clusterColumns);
          
    /// Creates a cluster object from a simple spreadsheet.
    /// Spreadsheet columns of type STRING will be converted to float implicitely.
    /// Need the createClusterPointsColumns before calling this function
    void computeClusterPoints(HxSpreadSheet *input, int table);
 
    /// Helper function whichs fill the HxSpreadsheetFilter::ColumnMapping variable
    /// This function prepare the variables before calling computeClusterPoints
    void createClusterPointsColumns(HxSpreadsheetFilter::ColumnMapping *clusterPointsColumns);
    
 
protected:
    // Helper functions
    void setBoundingBoxTensorPorts();
    void setInertiaTensorPorts( bool bbox );
    void setBoundingBoxPorts();
    void setPointPorts();    
    void setNoPorts();

    // Internal verification functions
    bool isBoundingBox();
    bool isCluster();
    bool isTensorNone();
    bool isTensorBoundingBox();
    bool isTensorInertia();

    bool isOrthogonalVectors(HxSpreadSheet *spreadsheet, int table);

    // Internal functions  
    void invalidData();
    int  getTableIndex();
    void updatePortOutput(HxSpreadSheet *spreadsheet);
    const char *getCurrentValue(HxPortMultiMenu &multimenu, int col);
       
    virtual int canCreateData(HxData* data, McString& createCmd);
};

#endif


/// @}
