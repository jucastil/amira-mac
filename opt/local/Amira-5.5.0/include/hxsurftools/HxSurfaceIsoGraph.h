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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HX_SURFACEISOGRAPH_H
#define HX_SURFACEISOGRAPH_H

#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>
#include <hxlines/HxLineSet.h>
#include <hxcore/HxMessage.h>

#include <mclib/McHashTable.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>

class HxSurfaceIsoEdge;
class HxSurfaceIsoContour : public McHandable {
public:
    HxSurfaceIsoContour () {
        from = to = NULL;
        isTraversed = false;
    }
    HxSurfaceIsoContour (HxSurfaceIsoEdge* _from, HxSurfaceIsoEdge* _to) {
        from = _from;
        to = _to;
        isTraversed = false;
    }
    HxSurfaceIsoEdge* otherEnd (HxSurfaceIsoEdge* otherThan) {
        return (otherThan == from?to:from);
    }
    HxSurfaceIsoEdge* from;
    HxSurfaceIsoEdge* to;
    bool isTraversed;
    
};
class HxSurfaceIsoEdge : public McHandable {
public:
    HxSurfaceIsoEdge (McVec2i _keyToMe, int _pointNumber) : 
      keyToMe (_keyToMe) 
      , pointNumber (_pointNumber)
      , contours (0,2)
      , pointBary (-1.0f)
      , isTraversed (false)
      {
        
    }
    void addNeighbour (McHandle<HxSurfaceIsoContour> contour) {
        contours.append (contour);
    }
    void gatherPoints (McDArray<int> &newLine, int addToIndex=0) {
        //theMsg->printf ("%d", addToIndex + pointNumber);
        newLine.append(addToIndex+pointNumber);
        for (int i=0; i < contours.size (); i++) {
            HxSurfaceIsoContour *nextContour = contours[i];
            if (!nextContour->isTraversed) {
                nextContour->isTraversed = true;
                nextContour->otherEnd (this)->gatherPoints (newLine, addToIndex);
                if (i+1 == contours.size ()) {
                    // traversed last neighbour, so i am fully traversed
                        isTraversed = true;
                }
                return;
            }
        }
        isTraversed = true;
    }
    void init () {
        isTraversed = false;
        for (int i=0; i < contours.size (); i++) {
            contours[i]->isTraversed = false;
        }
    }
    McVec2i keyToMe;
    int pointNumber;
    McDArray< McHandle<HxSurfaceIsoContour> > contours;
    float pointBary;
    bool isTraversed;
    McVec3f pointOnIsoline;
};
/** */
class HXSURFTOOLS_API HxSurfaceIsoGraph {
  public:
    /// Constructor.
      HxSurfaceIsoGraph();
     
      ~HxSurfaceIsoGraph ();
      void beginTraversal ();
      void addEdgePair (int i1, int i2, int j1, int j2, McVec3f &point1, McVec3f &point2, float u1, float u2);
      void addToLineSet (HxLineSet * lineset);
      void init ();
      int size ();
      McHashTable<McVec2i, McHandle<HxSurfaceIsoEdge> > &getIsoGraph () {return isoGraph;}
  private:
      McHashTable<McVec2i, McHandle<HxSurfaceIsoEdge> > isoGraph;
};

#endif

/// @}
