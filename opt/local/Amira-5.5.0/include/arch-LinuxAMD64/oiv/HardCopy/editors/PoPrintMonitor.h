/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef PO_PRINT_MONITOR_H
#define PO_PRINT_MONITOR_H

#include <SoVersion.h>

#ifdef _WIN32
#  if defined(_DEBUG)
#    define __HARDCOPYWDLL "HardCopyWinD.dll"
#    define __HARDCOPYWLIB "HardCopyWinD.lib"
#  else
#    define __HARDCOPYWDLL "HardCopyWin.dll"
#    define __HARDCOPYWLIB "HardCopyWin.lib"
#  endif
#ifndef HardCopyWin_EXPORTS
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__HARDCOPYWLIB)
#endif
#endif
#else
#    define __HARDCOPYWDLL "libHardCopyXt"
#endif

#include <Inventor/SbLinear.h>
#include <Inventor/Xt/SoXtComponent.h>

#include <HardCopy/SoVectorizeAction.h>
#include <Inventor/dialog/PoXtDialog.h>
class SoNode;
class SoPath;
class dialogRgbHsvControl;

#include <Inventor/SoModule.h>
#if defined(_WIN32)
SO_MODULE_HEADER(SoHardCopyWin, __HARDCOPYWDLL)
#else
SO_MODULE_HEADER(SoHardCopyXt, __HARDCOPYWDLL)
#endif

struct menuColumn;

/**
 * @HCEXT  Abstract base class for print dialog box.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *    Class to build a dialog box which contains all elements to configure a 
 *    printing. This abstract class uses SoVectorizeAction class parameters. 
 * 
 */
class HARDCOPYW_API PoPrintMonitor : public SoXtComponent {

 public:

  typedef void PoPrintMonitorCB(void *userData, PoPrintMonitor *action);

  enum PrintDialogMask {
    NO_PRINT_MASK      = 0x00000000,

    UNIT               = 0x00000001,

    GEOMETRY_WIDTH     = 0x00000002,
    GEOMETRY_HEIGHT    = 0x00000004,
    GEOMETRY_POS_X     = 0x00000008,
    GEOMETRY_POS_Y     = 0x00000010,
    /**
     *  Family mask.
     *  GEOMETRY is a family mask thus:
     *  GEOMETRY = GEOMETRY_WITH | ... | GEOMETRY_POS_Y
     */
    GEOMETRY           = GEOMETRY_WIDTH | GEOMETRY_HEIGHT | GEOMETRY_POS_X |  GEOMETRY_POS_Y, 

    ORIENTATION        = 0x00000020,

    BORDER_WIDTH       = 0x00000040,
    BORDER_COLOR       = 0x00000080,
    /**
     *  Family mask.
     */
    BORDER             = BORDER_WIDTH | BORDER_COLOR, 

    BACKGROUND_SET     = 0x00000100,
    BACKGROUND_COLOR   = 0x00000200,
    /**
     *  Family mask.
     */
    BACKGROUND         = BACKGROUND_SET | BACKGROUND_COLOR,  

    NOMINAL_WIDTH      = 0x00000400,
    TRANSLATION_METHOD = 0x00000800,
    LINE_END_STYLE     = 0x00001000,
    LINE_JOIN_STYLE    = 0x00002000,
    MITER_LIMIT        = 0x00004000,
    /**
     *  Family mask.
     */
    PRINT_REGULATION   = NOMINAL_WIDTH | TRANSLATION_METHOD
    | LINE_END_STYLE | LINE_JOIN_STYLE 
    | MITER_LIMIT, 
    
    PEN_DESCRIPTION    = 0x00008000,
 
    COLOR_PRIORITY     = 0x00010000,

    /**
     *  Family mask.
     */
    ALL_PRINT_MASK     = UNIT | GEOMETRY | ORIENTATION 
    | BORDER | BACKGROUND 
    | PRINT_REGULATION | PEN_DESCRIPTION 
    | COLOR_PRIORITY 
  };

  enum Presentation {
    TOGGLE_FOLD,
    TOGGLE_UNFOLD,
    LABEL_UNFOLD 
  };

 public:

  /**
   * Sets the presentation of the editor. (TOGGLE_FOLD by default).
   */
  virtual void setPresentation (Presentation type);

  /**
   * Gets the presentation of the editor. (TOGGLE_FOLD by default).
   */
  Presentation getPresentation () const;

  /**
   * Gets editing filters defining which print attributes will be displayed in the 
   * dialog box. (By default inclusionMask = ALL_PRINT_MASK and 
   * exclusionMask = NO_PRINT_MASK).
   */
  void setPrintFilter(unsigned long inclusionMask,
                      unsigned long exclusionMask);
  /**
   * Gets editing filters defining which print attributes will be displayed in the 
   * dialog box. (By default inclusionMask = ALL_PRINT_MASK and 
   * exclusionMask = NO_PRINT_MASK).
   */
  void getPrintFilter(unsigned long &inclusionMask,
                      unsigned long &exclusionMask) const;

  /**
   * Sets apply function to a node. (cf apply method of SoVectorizeAction).
   */
  void setApply(SoNode *node);

  /**
   * Sets apply function to a path. (cf apply method of SoVectorizeAction).
   */
  void setApply(SoPath *path);

  /**
   * Sets apply function to a pathList. (cf apply method of SoVectorizeAction).
   */
  void setApply(const SoPathList &pathList, SbBool obeysRules = FALSE);

  /**
   * Sets the file name for the output.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setFileName(char *fileName);

  /**
   * Sets the file name for the output.
   */
  void setFileName( const SbString& fileName );

  /**
   * Replaces the old action with a new action and updates the dialog box. Be 
   * careful, if the application destroys the action, the dialog box will not work. If 
   * the application specifies isDestroyed TRUE, the dialog box will destroy the 
   * action, otherwise the application has to destroy the action after the dialog box 
   * is destroyed. 
   */
  void setAction(SoVectorizeAction *action, SbBool isDestroyed);

  virtual void show();
  virtual void hide();

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  SoVectorizeAction * _vectorizeAction;
  SoVectorizeAction::DimensionUnit _unit;
  dialogRgbHsvControl * _dialogPenDescription;
  dialogRgbHsvControl * _colorEditorBorder;
  dialogRgbHsvControl * _colorEditorBackground;
  void updateXtElements();

 protected:
  PoPrintMonitor(SoWidget Parent, const SbString& name, SbBool buildInsideParent);
  virtual ~PoPrintMonitor(); 

  virtual void buildWidget(SoWidget Parent, 
                           const SbString& name, 
                           SbBool buildInsideParent);

  // specify the method for destroy action
  virtual void destroyAction() = 0;
  virtual int getMenuItems();
  virtual void setFilter();
  // do apply on vectorizeAction, return True if OK, otherwise False
  SbBool applyAction();

  void addAcceptCallback (PoPrintMonitorCB *func, void *userData = NULL);
  void removeAcceptCallback (PoPrintMonitorCB *func, void *userData = NULL);

  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  PoXtDialog *_dialog;

  Presentation    _presentation;

  menuColumn *_menu;
  int _menuItems;

  SbString _defaultFileName;

  SoNode *_node;
  SoPath *_path;
  SoPathList *_pathList;
  SbBool _obeysRules;
  SbBool _destroyAction;

  SbString _fileName;

 private:
  SoCallbackList *_acceptCallbackList;
  int _classMenusNb;
  unsigned long _incPrintMask;
  unsigned long _excPrintMask;

  SbBool _isPrintSet;

  static void acceptCallback(PoPrintMonitor *printMonitor, 
                             PoXtDialog::PoXtDialogDataCB *data);
  static void fileNameCallback(PoPrintMonitor *printMonitor, 
                               PoXtDialog::PoXtDialogDataCB *data);
};

#endif //PO_PRINT_PS_MONITOR_H

