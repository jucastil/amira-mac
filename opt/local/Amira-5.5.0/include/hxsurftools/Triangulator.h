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
#ifndef TRIANGULATOR_H
#define TRIANGULATOR_H

#include <amiramesh/HxParamBundle.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>

class Surface;
class EdgeFlipper;


/// This is an internal class used by the GMC module.
class HXSURFTOOLS_API Triangulator {

  public:
    /// Initialize triangulator to work on a volume of given dimensions
    Triangulator(int nx, int ny, int nz, int zmin, Surface* result);

    /// Destructor.
    ~Triangulator();
    
    /** Returns true if initialization in the constructor failed,
        due to missing memory for pointsOnEdges or pointsOnFaces. */
    bool initFailed() const
    {
        return mInitFailed;
    }

    /** The Triangulator works layer by layer. Call this to switch to
        the next z-layer. @return New z-layer number.*/
    int nextLayer();

    /// Extract edge and face indices of lower border for identifying 
    /// duplicate points.
    void extractLower(McDArray<int> &markDuplicate, mculong idx);
    
    /// Extract edge and face indices of upper border for identifying 
    /// duplicate points.
    void extractUpper(McDArray<int> &markDuplicate, mculong idx);
    
    /** General triangulation method. Works by computing sub-voxels in
        a cell and simplifying the resulting sub-voxel faces. */
    void triangulate(int x, int y, int nMat, int* label,
		     int* prob, int* prob2, int tableInv[8]);

    /** General triangulation method. Same as before, with additional 
        parameters for referencing a smooth material. */
    void triangulate(int x, int y, int nMat, int* label, int const *smoothMatLbl,
		     int* prob, int* prob2, int tableInv[8], 
             int const smoothMat, int const *pSmooth, int const *qSmooth);

    /// Face shift strategies: 0=straight lines, 1=probabilities
    void setFaceShiftPolicy(int which);

    /// Set stiffness values.
    void setStiffness(HxParamBundle& materials);

    struct OffsetTableEntry {	
	int di, dj, dk, dd;
    };

	/*
	 * After changings at the surface, some arrays are no longer correct, so they have to
	 * change
	 */
	void updatePointsOnEdges(McDArray<int> &newPointIndex);
	
	/*
	 * After changings at the surface, some arrays are no longer correct, so they have to
	 * change
	 */
	void updatePointsOnFaces(McDArray<int> &newPointIndex);
	
  protected:
    static int edgeEnds[];
    static float faceCenters[18];
    static OffsetTableEntry edgeOffsetTable[];
    static OffsetTableEntry faceOffsetTable[];
    
    // Auxiliary struct used in TableEntry
    struct Patch {
	    int innerRegion;
	    int outerRegion;

	    int nTriangles;
	    int (*triangles)[3];

    };

    //struct TableEntry;
    //friend struct TableEntry;
    
    struct TableEntry {	
        int nPoints;
	    int nPatches;
	    int (*points)[3];
	    Patch* patches;

        //TableEntry() { }
        TableEntry(Surface* surf);
        TableEntry(TableEntry* other);
        ~TableEntry();
    };
    
    // part of fix for BZ 3602: 
    // Each triangulator uses its own lookup table.
    TableEntry* mLut[1458];

    McDArray<int> hiresData;
    McDArray<int> pointsOnEdges;
    McDArray<int> pointsOnFaces;
    McDArray<float> stiffness;

    bool mInitFailed;

    int currZ;
    int dims[2];
    int faceShiftPolicy;
    Surface *surface;

    int errorCount;
    int repairCount;
    int noRepairCount;
    
    struct Counter {
        int simple;
        int checkerBoard;
    };

    Counter counter[9];

    inline int edgeIndex(int i,int j,int edge) {
	int di = edgeOffsetTable[edge].di;
	int dj = edgeOffsetTable[edge].dj;
	int dk = edgeOffsetTable[edge].dk;
	int dd = edgeOffsetTable[edge].dd;	
	return ((dims[1]*dk+dj+j)*dims[0]+i+di)*3+dd;	
    }

    inline int faceIndex(int i,int j,int edge) {
	int di = faceOffsetTable[edge].di;
	int dj = faceOffsetTable[edge].dj;
	int dk = faceOffsetTable[edge].dk;
	int dd = faceOffsetTable[edge].dd;	
	return ((dims[1]*dk+dj+j)*dims[0]+i+di)*3+dd;	
    }
    
    /** This method creates a cell triangulation for a given configuration.
	@c label contains the vertex labels. @c p contains the weight for
	this primary label. @c q contains the weight for all other labels
	which potentially might occur at the vertex. The secondary weight
	must always be smaller than the primary one. The method works by
	subdividing the cell into subvoxels. The resulting subvoxel
	geometry is then simplified.

	A return value of 1 indicates that the triangulation can be
	inserted into the triangulators lookup table. The criterium for
	this are: no more than 3 different materials and no checkerboard
	configuration at any face.
    */
    int hiresCube(int nMat, int* label, int* p, int* q, Surface* result);

    /// Auxiliary method called from @c hiresCube()
    void insertSubFace(Surface *surf, int n, int *volume,
		       int pi, int pj, int pk, int di, int dj, int dk);

    /// Create cell triangulation from given table entry.
    void triangulate(int x, int y, TableEntry*,
        int* label, int const *smoothMatLbl, 
        int* prob, int* prob2, int tableInv[8],
        int const *pSmooth, int const *qSmooth, int const smoothMat);

    /// Shift points on edges (linear interpolation of probs)
    void edgeShift(int idx, int* prob, int* prob2, 
        int const *smoothMatLbl, int const *pSmooth, int const *qSmooth,
        McVec3f& p);

    /// Shift points on faces (move along straight lines)
    int faceShift1(int faceIdx, int eidx[12], int* label,
	           int* prob, int* prob2, 
               int const *smoothMatLbl, int const *pSmooth, int const *qSmooth,
               McVec3f& res);

    /// Shift points on faces (determine exact intersection point)
    int faceShift2(int faceIdx, int eidx[12], int* label,
		   int* prob, int* prob2, McVec3f& res);

    /// Shift points on faces (use stiffness information)
    int faceShift3(int faceIdx, int eidx[12], int* label,
                   int tableInv[8], McVec3f& res);

    /// Shift inner points (average coordinates of neighbouring points)
    void innerShift(int idx, int pidx[], TableEntry* entry, int const smoothMat, McVec3f& res);

    int pointIndex(const McVec3f& p);
    void writeLUT(const char* filename);
    void writeConfig(int* label, int* p, int* q);

    int repair(TableEntry* entry, int* pidx);
    int intersectionTest(TableEntry* entry, int* pidx, McDArray<int>&);

    McDArray<int> intersectingTriangles;
    McDArray<int> intersectingTriangles2;
    EdgeFlipper* edgeFlipper;
    
    int counterNewPoint;
};

#endif

/// @}
