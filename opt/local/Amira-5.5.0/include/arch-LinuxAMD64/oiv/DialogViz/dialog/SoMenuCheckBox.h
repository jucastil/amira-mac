/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_CHECK_BOX_
#define  _SO_MENU_CHECK_BOX_

#include <DialogViz/dialog/SoMenuItem.h>

class SoMenuCheckBoxAuditor;

/**
 * @VSGEXT Menu pushbutton node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a push button item for a dialog menu.
 *
 *   You can change the parts in any instance of this menu check box using setPart().
 *   The default part geometries are defined as resources for this SoMenuCheckBox class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/MenuCheckBox.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   MenuCheckBox {
 *   @TABLE_FILE_FORMAT
 *       @TR accelerator      @TD ""
 *       @TR state            @TD FALSE
 *       @TR onString         @TD ""
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD LEFT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @anchor SoMenuCheckBox_CatalogParts @BR
 * @CATALOG_PARTS_INCLUDE somenucheckbox.cat.html
 *
 * @SEE_ALSO
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPopup,
 *   SoMenuPushButton,
 *   SoMenuPushButtonLauncher,
 *   SoMenuFileSelection,
 *   SoMenuRadioButtons,
 *   SoMenuSeparator
 *
 */

class DIALOGVIZ_API SoMenuCheckBox : public SoMenuItem  
{
  SO_DG_HEADER(SoMenuCheckBox);

 public:

  /**
   * Specify the state of the check button. When state is FALSE #label is showm,
   * otherwise #onString is shown instead. Default is FALSE
   */
  SoSFBool state;

  /**
   * This string appears when #state is TRUE. If it is empty, #label is used instead.
   * Default is empty string.
   */
  SoSFString  onString;

  /**
   * Defines the menu item accelerator key.
   */
  SoSFString accelerator;

  /**
   * Constructor
   */
  SoMenuCheckBox();

  /**
   * Add a menuCheckBoxAuditor to current CheckBox component.
   */
  void addAuditor(SoMenuCheckBoxAuditor* auditor);

  /**
   * Remove the defined checkBoxAuditor from the auditor list.
   */
  void removeAuditor(SoMenuCheckBoxAuditor* auditor);

  /*==============================================================================*/
 SoINTERNAL public:
  virtual void buildMenu(void* parent, SbBool isActive2d, int index = -1);
  static  void  initClass();
  static  void  exitClass();
  virtual void  menuEvent(void* parent, int itemId);
  virtual void  updateFromSensor(SoSensor* sensor);
  virtual void destroyNoDeleteMenuItem();
  void  applyDlgCptAuditor();

 protected:
  void* m_checkBoxMenuWin;
    
  virtual       ~SoMenuCheckBox();
  virtual void  changeLabel();
  virtual void  changeEnable();

 private:
  void  changeState();
  void  changeOnString();
  void  changeAccelerator();
  void  insertMenuItem(int index);
  void  updateMenuItem();
  virtual SbVec2i32 getItemInitSize();

  FIELD_SENSOR(state);
  FIELD_SENSOR(onString);
  FIELD_SENSOR(accelerator);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* MenuCheckBox; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:

  SO_DG_CATALOG_ENTRY_HEADER( chkSep   );
  SO_DG_CATALOG_ENTRY_HEADER( chkSwtch );
  SO_DG_CATALOG_ENTRY_HEADER( stateOff );
  SO_DG_CATALOG_ENTRY_HEADER( stateOn  );

  SoTranslation* menuCheckBoxShapeTranslation;
  void get3DOnStringCachedBBox(SbVec3f& min, SbVec3f& max);

private:
  SbBox3f m_onStringCachedBBox;
  static SbBool m_isSkinLoaded;

  void create3DCheckBox(int index);
  void update3DCheckBox();

  void change3DState();
  void change3DOnString();

  static void finishCB3D( void *, SoDragger *inDragger );
  virtual void draggerFinishCallback3D();

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_MENU_CHECK_BOX_
