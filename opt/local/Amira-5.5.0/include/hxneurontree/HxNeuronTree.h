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

/// @addtogroup hxneurontree hxneurontree
/// @{
#ifndef _HXNEURONTREE_H
#define _HXNEURONTREE_H

#include <mclib/McSmallArray.h>
#include <hxcore/HxVertexSet.h>
#include <hxlines/HxLineSetInterface.h>
#include <hxcolor/HxRangeSet.h>

#include "HxNeurontreeWinDLLApi.h"

class AmiraMesh;
class HxScalarField3;
class HxModule;

class HXNEURONTREE_API HxNeuronTree : public HxVertexSet {

    HX_HEADER(HxNeuronTree);

private:
    class HxRangeSetDataImpl : public HxRangeSetData {
      public:
        HxRangeSetDataImpl(HxNeuronTree* o)
            : HxRangeSetData(o->getOwner(), McInterfaceOwner::STATIC_IFACE)
            , mOuter(o)
        {}

        /** Returns true if the min / max values of the specified data set were
            determined successfully, and false otherwise. */
        virtual bool getRangeSet(float& min, float& max, int setId);

      private:
        HxNeuronTree* mOuter;
    };
    friend class HxRangeSetDataImpl;

  public:

    int isOfType(const McTypeInfo* t) const {
        return HxVertexSet::isOfType(t);
    }

    ///
    McTypedObject* getInterface(const McTypeInfo* t);

    /// Constructor.
    HxNeuronTree();

    // virtual methods from HxVertexSet:

    ///
    virtual McVec3f* getCoords() const { return (McVec3f*) points.dataPtr();}

    ///
    virtual int getNumPoints() const {return points.size();}

    // virtual methods from HxLineSetInterface:

    ///
    int getNumLines() { return(lines.size()); };

    /// number of points in i-th line segment.
    virtual int getLineLength(int i) {return lines[i].points.size();}

    /// Get p-th point (index) of l-th line.
    virtual int getLineVertex(int l, int p) {return lines[l].points[p];}

    ///
    virtual void setNumPoints(int n);

    ///
    virtual void setNumDataValues(int n);

    /// add a line consisting of n points with indices
    /// to whichPoints to line array at position pos
    /// default for pos is end of array (pos = -1)
    virtual void addLine(int n, int* whichPoints,
                         int pos=-1);

    virtual void deleteLine(int which);

    virtual void removeLineVertex(int l, int p);

    virtual void addPoints(McVec3f* newPoints, int n=1);

    /// add an additional vertex (index = p) to line l
    /// at position pos, default for pos is end of array
    virtual void addLineVertex(int l, int p, int pos=-1);


    /// Subclass representing a single polyline.
    struct Line {

        /** Indices to Vertex coordinates.  For closed lines the first
            index should be replicated as last one. */
        McDArray<int> points;
        int level;
        Line() {
            level = 0;
        }
        ///
        Line& operator=(const Line& line) {
            points = line.points;
            level = line.level;
            return *this;
        }
    };

    void getSubTree(int line, McDArray<int>& lines);
    ///
    static int read(const char *fileName);

    ///
    int load(const char *fileName);

    ///
    int save(const char *fileName);

    ///
    void getBoundingBox(float bbox[6]) const;

    ///
    void setNumLines(int n) ;

    ///
    Line& getLine(int i) { return (lines[i]); }

    /// Number of data values per vertex.
    int getNumDataValues() { return data.size(); }

    ///
    void info();

    /// Duplicates the current HxNeuronTree object
    virtual HxData *duplicate() const;

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    McVec3f& getPoint(int line, int point) {
        return points[lines[line].points[point]];
    }

    ///
    float getData(int line, int point, int dataVal) {
        return data[dataVal][lines[line].points[point]];
    }

    ///
    float* getData(int set) {
        return data[set].dataPtr ();
    }


    ///
    void setData(int line, int point, int dataVal, float dat) {
            data[dataVal][lines[line].points[point]] = dat;
    }



    /// array containing line data
    McDArray<Line> lines;

    /** Array of vertex data values in sequential order. */
    McDArray<McDArray<float> > data;

    /// Array of vertex coordinates
    McDArray<McVec3f> points;

    /// Move point idx to beginning of list indicating that this is the root
    /// of the neuron (soma).
    void setRoot(int idx);

    static int readAmiraMesh(AmiraMesh* m,const char* filename);
    int saveAmiraMesh(const char* filename);

    ///
    void splitLine(int lidx, int pidx);

    ///
    void merge(HxNeuronTree* o);

    ///
    void autoJoinLines();

    /// remove all points, which are not referenced by a line
    void cleanup();

    void removeDuplicateSegments();

    ///
    void propagateTopology(int lidx, int level);
    ///
    void computeTopology();

    /// Computes a graph consisting of the branching points and end points and
    /// stores edge information in HxNeuronTree::edge.
    /// @see makeTree()
      int makeGraph();

    /// Computes a spanning tree of a graph constructed my makeGraph(). Data set 3
    /// contains for every vertex the index of its predecessor vertex in the tree or
    /// -1 if this vertex does not belong to the tree. Traversing starts at the root
    /// (vertex 0).
    /// @see setRoot()
    /// @see makeGraph()
    int makeTree();

    void addSynapse( int section, int line, int point );
    void removeSynapse( int section, int line, int point );
    void removeSynapses();
    void restoreSynapses(); // from parameters, after loading dataset
    ///
    //void deleteLine(int which);
    enum {UNUSED, INNERPOINT, ENDPOINT, BRANCHING, SYNAPSE};
    struct PointInfo {
        // type of point
        char type;
        // index of line this point belongs to. For branching points
        // this is an index to the list of line-lists
        int line;
        // The number that this branching or endpoint has in the graph
        int vertex;

        PointInfo() {
            line=-1;
            type = UNUSED;
        }
    };

    /// Infos about an edge in the graph.
    struct EdgeInfo {
      int line, from, to, pre, id;
      float length;
      bool hasSynapses;

      EdgeInfo()
      {
        line = from = to = pre = id = -1;
        length = 0;
        hasSynapses = false;
      }
      EdgeInfo( int aline, int afrom, int ato )
          : line(aline),from(afrom),to(ato), pre(-1), id(-1){hasSynapses = false;};

      EdgeInfo( int aline, int afrom, int ato, float l )
          : line(aline),from(afrom),to(ato), pre(-1), id(-1), length(l){hasSynapses = false;};
    };

    struct Synapse
    {
      int section, line, point;
      Synapse() : section(-1), line(-1), point(-1){};
      Synapse( int asection, int aline, int apoint ) : section(asection), line(aline), point(apoint){};
    };

    McDArray<PointInfo> pointTypes;
    McDArray<McSmallArray<int,2> > linesPerBP;
    /// Contains for each vertex a list of edges to all connected branching or end points.
    McDArray<McSmallArray<EdgeInfo,6> > edge;
    McDArray<EdgeInfo> section;
    McDArray<Synapse> synapse;

    void updatePointTypes();
    void smooth(float f=0.5, int zonly=0);

    void computeData(HxScalarField3*, int set = 0);
    void mapPoints(int* newIdx, int mapcoords=1);
    protected:

    /// Used by duplicate(); copies the needed data
    void copyData(const HxNeuronTree &source);

    void init();
    int nDataVals;
  protected:
    HxLineSetInterface* mIface;
    ~HxNeuronTree();

  private:
    HxRangeSetDataImpl mRangeSetData;
};
#endif

/// @}
