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

/// @addtogroup hxgridgen hxgridgen
/// @{
#ifndef HX_TETRA_GEN2_H
#define HX_TETRA_GEN2_H

#include <hxgridgen/HxGridGenWinDLLApi.h>

#include <mclib/McFHeap.h>
#include <mclib/McFilename.h>
#include <mclib/McTmpDir.h> 
#include <mclib/McProgressInterface.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxMatDatabase.h>
#include <hxcore/HxParamDialog.h>
#include <hxsurface/HxSurface.h>
#include <hxfield/HxTetraGrid.h>
#include <hxsurface/FaceOctree.h>
#include <hxstatistics/HxSpreadSheet.h>

/// Tetrahedral grid generation program.
class HXGRIDGEN_API HxTetraGen2 : public HxCompModule {

  HX_HEADER(HxTetraGen2);
  
  public:
    /// Constructor.
    HxTetraGen2();

    /// Update method shows and hides some ports.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Name of region for which a grid should be generated (0=all).
    HxPortMultiMenu portMaterial;

    /// Options: 0=post-processing improve grid, 1=save grid
    HxPortToggleList portOptions;
    enum { OPT_IMPROVE=0, OPT_SAVE=1 };

    /// Name of resulting tetrahedral grid.
    HxPortFilename portGridFile;

    /// Action: 0=edit materials, 1=check, 2=run now, 3=run batch.
    HxPortButtonList portAction;
    enum HxTetraGen_Action { ACT_MESHSIZE=0, ACT_CHECK=1, ACT_NOW=2, ACT_BATCH=3 };

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Set the epsilon value for the difference check between the volume estimated with
        the aid of the triangle surface and the volume calculated by summation of each
        tetrahedron volume. Practice has shown that values greater than 10e-10 are 
        inaccurate to detect a volume difference for large tetrahedron meshes with varying 
        element sizes. */
    void setVolumeEps(const double eps) {
        if ( eps > 0.0 ) {
            m_volumeEps = eps;
        }
    }

    void setMeshSize(int matId, double meshSize);

    void setUpperBoundDiamRatio(const float ratio) {
        if ( ratio < 3.0f ) { 
            // smallest possible diameter ratio value is 3
            upperBoundDiamRatio = 3.0f;
            return;
        }
        upperBoundDiamRatio = ratio;
    }

  protected:
    ~HxTetraGen2();

    // This struct represents a triangle of the generation front
    // which can be inserted in a McFHeap.
    struct GFTriangle : public McFHeapElement {

	int numTri;		// number of triangle in triangle list
				// of grid
	int oppositeVertex;     // number of opposite vertex
	float priority;		// max edge length or -cos(angleNeighbour)

	int operator < (const GFTriangle& other) {
	    return priority < other.priority;
	}
    };

    struct elemHistory {
	int nRemovedTet;
	int starShaped;
	float maxDiamRatio;
	float meanDiamRatio;
	McVec3f starCenter;
    };

    HxTetraGrid*  grid;
    HxSurface*    inputSurface;
    HxSurface*	  genFront;
    HxParamBundle materials;
    HxParamDialog* meshsizeEditor;

    // result of check
    HxSpreadSheet *mSpreadSheet;
    int mNumRowsSpreadSheet;

    bool mCheckedSettings;

    McDArray<int> renumVertices;

    FaceOctree<HxTetraGrid> octree;
    FaceOctree<HxSurface>   octree2;

    McDArray< McSmallArray<int,3> > trianglesPerEdge;
    McDArray< McSmallArray<int,6> > edgesPerPoint;

    // All triangles of the generation front are inserted into this heap
    McFHeap<GFTriangle> triangleHeap;

    // Array of all triangles of the generation front
    McDArray<GFTriangle> allTriangles;

    int actualMaxSizeAllTriangles;
    int stepSizeAllTriangles;

    // actual number of faces of the generation front
    int nFacesGF;
    // actual number of faces skipped
    int nFacesSkipped;

    // parameters controlled by parse commands
    int isBatch;
    int savePartialGrid;
    int skipPostProc;

    // parameters of advancing front method
    int selectPriority;
    int finishAnyway;
    int nNextVert;       // max. length of list nextVertices
    float lowerBoundDihedAngle;
    float upperBoundNeighbourAngle;
    float lowerBoundAngleAtEdge;
    float lowerBoundAngleOneTetra;
    float upperBoundDiamRatio;
    float smallUpperBoundDiamRatio;
    float factLongEdge;
    float epsNodeTest;
    float epsInt;
    float par1EdgeTest;
    float par2EdgeTest;
    float sqPar1EdgeTest;
    float sqPar2EdgeTest;

    float minEdgeLenStart;
    float maxEdgeLenStart;
    float meanEdgeLenStart;
    float penalty;
    float meshSizeRegion;
    float maxEdgeLenRegion;
    float bBoxStart[6];

    float anglesAtEdges[3];

    double volumeOfRegion;
    float  sumTetraVol;

    float holeVolume;

    int nTetraStart;
    int nTetEstimated;
    int nTetMax;
    int basicTriangle;
    int nWarningHeight;

    int newTriangles[3];
    int newEdges[3];

    int radiatingMesh;
    int warningRad;
    int avoidNewVertex;

    float diamRatio10;
    /* allowed difference between the volume estimated with the aid of the triangle surface
       and the volume calculated by summation of each tetrahedron volume */
    double m_volumeEps;

    // for collectVerticesOfTriangles:
    McDArray<int> nextCollectedVertex;
    int firstCollectedVertex;
    int lastCollectedVertex;

    // for collectEdgesOfTriangles:
    McDArray<int> nextCollectedEdge;
    int firstCollectedEdge;
    int lastCollectedEdge;

    McDArray<int> triListPostProc;
    McDArray < McSmallArray<int,4> > listOfTriLists;
    int nWarningsPostProc;

    FILE* fp;

    void run(HxTetraGen_Action action);
    void setResultName();
    void editMaterials();

    //----------------------------------------------------------
    //  Pre-processing
    //----------------------------------------------------------

    /// Create generation front.
    void createGenFront(const char* name, int iRegion,
                        HxTetraGen_Action action);

    /// Check generation front.
    int checkGenFront(const char* name, int iRegion,
                      HxTetraGen_Action action);

    /// Check if generation front is closed.
    int checkClosedness();

    /// Check intersections.
    int checkIntersections(HxTetraGen_Action action);

    /// Check orientation.
    int checkOrientation(HxTetraGen_Action action);

    /// Calculate priority for triangle iTri.
    void calcPriority(int iTri);

    /// Change priority in case of small dihed angles.
    void penalizeSmallDihedAngles();

    /// Sort generation front.
    void sortGenFront();

    /// Pre-processing.
    int preProcess(const char* name, int iRegion, 
                   HxTetraGen_Action action);

    //----------------------------------------------------------
    //  advancing front method: advancingFront3D.cc
    //----------------------------------------------------------

    /// Enlarge bounding box by eps.
    void enlargeBoundingBox(float bb[6]);

    /// Find intersections of gf elements with line.
    void findIntersectLine(McDArray<int> &nearbyTriangles, 
			   McVec3f &xStart, McVec3f &xEnd,
			   int neighbours[4], float &lambdaMin);

    /// Find triangles adjacent to basic triangle.
    int findAdjacentTriangles(McVec3f &normal,
			      int neighbours[4], 
			      float anglesNeigh[3]);

    /// compute optimal height of tetrahedron.
    float getHeight(McVec3f &location,
		    const float meshSize,
		    const float meanEdgeLen);

    /// Find best vertex location considering neighbours.
    void findBestLocation(int neighbours[4], 
			  float anglesNeigh[3],
		     	  const float maxDist,
			  const float meanEdgeLen,
			  McVec3f &center,
			  McVec3f &normal,
			  McVec3f &location,
			  const int nVertices);

    /// Find best location for new vertex.
    void findBestNewLocation(const int nVertices,
			     const float meanEdgeLen,
			     McVec3f &center,
			     McVec3f &normal,
			     McVec3f &bestNew);

    /// Collect vertices of triangles given in triList.
    void collectVerticesOfTriangles(
		      McDArray<int> &triList,
		      McDArray<int> &vertList);

    /// Check if vertex iVert leads to long edges (1=true).
    int checkLongEdge(const int iVert);

    /// Find vertices of nearbyTriangles next to location
    void findNextVertices(McVec3f &normal, 
	                  McVec3f &location, 
	                  McDArray<int> &nearbyTriangles,
		     	  McDArray<int> &nextVertices);
 
    /// Update nearbyTriangles if bounding box has been enlarged.
    void checkBoundBox(float newBB[6], float oldBB[6],
		       McDArray<int> &nearbyTriangles);

    /// Select triangles with bounding boxes overlapping bb.
    void selectOverlap(float bb[6], const int vertNumb,
		       const int newVertex,
		       McDArray<int> &nearbyTriangles,
		       McDArray<int> &selectedTriangles);

    /// Check distance of location to midpoints of neighbouring triangles.
    int testDistToMidpoints(McVec3f &location,
			    int neighbours[4],
			    McDArray<int> &selectedTriangles);

    /// Find intersections of gf elements with line parallel to x-axis.
    int findIntersectLineX(McVec3f &location,
			   McDArray<int> &triList,
			   McDArray<float> &xCoords);

    /// Check if location is included by GF (1=inside).
    int testVertexInsideGF(McVec3f &location);

    /// Get new vertex from list nextVertices.
    int getNewNextVertex(McDArray<int> &history,
			 McDArray<int> &nextVertices);

    /// Check if one of nearby vertices is inside tetra.
    int vertexInsideTetra(int vertNumb,
			  McDArray<int> &nearbyVertices,
			  McDArray<int> &nextVertices);

    /// Collect edges of triangles given in triList.
    void collectEdgesOfTriangles(McDArray<int> &triList, 
			    	 McDArray<int> &edgeList);

    /// Which of the faces and edges are new?
    int findNewTriangles(const int vertNumb,
			 const int newVertex,
                         const int flagNewEdges=0);

    /// Test angle at edge.
    int testAngleAtEdge(const int vertNumb,
			const int jTri,
			int neighbours[4],
			McVec3f &normal,
			McDArray<int> &history,
			McDArray<int> &nextVertices);

    /// Handle intersection: search vertex next to center.
    int handleIntersection(int* idxOld, int nOld,
			   int* idx,
			   McDArray<int> &history,
			   McDArray<int> &nextVertices,
			   McVec3f& center,
			   McVec3f& normal);

    /// Test intersection of new edge with triangles of GF.
    int findIntersections2(const int simpleTest,
			   const int vertNumb,
			   const int jEdge,
			   McVec3f& center,
			   McVec3f& normal,
			   McDArray<int> &nearbyTriangles,
			   McDArray<int> &history,
			   McDArray<int> &nextVertices);

    /// Test distance of new edge to vertices and other edges.
    int edgeTest(int jEdge, 
		 const int vertNumb,
		 const int newVertex,
		 int neighbours[4],
		 McDArray<int> &nearbyVertices,
		 McDArray<int> &nearbyEdges);

    /// Check triangle intersections.
    int findIntersections(const int simpleTest,
			  const int vertNumb,
			  const int newVertex,
			  McVec3f& center,
			  McVec3f& normal,
			  McDArray<int> &nearbyTriangles, 
			  McDArray<int> &nearbyVertices, 
			  McDArray<int> &nearbyEdges,
			  McDArray<int> &history,
			  McDArray<int> &nextVertices,
			  int neighbours[4]);

    /// Find 4th vertex.
    int find4thVertex(const int simpleTest,
		      McDArray<int> &triList,
		      int &newVertex, int &vertNumb,
		      int neighbours[4], McVec3f& location,
		      McVec3f& normal);

    /// Update vertex list.
    void updateVertexList(int &vertNumb, McVec3f& location);

    /// Update tetra list.
    void updateTetraList(int vertNumb);

    /// Mark small angles.
    void markSmallAngles(const int vertNumb, 
			 const int newVertex,
			 int neighbours[4], 
			 McVec3f &normal, 
			 float cosAngles[3],
			 int oppositeVertices[3]);

    /// Clear triangleHeap.
    void clearHeap(McDArray<unsigned char> &markTriangles);

    /// Fill triangleHeap again.
    void fillHeapAgain(McDArray<unsigned char> &markTriangles);

    /// Update generation front.
    void updateGF(const int vertNumb, 
		  const int newVertex,
		  int neighbours[4], 
		  McVec3f &normal);

    /// Advancing front algorithm.
    void advancingFront(const char* name, 
			McProgressInterface* progress=0);

    //----------------------------------------------------------
    //  Post-processing: postProcTetGen.cc
    //----------------------------------------------------------

    /// Find connected parts of generation front.
    int findConnectedParts(McProgressInterface* progInterf=0);

    /// Create edge list for triangles of triList.
    void createEdgesPart(McDArray<int> &triList);

    /// Test if connected part can be filled by one tetrahedron.
    int fillByOneTetra(const int iPart);

    /// Examine if 'hole' is star-shaped.
    int testIfStarShaped(const int iPart,
			 McDArray<int> &triList,
			 McDArray<int> &invertedTriangles,
			 float &maxDiamRatio,
			 float &meanDiamRatio,
			 McVec3f &starCenter,
			 float &volume);

    /// Test if tetrahedron can be removed (should always be true).
    int testRemoveTetra(const int iTet);

    /// Flip triangle.
    void flipTriangle(const int iTri);

    /// Remove Tetrahedron.
    void removeTetrahedron(const int iTet,
			   const int iPart,
			   McDArray<int> &triList);

    /// Find most concave edge of 'hole'.
    void findMostConcaveEdge(McDArray<int> &triList, 
			     float &maxAngle,
			     int trianglesAtMaxAngle[2]);

    /// Fill star shaped 'hole'.
    int fillStarShapedGF(const int iPart,
			 McDArray<int> &triList,
			 McVec3f &starCenter);

    /// Restore tetrahedron.
    void restoreTetrahedron(const int iTet,
			    const int iPart,
			    McDArray<int> &triList);

    /// Create tetrahedron, update triList.
    void createTetra(int vertnumb, const int newVertex, 
		     McVec3f &location,
		     const int iPart, McDArray<int> &triList);

    void writePartSurface(McDArray<int> &triList);

    /// Simple version of advancing front method;
    int simpleAdvancingFront(const int iPart,
                             bool limitTrilistSize,
			     McDArray<int> &triList,
			     float &maxDiamRatioAdv,
			     float &meanDiamRatioAdv,
			     int   &nTetAdv);

    /// Examine if a 'bad' tetra is induced by surface triangles.
    int findTetInducedBySurf(const int iPart,
			     const int starShaped,
			     const float maxDiamRatio,
			     McDArray<int> &triList,
			     int &change);

    /// Clear edges of connected part.
    void clearEdgesPart();

    /// Clear boundaryConditionId for part iPart.
    void clearBoundCondID(const int iPart,
			  McDArray<int> &triList);

    /// Fill connected part of generation front.
    int fillConnectedPart(const int iPart);

    /// Fill holes.
    int fillHoles(McProgressInterface* progInterf=0);

    /// Post-processing.
    int postProcess(McProgressInterface* progInterf=0);

    //----------------------------------------------------------
    //  vertex smoothing: vertexSmoothing.cc
    //----------------------------------------------------------

    /// Calculate mean local edge length.
    float calcMeanLocalEdgeLength(McDArray<int>& tetraList);
	
    /// Calculate minimal determinant.
    float calcMinDet(McDArray<int>& tetraList,
		     McDArray<int>& iTetWorst);

    /// Calculate maximal diam ratio.
    float calcMaxDiamRatio(McDArray<int>& tetraList,
			   McDArray<int>& iTetWorst,
			   float &meanDiamRatio);

    /// Calculate worst quality (min det or max diam ratio).
    float calcWorstQuality(McDArray<int>& tetraList,
			   McDArray<int>& iTetWorst,
			   int qualityMeasure,
			   float &meanQuality);

    /// Optimization smoothing.
    int optimizationSmoothing(int iVertex, 
			      McDArray<int>& tetraList,
			      int qualityMeasure,
			      int &starShaped,
			      float &optimizedQuality,
			      float &meanQuality);

    //----------------------------------------------------------
    //  Post-post-processing
    //----------------------------------------------------------
    /// Copy boundary condition ids from surface to grid.
    void getBoundCondFromSurface();

    /// Check tetra intersections.
    void checkTetraIntersections();

    /// Simple tetgen for star-shaped regions.
    void simpleTetgen();

    void submitBatchJob();
};

#endif

/// @}
