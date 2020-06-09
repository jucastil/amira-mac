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

/// @addtogroup hxsurfacepath hxsurfacepath
/// @{
#ifndef HX_LINE_SET_TO_SURFACE_PATH_INTERFACE_H
#define HX_LINE_SET_TO_SURFACE_PATH_INTERFACE_H

#include "HxSurfacePathSet.h"
#include "hxsurfacepathAPI.h"
#include <hxlines/HxLineSetInterface.h>

class HXSURFACEPATH_API HxSurfacePathToLineSetInterface : public HxLineSetInterface {

    HX_HEADER(HxSurfacePathToLineSetInterface);

protected:

    /// Returns total number of vertices of all lines.
    virtual int getNumPoints() const;

    /// Returns total number of polylines.
    virtual int getNumLines();

    /// Returns the number of points in i-th line.
    virtual int getLineLength(int i);

    /// Returns index of p-th point in l-th line.
    virtual int getLineVertex(int l, int p);

    /// Deletes the specified line.
    virtual void deleteLine(int which);
    /// remove unused points or empty lines
    virtual void cleanup();

    // Computes average distance between vertices in specific line.
    virtual float getAveragePointSpacing(int l);

    /// Resizes points array to numPoints.
    virtual void setNumPoints(int numPoints);

    /** Adds a new line to the line set. The line consists of @c n
        points.  @c points specifies the index of each point in the
        global coordinate array returned by getCoords(). @c pos
        specifies the index of the new line. If @c pos is -1 the new
        line will be appended after all existing lines.
    */
    virtual void addLine(int n, int* whichPoints, int pos=-1);

    /// Delete point @c p of line @c l.
    virtual void removeLineVertex(int l, int p);

    /** Adds an additional vertex to line @c l. The second argument @c
        p is the index of the referenced point. @c pos specifies the
        position of the new vertex within the line. If @c pos is -1
        the new vertex will be appended after all other vertices of
        the line.
    */
    virtual void addLineVertex(int l, int p, int pos=-1);

    /** Appends new points at the end of the global vertex array. If
        the line set contained @c num points before the indices of the
        added points will be @c num ... @c num+n-1.
    */
    virtual void addPoints(McVec3f* points, int n=1);

    /// Returns number of data variables per point.
    virtual int getNumDataValues();

    /// Sets number of data sets.
    virtual void setNumDataValues(int n);

    /// Returns d-th data value at p-th point in l-th line.
    virtual float getData(int l, int p, int d);

    /** Returns point to data set array. There are as many data sets
        as returned by getNumDataValues(). Each set is stored in a
        separate array with as many entries as points.
    */
    virtual float* getData(int set);

    /// Set d-th data val at p-th point in l-th line to value val.
    virtual void setData(int l, int p, int d, float val);

    /// Returns the transformation.
    virtual SoTransform* getTransform() const;

    /// Returns the transformation.
    virtual void getTransform(SbMatrix& matrix) const;

private:

    HxSurfacePathSet* theOwner;
    HxSurfacePathToLineSetInterface(){};
    HxSurfacePathSet* obj() const;

public:
    HxSurfacePathToLineSetInterface( HxSurfacePathSet* sps)
    {
        this->setOwner(sps);
        theOwner=obj();
    };

    /// Returns pointer to vertex coordinates.
    virtual McVec3f* getCoords() const;
};

#endif // HX_LINE_SET_TO_SURFACE_PATH_INTERFACE_H

/// @}
