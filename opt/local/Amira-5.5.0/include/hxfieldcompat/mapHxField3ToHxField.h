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

/// @addtogroup hxfieldcompat hxfieldcompat
/// @{
#ifndef HXFIELDCOMPAT_MAPHXFIELD3TOHXFIELD_H
#define HXFIELDCOMPAT_MAPHXFIELD3TOHXFIELD_H

#include "HxFieldCompatWinDLLApi.h"

#include <mclib/McDArray.h>
#include <hxcore/HxInterface.h>
#include <hxfieldx/HxField.h>

#include <hxfieldcompat/HxConvolutionHelper.h>

#include <hxfield/HxLocation3.h>
#include <hxfield/HxScalarField3.h>

class HxField3;
class HxFieldEvaluatorX;
class HxFieldQuantity;
class HxFieldQuantitiesLib;

class HXFIELDCOMPAT_API HxField3ToHxField : public HxField {
  MC_HEADER (HxField3ToHxField);

public:
  HxField3ToHxField (HxField3* owner);

  virtual ~HxField3ToHxField();

  virtual int doGetNDims ();

  virtual McBoundingBox doGetBoundingBox();

  virtual HxFieldQuantityInfos doGetAllQuantityInfos ();

  virtual McDataType doGetNativeType ();

  /// InterpolationScheme: Default
  virtual HxInterpolationScheme doGetInterpolationScheme ();

  HxFieldEvaluatorX* doGetEvaluator(const McDArray<HxFieldQuantity>& quantities);

  virtual void doReleaseEvaluator (HxFieldEvaluatorX* eval);

private:

  class HxField3ToHxFieldEvaluatorX;
  class HxField3ToHxFieldPrimaryEvaluatorX;

  HxField3* mObj;

  HxFieldQuantitiesLib* QLib;
};

class HxScalarFieldMappingHelper {
public:

    /// This method computes the gradient for a given scalar field. The gradient is a little bit smoother than with finite differences.
    static bool derivativeGradient(HxScalarField3* field, HxLocation3* loc, float* result);

    /// This method computes the Hessian matrix for a given scalar field. Do not use this method with noisy data.
    static bool derivativeHessian(HxScalarField3* field, HxLocation3* loc, float* result);

};

#endif

/// @}
