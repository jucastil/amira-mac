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

/// @addtogroup hxcast hxcast
/// @{
#ifndef HX_FIELD_TO_LATTICE
#define HX_FIELD_TO_LATTICE

#include "HxCastWinDLLApi.h"
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxlatticex/HxLatticeType.h>

template <class OWNER> class HxLatticeProxyTemplate;
template <class OWNER> class HxPartRectLatticeGeomProxyTemplate;
class McDataSpace;
class McMemorySelection;
class McBoundingBox;
class HxLatticeHandle;
class HxLatticeGetQueue;
class McDataType;
class HxDataSetId;

/** \brief  A simple spacetime field for testing purposes.
            It provides a HxField and a HxTransformBox interface.
            The values are evaluated from an analytic expression.
    
 */
class HXCAST_API HxFieldAsLattice : public HxSpatialData
{
  HX_HEADER(HxFieldAsLattice);

  public:
    /// Default constructor (zero field).
    HxFieldAsLattice();

    /// Destructor.
    ~HxFieldAsLattice();

    HxPortIntTextN portResolution;
    
    /// .
    virtual void update();

    void getBoundingBox (float bbox[6]) const;

    int parse(Tcl_Interp* t, int argc, char** argv);
    int autoConnect(HxObject* primary) {
      return portMaster.connect(primary);
    }

  private:
    int nDataSets ();
    
    int nDataVarOfSet (int dataset);
   
    McDataType dataTypeOfSet (int dataset);

    const char* getNameOfSet (int dataset);

    void getRangeOfSet (int dataset, float& min, float& max);

    int trygetRangeOfSet (int dataset, float& min, float& max);

    McDataSpace getDataSpace ();

    McBoundingBox getBoundingBox (const McDataSpace* dataspace);
    
    HxLatticeType latticeType ();

    void getRectPositions (class McRectPositions& pos);

    HxLatticeHandle* getHandle (int datasetcount, const int* datasets);

    HxLatticeGetQueue* getQueue (int datasetcount, const int* datasets);

    void getDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem);

    int trygetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem); 

    void valueOfSet (void* result, int set, const int* indices);

    virtual int saveCreation(FILE* fp, const char* path, int flags) {
      return HxObject::saveCreation(fp, path, flags);
    }

    class HxLatticeHandleImpl;
    friend class HxLatticeHandleImpl;

  private:
    friend class HxLatticeProxyTemplate<HxFieldAsLattice>;
    friend class HxPartRectLatticeGeomProxyTemplate<HxFieldAsLattice>;
};

#endif

/// @}
