/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_ITEM_
#define  _SO_MENU_ITEM_

#include <DialogViz/dialog/SoDialogViz.h>

class SoMenuBar;

/** 
 * @VSGEXT Abstract class for all menu item nodes.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   SoMenuItem is the abstract class for all menu item nodes. Menu item
 *   nodes are added in an SoMenuPopup.
 *
 *   For all of the derived classes, it is possible to define a mnemonic character and
 *   an accelerator key combination. (Note: SoMenuPopup cannot have an accelerator key
 *   combination). The mnemonic character, if any, is underlined in the label string. 
 *   The purpose of menu accelerators is to
 *   allow the user to activate a menu item without opening any menus. Instead, the user can 
 *   do it by using
 *   keyboard shortcuts. These key sequences are aligned on the right of the menu items.
 *
 *   To define a mnemonic and an accelerator, simply define the #label field as
 *   follows:
 *     - Use the "&" character before the character you want to use as a mnemonic. For
 *       example, for a menu label defined by "Open &File", the "F" character will be underlined.
 * 
 *     - To register an accelerator, you must end your label with a block that
 *       begins with "\\t". For example, "Open\\tCtrl+O" registers the Ctrl+O key
 *       combination. Any time you press the @I Ctrl-O @i keyboard sequence, the action
 *       associated with this menu item is done. Available control keys are @B Alt@b, 
 *       @B Ctrl@b, and @B Shift@b (and @B Meta@b on UNIX platforms). The key to press 
 *       (e.g., @I O@i) must be at the end of the sequence.
 * 
 *       The following examples show how accelerators must be formatted:
 * <PRE>       *  "&Open\\tCtrl+O"      
 *       *  "&Save\\tCtrl+S"
 *       *  "&Save As...\\tCtrl+Alt+S"
 *       *  "New\\tF12"
 *       *  ...
 * </PRE>
 * @SEE_ALSO
 *   SoMenuBar,
 *   SoMenuCheckBox,
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPopup,
 *   SoMenuPushButton,
 *   SoMenuPushButtonLauncher,
 *   SoMenuFileSelection,
 *   SoMenuRadioButtons,
 *   SoMenuSeparator
 *
 */

class DIALOGVIZ_API SoMenuItem : public SoDialogViz  
{

  SO_DG_HEADER(SoMenuItem);

/*==============================================================================*/
SoINTERNAL public:
  SoMenuItem();

  virtual void buildMenu(void* parent, SbBool isActive2d, int index = -1);
  static  void initClass();
  static  void exitClass();
  virtual void menuEvent(void* , int ) {};
  virtual void updateFromSensor(SoSensor* sensor);
          SoMenuBar* getMenuBar();
          int  getId();
  virtual void destroyNoDeleteMenuItem() {};
  virtual SbVec2i32 getItemInitSize();
  virtual void setItemSize(SbVec2i32 nSize, SbBool force = FALSE);
  SbVec2i32 getItemSize();

protected:
  int  m_id;
  static  int  ID;  // windows only
  void* m_parentMenu;
  SbVec2i32 m_itemSize;

  static char buildTitleForMotifMenu( const SbString& inString, SbString& outString);
  static SbString getAccelerator( const SbString& inString );
  static SbString getKeyCombination( const SbString& inString, SoMenuItem* mi, unsigned int id = 0);

  virtual     ~SoMenuItem();


///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* MenuItem; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:
  SO_DG_CATALOG_ENTRY_HEADER( itemFrameSep );
  SO_DG_CATALOG_ENTRY_HEADER( frame        );
  SO_DG_CATALOG_ENTRY_HEADER( labelSep     );
  SO_DG_CATALOG_ENTRY_HEADER( labelProp    );

  SoScale* menuItemFrameScale;
  SoText3* menuItemLabel;
  SoTranslation* menuItemFrameTranslation, *menuItemLabelTranslation;
  SoTransform* menuItemFrameTransform;

  virtual void change3DLabel();
  void get3DLabelCachedBBox(SbVec3f& min, SbVec3f& max);

private:
  static SbBool m_isSkinLoaded;

  void create3DItem(int index);
  void update3DItem();
  
SoEXTENDER public:
  virtual void getBoundingBox(SoGetBoundingBoxAction* action);

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_MENU_ITEM_
