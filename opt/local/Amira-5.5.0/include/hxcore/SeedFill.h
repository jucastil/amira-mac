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

/// @addtogroup hxcore hxcore
/// @{
#ifndef SEEDFILL_H
#define SEEDFILL_H

#include <hxcore/HxAmiraWinDLLApi.h>

/** This method implements a 3D seed fill algorithm. The variables
    @c nx, @c ny, and @c nz denote the size of the 3D array @c buffer.
    The seed position is defined by @c x, @c y, @c z. All connected
    voxels with the same value as voxel (x,y,z) are set to the new
    value @c nv. Optionally, the bounding box of the filled region is
    returned in @c box. The method considers voxels sharing a face as
    neighbors. */
HXCORE_API
mculong seedFill(int x, int y, int z, int nx, int ny, int nz,
    unsigned char* buffer, unsigned char nv, int* box=0);

/** Seed fill algorithm similar to seedFill. However, voxels
    sharing at least one edge are considered as neighbors. */
HXCORE_API
mculong seedFill18(int x, int y, int z, const int dims[3],
    unsigned char* buffer, unsigned char nv, int* box=0);

/** Seed fill algorithm similar to seedFill. However, voxels
    sharing at least one corner are considered as neighbors. */
HXCORE_API
mculong seedFill26(int x, int y, int z, const int dims[3],
    unsigned char* buffer, unsigned char nv, int* box=0);

#endif

/// @}
