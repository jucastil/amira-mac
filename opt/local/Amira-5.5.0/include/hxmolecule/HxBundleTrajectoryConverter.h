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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef HxBundleTrajectoryConverter_H
#define HxBundleTrajectoryConverter_H

#include <hxmolecule/HxMoleculeWinDLLApi.h>
#include <hxmolecule/HxMolTrajectory.h>

/** */
class HXMOLECULE_API HxBundleTrajectoryConverter : public HxMolTrajectory
{
    HX_HEADER(HxBundleTrajectoryConverter);

public:
    /// Create from data handle.
    HxBundleTrajectoryConverter();
    /// Destructor.
    ~HxBundleTrajectoryConverter();

    /** Updates the user interface of an object. This method is called
        whenever an object is selected or whenever a port of the object has
        changed. On default, the method does nothing. Derived classes may
        overload it in order to show or hide some of their ports. On default,
        all ports of an object are visible. If some ports should not be
        visible the HxPort::hide method of the port must be called
        each time the update method is called. A common mistake is to call
        HxPort::hide only if some other port is new. */
    void update();

    /** Computes something in response to a parameter change. This method
        is called whenever a port of the object has changed. On default, the
        method does nothing. Derived classes should overload it in order to
        compute the things that should be computed by the object. */
    void compute();
};

#endif

/// @}
