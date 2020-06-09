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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_RECT_POSITIONS
#define MC_RECT_POSITIONS

#include "McDataSpace.h"
#include "McAssert.h"

/** A helper class to store everything needed to describe multi dimensional
    rectilinear positions.

    Each dimension might be either explicitly given by a vector or will
    be implicitly calculated from the bounding box assuming a uniform
    distribution of the positions in this dimension.
 */
class McRectPositions {
    public:
        /**
          */
        McRectPositions () {
            init ();
        };

        /**
          */
        McRectPositions (int numdims, const int* dims, const float* bbox, const float** coords) {
            mcenter3 ("McRectPositions");
            mcrequire (dims);

            init ();
            mNDims = numdims;
            memcpy (mDims, dims, mNDims * sizeof (int));
            if (bbox) {
                mPosbuffer.append (2 * mNDims * sizeof (float), bbox);
            } else {
                for (int d = 0; d < numdims; d++) {
                    mPosbuffer.append (-1.0);
                    mPosbuffer.append (1.0);
                }
            }
            if (coords) {
                for (int d = 0; d < numdims; d++) {
                    if (coords[d]) {
                        int idx = mPosbuffer.size ();
                        mPosbuffer.append (dims[d], coords[d]);
                        mPosIndex[d] = idx;
                    }
                }
            }
        };

        /**
          */
        McRectPositions (const McRectPositions& other) {
            copy(other);
        }

        /**
          */
        McRectPositions& operator=(const McRectPositions& other) {
            copy(other);
            return *this;
        }

        /**
          */
        int nDims () const {
            return mNDims;
        }

        /**
          */
        const int* dims() const {
            return mDims;
        }

        /**
          */
        const float* bbox () const {
            return mPosbuffer.dataPtr ();
        }

        /**
          */
        const float* positions (int indim) const {
            mcenter3 ("McRectPositions::positions");
            mcassert (indim >= 0 && indim < mNDims);
            if (mPosIndex[indim] >= 0) {
                return mPosbuffer.dataPtr() + mPosIndex[indim];
            }
            return 0;
        }

        void vertexpos (const int* idx, float* pos) const {
            const float* bb = bbox();
            for (int d = 0; d < mNDims; d++, idx++, bb += 2, pos++) {
                const float* pvec = positions(d);
                if (pvec) {
                    *pos = pvec[*idx];
                } else {
                    *pos = bb[0] + ((mDims[d] > 1) ? ((bb[1] - bb[0]) / float(mDims[d] - 1)) : 0) * float(*idx);
                }
            }
        }

    private:
        void init () {
            mNDims = 0;
            memset (mDims, 0, MC_MAX_NDIMS * sizeof (int));
            for (int i = 0; i < MC_MAX_NDIMS; i++) {
                mPosIndex[i] = -1;
            }
            mPosbuffer.clear ();
        }

        void copy (const McRectPositions& other) {
            mPosbuffer = other.mPosbuffer;
            mNDims = other.mNDims;
            memcpy (mDims, other.mDims, MC_MAX_NDIMS * sizeof(int));
            memcpy (mPosIndex, other.mPosIndex, MC_MAX_NDIMS * sizeof(int));
        }

        McDArray<float> mPosbuffer;
        int mNDims;
        int mDims[MC_MAX_NDIMS];
        int mPosIndex[MC_MAX_NDIMS];
};

#endif

/// @}
