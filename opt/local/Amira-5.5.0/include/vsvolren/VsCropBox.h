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
#ifndef _VS_CROP_BOX_H_
#define _VS_CROP_BOX_H_

#include "Vs.h"

#include "VsCropRegion.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <mclib/McBox3f.h>
#include <mclib/McPlane.h>


class VsData;

// VS_RELAY_CLASS VsCropBox VsCropRegionRelay


/** This class describes an axis-aligned crop box. All points
    outside the box are cut off.
*/
class VSVOLREN_API VsCropBox : public VsCropRegion
{
    VS_DECL_INTERFACE        ( VsCropBox )
    VS_DECL_INTERFACE_IMPL   ( VsCropBox )
    VS_DECL_INTERFACE_FACTORY( VsCropBox )
    VS_DECL_INTERFACE_RELAY  ( VsCropBox )
    
    ////////////////////////////////////////
    // override VsCropRegion
    ////////////////////////////////////////

    VSRESULT setPlane( McPlane const & inPlane, unsigned int inIdxProduct, unsigned int inIdxPlane ); // VS_RELAY


public:

    /** The box outside which the volume is cut off.
        \return 
                The current cut box.
    */
    McBox3f box() const; // VS_LOCAL_GET

    /** Set the cut box.
        \param  inBox
                New cut box.          
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setBox( const McBox3f & inBox ); // VS_RELAY

    /** Returns one of the six planes defining the box. Valid values for \c inPlaneIndex are 0 to 5.
        \param  inPlaneIndex
                Value from 0 to 5 indexing the requested plane.
        \param  outPlane
                Reference to the plane that gets a copy of the requested plane.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT plane( unsigned int inPlaneIndex, McPlane & outPlane ) const; // VS_LOCAL_GET
};


#endif


/// @}
