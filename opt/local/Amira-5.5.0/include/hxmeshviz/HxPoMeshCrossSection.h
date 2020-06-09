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

/// @addtogroup hxmeshviz hxmeshviz
/// @{
#ifndef HX_PO_MESH_CROSS_SECTION_H
#define HX_PO_MESH_CROSS_SECTION_H

#include "hxmeshvizAPI.h"

#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxPortColormap.h>

#include <hxcore/HxArbitraryCut.h>

#include <Inventor/nodes/SoSeparator.h>
#include <MeshViz/nodes/PoNonLinearDataMapping2.h>
#include <MeshViz/nodes/PoNonLinearDataMapping.h>
#include <MeshViz/nodes/PoCellFilter.h>
#include <MeshViz/3Ddata/PoMeshCrossSection.h>

class HxPbMesh3D;
class HxPbScalarField3;

//-----------------------------------------------------------------------------
class HXMESHVIZ_API HxPoMeshCrossSection : public HxArbitraryCut
{
    HX_HEADER(HxPoMeshCrossSection);

public:

    /// Constructor.
    HxPoMeshCrossSection();
	
    /// Compute method.
    virtual void compute();
	
    /// Update method.
    virtual void update();
	
    /// Colormap to be used.
    HxPortColormap portColormap;
	
    /// Color mode to be used.
    HxPortMultiMenu portColorMode;
	
    /// Modify list of displayed materials
    HxPortButtonMenu portSelection;
    
protected:
    HxPoMeshCrossSection(const McTypeInfo* type);
    void commonInit();
    virtual ~HxPoMeshCrossSection();

    static void preRebuildCB(void *userData, PoBase *base);
    static void postRebuildCB(void *userData, PoBase *base);

    static const SbColor* colorDataMappingCB(void *userData, float value);
    static float transparencyDataMappingCB(void *userData, float value);

    HxPbMesh3D*         m_grid;
    HxPbScalarField3*   m_field;

    McHandle<SoSeparator>               m_scene;
    McHandle<PoNonLinearDataMapping2>   m_gridDataMapping;
    McHandle<PoNonLinearDataMapping>    m_fieldDataMapping;
    McHandle<PoCellFilter>              m_filter;
    McHandle<PoMeshCrossSection>        m_section;

    McDArray<bool>      m_selectedMaterials;
};


//-----------------------------------------------------------------------------
class HxPoMeshCrossSection2 : public HxPoMeshCrossSection {
	HX_HEADER(HxPoMeshCrossSection2);

public: 
    HxPoMeshCrossSection2();

protected: 
    virtual ~HxPoMeshCrossSection2() { }
};


#endif

/// @}
