/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Dave Immel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef _WIN32
#  include <Inventor/Win/SoWinPrintDialog.h>
#else // _WIN32

#ifndef SO_XT_PRINT_DIALOG_
#define SO_XT_PRINT_DIALOG_

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include <Inventor/SbBasic.h>
#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/misc/SoCallbackList.h>

class SbPList;
class SoNode;
class SoPath;
class SoGLRenderAction;
class SoXtPrintDialog;


// callback function prototypes
typedef void SoXtPrintDialogCB(void *userData, SoXtPrintDialog *dialog);

///////////////////////////////////////////////////////////////////////
//
// class: SoXtPrintDialog
//
///////////////////////////////////////////////////////////////////////

/**
 * Dialog box for controlling printing.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class provides an interactive widget for setting available options used in
 *   printing with the SoPrintAction and its subclasses. Options include whether to
 *   print with hidden lines or not, whether to print using the Landscape format,
 *   whether to print to a file or a printer.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Print Dialog 
 *   !!------------------------------------------------ 
 *   *IvPrintDialTitle.labelString: Print Dialog 
 *   *IvPrintDialIconTitle.labelString: Print Dialog 
 *   *IvPrintDialPrinter.labelString: Printer: 
 *   *IvPrintDialPageOut.labelString: Page Output: 
 *   *IvPrintDialToPrinter.labelString: To Printer 
 *   *IvPrintDialToFile.labelString: To File 
 *   *IvPrintDialQuit.labelString: Quit 
 *   *IvPrintDialPrint.labelString: Print 
 *   *IvPrintDialMessage.labelString: Message: 
 *   *IvPrintDialFileFormat.labelString: File Format: 
 *   *IvPrintDialPostScript.labelString: PostScript 
 *   *IvPrintDialRGB.labelString: RGB 
 *   *IvPrintDialPrintQuality.labelString: Print Quality: 
 *   *IvPrintDialHigh.labelString: High 
 *   *IvPrintDialDraft.labelString: Draft 
 *   *IvPrintDialPageFormat.labelString: Page Format 
 *   *IvPrintDialPortrait.labelString: Portrait 
 *   *IvPrintDialLandscape.labelString: Landscape 
 *   *IvPrintDialPrintSize.labelString: Print Size (inches): 
 *   *IvPrintDialFileName.labelString: File Name: 
 *   *IvPrintDialResolution.labelString: Resolution 
 *   *IvPrintDialBy.labelString: by 
 *   *IvPrintDialDpi.labelString: DPI: 
 *   *IvPrintDialMess1.labelString: Printing in progress... 
 *   *IvPrintDialMess2.labelString: ERROR: Empty database. 
 *   *IvPrintDialMess3.labelString: ERROR: Exceeds 
 *   *IvPrintDialMess4.labelString: ERROR: Could not execute print. 
 *   *IvPrintDialMess5.labelString: ERROR: Could not execute print. 
 *   *IvPrintDialMess6.labelString: ERROR: No printer. 
 *   *IvPrintDialMess7.labelString: ERROR: Couldn't open 
 *   *IvPrintDialMess8.labelString: ERROR: No file name. 
 *   *IvPrintDialMess9.labelString: ERROR: Could not open file. 
 *   *IvPrintDialMess10.labelString: ERROR: Could not get data. 
 *   *IvPrintDialMess11.labelString: ERROR: Could not get data. 
 *   *IvPrintDialMess12.labelString: Printing completed. 
 * </PRE>
 * 
 * @SEE_ALSO
 *    SoGLRenderAction,
 *    SoXtComponent
 * 
 * 
 */ 

class INVENTORXT_API SoXtPrintDialog : public SoXtComponent {
 public:
  /**
   * Constructor.
   */
  SoXtPrintDialog(
                  SoWidget parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE);
  /**
   * Constructor that takes a render action.
   */
  SoXtPrintDialog(
                  SoGLRenderAction *act,
                  SoWidget parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoXtPrintDialog();

  /**
   * Sets the path to nodes to be used for printing. 
   */
  void        setSceneGraph( SoPath *path );
  /**
   * Sets the root node to be used for printing. 
   */
  void        setSceneGraph( SoNode *root );

  /**
   * Gets the root node to be used for printing. 
   */
  SoNode      *getSceneGraph()        { return rootNode; }
  /**
   * Gets the path to nodes to be used for printing. 
   */
  SoPath      *getSceneGraphPath()    { return rootPath; }

  /**
   * Sets the render action to be used when printing. 
   */
  void        setGLRenderAction(const SoGLRenderAction *act);
  /**
   * Gets the render action to be used when printing. 
   */
  SoGLRenderAction *getGLRenderAction();

  /**
   * Sets the size of the printed image in inches. This is typically 
   * the same size as the window displaying the scene to be printed.
   */
  void        setPrintSize( const SbVec2f &inches );
  /**
   * Sets the size of the printed image in pixels. This is typically 
   * the same size as the window displaying the scene to be printed.
   */
  void        setPrintSize( const SbVec2s &pixels );

  /**
   * Two callbacks are maintained, one which gets called just before a print is
   * executed, and one which gets called after a print is executed. 
   * This method sets the before print callback.
   * Set it to NULL to remove the callback.
   */
  inline void setBeforePrintCallback(
                                     SoXtPrintDialogCB *f,
                                     void *userData = NULL);
  /**
   * Two callbacks are maintained, one which gets called just before a print is
   * executed, and one which gets called after a print is executed.
   * This method sets the after print callback.
   * Set it to NULL to remove the callback.
   */
  inline void setAfterPrintCallback(
                                    SoXtPrintDialogCB *f,
                                    void *userData = NULL);

 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtPrintDialog::buildWidget()
  // when they are ready for it to be built.
  SoXtPrintDialog(
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
  void            placeBottomOfDialog( SoXtPrintDialog * );
  void            buildRadioButton( char *,  char *, char *, int, int,
                                    SoWidget, XtCallbackProc );
  void            buildSizeFields( char *, int, SoWidget, SoWidget &, SoWidget &,
                                   XtCallbackProc, XtCallbackProc );
  void            buildDPIField( int, SoWidget, SoWidget &, XtCallbackProc );
  void            updateTextports();

  //
  // Callback routines.
  //
  static void     qualityCB(  SoWidget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
  static void     pageFormatCB(  SoWidget, SoXtPrintDialog *,
                                 XmAnyCallbackStruct * );
  static void     fileFormatCB(  SoWidget, SoXtPrintDialog *,
                                 XmAnyCallbackStruct * );
  static void     printerHorizSizeCB(  SoWidget, SoXtPrintDialog *,
                                       XmAnyCallbackStruct * );
  static void     printerVertSizeCB(  SoWidget, SoXtPrintDialog *,
                                      XmAnyCallbackStruct * );
  static void     postScriptHorizSizeCB(  SoWidget, SoXtPrintDialog *,
                                          XmAnyCallbackStruct * );
  static void     postScriptVertSizeCB(  SoWidget, SoXtPrintDialog *,
                                         XmAnyCallbackStruct * );
  static void     rgbHorizSizeCB( SoWidget, SoXtPrintDialog *,
                                  XmAnyCallbackStruct * );
  static void     rgbVertSizeCB(  SoWidget, SoXtPrintDialog *,
                                  XmAnyCallbackStruct * );
  static void     printerDPICB(   SoWidget, SoXtPrintDialog *,
                                  XmAnyCallbackStruct * );
  static void     postScriptDPICB( SoWidget, SoXtPrintDialog *,
                                   XmAnyCallbackStruct * );
  static void     outputCB( SoWidget, SoXtPrintDialog *,
                            XmAnyCallbackStruct * );
  static void     printCB(  SoWidget, SoXtPrintDialog *,
                            XmAnyCallbackStruct * );
  static void     quitCB(   SoWidget, SoXtPrintDialog *,
                            XmAnyCallbackStruct * );
  static void     listPick( SoWidget, SoXtPrintDialog *ml,
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
SoXtPrintDialog::setBeforePrintCallback(
                                        SoXtPrintDialogCB *f,
                                        void *userData )
{ 
  beforeList.clearCallbacks();
  beforeList.addCallback((SoCallbackListCB *) f, userData);
}

void
SoXtPrintDialog::setAfterPrintCallback(
                                       SoXtPrintDialogCB *f,
                                       void *userData )
{
  afterList.clearCallbacks();
  afterList.addCallback((SoCallbackListCB *) f, userData);
}


#endif /* SO_XT_PRINT_DIALOG_ */

#endif // _WIN32


