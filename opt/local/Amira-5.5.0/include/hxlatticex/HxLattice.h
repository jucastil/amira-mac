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

/// @addtogroup hxlatticex hxlatticex
/// @{
#ifndef HX_LATTICE_H
#define HX_LATTICE_H

#include "HxLatticeXWinDLLApi.h"
#include <hxfield/HxCoordType.h>
#include <mclib/McInterface.h>
#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <mclib/McDArrayQueue.h>
#include <mclib/McAssert.h>
#include <mclib/McDataSpace.h> 
#include <mclib/McBoundingBox.h>
#include <hxlatticexbase/HxLatticeBase.h>

class HxLatticeHandle;
class HxNonBlockingLatticeHandle;
class HxLattice;
class HxLatticeGetQueue;

/** \brief HxLattice is the interface to a multidimensional lattice
    which may carry more than one data sets. 
    See \ref hxlatticex_Lattice for an introduction to the
    basic concepts.

    No direct access is provided. You must use one of
    the access methods:
       - You may use a HxLatticeHandle as a window to
         the data. Normally this way is the simplest and
         most efficient way because the
         implementation is free to choose the data layout
         which might help in caching the data.
       - You may use getData to request
         the HxLattice to fill a provided memoryblock with data.
         This way provides access to downsampled/supersampled
         versions of the data. It is more general but normally
         it is slower and more complicated.
       - Use a HxLatticeGetQueue to queue a bunch of 
         requests and retrieve them asynchronously. 
         By using this way the underlying 
         implementation could use threads to 
         deliver the data or it could try to optimize
         data fetching over all blocks.
       - A deprecated way is to use valueOfSet to get
         the value at a single position.

    Similar ways are available to request the coordinates.
    They are just special data sets. 
    
    This is the read only version. If you intend to modify the 
    data values, you have to use the HxMutableLattice.
  */
class HXLATTICEX_API HxLattice : public HxLatticeBase {
        MC_ABSTRACT_HEADER(HxLattice);

        ////////////////////////////////////////////////////////////////
        /** \name Basic Interface
         *
         */ 
        //@{
    protected:
        HxLattice (McInterfaceOwner* owner) : HxLatticeBase (owner) {};

    public:
        /** \brief Returns the range of the data values.
         *
         *  The default implementation performs a scan over
         *  all data which might be quite expensive in
         *  case of external data. The result
         *  will be cached until the data object changes.
         *  You may avoid calling this method
         *  if you have useful defaults, e.g byte [0, 255].
         *
         *  You can use HxLattice::DefaultComputeRange
         *  to implement this method.
         */
        void getRangeOfSet (int datasetidx, float& min, float& max) {
            mcenter ("HxLattice::getRangeOfSet");
            mcrequire (datasetidx >= 0 && datasetidx < nDataSets());
            doGetRangeOfSet (datasetidx, min, max);
        }

        /** \brief Get a HxLatticeHandle to read in a window.
         *
         *          The array (datasetcount, datasets) selects
         *          the data sets which will be available through
         *          this handle. It also fixes the numbering 
         *          of the data sets in the handle, e.g.:
\code
///... TODO change this
const int sel[] = {0, DATASET_POSITION_XYZ, DATASET_TIME}
HxLatticeHandle* handel = lat->getHandle (3, sel, MAP_FITER_NONE);
...
McMemorySelection* selectionset = handle->lockReadable ();
McMemorySelection& data = selectionset[0];
McMemorySelection& pos = selectionset[1]; 
McMemorySelection& time = selectionset[2];
handle->unlock (); // unlocks all
\endcode

         */
        HxLatticeHandle* getHandle (int datasetcount, const int* datasetidxs) {
            mcenter ("HxLattice::getHandle");
            HxLatticeHandle* handle = doGetHandle (datasetcount, datasetidxs);
            mcensure (handle);
            return handle;
        } 

        /** Copy data to the memory at buf. 
           
            \param srcdataset From which data set to retrieve. 
            \param srcspace Describes the selection in the data set
            \param destmem Describes the buffer (pointer and memorylayout).
            \param getopt describes options which might be used during the copy 
                          e.g. if a hyperslab with strides (means every ith point)
                          is selected, this points could be subsampled which
                          might cause aliasing effects. A better approach could
                          calculate a properly downsampled version of the data set
                          and take the values from there.
          */
        void getDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) {
            doGetDataOfSet (srcdatasetidx, srcspace, destmem);
        } 

        /** \brief Get access to single elements. You SHOULD avoid to use this
         *      method because it might be very inefficient in runtime and required space
         *      though it might be very tempting.
         *
         *      You might use the DefaultValueHandler to implement this method.
         */
        void valueOfSet (void* result, int datasetidx, const int* indices) {
            doGetValueOfSet (result, datasetidx, indices);
        } 

        //@}
        ////////////////////////////////////////////////////////////////



        ////////////////////////////////////////////////////////////////
        /** \name Convenience Methods and Wrappers
         *
         */
        //@{
    public: 
        int nDims () {
            const McDataSpace ds = getDataSpace ();
            return ds.nDims ();
        }
           
        using HxLatticeBase::getBoundingBox;

        /** \brief Number of data values per node. 
         *
         *      A convenience wrapper to the default data set. 
         */
        McBoundingBox getBoundingBox () {
            return getBoundingBox (0);
        }

        int nDataVar () {
            return nDataVarOfSet (0);
        }

        /// Wrapper to the default data set. 
        McPrimType primType () {
            const McDataType ty = dataTypeOfSet (0);
            mcassert (ty.isMcPrimType ());
            return ty.asMcPrimType();
        }

        HxCoordType coordType () {
            mcenter ("HxLattice::coordType");

            HxLatticeType id = latticeType ();
            if (!id.isHxCoordType()) {
                mcdebug (MCDL_CRIT, "HxLatticeType is not a HxCoordType but accessed through legacy wrapper.");
            }
            return id.asHxCoordType();
        }

        /// Wrapper to the default data set. 
        void getRange (float& min, float& max) {
            getRangeOfSet (0, min, max);
        }

        /** Wrapper to default handle.
          */
        HxLatticeHandle* getDataHandle () {
            const int sel = 0;
            return getHandle (1, &sel);
        }

        /** Wrapper to default handle.
          */
        HxLatticeHandle* getHandleOfSet (int datasetidx) {
            return getHandle (1, &datasetidx);
        }

        /// wrapper
        void getData (const McDataSpace& space, const McMemorySelection& memspace) {
            getDataOfSet (0, space, memspace);
        }

        //@}
        ////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////
        /** \name Helpers you might want to use to implement your 
                  the interface
         */
        //@{
    public:


        /** \brief Implements getDataOfSet using a handle. You might
                    want to use this method if you alread implemented
                    a Handle and don't want to implement an optimized
                    version of getDataOfSet.
          */
        void getDataOfSetUsingHandle (int dataset, const McDataSpace& space, const McMemorySelection& memselection);

        class DefaultComputeRange;
        class DefaultGetQueueHandler;
        class DefaultValueHandler;
        //@}
        ////////////////////////////////////////////////////////////////

    private:
        virtual void doGetRangeOfSet (int datasetidx, float& min, float& max) = 0;
        virtual HxLatticeHandle* doGetHandle (int datasetcount, const int* datasetidxs) = 0;
        virtual void doGetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) = 0;
        virtual void doGetValueOfSet (void* result, int datasetidx, const int* indices) = 0;
};



/** \brief Non-blocking interface to HxLattice. 
            It may be available in addition to an HxLattice.

    This interface is experimental and likely to change or to be removed. 
    See the \ref hxlatticex_LatticeTech "technote on Lattice" for some details.
  */
class HXLATTICEX_API HxNonBlockingLattice : public HxLatticeBase {
        MC_ABSTRACT_HEADER(HxNonBlockingLattice);

        ////////////////////////////////////////////////////////////////
        /** \name Basic Interface
         *
         */ 
        //@{
    protected:
        HxNonBlockingLattice (McInterfaceOwner* owner) : HxLatticeBase (owner) {};

    public:
        /** \brief Nonblocking getRangeOfSet().
        
            \param dataset the data set the range is requested of 
            \retval min Minimum of the range
            \retval max Maximum of the range
            \return 0 If range is not available immediately, min and max are unmodified.
            \return 1 If range is available immediately, min and max are set.
          */
        int trygetRangeOfSet (int datasetidx, float& min, float& max) {
            mcenter ("HxLattice::trygetRangeOfSet");
            mcrequire (datasetidx >= 0 && datasetidx < nDataSets());
            const int res = doTrygetRangeOfSet (datasetidx, min, max);
            mcensure (res == 0 || res == 1);
            return res;
        } 

        /** Nonblocking getDataOfSet ().

            \return 0 If data is not available immediately, nothing was done.
            \return 1 If data is available immediately, data were copied to destmem.
          */
        int trygetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) {
            mcenter ("HxLattice::trygetDataOfSet");
            const int ret = doTrygetDataOfSet (srcdatasetidx, srcspace, destmem);
            mcensure (ret == 0 || ret == 1);
            return ret;
        }

        /** \brief Get asynchronous access to the data. 
                   If asynchronous access is not available the method returns 0.

            \todo question: Should the Scanner stuff be merged with the queues?
                    e.g. something like queue->optimizeBlocks () which
                         could reorder and split the request to
                         match some requirements (e.g. block size, memory consumption...)
          */
        HxLatticeGetQueue* getQueue (int datasetcount, const int* datasetidxs) {
            return doGetQueue (datasetcount, datasetidxs);
        } 

        /** Return a handle that provides trylockReadable method.
          */
        HxNonBlockingLatticeHandle* getHandle (int datasetcount, const int* datasetidxs) {
            mcenter ("HxLattice::getHandle");
            HxNonBlockingLatticeHandle* ret = doGetHandle (datasetcount, datasetidxs);
            mcensure (ret);
            return ret;
        } 

    protected:
        /** \brief Implements trygetDataOfSet using a handle. You might
                    want to use this method if you alread implemented
                    a Handle and don't want to implement an optimized
                    version of getDataOfSet.
          */
        int trygetDataOfSetUsingHandle (int dataset, const McDataSpace& space, const McMemorySelection& memselection);


    private:
        virtual int doTrygetRangeOfSet (int datasetidx, float& min, float& max) = 0;
        virtual int doTrygetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) = 0;
        virtual HxLatticeGetQueue* doGetQueue (int datasetcount, const int* datasetidxs) = 0;
        virtual HxNonBlockingLatticeHandle* doGetHandle (int datasetcount, const int* datasetidxs) = 0;
};

#endif

/// @}
