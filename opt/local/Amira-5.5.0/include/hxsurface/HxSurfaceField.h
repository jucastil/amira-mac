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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef HX_SURFACE_FIELD_H
#define HX_SURFACE_FIELD_H

#include <amiramesh/AmiraMesh.h>
#include <hxcore/HxSpatialData.h>
#include <hxsurface/HxSurface.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

/** Represents a scalar field on a triangular surface.
*/

class HXSURFACE_API HxSurfaceField : public HxSpatialData
{
  HX_DATA_HEADER(HxSurfaceField);

  public:
    /// How the data is stored.
    enum Encoding {
        /// On the nodes of the surface.
        OnNodes=0, 
        /// On the triangles.
        OnTriangles,
        /// Three data values per triangle, one for each node.
        OnTriangleNodes
    };

    /**
        @param data if not 0, transfers ownership of the data to the object.
        Data must be allocated with malloc.            
    */
    HxSurfaceField(HxSurface* surface, Encoding, int nDataVar, void* data = 0);

    /// Destructor.
    ~HxSurfaceField();

    /// Returns bounding box of lattice.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Returns triangular surface.
    HxSurface* surface() const { return hxconnection_cast<HxSurface>(portSurface); }

    /** Attaches the field to a new surface. It is required that the
        new surface has the same number of nodes or triangles, depending
        on the encoding of the field. If this is not the case, the
        new surface will not be connected and the method returns 0. On
        sucess 1 is returned. */
    int setSurface(HxSurface*);

    /// Returns pointer to node data array.
    float* dataPtr() const { return theData; }

    /// Returns number of data variables per vertex/triangle.
    int nDataVar() const { return theNDataVar; }

    /// Returns number of data elements (nPoints, nTriangles, or 3*nTriangles).
    int nDataElements() const { return numNodes/theNDataVar; }

    /// Returns total number of float values (nDataVar*nDataElements).
    int nValues() const { return numNodes; }

    /// Returns encoding type.
    Encoding getEncoding() const { return encoding; }

    /** Sets encoding type. Causes memory reallocation. If the parameter
        adjustDataValues is true, the existing data values will be adjusted
        to match the new encoding scheme. E.g., if the encoding was OnNodes
        before and is set to OnTriangles, each triangle will be assigned
        the average value of its three node. */
    void setEncoding(Encoding, bool adjustDataValues=false);

    /// Info method
    virtual void info();

    /// Duplicates the current HxSurfaceField object
    virtual HxData *duplicate() const;

    /**
        Test if two fields can be merged. If true, nDataVar and the encoding match.
    */
    bool canMergeField( HxSurfaceField& other);

    /**
        Merges the current HxSurfaceField with another one and also merges the surfaces of the two fields.
        Caution: If the surface has more than one field only this field will be merged, all other fields
        will the not have enough data items.
    */
    virtual void merge( HxSurfaceField &other );

    /**
        merges the the surface field with another one. Only merges the field, not the corresponding surfaces.
    */
    void mergeFieldOnly( HxSurfaceField& other);


    /// Saves surface field in AmiraMesh/ascii
    int saveASCII(const char* filename);

    /// Saves surface field in AmiraMesh/binary
    int saveBINARY(const char* filename);

    /// Saves surface field in AmiraMesh.
    int saveAmiraMesh(const char* filename, int ascii);

    /// AmiraMesh reader.
    static int readAmiraMesh(AmiraMesh* m, const char* filename); 

    /// This is called when another surface is connected. 
    virtual void update(); 

    /// Reacts on changes of the surface, modifies controllingData.
    virtual void compute();

    /** Virtual function which is called whenever the input source
        has changed. theData and numNodes is already set up to
	the correct size when updateData() is called. */
    virtual void updateData();

    /** Create a surface field of the right type.
    HxSurface does not contain the undefined value so,
    you have to set it after having call this method.
    */
    static HxSurfaceField* create(HxSurface* surface, Encoding encoding,
        int nDataVar, void* data = 0);

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char** argv);
	    
    /** adapts current field to be an identical copy of @c source
        calls copyData and sets surface to @c source surface
    */    
    void copySurfaceField (const HxSurfaceField &source);

  protected:

    /// Used by duplicate(); copies the needed data
    void copyData(const HxSurfaceField &source);

    /** Here is how the range is computed : 
        The minimum and maximum of all data values
        is returned including data values of points not referenced by any
        line.
    */
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    HxConnection    portSurface;
    int		        theNDataVar;
    int		        numNodes;
    float*	        theData;
    Encoding	    encoding;
};

#endif

/// @}
