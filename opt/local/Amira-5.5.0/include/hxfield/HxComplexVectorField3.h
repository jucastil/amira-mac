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
#ifndef HX_COMPLEX_VECTORFIELD3_H
#define HX_COMPLEX_VECTORFIELD3_H

#include <hxfield/HxField3.h>


/** Class representing a generic complex vector field.
    This is the base class for complex vector fields. Complex vector fields
    are internally represented by usual fields with 6 data variables.
    All primitive data types are allowed. Complex vector fields provide
    transparent read access via HxLocation3. 
    */

class HXFIELD_API HxComplexVectorField3 : public HxField3
{
  HX_DATA_HEADER(HxComplexVectorField3);

  public:
    /// Constructor.
    HxComplexVectorField3(McPrimType primType);

    /// Duplicates the current HxComplexVectorField3 object
    virtual HxData *duplicate() const;
};

#endif

/// @}
