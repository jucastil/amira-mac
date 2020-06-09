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
#ifndef IM_GAUSSFILTER2D_H
#define IM_GAUSSFILTER2D_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImSepConvFilter2D.h>
#include <hxcore/HxEditor.h>
#include <hxcore/HxPortFloatTextN.h>

/** The Gauss filter smooths or blurs an image by performing a convolution
    operation with a Gaussian filter kernel. */
class HXIMPROC_API ImGaussFilter2D : public ImSepConvFilter2D {

  MC_HEADER(ImGaussFilter2D);

public:
  ///Constructor
  ImGaussFilter2D(HxEditor* editor=0);

  ///Destructor
  ~ImGaussFilter2D();

  HxPortFloatTextN portSigma;

  HxPortFloatTextN portKernelSize;

  /** Inherited from ImFilter3D **/
  virtual void update();

///Set filter kernel according to the values specified by ports
  void calculateKernel();
    
/**Change values of ports. Parameter size defines a quadratic
  kernel, parameter sigma allows to adjust the width of the Gauss function 
  relative to the kernel size. To set the new kernel, calculatekernel()
  is called from within this method.*/
  void calculateKernel(float sigma, int size);
  
/**Simply calls method ImSepConvFilter2D::convolve(class McTypedData2D*, class
  McTypedData2D*)*/
  void apply2D(class McTypedData2D* src, 
               class McTypedData2D* dst=NULL);

/**Calls calculateKernel() before calling ImFilter2D::apply3D(McTypedData3D*,
	   McTypedData3D*, McProgressInterface*) */
  virtual void apply3D(McTypedData3D* source, 
		 McTypedData3D* dest=NULL, 
		 McProgressInterface* progress=NULL);

/** Note that the kernel isn`t updated unless calculateKernel() is called */  
  void setKernelSize(float valX, float valY);
  
  float getKernelSizeX() { return portKernelSize.getValue(0); }
  
  float getKernelSizeY() { return portKernelSize.getValue(1); }

  
/**Sigma allows to adjust the width of the Gauss function relative to the 
  kernel size.
  Note that the kernel isn`t updated unless calculateKernel() is called */  
  void setSigma(float valX, float valY);
  
  float getSigmaX() { return portSigma.getValue(0); }
  
  float getSigmaY() { return portSigma.getValue(1); }

  /// Sets the filters parameters if any
  void setParameters(const ImFilterParameters *param);

  /// Updates the filter parameters class
  void updateParameters(ImFilterParameters *param);

  /// Updates the port names depending of the orientation
  void setPortLabels(char * port1, char *port2);

  static ImFilter3D* createFilter(HxEditor* e) {
      return new ImGaussFilter2D(e); }

};

#endif

/// @}
