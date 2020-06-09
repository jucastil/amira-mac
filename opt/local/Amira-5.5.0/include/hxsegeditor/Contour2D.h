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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef CONTOUR2D_H
#define CONTOUR2D_H

#include <mclib/McStringTokenizer.h>
#include <mclib/McVec2f.h>
#include <mclib/McVec2i.h>
#include <mclib/McData2D.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McHandable.h>
#include "GiSelection2D.h"
#include "HxGiWinDLLApi.h"

//--------------------------------------------------------------

#define DINA4W    21.0      // din a4 full width
#define DINA4H    29.7      // din a4 full height
#define DPIPS     72.0      // dots per inch in PS
#define CMPINCH   2.54      // cm per inch

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define NIL  1e-4           // float approximation to zero
#define COLOR_OUTSIDE 0     // color beyond image

#define MAXDIST 2.0         // maximum distance between two points
#define MINDIST 1.0         // minimum distance between two points

#define CUTSTEP 4           // -> splitLoop
#define DISTCUT 1.0         // -> splitLoop

//--------------------------------------------------------------

/// Class for 2D contours
class HXSEGEDITOR_API Contour2D : public McHandable {

public:
  /// Constructor.
  Contour2D();

  /// Destructor.
  ~Contour2D();

  /// Read contours in GRUMMP poly format.
  int readPoly(const char* filename);

  /// Compute bounding box (xmin, xmax, ymin, ymax).
  void getBoundingBox(float bb[4]);

  /// Create contours from raster data.
  void vectorize(GiSelection2D* rasterData);

  /// Class for one loop
  class Loop {
  public:
    /// loop data
    McDArray<McVec2f> vertices;

    /// Return area of one loop.
    float getArea() const;

    /// Return length of loop.
    float getLength() const;

    /// Add or delete points if necessary.
    void equalSpace();

    /// Delete points that lie on straight lines
    void straightDelete();

    /// Delete points that are closer than minDist from each other
    void minDistDelete(float minDist);

    /// Add points such that there is a maxDist between two vertices
    void maxDistAdd(float maxDist);

    /// Compute contour parallel to loop with same number of points
    void parallelLoop(Loop& parallel, float dist);

    /// Assignment operator for loops.
      Loop& operator= (const Loop& other) {
        vertices = other.vertices;
        return *this;
    }
  };

  /// contour data
  McDArray<Loop> loops;

  /// Compute parallel contours
  void parallelContours(Contour2D& cont2D, float dist);

  /// Add or delete points of each loop
  void equalSpace();

  /// Reduce points of each loop
  void straightDelete();

  /// Delete points from each contour
  void minDistDelete(float minDist);

  /// Add points to each contour
  void maxDistAdd(float maxDist);

  /// Return total area of all loops.
  float getArea();

  /// Split loop i into two separate loops
  int splitLoop(int num);

  /// Create PS-File of loops
  int postscript(const char* filename);

protected:
  /// Datatype for edges
  enum Direction {LEFT=1, RIGHT=2, UP=4, DOWN=8};

  /// Methods for Vectorize
  void getLoop(const McVec2i& start);
  McVec2i findNextPixel(Loop& contour, int i, int j);
  int sameColor(int i, int j);
  float getMean(int i, int j);
  int getSelection(int i, int j);
  void getContourPoint(Loop& contour, int i, int j);

  /// Variables for "vectorize"
  GiSelection2D* selection;
  int color;
  Direction edge;

  McDArray<unsigned char> pointInLoop;
};

#endif

/// @}
