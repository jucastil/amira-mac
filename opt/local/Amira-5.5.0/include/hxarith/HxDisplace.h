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
#ifndef _HXDISPLACE_H_
#define _HXDISPLACE_H_

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxtime/HxPortTime.h>

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


/// This module computes the magintude of a vector field.
class HXARITH_API HxDisplace : public HxCompModule {

  HX_HEADER(HxDisplace);

  public:

    /// Constructor.
    HxDisplace (void);

    /// Label for amount of vectors
    HxPortInfo  portInfo;

    /// Choose a scale factor. Grid points will be moved along the scaled vectors.
    HxPortTime portScale;

    /// Button for applying deformation
    HxPortDoIt  portDoIt;

    /// Update method
    virtual void  update (void);

    /// Compute method.
    virtual void compute (void);

    /// Save state
    void savePorts(FILE* fp);

    /// Tcl command interface
    int parse(Tcl_Interp* t, int argc, char **argv);

  protected:

    int nVectors;
    bool displacementUpToData;
    bool useOldGrid;

    virtual ~HxDisplace (void);

    //void regScalarField (HxSpatialData * data);
    void computeSurface (HxSpatialData * data);
    void computeTetraGrid (HxSpatialData * data);
    void computeHexaGrid (HxSpatialData * data);

    void displace (McDArray<McVec3f>& points, float * vectors);

    virtual int canCreateData (HxData * data, McString& createCmd);
};

#endif

/// @}
