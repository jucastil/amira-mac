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

/// @addtogroup hxlatticexbase hxlatticexbase
/// @{
#ifndef HX_LATTICEBASE_H
#define HX_LATTICEBASE_H

#include "HxLatticeXBaseWinDLLApi.h"
#include <mclib/McInterface.h>
#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <mclib/McDArrayQueue.h>
#include <mclib/McAssert.h>
#include <mclib/McDataSpace.h> 
#include <mclib/McBoundingBox.h>
#include "HxLatticeType.h"

class HxLatticeHandle;
class HxNonBlockingLatticeHandle;
class HxLattice;
class HxLatticeGetQueue;

/** \brief Base class for Lattice. Provides all metadata methods.
 */
class HXLATTICEXBASE_API HxLatticeBase : public McInterface {
        MC_ABSTRACT_HEADER(HxLatticeBase);

        ////////////////////////////////////////////////////////////////
        /** \name Basic Interface
         *
         */ 
        //@{
    protected:
        HxLatticeBase (McInterfaceOwner* owner) : McInterface (owner) {};

    public:
        /** \brief Number of basic data sets at each lattice node.
                   These data sets are indexed using numbers from 0 ... nDataSets() - 1.
         
                   Some lattice types may choose to also pass geometry information 
                   through data sets. E.g. a curvilinear lattice will advertise
                   the positions of the points as a data set with datatype float[nDims]
                   and index nDataSets () - 1.
                   See HxLatticeType for descriptions.
         */
        int nDataSets () {
            const int ret = doGetNDataSets();
            mcensure (ret >= 1);
            return ret;
        } 

        /** \brief Returns a human readable name for the requested data set.
         */ 
        const char* getNameOfSet (int datasetidx) {
            mcenter ("HxLatticeBase::getNameOfSet");
            mcrequire (datasetidx >= 0 && datasetidx < nDataSets());
            const char* ret = doGetNameOfSet(datasetidx);
            mcensure (ret);
            return ret;
        }

        /** \brief Number of data values per node in data set.
         */ 
        int nDataVarOfSet (int datasetidx) {
            mcenter ("HxLatticeBase::nDataVarOfSet");
            mcrequire (datasetidx >= 0 && datasetidx < nDataSets());
            const int ret = doGetNDataVarOfSet(datasetidx);
            mcensure (ret >= 1);
            return ret;
        }
        

        /** \brief Type of the data values in data set.
         */
        McDataType dataTypeOfSet (int datasetidx) {
            mcenter ("HxLatticeBase::dataTypeOfSet");
            mcrequire (datasetidx >= 0 && datasetidx < nDataSets());
            return doGetDataTypeOfSet(datasetidx);
        } 

        /// returns a dataspace which could be used to select a part of the data set.
        McDataSpace getDataSpace () {
            return doGetDataSpace ();
        } 
       
        /** \brief A Bounding box in all dimensions. If a dataspace is
                   provided, the McBoundingBox is
                   initialized to a volume containing the hyperslab
                   selected in dataspace.
          */
        McBoundingBox getBoundingBox (const McDataSpace* dataspace) {
            return doGetBoundingBox (dataspace);
        } 
        
        /** Lattice/grid type.

            Depending on the lattice type the geometry information must be accessed in 
            different ways:
                - c_uniform: Dataspace and BoundingBox provide all necessary information
                - c_stacked: 
                - c_curvilinear:  
          */
        HxLatticeType latticeType () {
            return doGetLatticeType();
        } 

    private:
        /// must be provided by the implementation of the interface.
        virtual int doGetNDataSets () = 0;

        /// must be provided by the implementation of the interface.
        virtual const char* doGetNameOfSet (int datasetidx) = 0;

        /// must be provided by the implementation of the interface.
        virtual int doGetNDataVarOfSet (int datasetidx) = 0;

        /// must be provided by the implementation of the interface.
        virtual McDataType doGetDataTypeOfSet (int datasetidx) = 0;

        /// must be provided by the implementation of the interface.
        virtual McDataSpace doGetDataSpace () = 0;

        /// must be provided by the implementation of the interface.
        virtual McBoundingBox doGetBoundingBox (const McDataSpace* dataspace) = 0;

        /// must be provided by the implementation of the interface.
        virtual HxLatticeType doGetLatticeType () = 0;
}; 

#endif

/// @}
