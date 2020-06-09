/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef IVFSRVRITEM_H
#define IVFSRVRITEM_H

#include <Inventor/SbBasic.h>

/**
 * Parallels the application CServerItem class.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   Used for OLE server handling.
 *   
 *   Note: Although the class name is CIvfServerItem, the header file name is
 *   IvfSrvrItem.h.
 *   
 * 
 */ 
class IVF_API CIvfServerItem
{
 public:
  /** Constructor */
  CIvfServerItem();
  
  /** Destructor */
  ~CIvfServerItem();
  
  /**
   * Called by the client when it wants to draw the metafile. 
   * Creates an offscreen renderer and writes to the metafile.
   */
  BOOL IvfOnDraw(CDC *pDC, int sizePX, int sizePY);
  
 protected:
};

#endif
