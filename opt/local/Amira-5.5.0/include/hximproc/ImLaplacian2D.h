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
#ifndef IM_LAPLACIAN2D_H
#define IM_LAPLACIAN2D_H

#include <hximproc/ImFilter2D.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>

/** The Laplace filter is a rotation invariant edge detection
 filter. The algorithm finds zero crossings of the second
 derivation, i.e. changes of the sign of the first derivation 
 of the "image function" which may indicate an edge. */ 
class HXIMPROC_API ImLaplacian2D : public ImFilter2D {

  MC_HEADER(ImLaplacian2D);

public:
  ///Constructor
  ImLaplacian2D(HxEditor* editor=0);

  ///Destructor
  ~ImLaplacian2D();

  //HxPortFloatSlider portSharpness;

  //HxPortFloatTextN portKernelSize;

  ///holds the filter algorithm
  void apply2D(class McTypedData2D* src, 
               class McTypedData2D* dst=NULL);

  //void setKernelSize(float val);
  
  //float getKernelSize() { return portKernelSize.getValue(0); }
  
  //void setSharpness(float val);
  
  //float getSharpness() { return portSharpness.getValue(); }

  static ImFilter3D* createFilter(HxEditor* e) {
      return new ImLaplacian2D(e); }

};

#endif

/// @}
