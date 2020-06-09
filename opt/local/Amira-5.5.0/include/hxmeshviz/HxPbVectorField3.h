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
#ifndef HX_PB_VECTOR_FIELD3_H
#define HX_PB_VECTOR_FIELD3_H

#include <hxfield/HxVectorField3.h>
#include <hxmeshviz/HxPbMesh3D.h>

class HxConnection;
class HxLoc3PbMesh3D;

//-----------------------------------------------------------------------------
class HXMESHVIZ_API HxPbVectorField3 : public HxVectorField3
{
    HX_ABSTRACT_HEADER(HxPbVectorField3);

public:

    /**
     * Constructor for Polyhedrical vector field.
     * Be careful: data arrays are not duplicated, but this class becomes their owner.
     * This means that user should not use those arrays again, neither delete them.
     * This class will assum that given arrays had been allocated with the malloc.
     */
    HxPbVectorField3(HxPbMesh3D* grid, int nDataVar, PbMesh::DataBinding e, float* data);

    /// Computes bounding box of geometry.
    virtual void getBoundingBox(float bbox[6]) const { m_theGrid->getBoundingBox(bbox); }

    /// Mesh accessor
    PbMesh3D *getMesh() const 
    { return m_theGrid->getMesh() ;}

    int getValueIndex() const { return m_valueIndex; }

    virtual HxLocation3* createLocation();

protected:

    virtual ~HxPbVectorField3();

    /// Computes magnitude range.
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    static int eval(HxPbVectorField3*, HxLoc3PbMesh3D*, float*);

    HxConnection*       m_portGrid ;
    HxPbMesh3D*         m_theGrid ;
    int                 m_valueIndex;

};

#endif

/// @}
