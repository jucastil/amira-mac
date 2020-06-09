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
#ifndef MC_DATASPACE_H
#define MC_DATASPACE_H

#include "McWinDLLApi.h"
#include "McMalloc.h"
#include "McPrimType.h"
#include "McDataPointer.h"
#include "McAssert.h"
#include "McDArray.h"

#include <string.h>

// the maximum number of dimensions
enum {
    MC_MAX_NDIMS = 10
};

/** Describe a multidimensional array from which a part is selected.

    At the moment one hyperslab can be selected using selectHyperslab.
    The selection is the same as a hdf5 hyperslab
    http://hdf.ncsa.uiuc.edu/HDF5/doc/H5.intro.html#Intro-PMSelectHyper
    except for the missing blocksize. Each block is only one voxel large.

    No memory is attached to objects of this class. Only the size of
    the space is described. Use McMemorySelection to describe physical memory.
  */
class McDataSpace {
    public:
        /// empty space
        McDataSpace () {
            init (0);
        };

        /// Space of rank with dims[rank].
        McDataSpace (int numdims, const int* dims) {
            init(numdims, dims);
        }

        McDataSpace (const McDArray<int>& dims) {
            init (dims.size(), dims.dataPtr());
        }

        /// 1d space.
        McDataSpace (int d0) {
            init (1, &d0);
        };

        /// 2d space.
        McDataSpace (int d0, int d1) {
            int d[2];
            d[0] = d0;
            d[1] = d1;
            init (2, d);
        };

        /// 3d space.
        McDataSpace (int d0, int d1, int d2) {
            int d[3];
            d[0] = d0;
            d[1] = d1;
            d[2] = d2;
            init (3, d);
        };

        /// 4d space.
        McDataSpace (int d0, int d1, int d2, int d3) {
            int d[4];
            d[0] = d0;
            d[1] = d1;
            d[2] = d2;
            d[3] = d3;
            init (4, d);
        };

        /// The number of dimensions.
        int nDims () const {
            return mNDims;
        }

        /// The size of the complete dataspace in each direction.
        const int* dims () const {
            return mDims;
        }

        McDArray<int> getDimsAsMcDArray() const {
            McDArray<int> d;
            d.append (mNDims, mDims);
            return d;
        }

        /// The size of the dataspace in a specific dimension d.
        int dims (int d) const {
            mcenter3 ("McDataSpace::dim");
            mcrequire (d < mNDims);

            return mDims[d];
        }

        /** Select a hyperslab (similar to hdf5).

            starting at voxel at start every stridesth
            voxel is selected, count voxels in each direction.
          */
        void selectHyperslab (const int* start, const int* count, const int* strides = 0) {
            // check bounds
            {
                for (int i = 0; i < mNDims; i++) {
                    mcrequire (count[i] >= 1);
                    mcrequire (start[i] >= 0 && start[i] < mDims[i]);
                    mcrequire (!strides || strides[i] >= 1);
                    mcrequire ((start[i] + (count[i] - 1) * (strides ? strides[i] : 1) < mDims[i]));
                }
            }
            // copy stuff
            memcpy (mStart, start, mNDims * sizeof (int));
            if (!strides) {
                for (int i = 0; i < mNDims; i++) {
                    mStrides[i] = 1;
                }
            } else {
                memcpy (mStrides, strides, mNDims * sizeof (int));
            }
            memcpy (mSize, count, mNDims * sizeof (int));
        }

        /** Select complete dataspace.
          */
        void selectAll () {
            memcpy (mSize, mDims, mNDims * sizeof(int));

            for (int i = 0; i < mNDims; i++) {
                mStart[i] = 0;
                mStrides[i] = 1;
            }
        }

        /** set selection in dimension dim.
          */
        void setSelection (int dim, int start, int count = 1, int stride = 1) {
            mcenter3 ("McDataSpace::setSelection");
            mcrequire (dim >= 0 && dim < mNDims);
            mcrequire (count >= 1);
            mcrequire (start >= 0 && start < mDims[dim]);
            mcrequire (stride >= 1);
            mcrequire ((start + (count - 1) * stride < mDims[dim]));

            mStart[dim] = start;
            mSize[dim] = count;
            mStrides[dim] = stride;
        }

        /** Get the number of elements of the selection.

            Note: this returns a 64 bit integer.
          */
        mcint64 selectionElemCount () const {
            mcint64 ret = 1;
            for (int i = 0; i < mNDims; i++) {
                ret *= mSize[i];
            }
            return ret;
        }

        /// Get the start of the selection.
        const int* selectionStart () const {
            mcenter3 ("McDataSpace::selectionStart");
            mcrequire (mNDims && mStart[0] >=0);

            return mStart;
        }

        // Get the start of the selection in dimension d.
        int selectionStart (int d) const {
            mcenter3 ("McDataSpace::selectionStart(int)");
            mcrequire (d >= 0 && d < mNDims);

            return mStart[d];
        }

        /// Get the strides of the selection.
        const int* selectionStrides () const {
            mcenter3 ("McDataSpace::selectionStrides");
            mcrequire (mNDims && mStart[0] >=0);

            return mStrides;
        }

        // Get the stride of the selection in dimension d.
        int selectionStrides (int d) const {
            mcenter3 ("McDataSpace::selectionStride");
            mcrequire (d >= 0 && d < mNDims);

            return mStrides[d];
        }

        /// Get the size of the selection.
        const int* selectionSize () const {
            mcenter3 ("McDataSpace::selectionSize");
            mcrequire (mNDims && mStart[0] >=0);

            return mSize;
        }

        // Get the size of the selection in dimension d.
        int selectionSize (int d) const {
            mcenter3 ("McDataSpace::selectionSize(int)");
            mcrequire (d >= 0 && d < mNDims);

            return mSize[d];
        }


        // Get the maximum index inside the selection.
        int selectionEnd (int d) const {
            mcenter3 ("McDataSpace::selectionEnd");
            mcrequire (d >= 0 && d < mNDims && mSize[d] >= 1);

            return mStart[d] + (mSize[d] - 1) * mStrides[d];
        }

        /// \brief Get the linear offset from (0, 0, ...) to pos. Returns mcint64.
        mcint64 calcOffset (const int* pos) const {
            mcint64 off = 0;
            for (int d = mNDims - 1; d >= 0; d--) {
                off = off * mcint64(mDims[d]) + mcint64(pos[d]);
            }
            return off;
        }

        /** Two dataspaces are identical if they have the
            same number of dims and size and the same selection.
          */
        bool isIdentical (McDataSpace const & other) const {
            if (mNDims != other.mNDims)
                return 0;
            for (int i = 0; i < mNDims; ++i) {
                if (mDims[i] != other.mDims[i])
                    return 0;
                if (mStart[i] != other.mStart[i])
                    return 0;
                if (mSize[i] != other.mSize[i])
                    return 0;
                if (mStrides[i] != other.mStrides[i])
                    return 0;
            }
            return 1;
        }

        /** Two dataspaces have the same space if they have
            the same number of dims and the same dimensions.

            The selection doesn't influence this test.
         */
        bool sameSpace (const McDataSpace& other) const {
            if (mNDims == other.mNDims
                    && memcmp (mDims, other.mDims, mNDims * sizeof(int)) == 0) {
                return true;
            }
            return false;
        }

        /** If the selection of other is included in
            the selection of this dataspace this test
            will be true.
          */
        bool includesSelection (const McDataSpace& other) const {
            // a selection is included if:
            //   - the start of other is in the selection of this
            //   - the strides of other are compatible with this strides
            //   - the sizes are compatible
            // we check for unmatched restrictions
            for (int i = 0; i < mNDims; i++) {
                const int startOffset = other.mStart[i] - mStart[i];
                const int startInMystrides = (startOffset) / mStrides[i];
                // ... check if the difference in starts is not a multiple of strides
                if (startInMystrides * mStrides[i] != startOffset) {
                    return 0;
                }
                // ... check if start is outside the selected range
                if (! (0 <= startInMystrides && startInMystrides < mSize[i])) {
                    return 0;
                }
                const int stridesInMystrides = other.mStrides[i] / mStrides[i];
                // ... check if other strides are not a multiple of this strides
                if (stridesInMystrides * mStrides[i] != other.mStrides[i]) {
                    return 0;
                }
                // ... check if other size is outside of this size
                if (! (stridesInMystrides * (other.mSize[i] - 1) + startInMystrides < mSize[i])) {
                    return 0;
                }
            }
            return true;
        }

        /** Snap start of the selection to a multiple of strides.
          */
        void snapToStrides () {
            for (int i = 0; i < mNDims; i++) {
                mStart[i] = (mStart[i] / mStrides[i]) * mStrides[i];
            }
        }

#ifndef HX_WITHOUT_DEPRECATED
        /// [DEPRECATED] use nDims.
        int rank () const {
            mcenter ("McDataSpace::rank");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return mNDims;
        }

        /// [DEPRECATED] use setSelection
        void restrictSelection (unsigned int dim, int start, int count = 1, int stride = 1) {
            mcenter3 ("McDataSpace::restrictSelection");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            setSelection (dim, start, count, stride);
        }

        /// [DEPRECATED] use restrictSelection
        void restrictDim (unsigned int dim, int start, int count = 1, int stride = 1) {
            mcenter3 ("McDataSpace::restrictDim");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            setSelection (dim, start, count, stride);
        }

        /// [DEPRECATED] use dims(d)
        int dim (int d) const {
            mcenter3 ("McDataSpace::dim");
            mcdebug (MCDL_WARNING, "use of deprecated method");
            return dims(d);
        }

        /// [DEPRECATED] use selectionStart()
        const int* start () const {
            mcenter3 ("McDataSpace::start");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return selectionStart ();
        }

        /// [DEPRECATED] use selectionStart(d)
        int start (int d) const {
            mcenter3 ("McDataSpace::start");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return selectionStart (d);
        }

        /// [DEPRECATED] use selectionStrides()
        const int* strides () const {
            mcenter3 ("McDataSpace::strides");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return selectionStrides ();
        }

        // [DEPRECATED] use selectionStrides (d)
        int strides (int d) const {
            mcenter3 ("McDataSpace::strides");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return selectionStrides(d);
        }

        /// [DEPRECATED] use selectionSize ()
        const int* count () const {
            mcenter3 ("McDataSpace::count");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return selectionSize ();
        }

        /// [DEPRECATED] use selectionSize (d)
        int count (int d) const {
            mcenter3 ("McDataSpace::count");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return selectionSize (d);
        }
#endif

    protected:
        /** init to numdims with dimensions. Initially everthing's selected.
          */
        void init (int numdims, const int* dims) {
            init (numdims);

			if (!numdims) {
                return;
            }
            memcpy (mDims, dims, numdims * sizeof(int));
            memcpy (mSize, dims, numdims * sizeof(int));

			// Need to init additional dimensions as well
            for (int k = mNDims; k < MC_MAX_NDIMS; k++) {
				mDims[k] = mSize[k] = 1;
                mStart[k] = 0;
                mStrides[k] = 1;
            }

            selectAll ();
        }
    private:
        /** Alloc space for numdims.
          */
        void init (int numdims) {
            assert (numdims <= MC_MAX_NDIMS);

            mNDims = numdims;
        }

        int mNDims;
        // dataspace
        int mDims[MC_MAX_NDIMS];
        // selection
        int mStart[MC_MAX_NDIMS];
        int mSize[MC_MAX_NDIMS];
        int mStrides[MC_MAX_NDIMS];
};

/** This describes a multidimensional selection of memory in linear memory.

    size() elements in each dimension of size elemSize() are layed out as follows:

    &elem(x,y,z...) = memory + elemSize() * (x * offsets()[0] + y * offsets()[1] + z * offsets()[2] ...)

    You might use put(), get(), copyFrom() to copy from/to local buffers or other selections. The
    elemSize() has to be the same. No casting is performed.

    You can create a McBytePattern from this McMemorySelection. If you're
    dealing with element wise operations (e.g. cast, map linear, ...) you're
    perhaps not interested in the multidimensional structure of the memory.
    A McBytePattern only describes the location of bytes relative
    to a base pointer. It provides a simple and efficient way
    to iterate over these bytes.

    \todo Do we need this separation? Note: McBytePattern is more capable than a McMemorySelection
           in describing patterns but it doesn't have the notion of dimension.
  */
class MCLIB_API McMemorySelection : public McDataPointer {
    public:
        ///
        McMemorySelection () : McDataPointer () {
            init (0);
        }

        /** Enhance a McDataPointer by a multidimensional selection.
          */
        McMemorySelection (const McDataPointer& buf, int numdims, const int* count, const mclong* offsets)
                    : McDataPointer (buf) {
            init(numdims, count, offsets);
        };

        /** \brief Mem points to element (0, 0, ...) of a dataspace
                   followed by enough memory to contain the complete space.
                   The selection in space is used to calculate memory, count and offsets to
                   construct a McMemorySelection pointing to (start[0], start[1], ...).
          */
        McMemorySelection (McDataPointer mem, const McDataSpace& space) : McDataPointer (mem) {

            const char* buf = rawmemory ();
            buf += space.calcOffset (space.selectionStart ()) * dataElemSize ();
            mclong offsets[MC_MAX_NDIMS];
            int mult = 1;
            for (int d = 0; d < space.nDims (); d++) {
                offsets[d] = mult * space.selectionStrides()[d];
                mult *= space.dims()[d];
            }

            changeDataPtr (buf);

            init (space.nDims(), space.selectionSize(), offsets);
        };

        /** \brief construct a McMemorySelection which is part of a larger one.

            Subselection is a dataspace which with the same space of
            completeselection (completeselection.sameSpace (subselection))
            and has a selection which is included in the selection of
            completeselection (completeselection.includesSelection (subselection)).

            Completemem represent the selection in completeselection in memory.
            It is therefore possible to select a part out of this memory to
            represent subselection in memory.

            This constructor might be helpful in building caches.
          */
        McMemorySelection (const McDataSpace& subselection, const McDataSpace& completeselection
                                    , const McMemorySelection& completemem) : McDataPointer (completemem) {

            mcrequire (completeselection.sameSpace (subselection)
                         && completeselection.includesSelection (subselection)
                         && completemem.selectionElemCount () == completeselection.selectionElemCount ());

            const int numdims = subselection.nDims ();
            mclong offsets[MC_MAX_NDIMS];
            mclong baseoff = 0;
            // calculate the offsets and the start of the subselection in the completemem
            // Note: No checks for validity are perfomed here. It is assumed that everthing's
            // consistent as stated in the mcrequire above.
            for (int i = 0; i < numdims; i++) {
                const int completestrides = completeselection.selectionStrides()[i];
                const int startInCompletestrides = (subselection.selectionStart()[i] - completeselection.selectionStart()[i]) / completestrides;
                const int stridesInCompletestrides = subselection.selectionStrides()[i] / completestrides;

                const mclong completeoffset = completemem.offsets()[i];

                baseoff += startInCompletestrides * completeoffset;
                offsets[i] = stridesInCompletestrides * completeoffset;
            }

            const mclong elemS = completemem.dataElemSize ();

            const char* buf = rawmemory ();
            buf += elemS * baseoff;
            changeDataPtr (buf);
            init (subselection.nDims (), subselection.selectionSize(), offsets);
        }

        ///
        int nDims () const {
            return mNDims;
        }

        ///
        const int* selectionSize () const {
            return mSize;
        }

        // Get the size of the selection in dimension d.
        int selectionSize (int d) const {
            mcenter3 ("McMemorySelection::selectionSize(int)");
            mcrequire (d >= 0 && d < mNDims);

            return mSize[d];
        }

        ///
        const mclong* offsets () const {
            return mOffsets;
        }

        /// Number of elements in this selection.
        mclong selectionElemCount () const {
            if (!mNDims) {
                return 0;
            }
            mclong prod = 1;
            for (int d = 0; d < mNDims; d++) {
                prod *= mSize[d];
            }
            return prod;
        }

        /// put num elems of size dataElemSize starting with elem idx of the selection from buf into our attached memory
        void put (mclong idx, mclong num, const void* buf) const {
            mcrequire (!isConst ());
            putget (1, idx, num, const_cast<void*>(buf));
        };

        /// get num elems of size dataElemSize starting with elem idx of the selection from our buffer and put them into buf
        void get (mclong idx, mclong num, void* buf) const {
            putget (0, idx, num, buf);
        }

        /** copy contents of selection from other selection.

            The elemSize and the selectionSize of both spaces have to be the same.
            No casting is performed.
          */
        void copyFrom (const McMemorySelection& fromspace) const;

#ifndef HX_WITHOUT_DEPRECATED
        /// [DEPRECATED] use nDims ()
        int rank () const {
            mcenter ("McMemorySelection::rank");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return mNDims;
        }

        /// [DEPRECATED] use selectionSize instead
        const int* count () const {
            mcenter ("McMemorySelection::count");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return selectionSize ();
        }
#endif

    private:
        /// used to implement put/get.
        void putget (int put, mclong idx, mclong num, void* buf) const;

    private:
        ///
        void init (int numdims, const int* count, const mclong* offsets) {
            init (numdims);

            // if we don't have offsets calculate the defaults
            mclong dummy[MC_MAX_NDIMS];
            if (!offsets) {
                mclong mult = 1;
                for (int d = 0; d < numdims; d++) {
                    dummy[d] = mult;
                    mult *= count[d];
                }
                offsets = dummy;
            }

            memcpy (mSize, count, numdims * sizeof (int));
            memcpy (mOffsets, offsets, numdims * sizeof (mclong));
        }

        ///
        void init (int numdims) {
            assert (numdims <= MC_MAX_NDIMS);
            mNDims = numdims;
        }

        int mNDims;
        int mSize[MC_MAX_NDIMS];
        mclong mOffsets[MC_MAX_NDIMS];
};

#endif

/// @}
