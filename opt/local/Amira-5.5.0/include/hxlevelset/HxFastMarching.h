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
#ifndef FASTMARCHING_H
#define FASTMARCHING_H

#include <mclib/McPrimType.h>

#include <mclib/McFHeap.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <hxfield/HxUniformScalarField3.h>

#include "HxSDF.h"



class  HXLEVELSET_API  FastMarching {
	
public:
	
	/// constructor
	FastMarching(const  McDArray<McVec3i> &seeds, HxUniformScalarField3* gradientImage,  HxUniformScalarField3* greyImage,
		const McDArray<float> &parameters);
	
	HxUniformScalarField3* getTimefield();
	
	
	/// compute all time stamps
	void startMarching(double stopTime, McFHeap<VoxelType> *heap=0);
	
	
private:
	
	
	inline float g1(float v) const; //!> edge detection function
	
	inline float g2(float v) const; //!> intensity function
	
	// return velocity for voxel i,j,k
	inline float velocity(int i, int j, int k) const;
	
	inline long  getIndex(int i, int j, int k) const;
	
	inline bool  closeBoundary(int x, int y, int z) const;
	
	inline float getDist(int i, int j, int k) const;
	
	
	inline float   getDist(int i1, int j1, int k1, int i2, int j2, int k2) const;
	
	void getCoeff(long index0, long index1, long index2, 
		float d0, float d1,  double &a, double &b, double &c) const;
	
	float solveEikonal(int i, int j, int k);
	
	
	void getDelta(int i, int j, int k, float* delta) const; 
	
	void getIndices(int index, int &x, int &y, int &z) const;
	
	// DATA
	
	McDArray<McVec3i> mSeeds; //!> seed points
	
	HxUniformScalarField3* mGradientImage; //!> image
	
	HxUniformScalarField3* mGreyImage; //!> image
	
	HxUniformScalarField3* mTimefield; //!> field to hold time stamps
	
	float* mTimeArray;  // pointer to coords in mTimefield
	
	McFHeap<VoxelType>  mHeap;
	
	//  QIntDict alive, narrow, faraway;
	
	int mNx, mNy, mNz; // image dimensions
	
	float mDx, mDy, mDz; // grid sizes for uniform coords
	
	long mNoVoxels; // no of voxels / image size
	
	int mFarLabel;  // label for far-away
	
	float mSigma, mMeanGreyValue; 
	float mGradientValue; ///>  stopping parameter
};






inline long FastMarching::getIndex(int i, int j, int k) const
{ return (long) ( i + (mNx * ( j + ( mNy * k))) ) ;}

inline bool  FastMarching::closeBoundary(int x, int y, int z) const
{
	return (x <=1 || y <= 1 || z <=1 || x >= mNx-2 || y >= mNy-2 || z >= mNz-2);
}


inline float  FastMarching::getDist(int i1, int j1, int k1, int i2, int j2, int k2) const
{
	McVec3f p1, p2;
	mGradientImage->lattice.coords()->pos(i1,j1,k1, &p1.x);
	
	mGradientImage->lattice.coords()->pos(i2,j2,k2, &p2.x);
	
	return (p1-p2).length();
}


#endif

/// @}
