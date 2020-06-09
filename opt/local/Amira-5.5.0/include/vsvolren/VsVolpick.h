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
#ifndef _VS_VOLPICK_H_
#define _VS_VOLPICK_H_

#include "Vs.h"

#include "VsObject.h"

class VsSceneManager;

/** Allows for picking into a volume using ray casting. */
class VSVOLREN_API VsVolpick : public VsObject
{
    VS_DECL_INTERFACE        ( VsVolpick )
    VS_DECL_INTERFACE_IMPL   ( VsVolpick )
//  VS_DECL_INTERFACE_FACTORY( VsVolpick )
//  VS_DECL_INTERFACE_RELAY  ( VsVolpick )

public:

    /// Sets a scene manager - a VsSeneManager is mandatory for useful behaviour.
    void setSceneManager(VsSceneManager* sceneMgr);
    VsSceneManager* sceneManager() const;

    /** Calculates point in object space which is visible in 3d volume
        and sets associated three slices of scene manager accordingly. 
        Parameters x and y are in pixel coordinates (forwarded by mouse event) */
    void handle(int x, int y);

    // things to think about
    // - rendering technique used (RenderMode) : ok, done by Threshold-class in Impl  (08.06.2005)
    // - transfer function                     : ok, for (S)VRT use VsVolren's        (08.06.2005)
    // - color table                           : not relevant?
    // - data interval                         : ok, automatic of transfer function
    // - threshold for iso-surfaces            : ok, use VsVolren's                   (08.06.2005)
    // - crop region                           : ok                                   (09.06.2005)
    // - level to choose from?                 : automatically?

    // - mouse cursor for volume pick mode     : use VsInteractionManager::SeekCursor (09.06.2005)
    // - display sphere / 3d-crosshair at intersection point in 3d view?
};

#endif // VS_VOLPICK_H


/// @}
