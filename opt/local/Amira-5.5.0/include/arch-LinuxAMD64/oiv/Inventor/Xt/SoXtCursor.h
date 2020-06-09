/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _NEW_SO_XT_CURSOR
#define _NEW_SO_XT_CURSOR

#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

class SbConfig;

/**
 * @SCVEXT Encapsulates the construction and definition of an X Windows cursor.
 * 
 * @ingroup ScaleViz
 * 
 * @DESCRIPTION
 * This class can be used with the setCursor method of SoWinMPGLWidget.
 *
 * 
 */ 

class INVENTORXT_API SoXtCursor {

 public:
    
  /**
   * Constructor.
   */ 
  SoXtCursor();
  
  /**
   * Destructor.
   */ 
  ~SoXtCursor();

  /**
   * Creates the cursor.
   */ 
  int create(void);

  /**
   * Sets a bitmap file for the shape of the cursor.
   */   
  int setBitmapShapeFile(char * fileName);
  
  /**
   * Sets a bitmap file for the mask of the cursor. 
   * By default the mask is the same bitmap as the shape bitmap.
   */  
  int setBitmapMaskFile(char * fileName);
  
  /**
   * Sets the foreground color of the cursor (i.e., color of the shape bitmap).
   */ 
  int setForegroundColor(int red,int green,int blue);

  /**
   * Sets the background color of the cursor (i.e., color of the mask bitmap).
   */ 
  int setBackgroundColor(int red,int green,int blue);

  /**
   * Sets the font cursor id.
   */ 
  int setFontCursor(int ID);

  /**
   * Sets the hot spot coordinates within the bitmap.
   */ 
  int setHotSpot(int x,int y);
  
  /**
   * Sets the pixmap to define the cursor shape.
   */ 
  int setPixmap(char * bits, unsigned int w, unsigned int h, int x_hot, int y_hot);
  
  /**
   * Enables the cursor within the specified window.
   */ 
  int define(Display *, Window, int cursorId);
  
 private:
  
  /**
   * Creates the cursor in the specified display.
   */ 
  int create(Display * dpy, int cursorId);
  
  /**
   * Font cursor id.
   */ 
  int fontCursor;

  /**
   * Dimensions of the pixmap.
   */ 
  unsigned int width,height;
  
  /**
   * Coordinates of the hot point within the cursor pixmap.
   */  
  int xhot,yhot;
  
  char * pixmap_bits;
  
  /**
   * File containing the shape bitmap.
   */  
  char * bitmap_shape_file;

  /**
   * File containing the shape bitmap.
   */  
  char * bitmap_mask_file;
  
  /**
   * Foreground color of the cursor.
   */    
  XColor foreground;

  /**
   * Background color ot the cursor.
   */    
  XColor  background;

  /**
   * Cursor.
   */    
  Cursor * cursor;

  /**
   * Cursor shape pixmap.
   */    
  Pixmap shape;
  /**
   * Cursor mask pixmap.
   */    
  Pixmap mask;

  /**
   * Pointer on Multipipe configuration.
   */      
  SbConfig * mpConfig;
  
  /**
   * Try to open bitmapfile.
   */      
  int fileValid(char * bitmapfile);

};

#endif /* _SO_XT_CURSOR*/
