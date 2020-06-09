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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HX_SIMPLIFIER_H
#define HX_SIMPLIFIER_H

#include <hxsurftools/HxSurfToolsWinDLLApi.h>
#include <hxcore/HxEditor.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxsurface/HxSurface.h>
/// This class implements surface simplification and surface smoothing.

class HXSURFTOOLS_API HxSimplifier : public HxEditor {

  HX_HEADER(HxSimplifier);

  public:
    /// Default constructor.
    HxSimplifier();
  
    /// Called whenever a port changes.
    virtual void fire();

    /// Simplify parameters: 0=number of faces 1=max edge length 2=min edge length
    HxPortFloatTextN portSimplify;

    /// Options: 0=preserve slice structure 1=fast intersection test
    HxPortToggleList portOptions;

    /// Do it button: 0=simplify 1=autoflip 2=contract edges
    HxPortButtonList portAction;

    /// Parse method
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Initialize ports here.
    virtual void startEditing(HxData *data);

  protected:
    ~HxSimplifier();

    HxSurface* surface;
    float zmin;
    float sliceThickness;
    int   stacked;
    float radiusRatio;
    float edgeLengthWeight;
    int intersectionTestStrategy;
    float factMaxError;
    int memoryless;

    /// Smooth surface.
    void smooth(int nSteps, float lambda);

    /// Debug.
    void debug(int edge);

    /// Submit surface simplification as batch job.
    void submitBatchJob();
};

#endif


/// @}
