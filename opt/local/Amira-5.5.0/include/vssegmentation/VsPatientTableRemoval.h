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
#ifndef VS_PATIENT_TABLE_REMOVAL_H
#define VS_PATIENT_TABLE_REMOVAL_H

#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>

#include "VsSegmentationAPI.h"
#include <vsvolren/VsVolume.h>
#include <vsvolren/VsTaskControl.h>

class McVec3l;

// VS_RELAY_CLASS VsPatientTableRemoval VsRelay

class McColor;
class McBitfield;
class McProgressInterface;

/** This class implements a patient table removal algorithm.
    The algorithm identifies all connected regions above a
    pre-defined threshold. The largest region is assumed to
    be the patient body, while all other regions larger than
    a pre-defined minimum size are marked as patient table.
*/
class VSSEGMENTATION_API VsPatientTableRemoval : public VsInterface
{
    VS_DECL_INTERFACE        ( VsPatientTableRemoval )
    VS_DECL_INTERFACE_FACTORY( VsPatientTableRemoval )
    VS_DECL_INTERFACE_RELAY  ( VsPatientTableRemoval )

public:
    /// Constructor.
    VsPatientTableRemoval( VsMeta * inMeta=0, bool readFromCache=true, bool writeToCache=true );

    /** Sets threshold separating between inside and outside.
        The threshold is specified in Hounsfield units. It will
        be automatically converted into the data set's raw unit
        using the DICOM rescale slope and intercept values. On
        default, a threshold value of -500 is used. */
    void setThreshold(float value); // VS_RELAY

    /// Returns threshold separating between inside and outside.
    float threshold() const; // LOCAL_GET

    /** Sets minimum size for regions marked as patient table.
        Regions smaller than this threshold for example could
        be nodules in the lung. On default, a volume of 5 ccm
        is assumed. */
    void setMinimumSize(float ccm); // VS_RELAY

    /// Returns minimum size for patient table regions.
    float minimumSize() const; // LOCAL_GET

    /** Identifies the patient table in the input volume. If
        not already present, label data will be allocated. The
        low-res version of the labels will be updated as well.
        Currently only image data of type unsigned short can be
        processed.*/
    VSRESULT compute(VsVolume* volume, VsTaskControl* progress=0); // VS_SYNC_CALL

    /** Identifies the patient table and returns the result in
        in a bitfield. The bitfield can be merged into a label
        field using VsLabelTools::insertBitfield(). Currently
        only image data of type unsigned short can be processed. */
    VSRESULT compute(VsData* imageData, McBitfield& bitfield,
        float rescaleSlope, float rescaleIntercept, VsTaskControl* progress=0); // LOCAL_GET // actualy, no use outside this class

    /** Returns the material name used by this tool. On default,
        this is <c>PatientTable</c>. */
    static const char* materialName(); // LOCAL_GET

    /** Returns the default color for the <c>PatientTabble</<c> ROI.
        The default color is blue (0,0,1). */
    static const McColor& defaultColor(); // LOCAL_GET

protected:
    float mThreshold;
    float mMinimumSize;
    float mShapeRelThres; // percentage of the voxels in a slice that may be different to the underlying voxel
    float mSliceRelThres; // percentage of the slices of a region that may miss the shape criteria for patient table
    bool mWriteToCache;
    bool mReadFromCache;

private:
    /** Checks whether a region which is a patient table candidate
        fits the expected shape criteria.
        For the patient table, we expect small changes in shape of the
        marked region in the different slices. */
    bool checkShapeCriteria(McBitfield& bitfield, const McVec3l& bitfieldDimensions, int* boundingBox, mclong regionSize);
};

#endif


/// @}
