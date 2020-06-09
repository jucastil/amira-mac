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

/// @addtogroup hxwarp hxwarp
/// @{
#ifndef HX_TEST_H
#define HX_TEST_H

#include <hxwarp/HxWarpWinDLLApi.h>
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <mclib/McList.h>
#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortDoIt.h>
#include <hxfield/HxUniformLabelField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxsurface/HxSurface.h>
//#include <hxwarp/HxLandmarkSurfaceWarp.h>

#include <hxlandmark/HxLandmarkSet.h>



class HXWARP_API HxWarpSkin : public HxCompModule {

  HX_HEADER(HxWarpSkin);
public:
    
    class Voxel : public McLink
    {
    public:
      short position[3];
    
      Voxel() { }
      Voxel(int i,int j,int d) {
	position[0] = i;
	position[1] = j;
	position[2] = d;
      }
    };

    ///
  HxWarpSkin();

    ///
    ~HxWarpSkin();
  // HxPortMultiMenu portMethod;
	
  //	HxPortIntSlider portNumOfTimes;

    ///
  HxConnection portVoxelGrid1;
  HxConnection portVoxelGrid2;
  HxConnection portSurface1;   
    /** Do it button. */
    HxPortDoIt portAction;
    ///
  //void interpolate(float u, unsigned char* IDF);   
  /** Compute method. */
    virtual void compute();
    
protected:
    unsigned char* input;
       int width, height, depth;
    
//     short* distField1;
//     short* distField2;
    HxUniformScalarField3* dstFld;
   

    float largeDist;

  // int maxDist1, maxDist2;

  
    /// bounding boxes
    int box1[6];
    int box2[6];

  

    void initializeDistanceField(float* distField, int *dims,McList<Voxel>& list, unsigned char* input);
    /// list1 and list2 contain original contour of input1 and input2
    McList <Voxel> list1;
    McList <Voxel> list2;
  void propagateDistanceField(float* distField, int *dims, float* boundingBox, McList<Voxel>& list);
  void signedDistanceField(float* distField, int *dims, unsigned char* input);

  void distanceField(float* distField, int *dims, float* boundingBox, McList <Voxel>& list, unsigned char* input);
  void createLandmarks(HxSurface* input1warped,HxUniformScalarField3* dstFld,int step, HxLandmarkSet* output);

void prepareBookstWarpSurface( 
			      //HxSurface* input1warped,
			      HxLandmarkSet* landmarks, HxSurface* outSurface,McDArray<unsigned char>&  markPoints);
void createTransformations( HxSurface* input1warped,int& nLandmarks, int& createLandmarks,HxLandmarkSet* output, HxUniformScalarField3* dstFld, McDArray<unsigned char>& markPoints, int saveSubsteps = 0);

int mapTissue(int material,HxUniformLabelField3* vg, HxSurface* surf);
   
};
#endif

/// @}
