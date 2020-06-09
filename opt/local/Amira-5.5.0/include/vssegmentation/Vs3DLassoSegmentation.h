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
#ifndef VS_3DLASSO_SEGMENTATION_H
#define VS_3DLASSO_SEGMENTATION_H

#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>

//#include <hxexamine/ExTimeSeries.h>

#include <mclib/McColor.h>

#include "VsSegmentationAPI.h"

// VS_RELAY_CLASS Vs3DLassoSegmentation VsRelay

/** Module for 3D lasso tool.
*/   
class VSSEGMENTATION_API Vs3DLassoSegmentation : public VsInterface
{
    VS_DECL_INTERFACE        ( Vs3DLassoSegmentation )
    VS_DECL_INTERFACE_FACTORY( Vs3DLassoSegmentation )
    VS_DECL_INTERFACE_RELAY  ( Vs3DLassoSegmentation )

public:
    /// Constructor.
    Vs3DLassoSegmentation( VsMeta * inMeta = 0 );

    /// Destructor.
    ~Vs3DLassoSegmentation();

    /* set the name of the labels e.g.: "Cropped"
    */
    void setName(const McString & inDefaultName); // VS_RELAY

    /* set the color of the labels "Cropped"
    */
    void setColor(const McColor & inDefaultColor); // VS_RELAY

    /* Sets all the volumes, which are contained in this time series. All this
     * volumes were used for cropping in the function scanConvert().
    */
    void setTimeSeries( McDArray<VsVolume*> ts ); // relayed by addVolume() and clearVolumes()

    void setThreshold (float min, float max); // VS_RELAY

    /* checks if there are material, which has to be cropped.
    */
    bool checkConvert(
            VsNode* root
        ,   VsVolume * volume
        ,   VsVolren * volren
        ,   VsSlice * slice
        ,   VsCamera * camera
        ,   bool mAdd
        ,   bool & outHasCroppedMaterial
        ); // VS_SYNC_CALL

    /* scan for voxels, which should be cropped. It sets the cropped voxels as
       cropped by using the label "cropped".
    */
    VSRESULT scanConvert(
            VsNode* root
        ,   VsVolume * volume
        ,   VsVolren * volren
        ,   VsSlice * slice
        ,   VsCamera * camera
        ,   bool mAdd
        ,   bool bRemoveInsideMode
        ,   bool bSelectionMode
        ,   const McDArray< McVec3f > & line
        ); // VS_SYNC_CALL

    /* remove the label "cropped".
    */
    void removeCroppedLabels( VsVolume * volume ); // VS_RELAY

    /***************************************************************************
     ** The volume function are only used private. The functions have to be
     ** declared as public, because these functions are used by roc.
     ** Use setTimeSeries().
     ** 
     ** Begin "volume function"
     **************************************************************************/

    /* clear all Volumes.
    */
    void clearVolumes(); // VS_RELAY

    /* added all Volumes which are relevant for the scanConvert()
    */
    void addVolume(VsVolume * volume); // VS_RELAY

    /***************************************************************************
     ** End "volume function"
     **************************************************************************/

protected:
    McDArray<VsVolume*> mVolumes;
    McString            mName;
    McColor             mColor;
    float               mMin;
    float               mMax;
};

#endif //VS_3DLASSO_SEGMENTATION_H

/// @}
