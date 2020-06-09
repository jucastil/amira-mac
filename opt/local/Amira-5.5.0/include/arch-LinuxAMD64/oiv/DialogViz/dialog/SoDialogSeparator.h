/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_DIALOG_SEPARATOR_
#define  _SO_DIALOG_SEPARATOR_

#include <DialogViz/dialog/SoDialogComponent.h>

/**
 * @VSGEXT Class to create a separator line.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node creates a separator line. When the SoDialogSeparator is a
 *   SoTopLevelDialog or SoRowDialog immediate child, the separator line is horizontal.
 *   When used as an SoColumnDialog child, the separator is represented by a vertical line.
 * 
 *   You can change the parts in any instance of this separator component using setPart().
 *   The default part geometries are defined as resources for this SoDialogSeparator class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/DialogSeparator.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   DialogSeparator {
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
 * @CATALOG_PARTS_INCLUDE sodialogseparator.cat.html
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
 *   SoDialogLabel,
 *   SoDialogPushButton,
 *   SoDialogPushButtonLauncher,
 *   SoDialogIntegerSlider,
 *   SoDialogRealSlider 
 *
 */

class DIALOGVIZ_API SoDialogSeparator : public SoDialogComponent  
{
  SO_DG_HEADER(SoDialogSeparator);

 public:

  /**
   * Constructor.
   */
  SoDialogSeparator();


/*==============================================================================*/
SoINTERNAL public:
  virtual void   buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool isActive2d);
  virtual void   destroyWidget();
  static  void   initClass();
  static  void   exitClass();
  virtual void   updateFromSensor(SoSensor* ) {};
          void   setOrientationHorz(SbBool orentation = TRUE);
          void   updateSeparatorWidget();

protected:
          
  virtual ~SoDialogSeparator();

private:
  SoWidget m_separatorWidget;
  SbBool m_orientationHorz;

  void   createSeparatorWidget();
  virtual void   getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  virtual void changeEdgeStyle();
    

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* DialogSeparator; // Internal default skins.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:
  SO_DG_CATALOG_ENTRY_HEADER(frameSep);
  SO_DG_CATALOG_ENTRY_HEADER(frameSwitch);
  SO_DG_CATALOG_ENTRY_HEADER(hFrame);
  SO_DG_CATALOG_ENTRY_HEADER(vFrame);

private:
  SoScale* separatorFrameScale;
  static SbBool m_isSkinLoaded;

  void create3DSeparator();
  void update3DSeparator();

///////////////////////////////////////////////////////////////////////////////////////
};

#endif // _SO_DIALOG_SEPARATOR_
