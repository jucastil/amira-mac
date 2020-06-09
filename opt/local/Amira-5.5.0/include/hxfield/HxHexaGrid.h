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
#ifndef HX_HEXA_GRID_H
#define HX_HEXA_GRID_H

#include <hxfield/HxFieldWinDLLApi.h>
#include <hxcore/HxVertexSet.h>
#include <hxfield/HexaGrid.h>

/// This class combines a standalone HexaGrid with Amira's HxVertexData.
class HXFIELD_API HxHexaGrid : public HxVertexSet, public HexaGrid {

    HX_HEADER(HxHexaGrid);

  public:
    /// Constructor.
    HxHexaGrid();

    /// Constructor.
    HxHexaGrid(McVec3f* coords,int npoints,int hexas[][8],int nHexas);

    //@name: Overloaded methods.
    //@{

    /// From HxVertexData...
    virtual int getNumPoints() const;
    
    /// From HxVertexData...
    virtual McVec3f* getCoords() const;

    /// From HxVertexSet...
    virtual void applyTransform(const SbMatrix& transform);

    /// Returns bounding box of grid.
    virtual void getBoundingBox(float b[6]) const;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* interpreter, int argc, char** argv);

    /// Prints info about the grid.
    virtual void info();

    /// Duplicates this class instance.
    virtual HxData *duplicate() const;

    //@}

    //@name: IO methods.
    //@{

    /// Creates grid from AmiraMesh struct.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Read grid from AmiraMesh file.
    static int readAmiraMesh(const char* filename);

    /// Save grid in AmiraMesh ascii or binary format.
    int saveAmiraMesh(const char* filename, int ascii);

    /// Save grid in AmiraMesh binary format.
    int saveAmiraMeshBinary(const char* filename);

    /// Save grid in AmiraMesh ascii format.
    int saveAmiraMeshAscii(const char* filename);

    //@}

    /// Add another hexahedral grid to this one.
    void add(HxHexaGrid& other, int removeDuplicated=1);

    /** Removes points with identical coordinates. This method also updates
        attached data fields with data values defined on nodes. Data values
        on duplicated points will be averaged. If @c tol is non-zero points
        are considered to be equal even if their coordinates are not more
        than @c tol apart. The method returns the number of removed
        duplicated points. If duplicated points were removed the grid is
        touched but downstream objects will not be fired automatically. */
    int removeDuplicatePoints(float tol, McProgressInterface* progress=0);

    /// Looks for grid with same number of elements as specified in @c m.
    static HxHexaGrid* findMatchingGrid(AmiraMesh* m, const char* filename);

  protected:
    ~HxHexaGrid();

    /// Used by duplicate(), copies the needed data
    void copyData(const HxHexaGrid &source);
};

#endif

/// @}
