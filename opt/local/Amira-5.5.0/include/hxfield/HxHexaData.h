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
#ifndef HX_HEXAFIELD_H
#define HX_HEXAFIELD_H

#include <hxcore/HxInterface.h>
#include <amiramesh/AmiraMesh.h>
#include <amiramesh/HxParamBundle.h>
#include <hxfield/HxHexaGrid.h>
#include <hxfield/HxLoc3Hexa.h>
#include <hxfield/HxFieldWinDLLApi.h>

class HxHexaData;

/// Represents a data grid with regular coordinates.

class HXFIELD_API HxHexaData : public HxInterface
{
    HX_ABSTRACT_HEADER(HxHexaData);

  public:

    /// Specifies how the field is defined
    enum Encoding { PER_VERTEX, PER_HEXA_VERTEX, PER_HEXA };

    /// Constructor.
    HxHexaData(HxHexaGrid* grid, int nDataVar, Encoding e, float* data=0);

    /// Destructor.
    ~HxHexaData();

    /// Returns how the field is encoded.
    Encoding encoding() const { return theEncoding; }

    /// Returns pointer to node data array.
    float* dataPtr() const { return theData; }

    /// Returns number of data variables per vertex/hexahedron.
    int nDataVar() const { return theNDataVar; }

    /// Returns number of data elements (nNodes, nHexa, or 8*nHexa).
    int nDataElements() const;

    /// Returns total number of float values (nDataVar*nDataElements).
    int nValues() const { return nDataElements()*theNDataVar; }

    /// Creates location class for this field.
    HxLoc3Hexa* createLocation();

    /// Returns bounding box of underlying grid.
    void getBoundingBox(float bbox[6]) const;

    /// Returns underlying hexahedral grid.
    HxHexaGrid* grid() const;

    /** Attaches the field to a new grid. It is required that the
        new grid has the same number of nodes or hexahedra, depending
        on the encoding of the field. If this is not the case, the
        new grid will not be connected and the method returns 0. On
        sucess 1 is returned. */
    int setGrid(HxHexaGrid*);

    /// Reads a regular field from an AmiraMesh structure
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Touches the lattice owner and invalidates the stored range.
    void touchMinMax();

    /// Touches the lattice owner.
    void touch();

    // Tcl-command interface.
    virtual int interface_parse(Tcl_Interp* t, int argc, char** argv);

    /// Duplicate lattice.
    virtual HxHexaData* duplicate();

    /// Called by the owner, creates the ports.
    void createPorts(HxObject* owner);

    /** Set the undefined value.
    This value will be avoid during magnitude range computation.
    Internal use only.*/
    void setUndefinedValue(double undefinedValue);

    /**Unset the undefined value use.
    The undefined default value is also reseted to its default value.
    Internal use only.*/
    void unSetUndefinedValue();

    /** Tell if lattice has an undefined value.
    Internal use only.*/
    bool hasUndefinedValue() {return m_hasUndefinedValue;}

    /** Return the undefined value. It's -FLT_MAX by default.
    Internal use only.*/
    double getUndefinedValue() {return m_undefinedValue;}

    /** Computes the range.
    This method won't use undefined values to compute the range if @c discardUndefinedValues is set to true.*/
    void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    /**Interpolation method.
    Return 0 if the data is equal to the undefined value at this location.
    Otherwise, return 1.*/
    static int interpol(HxHexaData*, HxLoc3Hexa*, float*);

    /// Computes the derivative at the given location
    void derivative(HxLoc3Hexa*,float*);

    /// Create a field of matching type and insert struct into it.
    static HxField3* create(HxHexaData* existingField);

    /// compute method that should be called from HxField3 deriven object
    void compute();

  protected:

    HxConnection*   portGrid;
    HxHexaGrid*     theGrid;
    int             theNDataVar;
    float*          theData;
    Encoding        theEncoding;
    int             numNodes;

    bool m_hasUndefinedValue;
    double m_undefinedValue;
};

#endif

/// @}
