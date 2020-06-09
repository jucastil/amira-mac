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

/// @addtogroup hxelasticslicereg hxelasticslicereg
/// @{
#ifndef HX_GRID_VIEW_EULER
#define HX_GRID_VIEW_EULER

#include <mclib/McHandle.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxTightConnection.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxCurvilinearCoord3.h>
#include <hxlatticex/HxLattice.h>

#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoSeparator.h>

class HxGridViewEuler : public HxModule {

  HX_HEADER(HxGridViewEuler);
  
  public:
    HxGridViewEuler();

    virtual void compute();
    virtual void update();

    HxTightConnection portModule;
    HxPortIntTextN portNumSamples;
    HxPortColormap portColormap;
    HxPortIntSlider portSliceNumber;
    HxPortIntSlider portLineWidth;
    HxPortFloatSlider portAlphaBase;
    HxPortColorList portLineColor;

  protected:
    void updateCurvedGrid();
    void updateGridLines();
    void updateColor();

    McHandle<SoSeparator> mRootSeparator;
    McHandle<SoDrawStyle> mLineDrawStyle;
    McHandle<SoIndexedLineSet> mIndexedLineSet;
    McHandle<SoVertexProperty> mVertexProperty;

    McDArray<float> vectorLength;
    int numSamplesX, numSamplesY;

    HxLattice *lattice;
    McBoundingBox rectbb;
    float voxelSizeX, voxelSizeY;
    float volumeSizeX, volumeSizeY;
    
    McHandle<HxCurvilinearCoord3> curvCoords;
    HxLoc3Regular* location;
};

#endif


/// @}
