/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef _WIN32
#  include <Inventor/Win/SoWinClipboard.h>
#else // _WIN32

#ifndef  _SO_XT_CLIPBOARD_
#define  _SO_XT_CLIPBOARD_

#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Xt/SoXtDef.h>

class SbDict;
class SoByteStream;
class SoNode;
class SoPath;
class SoPathList;
class SoSelection;
class SoXtImportInterestList;
class SbString;
class SbPList;


// callback function prototypes
typedef void SoXtClipboardPasteCB(void *userData, SoPathList *pathList);
typedef void SoXtClipboardImportCB(
                                   void *userData,
                                   Atom dataType,
                                   void *data,
                                   uint32_t numBytes);


// The CLIPBOARD selection atom is not a predefined atom in X11 R4.
// However, it is widely recognized. We define it to 0 here for
// convenience. Internally, when SoXtClipboard sees _XA_CLIPBOARD_,
// it will use XInternAtom(d, "CLIPBOARD", False).

#define _XA_CLIPBOARD_ ((Atom) 0)

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtClipboard
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Supports copy/paste for Open Inventor using the Xt clipboard.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class manages data transfers for copy and paste. Transfers may occur within
 *   the same process, or between different processes. This uses the Xt selection
 *   mechanism to implement the ICCCM protocol for the transfer of data. 
 * 
 * @SEE_ALSO
 *    SoSelection,
 *    SoXt
 * 
 * 
 */ 

class INVENTORXT_API SoXtClipboard {
 public:
  // Constructor.
  // The selection atom determines which X selection atom data transfers
  // should happen through. Default is _XA_CLIPBOARD_. (wsh uses XA_PRIMARY).

  /**
   * Constructor. @B w @b is the Xt widget that will be used for the
   * clipboard operations. @B selectionAtom @b is the X selection through which data should
   * be transferred. For quick data transfers, this should be XA_PRIMARY. The default
   * is _XA_CLIPBOARD_ which uses the X clipboard selection. 
   */
  SoXtClipboard(SoWidget w, Atom selectionAtom = _XA_CLIPBOARD_);

  /**
   * Destructor. 
   */
  ~SoXtClipboard();

  //
  // These methods transfer inventor scene graphs as the data.
  //

  // Copy - these routines copy the passed data into a byte stream,
  // and make the data available to any X client which requests it.
  // The eventTime should be the time stamp from the event which
  // triggered the copy request.
  //
  // The standard Inventor targets will be exported:
  //      INVENTOR_2_1
  //      INVENTOR_2_1_FILE
  //      VRML_1_0
  //      VRML_1_0_FILE
  //      INVENTOR
  //      INVENTOR_FILE
  //      INVENTOR_2_0
  //      INVENTOR_2_0_FILE

  /**
   * This copies the passed scene graph object, and tells the X server that the
   * clipboard now owns the selection which was specified by selectionAtom in the
   * constructor. When a paste happens (in this window, another window, or another
   * process), the X server will ask this clipboard for the data it copied here. The
   * eventTime should be the time found in the X event structure which triggered the
   * copy operation, and is used to ensure synchronization of copy and paste
   * requests. Data targets supported for export are INVENTOR_2_1, INVENTOR_2_1_FILE,
   * INVENTOR_2_0, INVENTOR_2_0_FILE, VRML_1_0, VRML_1_0_FILE. Also exported for
   * backwards compatibility are INVENTOR and INVENTOR_FILE, which are equivalent to
   * INVENTOR_2_0 and INVENTOR_2_0_FILE. 
   */
  void    copy(SoNode *node, Time eventTime);

  /**
   * This copies the passed scene graph object, and tells the X server that the
   * clipboard now owns the selection which was specified by selectionAtom in the
   * constructor. See copy(SoNode *node, Time eventTime) for additional details.
   */
  void    copy(SoPath *path, Time eventTime);

  /**
   * This copies the passed scene graph object, and tells the X server that the
   * clipboard now owns the selection which was specified by selectionAtom in the
   * constructor. See copy(SoNode *node, Time eventTime) for additional details. 
   */
  void    copy(SoPathList *pathList, Time eventTime);

  // This copies non-Inventor data to the clipboard
  void    copy(Atom dataType, void *data, uint32_t numBytes, Time eventTime);

  // Paste - make a request to the X server so we can import data for paste.
  // A paste is asynchronous - when this routine is called, it simply
  // makes a request to the X server for data to paste, then returns.
  // Once the data is delivered, the pasteDoneFunc will be called and passed
  // the user data along with a list of paths that were pasted. The app
  // should delete this path list when it is done with it.
  // The eventTime should be the time stamp from the event which
  // triggered the paste request.
  //
  // The standard Inventor targets will be recognized:
  //      INVENTOR_2_1
  //      INVENTOR_2_1_FILE
  //      VRML_1_0
  //      VRML_1_0_FILE
  //      INVENTOR
  //      INVENTOR_FILE
  //      INVENTOR_2_0
  //      INVENTOR_2_0_FILE
  //      XA_STRING - if the string describes ascii Inventor data

  /**
   * This makes a request to the X server for data to paste from the selection atom
   * specified in the constructor (selectionAtom), then returns. When the data is
   * retrieved from the selection owner, the pasteDoneFunc callback is invoked. The
   * newly pasted data is passed as the callback function's pathList argument (an
   * SoPathList). Data targets supported for import are INVENTOR_2_1,
   * INVENTOR_2_1_FILE, INVENTOR_2_0, INVENTOR_2_0_FILE, VRML_1_0, VRML_1_0_FILE.
   * Also imported for backwards compatibility are INVENTOR and INVENTOR_FILE, which
   * are equivalent to INVENTOR_2_0 and INVENTOR_2_0_FILE.
   */
  void    paste(Time eventTime,
                SoXtClipboardPasteCB *pasteDoneFunc,
                void *userData = NULL);

  // This extends the paste interest to recognize an additional target as
  // specified by 'dataType'. The pasteImportFunc will be called when this
  // type of data is pasted. This may be called multiple times to register
  // interest in more than one extension.
  //
  // Passing NULL as the pasteImportFunc will remove paste interest for that
  // data type (even if the data type is one of the defaults).
  //
  // This should be called before paste() so that paste() will look for data
  // types that have been specified here.
  //
  // The dataType atom can be created with XmInternAtom, e.g.:
  //     XmInternAtom(XtDisplay(widget),"INVENTOR",False);
  //
  // The order is important - first things added to the list are the first
  // things searched for at paste time. (The default interest types come first.)

  /**
   * This extends the paste interest to recognize an additional target as specified
   * by dataType. It can be called multiple times to register interest in more than
   * one extension. The pasteImportFunc will be called when data of the registered
   * type is pasted. Passing NULL as the pasteImportFunc will remove paste interest
   * for that data type (even if the data type is one of the defaults). This should
   * be called before paste() so that paste() will accept pastes of data types that
   * have been registered here. 
   * 
   * A dataType atom can be created with XmInternAtom, e.g.:
   * 
   * <PRE>
   *  XmInternAtom(XtDisplay(widget),"INVENTOR",False);
   *  </PRE>
   *  
   */
  void            addPasteInterest(
                                   Atom dataType,
                                   SoXtClipboardImportCB *pasteImportFunc,
                                   void *userData = NULL);

 SoEXTENDER public:

  // Convert the passed Inventor 2.1 data to a different format, specified by
  // the Atom desiredType. The data will be malloc'd here and placed in returnData,
  // with returnNumBytes describing the data length. This returns TRUE if successful.
  static SbBool  convertData(
                             SoWidget      widget,
                             void        *srcData,
                             uint32_t    srcNumBytes,
                             Atom        desiredType,
                             char        **returnData,
                             uint32_t    *returnNumBytes);

 SoINTERNAL public:
  // Sets a flag indicating whether the paste callback can and
  // should be passed an empty path list after a paste request is
  // made. For compatibility, this flag is FALSE by default, meaning
  // that the callback will never be invoked with an empty path list.
  void        setEmptyListOK(SbBool flag)     { emptyListOK = flag; }
  SbBool      isEmptyListOK() const           { return emptyListOK; }

 protected:
  SoWidget      widget;         // the widget to associated data with
  Atom        clipboardAtom;  // which selection: XA_PRIMARY, XA_SECONDARY, etc.
  Time        eventTime;      // time of the event which caused the copy/paste

  // Paste callback info
  SoXtClipboardPasteCB    *callbackFunc;
  void                    *userData;

  // There can only be one owner of each X selection at any one time.
  // We use the selection atom as the key, and 'this' as the data.
  // We set the owner for each selection in this list for exportSelection.
  static SbDict           *selOwnerList;

  // All the overloaded copy functions call this one.
  void                    copy(SoByteStream *byteStream, Time t);

  // This describes what data types we look for during paste.
  SoXtImportInterestList  *pasteInterest;
  SbPList                 *copyInterest;

  // This is called by exportSelection
  void                    getExportTargets(
                                           char        **value,
                                           uint32_t    *length);

  Atom                    chooseFromImportTargets(
                                                  Atom *supportedTargets,
                                                  int length);

  static SbBool           writeToFile(
                                      SbString    &tmpfile,
                                      void        *srcData,
                                      uint32_t    srcNumBytes);

  // Read the file if it is in Inventor format and add its data to the pathList.
  static void     readFile(SoPathList *&pathList, const char *filename);

  // Read target data we just imported via paste or drop if it is in Inventor format.
  // This returns a newly allocated path list. This will free data when done.
  static SoPathList *readData(
                              SoWidget w,
                              Atom target,
                              void *data,
                              uint32_t numBytes);
 private:
  SoByteStream            *copyBuffer;        // copy/paste storage buffer
  Atom                    copyDataType;
  SbBool                  emptyListOK;

  // This handles the default cases of paste
  void            pasteImport(Atom dataType, void *data, uint32_t numBytes);
  static void     pasteImportCB(
                                void *userData, Atom dataType,
                                void *data, uint32_t numBytes)
    { ((SoXtClipboard *)userData)->pasteImport(dataType, data, numBytes); }

  // Copy and paste callback functions - these are called by the X server.
  // importSelection is called when we import data to paste.
  // exportSelection is called when we send data for someone else to paste.
  // loseSelection is called when we no longer own the selection.
  static void         importSelection(
                                      SoWidget              w,
                                      SoXtClipboard       *clipboard,
                                      Atom                *selAtom,
                                      Atom                *type,
                                      char                *value,
                                      uint32_t    *length,
                                      int                 *format);

  static Boolean      exportSelection(
                                      SoWidget              w,
                                      Atom                *xselection,
                                      Atom                *target,
                                      Atom                *type,
                                      char                **value,
                                      uint32_t    *length,
                                      int                 *format);

  static void         loseSelection(
                                    SoWidget              w,
                                    Atom                *xselection);

  static void         importSelectionTargets(
                                             SoWidget              w,
                                             SoXtClipboard       *clipboard,
                                             Atom                *selAtom,
                                             Atom                *type,
                                             char                *value,
                                             uint32_t    *length,
                                             int                 *format);

};

#endif /* _SO_XT_CLIPBOARD_ */

#endif // _WIN32


