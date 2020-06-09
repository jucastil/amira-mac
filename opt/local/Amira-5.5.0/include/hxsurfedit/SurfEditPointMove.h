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
#ifndef SURF_EDIT_POINT_MOVE_H
#define SURF_EDIT_POINT_MOVE_H

#include "SurfEditMouseTool.h"
#include "Undoable.h"

/// Tool for moving points
class SurfEditPointMove : public SurfEditMouseTool {

public:
  /// Constructor.
  SurfEditPointMove(HxSurfEdit* surfEdit);

  /// Destructor.
  ~SurfEditPointMove();

  /// Hides the dragger if necessary.
  virtual void deactivate();

  /// Event handler.
  virtual void mouseClick(SoEventCallback *eventCB);

  // uses dragger from HxSurfEdit
  void setPointDragger(int p);


  ///////////////////////////////implementatation of Undoable:

  class PointMoveUndo : public Undoable {

  public:

    //konstruktor:
    PointMoveUndo( HxSurfEdit* edit){ surfEdit=edit; }

    ~PointMoveUndo(){
      //undoStack:
      for (int i=0; i<undoStack.size(); i++)
        delete undoStack[i];
    }

    struct MoveUndoEntry {

      int from, to;
      McVec3f oldLocation;

    };

    void undo();
    void saveEntry(MoveUndoEntry* entry);

    //to remeber the moveactions:
    McDArray< MoveUndoEntry* > undoStack;

    HxSurfEdit* surfEdit;


  };

protected:
  int draggerVisible;

  //undoable implementation
  PointMoveUndo* moveUndo;
};

#endif

/// @}
