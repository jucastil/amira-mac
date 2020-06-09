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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef CHAMFERCALC_H
#define CHAMFERCALC_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortOptionMenu.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>

#include <hxfield/HxUniformScalarField3.h>
#include <hxskeleton/HxSkeletonWinDLLApi.h>

class HXSKELETON_API ChamferCalc : public HxCompModule 
{
  HX_HEADER(ChamferCalc);

public :
  ChamferCalc();
  ~ChamferCalc();

  //  HxPortFloatTextN portVoxelSize;
  HxPortRadioBox   portMaskDim;
  HxPortRadioBox   portMaskSize;
  HxPortOptionMenu portMapLocation;
  HxPortToggleList portExactMap;
  HxPortDoIt       portAction;

  virtual void compute();
  virtual void update();


  /** Computes a chamfer map of the image src
      @param src      : HxUniformScalarField3 binary image ( > 0 => foreground, <= 0 => background)
      @param location : 0 -> chamfer map of the background
      1 -> chamfer map of the foreground
      2 -> chamfer map of both the foreground and background
      @param maskSize : width of the mask used to compute chamfer map
      the wider the mask is, the more precise the chamfer map is
      by construction, the width of the mask must be odd 3, 5, 7...
      @param maskDim  : 2D or 3D 
      (2D on a 3D image compute the chamfer map slice by slice
  */
  static 
    HxUniformScalarField3 * chamferMapCalc(HxUniformScalarField3 * src, 
					   int location = 1, 
					   int maskSize = 3, 
					   int maskDim  = 3);

  
  /** Returns the chamfer map in the right scale
      The chamfer map is computed with integer values that approximate the the real values
      with at a scale factor. This function takes this scale factor and the voxel size
      to compute the real values of the chamfer map with the same scale than the voxel size
  */
  static 
    HxUniformScalarField3 * exactMap(HxUniformScalarField3 * distmap);

  /** Same than the last function, but only for a given position in the image */
  static float 
    getExactValue(HxUniformScalarField3 * distmap, int pos);

  /** Same than the last function, but for a given position in space (performs a trilinear interpolation) */
  static 
    float getExactValue(HxUniformScalarField3 * distmap, 
			float x, float y, float z);


};


#endif // CHAMFERCALC_H

/// @}
