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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_LOC3_HEXA_H
#define HX_LOC3_HEXA_H

#include <hxfield/HxFieldWinDLLApi.h>
#include <hxfield/HxLoc3Regular.h>
#include <hxfield/HxHexaGrid.h>

/// Represents a general location in a hexahedral grid.

class HXFIELD_API HxLoc3Hexa : public HxLoc3Regular
{
  public:
    /// Sets location within hexahedral grid.
    virtual int set(float x, float y, float z);
    
    /// Updates location within hexahedral grid.
    virtual int move(float x, float y, float z);
    
    /// Index of current hexahedron.
    int idx;
    
    /// This class must only be created by a HxUniformCoord3.
    HxLoc3Hexa(HxHexaGrid* grid);

  private:
    /// Pointer to coordinates of the uniform grid.
    HxHexaGrid* theGrid;

    void stencilWalk(int cell, float x, float y, float z,
        float& u , float& v, float& w);
    float bbox[6];
};

#endif

/// @}
