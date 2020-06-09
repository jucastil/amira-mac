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
#ifndef _VS_IMAGEBUNDLE_H
#define _VS_IMAGEBUNDLE_H

#include <vsvolren/VsMemoryData.h>

/**
This local class is used for maintaining a bundle of individual images.
It is very useful for incremental processing of 3D volumes.
*/

class VSVOLREN_API VsImageBundleImpl : public VsMemoryData
{
    /// An index, that identifies the image bundle
    int mIndex;
    /// Number of slots already filled
    int mFilled;
    /// Pointer to data access currently in use
    const VsDataAccess * mDataAccess;
    
    /// Flag to indicate whether resampling is desired
    bool mNeedResampling;
    /// High res dimension - of the whole volume (not only the bundle)
    int mHighResDims[3];
    /// Low res dimension - if applicable
    int mLowResDims[3];

    /// The low res data array
    McHandle<VsData> mLowResData;

    /// The desired histogram size
    int mHistogramSize;

public:
    /// Constructor 
    VsImageBundleImpl();
    /// Destructor
    ~VsImageBundleImpl();

    /** Initialize the object. New memory will be allocated and the auto deletion
        flag is set to true, meaning that the memory chunk will be released upon object
        deletion.

        \param  inDims
                Target dimensions of the data. Must be a non-zero int[3] pointer.
        \param  inBundleSize
                Number of images within an image bundle
        \param  inPrimType
                Primitive type of the data components.
        \param  inNumDataVar
                Number of components per data element.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT init( const int * inDims, int inBundleSize, McPrimType inPrimType, int inNumDataVar=1 );

private:
    /// Hide all init routines from VsMemoryData
    VSRESULT init( const int * inDims, McPrimType inPrimType, int inNumDataVar=1, bool inForceLinear=true );
    VSRESULT init( const int * inDims, const int * inStrides, void * inVolumeData, McPrimType inPrimType, int inNDataVar=1 );
    VSRESULT init( const int * inDims, const int * inStrides, void ** inSliceData, McPrimType inPrimType, int inNDataVar=1 );
public:

    /// Gets the pointer to the next image's raw data array 
    void * nextImagePtr();
    /// Commit the image
    void commitImage();

    /// Returns, whether the bundle is already complete
    bool complete();
    /// Reset the object
    void nextBundle() { mFilled = 0; mIndex++; }

    /// Set an index
    void setIndex(int index) { mIndex = index; }
    /// Get the index
    int getIndex() { return mIndex; }

    /// Set a low level resolution
    void setLevel1Resolution(const int * dims);

    /// Write the (amira mesh) file header
    bool writeHeader( FILE * out );
    /// Write the current slice bundle as raw data to an (amira mesh) file
    bool writeRawData( FILE * out, VsData * data, bool swapBytes, int numSlices = -1 );
    /// Write the (amira mesh) file footer (low res data, histogram, etc.)
    bool writeFooter( FILE * out, VsData::HistogramType& histo, bool swapBytes );

    bool writeRawData( FILE * out, FILE * outMirror, VsData * data, bool swapBytes, int numSlices = -1 );
    bool writeFooter( FILE * out, FILE * outMirror, bool swapBytes );

    class VsMirrorWriter* mMirrorWriter;
    friend class VsMirrorWriter;
};

#endif


/// @}
