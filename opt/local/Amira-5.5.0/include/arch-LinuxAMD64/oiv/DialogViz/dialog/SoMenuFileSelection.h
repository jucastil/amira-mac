/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_FILE_SELECTION_
#define  _SO_MENU_FILE_SELECTION_

#include <DialogViz/dialog/SoMenuPushButton.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFInt32.h>

class SoMenuFileSelectionAuditor;

/** 
 * @VSGEXT Menu file selection button node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a push button item for a dialog menu.
 *   The push button launches a file selection dialog box for
 *   saving or opening a file.
 *
 *   On Windows systems, the system file selection dialog is launched.
 *
 *   On UNIX, the file selection dialog has been entirely constructed. 
 *   using Motif components. UNIX filename completion
 *   is available in the filename and directory edit fields.
 *
 * @FILE_FORMAT_DEFAULT
 *   MenuFileSelection {
 *   @TABLE_FILE_FORMAT
 *       @TR title            @TD ""
 *       @TR filter           @TD ["*.iv", "Inventor file"]
 *       @TR defaultFilter    @TD 0
 *       @TR fileDirectory    @TD "."
 *       @TR filename         @TD ""
 *       @TR mode             @TD OPEN
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD LEFT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @SEE_ALSO
 *   SoMenuCheckBox,
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPopup,
 *   SoMenuPushButton,
 *   SoMenuPushButtonLauncher,
 *   SoMenuRadioButtons,
 *   SoMenuSeparator
 *
 */

class DIALOGVIZ_API SoMenuFileSelection : public SoMenuPushButton
{
  SO_DG_HEADER(SoMenuFileSelection);

 public:

  /**
   * Title of the file selection dialog box.
   */
  SoSFString title;

  /** 
   * List of filters. Default list is empty.
   * Each filter consists of two strings. The first is the file extension, 
   * and the second is the user description.
   * For example: 
   * 
   * filter ["*.jpg; *.bmp", "Images Files", "M*e", "Special filter"] 
   * 
   * The displayed filter in your selection dialog is the concatenation of the filter and its description.
   * Thus, for the previous example, the strings that appear are:
   * 
   * "Images Files (*.jpg;*.bmp)" and "Special filter (M*e)".
   */
  SoMFString filter;

  /**
   * Default filter to use when loading file selection box. Default is 0.
   */
  SoSFInt32 defaultFilter;

  /**
   * Initial directory and selected directory. Default is current directory.
   */
  SoSFFilePathString fileDirectory;

  /**
   * Initial filename and selected filename. Default is empty string.
   */
  SoSFFilePathString filename;

  enum Mode {
    /** File opening mode (Default). */
    OPEN = 0x01,
    /** File saving mode. */
    SAVE = 0x02
  };

  /**
   * The file selection dialog box is configured for opening or saving a file
   * according to the value of this field. Default value is OPEN.
   */
  SoSFEnum mode;

  /**
   * Initial filename and selected filename. Default is empty string.
   */
  SoMenuFileSelection();

  /**
   * Adds a menuFileSelectionAuditor to current PushButton component.
   */
  void addAuditor(SoMenuFileSelectionAuditor* auditor);

  /**
   * Removes the defined fileSelectionAuditor from the auditor list.
   */
  void removeAuditor(SoMenuFileSelectionAuditor* auditor);

/*==============================================================================*/
SoINTERNAL public:
  static  void initClass();
  static  void exitClass();
  virtual void menuEvent(void* parent, int itemId);
          void validateFilename();
          void setIsOpened(SbBool iso) { m_isOpenedWindow = iso; };
  void applyDlgCptAuditor();

protected:
  virtual       ~SoMenuFileSelection();

  void openDialogBox();

  SbString m_dirPath; // saved current directory

private:
	SbBool m_isOpenedWindow;

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:

protected:
    virtual void add3DCallbackMethods();

private:
  static void finishCB3D( void *, SoDragger *inDragger );
  virtual void draggerFinishCallback3D();

///////////////////////////////////////////////////////////////////////////////////////
};

#endif // _SO_MENU_FILE_SELECTION_
