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

/// @addtogroup hxiso hxiso
/// @{
#ifndef HX_ISOTETRA_H
#define HX_ISOTETRA_H

#include <hxiso/HxIsoWinDLLApi.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

#include <hxsurface/HxTriBase.h>

#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxTetraScalarField3.h>

struct Edge {
   int to;
   int intersectionPoint;
};


/// Computes an isosurface for scalar fields defined on a tetrahedral grid.
class HXISO_API HxIsoTetra : public HxTriBase {

  HX_HEADER(HxIsoTetra);
  
  public:
    /// Constructor.
    HxIsoTetra();

    // In update() the slider bounds are set.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Auto-connect unsnaps the DoIt button.
    virtual int autoConnect(HxObject* primary);

    /// Special handling for DoIt button.
    virtual void savePorts(FILE* fp);

    /// Threshold of the isosurface.
    HxPortFloatSlider portThreshold;

    /// Optionally use a point probe to set the threshold value.
    HxConnection portPointProbe;

    /// Triggers the computation.
    HxPortDoIt portAction;

  protected:
    virtual ~HxIsoTetra();

    McHandle<HxTetraScalarField3> volume;

    void computeIsosurface(float threshold);
    void checkEncoding();

    unsigned int surfaceUpToDate:1;
    unsigned int colorsUpToDate:1;

    McDArray<float> averagedData;
};

#endif

/// @}
