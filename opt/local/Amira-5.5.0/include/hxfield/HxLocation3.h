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
#ifndef LOCATION3
#define LOCATION3

#include <hxfield/HxFieldWinDLLApi.h>

#include <mclib/McVec3f.h>

class HxField3;


/** Class representing a general location within a 3D field.
    Fields providing some numerical value for any position within a domain
    in @f$R^3@f$ may be represented in various ways, e.g. by evaluating a
    functional expression or by interpolating values defined on an
    arbitrary grid. In particular the use of curvilinear or unstructured
    grids is quite common. Evaluating such a field at a location @f$p@f$ 
    in general requires searching for the grid cell which contains @f$p@f$.
    This search might be accelearted significantly by exploiting the
    special structure of the grid. On the other hand, points in the
    neighbourhood of some previous location might be found much faster
    using some local search strategy.

    This class provides transparent access to all kinds of fields
    in @f$R^3@f$, irrespectively of how they are defined. The constructor
    @c Location3 is protected. Instead, a particular instance of this class
    can be obtained from any Field3. The location can be set to
    any value using several set() methods. This may involve a global
    search for a particular grid cell. If the new location is known to be
    in the neighbourhood of the old one, a local search strategy may
    be selected by calling move() methods. Both kind of methods
    return 1 on success and 0 if the field is not defined at the
    requested location. 
    */

class HXFIELD_API HxLocation3
{
  public:
    /// Returns pointer to current location vector.
    operator const float* () const { return &x; }

    /// Returns current location.
    void getLocation(float& X, float& Y, float& Z) const { X=x; Y=y; Z=z; }

    /// Sets new location. May involve global search.
    virtual int set(float x, float y, float z);

    /// Sets new location. May involve global search.
    int set(const float v[3]) { return set(v[0], v[1], v[2]); }

    /// Sets new location. May involve global search.
    int set(const McVec3f& v) { return set(v[0], v[1], v[2]); }

    /// Sets new location. May involve global search.
    int operator=(const float v[3]) { return set(v[0], v[1], v[2]); }

    /// Sets new location. May involve local search.
    virtual int move(float x, float y, float z);

    /// Sets new location. May involve local search.
    int move(const float v[3]) { return move(v[0], v[1], v[2]); }

    /// Sets new location. May involve local search.
    int move(const McVec3f& v) { return move(v[0], v[1], v[2]); }

    /// Modifies location by adding an increment. May involve local search.
    int operator+=(const float v[3]) { 
	return move(x+v[0], y+v[1], z+v[2]);
    }

    /// Destructor.
    virtual ~HxLocation3() { }

    HxLocation3(float X, float Y, float Z) {
	x = X; y = Y; z = Z; }

    /// Constructor. Objects are created by a particular field.
    HxLocation3() { }

    /// Current location.
    float x, y, z;

    friend class HxField3;
};

#endif

/// @}
