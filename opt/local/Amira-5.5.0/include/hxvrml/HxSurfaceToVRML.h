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

/// @addtogroup hxvrml hxvrml
/// @{
#ifndef HX_SURFACETOVRML
#define HX_SURFACETOVRML

#include <hxvrml/HxVrmlWinDLLApi.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortTabBar.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFilename.h>

#include <hxsurface/HxSurface.h>
#include <hxsurftools/HxDisplaySurface.h>

class HxField3;

/// Export module for writing VRML files.
class HXVRML_API HxSurfaceToVRML : public HxCompModule 
{
    HX_HEADER(HxSurfaceToVRML);
  

public:

    /// constructor
    HxSurfaceToVRML();   
    
    /// Update method.
    virtual void update();
    /// Compute method.
    virtual void compute();
    /// auto connect
    virtual int autoConnect(HxObject* primary);


protected:  

    /// Destructor.
    ~HxSurfaceToVRML();

    void updateInfoPort();


private:

    void getColor(int which, SbColor & col);

    float getTransparency(int which);

    void writeJPEG(HxField3* field, 
        const char* filename, 
        float min, 
        float max);
    
    int exportComplex();   
    int exportSimple();

    void extractPerPatch( int material,
        int patch,
        McDArray<McVec3f> & points, 
        int &nPoints,
        McDArray<int> & indexedFaceSet, 
        McDArray<int> & pointIsCopied,
        int &nTriangels);
    
    void extractMaterial( int material,
        McDArray<McVec3f> & points, 
        int &nPoints,
        McDArray<int> & indexedFaceSet, 
        McDArray<int> & pointIsCopied,
        int &nTriangels);
    
    void getPatchesFromSelectedTriangles( int **patchList, McDArray<int> & nPatches);
    
    void getInterfaces();

public:
    
    /// displays the selected materials
    HxConnection        portImage;
   
    /// different interfaces for simple and complex export
    HxPortTabBar        portTab;


    // TAB Selection //////////////////////////////////////

    /// displays info about the object to export
    HxPortInfo          portInfo;
    
    /// displays the selected materials
    HxPortInfo          portSelectInfo;

    /// Add, remove, clear.
    HxPortButtonMenu    portBuffer;
    enum { ADD=0, REMOVE=1, CLEAR=2 };

    /// additional per triangle AND-mask
    HxPortRadioBox      portSelectMask;


    // TAB VRML ///////////////////////////////////////////

    /// 
    HxPortToggleList    portRenderSpecular;
    /// 
    HxPortToggleList    portRenderSmooth;
    ///
    HxPortToggleList    portSceneMoveSlices;
    ///
    HxPortToggleList    portSceneStaticSwitches;
    ///
    HxPortToggleList    portSceneLabels;


    // TAB Slices /////////////////////////////////////////

    /// toggle to export slices or not
    HxPortToggleList    portExportSlices;

    /// for Hounsfield Range
    HxPortFloatTextN    portHfR;

    /// for number of slices per direction
    HxPortIntTextN      portSliceNumbers;
    

    ///
    HxPortSeparator     portSep01;
    /// 
    HxPortToggleList    portSimpleMode;
    /// Output file name.
    HxPortFilename      portFilename;
    /// Do it button.
    HxPortDoIt          portAction;


private:

    int                           connectedToHxDisplaySurface;
    int                           firstTime;
    McDArray<int>                 materialList;
    McDArray<McString>            nameList;
    FILE                        * _fp;

    // some interfaces of the connected input object
    class HxSurface             * _ISurface;
    class HxDisplaySurface      * _IDisplay;
    class HxUniformScalarField3 * _IField;
    class HxObject              * _IObject;
    class HxTriBase             * _ITriBase;
    class SoTriSurface          * _ITriSurf;
};

#endif

/// @}
