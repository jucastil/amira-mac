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
#ifndef HX_MUTABLE_LATTICE_H
#define HX_MUTABLE_LATTICE_H

#include "HxLattice.h"

class HxMutableLatticeHandle;

/** Mutable version of the HxLattice interface.
 * 
 *  If you're dealing with only one DataSet on the 
 *  lattice it's safe to assume that it is
 *  mutable.
 *
 *  If more than one dataset is defined you have
 *  to check for every single dataset if 
 *  it is mutable.
 */
class HXLATTICEX_API HxMutableLattice : public HxLattice {
        MC_ABSTRACT_HEADER(HxMutableLattice);
    public:
        HxMutableLattice (McInterfaceOwner* owner) : HxLattice (owner) {}

        /** check if a specific dataset is mutable.
         */
        int isMutableDataSet (int datasetidx) {
            return doIsMutableDataSet (datasetidx);
        } 
        
        /** Get a HxMutableLatticeHandle to write to a window.
            This is only possible at the full resolution, no filtering is available. 
          */
        HxMutableLatticeHandle* getMutableHandle (int datasetcount, const int* datasetidxs) {
            return doGetMutableHandle (datasetcount, datasetidxs);
        } 

        /** Stores the data at buf described by memspace in the selection described by space.
          */
        void putDataOfSet (int datasetidx, const McDataSpace& destspace, const McMemorySelection& srcmem) {
            doPutDataOfSet (datasetidx, destspace, srcmem);
        } 

        ////////////////////////////////////////////////////////////////
        /** \name Convenience Methods and Wrappers
         */
        //@{
    public:
        /** Wrapper to default handle.
          */
        HxMutableLatticeHandle* getMutableDataHandle () {
            const int sel = 0;
            return getMutableHandle (1, &sel);
        }

        /// wrapper
        void putData (const McDataSpace& space, const McMemorySelection& memspace) {
            putDataOfSet (0, space, memspace);
        };
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
        void putDataOfSetUsingHandle (int dataset, const McDataSpace& destspace, const McMemorySelection& srcmem);

        //@}
        ////////////////////////////////////////////////////////////////

    private:
        virtual int doIsMutableDataSet (int datasetidx) = 0;
        
        virtual HxMutableLatticeHandle* doGetMutableHandle (int datasetcount, const int* datasetidxs) = 0;

        virtual void doPutDataOfSet (int datasetidx, const McDataSpace& destspace, const McMemorySelection& srcmem) = 0;
};
#endif

/// @}
