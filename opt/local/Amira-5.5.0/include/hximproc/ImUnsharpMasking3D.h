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

/// @addtogroup hximproc hximproc
/// @{
#ifndef IM_UNSHARP_MASKING3D_H
#define IM_UNSHARP_MASKING3D_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter3D.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>

/**The unsharpmasking filter sharpens images. The 
    unsharp mask is computed by a Gaussian filter.  The weighted 
    difference of the original image (weight: c/2c-1 ) and the blurred image
    (weight: 1-c/2c-1) is calculated afterwards using the sharpness 
    parameter c. It determines the relation between original and blurred 
    image effectively controlling the degree of sharpness.  C should be in 
    the range of 0.6 to 0.8.  A value of 1 leaves the image unchanged.*/
class HXIMPROC_API ImUnsharpMasking3D : public ImFilter3D {

  MC_HEADER(ImUnsharpMasking3D);

public:
  ///Constructor
  ImUnsharpMasking3D(HxEditor* editor=0);

  ///Destructor
  ~ImUnsharpMasking3D();

  HxPortFloatSlider portSharpness;

  HxPortFloatTextN portKernelSize;
  


  void setKernelSize(float val);
  
  float getKernelSize() { return portKernelSize.getValue(0); }
  
  void setSharpness(float val);
  
  float getSharpness() { return portSharpness.getValue(); }

  /// Sets the filters parameters if any
  void setParameters(const ImFilterParameters *param);

  /// Updates the filter parameters class
  void updateParameters(ImFilterParameters *param);
  

  
  void apply3D(class McTypedData3D* src, 
	  class McTypedData3D* dst=NULL,
	  class McProgressInterface* progress=NULL);
  
  static ImFilter3D* createFilter(HxEditor* e) {
	  return new ImUnsharpMasking3D(e); }


};

#endif

/// @}
