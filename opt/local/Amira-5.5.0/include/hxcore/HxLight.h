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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_LIGHT_H
#define HX_LIGHT_H

#include <mclib/McColor.h>
#include <mclib/McHandle.h>

#include <hxcore/HxObject.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortFloatTextN.h>
#include <Inventor/draggers/SoDirectionalLightDragger.h>
#include <Inventor/draggers/SoPointLightDragger.h>
#include <Inventor/draggers/SoSpotLightDragger.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/engines/SoTransformVec3f.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/nodes/SoTransformSeparator.h>
#include <Inventor/nodes/SoTranslation.h>

class HxViewer;

/** Amira object representing a light in the global Inventor scene graph.
    Three different light types are support, namely directional lights,
    point lights, and spot lights. Lights can be defined in scene coordinates
    or in camera coordinates (camera slave mode). In order to interactively
    change the light parameters appropriate Open Inventor draggers can be
    activated. Note, that the Amira viewers define their own headlight on
    default. HxLight objects represent additional light sources and are
    not related to the viewer's head light. */
class HXCORE_API HxLight : public HxObject {
    HX_HEADER(HxLight);

  public:
    /// Light type
    enum Type {
        /// Directional light
        HxDirLight=0,
        /// Point light
        HxPointLight=1,
        /// Spot light
        HxSpotLight=2
    };

    /// Constructor.
    HxLight(const char* name=NULL, Type type=HxDirLight);

    /// Destructor.
    ~HxLight();

    /// Type: 0=directional light, 1=point light, 2=spot light
    HxPortRadioBox portType;

    /// Options: 0=light color, 1=camera slave toggle, 2=dragger toggle
    HxPortGeneric portOptions;

    /// Light direction (x,y,z)
    HxPortFloatTextN portDirection;

    /// Light location (x,y,z)
    HxPortFloatTextN portLocation;

    /// Spot angle.
    HxPortFloatTextN portSpot;

    /// Enables or disables camera slave mode.
    void setSlave(int onOff);

    /// Checks is camera slave mode is enabled or not.
    int isSlave() const;

    /// Sets the color of the current light.
    void setColor(const McColor& color);

    /// Returns the color of the current light.
    void getColor(McColor& color);

    /// Sets the light type.
    void setType(Type);

    /// Returns the current light type.
    Type getType() const { return type; }

    /// Returns Inventor node representing the current light.
    SoLight* getLight() const { return genLight; }

    /// Sets direction of current light (ignored for point lights).
    void setDirection(const SbVec3f&);

    /// Gets direction of current light (undefined for point lights).
    void getDirection(SbVec3f&);

    /// Sets location of current light (ignored for directional lights).
    void setLocation(const SbVec3f&);

    /// Gets location of current light (undefined for directional lights).
    void getLocation(SbVec3f&);

    /// Interpretes port changes.
    virtual void update();

    /// The viewer mask controls in which viewers lights are activated.
    virtual void setViewerMask(int mask, int master=0xffff);

    /// Allows to save light setting in network scripts.
    virtual void savePorts(FILE* fp);

    /// Light icons are blue.
    virtual McColor getIconColor();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* interpreter, int argc, char** argv);

  protected:
    void initializeDragger();
    void connectDragger();
    void disconnectDragger();
    void updateDragger();
    void initializeGUI();
    void updateGUI();
    void edit(int showDragger);
    float negativeSceneExtent();
    void connectLightToCamera(int viewerNumber=0);
    void disconnectLight();

    int cameraSlave;
    int editing;
    Type type;
    SbVec3f dLightLocation;

    static void draggerMotionCallback(void*, SoDragger*);
    static void valueChangedCallback(void*, SoDragger*);

    McHandle<SoDirectionalLight> dLight;
    McHandle<SoPointLight> pLight;
    McHandle<SoSpotLight> sLight;
    SoLight* genLight; // points to the current light

    McHandle<SoDirectionalLightDragger> dDrag;
    McHandle<SoPointLightDragger> pDrag;
    McHandle<SoSpotLightDragger> sDrag;
    SoDragger* genDrag; // points to the current dragger

    McHandle<SoRotation> camrot, w2c_rot;
    McHandle<SoTranslation> camtrans, w2c_trans;
    SbRotation c2w_rot;
    SbVec3f c2w_trans;

    McHandle<SoTransformSeparator> lightNode;
    McHandle<SoTransformSeparator> draggerNode;
    McHandle<SoComposeMatrix> drag2lightCME;
    McHandle<SoTransformVec3f> drag2lightTVE;
    McHandle<SoCalculator> drag2lightCE;

    static McHandle<SoScale> draggerScale;
};

#endif

/// @}
