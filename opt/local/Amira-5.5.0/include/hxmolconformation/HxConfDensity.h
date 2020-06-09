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

/// @addtogroup hxmolconformation hxmolconformation
/// @{
#ifndef HX_CONF_VOL_H
#define HX_CONF_VOL_H

#include <mclib/McVec4i.h>
#include <mclib/McVec3f.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxConnection.h>

#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxUniformColorField3.h>
#include <hxfield/HxUniformVectorField3.h>

#include <hxmolecule/MolFilter.h>

#include <hxmolecule/HxMolTrajectory.h>
#include <hxmolecule/MolAlignment.h>
#include <hxmolecule/MolColoring.h>

#include "HxMolConformationWinDLLApi.h"

///
class HXMOLCONFORMATION_API HxConfDensity : public HxCompModule {
    HX_HEADER(HxConfDensity);
    
    ///
    HxPortIntTextN    portTimeStepRange;
    ///
    HxPortMultiMenu   portFuzzyFunction;
    ///
    HxPortFloatSlider portVoxelSize;
    ///
    HxPortInfo        portDimsInfo;
    ///
    HxPortSeparator   portSep1;
    ///
    MolAlignment      alignment;
    ///
    MolFilter         filter;
    ///
    HxPortSeparator   portSep2;
    ///
    HxPortToggleList  portShape;
    HxPortRadioBox    portRadiusOption;
    HxPortFloatSlider portAtomRadius;
    HxPortFloatSlider portBondRadius;
    HxPortMultiMenu   portField;
    ///
    MolColoring       coloring;
    ///
    HxPortSeparator   portSep3;
    ///
    HxPortButtonList  portButtons;

    ///
    McDArray<int> fuzzyDataObs;
    
protected:
    ///
    HxMolTrajectory   *hxTraj;
    
    McHandle<HxUniformScalarField3> sField, sField2;
    McHandle<HxUniformColorField3>  cField;
    McHandle<HxUniformVectorField3> vField;
    
    int dims[3];
    float voxelSize;
    float bbox[6];
    float extBBox[6];

    McBitfield useAtom;

    McDArray<McMat4f> transf;

    char updateBBoxFlag:1;

public:
    ///
    HxConfDensity();
    
    ///
    void update();
    ///
    void compute();
    
protected:
    ///
    int computeColorField();
    ///
    void computeBBox();
    /// Compute atom radius offset, atom-type specific if necessary.
    float computeAtomRadiusOffset();
    ///
    void computeExtendedBBox();
    ///
    void doIt();

    int createScalarField(int flag = 0);
    int createColorField();
    int createVectorField();
    
    int computeVolumeForSpheresAndCylinders(McDArray<McMat4f> & molTr);

    int computeVolumeForSpheres(McDArray<McMat4f> & molTr);
    void handleInsideSpherePointsS(McVec3f &atomPos, int bboxInx[6],
                                   float radius2, McBitfield & bf, float weight);
    void handleInsideSpherePointsC(McVec3f &atomPos, int bboxInx[6],
                                   float radius2, SbColor &color, 
                                   McBitfield & bf, float weight);
    
    int computeVolumeForCylinders(McDArray<McMat4f> & transf);
    void bresenham(McVec3f bondEndPoints[2], float diam2, 
                   McBitfield & bf, McDArray<McVec4i> & points,
                   McDArray<McVec3f> & coords,
                   McVec4i offsetVec[4],
                   McVec3f coordsOffset[4]);
    void updateGridForCylindersS(McVec3f bondEndPoints[2], float diam2,
                                 McBitfield & bf, McBitfield & bf2, 
                                 McDArray<McVec4i> & points,
                                 McDArray<McVec3f> & coords,
                                 McVec4i offsetVec[4],
                                 McVec3f coordsOffset[4], float weight);
    void updateGridForCylindersC(McVec3f bondEndPoints[2], float diam2,
                                 SbColor colors[2], 
                                 McBitfield & bf, McBitfield & bf2,
                                 McDArray<McVec4i> & points,
                                 McDArray<McVec3f> & coords,
                                 McVec4i offsetVec[4],
                                 McVec3f coordsOffset[4], float weight);
    int isInsideCylinderS(McVec3f & point, McVec3f endPoints[2], 
                          float diam2, McVec3f dirVec);
    int isInsideCylinderC(McVec3f & point, McVec3f endPoints[2], 
                          float diam2, McVec3f dirVec);
    
    void compBBoxInx(float bbox[6], int bboxInx[6]);

    ///
    int parse(Tcl_Interp* t, int argc, char **argv);
    ///
    int canCreateData(HxData* data, McString& createCmd);

    ///
    void savePorts(FILE* fp);
};

#endif

/// @}
