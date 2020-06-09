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

/// @addtogroup hximio hximio
/// @{
#ifndef HX_STACKED_SLICES_LATTICE_H
#define HX_STACKED_SLICES_LATTICE_H

#include "HxImIOWinDLLApi.h"
#include <mclib/McFilename.h>
#include <hxcore/HxSpatialData.h>
#include <hxfield/HxCoordType.h>
#include <hxlatticex/HxLattice.h>
#include <hxlatticex/HxLatticeImplHelper.h>

class StackedSlicesLattice;

/** 
  */
class HXIMIO_API HxStackedSlicesLattice : public HxSpatialData {

    HX_DATA_HEADER (HxStackedSlicesLattice);

    public:
        ///
        virtual void getBoundingBox (float bbox[6]) const;

        /// OK
        virtual void info ();
        
        ///
        static int read(const char* filename);

    private:
        HxStackedSlicesLattice (StackedSlicesLattice* owner);

        StackedSlicesLattice* mOwner;
};



class McDataSpaceCache;
class McRectPositions;

template <class IMPL> class HxLatticeOwnerTemplate;

/** 
  */
class HXIMIO_API StackedSlicesLattice : public McInterface {

    HX_DATA_HEADER (StackedSlicesLattice);

    public:
        ///
        static StackedSlicesLattice* read(const char* filename);

    protected:
        /// OK
        StackedSlicesLattice ();

        /// OK
        ~StackedSlicesLattice ();

    public:
        virtual void getBoundingBox (float bbox[6]) const;

        /* --------------------------------------------- */
        /* The HxLattice Interface                      */
        /* --------------------------------------------- */

        ///
        int nDataSets () const;
       
        ///
        const char* getNameOfSet (int datasetidx) const;

        /// OK
        McDataType dataTypeOfSet(int set) const;

        /// OK
        int nDataVarOfSet(int set) const; 

        /// OK
        McDataSpace getDataSpace () const;

        /// OK
        HxLatticeType latticeType () const;

        /// OK
        McBoundingBox getBoundingBox (const McDataSpace* restrictds);

        ///
        void getRectPositions (McRectPositions& pos);

        /// OK
        void getRangeOfSet (int set, float& min, float& max);

        ///
        int trygetRangeOfSet (int datasetidx, float& min, float& max);

        /// OK
        HxLatticeHandle* getHandle (int datasetcount, const int* datasets);

        /// OK
        void getDataOfSet (int dataset, const McDataSpace& space, const McMemorySelection& memselection);

        /// OK
        int trygetDataOfSet (int dataset, const McDataSpace& space, const McMemorySelection& memselection);

        /// OK
        HxLatticeGetQueue* getQueue (int datasetcount, const int* datasets);

        /// OK
        void valueOfSet (void* result, int set, const int* indices);

        /* --------------------------------------------- */
        /* END The HxLattice Interface                  */
        /* --------------------------------------------- */

        class HxLatticeImpl;

      private:

        class Handle;
        friend class Handle;
        friend class HxStackedSlicesLattice;

        struct Slice {
            McFilename filename;
            float zCoord;
        };

        int mNumDataVar;
        int mImageWidth;
        int mImageHeight;
        float mPixelSize[2];
        float mPixelOrigin[2];
        McDArray<Slice> mSlices;
        bool mIsUniform;
        float mSliceDistance;
        float mMaxSliceDistance;
        McPrimType mPrimType;
        float mDataRange[2];
        McFilename mDirectory;
        HxLattice* mLattice;
        McDataSpaceCache* mCache;
        bool mCacheEnabled;
};

#endif

/// @}
