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
#ifndef HX_PB_SCALAR_FIELD3_H
#define HX_PB_SCALAR_FIELD3_H

#include <hxfield/HxScalarField3.h>
#include <hxmeshviz/HxPbMesh3D.h>

class HxConnection;
class HxLoc3PbMesh3D;

//-----------------------------------------------------------------------------
class HXMESHVIZ_API HxPbScalarField3 : public HxScalarField3
{
    HX_ABSTRACT_HEADER(HxPbScalarField3);

public:

    /**
     * Constructor for Polyhedrical scalar field.
     * Be careful: data arrays are not duplicated, but this class becomes their owner.
     * This means that user should not use those arrays again, neither delete them.
     * This class will assum that given arrays had been allocated with malloc.
     */
    HxPbScalarField3(HxPbMesh3D* grid, int nDataVar, PbMesh::DataBinding e, float* data);

    /// Parse the interpreter commandline and execute commands
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Computes bounding box of geometry.
    virtual void getBoundingBox(float bbox[6]) const { m_theGrid->getBoundingBox(bbox); }

    HxPbMesh3D *getGrid() const { return m_theGrid; }

    /// Mesh accessor
    PbMesh3D *getMesh() const { return m_theGrid->getMesh(); }

    int getValueIndex() const { return m_valueIndex; }

    virtual HxLocation3* createLocation();

protected:

    virtual ~HxPbScalarField3();

    /// Computes magnitude range.
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    static int eval(HxPbScalarField3*, HxLoc3PbMesh3D*, float*);

    HxConnection*       m_portGrid;
    HxPbMesh3D*         m_theGrid;
    int                 m_valueIndex;
};

#endif

/// @}
