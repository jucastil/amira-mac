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
#ifndef MC_RAWDATA_H
#define MC_RAWDATA_H

#include <stdio.h>
#include <float.h>

#include "McWinDLLApi.h"
#include "McPrimType.h"
#include "McTypedPointer.h"
#include "McProgressInterface.h"
#include "McHandle.h"

/** Provides a set of utility functions for operating on (3D) raw data.
    Among the functions provided by this class is type casting, linear
    mapping, down sampling, byte swapping, flipping, and cropping. */

class McHistogram;

class MCLIB_API McRawData
{
  public:
    /** Copy n values from src to dst. If the destination type is
        smaller than the source type, values are clipped. For example,
        if the dst type is mc_uint8 and the src type is mc_int16,
        negative values will be set to 0 and values larger than 255
        will be set to 255. */
    static void memcpy(McTypedPointer dst,McTypedPointer src,mclong n);

    /** Set n values at dst to val (val is rounded for integer types). */
    static void memset(McTypedPointer dst,double val,mclong n);

    /** Set n values at dst to val. */
    static void memset(McTypedPointer dst,int val,mclong n);

    /** Copy n values from src to dst and map them by the expression
        x'=scale*(x+off). The calculation is performed using double
        variables if either dst or src is of type double. Otherwise
        (if neither src nor dst is double) float calculations are
        used.  The result is casted to the correct destination
        type and clipped if necessary. */
    static void mapLinear(McTypedPointer dst,McTypedPointer src,
                          mculong n,double off,
                          double scale);

    /** Copy n values from src to dst and map them by the expression
        x'=scale*(x+off). All calculations will be done with integer
        arithmetic if src and dst both are integer data types (like
        i.e. shorts). */
    static void mapLinear(McTypedPointer dst,McTypedPointer src,
                   mculong n,int off, int scale);

    /** Downsample 3D array of size dimsx*dimsy*dimsz by averaging
        nx*ny*nz values.  All calculations will be done with integer
        arithmetic if src and dst both are integer data types (like
        i.e. shorts). Currently dst and src are to be of the same data
        type. !*/
    static void downSample3D(void* dst,McTypedPointer src,
                             mculong dimsx,mculong dimsy,mculong dimsz,int nx,int ny,int nz,
                             McProgressInterface* progress=0);

    /** Same as downSample3D for nDataVar. !*/
    static void downSample3DN(void* dst,McTypedPointer src,
                             mculong dimsx,mculong dimsy,mculong dimsz,int nx,int ny,int nz,
                             int nDataVar, McProgressInterface* progress=0);


    /** Downsample using a maximum filter. */
    static void downSampleMaxFilterComponents3DN(void* dst,McTypedPointer src,
                             mculong dimsx,mculong dimsy,mculong dimsz,int nx,int ny,int nz,
                             int nDataVar, McProgressInterface* progress=0);

    /** Downsample 3D array of size dimsx*dimsy*dimsz by taking
        the nearest value of original data set. All calculations
        will be done with integer arithmetic if src and dst both are
        integer data types (like i.e. shorts). Currently dst and src
        are to be of the same data type. !*/
    static void downSampleLabels3D(void* dst,McTypedPointer src,
                             mculong dimsx,mculong dimsy,mculong dimsz,int nx,int ny,int nz,
                             McProgressInterface* progress=0);


    /** Does kind of a rotation of 90 degrees of a 3D array. /c didx[i]
        tells, at which position the index i has been before. For example,
        didx[] = {1,2,0} would mean xyz becomes yzx. The 3 values in the
        array /c dims give the size of the initial array. The dims values
        are swapped also. For example, if initially dims = {512,512,200}
        and didx[] = {1,2,0} then on exit you get dims = {512,200,512}.

        This method allocates memory in order to temporarily store a copy
        of the data array to be swapped. If not enough memory can be
        allocated the data is not swapped, dims is not modified, and false
        is returned. If the method succeeds true is returned. */
    static bool swapDims(McTypedPointer src, int dims[], const int* didx,
        int nChannels=1);

    /** Compute value range of n values. The result is stored in
        mini and maxi.
        If @param discardUndefinedValue is set to true, 
        @param undefinedValue will be used to avoid this value during range computation*/
    static void getRange(McTypedPointer data, mculong n,
                         float& mini, float& maxi, McProgressInterface* progress=0,
                         bool discardUndefinedValue = false,
                         float undefinedValue = -FLT_MAX);

    /** Compute histogram of n values.
        @param inData Typed data pointer used to calculate the histogram
        @param n Length of \c inData e.g.   
        @param numBins Number of bins (number of bins of the returned histogram can be equal or less).
        @param min Minimum data value. For some data types e.g. int, float and double the dataset's
               min, max values need to be precomputed before calculating the actual histogram in order to scale the
               values. If both, min and max pointers are given, these values will be used instead of
               recalculating them again.
        @param Maximum data value (@see min).
        @param progress
        @return McHandle of a McHistogram containing the result histogram.
    */
    static McHandle<McHistogram> getHistogram(McTypedPointer inData, mculong n,
                             unsigned int numBins, float* min=0, float* max=0, McProgressInterface* progress=0);

    /** Check whether n values are all the same. 
    */
    static bool isConstant(McTypedPointer data, mculong n);

    /** Converts (if necessary) big-endian data to to native machine format.
    */
    static void fromBigEndian(McTypedPointer dst, size_t n);

    /** Converts (if necessary) little-endian data to to native machine format.
    */
    static void fromLittleEndian(McTypedPointer dst, size_t n);

    /** Read n words in big-endian byte order from file, do byte swapping
        if necessary. */
    static size_t readBigEndian(McTypedPointer dst, size_t n, FILE* fp);

    /** Write n words in big-endian byte order to file, do byte swapping
        if necessary. */
    static size_t writeBigEndian(McTypedPointer dst, size_t n, FILE* fp);

    /** Read n words in little-endian byte order from file, do byte swapping
        if necessary. */
    static size_t readLittleEndian(McTypedPointer dst, size_t n, FILE* fp);

    /** Write n words in little-endian byte order to file, do byte swapping
        if necessary. */
    static size_t writeLittleEndian(McTypedPointer dst, size_t n, FILE* fp);

    /// Swap byte order in nn words.
    static void swapBytes(McTypedPointer dp, mculong nn);

    /// Swap byte order in nn words of length 2 bytes.
    static void swapBytesWord2(void* dp, mculong nn);

    /// Swap byte order in nn words of length 4 bytes.
    static void swapBytesWord4(void* dp, mculong nn);

    /// Swap byte order in nn words of length 8 bytes.
    static void swapBytesWord8(void* dp, mculong nn);

    /** Flips the slices of a 3D array in x, y, or z-direction, depending
        on whether @c dimension is 0, 1, or 2. Returns 1 on success and 0
        otherwise. */
    static int flip(void* data, int sizeOfAnElement, const int dims[3],
        int dimension);

    /** Crops a 3D array. The array may also be enlarged. In this case
        the last slice in the direction in which the array is to be
        enlarged is replicated (default <tt>replicate  NULL</tt>)
        or new slices with the imageValue in @c replicate are created.
        In any case a realloc() is performed on data if the required amount
        of memory changes. Neither one of the original dimensions nor
        one of the new ones may be zero. On success 1 is return, otherwise 0. */
    static int crop(void*& data, int sizeOfAnElement, int dims[3],
        const int newMin[3], const int newMax[3], const void* replicate = NULL);

    /** This is a fail-safe version of ::read. It calls ::read repeatedly
        until the desired number of bytes have been read. A single call
        to ::read may return less bytes. On Windows this happens frequently
        when reading from a network share. */
    static mcint64 read(int handle, void* buffer, mcint64 count, McProgressInterface *progress=0);

    /** Fail-safe version of fread(). When using fread() to read data
        from a file it might happen that less bytes than requested are
        read and that fread() has to be called multiple times in order to
        read all data. In particular, this happens when reading a large
        block of data from a mounted network drive on Windows. This
        method automatically tries to call fread() multiple times in order
        to read all data. This approach may still fail due to other errors.
        The return value and the error behaviour are the same as for the
        standard fread(). */
    static size_t fread(void* buffer, size_t size, size_t count, FILE* fp, McProgressInterface *progress=0);

    /** Fail-safe version of fwrite(). When using fwrite() to write data
        to a file it might happen that less bytes than requested are
        written and that fwrite() has to be called multiple times in order to
        write all data. In particular, this happens when writng a large
        block of data to a mounted network drive on Windows. This
        method automatically tries to call fwrite() multiple times with
        smaller blocksizes in order to write all data. This approach may
        still fail due to other errors. The return value and the error
        behaviour are the same as for standard fwrite(). */
    static size_t fwrite(void* buffer, size_t size, size_t count, FILE* fp, McProgressInterface *progress=0);
};

#endif

/// @}
