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
#ifndef STACKED_SCALARFIELD3_H
#define STACKED_SCALARFIELD3_H

#include <hxfield/HxStackedCoord3.h>
#include <hxfield/HxRegScalarField3.h>

/// Represents a scalar field consisting of parallel slices.

class HXFIELD_API HxStackedScalarField3 : public HxRegScalarField3
{
  HX_DATA_HEADER(HxStackedScalarField3);

  public:
    /// Constructor.
    HxStackedScalarField3(const int dims[3], McPrimType primType,
	void* data=0);

    /// This constructor uses an existing lattice object.
    HxStackedScalarField3(HxLattice3* existingLattice);

    /// Destructor.
    ~HxStackedScalarField3();

    /// Returns pointer to coordinate object.
    HxStackedCoord3* coords() { return (HxStackedCoord3*) lattice.coords(); }

    /// Duplicates the current HxStackedScalarField3 object
    virtual HxData *duplicate() const;

  protected:
    void copyData(const HxStackedScalarField3& source);
};

#endif

/// @}
