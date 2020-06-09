/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_ROW_DIALOG_
#define  _SO_ROW_DIALOG_

#include <DialogViz/dialog/SoDialogGroup.h>

/**
 * @VSGEXT Class that creates the dialog row container.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This class creates a new widget that consists of a set of SoDialogComponents
 *   arranged by row.
 *   The #rowSpacing field specifies the space between each row.
 *   You can add, insert, and remove dialog components (SoDialogComponent) by using 
 *   the addChild(),
 *   insertChild() and removeChild() methods. 
 *
 * @FILE_FORMAT_DEFAULT
 *   RowDialog {
 *   @TABLE_FILE_FORMAT
 *       @TR rowSpacing              @TD 0
 *       @TR // fields from SoDialogGroup
 *       @TR verticalScrollBar       @TD TRUE
 *       @TR horizontalScrollBar     @TD TRUE
 *       @TR scrollPolicy            @TD AUTO
 *       @TR windowResizedByChildren @TD TRUE
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
 *       @TR labelAlignment          @TD RIGHT
 *       @TR auditorID             @TD ""
 *   @TABLE_END
 *   }
 * 
 * @SEE_ALSO
 *   SoColumnDialog,
 *   SoTabDialog,
 *   SoDialogGroup
 *
 */

class DIALOGVIZ_API SoRowDialog : public SoDialogGroup  
{
  SO_DG_HEADER(SoRowDialog);

 public:

  /**
   * Specifies the space between each row. Default is zero.
   */
  SoSFInt32 rowSpacing;

  /**
   * Constructor.
   */
  SoRowDialog();

  /*==============================================================================*/
 SoINTERNAL public:
  virtual void buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  static  void initClass();
  static  void exitClass();
  virtual void updateFromSensor(SoSensor* sensor);

 protected:
  virtual      ~SoRowDialog();
  virtual void fixSizeWithBorder(SbVec2i32 &size, int revert = 1);

 private:
  void      computeNewChildrenHeight(SbVec2i32 &rSize);
  void      getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  void      fixPosWithComponentBorder(SbVec2i32 &pos);
  virtual SbVec2i32 getComponentInitSize();
  virtual void      setChildrenComponentSize();
  virtual void      setChildrenLabelSize();
  void      updateChildren();


  // Field related declares and methods
  FIELD_SENSOR(rowSpacing);
  void changeRowSpacing();
  virtual void changeEdgeStyle();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:

private:
  void update3DChildren();

///////////////////////////////////////////////////////////////////////////////////////
};

#endif // _SO_ROW_DIALOG_
