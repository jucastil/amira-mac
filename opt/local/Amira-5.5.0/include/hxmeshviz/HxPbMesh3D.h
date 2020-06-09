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
#ifndef HX_PB_MESH_3D_H
#define HX_PB_MESH_3D_H

#include "hxmeshvizAPI.h"
#include <hxcore/HxSpatialData.h>

#include <MeshViz/nodes/PoIndexedMesh3D.h>

//-----------------------------------------------------------------------------
class HXMESHVIZ_API HxPbMesh3D : public HxSpatialData
{
    HX_ABSTRACT_HEADER(HxPbMesh3D);

public:

    /**
     * Constructor for Polyhedrical mesh.
     * Be careful: data arrays are not duplicated, but this class becomes their owner.
     * This means that user should not use those arrays again, neither delete them.
     * This class will assum that given arrays had been allocated with malloc.
     */
    HxPbMesh3D(int numNodes, float* xn, float* yn, float* zn, 
        int numCells, int* cellIndex, int* cellType);

    /// Computes bounding box of geometry.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Mesh accessor
    PbMesh3D* getMesh() const { return (PbIndexedMesh3D*) m_meshProperty->getMesh(); }

    /// 
    PoMeshProperty* getMeshPropertyNode() const { return m_meshProperty; }

    /**
     * Sets the cells materials.
     * Be careful: data arrays are not duplicated, but this class becomes their owner.
     * This means that user should not use those arrays again, neither delete them.
     * This class will assum that given arrays had been allocated with malloc.
     */
    void setCellMaterial(float* cellMaterial);

protected:
    virtual ~HxPbMesh3D();
    virtual void info();

    McHandle<PoIndexedMesh3D>   m_meshProperty;
};

#endif

/// @}
