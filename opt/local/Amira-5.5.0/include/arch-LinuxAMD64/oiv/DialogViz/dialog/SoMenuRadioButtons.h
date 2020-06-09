/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_RADIO_BUTTONS_
#define  _SO_MENU_RADIO_BUTTONS_

#include <DialogViz/dialog/SoMenuItem.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFInt32.h>

class SoMenuRadioButtonsAuditor;

/**
 * @VSGEXT Dialog RadioButtons node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines radio buttons in a menu bar component.
 *
 *   You can change the parts in any instance of this menu radio buttons components using setPart().
 *   The default part geometries are defined as resources for this SoMenuRadioButtons class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/MenuRadioButtons.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   MenuRadioButtons {
 *   @TABLE_FILE_FORMAT
 *       @TR items            @TD []
 *       @TR selectedItem     @TD 0
 *       @TR accelerators     @TD ""
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD LEFT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE somenuradiobuttons.cat.html
 *
 * @SEE_ALSO
 *   SoMenuCheckBox,
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPopup,
 *   SoMenuPushButton,
 *   SoMenuPushButtonLauncher,
 *   SoMenuFileSelection,
 *   SoMenuSeparator
 *
 */

class DIALOGVIZ_API SoMenuRadioButtons : public SoMenuItem  
{
  SO_DG_HEADER(SoMenuRadioButtons);

 public:

  /**
   * List of string appearing in the component. Default list is empty.
   */
  SoMFString  items;

  /**
   * Selected choice. Default is zero.
   */
  SoSFInt32   selectedItem;

  /**
   * Defines the accelerator keys for each items.
   */
  SoMFString accelerators;

  /**
   * Constructor
   */
  SoMenuRadioButtons();

  /**
   * Add a menuRadioButtonsAuditor to current RadioButtons component.
   */
  void addAuditor(SoMenuRadioButtonsAuditor* auditor);

  /**
   * Remove the defined radioButtonsAuditor from the auditor list.
   */
  void removeAuditor(SoMenuRadioButtonsAuditor* auditor);

  /*==============================================================================*/
 SoINTERNAL public:
  virtual void   buildMenu(void* parent, SbBool isActive2d, int index = -1);
  static  void   initClass();
  static  void   exitClass();
  void   menuEvent(void* parent, int itemId);
  virtual void   updateFromSensor(SoSensor* sensor);
  virtual void destroyNoDeleteMenuItem();
  void applyDlgCptAuditor();

 protected:
    
  virtual ~SoMenuRadioButtons();

 private:
  
  int m_numItems;
  int m_oldNumItems;
  int m_index;
  
  FIELD_SENSOR(selectedItem);
  FIELD_SENSOR(items);
  FIELD_SENSOR(accelerators);

  virtual SbVec2i32 getItemInitSize();
  virtual void setItemSize(SbVec2i32 nSize, SbBool force = FALSE);

  virtual void changeLabel();
  virtual void changeEnable();
  void changeSelectedItem();
  void changeItems();
  void changeAccelerators();

  void** m_radioButtonsMenuWin;
  void insertMenuItem(int index);
  void updateMenuItem();
  void verifySelectedItem();

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* MenuRadioButtons; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:
  SO_DG_CATALOG_ENTRY_HEADER( radioSep  );
  SO_DG_CATALOG_ENTRY_HEADER( itemsSep  );
  SO_DG_CATALOG_ENTRY_HEADER( itemSwtch );
  SO_DG_CATALOG_ENTRY_HEADER( stateOff  );
  SO_DG_CATALOG_ENTRY_HEADER( stateOn   );

  SoTranslation* menuRadioButtonsShapeTranslation;
  SoScale* menuRadioButtonsShapeScale;

private:
  SoNodeList m_item3DList;
  SoNodeList m_item3DSwitchList;
  SoNodeList m_item3DTextList;
  SoNodeList m_item3DLabelTranslList;
  static SbBool m_isSkinLoaded;

  void create3DRadioButtons(int index);
  void update3DRadioButtons();
  void add3DItem(int index);

  void change3DItems();
  void change3DSelectedItem();

  static void finishCB3D( void *, SoDragger *inDragger );
  virtual void draggerFinishCallback3D();

///////////////////////////////////////////////////////////////////////////////////////
  
};

#endif // _SO_MENU_RADIO_BUTTONS_
