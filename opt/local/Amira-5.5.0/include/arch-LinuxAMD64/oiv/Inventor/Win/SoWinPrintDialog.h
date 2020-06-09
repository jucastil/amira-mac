/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef SO_WIN_PRINT_DIALOG_
#define SO_WIN_PRINT_DIALOG_

#ifndef DONT_DOC

#ifdef _WIN32
// Not currently implemented for _WIN32
// (printing support provided through MFC and IVF)
#else

#include <Xm/Xm.h>

#include <Inventor/SbBasic.h>
#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/misc/SoCallbackList.h>

class SbPList;
class SoNode;
class SoPath;
class SoGLRenderAction;
class SoWinPrintDialog;


// callback function prototypes
typedef void SoWinPrintDialogCB(void *userData, SoWinPrintDialog *dialog);

///////////////////////////////////////////////////////////////////////
//
// class: SoWinPrintDialog
//
///////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTORW_API SoWinPrintDialog : public SoWinComponent {
 public:
  // Constructors and destructor.
  SoWinPrintDialog(
                   SoWidget parent = NULL,
                   const char *name = NULL, 
                   SbBool buildInsideParent = TRUE);
  SoWinPrintDialog(
                   SoGLRenderAction *act,
                   SoWidget parent = NULL,
                   const char *name = NULL, 
                   SbBool buildInsideParent = TRUE);
  ~SoWinPrintDialog();

  // Sets/gets the node to be used for printing
  void        setSceneGraph( SoPath *path );
  void        setSceneGraph( SoNode *root );

  SoNode      *getSceneGraph()        { return rootNode; }
  SoPath      *getSceneGraphPath()    { return rootPath; }

  void        setGLRenderAction(const SoGLRenderAction *act);
  SoGLRenderAction *getGLRenderAction();

  // Sets the size of the printing
  void        setPrintSize( const SbVec2f &s );
  void        setPrintSize( const SbVec2s &s );

  // These two callbacks are used before and after a print
  // action is performed.
  inline void setBeforePrintCallback(
                                     SoWinPrintDialogCB *f,
                                     void *userData = NULL);
  inline void setAfterPrintCallback(
                                    SoWinPrintDialogCB *f,
                                    void *userData = NULL);

 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinPrintDialog::buildWidget()
  // when they are ready for it to be built.
  SoWinPrintDialog(
                   SoWidget parent,
                   const char *name, 
                   SbBool buildInsideParent, 
                   SbBool buildNow);

  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
  SoNode          *rootNode;
  SoPath          *rootPath;
  SbBool          printDone;
  SbBool          highQuality;
  SbBool          portraitFormat;
  SbBool          printerOutput, postScriptOutput;
  SbBool          nodeMostRecent;
  SbBool          WYSIWYGflag;
  SoWidget          messageWidget, printButton, quitButton;
  SoWidget          messageLabelWidget, fileFormatWidget;
  SoWidget          toPrinterWidget, toPostScriptFileWidget, toRGBFileWidget;
  SoWidget          printerHorizSize, printerVertSize;
  SoWidget          postScriptHorizSize, postScriptVertSize;
  SoWidget          rgbHorizSize, rgbVertSize;
  SoWidget          printerDPIField, postScriptDPIField;
  SoWidget          rgbFilenameWidget, postScriptFilenameWidget;
  SbPList         *printers;
  char            *defaultPrinter;
  int             whichPrinter;       // index into printers list
  SbVec2f         printSize;
  SbVec2s         printRes;
  SoCallbackList  beforeList, afterList;
  SbBool          alreadyUpdated;

  void            print();            // called by printCallback
  void            getPrinterList();
  void            printToPostScript( SoNode *, char *, int, int );
    
  // Methods used to build the print dialog.
  void            buildToPrinterWidget( SoWidget parent );
  void            buildToPostScriptFileWidget( SoWidget parent );
  void            buildToRGBFileWidget( SoWidget parent );
  void            placeBottomOfDialog( SoWinPrintDialog * );
  void            buildRadioButton( char *,  char *, char *, int, int,
                                    SoWidget, XtCallbackProc );
  void            buildSizeFields( char *, int, SoWidget, SoWidget &, SoWidget &,
                                   XtCallbackProc, XtCallbackProc );
  void            buildDPIField( int, SoWidget, SoWidget &, XtCallbackProc );
  void            updateTextports();

  //
  // Callback routines.
  //
  static void     qualityCB(  SoWidget, SoWinPrintDialog *,
                              XmAnyCallbackStruct * );
  static void     pageFormatCB(  SoWidget, SoWinPrintDialog *,
                                 XmAnyCallbackStruct * );
  static void     fileFormatCB(  SoWidget, SoWinPrintDialog *,
                                 XmAnyCallbackStruct * );
  static void     printerHorizSizeCB(  SoWidget, SoWinPrintDialog *,
                                       XmAnyCallbackStruct * );
  static void     printerVertSizeCB(  SoWidget, SoWinPrintDialog *,
                                      XmAnyCallbackStruct * );
  static void     postScriptHorizSizeCB(  SoWidget, SoWinPrintDialog *,
                                          XmAnyCallbackStruct * );
  static void     postScriptVertSizeCB(  SoWidget, SoWinPrintDialog *,
                                         XmAnyCallbackStruct * );
  static void     rgbHorizSizeCB( SoWidget, SoWinPrintDialog *,
                                  XmAnyCallbackStruct * );
  static void     rgbVertSizeCB(  SoWidget, SoWinPrintDialog *,
                                  XmAnyCallbackStruct * );
  static void     printerDPICB(   SoWidget, SoWinPrintDialog *,
                                  XmAnyCallbackStruct * );
  static void     postScriptDPICB( SoWidget, SoWinPrintDialog *,
                                   XmAnyCallbackStruct * );
  static void     outputCB( SoWidget, SoWinPrintDialog *,
                            XmAnyCallbackStruct * );
  static void     printCB(  SoWidget, SoWinPrintDialog *,
                            XmAnyCallbackStruct * );
  static void     quitCB(   SoWidget, SoWinPrintDialog *,
                            XmAnyCallbackStruct * );
  static void     listPick( SoWidget, SoWinPrintDialog *ml,
                            XmAnyCallbackStruct * );

  // SoWidget for controlling the Print Style
  SoWidget          styleButton;
  int             currentStyle;

 private:
  // Builds the widget.
  SoWidget          buildWidget(SoWidget parent);

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
};

// Inline methods
void
SoWinPrintDialog::setBeforePrintCallback(
                                         SoWinPrintDialogCB *f,
                                         void *userData )
{ 
  beforeList.clearCallbacks();
  beforeList.addCallback((SoCallbackListCB *) f, userData);
}

void
SoWinPrintDialog::setAfterPrintCallback(
                                        SoWinPrintDialogCB *f,
                                        void *userData )
{
  afterList.clearCallbacks();
  afterList.addCallback((SoCallbackListCB *) f, userData);
}

#endif //_WIN32

#endif
#endif /* SO_WIN_PRINT_DIALOG_ */

