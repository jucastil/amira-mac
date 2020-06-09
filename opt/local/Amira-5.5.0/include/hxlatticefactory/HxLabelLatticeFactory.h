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
#ifndef HX_LABEL_LATTICE_FACTORY_H
#define HX_LABEL_LATTICE_FACTORY_H

#include "HxLatticeFactoryWinDLLApi.h"
#include <mclib/McPrimType.h>
#include <hxfield/HxCoordType.h>

class HxLatticeHandle;
class McRectPositions;
class HxData;

/** Create a dataobject with a HxMutableLabelLattice interface. So far it has more or less only been copied from the HxLatticeFactory.
        
    Use it like  

\code
    HxData* res = HxLabelLatticeFactory::create (1, dims4, McPrimType (t), c_uniform, bbox8, 0); 
    if (!res) {
        theMsg->printf("error creating result");
        return;
    }
    HxMutableLattice* reslat = static_cast<HxMutableLabelLattice*> (res->getInterface (HxMutableLabelLattice::getClassTypeId ()));
    if (!reslat) {
        mcdebug (MCDL_CRIT, "internal error");
    }
\endcode
  */
class HXLATTICEFACTORY_API HxLabelLatticeFactory {
    public:
        /** Create a dataobject with a HxMutableLabelLattice interface.
        
           \param nDataVar   Number of values per position.
           \param dims4      Dimensions.
           \param primType   McPrimType of data values.
           \param coordType  c_uniform, c_stacked, c_rectilinear, c_curvilinear are allowed.
           \param bbox       Bounding box.
           \param rectpos    The factory will ask rectpos for rectilinear positions
           \param arbpos     Arbirary positions are passed along using positions.
                             The format depends on the latticeType.

           
           \return Pointer to instance.
           \return 0 in case of failure.

           \todo fix doc
         */
        static HxData* create (   const McDataSpace& space
                                , const McBoundingBox& bbox
                                , HxLatticeType latticeType
                                , McRectPositions* rectpos
                                , HxLatticeHandle* arbpos
                              );
};

#endif

/// @}
