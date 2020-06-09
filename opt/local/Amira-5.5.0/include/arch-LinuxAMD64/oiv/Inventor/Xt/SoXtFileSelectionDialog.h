/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_XTFILESELECTIONDIALOG_
#define _SO_XTFILESELECTIONDIALOG_

#include <Inventor/SbLinear.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Xt/SoXtDef.h>

#if defined(_WIN32) && !defined(SOQT)
class SoWinFileSelectionDialog;
#define SoXtFileSelectionDialog SoWinFileSelectionDialog
#define SoXtFileSelectionDialogCB SoWinFileSelectionDialogCB
typedef void SoWinFileSelectionDialogCB(void *data, SoWinFileSelectionDialog *dialog);
#elif defined(__APPLE__) || defined(SOQT)
class SoQtFileSelectionDialog;
#define SoXtFileSelectionDialog SoQtFileSelectionDialog
#define SoXtFileSelectionDialogCB SoQtFileSelectionDialogCB
typedef void SoQtFileSelectionDialogCB(void *data, SoQtFileSelectionDialog *dialog);
#else
class SoXtFileSelectionDialog;
#include <Xm/Xm.h>
typedef void SoXtFileSelectionDialogCB(void *data, SoXtFileSelectionDialog *dialog);
#endif

#define charset XmSTRING_DEFAULT_CHARSET

/*****************************************************************************/
//: Class used to realize fileselection boxes to open or save a file
/******************************************************************************/

/**
 * Cross-platform file selection box.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class provides an interactive widget for file selection. Files can be
 *   selected in open file mode or in close file mode.
 * 
 * 
 */ 

class INVENTORXT_API SoXtFileSelectionDialog {
 public:
  /**
   * Constructor.
   */
  SoXtFileSelectionDialog();
  /**
   * Destructor.
   */
  ~SoXtFileSelectionDialog();

  /**
   * Sets the dialog box size (UNIX only).
   */
  void setSize(const SbVec2s &size);

  /**
   * Gets the dialog box size (UNIX only).
   */
  SbVec2s getSize(void);


  /**
   * Sets the file selection dialog box title.
   */
  void                setTitle(char *title);

  /**
   * Gets the file selection dialog box title.
   */
  char                *getTitle(void);


  /**
   * Sets the suffix filter and the filter title.
   */
  void                setFilter(char *suffix, char *title);

  /**
   * Gets the suffix filter and the filter title.
   */
  void                getFilter(char **suffix, char **title);


  /**
   * Sets the file directory.
   */
  void                setFileDirectory(char *directory);
        
  /**
   * Gets the file directory.
   */
  char                *getFileDirectory();

  /**
   * Sets the file name.
   */
  void                setFileName(char *fName);

  /**
   * Gets the file name.
   */
  char                *getFileName(void);

  /**
   * Retrieves the full file path.
   */
  char                *getFilePath(void);

  /** Enum to set the dialog box mode (Open file / Save file). */
  enum Dialog_Mode {
    /**
     *  Open file mode 
     */
    OPEN_FILE,
    /**
     *  Save file mode 
     */
    SAVE_FILE
  };


  /**
   * Sets the mode (Open or Close) of the file selection box.
   */
  void                setMode(Dialog_Mode dMode);
        
  /**
   * Gets the mode (Open or Close) of the file selection box.
   */
  Dialog_Mode     getMode(void);

  /**
   * Shows the file selection box dialog.
   */
  void                show();

  /**
   * Set the callback associated with the OK button.
   */
  void                setAcceptCallback(SoXtFileSelectionDialogCB *f, void *data);

  /**
   * Set the callback associated with the Cancel button.
   */
  void                setAbortCallback(SoXtFileSelectionDialogCB *f, void *data);

        
  private :
    void                buildFilePath(void);
  void                updateFileDirectory(void);
  char                *m_boxTitle;
  char                *m_filterSuffix;
  char                *m_filterTitle;
  char                *m_fileDirectory;
  char                *m_fileName;
  char                m_fullFilePath[1000];
  Dialog_Mode     m_dlgMode;
  SoXtFileSelectionDialogCB   *acceptPtr;
  SoXtFileSelectionDialogCB   *abortPtr;
  void                *acceptDataPtr;
  void                *abortDataPtr;
  void            setFilePath(char *fPath);

  SbVec2s         m_dlgSize;
#if !defined(_WIN32) && !defined(SOQT)
  SbBool          m_boxExist;
  SbVec2s         m_defaultSize;
  SoWidget          m_toplevel;
  SoWidget          m_fileSelectionDialog;
  SoWidget          m_SoXtFileSelectionDialog;
  static void     OK_Button (SoWidget fs, XtPointer client_data, XmFileSelectionBoxCallbackStruct *cbs);
  static void     Cancel_Button (SoWidget fs, XtPointer client_data, XmFileSelectionBoxCallbackStruct *cbs);
  // if m_keepDialog is set to TRUE, the dialog box will not be deleted 
  // after buttons are pressed.
  SbBool                      m_keepDialog;
 public:
  void keepDialog(SbBool);

#endif

};

#endif // _SO_XTFILESELECTIONDIALOG_



