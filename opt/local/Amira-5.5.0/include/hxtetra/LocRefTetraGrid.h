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

/// @addtogroup hxtetra hxtetra
/// @{
#ifndef LOCREF_TETRAGRID_H
#define LOCREF_TETRAGRID_H

#include <hxsurface/HxSurface.h>
#include <hxfield/HxTetraGrid.h>
#include <hxtetra/HxTetraWinDLLApi.h>

/// Perform local refinement of tetrahedral grid.
class HXTETRA_API LocRefTetraGrid 
{
  public:

    /// Constructor.
    LocRefTetraGrid();

    /// Destructor.
    ~LocRefTetraGrid();

    /// Find edge in surface.
    int findEdgeInSurf(HxSurface* surface, int from, int to);

    /// Find edge in grid.
    int findEdgeInGrid(HxTetraGrid* grid, 
		       McDArray < McSmallArray <int,8> > &edgesPerPoint,
		       int from, int to);

    /// Initialize pointsToBeMoved.
    void initPointsToBeMoved(int mode,
			     HxTetraGrid* grid, HxSurface* surface, 
			     McDArray<int> &markRefinedEdges,
			     McDArray<int> &aliasesGridToSurf,
			     McDArray<int> &pointsToBeMoved,
			     McDArray< McSmallArray<int,8> > &edgesPerPoint,
			     int check);

    /// Modify refinement: remove bad green triangles.
    void modifyRefinement(int mode,
			  int selectTriangles,
			  float threshold,
			  HxTetraGrid* grid, 
			  HxSurface* surface,
			  HxSurface* refinedSurface,
			  McDArray<int> &markRefinedEdges,
			  McDArray<int> &aliasesGridToSurf,
			  McDArray<int> &pointsToBeMoved,
			  McDArray< McSmallArray<int,8> > &edgesPerPoint);

    /// Do local refinement as implied by markRefinedEdges.
    int doLocalRefinement(HxTetraGrid* coarseGrid, 
			  HxTetraGrid* grid, 
			  McDArray<int> &markRefinedEdges,
			  McDArray< McSmallArray<int,8> > &edgesPerPoint);

    /// Do local refinement considering markPoints in red refinements.
    int doLocalRefinement(HxTetraGrid* coarseGrid, 
			  HxTetraGrid* grid, 
			  McDArray<int> &markRefinedEdges,
			  McDArray< McSmallArray<int,8> > &edgesPerPoint,
			  McDArray<signed char> &markPoints);

    /// Move points, 0: new points, 1: all points, 2: new and adjacent old.
    void movePoints(int moveInner,
		    HxTetraGrid* grid, 
		    HxTetraGrid* coarseGrid,
		    HxSurface* refinedSurf,
		    McDArray<int> &markRefinedEdges,
		    McDArray<int> &pointsToBeMoved);

    /// Restore boundary condition triangles in refined grid.
    int restoreBCTriangles(HxTetraGrid* coarseGrid, 
			   HxTetraGrid* grid, 
			   McDArray<int> &markRefinedEdges,
			   McDArray< McSmallArray<int,8> > &edgesPerPoint);

    /// Create regular green closure.
    void createRegularGreenClosure(
             HxTetraGrid* grid,
	     McDArray<int> &markRefinedEdges,
	     McDArray< McSmallArray<int,8> > &trianglesPerEdge,
	     McDArray< McSmallArray<int,8> > &edgesPerPoint,
	     McDArray<int> &newMarkedEdges, 
	     McDArray<int> &allMarkedEdges);

    /// Check quality of green triangles.
    void checkGreenTriangles(int mode,
			     int selectTriangles, 
			     float threshold,
			     HxTetraGrid* grid, 
			     HxSurface* surface, 
			     HxSurface* refinedSurface, 
			     McDArray<int> &markRefinedEdges,
			     McDArray<int> &aliasesGridToSurf,
			     McDArray<int> &pointsToBeMoved,
			     McDArray< McSmallArray<int,8> > &trianglesPerEdge,
			     McDArray< McSmallArray<int,8> > &edgesPerPoint);


  protected:

    /// Update pointsToBeMoved after regular green closure.
    void updatePointsToBeMoved(int mode,
			       HxTetraGrid* grid, HxSurface* surface, 
			       McDArray<int> &markRefinedEdges,
			       McDArray<int> &aliasesGridToSurf,
			       McDArray<int> &pointsToBeMoved,
			       McDArray< McSmallArray<int,8> > &edgesPerPoint,
			       McDArray<int> &newMarkedEdges,
			       McDArray<int> &allMarkedEdges,
			       int nLastEdges);

    /// Green1 refinement (one edge to be refined).
    int refineGreen1(HxTetraGrid* grid, 
		     int* tetVertices, 
		     int midPoints[6], 
		     unsigned char material);

    /// Green2 refinement (two edges to be refined).
    int refineGreen2(HxTetraGrid* grid, 
		     int* tetVertices, 
		     int midPoints[6], 
		     unsigned char material);

    /// Green3 refinement (three edges to be refined).
    int refineGreen3(HxTetraGrid* grid, 
		     int* tetVertices, 
		     int midPoints[6], 
		     unsigned char material);

    /// Red (global) refinement.
    int refineRed(HxTetraGrid* grid, 
		  int* tetVertices, 
		  int midPoints[6], 
		  unsigned char material,
		  McDArray<signed char> &markPoints);

    /// Find triangle given by triVertices using trianglesPerPoint.
    int findTriangle(HxTetraGrid* grid,
		     McDArray< McSmallArray<int,8> > &trianglesPerPoint,
		     int triVertices[3]);

};

#endif

/// @}
