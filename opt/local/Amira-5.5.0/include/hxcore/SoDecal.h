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
#ifndef SO_DECAL
#define SO_DECAL

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoPolygonOffset.h> 

#include <hxcore/HxAmiraWinDLLApi.h>

class HxPreferences;

// SoGroup.h includes SoSubNode.h; no need to include it again

#pragma warning(push)

// non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable:4275)

/// Inventor node for making decals (requires a stencil plane)
class HXCORE_API SoDecal : public SoGroup {

    SO_NODE_HEADER(SoDecal);

  public:
    /// May be @c NONE, @c DELAY, @c ALPHATEST
    enum AlphaPolicy { NONE=0, DELAY, ALPHATEST };

    /** Nodes with indices smaller than @c backgroundIndex define
        the background, on top of which all other nodes are placed.
    */
    SoSFInt32 backgroundIndex;

    /// Indicates if background is opaque, masked or transparent
    SoSFInt32 alphaPolicy;

    /// Convenience method updating @c backgroundIndex automatically
    void addForeground(SoNode* node);

    /// Convenience method updating @c backgroundIndex automatically
    void addBackground(SoNode* node);

    void removeBackground(SoNode* node);

    /// Initializes the type
    static void initClass();

    /// Default constructor
    SoDecal();

  protected:
    // Generic traversal of children for any action
    virtual void  doAction(SoAction *action);

    // These implement supported actions
    virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void  GLRender(SoGLRenderAction *action);
    virtual void  handleEvent(SoHandleEventAction *action);
    virtual void  pick(SoPickAction *action);
    virtual void  getMatrix(SoGetMatrixAction *action);
    virtual void  search(SoSearchAction *action);

  private:
    // Destructor
    virtual ~SoDecal();
};

#pragma warning(pop)

#endif // SO_DECAL

/// @}
