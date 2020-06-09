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

/// @addtogroup hxlevelset hxlevelset
/// @{
#ifndef HxSDF_H
#define HxSDF_H


//#define DEBUG_PRINT

#ifdef linux
#  include <new>
#else
#  include <new.h>
#endif


#include <mclib/McPrimType.h>

#include <mclib/McFHeap.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxLattice3.h>
#include <mclib/McException.h>
#include "HxLevelSet.h"


class LevelsetException : McException
{};


inline double sqr(double a) {return a*a;}

inline double sqr(const McVec3f &v) {return sqr(v[0]) + sqr(v[1]) + sqr(v[2]);}

template<class Type>
inline Type  _min(Type a, Type b)
{ return (a<b ? a : b);}


template<class Type>
inline Type  _max(Type a, Type b)
{ return (a>b ? a : b);}



template<class Type>
inline void  _swap(Type &a, Type &b)
{Type c; c=a; a=b; b=c;}



class VoxelType : public  McFHeapElement
 { 

 public:  

     short x,y,z; 
     float time;

  VoxelType(int a, int b, int c, float t) {
    x = a;
    y = b;
    z = c;
    time= t;
  }

  int operator<(const VoxelType &v) { return (time <  v.time); }
 };


inline int fsign(float t) { return (t<0) ? -1 : 1; } 



class HxLevelset;

class HxSDF {
	
public:
	
	
	/// constructor
	HxSDF(const  McDArray<McVec3i> &seeds, HxUniformScalarField3* image);
	
	
	HxSDF(HxLevelset *levelset);
	
	~HxSDF();

	HxUniformScalarField3* getTimefield();
	
	
	/// compute all time stamps
	void startMarching(double stopTime);
	
	int computeSDF(double stopTime);
	
	void initFromSurface(const McDArray<McVec3i> &NarrowBand);
	
private:
	
	// return velocity for voxel i,j,k
	float velocity(int i, int j, int k) const;
	
	inline long  getIndex(int i, int j, int k) const;
	
	inline float getDist(int i, int j, int k) const;
	
	
	inline float   getDist(int i1, int j1, int k1, int i2, int j2, int k2) const;
	
	void getCoeff(long index0, long index1, long index2, float d0, float d1,  double &a, double &b, double &c) const;
	
	float solveEikonal(int i, int j, int k);
	
	
	void getDelta(int i, int j, int k, float* delta) const; 
	
	void getIndices(int index, int &x, int &y, int &z) const;
	
	// DATA
	
	McDArray<McVec3i> mSeeds; //!> seed points
	
	HxLattice3* mLattice; //!> image
	
	float* mTimeArray;  // pointer to coords in mTimefield
	
	float* mInitialFront; // for initialization from existing front
	
	VoxelType** mHeapElements;        //> pointer to element in heap
	
	McFHeap<VoxelType>  mHeap; //> heap for  dist values
	
	HxLevelset*  mLevelset;
	
	int mNx, mNy, mNz; // image dimensions
	
	mclong mNoVoxels; // no of voxels / image size
	
	int mFarLabel;  // label for far-away
		
    float mFinalTime;
    float mMarkerTime;
	float mGridSize;
	float mMaxVelo;
	float mDx, mDy, mDz;
	
};






inline long HxSDF::getIndex(int i, int j, int k) const
{ return (long) ( i + (mNx * ( j + ( mNy * k))) ) ;}




inline float  HxSDF::getDist(int i1, int j1, int k1, int i2, int j2, int k2) const
{
    McVec3f p1;
    McVec3f p2;
	
    mLattice->coords()->pos(i1,j1,k1, &p1.x); 
    mLattice->coords()->pos(i2,j2,k2, &p2.x);
    
    return (p1-p2).length();
}





#endif

/// @}
