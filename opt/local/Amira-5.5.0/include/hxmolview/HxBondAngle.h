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

/// @addtogroup hxmolview hxmolview
/// @{
#ifndef HX_BONDANGLE_H
#define HX_BONDANGLE_H

#include <hxmolecule/MolColoring.h>
#include <mclib/McSmallArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec2i.h>

#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortSeparator.h>

#include <hxsurface/HxTriBase.h>

#include <hxmolecule/HxMolecule.h>
#include <hxmolecule/MolFilter.h>
#include <hxmolecule/MolHighlighting.h>
#include <hxmolecule/HxMolBaseDisplayModule.h>

#include <hxmolview/HxMolViewWinDLLApi.h>

class HXMOLVIEW_API HxBondAngle : public HxTriBase, 
                                  public HxMolBaseDisplayModule
{
    HX_HEADER(HxBondAngle);
    
    ///
    HxPortFloatSlider portTransparency;

    HxPortSeparator sep1;

    ///
    HxPortRadioBox portColorMode;
    ///
    MolColoring coloring;

    HxPortSeparator sep2;
    
    ///
    MolFilter filter;
    
    ///
    MolHighlighting highlighting;

    ///
    McDArray<McSmallArray<int, 4> > connectionList;

    ///
    McHandle<HxMolecule>  hxmol;
    /// 
    McHandle<Molecule>    molecule;
    ///
    McHandle<MolTopology> topo;

#ifdef BONDANGLE_HANDLE_SUBSTRUCTURE_LEVEL
    HxPortSeparator sep3;
    
    HxPortMultiMenu portSubstructureLevel;

    ///
    HxPortColormap portSubLevelColMap;
#endif

public:
    HxBondAngle();
    ~HxBondAngle();

    ///
    void info();
    ///
    void compute();
    ///
    void update();
    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

protected:
    void computeTriangles();
    void setColors();
    void highlightTriangles();
    void selectTriangles();

    void savePorts(FILE* fp);
};

#endif

/// @}
