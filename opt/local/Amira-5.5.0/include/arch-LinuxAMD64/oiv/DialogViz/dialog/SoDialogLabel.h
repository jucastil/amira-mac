/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_LABEL_
#define  _SO_DIALOG_LABEL_

#include <DialogViz/dialog/SoDialogComponent.h>

/**
 * @VSGEXT Class that creates an SoDialogLabel node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node creates a label component for the dialog. This node is represented
 *   visually only by a widget containing a string.
 *
 *   @IMAGE DialogLabel.jpg
 *
 *   SoDialogLabel supports multi-line mode. Lines must be separated by a newline
 *   (\\n) character.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogLabel {
 *   @TABLE_FILE_FORMAT
 *       @TR // fields from SoDialogComponent
 *       @TR width                   @TD 0
 *       @TR height                  @TD 0
 *       @TR fixedWidth              @TD FALSE
 *       @TR fixedHeight             @TD FALSE
 *       @TR minWidth                @TD 0
 *       @TR maxWidth                @TD 0
 *       @TR minHeight               @TD 0
 *       @TR maxHeight               @TD 0
 *       @TR margin                  @TD 0
 *       @TR edgeStyle               @TD NONE
 *       @TR labelVisibility         @TD TRUE
 *       @TR // fields from SoDialogViz
 *       @TR enable                  @TD TRUE
 *       @TR label                   @TD ""
 *       @TR labelAlignment          @TD LEFT
 *       @TR auditorID             @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE sodialoglabel.cat.html
 *
 * @SEE_ALSO
 *   SoDialogCheckBox,
 *   SoDialogCheckBoxLauncher,
 *   SoDialogComboBox,
 *   SoDialogRadioButtons,
 *   SoDialogCustom,
 *   SoDialogEditText,
 *   SoColumnDialog,
 *   SoRowDialog,
 *   SoTabDialog,
 *   SoDialogPushButton,
 *   SoDialogPushButtonLauncher,
 *   SoDialogSeparator,
 *   SoDialogIntegerSlider,
 *   SoDialogRealSlider 
 *
 */

class DIALOGVIZ_API SoDialogLabel : public SoDialogComponent
{
  SO_DG_HEADER(SoDialogLabel);

 public:

  /**
   * Constructor.
   */
  SoDialogLabel();

/*==============================================================================*/
SoINTERNAL public:
  virtual void    buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  static  void    initClass();
  static  void    exitClass();
  virtual void    updateFromSensor(SoSensor* sensor);
          void    updateLabelWidget();

protected:

  virtual         ~SoDialogLabel();
  virtual SbVec2i32 getComponentInitSize();
  virtual void      getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  virtual SbVec2i32 getLabelInitSize();

private:
  SbVec2i32 m_ollSize;

  void    createLabelWidget();

  // geometry inherit from SoDialogViz
  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);
  virtual void changeLabel();
  virtual void changeLabelAlignment();
  virtual void changeEdgeStyle();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:

protected:

  SO_DG_CATALOG_ENTRY_HEADER(labelSep);
  SO_DG_CATALOG_ENTRY_HEADER(labelProp);

  SoText3 *labelText;
  SoTranslation *labelTextTranslation;

private:

  void create3DDialogLabel();
  void update3DLabel();

  virtual void change3DLabel();
  virtual void change3DLabelAlignment();

///////////////////////////////////////////////////////////////////////////////////////

};


#endif // _SO_DIALOG_LABEL_
