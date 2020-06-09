/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __CIVFMAINFRM_H__
#define __CIVFMAINFRM_H__

#include <Inventor/SbBasic.h>

class CIvfView ;

/**
 * Interface of the IVF frame window class.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   This class provides methods to process messages directed to the frame window.
 *   
 *   Note: Although the class name is CIvfMainFrame, the header file name is
 *   IvfMainFrame.h.
 * 
 * @SEE_ALSO
 *    CIvfApp,
 *    CIvfArchiveInput,
 *    CIvfArchiveOutput,
 *    CIvfComponent,
 *    CIvfDocument
 * 
 * 
 */ 

class IVF_API CIvfMainFrame
{
 protected: //PROTECTED_TO_DOCUMENT 
  /** Constructor */
  CIvfMainFrame();
  /** Destructor */ 
  virtual ~CIvfMainFrame();

 public:
        
  /**
   * This method is called when the application frame window 
   * or dialog is created.  This is where initialization of the
   * SoWin component library occurs.
   */
  virtual void IvfOnCreate(CWnd *pWnd) ;

  /**
   * This method routes command messages to the IVF viewer
   * class.  If the command is processed, TRUE is returned
   * FALSE otherwise.
   */
  virtual BOOL IvfOnCommand(WPARAM wParam, LPARAM lParam);

  /**
   * This method passes query palette messages to the SoWin
   * component library.
   */
  virtual BOOL IvfOnQueryNewPalette();

  /**
   * This method passes palette changed messages to the SoWin
   * component library.
   */
  virtual void IvfOnPaletteChanged(CWnd* pFocusWnd);

  /**
   * This method sets the initial size of the application frame
   * window.
   * OBSOLETE:  you should do whatever you need to do with cs
   *            in your app PreCreateWindow function.  All this
   *          does is set cs.cx = cx and cs.cy = cy
   */
  virtual BOOL IvfPreCreateWindow(CREATESTRUCT& cs,UINT cx,UINT cy) ;

  /**
   * This method sets the window text for the application frame
   * window.  If the window text is set, this method returns
   * TRUE, otherwise FALSE is returned.
   */
  virtual BOOL IvfOnUpdateFrameTitle(BOOL bAddToTitle,CString &strTitle) ;

  /**
   * Set the status line text
   */
  virtual void IvfSetStatusText(LPCTSTR)=0;
  virtual void IvfSetViewerText(CString &);

};

#define IVF_MAINFRAME_BASE() \
        virtual void IvfSetStatusText(LPCTSTR pText);\
        virtual void IvfSetViewerText(CString &);

#endif

