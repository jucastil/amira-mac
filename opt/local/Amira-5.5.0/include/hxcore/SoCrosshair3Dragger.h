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
#ifndef SO_CROSSHAIR3_DRAGGER
#define SO_CROSSHAIR3_DRAGGER

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFBox3f.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/nodes/SoEventCallback.h>

#include <mclib/McHandle.h>

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/SoCrosshair1Dragger.h>
#include <hxcore/SoCrosshairDraggerInterface.h>

class SbPlaneProjector;
class SoScale;
class SoTranslation;
class SoSwitch;
class SoSeparator;

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
// non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable:4251 4275)

class HXCORE_API SoCrosshair3Dragger : public SoCrosshairDraggerInterface {
    SO_KIT_HEADER(SoCrosshair3Dragger);

    // Catalog entries for new parts added by this class.
    SO_KIT_CATALOG_ENTRY_HEADER(keyEvent);
    SO_KIT_CATALOG_ENTRY_HEADER(XtranslatorSep);
    SO_KIT_CATALOG_ENTRY_HEADER(XtranslatorScale);
    SO_KIT_CATALOG_ENTRY_HEADER(XtranslatorTrans);
    SO_KIT_CATALOG_ENTRY_HEADER(Xtranslator);
    SO_KIT_CATALOG_ENTRY_HEADER(YtranslatorSep);
    SO_KIT_CATALOG_ENTRY_HEADER(YtranslatorScale);
    SO_KIT_CATALOG_ENTRY_HEADER(YtranslatorTrans);
    SO_KIT_CATALOG_ENTRY_HEADER(Ytranslator);
    SO_KIT_CATALOG_ENTRY_HEADER(ZtranslatorSep);
    SO_KIT_CATALOG_ENTRY_HEADER(ZtranslatorScale);
    SO_KIT_CATALOG_ENTRY_HEADER(ZtranslatorTrans);
    SO_KIT_CATALOG_ENTRY_HEADER(Ztranslator);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackRot);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackTrans);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackScale);
    SO_KIT_CATALOG_ENTRY_HEADER(feedback);

  public:

    /// Constructor
    SoCrosshair3Dragger();

    /// Field that will always contain the dragger's position.
    SoSFVec3f translation;

    ///
    SoSFBox3f bounds;

    /// Initialize the class. This should be called once
    /// after SoInteraction::init().
    static void initClass();

  protected:
    // Pointers to the draggers this dragger is made of.
    McHandle<SoCrosshair1Dragger> xDrag, yDrag, zDrag;

    // Pointers to the translators for the draggers this dragger is made of.
    SoTranslation *xTrans, *yTrans, *zTrans;

    // Static callback functions invoked by SoDragger when the
    // mouse button goes down over this dragger, when the
    // mouse drags, and when the button is released.

    static void startCB(void *userData, SoDragger *dragger);
    static void motionCB(void *userData, SoDragger *dragger);
    static void finishCB(void *userData, SoDragger *dragger);

    void orientFeedbackGeometry();

    // These functions, invoked by the static callback
    // functions, do all the work of moving the dragger.
    void dragStart(SoDragger *which);
    void drag(SoDragger *which);
    void dragFinish(SoDragger *which);
    void valueHasChanged();

    /// updates all chlid draggers according to movement
    void updateChildDraggers(SbVec3f trans);

    // This sensor watches for changes to the translation field.
    SoFieldSensor *fieldSensor;
    static void fieldSensorCB(void *, SoSensor *);

    SoFieldSensor *bbFieldSensor;
    static void bbFieldSensorCB(void *, SoSensor *);

    // This callback updates the translation field when
    // the dragger is moved.
    static void valueChangedCB(void *, SoDragger *);

    // This will detach/attach the fieldSensor.
    // It is called at the end of the constructor (to attach).
    // and at the start/end of SoBaseKit::readInstance()
    // and on the new copy at the start/end of SoBaseKit::copy().
    // Returns the state of the node when this was called.
    virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE);

  private:
    static void keyPressedCB(void *userData, SoEventCallback *eventCB);

    int hitAxis;
    SbBool shiftIsPressed, useShiftMask;
    float  shiftMask[3];
    SoCrosshair1Dragger *currDragger;

    SoScale *xScale, *yScale, *zScale;
    SbVec3f startPoint;
    SbVec3f xPrevTrans;
    SbVec3f yPrevTrans;
    SbVec3f zPrevTrans;

    float xFac, yFac, zFac;
    float xOff, yOff, zOff;
    SbVec3f minMove, maxMove;

    static const unsigned char geomBuffer[];

    // Destructor.
    ~SoCrosshair3Dragger();
};

#pragma warning(pop)

#endif

/// @}
