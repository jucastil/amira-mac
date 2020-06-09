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
#ifndef SO_CROSSHAIR1_DRAGGER
#define SO_CROSSHAIR1_DRAGGER

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class SbPlaneProjector;

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
// non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable:4251 4275)

class HXCORE_API SoCrosshair1Dragger : public SoDragger {

    SO_KIT_HEADER(SoCrosshair1Dragger);

    // Catalog entries for new parts added by this class.
    SO_KIT_CATALOG_ENTRY_HEADER(translatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator);
    SO_KIT_CATALOG_ENTRY_HEADER(translatorActive);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackTranslate);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(feedback);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackActive);

  public:

    /// Constructor
    SoCrosshair1Dragger();

    /// Field that will always contain the dragger's position.
    SoSFVec3f translation;

    /// Initialize the class. This should be called once
    /// after SoInteraction::init().
    static void initClass();

    /// sets the translation without going into fieldSensor Callback.
    void setValueNF(SbVec3f trans);

    /// sets a mask to assure motion in a plane
    void setMask(SbVec3f mask);

  protected:

    /// Projector used for calculating motion along a line.
    SbPlaneProjector *planeProj;

    ///
    void orientFeedbackGeometry(const SbVec3f &localDir);

    // Static callback functions invoked by SoDragger when the
    // mouse button goes down over this dragger, when the
    // mouse drags, and when the button is released.

    static void startCB(void *, SoDragger *);
    static void motionCB(void *, SoDragger *);
    static void finishCB(void *, SoDragger *);

    // These functions, invoked by the static callback
    // functions, do all the work of moving the dragger.
    void dragStart();
    void drag();
    void dragFinish();

    // This sensor watches for changes to the translation field.
    SoFieldSensor *fieldSensor;
    static void fieldSensorCB(void *, SoSensor *);

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
    static const unsigned char geomBuffer[];

    SbVec3f planeMask, invPlaneMask;

    // Destructor.
    ~SoCrosshair1Dragger();
};

#pragma warning(pop)

#endif

/// @}
