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
#ifndef HX_PUSH_MATLAB_H
#define HX_PUSH_MATLAB_H

#include <hxfield/HxLattice3.h>
#include <hxtime/HxTime.h>
#include <hxsurface/HxSurface.h>
#include <hxsurface/HxSurfaceField.h>
#include <hxlines/HxLineSet.h>

#include <mclib/McDArray.h>

#include <hxmatlab/HxMatlabWinDLLApi.h>
#include <hxmatlab/HxMatlabEng.h>

/** \namespace hxmatlab
 *  HxPushMatlab
 *
 *  HxPushMatlab provides routines for transfering objects from
 *  Amira to Matlab. All objects, except HxTime, are stored in a
 *  Matlab struct. HxLattice3 objects can be stored in structs or
 *  as 3D/4D arrays.  The following types and information are
 *  supported:
 *  HxLattice3: stored in a struct named 'field'. If several
 *  HxLattice3 objects are transfered, the name includes a counter
 *  'fieldID'.
 *  The struct looks like:
 *      field.data - 3D/4D array of data values (scalar/vector);
 *      field.coords - 2D array of 3D-coordinates (3 x numPoints). The addressing is x-fastest
 *      field.bbox - 1D array of bounding box (xmin xmax ymin ymax zmin zmax)
 *      field.name - string of the object name
 *      field.type - primeType of the object
 *
 *  HxTime: a single scalar value 't' is transfered to Matlab. If
 *  several HxTime objects are transfered, the name includes a
 *  counter 'tID'.
 *
 *  HxSurface: stored in a struct named 'surf'. If several
 *  HxSurface objects are transfered, the name includes a counter
 *  'surfID'.
 *  The struct looks like:
 *      surf.vertices - 2D array of coordinates (numPoints x 3)
 *      surf.faces - 2D array of vertex-IDs (numTriangles x 3)
 *      surf.FaceVertexCData - 2D array of triangleVertex-colors (numTriangles x 3)
 *      surf.FaceColor - string 'flat'
 *      surf.EdgeColor - string 'none'
 *      surf.bbox - 1D array of bounding box (xmin xmax ymin ymax zmin zmax)
 *      surf.name - string of the object name
 *      surf.type - primeType of the object
 *
 *  HxSurfaceField: stored in a struct named 'surf'. If several
 *  HxSurfaceField objects are transfered, the name includes a
 *  counter 'surfID'.
 *  The struct looks like:
 *      The underlying surface is transfered. The structure is the same as for HxSurface.
 *      surf.data - 2D-array of data values (nD x numPoints/numTrinagles/numEdges)
 */

namespace hxmatlab
{

    /// function to transfer HxLattice3 objects as array
    HXMATLAB_API int pushLattice(Engine * eng, HxLattice3 * plattice, int & fieldCounter);

    /// function to transfer HxLattice3 objects as struct
    HXMATLAB_API int pushField(Engine * eng, HxLattice3 * plattice, int & fieldCounter);

    /// function to transfer HxTime objects as scalar value
    HXMATLAB_API int pushTime(Engine * eng, HxTime * ptime, int & timeCounter);

    /// function to convert a surface into a mxArray
    HXMATLAB_API int pushSurfaceIntoMxArray(const McDArray<int> & indices, HxSurface * psurface, mxArray * surf);

    /// function to transfer a surface to the Matlab workspace
    HXMATLAB_API int pushSurface(Engine * eng, HxSurface * psurface, int & surfCounter);

    /// function to transfer a surfacefield to the Matlab workspace
    HXMATLAB_API int pushSurfaceField(Engine * eng, HxSurfaceField * psurfaceField, int & surfCounter);

    /// function to transfer a lineset to the Matlab workspace
    HXMATLAB_API int pushLineSet(Engine * eng, HxLineSet * plineset, int & lineCounter);

    /// function to transfer an Amira object as struct
    HXMATLAB_API int pushObject(Engine * eng, HxObject * pobject);

};
#endif

/// @}
