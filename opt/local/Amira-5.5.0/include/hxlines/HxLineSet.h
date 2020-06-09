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

/// @addtogroup hxlines hxlines
/// @{
#ifndef _HXLINESET_H
#define _HXLINESET_H

#include <hxcore/HxVertexSet.h>
#include <hxlines/HxLinesWinDLLApi.h>
#include <hxlines/HxLineSetInterface.h>
#include <hxcolor/HxRangeSet.h>

class AmiraMesh;
class HxModule;

/** This class represents a set of polylines. Optionally one or more
    floating point data values can be stored with each vertex. */

class HXLINES_API HxLineSet : public HxVertexSet {

    MC_HEADER(HxLineSet);

private:
    class HxRangeSetDataImpl : public HxRangeSetData {
      public:
        HxRangeSetDataImpl(HxLineSet* o)
            : HxRangeSetData(o->getOwner(), McInterfaceOwner::STATIC_IFACE)
            , mOuter(o)
        {}

        /** Returns true if the min / max values of the specified data set were
            determined successfully, and false otherwise. */
        virtual bool getRangeSet(float& min, float& max, int setId);

      private:
        HxLineSet* mOuter;
    };
    friend class HxRangeSetDataImpl;

  public:
    /// Subclass representing a single polyline.
    struct Line {
        /** Indices to vertex coordinates. For closed lines the first
            index should be duplicated at the end. */
        McDArray<int> points;

        /// Assignment operator.
        Line& operator=(const Line& line) {
            points = line.points;
            return *this;
        }
    };

    /** Constructs an empty line set. @c nDataVals specifies the number
        of floating point data values per vertex. @c numLinesHints can be
        used to pre-allocate memory for that many lines. */
    HxLineSet(int nDataVals=0, int numLinesHint=1);

    /**@name Virtual methods from HxVertexSet */
    //@{

    /// Returns pointer to vertex coordinates.
    virtual McVec3f* getCoords() const { return (McVec3f*) points.dataPtr();}

    /// Returns total number of vertices of all lines.
    virtual int getNumPoints() const { return points.size(); }

    //@}

    /// Returns total number of lines.
    int getNumLines() { return(lines.size()); };

    /** Sets the total number of lines. New lines will be empty, i.e., they
        do not contain any vertices. */
    void setNumLines(int n);

    /// Returns i-th line.
    Line& getLine(int i) { return (lines[i]); }

    /// Returns number of points in i-th line segment.
    virtual int getLineLength(int i) { return lines[i].points.size(); }

    /**
     * Returns the i-th line length.
     */
    virtual float getLineCurveLength(int i);

    /// Get index of point @c p in line @c l..
    virtual int getLineVertex(int l, int p) {return lines[l].points[p];}

    /** Adds a new line to the line set. The line consists of @c n points.
        @c points specifies the index of each point in the global coordinate
        array returned by getCoords(). @c pos specifies the index of the
        new line. If @c pos is -1 the new line will be appended after all
        existing lines. */
    virtual void addLine(int n, int* points, int pos=-1);

    /**
        Adds all lines from @c other. Both line sets must have the same
        number of data items, otherwise the addition of lines fails.
        @return success of line addition.
    */
    bool addLineSet(HxLineSetInterface* other);

    /**
       Clear the lineset.
       This clears internal arrays.  Memory, however, might stay allocated.
    **/
    void clear();

    /**
       Clear the lineset.
       This clears internal arrays and deallocates memory.
    **/
    void clearAndFree();

    /** Sets the number of points of the line set. The coordinates of new
        points need to be initialized afterwards. They can be accessed
        using the method getCoords(). Care must be taken that only existing
        points are referenced by the lines, i.e., no point index must be
        bigger than @c n-1. */
    virtual void setNumPoints(int n);

    /// Deletes the specified line.
    virtual void deleteLine(int which);

    /// Number of data values per vertex.
    int getNumDataValues() const { return data.size(); }

    /** Adjusts the number of data values per vertex. All vertices/points 
        need to be added to the LineSet before the number of values can be 
        changed. Alternatively, this function can be called after the addition 
        of each vertex/point. New data values need to be initialized afterwards
        by the caller. */
    virtual void setNumDataValues(int n);

    /** Delete point @c p of line @c l. The method does not remove the point
        from the global vertex array even if the point is not referenced by
        any other line. Therefore the number of points returned by
        getNumPoints() does not change, */
    virtual void removeLineVertex(int l, int p);

    /** Appends new points at the end of the global vertex array. If the
        line set contained @c num points before the indices of the added
        points will be @c num ... @c num+n-1. */
    virtual void addPoints(McVec3f* points, int n=1);

    /** Adds an additional vertex to line @c l. The second argument @c p
        is the index of the referenced point. @c pos specifies the position
        of the new vertex within the line. If @c pos is -1 the new vertex
        will be appended after all other vertices of the line. */
    virtual void addLineVertex(int l, int p, int pos=-1);

    /**
         Removes points with identical coordinates. This method also updates
         the data fields. Data values on
         duplicated points will not be averaged, the data value of the last
         occurence of a duplicated point will be used instead. If @c tol is
         non-zero points are considered to be equal even if their coordinates
         are not more than @c tol apart. The method returns the number of
         removed duplicated points. If duplicated points were removed the
         lineset is touched but downstream objects will not be fired
         automatically.
    */
    int removeDuplicatePoints(float tolerance, McProgressInterface* progress=0);

    /** Smoothes the LineSet by replacing the coordinates of each vertex by the
        weighted average of its neighboring vertices. The bigger the float parameter,
        the bigger the weight of the neighboring vertices 
        and therefore, the smoother the line.
    */
    virtual void smoothLineSet(float f);

    virtual void cleanup() ;
    /// Returns box enclosed by all referenced points.
    void getBoundingBox(float bbox[6]) const;


    /// Duplicates the current HxLineSet object
    virtual HxData *duplicate() const;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Returns the coordinates of point @c point of line @c line. No range
        check is performed. */
    McVec3f& getPoint(int line, int point) {
        return points[lines[line].points[point]];
    }

    /** const version of getPoint(int line, int point).
      */
    const McVec3f& getPoint(int line, int point) const {
        return points[lines[line].points[point]];
    }

    /** Returns data value @c set of point @c point of line @c line. No range
        check is performed. */
    float getData(int line, int point, int set) {
        return data[set][lines[line].points[point]];
    }

    /** Returns pointer to array storing the data values. In total there are
        @c n sets of data values, where @c n is returned by getNumDataValues().
        Each set is stored in a separate array which has as many entries as
        there are points. */
    float* getData(int set) {
        return data[set].dataPtr ();
    }

    /// Sets a data value. No range check is performed.
    void setData(int line, int point, int set, float dat) {
        data[set][lines[line].points[point]] = dat;
    }

    /// Array containing the lines.
    McDArray<Line> lines;

    /** Array of data values. In total there are @c n sets of data values,
        where @c n is returned by getNumDataValues(). Each set is stored in a
        separate array which has as many entries as there are points. In
        order to access data value 1 point 27 use @c data[1][27]. */
    McDArray<McDArray<float> > data;

    /// Array of vertex coordinates
    McDArray<McVec3f> points;

    /// Read a line set from an AmiraMesh struct and adds it to the object pool.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Writes the line set into an AmiraMesh file.
    int saveAmiraMesh(const char* filename);

    /** Save a data object with a HxLinesetInterface as HxLineSet.
     */
    static int saveAmiraMeshBinary(HxLineSetInterface *lines, const char* filename);

    /** Save a data object with a HxLinesetInterface as HxLineSet.
     */
    static int saveAmiraMeshASCII(HxLineSetInterface *lines, const char* filename);
    /// Reads a line set from a LineSet file (obsolete).
    static int read(const char *filename);

    /// Reads a line set from a LineSet file (obsolete).
    int load(const char *filename);

    /// Writes the line set into a LineSet file (obsolete).
    int save(const char *filename);

    /** Checks if the point indices of all lines are valid. If a point with
        a negative index or with an index larger or equal than the value
        returned by getNumPoints() is reference the index will be replaced
        by zero. The method returns true if all indices were consistent,
        and false otherwise. */
    bool consistencyCheck(bool verbose=true);

    HxLineSetInterface* getLineSetInterface(void) const { return mIface; }

    virtual McString getLoggingInfo();

  protected:
    virtual void info();
  /* The minimum and maximum of all data values is returned including data
     values of points not referenced by any line.
  */
  virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    ~HxLineSet();

    void copyData(const HxLineSet &source);
    void init();

    static int saveAmiraMeshInternal(HxLineSetInterface *lines, const char* filename, int ascii);

    HxLineSetInterface* mIface;

  private:
    HxRangeSetDataImpl mRangeSetData;
};

#endif

/// @}
