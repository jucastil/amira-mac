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

/// @addtogroup hxfastLIC hxfastLIC
/// @{
#ifndef HX_FASTLIC_H
#define HX_FASTLIC_H

#include <hxfastLIC/HxFastLICWinDLLApi.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoSeparator.h>

#include <mclib/McPrimType.h>
#include <flic/flic.h>

#include <hxcore/HxArbitraryCut.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/TetraCut.h>
#include <hxfield/HxVectorField3.h>

class HxTetraGrid;
class SoTexturedSlice;

/// Implements LIC on an arbitrary cutting plane.

class HXFASTLIC_API HxFastLIC : public HxArbitraryCut {

  HX_HEADER(HxFastLIC);

  public:
    /// Constructor.
    HxFastLIC();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Color mode: 0=none, 1=magnitude, 2=normal, 3=tangent, 4=color field
    HxPortMultiMenu portColorMode;

    /// Connection to field used for pseudo-coloring.
    HxConnection portColorField;

    /// Connection to field used for pseudo-coloring.
    HxConnection portColorField2;
    
    /// Connection to colormap.
    HxPortColormap portColormap;

    /// Connection to colormap. For two dimensional coloring
    HxPortColormap portColormap2;

    /// Options: 0=filterLength, 1=resolution, 2=seed.
    HxPortIntTextN portOptions;

    /// Phase used when projecting complex vectors.
    HxPortFloatSlider portPhase;

    /// When LIC plane extract data values out of the input grid or equals to the undefined value,
    //  this port allows to make them transparent.
    HxPortToggleList portHideUndefinedValues;

    /// Do it button.
    HxPortDoIt portDoIt;
    
    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    enum ColorMode { NOCOLOR=0, MAGNITUDE=1, NORMAL=2, TANGENT=3, FIELD=4 };

  protected:
    virtual ~HxFastLIC();


    //handle projection activation
    virtual void projectionActivated();

    //handle projection deactivation
    virtual void projectionDeactivated();

    McHandle<SoSeparator> m_root;
    SoTexturedSlice*      m_slice;

    // Stores different states of the algorithm to prevent redundant computes
    int stateFlag;
    int filterLength;
    int resolution;
    int seed;
    bool m_hasFoundUndefinedValues;
    bool m_hideOutOfGridValues;

    // Flic stuff.
    McDArray<float> sampledVectors;
    McDArray<float> realVectors;
    FlicScalarField flicScalar;
    FlicScalarField flicScalar2;
    FlicImage flicRaw;
    FlicImage flicFinal;
    FlicImage flicMaskInWorldSpace;
    FlicImage flicMaskInTextureSpace;
    FlicCompute flic;

    void doGeneric();
    void doIntersection(HxTetraGrid* grid);

    void computeTextureCoords();
    void sample3DVectorField();
    void extractRealVectors();
    void computeFlicImage();    
    void computeExternal2DScalarField(HxField3* field, FlicScalarField* flicScalar);
    void compute2DScalarField();
    void colorizeFlicImage();

    int getSamplingResolution();
    int getTextureResolution();

    void convertColormap(FlicColormap&, HxPortColormap&);
    void createDefaultColormap(FlicColormap&);

    void setFlicTexture(SoTexturedSlice* texture);
    void setDefaultTexture(SoTexturedSlice* texture);

    SbVec3f mOrig;
    SbVec3f muVec;
    SbVec3f mvVec;
};

#endif

/// @}
