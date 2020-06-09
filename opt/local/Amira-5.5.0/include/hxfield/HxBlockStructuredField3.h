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
#ifndef HX_BLOCK_STRUCTURED_FIELD_3_H
#define HX_BLOCK_STRUCTURED_FIELD_3_H

#include <hxcore/HxConnection.h>

#include <hxfield/HxScalarField3.h>
#include <hxfield/HxVectorField3.h>
#include <hxfield/HxRegScalarField3.h>

#include "HxBlockStructuredGrid.h"

#include "HxFieldWinDLLApi.h"

class HxLoc3Block;

class HxLocation3;

/** Common Implementation for (at least) Vector and Scalar fields of Block
    structured fields.  Because the HxVectorField3 and HxScalarField3 are not
    interfaces, we use this template-based inheritance construct. TFieldType is
    either HxScalarField3 or HxVectorField3.
*/
template<class TFieldType>
class HxBlockStructuredField3 : public TFieldType
{
public:
    typedef HxBlockStructuredField3<TFieldType> TBlockClassName;

    /** Construct field.  The number of fields must match the number of zones,
        and the fields must have the same coordinates as the grid zones.

        @pre grid->getNumZones() == nfields.
        @pre grid->getZone(i) == mcinterface_cast<HxLattice3>(fields[i]).coords().
      */
    HxBlockStructuredField3(HxBlockStructuredGrid* grid, int nfields, TFieldType* const * fields);

    virtual int derivative(HxLocation3 *loc, float result[][3]);
    virtual HxLocation3* createLocation();
    virtual void getBoundingBox(float bbox[6]) const;

    TFieldType* getField(int iZone);

    HxConnection portGrid;

    HxBlockStructuredGrid* getGrid() const;

protected:
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

private:
    static int eval(HxBlockStructuredField3<TFieldType>*, HxLoc3Block*, float*);
    int doEval(HxLoc3Block* blockLocation, float* val);

    McDArray<McHandle<TFieldType> > m_fields;
};

class HXFIELD_API HxBlockStructuredScalarField3 : public HxBlockStructuredField3<HxScalarField3>
{
    HX_HEADER(HxBlockStructuredScalarField3);
public:

    /** Construct field.  The number of fields must match the number of zones,
        and the fields must have the same coordinates as the grid zones.

        @pre grid->getNumZones() == nfields.
        @pre grid->getZone(i) == mcinterface_cast<HxLattice3>(fields[i]).coords().
      */
    HxBlockStructuredScalarField3(HxBlockStructuredGrid* grid, int nfields, HxScalarField3* const * fields);
};

class HXFIELD_API HxBlockStructuredVectorField3 : public HxBlockStructuredField3<HxVectorField3>
{
    HX_HEADER(HxBlockStructuredVectorField3);
public:

    /** Construct field.  The number of fields must match the number of zones,
        and the fields must have the same coordinates as the grid zones.

        @pre grid->getNumZones() == nfields.
        @pre grid->getZone(i) == mcinterface_cast<HxLattice3>(fields[i]).coords().
      */
    HxBlockStructuredVectorField3(HxBlockStructuredGrid* grid, int nfields, HxVectorField3* const * fields);
};

#endif


/// @}
