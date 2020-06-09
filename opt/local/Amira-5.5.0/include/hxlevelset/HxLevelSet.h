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
#ifndef HXLEVELSET_H
#define HXLEVELSET_H


#include <mclib/McRawData3D.h>
#include <mclib/McPrimType.h>

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <hxfield/HxUniformScalarField3.h>


#include "levelsetAPI.h"
#include "HxSDF.h"


typedef void (*RedrawFunction)(void* userData,HxLattice3 *&lattice, unsigned char *&selection);

class HxSDF;

typedef enum {outside, inside, mine} Markers;

class HXLEVELSET_API  HxLevelset 
{ // start class HxLevelset
	
    friend class HxSDF;
	
public:
	
   
    HxLevelset(HxUniformScalarField3* image, HxUniformScalarField3* initialFront,
	       const  McDArray<float> &parameters,  unsigned char* result=0);
		
   
    /// constructor for use in Gi
    HxLevelset(HxLattice3* lattice, McRawData3D* image, float* initialFront, 
	       const McDArray<float> &parameters,  unsigned char* result=0 );
	
    ~HxLevelset();
  
    void propagateFront(double finalTime, void* redrawData=0, RedrawFunction  redraw=0);
	
    void setBandWidth(float bw);
    
	
private:
	
    /// the edge filter function
    inline float g(float v) const ; 

    // return velocity for voxel i,j,k
    inline float velocity(int i, int j, int k);
	
    float getCurvature(int i, int j, int k);

    McVec3f getImageGradient(int i, int j, int k);
	
    int  doStep();
	
    float solveVoxel(int x, int y, int z);
    
    void reInit();
	
    inline bool valid(int i, int j, int k) const;
	
    double getCoeff(long index0, long index1, long index2, 
		    float d0, float d1, int orientation) const;
	
	
    void getDelta(int i, int j, int k, float* delta) const;
	
    inline long getIndex(int i, int j, int k) const;
	
	
    inline double  getDerivX(int i, int j, int k);
	
    inline double  getDerivY(int i, int j, int k);
	
    inline double  getDerivZ(int i, int j, int k);
	
    void smoothNarrowBand();
	
    // DATA
	
    int mNx, mNy, mNz; // image dimensions
	
    float mDx, mDy, mDz; // grid spacing
	
    double mDt; // time step
	
    int mElSize; // size of data el (only byte/short)

    mclong mNoVoxels; // no of voxels / image size
	
    float mBandWidth;
    
    int mFarLabel;
	
    int mStartVoxel; 
	
    float mMaxVelo;
    float mGridLength;
	
    float mEpsilon;  //!> weight for curvature term
    float mGradientWeight; //!> weight for gradient term
    float mAttractorWeight; //!> weight for active attraction

    int mDerivOk;
	
    McDArray<McVec3i> mNarrowBand; //!> indices of voxels in narrow band  
  
    HxLattice3* mLattice; //!> lattice for all data
	
    McRawData3D* mImage; //!> image
    unsigned char* mResult; //!> selection
  
	
    float* mField1;
    float* mField2;
    float* mInputField;  ///> used in destructor
  
    McDArray<Markers> mMarkers;
	
    HxSDF *mFastMarching;
	
public:
	
    HxUniformScalarField3* getField();
	
	
    HxUniformScalarField3* getVeloField();
};


inline long HxLevelset::getIndex(int i, int j, int k) const
{ return (long) ( i + (mNx * ( j + ( mNy * k))) ) ;}


inline bool HxLevelset::valid(int i, int j, int k) const
{
    return (i>=0 && j>=0 && k>=0  && i<mNx && j<mNy && k<mNz &&  mField1[getIndex(i,j,k)] != mFarLabel);
}





#endif

/// @}
