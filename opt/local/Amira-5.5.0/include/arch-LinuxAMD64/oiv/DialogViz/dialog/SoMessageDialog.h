/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Jan 2003)
**=======================================================================*/
#ifndef  _SO_MESSAGE_DIALOG_
#define  _SO_MESSAGE_DIALOG_

#include <DialogViz/dialog/SoDialogViz.h>
#include <Inventor/threads/SbThread.h>

/**
 * @VSGEXT Message Dialog node.
 *
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 * 
 * @SEE_ALSO
 *
 */

class DIALOGVIZ_API SoMessageDialog : public SoDialogViz  
{
  SO_DG_HEADER(SoMessageDialog);

 public:

  enum Type {
    /** Display the Error symbol. */
    MD_ERROR,
    /** Display the international information symbol (an "i" with a circle around it). */
    MD_INFORMATION,
    /** Display the default message symbol. */
    MD_MESSAGE,
    /** Display the question symbol (a "?" in a circle). */
    MD_QUESTION,
    /** Display the warning symbol (a "!" is displayed)*/
    MD_WARNING,
    /** Display a working window*/
    MD_WORKING
  };
  /**
   * Control the message dialog box type.
   */
  SoSFEnum type;
  
  /**
   * Constructor
   */
  SoMessageDialog();

  /**
   * Special constructor : build the message dialog box with text, title
   * and type properties, and show it next.
   */
  SoMessageDialog(SbString MDText, SbString MDTitle, Type MDType );

  /**
   * Title of the message dialog box
   */
  SoSFString title;

  /**
   * Show the MessageDialog widget.
   */
  virtual void show();

  /**
   * Close the current working message dialog. Only used with message dialog of type MD_WORKING
   */
  virtual void close();

  /**
   * Destroy the message dialog.
   */
  void destroy();

  /*==============================================================================*/
 SoINTERNAL public:

  void     * m_wnd;
  void     * m_wndLabel;
  SbThread * m_thread;

  static void initClass();
  static void exitClass();
  void createWorkingMessageDialog();

 protected:
    
  virtual  ~SoMessageDialog();

 private:
  static SbVec2i32 getLabelPixelSize(SbString string);
};

#endif // _SO_MESSAGE_DIALOG_
