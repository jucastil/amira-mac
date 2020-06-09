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
#ifndef IM_GAUSSFILTER_H
#define IM_GAUSSFILTER_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImSepConvFilter3D.h>
#include <hxcore/HxPortFloatTextN.h>

/** The Gauss filter smooths or blurs an image by performing a convolution
    operation with a Gaussian filter kernel. */
class HXIMPROC_API ImGaussFilter3D : public ImSepConvFilter3D {
  MC_HEADER( ImGaussFilter3D);

public:
   ///Constructor
  ImGaussFilter3D(HxEditor* editor=0);

  ///Destructor
  ~ImGaussFilter3D();

  HxPortFloatTextN portSigma;

  HxPortFloatTextN portKernelSize;

  /** Inherited from ImFilter3D **/
  virtual void update();

  ///Set filter kernel according to the values specified by ports
  void calculateKernel();

  /**Calls calculateKernel() before calling ImSepConvFilter3D::convolve(class
   * McTypedData3D*, class McTypedData3D*) */
  void apply3D( class McTypedData3D* src, 
		class McTypedData3D* dst=NULL,
		class McProgressInterface* progress=NULL);

  void setParams(int kernelsize,float sigma);
  void setParams(int kernelsize[3],float sigma[3]);

  /** Note that the kernel isn`t updated unless calculateKernel() is called */  
  void setKernelSize(float valX, float valY, float valZ);
  
  float getKernelSizeX() { return portKernelSize.getValue(0); }
  
  float getKernelSizeY() { return portKernelSize.getValue(1); }
  
  float getKernelSizeZ() { return portKernelSize.getValue(2); }

  /**Sigma allows to adjust the width of the Gauss function relative to the 
  kernel size.
  Note that the kernel isn`t updated unless calculateKernel() is called */  
  void setSigma(float valX, float valY, float valZ);
  
  float getSigmaX() { return portSigma.getValue(0); }
  
  float getSigmaY() { return portSigma.getValue(1); }
  
  float getSigmaZ() { return portSigma.getValue(2); }

  /// Sets the filters parameters if any
  void setParameters(const ImFilterParameters *param);

  /// Updates the filter parameters class
  void updateParameters(ImFilterParameters *param);

  static ImFilter3D* createFilter(HxEditor* e) {
      return new ImGaussFilter3D(e); }
};
#endif

/// @}
