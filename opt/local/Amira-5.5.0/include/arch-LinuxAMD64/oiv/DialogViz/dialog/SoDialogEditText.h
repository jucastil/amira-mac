/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_EDIT_TEXT_
#define  _SO_DIALOG_EDIT_TEXT_

#include <DialogViz/dialog/SoDialogComponent.h>

class SoDialogEditTextAuditor;
class SoEventCallback;
class SoClipPlane;
class SbLineProjector;

/**
 * @VSGEXT Dialog EditText node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a multi-line editing zone for the dialog.
 *
 *   @IMAGE DialogEditText.jpg
 *
 *   The #editText field represents the text of the editing zone. This field supports
 *   the newline (\\n) character and the tabulation character (\\t).
 *   The #editable field specifies if the user can write new text in the edit zone or not. 
 *   The #multiLine field allows to edit a multiLine text. In this case, a vertical scroll
 *   bar appears at the left side of the component. On windows system, mouse scroll wheel is
 *   supported in the edit area.
 *   The #trigOnEnter field specifies how the associated auditor is triggered. If its value
 *   is TRUE, the event happened only when the \<ENTER> key is pressed. Otherwise, the auditor
 *   is called each time the edit text changes.
 *   It's possible to filter text to be numeric or not by using the #isNumeric field.
 *
 *   Note : On UNIX systems, the auditor call is depending on the #multiLine field value. If the
 *   edit control is multiLine, only the num pad \<ENTER> key will process the auditor, else, in
 *   case multiLine is FALSE, the two \<ENTER> key will do it.
 * 
 *   To add or remove an SoDialogEditTextAuditor, use the addAuditor() and removeAuditor() methods.
 *
 *   You can change the parts in any instance of this editText component using setPart().
 *   The default part geometries are defined as resources for this SoDialogEditText class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/DialogEditText.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogEditText {
 *   @TABLE_FILE_FORMAT
 *       @TR editText         @TD ""
 *       @TR editable         @TD TRUE
 *       @TR trigOnEnter      @TD TRUE
 *       @TR isNumeric        @TD FALSE
 *       @TR multiLine        @TD FALSE
 *       @TR wrapLine         @TD TRUE
 *       @TR // fields from SoDialogComponent
 *       @TR width            @TD 0
 *       @TR height           @TD 0
 *       @TR fixedWidth       @TD FALSE
 *       @TR fixedHeight      @TD FALSE
 *       @TR minWidth         @TD 0
 *       @TR maxWidth         @TD 0
 *       @TR minHeight        @TD 0
 *       @TR maxHeight        @TD 0
 *       @TR margin           @TD 0
 *       @TR edgeStyle        @TD NONE
 *       @TR labelVisibility  @TD TRUE
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD RIGHT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE sodialogedittext.cat.html
 *
 * @SEE_ALSO
 *   SoDialogCheckBox,
 *   SoDialogCheckBoxLauncher,
 *   SoDialogComboBox,
 *   SoDialogRadioButtons,
 *   SoDialogCustom,
 *   SoColumnDialog,
 *   SoRowDialog,
 *   SoTabDialog,
 *   SoDialogLabel,
 *   SoDialogPushButton,
 *   SoDialogPushButtonLauncher,
 *   SoDialogSeparator,
 *   SoDialogIntegerSlider,
 *   SoDialogRealSlider 
 *
 */

class DIALOGVIZ_API SoDialogEditText : public SoDialogComponent  
{
  SO_DG_HEADER(SoDialogEditText);

 public:

  /**
   * String of the edit zone. Default value is an empty string.
   */
  SoSFString editText;

  /**
   * Allows writing in the edit zone. Default is TRUE.
   */
  SoSFBool editable;

  /**
   * Sets multi-line mode. Default is FALSE.
   */
  SoSFBool multiLine;

  /**
   * Sets wraping line mode. Default is TRUE.
   */
  SoSFBool wrapLine;

  /**
   * When trigOnEnter is TRUE, the associated auditor is called only when
   * the \<ENTER\> key is pressed. Otherwise, the auditor is called at
   * any edit text changes. Default is TRUE.
   */
  SoSFBool trigOnEnter;

  /** 
   * Specifies if typed text is numeric only.
   */
  SoSFBool isNumeric;

  /**
   * Constructor.
   */
  SoDialogEditText();

  /**
   * Adds a dialogEditTextAuditor to the current editText component.
   */ 
  void addAuditor(SoDialogEditTextAuditor* auditor);

  /**
   * Removes the specified editTextAuditor from the auditor list.
   */
  void removeAuditor(SoDialogEditTextAuditor* auditor);

  /*==============================================================================*/
 SoINTERNAL public:
  virtual void   buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void   destroyWidget();
  virtual void   eventNotify(unsigned int event, uintptr_t param);
  virtual SoWidget getLabelWidget();
  static  void   initClass();
  static  void   exitClass();
  virtual void   updateFromSensor(SoSensor* sensor);
  void      processEvent(SbBool force);

  void      updateLabelWidget();                // update label widget position and size
  void      updateEditTextWidget();             // update edit widget position and size

  void   applyDlgCptAuditor();

protected:
  SoWidget m_editTextWidget;
          
  virtual        ~SoDialogEditText();

private:
  SbVec2i32 m_oeSize, m_olSize;
  SbBool m_fromSensor;

  void createLabelWidget();
  void createEditTextWidget();
  virtual SbVec2i32 getComponentInitSize();
  virtual void getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  virtual void changeEditable();
  virtual void changeMultiLine();
  virtual void changeWrapLine();
  virtual void changeEditText();
  virtual void changeEnable();                     // update edit and label widget state
  virtual void changeWidgetEnable(SbBool state);
  virtual void changeLabel();                      // change the label widget text
  virtual void changeLabelAlignment();             // change the label widget alignment
  virtual void changeLabelVisibility();            // show or hide the label widget.
  virtual void changeEdgeStyle();

  virtual void setFocus();                         // set focus to current edit area

  // Declare Field Sensors.
  FIELD_SENSOR(editText);
  FIELD_SENSOR(editable);
  FIELD_SENSOR(multiLine);
  FIELD_SENSOR(wrapLine);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogEditText; // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);
  void insertCharTo3DText(char c);
  void removeCharIn3DText();

protected:
  SO_DG_CATALOG_ENTRY_HEADER( labelSep      );
  SO_DG_CATALOG_ENTRY_HEADER( labelSwitch   );
  SO_DG_CATALOG_ENTRY_HEADER( labelProp     );

  SO_DG_CATALOG_ENTRY_HEADER( scrollVSwitch );
  SO_DG_CATALOG_ENTRY_HEADER( downSep       );
  SO_DG_CATALOG_ENTRY_HEADER( downSwitch    );
  SO_DG_CATALOG_ENTRY_HEADER( downPressed   );
  SO_DG_CATALOG_ENTRY_HEADER( downReleased  );
  SO_DG_CATALOG_ENTRY_HEADER( upSep         );
  SO_DG_CATALOG_ENTRY_HEADER( upSwitch      );
  SO_DG_CATALOG_ENTRY_HEADER( upPressed     );
  SO_DG_CATALOG_ENTRY_HEADER( upReleased    );
  SO_DG_CATALOG_ENTRY_HEADER( scrollVSep    );
  SO_DG_CATALOG_ENTRY_HEADER( scrollVBack   );
  SO_DG_CATALOG_ENTRY_HEADER( scrollVFrame  );
  SO_DG_CATALOG_ENTRY_HEADER( cursorVSep    );
  SO_DG_CATALOG_ENTRY_HEADER( cursorVFrame  );

  SO_DG_CATALOG_ENTRY_HEADER( scrollHSwitch );
  SO_DG_CATALOG_ENTRY_HEADER( leftSep       );
  SO_DG_CATALOG_ENTRY_HEADER( leftSwitch    );
  SO_DG_CATALOG_ENTRY_HEADER( leftPressed   );
  SO_DG_CATALOG_ENTRY_HEADER( leftReleased  );
  SO_DG_CATALOG_ENTRY_HEADER( rightSep      );
  SO_DG_CATALOG_ENTRY_HEADER( rightSwitch   );
  SO_DG_CATALOG_ENTRY_HEADER( rightPressed  );
  SO_DG_CATALOG_ENTRY_HEADER( rightReleased );
  SO_DG_CATALOG_ENTRY_HEADER( scrollHSep    );
  SO_DG_CATALOG_ENTRY_HEADER( scrollHBack   );
  SO_DG_CATALOG_ENTRY_HEADER( scrollHFrame  );
  SO_DG_CATALOG_ENTRY_HEADER( cursorHSep    );
  SO_DG_CATALOG_ENTRY_HEADER( cursorHFrame  );

  SO_DG_CATALOG_ENTRY_HEADER( editSep       );
  SO_DG_CATALOG_ENTRY_HEADER( frameSep      );
  SO_DG_CATALOG_ENTRY_HEADER( frameSwitch   );
  SO_DG_CATALOG_ENTRY_HEADER( frame         );
  SO_DG_CATALOG_ENTRY_HEADER( editFrame     );
  SO_DG_CATALOG_ENTRY_HEADER( textSep       );
  SO_DG_CATALOG_ENTRY_HEADER( textProp      );

  SO_DG_CATALOG_ENTRY_HEADER( caretSep      );
  SO_DG_CATALOG_ENTRY_HEADER( caretSwitch   );
  SO_DG_CATALOG_ENTRY_HEADER( caretFrame    );

private:

  SoText3 *editTextText, *editTextLabel;
  SoTranslation *editTextLabelTranslation, *editTextFrameTranslation;
  SoTranslation *editTextTextTranslation, *scrollVCursorTranslation, *scrollHCursorTranslation;
  SoTranslation *editTextDownTranslation, *editTextUpTranslation;
  SoTranslation *editTextLeftTranslation, *editTextRightTranslation;
  SoTranslation *editTextScrollVTranslation, *scrollVCursorPosTranslation, *editTextCaretTranslation;
  SoTranslation *editTextScrollHTranslation, *scrollHCursorPosTranslation, *editTextScrollTextTranslation;
  SoScale *editTextFrameScale;
  SoScale *editTextButtonScale, *editTextScrollVScale, *editTextScrollHScale;
  SoScale *scrollVCursorScale, *scrollHCursorScale, *editTextCaretScale;
  SoTransform *editTextFrameTransform, *scrollVFrameTransform, *scrollHFrameTransform;
  SoClipPlane *editTextClipPlaneTop, *editTextClipPlaneBottom;
  SoClipPlane *editTextClipPlaneLeft, *editTextClipPlaneRight;

  SoEventCallback* eventCB;
  SbBool m_isEditing;
  SbLineProjector* m_lineProj;
  SbVec3f m_initialVPos, m_initialHPos;
  int m_currentPos;
  int m_current3DLine;
  int m_current3DCaretPos;

  SbBox3f m_textCachedBBox;

  void create3DDialogEditText();
  void update3DEditText();
  void update3DLabel();
  void update3DCursors();
  void update3DScrollBars();
  void update3DTextPosition();
  void update3DTextScrollPosition();
  void move3DCursor(float inc);
  void move3DCaret(int line, int pos);
  void update3DTextCache(int prevLine);
  void apply3DEvent(SbString str);

  void change3DEditText();
  virtual void change3DLabelVisibility();
  virtual void change3DLabel();
  virtual void change3DLabelAlignment();
  virtual void set3DInactive();

  static void startCB3D( void *, SoDragger *inDragger );
  static void motionCB3D( void *, SoDragger *inDragger );
  static void finishCB3D( void *, SoDragger *inDragger );
  static void processKeyEvents(void *inDragger, SoEventCallback *cb);
  void draggerStartCallback3D();
  void draggerMotionCallback3D();
  void draggerFinishCallback3D();

  void finish3DEditing();

  static SbBool m_isSkinLoaded;

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_DIALOG_EDIT_TEXT_
