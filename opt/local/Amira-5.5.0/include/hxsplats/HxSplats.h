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

/// @addtogroup hxsplats hxsplats
/// @{
#ifndef HX_SPLATS_H
#define HX_SPLATS_H

#include "SoSplats.h"

#include <mclib/McHandle.h>
#include <mclib/McBox3f.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxDisplay.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>

#include <hxcolor/HxPortColormap.h> 

#include <hxfield/HxTetraGrid.h>
#include <hxfield/HxTetraScalarField3.h>
#include "HxSplatsWinDLLApi.h"


#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoSeparator.h>

/// Tetrahedral mesh volume renderer of Shirley-Tuchman type.
class HXSPLATS_API HxSplats : public HxModule {

    HX_HEADER(HxSplats);

  public:
    /// Constructor.
    HxSplats();

    /// Maximum opacity of a cell.
    HxPortFloatSlider portAlphaScale;

    /// Defines non-linear alpha lookup table by @f$x^\gamma@f$.
    HxPortFloatSlider portGamma;

    /// Defines which cells should be rendered.
    HxPortFloatTextN portMinMax;

    /// Switches between constant (0) and linear (1) interpolation.
    HxPortRadioBox portTexture;

    /// Switches between different optical models: (0) only light emission, (1) emessive and absortive light model (2) absorbing light only
    HxPortRadioBox portOpticalModel;

    HxPortColormap portColormap;

    HxPortDoIt portDoIt;

    HxConnection portRoi;

    /// Compute method.
    virtual void compute();

    virtual void update();

    // Parse method.
    virtual int parse(Tcl_Interp* , int , char **);

  protected:
    /// Destructor.
    virtual ~HxSplats();

    /**
        Gives the range that should be mapped to [0,1] for displaying.
    */
    void getMinMax(float& min, float& max);

    /**
        Gives the ids of the tetras which should be rendered.
    */
    void getTetraIdsToDisplay(McDArray<int>& tetraIds);

    /**
        Creates a subgrid and subfield of a HxTetraScalarField. In the new
        grid/field are all values used by the tetras with the ids given by @c selectedTetras.
    */
    McHandle<HxTetraScalarField3> getSelectedTetraField(const McDArray<int>& tetraIds, HxTetraScalarField3* field);

    static float calcBBoxDiameter2(const McVec3f& v0, const McVec3f& v1, const McVec3f& v2, const McVec3f& v3);

    McHandle<SoSeparator> root;
    McHandle<SoTexture2> tex2;
    McHandle<SoSplats> splats;
    HxTetraScalarField3* field;
    unsigned char tex[4*128*128];
};


#endif

/// @}
