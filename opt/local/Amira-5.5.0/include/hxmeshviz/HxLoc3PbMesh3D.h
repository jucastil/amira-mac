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
#ifndef HX_LOC3_PB_MESH_3D_H
#define HX_LOC3_PB_MESH_3D_H

#include "hxmeshvizAPI.h"

#include <hxfield/HxLocation3.h>

#include <Inventor/SbLinear.h>

class HxPbMesh3D;
class PbCell;

class HXMESHVIZ_API HxLoc3PbMesh3D : public HxLocation3
{
  public:
    /// Constructor.
    HxLoc3PbMesh3D(HxPbMesh3D* grid);

    /// Sets location in the grid (global search).
    virtual int set(float x, float y, float z);

    /// Moves to new location in the grid.
    virtual int move(float x, float y, float z);

    const PbCell* getCurrentCell() {return m_cell;}
    const SbVec3f& getCurrentCoords() {return m_pcoord;}

  protected:

    HxPbMesh3D* m_grid;

    /// Index of current cell.
    const PbCell* m_cell;

    /// Parametric coordinates.
    SbVec3f m_pcoord;

};

#endif // HX_LOC3_PB_MESH_3D_H

/// @}
