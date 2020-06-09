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
#ifndef _VS_VOLUME_IMPL_H
#define _VS_VOLUME_IMPL_H

#include "VsVolume.h"

#include "VsObjectImpl.h"


#include "VsVolumeLevel.h"
#include "VsData.h"
#include "VsCropRegion.h"

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>

#include <amiramesh/HxParamBundle.h>

class AmiraMesh;
class VsVolumeReader;
class VsColorMap;


////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_IMPL VsVolumeImpl : public VsObjectImpl
{
    VS_IMPLEMENTATION( VsVolumeImpl, VsObjectImpl, VsVolume );

    friend class VsVolumeReader;

public:
    
    /** Strategy for selecting volume data. */
    enum SelectionStrategy
    {
        INTERACTIVE,        // specified level or lower resolution level
        INTERACTIVE_FIRST,  // specified level or lower resolution, higher
                            // resolution in case no lower resolution is available
        QUALITY,            // specified level or higher level
        QUALITY_FIRST,      // specified level or higher resolution, lower
                            // resolution in case no higher resolution is available
        EXACT,              // specified level only
        DONT_CARE           // any level

    };

    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
public:

    float           performance();
    VSRESULT        setData( VsData * level0Density );
    VsData        * data() const;
    VsData        * primaryData() const;
    VsData        * labelData( unsigned int inLevel ) const;
    VsData        * colorData( unsigned int inLevel ) const;
    bool            hasLabelData() const { return (labelData(0)!=0); }
    VSRESULT        boundingBox( McBox3f & outBox ) const;
    void            setBoundingBox( const McBox3f & inBox ); // _RELAY
    VSRESULT        computeLevels(VsJobControl * control = 0);
    void            updateLevel1(const McBox3i* roi=0);
    void            updateLevel1Labels(const McBox3i* roi=0);
    VSRESULT        createLabels();
    VSRESULT        clearSelection();
    VSRESULT        computeNormals( VsVoxelDescriptor::VoxelDescriptor normalType, unsigned int mask=0);
    void            clearNormals();
    bool            hasNormals() const;
    VSRESULT        setData   ( unsigned int inLevel, VsData * inData );
    VSRESULT        addData   ( unsigned int inLevel, VsData * inData, VsVoxelDescriptor::VoxelDescriptor inDesc ); // _RELAY
    VSRESULT        setLabelData( unsigned int inLevel, VsData * inData, bool fromMaster=false );
    VSRESULT        setColorData( unsigned int inLevel, VsData * inData );
    VSRESULT        removeData( unsigned int inLevel, unsigned int inSemantics );
    VSRESULT        removeData( unsigned int inLevel, VsData * inData );
    VSRESULT        removeData( unsigned int inLevel );
    VSRESULT        setDataModified( VsData * inData );
    unsigned int    semantics ( unsigned int inLevel );
    int             numData   ( unsigned int inLevel );
    VsData        * dataByIndex ( unsigned int inLevel, unsigned int inDataIndex, McHandle<VsVoxelDescriptor> * outDesc=0 ) const;
    VsData        * data      ( unsigned int inLevel, unsigned int inSemantics ) const;
    VsData        * data      ( unsigned int inLevel ) const;
    VsData        * primaryData( unsigned int inLevel ) const;
    int             dataIndex ( unsigned int inLevel, VsData * inData ) const ;



    int             numLevels() const;
    VSRESULT        writeAmiraMesh(const char* filename);
    VSRESULT        readLabelsAmiraMesh(const char* inFileName);
    VSRESULT        readLabelsAmiraMesh(AmiraMesh* m, const char* inFileName);
    VSRESULT        writeLabelsAmiraMesh(const char* inFileName, const char * inDescription = 0, const char * codec = 0);
    static VsVolume* readAmiraMesh(const char* filename, const McBox3i* roi=0, const McVec3i* downsamplingFactor=0, bool autoStart=true, VsJobControl* jc=0);
    static VsVolume* readAmiraMesh(AmiraMesh* m, const char* filename, bool moveParameters, const McBox3i* roi=0, const McVec3i* downsamplingFactor=0, bool autoStart=true, VsJobControl* jc=0);
    static void     adjustBoundingBox( McBox3f & inOutBox, const McVec3i& inSourceSize, const McVec3i& inTargetSize );

    VSRESULT setLabelMaster(VsVolume * inVolume);
    const VsVolume * labelMaster();

    HxParamBundle & parameters(bool possiblyShared=true);
    const HxParamBundle & parameters(bool possiblyShared=true) const;
    void setParameters(HxParamBundle* inBundle);
    HxParamBundle* parseParametersPath(const char * path, VsVolume::ParamType type=VsVolume::P_SHARED);
    void setParameters(VsVolume::ParamType type, const char * path, const char * name, const char*  value, int parse);
    void setParameters(VsVolume::ParamType type, const char * path, const char * name, const int    value);
    void setParameters(VsVolume::ParamType type, const char * path, const char * name, const double value);
    void setParameters(VsVolume::ParamType type, const char * path, const char * name, const int dim, const float*  values);
    void setParameters(VsVolume::ParamType type, const char * path, const char * name, const int dim, const int*    values);
    void setParameters(VsVolume::ParamType type, const char * path, const char * name, const int dim, const double* values);
    void removeParameters(VsVolume::ParamType type, const char * path, const char * name); // _RELAY
    void setDataWindow(float vmin, float vmax); // _RELAY


    const unsigned int  * preferredBrickSize();
    void            setPreferredBrickSize(const unsigned int* brickSize);
    const McBox3f & boundingBoxAllLevels();
    void            recomputeBoundingBoxAllLevels(); // _RELAY
    int             clipPlanes( VsColorMap * m, McDArray<McVec4f> & planes );
    VsCropRegion  * cropRegion() const;
    VSRESULT        clipPlane( unsigned int inPlaneIndex, McPlane & outPlane ) const;
    VSRESULT        addClipPlane( const McPlane & p, float min=1, float max=-1 );
    VSRESULT        deleteClipPlanes();
    unsigned int    numClipPlanes() const;
    void            doneReading(bool success);

    ////////////////////////////////////////
    // verification methods for WAN
    ////////////////////////////////////////
    bool verify_parameters(const VsMsg & inValue, bool workerSide=false, VsVolume::ParamType type=VsVolume::P_SHARED) const;
    bool verify_getMaterials(const VsMsg & inValue, bool workerSide=false) const;


    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
private:

    VSRESULT        vimpl_setOptioni( int inOption, int inValue );
    VSRESULT        vimpl_setOptiond( int inOption, double inValue );
    VSRESULT        vimpl_optioni( int inOption, int & outValue ) const;
    VSRESULT        vimpl_optiond( int inOption, double & outValue ) const;
    void *          vimpl_extension( int inEnum, void * inData);
    VSRESULT        vimpl_setCropRegion( VsCropRegion * inCropRegion );
    VSRESULT        vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );


    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////
public:

    VSRESULT        level( unsigned int inLevel, McHandle< VsVolumeLevel > & outLevel );
    VsVolumeLevel*  level( int iLevel ) const { return mLevels[iLevel]; }

    /** Returns the level according to selection strategy. Returns zero if no valid 
        level could be found according to the selection strategy @c inStrategy. 
        The actually selected level is returned in @c outLevel. */

    VsVolumeLevel * selectLevel(int level, SelectionStrategy strategy = INTERACTIVE_FIRST, int* outLevel = NULL );

    /** Reads histogram data from the AmiraMesh data handle @c inMesh. If no actual data
        is stored in this data handle, the histogram elements are read directly from
        the AmiraMesh file @c inFileName, instead. 
        The resulting histogram is stored in the @c outHistogram array.
        If no histogram could be obtained, the size of that array is set to zero. */
    static void     readAmiraMeshHistogram(AmiraMesh::Data* d, const char* filename, VsData::HistogramType& histogram);

    void invalidateCachedData();


    ////////////////////////////////////////
    // members
    ////////////////////////////////////////

public:

    // transformation from raw to physical data
    float                   mRescaleSlope;
    float                   mRescaleIntercept;

    // ??? RK
    HxParamBundle         * mExternalParameters;

    // ??? RK something if volumes share the same labels ???
    VsVolume              * mLabelMaster;
    McDArray<VsVolume*>     mLabelSlaves;


protected:

    /** Fallback parameters. This parameter bundle is used if no level
        0 data set exists. Should never be the case... */
    HxParamBundle       mParameters;
        
    /** Usually the bounding box of the volume is identical to the bounding box
        of the level-0 data set. However, if the volume is reconstructed from
        separate bricks stored in a file there is no level-0 data object. Thus
        we store the bounding box in a separate member. */
    McBox3f             mBoundingBox;

    /** The boxes of the various levels are different.
        Reason 1: different voxel sizes and the box goes through the center of the border voxels.
        Reason 2: small bricks are discarded which leads to a box shrink.
        This box is the maximum common box of all current levels and may change 
        if new levels or bricks are created.
        Call recomputeBoundingBoxAllLevels() to recompute this box.
    */
    McBox3f             mBoundingBoxAllLevels;


    McDArray< McHandle<VsVolumeLevel> > mLevels;

    unsigned int        mPreferredBrickSize[3];

    /** Reader thread, used for asynchroneous import of high-res data */
    VsVolumeReader    * mVolumeReader;

    /** To ensure no touch is triggered by the asynchroneous reader 
        if cancelation of the reader was invoked in the destructor. */
    bool                mInDestructor;



    float               mReadTime;
    float               mReadTimeAsync;
    bool                mWaitedForVolumeReader;


    struct ClipRegion
    {
        McPlane mPlane;
        float   mRange[2];
    };
    McDArray<ClipRegion> mPlanes;

    McHandle<VsCropRegion>  mCropRegion;
};

#endif


/// @}
