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

/// @addtogroup hxarith hxarith
/// @{
#ifndef _HxMagnitude_h_
#define _HxMagnitude_h_

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>

#if 0
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoSeparator.h>
#endif

#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxTetraScalarField3.h>
#include <hxfield/HxHexaScalarField3.h>
#include <hxsurface/HxSurfaceScalarField.h>

#include <hxarith/HxArithWinDLLApi.h>


class HxSurfaceField;
class HxHexaData;
class HxTetraData;
class HxLattice3;

/// This module computes the magnitude of a vector field.
class HXARITH_API HxMagnitude : public HxCompModule {

  HX_HEADER(HxMagnitude);

  public:

    /// Constructor.
    HxMagnitude (void);

    /// Automatically establish connection to field
    int autoConnect(HxObject* primary);

    /// Label for amount of vectors
    HxPortInfo  portInfo;

    /// Choose to compute magnitude of vector, normal or tangential
    HxPortRadioBox portMode;

    /// Button for starting the computation
    HxPortDoIt  portDoIt;

    /// Update method
    virtual void  update (void);

    /// Compute method.
    virtual void compute (void);

  protected:

    int         nDataElements;
    int         nDataVar;
    void*       srcDataPtr;
    McPrimType  primType;

    HxHexaData*     hex;
    HxTetraData*    tet;
    HxLattice3*     lattice;
    HxSurfaceField* surffield;

    virtual ~HxMagnitude (void);

    HxRegScalarField3*    regScalarField (HxSpatialData* data);
    HxSurfaceScalarField* surfaceScalarField (HxSpatialData* data);
    HxTetraScalarField3*  tetraScalarField (HxSpatialData* data);
    HxHexaScalarField3*   hexaScalarField (HxSpatialData* data);

    static void magnitude (float* src, float* dst, int nVectors, int nDim);

    virtual int canCreateData (HxData* data, McString& createCmd);
};

#endif

/// @}
