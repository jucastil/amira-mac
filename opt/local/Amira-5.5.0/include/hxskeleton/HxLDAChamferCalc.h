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
#ifndef HXLDACHAMFERCALC_H
#define HXLDACHAMFERCALC_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortOptionMenu.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxWorkArea.h>

#include <hxskeleton/HxSkeletonWinDLLApi.h>

#ifndef WITH_OLD_LDA
class HxExternalData;
#else /* WITH_OLD_LDA */
#include <hxlda/HxLDAfile.h>
#endif /* WITH_OLD_LDA */

#ifdef WITH_OLD_LDA

#endif /* WITH_OLD_LDA */
class HXSKELETON_API HxLDAChamferCalc : public HxCompModule
{
  HX_HEADER(HxLDAChamferCalc);

public :
  HxLDAChamferCalc();
  ~HxLDAChamferCalc();

  HxPortFilename   portFilename;
  HxPortRadioBox   portMaskDim;
  HxPortRadioBox   portMaskSize;
  HxPortOptionMenu portMapLocation;
  HxPortRadioBox   portSign;
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
#ifndef WITH_OLD_LDA
  HxExternalData * chamferMapCalc(HxExternalData * src,
#else /* WITH_OLD_LDA */
  HxLDAfile * chamferMapCalc(HxLDAfile * src,
#endif /* WITH_OLD_LDA */
			     const char * filename,
			     int location = 1, 
			     int maskSize = 3, 
			     int maskDim  = 3,
			     bool changeTheSign = false,
			     HxWorkArea * workArea = 0);

  
  /** Returns the chamfer map in the right scale
      The chamfer map is computed with integer values that approximate the the real values
      with at a scale factor. This function takes this scale factor and the voxel size
      to compute the real values of the chamfer map with the same scale than the voxel size
  */
  static 
#ifndef WITH_OLD_LDA
    HxExternalData * exactMap(HxExternalData * distmap, 
#else /* WITH_OLD_LDA */
    HxLDAfile * exactMap(HxLDAfile * distmap, 
#endif /* WITH_OLD_LDA */
			 HxWorkArea * workArea = 0);

};

#endif // LDACHAMFERCALC_H

/// @}
