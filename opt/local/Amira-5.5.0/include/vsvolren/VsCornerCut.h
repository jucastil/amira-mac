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
#ifndef _VS_CORNER_CUT_H_
#define _VS_CORNER_CUT_H_

#include "Vs.h"

#include "VsCropRegion.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <mclib/McBox3f.h>

class VsData;

// VS_RELAY_CLASS VsCornerCut VsCropRegionRelay


/** This class implements a VsCropRegion used to restrict 
    rendered parts of the volume image.

    Specifically VsCornerCut defines an octant to be cut off. The 
    octant is indicated by an enumeration type. The center where the
    eight octants meet can be positioned at an arbitrary location 
    via the setCenter() method. 
*/

class VSVOLREN_API VsCornerCut : public VsCropRegion
{
    VS_DECL_INTERFACE        ( VsCornerCut )
    VS_DECL_INTERFACE_IMPL   ( VsCornerCut )
    VS_DECL_INTERFACE_FACTORY( VsCornerCut )
    VS_DECL_INTERFACE_RELAY  ( VsCornerCut )

public:
    
    ////////////////////////////////////////
    // override VsCropRegion
    ////////////////////////////////////////

    VSRESULT setPlane( McPlane const & inPlane, unsigned int inIdxProduct, unsigned int inIdxPlane );


public:

    /** Denotes one of the 8 octants. 
        Bit 0 is x, bit 1 is y, bit 2 is z.
        If a bit for an axis is cleared, the octant
        is on the positive side of the center position
        for that axis.
    */
    enum Octant 
    {
        /// positive Z - positive Y - positive X
        PZ_PY_PX = 0,   
        /// positive Z - positive Y - negative X
        PZ_PY_NX = 1,
        /// positive Z - negative Y - positive X
        PZ_NY_PX = 2,
        /// positive Z - negative Y - negative X
        PZ_NY_NX = 3,
        /// negative Z - positive Y - positive X
        NZ_PY_PX = 4,
        /// negative Z - positive Y - negative X
        NZ_PY_NX = 5,
        /// negative Z - negative Y - positive X
        NZ_NY_PX = 6,
        /// negative Z - negative Y - negative X
        NZ_NY_NX = 7
    };
        

    /** Returns the center for the eight octants.
        \return 
                Current center position.
    */
    McVec3f center() const; // VS_LOCAL_GET

    /** Sets the center for the eight octants.
        \param  inCenter
                The new center position.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setCenter( const McVec3f & inCenter ); // VS_RELAY

    /** Returns the octant to be cut off.
        \return 
                Current octant, see VsCornerCut::Octant for valid values.
    */
    Octant octant() const; // VS_LOCAL_GET

    /** Sets the octant to be cut off.
        \param  inOctant
                The new octant, see VsCornerCut::Octant for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setOctant( VsCornerCut::Octant inOctant ); // VS_RELAY

    /** Returns those part of a box, that falls into the cut-off octant.
        \param  inBoxToBeCut
                The box that gets intersected with the octant.
        \return
                Intersection between \c inBoxToBeCut and the current octants box.
    */
    McBox3f box( const McBox3f & inBoxToBeCut ) const; // VS_LOCAL_GET
};


#endif

/// @}
