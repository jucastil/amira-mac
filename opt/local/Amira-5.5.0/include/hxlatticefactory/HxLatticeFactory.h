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

/// @addtogroup hxlatticefactory hxlatticefactory
/// @{
#ifndef HX_LATTICE_FACTORY_H
#define HX_LATTICE_FACTORY_H

#include "HxLatticeFactoryWinDLLApi.h"

class HxLatticeHandle;
class McRectPositions;
class HxData;
class McDataType;
class McDataSpace;
class McBoundingBox;
class HxLatticeType;

extern "C" {
    /** Note: to facilitate legacy code, we don't use the new classes (McDataType, HxLatticeType...) here.
              We just pass POD. Take care to do the right thing there.
      */
    typedef HxData* (*create_hxlattice_t) (   int nDataVar
                                            , const char* datatype       // this is a McDataType
                                            , int numdims
                                            , const int* dims    // dims[numdims]
                                            , const float* bbox  // bbox[2 * numdims]
                                            , const char* latticeType    // this is a HxLatticeType
                                            , McRectPositions* rectpos
                                            , HxLatticeHandle* arbpos
                                          );
}

/** Create a dataobject with a HxMutableLattice interface.
        
    Use it like  

\code
    HxData* res = HxLatticeFactory::create (nDataVar, McDataType(primType), McDataSpace(3, dims), McBoundingBox (3, bbox), HxLatticeType::c_uniform, 0);
    if (!res) {
        theMsg->printf("error creating result");
        return;
    }
    HxMutableLattice* reslat = static_cast<HxMutableLattice*> (res->getInterface (HxMutableLattice::getClassTypeId ()));
    if (!reslat) {
        mcdebug (MCDL_CRIT, "internal error");
    }
\endcode
  */
class HXLATTICEFACTORY_API HxLatticeFactory {
    public:
        /** Create a dataobject with a HxMutableLattice interface.
        
           \param nDataVar     Number of values per position.
           \param datatype     type
           \param space        Requested McDataSpace
           \param bbox         McBoundingBox of the data
           \param latticeType  The coordinate type of the lattice.
           \param rectpos      The factory will ask rectpos for rectilinear positions
           \param arbpos       Arbirary positions are passed along using positions.
                               The format depends on the latticeType.
           \param contentTypeFlag tells create() to favor a specific data type.
                               1 tells create() to favor HxComplexVectorField.
                               2 tells create() to favor HxRegSym2TensorField3.

           \return Pointer to instance.
           \return 0 in case of failure.

           \todo replace return type with HxMutableLattice
         */
        static HxData* create (   int nDataVar
                                , McDataType datatype
                                , const McDataSpace& space
                                , const McBoundingBox& bbox
                                , HxLatticeType latticeType
                                , McRectPositions* rectpos
                                , HxLatticeHandle* arbpos
                                , int contentTypeFlag = 0
                              );

};

#endif

/// @}
