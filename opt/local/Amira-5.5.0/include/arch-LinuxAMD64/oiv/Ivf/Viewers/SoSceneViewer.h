/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
** Modified by : Alain Dumesny (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
** Modified by : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SCENE_VIEWER_
#define  _SCENE_VIEWER_

#ifdef _WIN32
#  include <Inventor/Win/SoWinBeginStrict.h>
#else
#  include <X11/Intrinsic.h>
#  include <Xm/Xm.h>
#  include <Xm/RowColumn.h>
#endif

#include <Inventor/nodes/SoNode.h>
#include <Inventor/SbPList.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/actions/SoGLRenderAction.h>  // transparency levels
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>

// components
#ifdef _WIN32
#  define MyColorEditor SoWinColorEditor
// this can be changed below with setFirstLightMenuId
#  define ID_SV_FIRST_LIGHT  16386
#endif

class MyColorEditor;
class SoWinMaterialEditor;

class SoWinPrintDialog;

class SoWinClipboard;
class SoWinDirectionalLightEditor;

// interaction
class SoBoxHighlightRenderAction;
class SoSelection;
class SoPickedPoint;

// nodes
class SoDirectionalLight;
class SoEnvironment;
class SoGroup;
class SoLabel;
class SoMaterial;
class SoSceneViewer;
class SoSwitch;
class SoLight;
class SoTransform;

// misc.
class SvManipList;

enum SvEViewer { 
  SV_VWR_NONE = -1,
  SV_VWR_EXAMINER, 
  SV_VWR_FLY, 
  SV_VWR_WALK, 
  SV_VWR_PLANE 
};

enum SvEManipMode { 
  SV_NONE, // None
  SV_TRANSFORMER, // Transformer manip
  SV_TRACKBALL, // Trackball manip
  SV_HANDLEBOX, // Handlebox manip
  SV_JACK, // Jack manip
  SV_CENTERBALL, // Centerball manip
  SV_XFBOX, // TransformBox manip
  SV_TABBOX // TabBox manip
};

#ifdef _WIN32
#  define SvMenuAction(pSV,action) { \
  SoSceneViewerData data; \
  data.classPt = pSV; \
  data.id = action; \
  data.widget = NULL; \
  SoSceneViewer::processTopbarEvent(pSV, &data, NULL); \
}

struct SoSceneViewerData { 
  int id;
  SoSceneViewer *classPt;
  SoWidget widget;
};
#else
struct SoSceneViewerData;
#endif

class SvLightData;

//////////////////////////////////////////////////////////////////////////////
//
// Class: SoSceneViewer
//
// The SceneViewer component lets you select between different viewers
// (Examiner, Navigator,..) and lets you perform some simple attribute
// assignment, and some manipulation of data.
//
//////////////////////////////////////////////////////////////////////////////

class IVF_API SoSceneViewer : public SoWinComponent { 

  friend class CIvfSceneViewer;
 
 public: 
  // Constructor:
  // envFile is the environment file to use. This is where the camera,
  // environment node, and lights are found. 
  // Passing NULL means use the default environment.
  //
  // Save will save all the children of root, not including root itself.
  // Save Environment will save the lights and camera environment into envFile
  //
  SoSceneViewer(SoWidget parent = NULL, 
                const char *name = NULL, 
                SbBool buildInsideParent = TRUE, 
                SoSelection *root = NULL,
                const char * envFile = NULL);
  ~SoSceneViewer();

#ifdef _WIN32
  SoEXTENDER SoSceneViewer(SoWidget parent,
                           const char *name, 
                           SbBool buildInsideParent, 
                           SoSelection *root,
                           const char *envFile, 
                           SbBool buildNow);
  
  static void processTopbarEvent(void *, SoSceneViewerData *, 
                                 XmAnyCallbackStruct *);
  
  void realizeWidget();
#endif
  
  // Turns fog on/off
  void setFog(SbBool onOrOff);
  // Turns antialiasing on/off
  void setAntialiasing(SbBool onOrOff);
  
  // Sets the antialiasing used for rendering. There are two kinds of 
  // antialiasing available: smoothing and multipass antialiasing. If 
  // smoothing is set to TRUE, smoothing is enabled. Smoothing uses OpenGL's
  // line- and point-smoothing features to provide cheap antialiasing of 
  // lines and points. The value of numPasses controls multipass antialiasing.
  // Each time a render action is applied, Open Inventor renders the scene
  // numPasses times from slightly different camera
  // positions, averaging the results. numPasses can be from one to 255,
  // inclusive. Setting numPasses to one disables multipass antialiasing.
  // You can use either, both, or neither of these antialiasing techniques.
  // By default, both smoothing and multipass antialiasing are disabled.
  
  void setAntialiasing(SbBool smoothing, int numPasses);
  
  // Sets the antialiasing used for rendering.
  void setFullSceneAntialiasing(SbBool onOrOff, float quality, int filterMask);

  SvLightData *addLight(SoLight *light, int);
  void removeLight(SvLightData *);
  SbPList lightDataList;
  static void editLightColorCB(SoWidget, SvLightData *, void *);
  static void lightToggleCB(SoWidget, SvLightData *, void *);
  static void editLightToggleCB(SoWidget, SvLightData *, void *);
  static void removeLightCB(SoWidget, SvLightData *, void *);
 
  static void beforePrintCallback(void *uData, SoWinPrintDialog *);
  static void afterPrintCallback(void *uData, SoWinPrintDialog *);
  
  static void __TGSSVSetLogoFlag(SbBool);
  
  //protected:
  static SbBool m_bTGSSVLogoFlag; 
  
#ifdef _WIN32
  SbBool realized;
#endif
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoSceneViewer::buildWidget()
  // when they are ready for it to be built.
#ifndef _WIN32
  SoEXTENDER SoSceneViewer(SoWidget parent,
                           LPCTSTR name, 
                           SbBool buildInsideParent, 
                           SoSelection *root,
                           LPCTSTR envFile, 
                           SbBool buildNow);
#endif
  
 public:
  void saveViewerSceneGraph(LPCTSTR fileName);
#ifdef _WIN32
  void setFileMode(int nMode)
    { fileMode = nMode; };
  SbBool doFileIO(LPCTSTR filename);
  SoWinFullViewer *getViewer(int n)
    { return viewerList[n]; };
  SoWinFullViewer *getCurrViewer()
    { return viewerList[whichViewer]; };
  SvEViewer getWhichViewer()
    { return whichViewer; };
  
  SoWinMaterialEditor *getMaterialEditor()
    { return materialEditor; };
  SoWinColorEditor *getBackgroundColorEditor()
    { return backgroundColorEditor; };
  SoWinColorEditor *getAmbientColorEditor()
    { return ambientColorEditor; };
  SoWinColorEditor *getColorEditor()
    { return colorEditor; };
  SoWinDirectionalLightEditor *getHeadlightEditor()
    { return headlightEditor; };
  
  SoSelection *getSelection()
    { return selection; };
  
  SoWinClipboard *getClipboard()
    { return clipboard; };
  
  SvLightData *getHeadlightData()
    { return headlightData; };
  
  void editHeadlight()
    { editLight(headlightData,TRUE); };
  
  SvEManipMode getCurrManip()
    { return curManip; };
  
  SoSeparator *getSceneGraph()
    { return sceneGraph; };
  SbBool setSceneGraph(SoNode *node);
  void releaseDocScene();
  
  void setMenuWidget(HMENU hMenu);
  void setLightMenuWidget(HMENU hMenu);
  void setFirstLightMenuId(ULONG nId);
  
  SbBool getAAFlag()
    { return antialiasingFlag; };
  SbBool getFogFlag()
    { return fogFlag; };
  
  SbBool onCommand(WPARAM wParam, LPARAM lParam);
#endif

  //
  // Camera operation routines
  //

  void viewAll() 
    { if (currentViewer != NULL) currentViewer->viewAll(); }
  void viewSelection();
  void saveHomePosition() 
    { if (currentViewer != NULL) currentViewer->saveHomePosition(); }
  void setCamera(SoCamera *cam);
  // NOTE: because the camera may be changed dynamically (switch between ortho
  // and perspective), the user shouldn't cache the camera.
  SoCamera *getCamera() 
    { return (currentViewer) ? currentViewer->getCamera() : NULL; }
  
  //
  // Before new data is sent to the viewer, the newData method should
  // be called to disconnect all manipulators and highlights
  //
  void newData();
 
  // Show/hide the pulldown menu bar (default shown)
  void showMenu(SbBool onOrOff);
  SbBool isMenuShown()
    { return showMenuFlag; }
  
  // Show/hide the viewer component trims (default shown)
  void setDecoration(SbBool onOrOff) 
    { if (currentViewer != NULL) currentViewer->setDecoration(onOrOff); }
  SbBool isDecoration() 
    { return currentViewer != NULL ? currentViewer->isDecoration() : FALSE; }
  
  // Show/hide headlight (default on) and get to the headlight node.
  void setHeadlight(SbBool onOrOff) 
    { if (currentViewer != NULL) currentViewer->setHeadlight(onOrOff); }
  SbBool isHeadlight() 
    { return currentViewer != NULL ? currentViewer->isHeadlight() : FALSE; }
  SoDirectionalLight *getHeadlight() 
    { return currentViewer != NULL ? currentViewer->getHeadlight() : NULL; }
  
  //
  // Sets/gets the current drawing style in the main view - The user
  // can specify the INTERACTIVE draw style (draw style used when 
  // the scene changes) independently from the STILL style.
  //
  // (default VIEW_AS_IS for both STILL and INTERACTIVE)
  //
  void setDrawStyle(SoWinViewer::DrawType type, 
                    SoWinViewer::DrawStyle style)
    { currentViewer->setDrawStyle(type, style); }
  SoWinViewer::DrawStyle getDrawStyle(SoWinViewer::DrawType type)
    { return currentViewer->getDrawStyle(type); }
  
  //
  // Sets/gets the current buffering type in the main view
  // (default BUFFER_INTERACTIVE on Indigo, BUFFER_DOUBLE otherwise)
  //
  void setBufferingType(SoWinViewer::BufferType type)
    { currentViewer->setBufferingType(type); }
  SoWinViewer::BufferType getBufferingType()
    { return currentViewer->getBufferingType(); }
  
  // Turn viewing on/off (Default to on) in the viewers.
  void setViewing(SbBool onOrOff)
    { currentViewer->setViewing(onOrOff); }
  SbBool isViewing()
    { return currentViewer->isViewing(); }
  
  // Set/get the level of transparency type
  void setTransparencyType(SoGLRenderAction::TransparencyType type)
    { currentViewer->setTransparencyType(type); }
  SoGLRenderAction::TransparencyType getTransparencyType()
    { return currentViewer->getTransparencyType(); }
  
  // returns the current render area widget
  SoWidget getRenderAreaWidget()
    { return currentViewer->getRenderAreaWidget(); }
  
#ifdef EXPLORER
  // set the EXPLORER user mode callback routine
  void setUserModeEventCallback(SoWinRenderAreaEventCB *fcn);
#endif /* EXPLORER */
  
  // Flags for light menu creation
  static const int SV_LIGHT_NEW_FLAG;
  static const int SV_LIGHT_DEFNAME_FLAG;
  
  //protected:
#ifdef _WIN32
  HMENU hLightMenu;
  ULONG nFirstLightMenuId;
#endif
  LPTSTR envFileName;
  
  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;
  
  // Support for menus in the popup planes
  SoWidget popupWidget;
  
  // Stuff to do after the component has been realized (shown)
  virtual void afterRealizeHook();
  
  //private:
  // Scene graph data
  SoSelection *selection; // the same user supplied graph
  SoSeparator *sceneGraph; // viewer maintained scenegraph
  SoSeparator *docSceneRoot; // user supplied scene graph
  
  // Lights, camera, environment!
  SoGroup *lightsCameraEnvironment;
  SoLabel *envLabel;
  SoEnvironment *environment;
  SoGroup *lightGroup;
  SoGroup *t_Group;
  int lightGroupIX;
  SoCamera *pCamera;
  
  void createLightsCameraEnvironment();
  
  SoGroup *getParentNode(SoNode *);
  
  // Selection highlight
  SoBoxHighlightRenderAction *highlightRA;
  
  //
  // Widgets and menus
  //

  // our topmost form widget
  SoWidget mgrWidget;
  // topbar menu widget
  SoWidget menuWidget;
  SbBool showMenuFlag;

#ifndef _WIN32
  // list of menu items data
  SoSceneViewerData *menuItems;
#endif
  
  SoWidget buildWidget(SoWidget parent);
  void buildAndLayoutMenu(SoWidget parent);
  void buildAndLayoutViewer(SoWinFullViewer *vwr);
  
  // callback for all menu buttons to perform action
#ifndef _WIN32
  static void processTopbarEvent(SoWidget, SoSceneViewerData *,
                                 XmAnyCallbackStruct *);
#endif
  // callback when a menu is displayed
  static void menuDisplay(SoWidget, SoSceneViewerData *, XtPointer);
  
  // this is called after objects are added/deleted or the selection changes
  void updateCommandAvailability();
  
  //
  // File
  //

  // file reading methods
  int fileMode;
  LPTSTR fileName;
  SbBool useShowcaseBrowser;
  void getFileName();
#ifndef _WIN32
  SbBool doFileIO(LPCTSTR filename);
#endif
  SbBool readFile(LPCTSTR filename);
  SbBool writeFile(LPCTSTR filename);
  SbBool readEnvFile(LPCTSTR filename);
  SbBool writeEnvFile(LPCTSTR filename);
  void deleteScene();
  void save();
  
  // cameras
  void removeCameras(SoGroup *root);
  // Returns the last scene kit camera in a scene.
  SoCamera *getLastSceneKitCamera(SoGroup *root);
  // Copies our camera into the last scene kit camera in a scene.
  void setLastSceneKitCamera(SoGroup *root, SoCamera *theCam);
  // Switches off/ restores camera num settings of scenekits.
  void switchOffSceneKitCameras(SoGroup *root);
  void restoreSceneKitCameras(SoGroup *root);
  // Copies from given camera into this viewer's camera, if types match.
  void setCameraFields(SoCamera *fromCam);
  SbDict *sceneKitCamNumDict;
  
  // motif vars for file reading/writting
#ifndef _WIN32
  SoWidget fileDialog;
  static void fileDialogCB(SoWidget, SoSceneViewer *,
                           XmFileSelectionBoxCallbackStruct *);
#endif
  
  SbBool feedbackShown;
  
  void showAboutDialog();
  
  //
  // Edit
  //

  // Select parent, if there is one; select everything.
  void pickParent();
  void pickAll();
  
  // for copy/paste 3d data
  SoWinClipboard *clipboard;
  void destroySelectedObjects();
  
  // Paste callback - invoked when paste data transfer is complete
  void pasteDone(SoPathList *pathList);
  static void pasteDoneCB(void *userData, SoPathList *pathList);
  
  //
  // Viewing
  //

  SoWinFullViewer *viewerList[4]; // list of viewers
  SvEViewer whichViewer; // current viewer ID
  SoWinFullViewer *currentViewer; // current viewer pt
  
  void switchToViewer(SvEViewer newViewer);
  
  // Environment: fog, antialiasing
  SbBool fogFlag; // Fog on/off
  SbBool antialiasingFlag; // AA-ing on/off
  
  // Background color
  MyColorEditor *backgroundColorEditor;
  const SbColor & getBackgroundColor()
    { return currentViewer->getBackgroundColor(); }
  void editBackgroundColor(); // Invokes color editor on bkg
  static void backgroundColorCallback(void *userData,
                                      const SbColor *color);
  
  //
  // Editors
  //
  
  SbBool ignoreCallback;
  SoMaterial *findMaterialForAttach(const SoPath *target);
  SoPath *findTransformForAttach(const SoPath * target);
  // Callback used by Accum state action created by findMaterialForAttach
  static SoCallbackAction::Response findMtlPreTailCB(void *data, 
                                                     SoCallbackAction *accum,
                                                     const SoNode *);
  
  // Material editor
  SoWinMaterialEditor *materialEditor;
  void createMaterialEditor();
  
  // Color editor
  MyColorEditor *colorEditor;
  void createColorEditor();
  
  //
  // Manips
  //

  SvEManipMode curManip;
  SbBool curManipReplaces;
  // list of selection/manip/xfPath triplets.
  SvManipList *maniplist;
  
  // replaces manips with the given type for all selected objects.
  void replaceAllManips(SvEManipMode manipType);
  
  // attaches a manipulator
  void attachManip(SvEManipMode manipType, SoPath *p);
  void attachManipToAll(SvEManipMode manipType);
  
  // detaches a manipulator
  void detachManip(SoPath *p);
  void detachManipFromAll();
  
  // Temporarily remove manips for writing, printing, copying, etc.
  // and restore later
  void removeManips();
  void restoreManips();
  
  // Callback to adjust size of scale tabs. Used only for SoTabBoxManip
  // Added to viewer as a finishCallback.
  static void SoSceneViewer::adjustScaleTabSizeCB(void *, SoWinViewer *);
  
  //
  // Lighting
  //

  SoWinDirectionalLightEditor *headlightEditor;
  SvLightData *headlightData;
  SvLightData *addLightEntry(SoLight *light, SoSwitch *lightSwitch, int);
  void setupLightListFromSceneGraph();
  void addLightMenuEntry(SvLightData *);
  void turnLightOnOff(SvLightData *data, SbBool flag);
  void editLight(SvLightData *data, SbBool flag);
  static void lightSubmenuDisplay(SoWidget, SvLightData *, void *);
  void transferDirectionalLightLocation(SvLightData *data);
  
  int user_directional_lightno, user_point_lightno, user_spot_lightno;
  
#ifdef _WIN32
  static void headlightEditorCloseCB(void *userData, SoWinComponent *comp);
  static void lightColorEditorCloseCB(void *userData, SoWinComponent *comp);
#endif 
  
  // vars to make the light manips all the same size
  void calculateLightManipSize();
  float lightManipSize;
  SbBool calculatedLightManipSize;
  
  // temporary remove/add the light manip geometry of the attached manips
  // (used for file writting and printing)
  void removeAttachedLightManipGeometry();
  void addAttachedLightManipGeometry();
  
  // Ambient lighting color
  MyColorEditor *ambientColorEditor;
  void editAmbientColor(); // Invokes color editor on amb
  static void ambientColorCallback(void *userData, const SbColor *color);
  
  //
  // Selection
  //

  // manages changes in the selection.
  static void deselectionCallback(void *userData, SoPath *obj);
  static void selectionCallback(void *userData, SoPath *obj);
  static SoPath * pickFilterCB(void *userData, const SoPickedPoint *pick);
  
  //
  // Convenience routines
  //
  static SbBool isAffectedByTransform(SoNode *node);
  static SbBool isAffectedByMaterial(SoNode *node);
  
#ifdef EXPLORER
  //
  // user pick function
  //

  SoWinRenderAreaEventCB *userModeCB;
  void *userModedata;
  SbBool userModeFlag;
#endif /* EXPLORER */
  
  void constructorCommon(SoSelection *root, 
                         const char* envFile, 
                         SbBool buildNow);
};


class SoWinColorEditor;
class SoTranslation;
class SoScale;
class SoLight;
class SoSwitch;

class IVF_API SvLightData { 

 public:

  // Constructor inits everything to NULL
  SvLightData();
  
  SoSceneViewer *classPt;
  SoSwitch *lightSwitch;
  // for placing a directional light manip
  SoTranslation *translation;
  SoScale *scale;
  SoLight *light;
  SoScale *scaleInverse;
  SoTranslation *translationInverse;
  SoType type;
  LPTSTR name;
  SoWinColorEditor *colorEditor;
  SbVec3f position;
  SbBool isManip();
  // Used to remember what it was when
  // they all get turned off for writing,
  // printing, etc.
  SbBool shouldBeManip; 
  SoWidget cascadeWidget;
  SoWidget submenuWidget;
  SoWidget onOffWidget;
  SoWidget iconWidget;
  SoWidget editColorWidget;
  SoWidget removeWidget;
};

#ifdef _WIN32
#  include <Inventor/Win/SoWinEndStrict.h>
#endif

#endif /* _SCENE_VIEWER_ */
