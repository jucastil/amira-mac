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
#ifndef SURFACE_UNDO_H
#define SURFACE_UNDO_H

#include "Undoable.h"
#include "HxSurfEdit.h"
#include <hxsurface/HxSurface.h>

/// implements Undoable for Surfaces
class SurfaceUndo : public Undoable {

 public:

  /// Constructor
  SurfaceUndo(HxSurfEdit* parent);

  /// destructor
  virtual ~SurfaceUndo();

  struct SurfaceUndoEntry {
    struct Patch {
      unsigned char innerRegion;
      unsigned char outerRegion;
      unsigned short boundaryId;
    };

    int mode;
    HxParamBundle parameters;
    McDArray<McVec3f> points;
    McDArray<Patch> patches;
    McDArray<McVec4i> triangles;
    McBitfield selectionData;
    McBitfield highlightData;
  };

  /// remember only one surface
  SurfaceUndoEntry *  savedSurface;

  HxSurfEdit* surfEdit;

  /// undos the last surfaceAction in undoStack
  void undo();

  /** Used to implement undo of surface changes. The method should be
      called before the surface is actually modified. A compressed copy
      of the current surface is stored. Mode bit 0 indicates that
      parameters should be copied. Mode bit 1 indicates that the points
      should be copied. Mode bit 2 indicates that patches and triangles
      should be copied. The default is 7, i.e., all bits are set.
      !!! saveSurface even announce this undoable action in HxSurfEdit.
      You Don`t have to do it!!! */
  void saveSurface(int mode=7);
};

#endif

/// @}