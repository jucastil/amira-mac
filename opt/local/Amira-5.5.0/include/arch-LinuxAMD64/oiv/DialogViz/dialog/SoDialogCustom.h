/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_CUSTOM_
#define  _SO_DIALOG_CUSTOM_

#include <DialogViz/dialog/SoDialogComponent.h>

/**
 * @VSGEXT Dialog Custom node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node creates a widget that can be used as a container for 
 *   building another widget inside. This node can manage only one
 *   widget. See the Example section below.
 * 
 * @FILE_FORMAT_DEFAULT
 *   DialogCustom {
 *   @TABLE_FILE_FORMAT
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
 * @EXAMPLE
 *    Here is an example of how assign a widget to the SoDialogCustom, and use it.
 * 
 *  <PRE>
 *      // create and build the dialog scene graph
 *      SoTopLevelDialog * myTopLevelDialog = new SoTopLevelDialog();
 *      
 *      SoDialogCustom * myDialogCustom = new SoDialogCustom();
 *              myTopLevelDialog->addChild(myDialogCustom);
 *              myTopLevelDialog->buildDialog( parent, buildInsideParent );
 *              myTopLevelDialog->show();
 *
 *      // Set an examinerViewer in the dialogCustom component.
 *      // Here, we have to get the custom widget and set it has the parent of the 
 *      // new widget. (For examiner viewer, pass TRUE as third param to build inside parent.)
 *  SoXtExaminerViewer* myViewer = new SoXtExaminerViewer(custom->getWidget(), "", TRUE);
 *      
 *      // Add a scene graph in viewer and show.
 *  myViewer->setSceneGraph(new SoCube());
 *  myViewer->show();
 *  </PRE>
 *
 * @SEE_ALSO
 *   SoDialogCheckBox,
 *   SoDialogCheckBoxLauncher,
 *   SoDialogComboBox,
 *   SoDialogRadioButtons,
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

class DIALOGVIZ_API SoDialogCustom : public SoDialogComponent  
{
  SO_DG_HEADER(SoDialogCustom);

 public:
  /**
   * Constructor
   */
  SoDialogCustom();

  /**
   *  Returns the custom base widget.
   */
  SoWidget getWidget();

  /*==============================================================================*/
 SoINTERNAL public:
  static  void initClass();
  static  void exitClass();
  virtual void buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  void addChildWidget();

 protected:
  virtual ~SoDialogCustom();

 private:
  SoWidget m_childWidget;

  virtual void changeEdgeStyle();
};

#endif // _SO_DIALOG_CUSTOM_
