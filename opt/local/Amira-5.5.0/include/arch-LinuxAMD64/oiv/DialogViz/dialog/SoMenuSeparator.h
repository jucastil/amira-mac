/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_SEPARATOR_
#define  _SO_MENU_SEPARATOR_

#include <DialogViz/dialog/SoMenuItem.h>

/**
 * @VSGEXT Menu separator node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines an horizontal separator in a menu bar component.
 *
 *   You can change the parts in any instance of this menu separator using setPart().
 *   The default part geometries are defined as resources for this SoMenuSeparator class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/MenuSeparator.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   MenuSeparator {
 *   @TABLE_FILE_FORMAT
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD LEFT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE somenuseparator.cat.html
 *
 * @SEE_ALSO
 *   SoMenuCheckBox,
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPopup,
 *   SoMenuPushButton,
 *   SoMenuPushButtonLauncher,
 *   SoMenuFileSelection,
 *   SoMenuRadioButtons
 *
 */

class DIALOGVIZ_API SoMenuSeparator : public SoMenuItem  
{
  SO_DG_HEADER(SoMenuSeparator);

 public:

  /**
   * Constructor
   */
  SoMenuSeparator();


  /*==============================================================================*/
 SoINTERNAL public:
  virtual void buildMenu(void *parent, SbBool isActive2d, int index = -1);
  static  void initClass();
  static  void exitClass();
  virtual void updateFromSensor(SoSensor* ) {};
  virtual void destroyNoDeleteMenuItem();

 protected:
  virtual ~SoMenuSeparator();

 private:
  void* m_separatorMenuWin;
  void insertMenuItem(int index);
  void updateMenuItem();

  virtual SbVec2i32 getItemInitSize();
  virtual void setItemSize(SbVec2i32 nSize, SbBool force = FALSE);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* MenuSeparator; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

protected:

  SO_DG_CATALOG_ENTRY_HEADER( sepSep   );
  SO_DG_CATALOG_ENTRY_HEADER( sepFrame );

  SoScale* menuSeparatorFrameScale;

private:
  static SbBool m_isSkinLoaded;

  void create3DSeparator(int index);
  void update3DSeparator();

///////////////////////////////////////////////////////////////////////////////////////


};

#endif // _SO_MENU_SEPARATOR_
