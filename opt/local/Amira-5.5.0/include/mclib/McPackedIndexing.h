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
#ifndef MC_PACKED_INDEXING_H
#define MC_PACKED_INDEXING_H

#include "McDArray.h"
#include "McBitfield.h"
#include "McPrimType.h"
#include "McWinDLLApi.h"

/** If you think of a lattice populated with sparse data. Often there
    is the need to calculate different things, but only in the object
    and not in the background. This class provides the possibilty to
    pack the data in a convenient, obvious and fast way.
    First construct one instance with the size of the sparse data
    array and the datavalues. Afterwards use index() to convert
    normal linear indexing to indizes in the packed array.
    The minimum size of the container, that contains the packed data
    is returned by getNumPackedElems ().
    Example:
    @code
        int size;
        unsigned char sparseData[size];

        McPackedIndexing packer (sparseData, size);
        McDArray<int> field1 (idx->getNumPackedElems ());
        McBitfield mask (idx->getNumPackedElems ());

        for (int i = 0; i < size; i++) {
            if (sparseData[size]) {
                int value = ...;
                field1[packer.index (i)] = value;
                mask.set (packer.index (i));
            }
        }
    @endcode

    As you can see the packing of the data must be explicitly coded

    \note An object of this class needs about (1 + 1/256) bytes for
            each element of the unpacked array.
  */
class MCLIB_API McPackedIndexing {
    public:
        /** \brief Construct with data given as a array of unsigned char.
          *        Values != 0 will be available.
          */
        McPackedIndexing (const unsigned char* dat, int size);
        /** \brief Construct using a bitfield.
          */
        McPackedIndexing (McBitfield& dat);

        /** Get the number of elements in the packed array.
          */
        int getNumPackedElems () {
            return numData;
        };
        /** Get the number of elements in the packed array.
          */
        int getPackedSize () {
            return numData;
        };
        /** Map from a linear index to a index to the packed array.
         *
         *  \todo This should return -1 if the index is not valid to
         *          be compatible with McSuperPackedIndexing. Right
         *          now this is not.
          */
        int index (int linear) {
            assert (data[linear]);
            int block = linear/256;
            return (blockStartIdx[block] + offsetInBlock[linear]);
        };

//        int getLinear (int packed);
// ist teuer, weiss noch nicht, ob man das braucht.
    private:
        McDArray<int> blockStartIdx;
        McDArray<unsigned char> offsetInBlock;
        McBitfield data;
        int numData;
};

/** \brief This class is like McPackedIndexing. It uses less space but more time.

           The implementation builds a Run Length Encoding of the input data
           and searches the indices in this RLE.
  */
class MCLIB_API McSuperPackedIndexing {
        // we use a block size of 255 because one rle run can
        // only encode 255 elements.
        enum Constants {
            BlockSize = 255
        };
    public:
        /** \brief Construct with data given as a array of unsigned char.
          *        Values != 0 will be available.
          */
        McSuperPackedIndexing ();

        /** \brief append index space
         */
        void appendIndexSpace (const unsigned char* dat, mclong size);

        /** \brief return the number of element in the original array.
         */
        int getNumElems () {
            return numInputElems;
        };
        /** Get the number of elements in the packed array.
          */
        int getNumPackedElems () {
            return numData;
        };
        /** Get the number of elements in the packed array.
          */
        int getPackedSize () {
            return numData;
        };
        /** Map from a linear index to a index to the packed array.
         *  If linear index is not valid, -1 will be returned.
          */
        int index (int linear) {
            // search through rle in the block until the idx is found
            int block = linear / BlockSize;
            int idxInBlock = linear % BlockSize;

            mclong packedidx = blockStartIdx[block];

            mclong rleidx = blockStartRle[block];
            mcuint8 rlestate = 0; // each rle block starts with a 0-run

            int pos = 0;
            for (;;) {
                mcuint8& count = rle[rleidx];
                if (pos + count > idxInBlock) {
                    packedidx += idxInBlock - pos;
                    break;
                }
                pos += count;
                if (rlestate) {
                    // add to packedindx only if we're in a 1-run
                    packedidx += count;
                }
                rlestate = !rlestate;
                rleidx++;
            }

            return (rlestate) ? packedidx : -1;
        };

        bool valid (int linear) {
            // search for the index in the block
            // if it is in a 0-run the index is not valid in a packed array
            int block = linear / BlockSize;
            int idxInBlock = linear % BlockSize;

            mclong rleidx = blockStartRle[block];
            mcuint8 rlestate = 0; // each rle block starts with a 0-run

            int pos = 0;
            for (;;) {
                mcuint8& count = rle[rleidx];
                if (pos + count > idxInBlock) {
                    break;
                }
                pos += count;
                rlestate = !rlestate;
                rleidx++;
            }

            return rlestate!=0;
        }

//        int getLinear (int packed);
// ist teuer, weiss noch nicht, ob man das braucht.
    private:
        McDArray<mclong> blockStartIdx;
        McDArray<mclong> blockStartRle;
        McDArray<mcuint8> rle;
        mclong numData;
        mclong numInputElems;

        mcuint8 lastValue;
};

template<class ARRAY, class VALUE>
class McPackedArray {
public:
    McPackedArray(ARRAY& a, McPackedIndexing& p) : array(a), packer(p) {}

    const VALUE& operator[] (int i) const {
	return array[packer.index(i)];
    }

    VALUE& operator[] (int i) {
	return array[packer.index(i)];
    }
private:
    ARRAY& array;
    McPackedIndexing& packer;
};

#endif

/// @}
