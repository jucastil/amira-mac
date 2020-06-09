/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_WIN_CLIPBOARD_
#define  _SO_WIN_CLIPBOARD_

#include <Inventor/sys/port.h>

#include <Inventor/Win/SoWin.h>

#include <Inventor/Win/SoWinBeginStrict.h>


class SbDict;
class SoByteStream;
class SoNode;
class SoPath;
class SoPathList;
class SoSelection;


// callback function prototypes
/** 
 * [OIV-WRAPPER NAME{ClipboardPasteCB}] 
 */
typedef void SoWinClipboardPasteCB(void *userData, SoPathList *pathList);


// The CLIPBOARD selection atom is not a predefined atom in X11 R4.
// However, it is widely recognized. We define it to 0 here for
// convenience. Internally, when SoWinClipboard sees _XA_CLIPBOARD_,
// it will use XInternAtom(d, "CLIPBOARD", False).

#define _XA_CLIPBOARD_ ((Atom) 0)

#define XA_STRING ((Atom) 1)


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinClipboard
//
//      
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Supports copy/paste for Open Inventor using the Windows clipboard.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   This class manages data transfers for copy and paste to and from the Windows
 *   clipboard. Transfers may occur within the same window, from one window to
 *   another window, and from process to process.
 *   
 *   Clipboard support is currently strictly text. The copy type @B cbFormat @b will
 *   be forced to CF_TEXT, no matter what, if anything, is specified in the second
 *   argument of the constructor.
 * 
 * @SEE_ALSO
 *    SoSelection,
 *    SoWin
 * 
 * 
 */ 

class INVENTORW_API SoWinClipboard {
 public:
  // Constructor.
  // The selection atom determines which X selection atom data transfers
  // should happen through. Default is _XA_CLIPBOARD_. (wsh uses XA_PRIMARY).
    
  /**
   * Constructor. @B w @b is the window that will be used for the
   * clipboard operations. @B cbFormat @b specifies the Windows clipboard format to
   * be used for the data transfer.
   * [OIV-WRAPPER-ARG IN,NO_WRAP]
   */
  SoWinClipboard(SoWidget w, Atom selectionAtom = _XA_CLIPBOARD_);
    
  /**
   * Destructor.
   */
  ~SoWinClipboard();

  //
  // These methods transfer inventor scene graphs as the data.
  //
  // Data types supported for export (so another process can paste):
  //      INVENTOR, XA_STRING
  // (and someday: POSTSCRIPT, IMAGE)
  //
  // Data types supported for import (so this process can paste):
  //      INVENTOR, XA_STRING (pasted as an SoText2 node)
  //

  // Copy - these routines copy the passed data into a byte stream,
  // and make the data available to any X client which requests it.
  // The eventTime should be the time stamp from the event which
  // triggered the copy request.
    
  /**
   * Copies the passed scene graph object (node, path, or pathlist) to the 
   * clipboard using the current
   * clipboard format. The @B eventTime @b should be the time returned by the system
   * routine @B time @b(), and can be used to insure synchronization of copy and
   * paste requests.
   * 
   * For example,
   * 
   * @code
   *  #include <windows.h>
   *  #include <time.h>
   *  #include <...>
   *  ... (necessary Inventor includes)
   *  void SomeFunc(some_args)
   *  {
   *  HWND hwnd;
   *  // (window value gets set in normal Windows usage
   *  // or is passed in as an argument)
   *  ...
   *  SoNode *the_node
   *  // a node to copy to the clipboard
   *  // (will be incorporated in a pathlist)
   *  ...
   *  SoWinClipboard the_clipboard(hwnd);
   *  // CF_TEXT is forced as the clipboard format
   *  ...
   *  the_clipboard.copy(the_node, time(NULL));
   *  // copy the node to the clipboard
   *  ...
   *  }
   *  @endcode
   *  
   */
  void    copy(SoNode *node, Time eventTime);
    
  /**
   * Copies the passed path to the clipboard using the current
   * clipboard format. See copy() for details.
   */
  void    copy(SoPath *path, Time eventTime);

  /**
   * Copies the passed pathlist to the clipboard using the current
   * clipboard format. See copy() for details.
   */
  void    copy(SoPathList *pathList, Time eventTime);

  // Paste - make a request to the X server so we can import data for paste.
  // A paste is asynchronous - when this routine is called, it simply
  // makes a request to the X server for data to paste, then returns.
  // Once the data is delivered, the pasteDoneFunc will be called and passed
  // the user data along with a list of paths that were pasted. The app
  // should delete this path list when it is done with it.
  // The eventTime should be the time stamp from the event which
  // triggered the paste request.
    
  /**
   * This requests data from the clipboard in the current clipboard format. When the
   * data is retrieved, the @B pasteDoneFunc @b callback is invoked. The newly
   * pasted data is passed as the callback function's @B pathList @b argument (an
   * SoPathList).
   * [OIV-WRAPPER SINGLE_CALLBACK{True}]
   */
  void    paste(Time eventTime,
                SoWinClipboardPasteCB *pasteDoneFunc,
                void *userData = NULL);

	SoINTERNAL public:
	static void exitClass();
    
 protected:
  SoWidget      widget;         // the widget to associated data with
  Atom        selAtom;        // which selection: XA_PRIMARY, XA_SECONDARY, etc.
  Time        eventTime;      // time of the event which caused the copy/paste
    
  // Paste callback info
  SoWinClipboardPasteCB    *callbackFunc;
  void                    *userData;
    
  // Atoms supported for copy and paste targets:
  static Atom     TARGETSatom;  // XInternAtom(d, "TARGETS", False);
  static Atom INVENTORatom; // XInternAtom(d, "INVENTOR", False);
  //          XA_STRING

  static Atom *supportedTargets;
    
  // There can only be one owner of each X selection at any one time.
  // We use the selection atom as the key, and 'this' as the data.
  // We set the owner for each selection in this list for exportSelection.
  static SbDict   *selOwnerList;
    
  // Return the clipboard data in binary or ascii form.
  SoByteStream    *getBinaryBuffer();
  SoByteStream    *getAsciiBuffer();
    
  // All the overloaded copy functions call this one.
  void            copy(SoByteStream *byteStream, Time t);

 private:
  SoByteStream    *binaryBuffer;      // copy/paste storage buffer
  SoByteStream    *asciiBuffer;       // ascii version of storage buffer
    
  // Copy and paste callback functions - these are called by the X server.
  // importSelection is called when we import data to paste.
  // exportSelection is called when we send data for someone else to paste.
  // loseSelection is called when we no longer own the selection.
  static void         importSelection(
                                      SoWidget              w,
                                      SoWinClipboard      *clipboard,
                                      Atom                *selAtom,
                                      Atom                *type,
                                      char                *value,
                                      size_t      *length,
                                      int                 *format);

  static Boolean      exportSelection(
                                      SoWidget              w,
                                      Atom                *xselection,
                                      Atom                *target,
                                      Atom                *type,
                                      char                **value,
                                      size_t      *length,
                                      int                 *format);

  static void         loseSelection(
                                    SoWidget              w,
                                    Atom                *xselection);
                            
  static void         importSelectionTargets(
                                             SoWidget              w,
                                             SoWinClipboard      *clipboard,
                                             Atom                *selAtom,
                                             Atom                *type,
                                             char                *value,
                                             unsigned long       *length,
                                             int                 *format);

};

#include <Inventor/Win/SoWinEndStrict.h>

#endif /* _SO_WIN_CLIPBOARD_ */

