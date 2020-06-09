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

/// @addtogroup hxisl hxisl
/// @{
#ifndef HX_DISPLAY_ISL_H
#define HX_DISPLAY_ISL_H

#include <hxisl/HxISLWinDLLApi.h>

#include <Inventor/nodekits/SoWrapperKit.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/draggers/SoTransformBoxDragger.h>
#include <Inventor/draggers/SoTabBoxDragger.h>
#include <Inventor/manips/SoDirectionalLightManip.h>
#include <Inventor/draggers/SoDirectionalLightDragger.h>
#include <Inventor/engines/SoElapsedTime.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortColorList.h>
#include <hxcolor/HxPortColormap.h>

#include <hxisl/SoIllumLines.h>
#include <hxisl/FieldLineSet.h>

#include <mclib/McHandle.h>

class SoNode;
class SoSeparator;
class SoWrapperKit;
class HxVectorField3;
class SoTransform;
class HxLineSet;

/// This module displays illuminated field lines in a 3D vector field.
class HXISL_API HxDisplayISL : public HxModule {

  HX_HEADER(HxDisplayISL);

  public:
    /// Constructor.
    HxDisplayISL();

    /// Update method shows/hides some ports.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Optional scalar field used for pseudo-coloring.
    HxConnection portColorField;

    /// Optional scalar field determining opacity of field lines.
    HxConnection portAlphaField;

    /// Optional scalar field determining distribution of seed points.
    HxConnection portDistField;

    /// Optional colormap used for pseudo-coloring.
    HxPortColormap portColormap;

    /// Constant color used for pseudo-coloring when no colorfield is connected
    HxPortColorList portColor;

    /// Number of field lines to be computed.
    HxPortFloatSlider portNumLines;

    /// One-sided length of field lines.
    HxPortFloatSlider portLength;

    /// Base opacity of field lines.
    HxPortFloatSlider portBaseTrans;

    /// Exponential controlling how fast opacity vanishes along a line.
    HxPortFloatSlider portFadeFactor;

    /// Integration step size of the ODE solver. This value will be multiplied with the diameter of the fields bounding box.
    HxPortFloatSlider portStepSize;

    /// Seed Value for the random number generator that distributes the seedpoints. Seed value of 0 triggers each time a different distribution.
    HxPortRadioBox portSeed;

    /** If fade mode is off, opacity is set according to vector magnitude
	or alpha field. This port defines the data window used to map
	scalar values to opacity. */
    HxPortFloatTextN portAlphaRange;

    /// Enables to control the animation if animationSpeed is set to zero. Hidden by default.
    HxPortFloatSlider portAniTime;

    /// Options: fade mode=0, texture mode=1, animation mode=2.
    HxPortToggleList portToggles;
    enum { FADE=0, LIGHTING=1, ANIMATE=2, DEC=3 };

    /// Seed box: transform box=0, tab box=1, no box=2.
    HxPortRadioBox portBox;

    /// Connection port to specify a ROI for seeding.
    HxConnection portSeedROI;

	/** This port enables the user to adjust the resolution for distribution.
	It is only visible, if 'proportional' or 'equalized' distribution
	has been choosen.
	*/
	HxPortIntTextN portDistributeResolution;

    /// This contains the distribution menu.
    HxPortButtonMenu portDistribute;

    // This contains the "DoIt" button.
    HxPortDoIt portDoIt;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Implements save network feature.
    void savePorts(FILE* fp);

    /// Creates a LineSet object from the current set of stream lines.
    HxLineSet* createLineSet();

    FieldLineSet *getNewFieldLineSet();
    void updateFieldLineSet(FieldLineSet*, int updateIllums=1);

    unsigned int doIntegrate:1;
	unsigned int doRedistribute:1;

  protected:
    virtual ~HxDisplayISL();

    float balance;
    int boxType;
    enum BoxType { XFORMBOX=0, TABBOX=1, NOBOX=2 };

    McDArray<float> colorValues;
    McDArray<float> alphaValues;
    McDArray<FieldLineSet*> fieldLineSet;

    void updateFieldLineSet();
    void updateSoIllumLines();
    void showBoxGeom(int which);

    /// returns true if a HxVertexSet has been connected to the portDistField.
    bool hasSeedVertexSet();

    /// gets the current valid seedbox from the UI.
    /// The seedbob can either be a connected seedROI box, the module internal dragger box
    // or the bundingbox of the vectorfield.
    McBox3f getSeedBox();

    bool goBox(bool bSetBox);
    void boxOn();
    void boxOff();
    void boxReset();
    void boxCreate(int boxType);
    void defaultTransform(SbVec3f& trans, SbVec3f& scale);

    void computeAlphaValues();
    void mapAlphaValues();
    void computeColorValues();
    void mapColorValues();

    void lightDrag(SoDragger* drag);
    static void lightDragCB(void *that,SoDragger *drag);

    HxVectorField3* vectorField;
    ParticleSet* particles;
    McHandle<SoSeparator> boxSeparator;
    McHandle<SoDragger>	box;
    McHandle<SoSeparator> separator;
    McHandle<SoIllumLines> ilines;
    McHandle<SoElapsedTime> elapsedTime;
    McHandle<SoSeparator> lsep;
    McHandle<SoTransform> ltrans;
    McHandle<SoDirectionalLightDragger> light;

    unsigned int doComputeColorValues:1;
    unsigned int doComputeAlphaValues:1;
    unsigned int doMapColorValues:1;
    unsigned int doMapAlphaValues:1;
    unsigned int doRender:1;

	float OldParticlesBBox[6];

  /**
  * Override this method to hide plane interaction toggles when a projection is activated.
  */
  virtual void projectionActivated();

  /**
  * Override this method to show plane interaction toggles when a projection is activated.
  */
  virtual void projectionDeactivated();
};

#endif


/// @}
