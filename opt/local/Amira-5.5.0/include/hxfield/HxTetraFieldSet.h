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
#ifndef TETRA_FIELD_SET_H
#define TETRA_FIELD_SET_H

#include <mclib/McDArray.h>
#include <hxcore/HxSpatialData.h>
#include <amiramesh/HxParamBundle.h>
#include <amiramesh/AmiraMesh.h>
#include <hxfield/HxFieldWinDLLApi.h>
#include <hxfield/HxTetraGrid.h>

/// This class holds multiple fields defined on a tetrahedral grid.

class HXFIELD_API HxTetraFieldSet : public HxSpatialData
{
  HX_DATA_HEADER(HxTetraFieldSet);

  public:
    ///
    enum Encoding { OnNodes=0, OnEdges=1, onTetra=2 };

    /// Constructor.
    HxTetraFieldSet(HxTetraGrid* grid, int nDataVar, Encoding=OnNodes);

    /// Destructor.
    ~HxTetraFieldSet();

    /// Returns bounding box of grid.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Returns underlying tetrahedral grid.
    HxTetraGrid* grid() const { return hxconnection_cast<HxTetraGrid>(portGrid); }

    /// Returns number of data variables.
    int nDataVar() const { return theNDataVar; }

    /// Returns number of channels.
    int nChannels() const { return theData.size(); }

    /// Returns pointer to data array.
    float* dataPtr(int channel=0) const { return theData[channel]; }

    /// Info method.
    virtual void info();

    /// This describes the way how the data is defined.
    Encoding encoding() const { return theEncoding; }

    /// Duplicates the current HxTetraFieldSet object
    virtual HxData *duplicate() const;

    /// Create object from AmiraMesh struct.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

  protected:

    /// Used by duplicate(); copies the needed data
    void copyData(const HxTetraFieldSet &source);

    HxConnection portGrid;
    Encoding theEncoding;
    int theNDataVar;

  public:
    McDArray<float*> theData;
};

/// A set of complex valued electromagnetic fields.

class HXFIELD_API HxTetraEFieldSet : public HxTetraFieldSet
{
  HX_DATA_HEADER(HxTetraEFieldSet);

  public:
    /// Constructor.
    HxTetraEFieldSet(HxTetraGrid* grid);

    /// Destructor.
    ~HxTetraEFieldSet();

    /// Saves field set in AmiraMesh format.
    int saveAmiraMesh(const char* filename);

    /// Duplicates the current HxTetraEFieldSet object
    virtual HxData *duplicate() const;
};

/// A set of real valued temperature fields.

class HXFIELD_API HxTetraTemperatureSet : public HxTetraFieldSet
{
  HX_DATA_HEADER(HxTetraTemperatureSet);

  public:
    /// Constructor.
    HxTetraTemperatureSet(HxTetraGrid* grid);

    /// Destructor.
    ~HxTetraTemperatureSet();

    /// Saves field set in AmiraMesh format.
    int saveAmiraMesh(const char* filename);

    /// Duplicates the current HxTetraTemperatureSet object
    virtual HxData *duplicate() const;
};

/// A set of complex valued vector fields defined by edge elements

class HXFIELD_API HxTetraEdgeElemSet : public HxTetraFieldSet
{
  HX_DATA_HEADER(HxTetraEdgeElemSet);

  public:
    /// Constructor.
    HxTetraEdgeElemSet(HxTetraGrid* grid);

    /// Destructor.
    ~HxTetraEdgeElemSet();

    /// Saves field set in AmiraMesh format.
    int saveAmiraMesh(const char* filename);

    /// Duplicates the current HxTetraEdgeElemSet object
    virtual HxData *duplicate() const;

    /// Create object from AmiraMesh struct.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);
};
    
#endif

/// @}
