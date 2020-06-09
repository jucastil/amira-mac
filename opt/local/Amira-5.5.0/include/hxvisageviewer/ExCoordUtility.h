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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef EX_COORDUTILITY_H
#define EX_COORDUTILITY_H

#include "ExBase.h"

#include <mclib/McVec2i.h>
#include <mclib/McVec2f.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include "VisageViewerWinDLLApi.h"

class VsCamera;
class VsNode;
class VsSlice;
class VsVolume;
class ExBaseViewer;
class McMat4f;
class McLine;
class McBox3f;

/// Compute the 3D point or line that has been picked
extern bool HXVISAGEVIEWER_API pickedPoint(ExBaseViewer* viewer, int x, int y, VsNode* node, McVec3f& pos);
extern bool HXVISAGEVIEWER_API pickedLine(ExBaseViewer* viewer, int x, int y, McLine& line);

/// Methods to be typcially used within ExShapeTools in order to determine whether something has been hit
extern int HXVISAGEVIEWER_API hitPoint(ExBaseViewer* viewer, int inX, int inY, const McDArray<McVec3f> & inPoints, unsigned int tolerance = 5);
extern int HXVISAGEVIEWER_API hitLine(ExBaseViewer* viewer, int inX, int inY, const McDArray<McVec3f> & inPoints, unsigned int tolerance = 3);
extern int HXVISAGEVIEWER_API hitLineSet(ExBaseViewer* viewer, int inX, int inY, const McDArray<McVec3f> & inPoints);

extern void  HXVISAGEVIEWER_API screenPoint(ExBaseViewer* viewer, const McVec3f& pWorld, McVec3f& pScreen);
extern float HXVISAGEVIEWER_API distanceFromLineSegment(ExBaseViewer* viewer, const McVec3f& pw0, const McVec3f& pw1, int x, int y);
extern float HXVISAGEVIEWER_API distanceFromPoint(ExBaseViewer* viewer, const McVec3f& p, int x, int y);
extern float HXVISAGEVIEWER_API  distanceOnScreen(ExBaseViewer* viewer, const McVec3f& pw0, const McVec3f& pw1);
extern Ex::CursorShape HXVISAGEVIEWER_API cursorDependingOnLineSlope(ExBaseViewer* viewer, const McVec3f& pworld1, const McVec3f& pworld2);

extern bool HXVISAGEVIEWER_API computeRotateCenter(ExBaseViewer* viewer, McVec3f& rotateCenter);

extern int HXVISAGEVIEWER_API voxelPrecision(const VsVolume* volume);

/** Depending on the current locale settings, returns a separator for CSV
    such that Excel opens CSV files with that separator correctly.
    Windows only, for Linux returns ','. 
    This function should probably moved somewhere else. */

extern char HXVISAGEVIEWER_API getSeparatorForCSVFormat();

extern McVec3f HXVISAGEVIEWER_API mapScreenToWorld(const McMat4f& tm, const McVec2i& windowSize, const McVec3f& screen);
extern McVec3f HXVISAGEVIEWER_API mapScreenToWorldInv(const McMat4f& tmInv, const McVec2i& windowSize, const McVec3f& screen);
extern McVec3f HXVISAGEVIEWER_API mapWorldToScreen(const McMat4f& tm, const McVec2i& windowSize, const McVec3f& world);
extern McVec3f HXVISAGEVIEWER_API mapScreenToWorld(VsCamera* camera, const McVec2i& windowSize, const McVec3f& screen);
extern McVec3f HXVISAGEVIEWER_API mapWorldToScreen(VsCamera* camera, const McVec2i& windowSize, const McVec3f& world);
extern McVec3f HXVISAGEVIEWER_API mapScreenToFocalPlane(VsCamera* camera, const McVec2i& windowSize, const McVec3f& pixel);

float HXVISAGEVIEWER_API screenUnit(const McMat4f& tm, const McVec2i& windowSize, const McVec3f& world);

/** Returns the center point on the bounding box's face that is most exposed in the direction given
    by \c direction, e.g. for \c direction == McVec3f(1, 0, 0) the method will return the center of 
    the face 
    x == box.getMin()[0] etc.
*/
extern McVec3f HXVISAGEVIEWER_API closestFaceCenter(const McBox3f & box, const McVec3f direction);

#endif // EX_COORDUTILITY_H

/// @}
