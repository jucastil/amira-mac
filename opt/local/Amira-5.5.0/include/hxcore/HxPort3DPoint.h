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
#ifndef HX_PORT_3DPOINT_H
#define HX_PORT_3DPOINT_H

#include <hxcore/HxPort3DPointList.h>

/** Required for compatibility with Amira 2.x. In Amira 3.0 the class
    HxPort3DPoint has been removed because it merely provided a subset
    of the functionality of HxPort3DPointList. With this define old
    code should compile as is with one possible expection. In the old
    class HxPort3DPoint the method getValue(int n) returned a float,
    namely the n-th component of the 3D point. In HxPort3DPointList the
    method getValue(int n) returns an SbVec3f, namely the n-th point
    in the list. In order to fix this you have to replace getValue(k)
    by getValue()[k]. If getValue() was used without arguments (which
    should be the standard case) nothing has to be done. */
#define HxPort3DPoint HxPort3DPointList

#endif

/// @}
