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

/// @addtogroup hxmatlab hxmatlab
/// @{
#ifndef HX_PULL_MATLAB_H
#define HX_PULL_MATLAB_H

#include <hxcore/HxCompModule.h>

#include <mclib/McDArray.h>

#include <hxmatlab/HxMatlabWinDLLApi.h>
#include <hxmatlab/HxMatlabEng.h>

/** \namespace hxmatlab
 *  HxPullMatlab
 *
 *  HxPullMatlab provides routines for transfering objects from
 *  Matlab to Amira.
 *  Every function has the calling compute module as parameter to
 *  access the compute module's results.
 */

namespace hxmatlab
{
    /// function seperates the mxArray between a struct or an array
    HXMATLAB_API int pullMatlab(HxCompModule * compMod, int * numResult, mxArray * result, const char* buf);

    /// function to pull arrays as HxUniformField
    HXMATLAB_API int pullLattice(HxCompModule * compMod, int * numResult, mxArray * result, const McPrimType resultType, const char* buf);

    /// function determines the type of the mxarray (e.g. surface / surfacefield)
    HXMATLAB_API int pullStruct(HxCompModule * compMod, int * numResult, mxArray * result, const char* buf);

    /// function to pull fields as HxField3
    HXMATLAB_API int pullField(HxCompModule * compMod, int * numResult, mxArray * result, const char* name);

    /// function to pull surfaces
    HXMATLAB_API int pullSurface(HxCompModule * compMod, int * numResult, mxArray * result, const char* buf);

    /// function to pull HxLineSets
    HXMATLAB_API int pullLineSet(HxCompModule * compMod, int * numResult, mxArray * result, const char* name);

};
#endif

/// @}
