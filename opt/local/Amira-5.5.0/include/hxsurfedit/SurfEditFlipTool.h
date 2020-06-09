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
#ifndef SURF_EDIT_FLIP_TOOL_H
#define SURF_EDIT_FLIP_TOOL_H

#include "SurfEditMouseTool.h"
#include "Undoable.h"

/// Tool for flipping edges
class SurfEditFlipTool : public SurfEditMouseTool {

public:
  /// Constructor.
  SurfEditFlipTool(HxSurfEdit* surfEdit);

  /// Destructor.
  ~SurfEditFlipTool();

  /// Checks if trianglesPerPoint is ok.
  virtual void activate(int);

  /// Checks if trianglesPerPoint is ok.
  virtual void surfaceChanged();

  /// Event handler.
  virtual void mouseClick(SoEventCallback *eventCB);

  /// flips edge and saves action for undo
  int flipEdge(int from, int to);

  /// flips edge without saving action for undo
  int flipEdge(int p1, int p2, int &p3, int &p4, int &t1, int &t2, int &e);


  //////////////////////////////////////////////////////////////
  ////////////////////////// implementierung Undoable-interface:

  class FlipUndo : public Undoable {

  public:

    //konstruktor:
    FlipUndo(SurfEditFlipTool* owner){ parent = owner; }

    ~FlipUndo(){
      //undoStack:
      for (int i=0; i<undoStack.size(); i++)
        delete undoStack[i];
    }


    struct FlipUndoEntry {
      int from, to;
      McSmallArray<int,3> trianglesAtEdge;
      McSmallArray<int,3> patches;
    };

    /// rember the flipped edges
    McDArray< FlipUndoEntry* > undoStack;

    SurfEditFlipTool* parent;

    /// unflips the last edge in undoStack
    void undo() {

      FlipUndoEntry* entry = undoStack.last();
      undoStack.removeLast();

      int from = entry->from;
      int to   = entry->to;
      int e    = entry->patches[0];
      int t1   = entry->trianglesAtEdge[0];
      int t2   = entry->trianglesAtEdge[1];

      int p3,p4;

      parent->flipEdge(from,to,p3,p4,t1,t2,e);
      parent->displaySurface->fire();

    }

    /// puts new Entry into undoStack
    void saveEntry(FlipUndoEntry* entry){
      undoStack.append(entry);
    }

  };


private:

  ////////////////////////////////ATTRIBUTE

  /// Input surface to be drawn
  McHandle<HxSurface>  surface;

  /// Display module for the contour
  HxDisplaySurface * displaySurface;

  /// implementation of Undoable
  FlipUndo* flipUndo;


  /////////////////////////////////////////

  friend class FlipUndo;

};

#endif

/// @}
