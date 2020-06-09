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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_PLANE_CUT_H_
#define _VS_PLANE_CUT_H_

#include "Vs.h"

#include "VsCropRegion.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <mclib/McPlane.h>


// VS_RELAY_CLASS VsPlaneCut VsCropRegionRelay

/** The VsPlaneCut class defines a half space to be cut off.
    All points in the half space the normal points to are
    cut off. 
*/
class VSVOLREN_API VsPlaneCut : public VsCropRegion
{
    VS_DECL_INTERFACE        ( VsPlaneCut )
    VS_DECL_INTERFACE_IMPL   ( VsPlaneCut )
    VS_DECL_INTERFACE_FACTORY( VsPlaneCut )
    VS_DECL_INTERFACE_RELAY  ( VsPlaneCut )

public:    

    ////////////////////////////////////////
    // override VsCropRegion
    ////////////////////////////////////////

    VSRESULT setPlane( McPlane const & inPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ); // VS_RELAY


public:

    /** Get the current clip plane.
        \return 
                The current clip plane.
    */
    McPlane plane() const; // VS_LOCAL_GET

    /** Set clip plane.
        \param  inPlane
                The new clip plane.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setPlane( const McPlane & inPlane ); // VS_RELAY

    /** Flip the current clip plane.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT revert(); // VS_RELAY
};


#endif


/// @}
