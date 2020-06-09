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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_MEASURE_GUI
#define HX_MEASURE_GUI

#include <hxmeasure/HxMeasureWinDLLApi.h>

#include <hxmeasure/HxGLStates.h>
#include <hxmeasure/HxMeasureGUIFrame.h>
#include <hxcore/HxController.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/events/SoEvent.h>
#include <mclib/McHandle.h>

class HxMeasureGUIEvent;

class HxMeasureGUIElem;
class HxViewer;

class QxMTBox;
class QCursor;
class QxMeasureGUINotifier;

const int MEASURE_GUI_DEFAULT_FONT_SIZE = 14;

/** This class does the low level stuff of the measurement tools.
*/
class HXMEASURE_API HxMeasureGUI {

    /// some state stuff.
    enum States { SLEEPING, RUNNING };

public:
    /// it is a singleton.
    static HxMeasureGUI* getTheMeasureGUI ();

    /// .
    void startEdit ();
    /// .
    void stopEdit ( bool setViewing=true);
    ///
    bool isEditing() const { return (state==RUNNING); }

    /** get the SoNode that has to be added to the rendered as the
    very last. 
    */ 
    SoNode* getGeomRoot ();

    SoSeparator*getRoot();

    /// elem takes all the events up to a call to stopGrabbing (). 
    void startGrabbing (HxMeasureGUIElem* elem);
    /// .
    void stopGrabbing ();

    /** Redraw the scene. If sleeping a whole Inventor rendering is
    done for each viewer. If in a edit mode the screenshot is
    written into the display buffer and only the tools are rendered
    in 3D using openGL directly.
    */
    void redraw ();

    /// the number of tools.
    int getNumElems ();
    /// get tool number i.
    HxMeasureGUIElem* getElem (int i);
    /// add a tool.
    void addElem (HxMeasureGUIElem* el);
    /** remove a tool. The numeration of the tools is changed.
    WARNING: DON'T do things like
    @code
    for (int i = 0; i < 5; i++) {
    gui->removeElem (gui->getElem (i));
    }
    @endcode
    Do it this way
    @code
    McDArray<HxMeasureGUIElem*> del;
    for (int i = 0; i < 5; i++) {
    del.append (gui->getElem (i));
    }
    for (int i = 0; i < del.size (); i++) {
    gui->removeElem (del[i]);
    }
    @endcode
    */
    void removeElem (HxMeasureGUIElem* el);

    /**
    *  For convenience, remove all tools.
    */
    void removeAllElems();

    /// Select a tool.
    void selectTool (HxMeasureGUIElem* el);

    /// get the viewState of the current viewer and buffer.  
    const HxGLViewState* viewState () {
        return &(viewStates[activeViewer][activeBuffer]);
    }

    // tcl stuff 
    int parse(Tcl_Interp* t, int argc, char **argv); 

    // save stuff
    void saveTCL (FILE* fp, const char* prefix);

    /// restore the GL state. 
    void enterGL ();
    /// restore all GL stuff.
    void exitGL ();

    QxMeasureGUINotifier* const mNotifier;

    void deselectAll();

    void setState(States inState) { state = inState; }

    /**
     *  Enable or not the possibility to activate a new tool when the user
     *  clicks beside the selected one. This feature has been introduced
     *  since Avizo6.0.
     *  This option is true by default.
     */
    void enableAutoActivation(bool enableOrNot)
    {
        m_enableAutoActivation = enableOrNot;
    }

private:
    /// the tools.
    McHandle<HxMeasureGUIFrame> members;

    /// we're a Singleton so construction and destruction is private.
    HxMeasureGUI ();
    /// we're a Singleton so construction and destruction is private.
    ~HxMeasureGUI ();

    /// the Inventor event callback.
    static int eventCallback(const SoEvent* event, HxViewer* viewer, void* userData);

    /// the Inventor action callback. 
    static void sceneCallback (void* userData, SoAction* action);
    /// specific Inventor action callback.
    void render (SoGLRenderAction* renderAction);
    ///function called before render()
    virtual void preRender(SoGLRenderAction* renderAction);
    /// specific Inventor action callback.
    void getBBox (SoGetBoundingBoxAction* action);


    /// the actual grabber. 
    HxMeasureGUIElem* grabber;

    States state;
    /// should we grab the screen.
    bool saveState;

    //stored matrix mode
    GLint m_matrixMode;

    /// The only object.
    static HxMeasureGUI* _theGUI;

    /// our inventor geometry (Annotation)
    McHandle<SoSeparator> geomRoot;

    /// Separator geometry 
    McHandle<SoSeparator> m_root;

    /// the states.
    HxGLViewState viewStates[HxController::nViewers][2];
    /// the states.
    HxGLBufferState bufferStates[HxController::nViewers][2];
    /// the states.
    HxGLLightState lightStates[HxController::nViewers][2];
    /// stereo?
    int stereoViewing;
    /// the active Buffer. (We're not multithreaded, there is only one)
    int activeBuffer;
    /// the active Buffer. (We're not multithreaded, there is only one)
    int activeViewer;

    /// the qt widget for our tools.
    QxMTBox* qMTBox;

    friend class QxMTBox;
    friend class HxMeasureGUIEvent;

    /// cursor before forbidden cursor
    bool mForbiddenCursor;

    /// To know if a new tool should be activate when the user
    ///  clicks beside the currently selected tool.
    bool m_enableAutoActivation;
};

/** Supporting class to HxMeasureGUI, that gives some information
about the actual SoEvent.
*/
class HxMeasureGUIEvent {
public:
    /// get the depth value at screen space position pos
    static float getZBuffer (const McVec2f& pos) {
        HxMeasureGUI* gui = HxMeasureGUI::getTheMeasureGUI();
        return gui->bufferStates
            [gui->activeViewer][gui->activeBuffer].getZBuffer(pos);
    }

    /// get the depth value at event position
    static float getZBuffer (const SoEvent* ev) {
        HxMeasureGUI* gui = HxMeasureGUI::getTheMeasureGUI();
        return gui->bufferStates
            [gui->activeViewer][gui->activeBuffer].getZBuffer 
            (ev->getPosition ());
    }

    /// get the world position.
    static McVec3f getWorldPosition (const SoEvent* ev) {
        const SbVec2s& pos = ev->getPosition ();
        McVec3f sc (pos[0], pos[1], getZBuffer (ev));
        McVec3f world;
        HxMeasureGUI::getTheMeasureGUI()->viewState()->mapScreenToWorld 
            (sc, world);
        return world;
    }

    /// get the normalized screen space position.
    static McVec3f getScreenPosition (const SoEvent* ev) {
        const SbVec2s& pos = ev->getPosition ();
        McVec2f size = HxMeasureGUI::getTheMeasureGUI()->viewState()->getViewportSize();
        return McVec3f(pos[0]/size[0],pos[1]/size[1],0);
    }
};

#endif

/// @}
