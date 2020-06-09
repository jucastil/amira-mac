/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_PUSH_BUTTON_
#define  _SO_MENU_PUSH_BUTTON_

#include <DialogViz/dialog/SoMenuItem.h>

class SoMenuPushButtonAuditor;

/**
 * @VSGEXT Menu pushbutton node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a push button item for a dialog menu.
 *
 *   You can change the parts in any instance of this menu push button using setPart().
 *   The default part geometries are defined as resources for this SoMenuPushButton class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/MenuPushButton.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   MenuPushButton {
 *   @TABLE_FILE_FORMAT
 *       @TR accelerator      @TD ""
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD LEFT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @anchor SoMenuPushButton_CatalogParts @BR
 * @CATALOG_PARTS_INCLUDE somenupushbutton.cat.html
 *
 * @SEE_ALSO
 *   SoMenuCheckBox,
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPopup,
 *   SoMenuPushButtonLauncher,
 *   SoMenuFileSelection,
 *   SoMenuRadioButtons,
 *   SoMenuSeparator
 *
 */

class DIALOGVIZ_API SoMenuPushButton : public SoMenuItem  
{
  SO_DG_HEADER(SoMenuPushButton);

 public:

  /**
   * Constructor
   */
  SoMenuPushButton();

  /**
   * Defines the menu item accelerator key.
   */
  SoSFString accelerator;

  /**
   * Add a menuPushButtonAuditor to current PushButton component.
   */
  void addAuditor(SoMenuPushButtonAuditor* auditor);

  /**
   * Remove the defined pushButtonAuditor from the auditor list.
   */
  void removeAuditor(SoMenuPushButtonAuditor* auditor);

/*==============================================================================*/
SoINTERNAL public:
  virtual void buildMenu(void* parent, SbBool is2dRender, int index = -1);
  static  void initClass();
  static  void exitClass();
  virtual void updateFromSensor(SoSensor* sensor);
  virtual void menuEvent(void* parent, int itemId);
  virtual void destroyNoDeleteMenuItem();
  void applyDlgCptAuditor();

protected:
  void* m_pushButtonMenuWin;
  virtual ~SoMenuPushButton();

  virtual void changeLabel();
  virtual void changeEnable();

private:
  void insertMenuItem(int index);
  void updateMenuItem();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* MenuPushButton; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:

  SO_DG_CATALOG_ENTRY_HEADER( btnSep   );
  SO_DG_CATALOG_ENTRY_HEADER( btnSwtch );
  SO_DG_CATALOG_ENTRY_HEADER( released );
  SO_DG_CATALOG_ENTRY_HEADER( pressed  );

  SoScale* menuPushButtonFrameScale;
  SoTransform* menuPushButtonFrameTransform;

  virtual void draggerStartCallback3D();
  virtual void draggerFinishCallback3D();
  virtual void add3DCallbackMethods();
  static void startCB3D( void *, SoDragger *inDragger );
  static void finishCB3D( void *, SoDragger *inDragger );

private:
  FIELD_SENSOR(accelerator);
  static SbBool m_isSkinLoaded;

  void create3DPushButton(int index);
  void update3DPushButton();
  void changeAccelerator();

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_MENU_PUSH_BUTTON_
