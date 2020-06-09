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

/// @addtogroup hxcluster hxcluster
/// @{
#ifndef HX_CLUSTER_H
#define HX_CLUSTER_H

#include <hxcore/HxVertexSet.h>
#include <hxcolor/HxRangeSet.h>

#include "HxClusterWinDLLApi.h"

class AmiraMesh;
class HxModule;
class McBitfield;

/** This class represents a set of points with associated data values.
    The data values are organized in columns. The number of data
    columns is variable. The values of a data column can be stored
    as bytes, shorts, ints, or floats.

    In addition to data columns also an arbitrary number of label
    columns can be defined. A label column stores a string for each
    point of the HxCluster object. */

class HXCLUSTER_API HxCluster : public HxVertexSet {

    HX_HEADER(HxCluster);

private:
    class HxRangeSetDataImpl : public HxRangeSetData {
      public:
        HxRangeSetDataImpl(HxCluster* o)
            : HxRangeSetData(o->getOwner(), McInterfaceOwner::STATIC_IFACE)
            , mOuter(o)
        {}

        /** Returns true if the min / max values of the specified data set were
            determined successfully, and false otherwise. */
        virtual bool getRangeSet(float& min, float& max, int setId);

      private:
        HxCluster* mOuter;
    };
    friend class HxRangeSetDataImpl;

  public:

    /// Constructor.
    HxCluster();

    /// Returns number of points.
    virtual int getNumPoints() const;

    /// Returns pointer to coordinate vectors.
    virtual McVec3f* getCoords() const;

    /// Transform the vertices.
    virtual void applyTransform(const SbMatrix& transform);

    /// Returns number of data columns.
    int getNumDataColumns() const { return dataColumns.size(); }

    /// Returns number of label columns.
    int getNumLabelColumns() const { return labelColumns.size(); }

    /** Returns index of data column with name @c dataColumnName. 
        Returns -1 if no such column exists.*/
    int getDataColumnIndex(const McString& dataColumnName) const;

    /** Returns a text symbol identifying the specified column. Usually,
        the method simply returns @c dataColumns[col].symbol.dataPtr().
        However, if no symbol is defined a new one will be created from
        the name of the data column. If no name is defined NULL is
        returned. */
    const char* getSymbol(int col);

    /// Read routine.
    static int readPSI(const char *filename);

    /*  Try to read extra header info. This method is called in readPSI().
        You may overload the method is a derived class if you wish to
        extend the PSI file format. */
    virtual int tryReadExtraHeader(const char* str) {return 1;}

    /// Write routine.
    int writePSI(const char *filename);

    /// Read AmiraMesh format.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Write AmiraMesh format.
    int writeAmiraMesh(const char* filename);

    /// Returns bounding box of point cluster.
    void getBoundingBox(float bbox[6]) const;

    /// Overloaded info method.
    virtual void info();
    
    /// Copies all data and parameters
    void copyData(const HxCluster& source);

    /// Overloaded duplicate method.
    virtual HxData* duplicate() const;

    /// Overloaded parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Adjusts the number of points. The method also updates the length of
        all data columns stored in @c dataColumns as well as the length of
        the @c ids array. If numAtoms is -1 the number of points is not
        changed but only the length of the data columns is updated. */
    void resize(int numAtoms=-1);

    /** Adjusts the number of data columns. The argument p determines the
        primitive data type of newly created data columns. If the new
        number of data columns is smaller than the previous one columns
        will be deleted (last ones first). In this case p has no effect. */
    void setNumDataColumns(int n, McPrimType p=McPrimType::mc_float);

    /** Adjusts the number of label columns. If the new
        number of label columns is smaller than the previous one columns
        will be deleted (last ones first). */
    void setNumLabelColumns(int n);

    /** This method computes the bounding box of the point cluster as well
        as the minimum and maximum values in each data column and the minimum
        and maximum id stored in @c ids. The method should be called after
        points have been added or removed or after any other relevant
        update. */
    void computeBounds();

    /// Computes connectivity information.
    void computeConnectivity();

    /// Represents a data column.
    struct HXCLUSTER_API DataColumn {
        /** Constructor, default primType is float. No memory is allocated.
            You may append a new empty data column to the dynamic array
            @c dataColumns, adjust the primitive data type as required, and
            then call @c HxCluster::resize() in order to allocate memory. */
        DataColumn();

        /// Destructor, frees all memory.
        ~DataColumn();

        /// Name of a data column.
        McString name;

        /// Symbol identifying the column.
        McString symbol;

        /// Primitive data type.
        McPrimType primType;

        /// Array of tokens used for enumerated data.
        McDArray<McString> tokens;

        /// Minimum data value casted to float.
        float min;

        /// Maximum data value casted to float.
        float max;

        /// Pointer to data array, must not be freed.
        void* data;

        /// Stores the number of values in data (should be equal to getNumPoints())
        int numDataValues;

        /// Set value for i-th point if primtype is byte.
        void setByte(int i, int val) { ((unsigned char*)data)[i] = val; }

        /// Set value for i-th point if primtype is short.
        void setShort(int i, int val) { ((short*)data)[i] = val; }

        /// Set value for i-th point if primtype is short.
	///@test GW: should be OK. Side effects?
        void setUShort(int i, int val) { ((unsigned short*)data)[i] = val; }

        /// Set value for i-th point if primtype is int.
        void setInt(int i, int val) { ((int*)data)[i] = val; }

        /// Set value for i-th point if primtype is float.
        void setFloat(int i, float val) { ((float*)data)[i] = val; }

        /// Get value for i-th point if primtype is byte.
        unsigned char getByte(int i) const { return ((unsigned char*)data)[i]; }

        /// Get value for i-th point if primtype is short.
        short getShort(int i) const { return ((short*)data)[i]; }

        /// Get value for i-th point if primtype is short.
        short getUShort(int i) const { return ((unsigned short*)data)[i]; }

        /// Get value for i-th point if primtype is int.
        int getInt(int i) const { return ((int*)data)[i]; }

        /// Get value for i-th point if primtype is float.
        float getFloat(int i) const { return ((float*)data)[i]; }
    };

    /// Represents a label column.
    struct HXCLUSTER_API LabelColumn {

        /// Name of a label column.
        McString name;

        /** Stores the labels of this column. The size of this array matches
            the number of points of the cluster as returned by getNumPoints(). */
        McDArray<McString> data;
    };

    /// Stores an id for each point.
    McDArray<int> ids;

    /// Stores the point coordinates.
    McDArray<McVec3f> points;

    /// Stores the data columns.
    McDArray<DataColumn> dataColumns;

    /// Stores connectivity information.
    McDArray<int> connectivity;

    /// Stores the label columns.
    McDArray<LabelColumn> labelColumns;

    float boundingBox[6];
    int dummy, step, minId, maxId;

    // Export points according to selection
    virtual HxCluster* exportPoints(const McBitfield& selection, int numSelected);

    virtual McString getLoggingInfo();

private:
    HxRangeSetDataImpl mRangeSetData;
};

#endif

/// @}
