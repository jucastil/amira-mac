/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_COLUMN_DIALOG_
#define  _SO_COLUMN_DIALOG_

#include <DialogViz/dialog/SoDialogGroup.h>

/**
 * @VSGEXT Dialog column node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This class creates a new SoWidget that consists of a set of SoDialogComponents
 *   arranged by columns.
 *   The #columnSpacing field specifies the space between each column.
 *   You can add, insert, and remove dialog components (SoDialogComponent) by using 
 *   the addChild(),
 *   insertChild(), and removeChild() methods. 
 *
 * @FILE_FORMAT_DEFAULT
 *   ColumnDialog {
 *   @TABLE_FILE_FORMAT
 *       @TR columnSpacing           @TD 0
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
 *   SoRowDialog,
 *   SoTabDialog,
 *   SoDialogGroup
 *
 */

class DIALOGVIZ_API SoColumnDialog : public SoDialogGroup  
{
  SO_DG_HEADER(SoColumnDialog);

 public:

  /**
   * Spacing between each column. Default is zero.
   */
  SoSFInt32 columnSpacing;

  /**
   * Constructor
   */
  SoColumnDialog();

  /*==============================================================================*/
 SoINTERNAL public:
  virtual void buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  static  void initClass();
  static  void exitClass();
  virtual void updateFromSensor(SoSensor* sensor);

 protected:
  virtual      ~SoColumnDialog();
  virtual void fixSizeWithBorder(SbVec2i32 & size, int revert = 1) ;

 private:

  /* === SIZE COMPUTING METHODS === */
  virtual           SbVec2i32 getComponentInitSize();
          void      getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  virtual void      setChildrenComponentSize();
  virtual void      setChildrenLabelSize();

  void updateChildren();

  /* === FIELDS DECLARATION === */
  FIELD_SENSOR(columnSpacing);

  /* === UPDATE METHODS === */
  // pos and size changes
  void computeNewChildrenWidth(SbVec2i32 &rSize);
  void fixPosWithComponentBorder(SbVec2i32 &pos);

  // local change methods
  void changeColumnSpacing();
  virtual void changeEdgeStyle();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:

private:
  void update3DChildren();

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // SO_COLUMN_DIALOG_
