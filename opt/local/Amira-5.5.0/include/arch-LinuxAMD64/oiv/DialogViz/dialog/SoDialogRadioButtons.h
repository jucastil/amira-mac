/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_RADIO_BUTTONS_
#define  _SO_DIALOG_RADIO_BUTTONS_

#include <DialogViz/dialog/SoDialogChoice.h>
#include <DialogViz/SoDialogWidgetList.h>

/**
 * @VSGEXT Dialog radio buttons node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines radio buttons as a one-dialog component.
 *
 *   @IMAGE DialogRadioButtons.jpg
 *
 *   This component does not support \\n (newline) characters in its fields.
 *
 *   @TABLE_1B
 *   @TR @TABLE_0B
 *   @TR #labelAlignment field change
 *   @TD LEFT
 *   @TD CENTER
 *   @TD RIGHT
 *   @TR
 *   @TD @IMAGE DialogRadioButtons_labelAlignment_LEFT.jpg
 *   @TD @IMAGE DialogRadioButtons_labelAlignment_CENTER.jpg
 *   @TD @IMAGE DialogRadioButtons_labelAlignment_RIGHT.jpg
 *   @TABLE_END
 *   @TABLE_END
 *
 *   You can change the parts in any instance of this radio button component using setPart().
 *   The default part geometries are defined as resources for this SoDialogRadioButtons class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/DialogRadioButtons.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogRadioButtons {
 *   @TABLE_FILE_FORMAT
 *       @TR // fields from SoDialogChoice
 *       @TR items            @TD []
 *       @TR selectedItem     @TD 0
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
 * @CATALOG_PARTS_INCLUDE sodialogradiobuttons.cat.html
 *
 * @SEE_ALSO
 *   SoDialogCheckBox,
 *   SoDialogCheckBoxLauncher,
 *   SoDialogComboBox,
 *   SoDialogCustom,
 *   SoDialogEditText,
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

class DIALOGVIZ_API SoDialogRadioButtons : public SoDialogChoice  
{
  SO_DG_HEADER(SoDialogRadioButtons);

 public:

  /**
   * Constructor.
   */
  SoDialogRadioButtons();

  /*==============================================================================*/
 SoINTERNAL public:
  virtual void   buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void   destroyWidget();
  void   eventNotify(unsigned int event, uintptr_t lParam);
  static  void   initClass();
  static  void   exitClass();
  virtual void updateFromSensor(SoSensor* sensor);
  void drawLabel();
  virtual void resetSize();

  void    updateLabelWidget();
  void    updateRadioButtonsWidget();

 protected:

  SoDialogWidgetList m_rbWidgetList;

  SbVec2i32* m_buttonSize;
  SbVec2i32* m_buttonMin;
  SbVec2i32* m_buttonMax;
  int        m_arrayNumButtons;
  int        m_cptToResize;

  virtual         ~SoDialogRadioButtons();

 private:
  SbVec2i32 m_orSize;
  SoWidget m_labelTextWidget;
  SoWidget m_labelFrameWidget;
  SbBool m_itemsChangeFromSensor;

  void    computeNewButtonsHeight(SbVec2i32 &rSize);
  void    createLabelWidget();
  void    createRadioButtonsWidget(int index);
  virtual SbVec2i32 getComponentInitSize();
  virtual SbVec2i32 getLabelInitSize();
  virtual void    getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  // reflex function when fields change
  virtual void changeLabelVisibility();
  virtual void changeLabelAlignment();
  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);
  virtual void changeLabel();
  virtual void changeEdgeStyle();
  virtual void changeSelectedItem();
          void changeItems();
          void changeItemText(int index, SbString newText);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogRadioButtons; // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

 protected:
  SO_DG_CATALOG_ENTRY_HEADER( frameSep     );
  SO_DG_CATALOG_ENTRY_HEADER( frame        );
  SO_DG_CATALOG_ENTRY_HEADER( labelSep     );
  SO_DG_CATALOG_ENTRY_HEADER( labelSwitch  );
  SO_DG_CATALOG_ENTRY_HEADER( labelProp    );
  SO_DG_CATALOG_ENTRY_HEADER( itemsSep     );
  SO_DG_CATALOG_ENTRY_HEADER( itemSep      );
  SO_DG_CATALOG_ENTRY_HEADER( itemFrameSep );
  SO_DG_CATALOG_ENTRY_HEADER( itemFrame    );
  SO_DG_CATALOG_ENTRY_HEADER( itemBtnSep   );
  SO_DG_CATALOG_ENTRY_HEADER( itemBtnSwtch );
  SO_DG_CATALOG_ENTRY_HEADER( stateOff     );
  SO_DG_CATALOG_ENTRY_HEADER( stateOn      );
  SO_DG_CATALOG_ENTRY_HEADER( itemTextSep  );
  SO_DG_CATALOG_ENTRY_HEADER( itemTextProp );

  SoScale *radioLabelFrameScale, *radioItemFrameScale, *radioItemButtonScale;
  SoText3 *radioItemText;
  SoTranslation *radioLabelFrameTranslation, *radioTranslation, *radioItemTranslation;
  SoTranslation *radioItemButtonTranslation, *radioItemTextTranslation;
  SoTransform *radioLabelFrameTransform, *radioItemFrameTransform;

 private:
  SoNodeList m_item3DTextList;
  SoNodeList m_item3DItemList;
  SoNodeList m_item3DSwList;
  static SbBool m_isSkinLoaded;

  SbBox3f m_itemTextCachedBBox;

  void create3DDialogRadioButtons();
  void update3DRadioButtons();
  void update3DLabel();

  // local change methods
          void change3DItems();
  virtual void change3DSelectedItem();

  // inherited change methods from SoDialogComponent
  virtual void change3DLabelVisibility();

  // inherited change methods from SoDialogViz
  virtual void change3DLabel();
  virtual void change3DLabelAlignment();

  static void finishCB3D( void *, SoDragger *inDragger );
  void draggerFinishCallback3D();

///////////////////////////////////////////////////////////////////////////////////////
};

#endif // _SO_DIALOG_RADIO_BUTTONS_
