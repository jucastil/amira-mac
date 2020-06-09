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

/// @addtogroup hxdeconv hxdeconv
/// @{
#ifndef HX_BEAD_EXTRACT_H
#define HX_BEAD_EXTRACT_H

#include <hxcore/HxConnection.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxCompModule.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxlandmark/HxLandmarkSet.h>
#include <hxdeconv/hxdeconvAPI.h>

///
class HXDECONV_API HxBeadExtract : public HxCompModule {

  HX_HEADER(HxBeadExtract);
  
  public:
    /// Constructor.
    HxBeadExtract();
  
    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Auto-connect method.
    virtual int autoConnect(HxObject* primary);

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Connection to landmark set with estimated bead centers.
    HxConnection portLandmarks;

    /// Says how many beads have already been averaged
    HxPortInfo portInfo;

    /// Resolution
    HxPortIntTextN portResolution;
    
    /// Voxel size
    HxPortFloatTextN portVoxelSize;

    /// Preprocess: 0=Adjust centers, 1=estimate size, 2=undo
    HxPortButtonList portPreprocess;

    /// Do it button
    HxPortDoIt portAction;

  protected:
    virtual ~HxBeadExtract();
    virtual void resultChanged(int);

    void computeBeadSize(HxUniformScalarField3* data,
        HxLandmarkSet* landmarks, int dims[3]);
    void extractBeads(HxUniformScalarField3* data,
        HxLandmarkSet* landmarks, HxUniformScalarField3* result);
    void optimizeBeadCenters(HxUniformScalarField3* data,
        HxLandmarkSet* landmarks);

    void undoSave(HxLandmarkSet* landmarks);
    void undoRestore(HxLandmarkSet* landmarks);

    struct UndoItem {
        McDArray<McVec3f> beads;
        float resolution[3];
        float voxelSize[3];
    };

    McDArray<UndoItem> undoStack;
};

#endif

/// @}
