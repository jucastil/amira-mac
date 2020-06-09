/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Apr 2002)
**=======================================================================*/

#ifndef _SO_WIN_ERROR_CONSOLE_H__
#define _SO_WIN_ERROR_CONSOLE_H__

#include <Inventor/Win/SoWinComponent.h>

class SbThreadMutex;

#ifdef OIV_NET_DOC
/**
* 
*  @VSGEXT Creates a Win32 console for printing messages
*
*  @ingroup mixedMode
* 
* @DESCRIPTION
*  The SoConsole class provides a convenient way to display Open Inventor
*  error messages or other application debug messages in a Win32 console.
*  This can be a very useful feature for simple Win32 applications.
*
*  There is only one error console per application. To get a reference to the 
*  console, call SoWin::getErrorConsole(). It is then possible to print 
*  messages to it using the printMessage function.
*
*  The console replaces the original message box mechanism. Every Open
*  Inventor error is caught and written to the console. This includes
*  user-defined error messages that are generated with SoDebugError. 
*  For example, SoDebugError::post("YourClass", "YourMessage") will print
*  your message to the console.
*
*  Due to a Windows programming limitation, the console is not usable in
*  multi-threaded applications. In this case, it is possible to switch to 
*  the original message box mechanism by setting environment variable 
*  OIV_OLD_ERROR_HANDLER.
*
*  The Save button allows the user to save error information into a file named
*  oivErrorFile.txt.
*  The Clear button deletes all error messages currently displayed in the console.
*
* @SEE_ALSO
*  SoWin, SoDebugError
*
* 
*/ 
#else
/**
* 
*  @VSGEXT Creates a Win32 console for printing messages
*
*  @ingroup mixedMode
* 
* @DESCRIPTION
*  The SoConsole class provides a convenient way to display Open Inventor
*  error messages or other application debug messages in a Win32 console.
*  This can be a very useful feature for simple Win32 applications.
*
*  There is only one error console per application. To get a pointer to the 
*  console, call SoWin::getErrorConsole(). It is then possible to print 
*  messages to it using the printMessage function.
*
*  The console replaces the original message box mechanism. Every Open
*  Inventor error is caught and written to the console. This includes
*  user-defined error messages that are generated with SoDebugError. 
*  For example, SoDebugError::post("YourClass", "YourMessage") will print
*  your message to the console.
*
*  Due to a Windows programming limitation, the console is not usable in
*  multi-threaded applications. In this case, it is possible to switch to 
*  the original message box mechanism by setting environment variable 
*  OIV_OLD_ERROR_HANDLER.
*
*  The Save button allows the user to save error information into a file named
*  oivErrorFile.txt.
*  The Clear button deletes all error messages currently displayed in the console.
*
* @SEE_ALSO
*  SoWin, SoDebugError
*
* 
*/ 
#endif //OIV_NET_DOC

class INVENTORW_API SoConsole : public SoWinComponent 
{

  public :
    /**
     * Constructor.
     */
    SoConsole(SoWidget parent = NULL,
              const char *name = NULL, 
              SbBool buildInsideParent = TRUE);

  /**
   * Destructor.
   */
  virtual ~SoConsole();

  /**
   * Returns a handle to the console.
   */
  HWND getConsoleHandle(void);

  /**
   * Sets the maximum number of messages to be printed in the console.
   */
  static void setMaxNumMessages(int);

  /**
   * Sends a message to the console.
   */
  void printMessage(const SbString& str);

 protected:
  void commonConstructor();
  HWND handleToConsole;
  
  // String to print. All the messages are in it.
  static char *stringBuffer;
  
  static unsigned int maxNumMessages; 
  static unsigned int numMessages ; //current number of messages
  
  // Delete the current message in stringBuffer
  static void clearStringBuffer(void);
  
  // Initial positions for resize event :
  static POINT upLeftCtrlCorner;
  static POINT upLeftClearButtonCorner;
  static POINT upLeftSaveButtonCorner;
  static POINT upLeftCloseButtonCorner;
  static RECT initDlgSize;
  
  // Same as strcpy (I can't use it in here (bug in std lib))
  void copyString(const char *string, char *intoString);
  
  // Add a string to stringBuffer
  char *addString(const SbString& newString);
  
  //If the string comes from Inventor we want to format it a little
  void formatString(SbString& newString);
  
  int countChar(const char *source, char toCount);
  
  char *changeCarriageReturn(const SbString& str, int n);

 private:
  SoWidget buildWidget(SoWidget parent);
  
  // Our window proc so we can filter events :
  static WBOOL CALLBACK dialogWndProc(Hwnd hdlg, UINT message, WPARAM wParam, LPARAM lParam);
  static WBOOL CALLBACK editWndProc(Hwnd hdlg, UINT message, WPARAM wParam, LPARAM lParam);
  
  static void onCommand(Hwnd hdlg, int id, Hwnd hCtrl, UINT codeNotify);
  
  SoWidget mgrWidget;

  SbThreadMutex* m_classMtx;
  SbThreadId_t m_threadId;
};

#endif /* _SO_WIN_ERROR_CONSOLE_H__ */
