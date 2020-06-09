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

/// @addtogroup vssegmentation vssegmentation
/// @{
#ifndef VS_LABEL_STATS_CALCULATION_H
#define VS_LABEL_STATS_CALCULATION_H

#include "VsSegmentationAPI.h"
#include "VsLabelStats.h"

#include <mclib/McBox3f.h>
#include <mclib/McBox3i.h>
#include <mclib/McDArray.h>

#include <vsvolren/McVec3l.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsTaskControl.h>

class McMat4f;
class McBitfield;
class VsData;
class VsMsg;
class VsVolume;

// VS_RELAY_CLASS VsLabelStatsCalculation VsRelay

class VSSEGMENTATION_API VsLabelStatsCalculation : public VsInterface
{
    VS_DECL_INTERFACE        ( VsLabelStatsCalculation )
    VS_DECL_INTERFACE_FACTORY( VsLabelStatsCalculation )
    VS_DECL_INTERFACE_RELAY  ( VsLabelStatsCalculation )

public:

    VsLabelStatsCalculation( VsMeta * inMeta = 0 );
    ~VsLabelStatsCalculation();

    VSRESULT compute(
        McDArray<VsLabelStats> & outLabelStats       // output of the function

    ,   const McBox3f          & inReferenceBound    // bounding box of the reference volume
    ,   const McVec3l          & inReferenceDim      // dimensions of the reference volume
    ,   const McMat4f          & inReferenceToDensityTrans   // transformation from the reference system to the density system

    ,   VsData                 * inDataDensi         // density data (might be transformed to the reference volume or have a different bbox or dims)
    ,   VsData                 * inDataLabel         // label data (if nonzero always the same as the reference volume)

    ,   double                   inDensiScale        // to get from raw data to real data
    ,   double                   inDensiOffset       // to get from raw data to real data

    ,   VsTaskControl          * inProgress
    ); // VS_SYNC_CALL


    VSRESULT compute(
        VsLabelStats & outLabelStats                 // output of the function

    ,   const McBox3i          & inLabelBound        // bounding box of the label data
    ,   const McBox3f          & inReferenceBound    // bounding box of the reference volume
    ,   const McVec3l          & inReferenceDim      // dimensions of the reference volume

    ,   VsData                 * inDataDensi         // density data (might be transformed to the reference volume or have a different bbox or dims)
    ,   McBitfield             & inDataLabel

    ,   double                   inDensiScale        // to get from raw data to real data
    ,   double                   inDensiOffset       // to get from raw data to real data

    //,   VsTaskControl          * inProgress
    ); 

};

VsMsg& operator<<(VsMsg& msg, const McDArray<VsLabelStats>& str);
VsMsg& operator>>(VsMsg& msg,       McDArray<VsLabelStats>& str);

#endif // VS_LABEL_STATS_CALCULATION_H

/// @}
