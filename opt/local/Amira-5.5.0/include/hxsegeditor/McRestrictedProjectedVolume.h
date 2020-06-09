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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef MC_RESPROJVOL_H
#define MC_RESPROJVOL_H

/** This class handles selection of 3D voxels by defining
    regions in the projections onto the major planes. */

#include <mclib/McBitfield.h>
//#include <mclib/McData2D.h>
#include "GiSelection2D.h"

class McRestrictedProjectedVolume
{

protected:
    McBitfield planes[3];
    int dims[3];
public:
    McRestrictedProjectedVolume();
    McRestrictedProjectedVolume(const int* dims);
    void init(const int* dims);
    //void setPlane(int which, McData2D<unsigned char>* selection);
    void setPlane(int which, GiSelection2D* selection);

    int isSelected(int i, int j, int k) {
        if (planes[0].nBits() && !planes[0][k*dims[1]+j])
            return 0;
        if (planes[1].nBits() && !planes[1][k*dims[0]+i])
            return 0;
        if (planes[2].nBits() && !planes[2][j*dims[0]+i])
            return 0;
        return 1;
    }

    int isSelected(int idx3d) {
        if (planes[0].nBits() && !planes[0][idx3d/dims[0]])
            return 0;
        if (planes[1].nBits()) {
            int x = idx3d % dims[0];
            int z = idx3d / (dims[0]*dims[1]);
            if (!planes[1][z*dims[0]+x])
                return 0;
        }
        if (planes[2].nBits() && !planes[2][idx3d % (dims[0]*dims[1])])
            return 0;
        return 1;
    }
};

#endif

/// @}
