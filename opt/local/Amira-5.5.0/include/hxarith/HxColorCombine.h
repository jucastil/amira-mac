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
#ifndef HX_COLOR_COMBINE
#define HX_COLOR_COMBINE

#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxUniformColorField3.h>
#include <hxfield/HxLattice3.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxCompModule.h>
#include <hxarith/HxArithWinDLLApi.h>

/// Computes a color field by combining multiple other scalar or color fields.

class HXARITH_API HxColorCombine : public HxCompModule
{
  HX_HEADER(HxColorCombine);

  public:
    /// Default constructor.
    HxColorCombine();

    /// Constructor.
    HxColorCombine(const int dims[3], void* data=0);

    /// Automatically establish connection to field
    int autoConnect(HxObject* primary);

    /// First input field (required).
    //HxConnection portSourceField1;

    /// Second input field (optional).
    HxConnection portSourceField2;

    /// Third input field (optional).
    HxConnection portSourceField3;

    /// Colormap applied to first input field (if this is a scalar field).
    HxPortColormap portColormap1;

    /// Colormap applied to second input field (if this is a scalar field).
    HxPortColormap portColormap2;

    /// Colormap applied to third input field (if this is a scalar field).
    HxPortColormap portColormap3;

    /// How to combine RGBA values: 0=alpha weighted, 1=average, 2=add.
    HxPortRadioBox portComposeMode;

    /// for fields of equal size: combine them regularly or interpret them as RGB, respectively
    HxPortRadioBox portColorMode;

    /// Provides button to start actual computation.
    HxPortDoIt portDoIt;

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    /// Destructor.
    virtual ~HxColorCombine();

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    HxLattice3* lattice1;
    HxLattice3* lattice2;
    HxLattice3* lattice3;

    int isFast;

    void regularCombine(unsigned char* dst);

    void fastCombine(unsigned char* dst, const mculong* dims);
};

#endif

/// @}
