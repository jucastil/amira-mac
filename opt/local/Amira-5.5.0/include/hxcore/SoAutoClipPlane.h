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

/// @addtogroup hxcore hxcore
/// @{
#ifndef SO_AUTO_CLIPPLANE_H
#define SO_AUTO_CLIPPLANE_H

#include <Inventor/nodes/SoClipPlane.h>

#include <hxcore/HxAmiraWinDLLApi.h>

class SoAction;
class SoGLRenderAction;
class SoGetBoundingBoxAction;

/**
 *  ClipPlane node allowing the clipped plane to be side switched depending on the camera orientation
 */
class HXCORE_API SoAutoClipPlane : public SoClipPlane {

    SO_NODE_HEADER( SoAutoClipPlane );

public:

    /// Constructor
    SoAutoClipPlane();

    /// Initializes the type
    static void initClass();

    /// Inherited SoNode traversal actions
    virtual void doAction( SoAction *action );
    virtual void GLRender( SoGLRenderAction *action );
    virtual void getBoundingBox(SoGetBoundingBoxAction *action);

    /**
     *  If set to true, plane normal is adjusted depending on camera orientation 
     */ 
    SoSFBool autoClip;

    /**
     *  If set to true, and autoClip is turned on, clip the front of the plane,
     *  otherwise clip the back.
     */
    SoSFBool clipFront;

protected:
 
    /**
     *  Update cutting plane according to state viewing matrix
     */
    void updateCuttingPlane( SoState* state );

private:

    /// Destructor
    virtual ~SoAutoClipPlane();
};

#endif //SO_AUTO_CLIPPLANE_H


/// @}
