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
#ifndef FLIP_TETRAGRID_H
#define FlIP_TETRAGRID_H

#include <mclib/McVec4i.h>
#include <mclib/McProgressInterface.h>

#include <hxcore/HxMessage.h>

#include <hxfield/HxTetraGrid.h>
#include <hxtetra/HxGridVolume.h>
#include <hxtetra/HxTetraWinDLLApi.h>

#define EDGE_FLIP_NORTH_POLE -2
#define EDGE_FLIP_SOUTH_POLE -1
#define EDGE_FLIP_NORTH_FACE  1000
#define EDGE_FLIP_SOUTH_FACE  2000

/// Edge and face flips in tetrahedral grids.
class HXTETRA_API FlipTetraGrid {

  public:

    /// Constructor.
    FlipTetraGrid(HxTetraGrid* tetraGrid);

    /// Destructor.
    ~FlipTetraGrid();

    /// Set grid volume.
    void setGridVolume(HxGridVolume* gridVol);

    /// possible face types
    enum FaceClass {
	/// Obsolete triangle.
	OBSOLETE=0,
	/// Boundary face (marked by isBoundary or 
	/// boundaryConditionId).
	BOUNDARY,
	/// Swappable 2 to 3.
	FLIP23,
	/// Swappable 3 to 2.
	FLIP32,
	/// Swappable 2 to 2.
	FLIP22,
	/// Swappable 4 to 4.
	FLIP44,
	/// Non-Swappable 3 to 2.
	NOFLIP32,
	/// Non-Swappable 4 to 4.
	NOFLIP44,
	/// Non-Swappable.
	NOFLIP40,
	/// Non-Swappable (Never used (?).
	NOFLIP30,
	/// Non-Swappable (Never used (?).
	NOFLIP20,
	/// Other (non-swappable).
	OTHER,
	/// Classify Error.
	CLASSIFY_ERROR
    };

    /// Configuration for edge flip.
    struct EdgeFlipConfig {
	int nPerm;
	McSmallArray<McVec2i,13> faceCells;
	McSmallArray<McVec3i,13> faceVerts;
	McSmallArray<McVec4i,10> cellFaces;
    };

    /// Combined smoothing: flip and smooth.
    void combinedSmoothing(float threshold1, float threshold2,
			   int nLoops, int saveBoundaryTriangles=0,
			   McProgressInterface *progress=NULL,
			   HxMessage *hxMsg=NULL);

    /// Flip faces and edges.
    int flip(float qualityBound=0., int tppExists=0,
	     int flagCombined=0, int saveBoundaryTriangles=0,
	     McProgressInterface *progress=NULL,
	     HxMessage *hxMsg=NULL);

    /// Flip marked faces (and edges).
    int flip(McBitfield &markFacesToBeFlipped,
	     float qualityBound=0., int tppExists=0,
	     int flagCombined=0, int saveBoundaryTriangles=0,
	     McProgressInterface *progress=NULL,
	     HxMessage *hxMsg=NULL);

    /// Flip long edges.
    int flipLongEdges(float maxEdgeLen, float minEdgeQuali,
		      float qualityBound=0., int flagCombined=0,
		      McProgressInterface *progress=NULL,
		      HxMessage *hxMsg=NULL);

    /// Bisect edges.
    // int bisectEdges();

    /// Remove inner vertices surrounded by 4, 6 .. 14 tetras.
    int removeInner(int tppExists=0,
		     int maxNumNeighbours=10,
		     float limitEdgeLen=0.,
		     McProgressInterface *progress=NULL,
		     HxMessage *hxMsg=NULL);

    /// Repair bad tetras (inverted, slivers and caps).
    int repairBadTetras(float qualityBound=0., int onlyInverted=0, 
			int tppExists=0,
			McProgressInterface *progress=NULL,
			HxMessage *hxMsg=NULL);

  protected:
    /// Create lookup tables for edge flip.
    void initEdgeConfigs();

    /// Flip edge.
    int flipEdge(int iEdge, HxMessage *hxMsg=NULL);

    /// Flip edge.
    int flipEdge(int iVert1, int iVert2, HxMessage *hxMsg=NULL);

    /// Flip edge.
    int flipEdge(int iVert1, int iVert2, float threshold,
		 HxMessage *hxMsg=NULL);

    /// Flip boundary edge
    int flipBoundaryEdge(int iNorth, int iSouth, 
			 McSmallArray<int,10>& tetrasAtEdge, 
			 McSmallArray<int,10>& trianglesAtEdge, 
			 McSmallArray<int,10>& equatorVertices);

    /// Flip face.
    int flipFace(int iFace, int ignoreBoundary=0,
		 HxMessage *hxMsg=NULL);

    /// Classify face.
    FaceClass classifyFace(int iFace, int* tetList, int* vertList, 
			   int ignoreBoundary=0);

    /// Examine if swapping improves tetra quality.
    int swapImprovement(FaceClass faceClass, 
			int* tetList, int* vertList,
			int qualityMeasure=0);

    /// Examine if swapping improves diam ratio.
    int swapImprovementMaxDiamRatio(FaceClass faceClass, 
				    int* tetList, int* vertList);

    /// Perform swapping.
    int reconfigure(FaceClass faceClass, int* tetList, 
		    int iFace, int* vertList,
		    HxMessage *hxMsg=NULL);

    /// Perform swapping for case FLIP22.
    int reconfigureF22(int* tetList, int iFace, int* vertList,
		       HxMessage *hxMsg=NULL);

    /// Perform swapping for case FLIP23.
    int reconfigureF23(int* tetList, int iFace, int* vertList,
		       HxMessage *hxMsg=NULL);

    /// Perform swapping for case FLIP32.
    int reconfigureF32(int* tetList, int iFace, int* vertList,
		       HxMessage *hxMsg=NULL);

    /// Perform swapping for case FLIP44.
    int reconfigureF44(int* tetList, int iFace, int* vertList,
		       HxMessage *hxMsg=NULL);

    /// Return 1 if tetrahedron iTet is a cap.
    int isCap(int iTet, int iVert, float* dihedAngles);

    /// Return 1 if tetrahedron iTet is a sliver.
    int isSliver(int iTet, int iVert, float* dihedAngles, 
		 McVec3f* newVertices,
		 HxMessage *hxMsg=NULL);

    /// Repair sliver.
    int repairSliver(int iTet, int iEdgeMax, McVec3f* newVertices,
		     HxMessage *hxMsg=NULL);

    /// Repair cap.
    int repairCap(int iTet, int iVertMax, HxMessage *hxMsg=NULL);

    /// Find chain of tetras adjacent to an edge.
    int findChain(int iTet, McDArray<int> &neighbours,
		  McDArray<int> &localFaceNumbers,
		  int nei1, int nei2, 
		  int material,
		  McDArray<int> &chain);

    /// Find exterior faces for a group of tetras.
    void findExteriorFaces(McDArray<int> &tetraList, 
			   McDArray<int> &exteriorFaces,
			   McDArray<int> &orientations,
			   McDArray<int> &interiorFaces);

    /// Compute center of face midpoints.
    void getCenterOfFaces(McDArray<int> &faces, 
			  McVec3f &center);


    /// Replace oldTetras by newTetras.
    int replaceTetras(McDArray<int> &oldTetras, 
		      McDArray<int> &newTetras, 
		      McDArray<int> &exteriorFaces, 
		      McDArray<int> &orientations,
		      McDArray<int> &oldInteriorFaces,
		      int connectToCenter=0);

    /// Check if oldTetras form a star-shaped region and 
    /// can be replaced.
    int canBeReplaced(int iTet, int nNei, 
		      McDArray<int> &oldTetras);

    /// Repair inverted tetra.
    int repairInverted(int iTet, HxMessage *hxMsg=NULL);

    HxTetraGrid* grid;
    HxGridVolume* gridVolume;

    int flagRecursiveSwapping;
    int flagSaveBoundaryTriangles;
    int flagInitializedEdgeConfigs;
    int theQualityMeasure;

    McDArray<unsigned char> markForFlip;

    // set of edge flip configurations
    McSmallArray< McSmallArray<EdgeFlipConfig,8> ,8> edgeFlipConfigs;
};

#endif

/// @}
