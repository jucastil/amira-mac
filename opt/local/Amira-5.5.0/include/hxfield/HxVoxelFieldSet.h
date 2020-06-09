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
#ifndef HX_VOXEL_FIELD_SET_H
#define HX_VOXEL_FIELD_SET_H

#include <mclib/McDArray.h>
#include <hxcore/HxSpatialData.h>
#include <hxfield/HxUniformCoord3.h>

/// This class holds multiple fields defined on a voxel grid.

class HXFIELD_API HxVoxelFieldSet : public HxSpatialData
{
  HX_DATA_HEADER(HxVoxelFieldSet);

  public:
    /// Constructor.
    HxVoxelFieldSet(HxUniformCoord3* coord, int nDataVar);

    /// Destructor.
    ~HxVoxelFieldSet();

    /// Returns bounding box of grid.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Returns pointer to coordinate structure.
    HxUniformCoord3* coord() const { return theCoords; }

    /// Returns number of data variables.
    int nDataVar() const { return theNDataVar; }

    /// Returns number of channels.
    int nChannels() const { return theData.size(); }

    /// Returns pointer to data array.
    float* dataPtr(int channel=0) const { return theData[channel]; }

    /// Info method.
    virtual void info();

    /// Duplicates the current HxVoxelFieldSet object
    virtual HxData *duplicate() const;

  protected:

    /// Used by duplicate(); copies the needed data
    void copyData(const HxVoxelFieldSet &source);
  
    HxUniformCoord3* theCoords;
    int theNDataVar;

  public:
    McDArray<float*> theData;
};

/// A set of complex valued electromagnetic fields.

class HXFIELD_API HxVoxelEFieldSet : public HxVoxelFieldSet
{
  HX_DATA_HEADER(HxVoxelEFieldSet);

  public:
    /// Constructor.
    HxVoxelEFieldSet(HxUniformCoord3* coord);

    /// Destructor.
    ~HxVoxelEFieldSet();

    /// Duplicates the current HxVoxelEFieldSet object
    virtual HxData *duplicate() const;
};

#endif

/// @}
