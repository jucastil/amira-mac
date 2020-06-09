/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef SURF_EDIT_BRUSH_TOOL_H
#define SURF_EDIT_BRUSH_TOOL_H

#include <QLabel>
#include <QCursor>

#include "SurfEditMouseTool.h"

class HxViewer;
class QMenu;
class QAction;
class QSlider;
class QLabel;
class BufferUndo;
class QCheckBox;

/// Tool for picking triangles by brush painting.
class SurfEditBrushTool : public SurfEditMouseTool {
  
  Q_OBJECT

public:
  /// Constructor.
  SurfEditBrushTool(HxSurfEdit* surfEdit);
  
  /// Destructor.
  ~SurfEditBrushTool();
  
  /// activates pulldownmenu and eventcallback
  virtual void activate(int);

  /// Hides popupmenu
  virtual void deactivate();
  
  /// Checks if trianglesPerPoint is ok.
  virtual void surfaceChanged();  

  virtual void mouseClick(SoEventCallback* eventCB);

 protected slots:
 void setWidth(int n);

  /// Event handler.
  virtual bool mouseMove(const SoEvent *, HxViewer *);
  static SbBool eventCallback (const SoEvent *, HxViewer *, void *owner);
 
private:

  /// MEMBERVARS

  int screen_x, screen_y, screen_w, screen_h;

  // mouse movement during selection
  bool  eventCallbackRegistered;
  bool  dragSelection;

  HxSurface *  surface;

  /// popup menu
  QMenu * pmenu;
  QSlider *  item_slider;
  QLabel * item_num;
  QAction * item_visible_trngl;

  /// to convert world->view
  SbMatrix  viewMatrix;

  /// set of current visible trngls
  McBitfield  visibleTrngls;

  /// the implementation of undoable
  BufferUndo *  bufferUndo;

  // line width, line color and point list for triangle selection
  int  lineWidth;
  float  lineColor[3];

  // highlight or unhighlight?
  int state;

  //////////////////////////////////////////////


  void  registerEventCallback (void);
  void  unregisterEventCallback (void);

  /// draws a circle around the mouse
  void drawMouse(int x, int y);

  /// highlights triangles in circle
  void selectTrngls(McVec2i center, float radius );

};

#endif

/// @}
