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

/// @addtogroup hxdistmap hxdistmap
/// @{
#ifndef HX_NEIGHBOR_INDEXING3_H
#define HX_NEIGHBOR_INDEXING3_H

#include <assert.h>
#include <hxdistmap/HxDistmapWinDLLApi.h>
#include <mclib/McPrimType.h>

/// neighborhood models
typedef enum { N26, N18, N6 } HxNeighborhoodType3D;

/// neighbor types in 3D (neighbor-sharing-a-XXX)
typedef enum { VERTEX, EDGE, FACE } HxNeighborType26;

/// neighbor weights
typedef enum { W_CHAMFER=0, W_ONE, W_EUCLID, W_SCALED } HxNeighborWeightType;

/** HxIndexingInfo3 provides basic routines for efficient 3D/1D indexing, 
    neighbor indexing, and neighbor distance weighting.

    through the use of this class, different neighborhood and metric types
    can be used transparently in all algorithms.
    operations:

    
    @li nextNeighbor() can be called a number of times to get the indices 
        and voxel coordinates of all neighbors of a given voxel.
    @li nextInsideNeighbor() does the same, but only returns neighbors
        which are contained in the volume.
    

    These routines return the index of the desired neighbor as well
    as a floating point "weight" which gives the distance from the
    current voxel to the current neighbor according to the currently
    chosen metric type.
*/
class HXDISTMAP_API HxNeighborIndexing3
{
public:
    // constructor sets class variables
    HxNeighborIndexing3(const mculong *dims, 
		    HxNeighborhoodType3D nhtype,
		    HxNeighborWeightType wtype,
		    float *voxelExtents = NULL);

    // compute 1D from 3D index (32 bit)
    inline int index1DInt(int x,int y,int z) const;

    // compute 1D from 3D index (64 bit)
    inline mclong index1DLong(int x,int y,int z) const;

    /// compute 3D from 1D index (32 bit)
    inline void index3DInt(int xyz, int&x, int&y, int& z) const;

    /// compute 3D from 1D index (64 bit)
    inline void index3DLong(mclong xyz, int&x, int&y, int& z) const;

    /// chose among different neighborhood types
    void setNeighborhood(HxNeighborhoodType3D nhtype);

    /// query neighborhood type
    inline HxNeighborhoodType3D neighborhoodType() const { return neiType; }

    /** get x,y,z,index of the (first/) next neighbor (32 bit). 
	
	@li returns 1 on success or 0 if there's no more valid neighbor
	@li to get the first neighbor, use next_number = 0
	@li x,y,z,index is the center voxel's data (input)
	@li xn,yn,zn,indexn is the neighbor's data (in/out)
	@li weight is the distance weight from (x,y,z) to (xn,yn,zn)
	@li next_number, xn, yn, zn, and indexn must always be passed from
            one call to the next one by the caller 
	 */
    inline 
    int nextNeighborInt(int& next_number,
		      int x,int y,int z, int index,
		      int& xn, int& yn, int& zn, int& indexn,
		      int& inside, float& weight) const;

    /** get x,y,z,index of the (first/) next neighbor (64 bit). */
    inline 
    int nextNeighborLong(int& next_number,
		      int x,int y,int z, mclong index,
		      int& xn, int& yn, int& zn, mclong& indexn,
		      int& inside, float& weight) const;

    /// the same as nextNeighbor, but skips neighbors outside the field (32 bit)
    inline 
    int nextInsideNeighborInt(int& next_number,
			    int x,int y,int z, int index,
			    int& xn, int& yn, int& zn, int& indexn,
			    float &weight) const;

    /// the same as nextNeighbor, but skips neighbors outside the field (64 bit)
    inline 
    int nextInsideNeighborLong(int& next_number,
			    int x,int y,int z, mclong index,
			    int& xn, int& yn, int& zn, mclong& indexn,
			    float &weight) const;

    /// compat, maps to 32 bit version
    inline int index1D(int x,int y,int z) const {
        return index1DInt (x, y, z);
    }

    /// compat, maps to 32 bit version
    inline void index3D(int xyz, int&x, int&y, int& z) const {
        index3DInt (xyz, x, y, z);
    }

    /// compat, maps to 32 bit version
    inline 
    int nextNeighbor(int& next_number,
		      int x,int y,int z, int index,
		      int& xn, int& yn, int& zn, int& indexn,
		      int& inside, float& weight) const {
         return nextNeighborInt (next_number, x, y, z, index, xn, yn, zn, indexn, inside, weight);
    }

    /// compat, maps to 32 bit version
    inline 
    int nextInsideNeighbor(int& next_number,
			    int x,int y,int z, int index,
			    int& xn, int& yn, int& zn, int& indexn,
			    float &weight) const {
        return nextInsideNeighborInt (next_number, x, y, z, index, xn, yn, zn, indexn, weight);
    }

    /** chose a set of weights; for W_SCALED you must specify the 
	voxel extents as an array of three floats or NULL to let the
        extents remain as they are */
    void setWeights(HxNeighborWeightType wtype, 
		    float* voxelExtents = NULL);

    /// query minimum of currently chosen weights
    inline float minWeight() const { return minweight; }

    /// query extents of voxel
    inline float voxelSize(int i) const { assert(i>=0 && i<3); 
                                          return voxelExtents[i]; }

    /// query weights type
    inline HxNeighborWeightType weightsType() const { return weiType; }

    /// query dimensions
    inline mculong xDim()   const { return dim[0]; }
    inline mculong yDim()   const { return dim[1]; }
    inline mculong zDim()   const { return dim[2]; }
    inline mculong yxDim()  const { return yxdim; }
    inline mculong zyxDim() const { return zyxdim; }

protected:

    // init weights using voxel edge sizes
    void initWeights(float *voxelExtents = NULL);

    // consistency check (debugging)
    int checkShiftConsistency();

    // output weights to stderr
    void outputWeights();

    // all the dimensions you might need ;-)
    mclong zyxdim;
    mculong  yxdim, xdim, dim[3];

    // copy voxel extents in the case you need them
    float voxelExtents[3];

    // how to shift from a) the center voxel to the first neighbor
    //                   b) a neighbor to the next one
    int shift26[26], shift18[18], shift6[6], *shift;

    // how to compute the neighbor's x/y/z values from the center's
    int xshift26[26],yshift26[26],zshift26[26],
	xshift18[18],yshift18[18],zshift18[18],
	xshift6[6],yshift6[6],zshift6[6], *xshift, *yshift, *zshift;

    // how many neighbors?
    int numNeighbors;

    // weight sets and minimal weights
    float w_eucl26[26], w_eucl18[18], w_eucl6[6], min_eucl;
    float w_chamfer26[26], w_chamfer18[18], w_chamfer6[6], min_chamfer;
    float w_one26[26], w_one18[18], w_one6[6], min_one;
    float w_scaled26[26], w_scaled18[18], w_scaled6[6], min_scaled;

    // currently chosen weights/minweight/number of neighbors
    float *weight, minweight;

    // current neighbor/weight types
    HxNeighborhoodType3D neiType;
    HxNeighborWeightType weiType;

    // neighbors can be face, edge, or vertex neighbors
    static HxNeighborType26 ntype[26];
};


// inlines must be included here ;-(

// compute 1D index from 3D index
inline 
int 
HxNeighborIndexing3::index1DInt(int x,int y,int z) const
{
    // our method: x changes fastest
    return z*yxdim + y*xdim + x;
}

inline 
mclong 
HxNeighborIndexing3::index1DLong(int x,int y,int z) const
{
    // our method: x changes fastest
    return mclong(z)*mclong(yxdim) + mclong(y)*mclong(xdim) + mclong(x);
}

// compute 3D from 1D index
inline 
void
HxNeighborIndexing3::index3DInt(int xyz, int& x, int& y, int& z) const
{
  int tmp = xyz;

  // inverse to index1D
  z = tmp / yxdim; tmp -= z*yxdim;
  y = tmp / xdim;  
  x = tmp - y*xdim;
  
  // debugging!
  assert(index1DInt(x,y,z) == xyz);
}

inline 
void
HxNeighborIndexing3::index3DLong(mclong xyz, int& x, int& y, int& z) const
{
  mclong tmp = xyz;

  // inverse to index1D
  z = int(tmp / mclong(yxdim)); tmp -= mclong(z) * mclong(yxdim);
  y = int(tmp / xdim);  
  x = int(tmp - y*xdim);
  
  // debugging!
  assert(index1DLong(x,y,z) == xyz);
}
/* 
   (efficient?) neighbor access.
    input: - next_number=0 at the beginning; 
           - x/y/z/index of the voxel whose neighbors are wanted
	   - (initially uninitialized) x/y/z/index values for the neighbor
    output: - new next_number (must be passed again with the succeeding call)
            - new x/y/z/index of neighbor (must also be passed in next call)
	    - inside=1 if the neighbor is inside the field, 0 if outside
            - returns 1 on success, 0 if there are no more (valid) neighbors
*/            

inline 
int 
HxNeighborIndexing3::nextNeighborInt(int &next_number,
			       int x,int y,int z, int index,
			       int& xn, int& yn, int& zn, int& indexn,
			       int& inside, float& weight) const
{
    // next_number must be initialized with 0 and should then only changed
    //   (incremented) by this method
    assert(next_number>=0 && next_number<=numNeighbors);

    // EON -- end of neighbors
    if(next_number >= numNeighbors)
      return 0;

    // init values for xn/yn/zn/indexn for the first neighbor
    if(next_number == 0) {
      xn=x; yn=y; zn=z; 
      indexn=index;
    }

    // shift once, don't care about neighbors at the outside
    xn     += xshift[next_number];
    yn     += yshift[next_number];
    zn     += zshift[next_number];
    indexn += shift[next_number];
    weight  = this->weight[next_number];
    next_number++;
    inside = (xn>=0 && yn>=0 && zn>=0 && xn<(int)xDim() && yn<(int)yDim() && zn<(int)zDim());

    return 1;
}

inline 
int 
HxNeighborIndexing3::nextNeighborLong(int &next_number,
			       int x,int y,int z, mclong index,
			       int& xn, int& yn, int& zn, mclong& indexn,
			       int& inside, float& weight) const
{
    // next_number must be initialized with 0 and should then only changed
    //   (incremented) by this method
    assert(next_number>=0 && next_number<=numNeighbors);

    // EON -- end of neighbors
    if(next_number >= numNeighbors)
      return 0;

    // init values for xn/yn/zn/indexn for the first neighbor
    if(next_number == 0) {
      xn=x; yn=y; zn=z; 
      indexn=index;
    }

    // shift once, don't care about neighbors at the outside
    xn     += xshift[next_number];
    yn     += yshift[next_number];
    zn     += zshift[next_number];
    indexn += mclong(shift[next_number]);
    weight  = this->weight[next_number];
    next_number++;
    inside = (xn>=0 && yn>=0 && zn>=0 && xn<(int)xDim() && yn<(int)yDim() && zn<(int)zDim());

    return 1;
}

inline 
int 
HxNeighborIndexing3::nextInsideNeighborInt(int &next_number,
				     int x,int y,int z, int index,
				     int& xn, int& yn, int& zn, int& indexn,
				     float& weight) const
{
    // next_number must be initialized with 0 and should then only changed
    //   (incremented) by this method
    assert(next_number>=0 && next_number<=numNeighbors);

    // EON -- end of neighbors
    if(next_number >= numNeighbors)
      return 0;

    // init values for xn/yn/zn/indexn for the first neighbor
    if(next_number == 0) {
      xn=x; yn=y; zn=z; 
      indexn=index;
    }

    int outside;
    // shift the indices until a valid (inside) neighbor is reached
    do {
	xn     += xshift[next_number];
	yn     += yshift[next_number];
	zn     += zshift[next_number];
	indexn += shift[next_number];
	weight  = this->weight[next_number];
	next_number++;
	outside = (xn<0 || yn<0 || zn<0 || 
	    xn>=(int)xDim() || yn>=(int)yDim() || zn>=(int)zDim());
    } while(outside && next_number<numNeighbors);
    // 1. bugfix: replaced < with <=
    // 2. bugfix: if !outside added
    if (next_number<=numNeighbors && !outside)
	return 1;
    else 
	return 0;
}

inline 
int 
HxNeighborIndexing3::nextInsideNeighborLong(int &next_number,
				     int x,int y,int z, mclong index,
				     int& xn, int& yn, int& zn, mclong& indexn,
				     float& weight) const
{
    // next_number must be initialized with 0 and should then only changed
    //   (incremented) by this method
    assert(next_number>=0 && next_number<=numNeighbors);

    // EON -- end of neighbors
    if(next_number >= numNeighbors)
      return 0;

    // init values for xn/yn/zn/indexn for the first neighbor
    if(next_number == 0) {
      xn=x; yn=y; zn=z; 
      indexn=index;
    }

    int outside;
    // shift the indices until a valid (inside) neighbor is reached
    do {
	xn     += xshift[next_number];
	yn     += yshift[next_number];
	zn     += zshift[next_number];
	indexn += mclong(shift[next_number]);
	weight  = this->weight[next_number];
	next_number++;
	outside = (xn<0 || yn<0 || zn<0 || 
	    xn>=(int)xDim() || yn>=(int)yDim() || zn>=(int)zDim());
    } while(outside && next_number<numNeighbors);
    // 1. bugfix: replaced < with <=
    // 2. bugfix: if !outside added
    if (next_number<=numNeighbors && !outside)
	return 1;
    else 
	return 0;
}


#endif 

/// @}
