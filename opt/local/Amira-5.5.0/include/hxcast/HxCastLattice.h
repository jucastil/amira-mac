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
#ifndef HX_CAST_LATTICE
#define HX_CAST_LATTICE

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortToggleList.h>
#include <hxfield/HxLabelLattice3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxRegColorField3.h>
#include <hxcolor/HxPortColormap.h>
#include "HxCastWinDLLApi.h"

/** Cast a HxLattice similar to HxCastLattice */
class HXCAST_API HxCastLattice : public HxCompModule {

  HX_HEADER(HxCastLattice);
  
  public:
    /// Constructor.
    HxCastLattice();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Info port to display data type of source.
    HxPortInfo portDataInfo;

    /// New data type: 0=byte, 1=short, 2=ushort, 3=int, 4=float, 5=doubble, 6=labels.
    HxPortMultiMenu portDataType;

    /// Defines  scaling: X'(x,y,z) = SCALE * ( X(x,y,z) + OFFSET )
    HxPortFloatTextN portScaling;

    /// Do it button.
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    // Destructor.
    ~HxCastLattice();

    virtual int canCreateData(HxData* data, McString& createCmd);
};
#endif

/// @}
