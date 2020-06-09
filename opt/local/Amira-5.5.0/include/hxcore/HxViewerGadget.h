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
#ifndef HX_VIEWER_GADGET_H
#define HX_VIEWER_GADGET_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoCamera.h>

class QxViewer;
class PoSceneView;
class SoAction;
class SoNode;
class SoSeparator;
class SoSwitch;
class SoPickStyle;
class SoDirectionalLight;
class SoCallback;
class SoRotation;
class QEvent;

#define USE_ORTHO_CAMERA
const int DEFAULT_WIDTH = 130;
const int DEFAULT_HEIGHT = 130;

#ifdef HX_OS_MACX
    const int HX_NUM_DEFAULT_ANTIALIAS_PASSES = 1; 
#else
    const int HX_NUM_DEFAULT_ANTIALIAS_PASSES = 4;
#endif

class HXCORE_API HxViewerGadget {

public:
    
	enum Position {
        LOWER_LEFT,
        LOWER_RIGHT,
        UPPER_RIGHT,
        UPPER_LEFT
	};

	enum VisibilityMode {
		ALWAYS_VISIBILITY_MODE,
		NEVER_VISIBILITY_MODE,
		AUTO_HIDE_VISIBILITY_MODE
	};


	/// Constructor.
	HxViewerGadget(QxViewer * viewer);

	/// Destructor.
	virtual ~HxViewerGadget();

	/// Sets/Gets the position of the gadget.
	void setPosition(Position pos);
	inline Position getPosition() const {return m_position;};

	/// Sets the size of the gadget in pixels.
	inline void setSize(const SbVec2s &sizePixels) {m_sizePixels = sizePixels;};

	/// Sets/Gets the visibility mode.
	/** ALWAYS_VISIBILITY_MODE:    always visible whatever the visibility sets (ie. setVisibilty())
		NEVER_VISIBILITY_MODE:     never visible whatever the visibility sets (ie. setVisibilty())
		AUTO_HIDE_VISIBILITY_MODE: the visibility depends on the visibility sets (ie. setVisibilty()) */
	void setVisibilityMode(VisibilityMode visibilityMode);
	inline VisibilityMode getVisibilityMode() const {return m_visibilityMode;};

	/// To know if the gadget is in auto-hide mode.
	inline bool isAutoHideMode() const {return (m_visibilityMode == AUTO_HIDE_VISIBILITY_MODE);};

	/// Sets/Gets the visibility.
	void setVisibility(bool onOff);
	bool isVisible() const;

	/** Compute the visibility of the compass according to the mouse events.
		If the mouse pointer is inside the compass area, it forces
		the viewing mode to false and it restores it as soon as the mouse pointer
		leave the compass area.
		Furthemore in order to prevent from the picking of other 3D objects than the 
		compass, it forces the pick style as argument to be set to UNPICKABLE if
		a mouse button press occurs whereas the mouse pointer is within the compass 
		area (ie the pick stype is set SHAPES when the mouse button is released). */
	void computeVisibility(QEvent *event, SoPickStyle *style);

	/// Indicates if a point in pixel is inside the compass area.
	bool isPointInside(int xpixels, int ypixels) const;

	/// To get the scene graph.
	inline SoNode * getSceneGraph() const {return (SoNode*) m_sceneView;};

	/// Returns the camera of the gadget.
	inline SoCamera *getCameraCompass() const {return (SoCamera*) m_gadgetCamera;};

	/// Calls this method each time the viewer size has changed in order to update the size of the gadget.
	void viewerSizeChanged();

	/// Specify the number of passes to antialiase the compass rendering.
	void setNumAntialiasingPasses(int numPasses);
    
    int getNumAntialiasingPasses() const { return m_numAntialiasPasses; };
	
    /// Returns the number of default anti aliasing passes.
	inline int getNumDefaultAntialiasingPasses() const {return HX_NUM_DEFAULT_ANTIALIAS_PASSES;};

	/// To save/restore the state (i.e. Visibility/Position/Visibility Mode).
	void saveState();
	void restoreState();

	///
    void setAntiAliasPass(int num){ m_antialiasPass = num % m_numAntialiasPasses; }
    int  getAntiAliasPass() const { return m_antialiasPass; }

    QxViewer* getViewer() const {  return m_viewer; }

    /**
     * To enable/disable the gadget.
     * A disabled gadget will always be hidden.
     */
    void setEnabled(bool enable);

    /**
     * To know if a gadget is enabled.
     */
    bool isEnabled() const { return m_enabled; }

protected:

	/// Read the compass geometry.
	virtual SoSeparator * readGeometry(const char * filename);

	///
	virtual void enterGadgetArea();
	virtual void leaveGadgetArea();

    virtual SoGroup * getHook() const { return m_hook; }

    virtual void startRendering(SoAction *action);
    virtual void endRendering(SoAction *action);

    /**
     *  For convenience, another way to set the visibility.
     */
    void setVisibility(bool showGadget, bool autoHideGadget);

private:
    /// 
    void initSceneView();

	static void startRenderingCB(void *udata, SoAction *action);
	static void endRenderingCB(void *udata, SoAction *action);
    QxViewer            *m_viewer;
	Position			m_position;
	VisibilityMode      m_visibilityMode;
	bool				m_mouseWasInside;

	SoSwitch            *m_switchVisibility;
	SoSeparator         *m_root;
	SbVec2s             m_sizePixels;
	PoSceneView         *m_sceneView;
	SoCamera            *m_gadgetCamera;
	SoDirectionalLight	*m_dirLight;
	SoCallback			*startRenderingCallback;
	SoCallback			*endRenderingCallback;
    SoGroup             *m_hook;
  SoGroup* m_headLightGroup;
  SoRotation* m_headLightRot;  

	/// Antialiasing.
	int                 m_antialiasPass;
	int                 m_numAntialiasPasses;
	float               m_antialiasPassFrac;
	SoSeparator         *m_passSep;

	/// Save/Restore.
    Position            m_savedPosition;
    VisibilityMode      m_savedVisibilityMode;
    bool                m_savedIsVisible;

    /// Enabled/disabled gadget.
    bool                m_enabled;



  static void pushOrthoView(float left, float right, float bottom, float top, float znear, float zfar);
  static void popView(void);

  static void beforeRenderingCB(void *udata, SoAction *action);
  static void afterRenderingCB(void *udata, SoAction *action);
};
#endif



/// @}
