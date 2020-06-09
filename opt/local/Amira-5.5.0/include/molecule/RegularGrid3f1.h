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

/// @addtogroup molecule molecule
/// @{
#ifndef RegularGrid3f1_H
#define RegularGrid3f1_H

#include "MoleculeWinDLLApi.h"

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McBox3f.h>
#include <mclib/McVec3i.h>

/** /brief Regular 3-dimensional grid containing a scalar field of type float.

    This class is used in instances where use of hxfield/HxRegScalarField3 needs to be avoided to
    ensure independence from the amira libraries.
*/

class MOLECULE_API RegularGrid3f1 {
private:
    // bounding box
    McBox3f bbox;
    // grid dimensions (number of points in x y and z direction)
    McVec3i dim;
    // field values
    McDArray<float> data;
    // spacing between neighboring grid notes in each direction (all equal for uniform grids)
    McVec3f spacing;
public:
    ///
    RegularGrid3f1(const McBox3f& b,const McVec3i& d);
    /** Creates a uniform grid with the center, and the uniform spacing */
    RegularGrid3f1(const McVec3f& center,const McVec3i& d,float spacing);
    /// initialize data with 0
    void clear();
    /// returns range of data
    void computeRange(float& min,float& max) const;
    /// returns whether 2 grids have same bounding box and dimension
    bool isSameGrid(const RegularGrid3f1& g) const;
    /// returns overall number of data values
    int getSize() const { return data.size();}
    /// converts grid index into position in space
    void getPos(int ix,int iy, int iz,McVec3f& p) const {p[0]=bbox[0]+ix*spacing[0];p[1]=bbox[2]+iy*spacing[1];p[2]=bbox[4]+iz*spacing[2];}
    /// converts absolute index to position space
    void getPos(int ix,McVec3f& p) const;
    /// converts grid index into absolute index of data elements
    int getIx(int ix,int iy,int iz) const {return ix+(iy + iz*dim[1])*dim[0];}
    /// converts absolute index into grid index
    void getIx(int i,int& ix,int& iy,int& iz) const;
    /// sets value by absolute index
    void setValue(int index,float v) {data[index]=v;}
    /// returns value by absolute index
    float getValue(int index) const {return data[index];}
    /// Returns the value obtained from linear interpolation between neighboring points
    float getLinearInterpolatedValue(const McVec3f& v) const;
    /// sets value by grid indices
    void setValue(int ix,int iy,int iz,float v) {setValue(getIx(ix,iy,iz),v);}
    /// returns value by grid indices
    float getValue(int ix,int iy,int iz) const {return getValue(getIx(ix,iy,iz));}
    /// returns pointer to grid data
    const float* getValues() const {return data.dataPtr();}
    float* getValues() { return data.dataPtr();}
    /// returns bounding box
    void getBBox(McBox3f& b) const { b = bbox;}
    /// returns dimenstion
    void getDim(McVec3i& d) const { d = dim;}
    /// returns voxel size 
    void getSpacing(McVec3f& v) const {v = spacing;}
    /// initializes grid with given value
    void fill(float v) {data.fill(v);}
    /** finds all indices of grid points which are within distance d from given point */
    void getIxCloseToPoint(const McVec3f& point,float d,McDArray<int>& indices) const;
    /** finds all indices of grid points within given bounding box */
    void getIxWithinBBox(const McBox3f& box,McDArray<int>& indices) const;
};

#endif

/// @}
