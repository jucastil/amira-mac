/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_VIZ_
#define _SO_DIALOG_VIZ_

#include <SoVersion.h>

// On Windows the "comment" pragma will automatically add our DialogViz
// library to the application's link string.

#ifdef _WIN32
#  if !defined(SOQT) || defined(LOAD_DIALOGVIZ_FOR_IVTUNE)
#    if defined(_DEBUG)
#      define __DIALOGVIZDLL "DialogVizWinD.dll"
#      define __DIALOGVIZLIB "DialogVizWinD.lib"
#    else
#      define __DIALOGVIZDLL "DialogVizWin.dll"
#      define __DIALOGVIZLIB "DialogVizWin.lib"
#    endif
#  else
#    if defined(_DEBUG)
#      define __DIALOGVIZDLL "DialogVizQtD.dll"
#      define __DIALOGVIZLIB "DialogVizQtD.lib"
#    else
#      define __DIALOGVIZDLL "DialogVizQt.dll"
#      define __DIALOGVIZLIB "DialogVizQt.lib"
#    endif
#  endif
#  if !defined(DialogVizWin_EXPORTS) && !defined(DialogVizQt_EXPORTS)
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__DIALOGVIZLIB)
#    endif
#  endif
#else
#  if !defined(SOQT) || defined(LOAD_DIALOGVIZ_FOR_IVTUNE)
#    define __DIALOGVIZDLL "libDialogVizXt"
#  else
#    define __DIALOGVIZDLL "libDialogVizQt"
#  endif
#endif

#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>
#if !defined(LOAD_DIALOGVIZ_FOR_IVTUNE) || defined(SCALEVIZGUIQTBUILD)
#include <Inventor/Xt/SoXt.h>
#else
//#undef SoWidget
//#define SoWidget QWidget
#endif

#include <DialogViz/auditors/SoAuditor.h>
#include <DialogViz/dialog/SoSubDialogViz.h>

class SoGetMatrixAction;
class SoMaterial;
class SoNode;
class SoPickStyle;
class SoSearchAction;
class SoText3;
class SoTopLevelDialog;
class SoTransform;
class SoTranslation;

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoDialogViz,__DIALOGVIZDLL)

/**
 * @VSGEXT Abstract base class for DialogViz components
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This is the abstract base class for all DialogViz (user interface)
 *   nodes. It defines common methods and fields that all DialogViz
 *   nodes inherit. It is also used to initialize DialogViz.
 *
 *   SoDialogViz::init must be called before creating any DialogViz
 *   nodes. 
 *   
 *   The #enable field allows/disallows use of the node.
 *
 *   The #label field specifies the string contained in the left part of a control
 *   or the text on a button. See individual components for their specific usage
 *   of this field.
 *
 *   An auditor ID is a name that identifies a specific component and
 *   is specified using the #auditorID field. Generally, the auditor ID
 *   should be unique. It
 *   allows you to access a specific component from your application program.
 *   - You can use the auditor ID to specify a specific component in order
 *     to modify it. For example, cause a particular check box to be checked.
 *   - When an auditor is called, you can use the auditor ID to determine
 *     which specific component was modified/interacted with. For example,
 *     you can determine which slider was moved.
 *
 *   DialogViz components can be used to build 2D and/or 3D interfaces.
 *   A DialogViz interface definition can be read from an Inventor file
 *   or created programmatically.
 *   To build a 2D user interface, call the buildDialog() method.
 *   To build a 3D user interface, insert the DialogViz nodes in your scene graph.
 *   Note that when using 3D mode, DialogViz nodes are fully built only after
 *   the first rendering traversal is complete.
 * 
 *   When using components as 3D objects in your scene, DialogViz allows the user
 *   to customize the look for each type of component using DialogViz
 *   skin files.
 *   DialogViz components are draggers, and draggers allow their parts to be
 *   redefined. A skin file redefines the 3D geometry for different parts of 
 *   a component.
 *   To use your own skin files, use the setSkin() method, or set the
 *   DIALOGVIZ_SKIN environment variable to specify the path/name of the skin files
 *   directory. By default, the DialogViz skin directory is located at
 *   $OIVHOME/data/DialogViz/Skins/ and the used skin name is "default".
 *   A skin is a collection of several files defining DialogViz component geometry,
 *   colors, etc...
 *   For example, the skin file @B TextProperties.iv@b is used by all of the DialogViz components. 
 *   This skin file can be useful for applying a font, a color, etc. to the text nodes.
 *
 *   The default font for DialogViz components in 2D mode is:
 *   - Windows systems: the default desktop font
 *   - UNIX systems: the font is set to -adobe-helvetica-medium-r-normal--12-0-0-0-p-0-iso8859-1.
 *     If not found, the font is set by the system to a default font (In this case
 *     sizing problems may occur).
 * 
 *   In 3D mode, the font is defined in the TextProperties.iv Inventor file.
 *
 *   2D Mode Limitation: We do not recommend the use of ref(), unref(), 
 *   or unrefNoDelete() when manipulating DialogViz nodes in 2D mode. 
 *   However, these methods can be used as long as you don't destroy 
 *   and re-create nodes or change the hierarchical structure of components.
 *
 * @FILE_FORMAT_DEFAULT
 *    DialogViz {
 *    @TABLE_FILE_FORMAT
 *       @TR label           @TD ""
 *       @TR callbackID      @TD ""
 *       @TR enable          @TD TRUE
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoTopLevelDialog,
 *    SoTopComponent,
 *    SoMenuItem
 *
 */

class DIALOGVIZ_API SoDialogViz : public SoDragger
{
  SO_DG_HEADER(SoDialogViz);

 public:
  /**
   * Enables component. Default is TRUE.
   * If set to FALSE, the component is grayed out and is not usable.
   */
  SoSFBool enable;

  /**
   * Label string of the element. Default is an empty string.
   * This field is used by all derived classes except for SoMenuSeparator, 
   * SoMenuBar, SoDialogCustom, SoDialogSeparator, and SoDialogGroup.
   * This field is the title of the window created by an SoTopLevelDialog.
   * This field supports the newline (\\n) character except for some derived 
   * classes such as SoMenuItem. It supports the tab (\\t) character as well.
   */
  SoSFString  label;

  enum LabelAlignment {
    /** Label is left aligned. */
    LEFT,
    /** Label is center aligned. */
    CENTER,
    /** Label is right aligned (default). */
    RIGHT
  };

  /**
   * Specifies the label alignment. Default is RIGHT.
   */
  SoSFEnum labelAlignment;

  /**
   * Specifies the auditor ID of the node. Default is empty string.
   */
  SoSFString auditorID;

  /**
   * Initalizes the DialogViz classes.
   */
  static void init();

  /**
   * Shuts down the DialogViz module, which includes freeing any
   * internal static memory that it allocated. 
   * Finish methods must be called in the reverse order of the init method calls: 
   * <PRE>    SoDialogViz::finish(); 
   *    SoXt::finish(); 
   *    ... </PRE>
   */
  static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   */
  static bool isInitialized();

  /**
   * Returns a character string identifying the name of the extension.
   */
  static const char *getProductName();

  /**
   * Returns a character string identifying the version of the extension.
   */
  static const char *getVersion();

  /**
   * Loads a DialogViz node from an Inventor file. 
   *    @param filename: Specifies the full path of a file containing DialogViz nodes. This file
   *    is loaded.
   *    @param auditorID: The first DialogViz node in the file having this auditorID is
   * returned. If this parameter 
   * is not supplied or if no DialogViz nodes having this auditorID are found in the
   * file, the first DialogViz node in the file is returned.
   */
  static SoDialogViz* loadFromFile(SbString filename, SbString auditorID = "");

  //  /**
  //   * Shows the component.
  //   */
  //  virtual void show() {};

  //  /**
  //   * Hides the component.
  //   */
  //  virtual void hide() {};
  
  /**
   * Sets the directory for 3D DialogViz component skins. The directory is
   * searched for in the current directory (usually, but not always the
   * directory from which the application was started), and then in 
   * $OIVHOME/data/DialogViz/skins. 
   * Returns TRUE if the specified directory exists, FALSE otherwise.
   * The default skin to use can be set using the DIALOGVIZ_SKIN environment
   * variable.
   */
  static void setSkin(SbString skinName);

  /**
   * Sets a list of directories where to search for skins.
   * Each directory in the list must be separated by a semicolon (;).
   * Using this method overrides the DIALOGVIZ_SKINS_DIR environment value.
   */
  static void setSkinsDirectories(SbString directories);

  /**
   * Returns the skins directory.
   */
  static SbString getSkinsDirectories();

  /**
   * Sets the DialogViz font.
   */
  static void setFont(DG_FONT font);

/*==============================================================================*/
 SoINTERNAL public:
//#pragma deprecated(setSkinsDirectory, getSkinsDirectory)
  static SbBool setSkinsDirectory(SbString directory) { setSkin(directory); return TRUE; }
  static SbString getSkinsDirectory() {return getSkinsDirectories(); }

  static void initClass();
  static void exitClass();

  virtual void  buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 &pos, SbBool is2dRender);
  virtual void  destroyWidget();
  virtual void  updateFromSensor(SoSensor* sensor);
          void  setParent(SoDialogViz* parent);
  virtual void  applyAuditor(SoDialogViz* ) {};
          SoDialogViz* getFirstTopParent(SbBool is2DRender = TRUE, SbBool getLastValidParent = FALSE);
  static  SbVec2i32 getLabelPixelSize(SbString string, SoDialogViz* cpt);
  static DG_FONT getDialogVizFont();

//  static void PrintMemoryInfo(SbString name);

  static void setWidgetFont(SoWidget widget);
  virtual void resetSize() {};

 protected:

  SbString m_cLabel;
  SbBool m_isActive2d;
  SoWidget m_topParentWidget;

  static DG_FONT m_font;

  SoDialogViz();
  virtual ~SoDialogViz();

  static SbString  convertToCString(const SbString& oldString, SoDialogViz* cpt);
  static SbString  convertFromCString(const SbString& oldString, SbBool toEdit = FALSE);
  static void setStringToText3(SoText3* myText, const SbString& inString);

  static SbBool existWidget(SoWidget widget);
  static void   fieldChangedCB(void *guiComponent , SoSensor* sensor);
  static int    getNumLines( const SbString& string);  // retrieve the number of lines in the string.
  
  // reflex functions when fields change
  virtual void changeEnable() {};
  virtual void changeLabel() {};
  virtual void changeLabelAlignment() {};

  // auditor methods
  SoDialogViz* m_parentComponent;
  void addAuditor(SoAuditor* auditor);
  void removeAuditor(SoAuditor* auditor);
  SoAuditor*& getAuditor(int index);
  int getAuditorListLength();

 private:

  static int s_initRefCount;

  static const char *s_versionString;

  SbPList* m_auditorList;
  static SbBool m_errorMsgDelivered;

  // Field sensors declare
  FIELD_SENSOR(enable);
  FIELD_SENSOR(label);
  FIELD_SENSOR(labelAlignment);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* TextProperties; // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);
  static void free3DSkin(SbString partName);
  static void load3DSkin(SbString partName);

  virtual void show3D(SbBool show);
  SbVec3f get3DParentTranslation();
  virtual void set3DParentTranslation(SbVec3f& tsl);
  void apply3DParentTranslation();  // this method need to be applied in each component create method.

  SbBool isBuilt3D();
  SbBool canBeTraversed();
  void setBuilt3D(SbBool built);
  void setCanBeTraversed(SbBool enable);

  virtual void change3DPosition() {};
  virtual void change3DWidgetEnable(SbBool state);

protected:

  SO_DG_CATALOG_ENTRY_HEADER(geomSwitch);

  SoGetBoundingBoxAction* m_boundingBoxAction;
  SoSearchAction* m_searchAction;
  SoGetMatrixAction* m_getMatrixAction;
  SoPickStyle* m_enableNode;
  SoMaterial* m_enableMaterial;

  SbBool isLabelCachedBBox();
  void setLabelCacheBBox(SbBox3f bBox);
  SbBox3f getLabelCachedBBox();

  virtual void change3DEnable();
  virtual void change3DLabel();
  virtual void change3DLabelAlignment() {};

  void loadFontProperties();
  void undoTransformMatrix(SoNode* searchInNode, SoTransform* tsf);
#ifndef HIDDEN_FROM_DOC
  void writeNode(char* file);
#endif

  static void readDefaultSkinsParts( const SbString& fileName, char* defaultSkin );

  float compute3DDepth(SoNode* node);
  void apply3DTranslation(SoNode* node, float& variable, SbVec3f& vec);

  SbBool m_is3DVisible;
  static SoDialogViz* m_lastActive;

  static void set3DCurrentActive(SoDialogViz* dvNode);
  virtual void set3DInactive();

  static int insertTextTo3DText(SbString addStr, SoText3 * text, int line, int pos);
  static int wrap3DTextLine(SoText3* text, int line, float maxWidth, SoGroup* textProp, SoDialogViz* dv);

private:
  SbBox3f m_labelCachedBBox;
  static SbBool m_isSkinLoaded;

  SbBool m_isBuilt3D;
  SbBool m_canBeTraversed;

  static SbString s_skinsPath;

  SoTranslation *m_parentTranslation;
  SbVec3f m_3DParentTranslation;

  void create3DDialogViz();

  static SoGroup *readFromFile( const SbString& fileName );

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_DIALOG_VIZ_
