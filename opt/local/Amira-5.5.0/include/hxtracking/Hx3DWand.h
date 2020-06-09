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

/// @addtogroup hxtracking hxtracking
/// @{
#ifndef HX_3D_WAND_H
#define HX_3D_WAND_H

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <hxcore/Hx3DWandBase.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <hxtracking/hxtrackingAPI.h>
#include <hxtracking/HxVREvent.h>

class Qx3DWidget;

/** Represents the 3D wand for picking and menu interaction.
    Usually for AmiraDev programmers it is sufficient to
    interact with the base class Hx3DWandBase, which is not
    defined in hxtracking but in the base Amira package. */

class HXTRACKING_API Hx3DWand : public Hx3DWandBase
{
  public:
    Hx3DWand();

    virtual ~Hx3DWand();

    SoSeparator* getSceneGraph() const { return root; }

    /// Enables or disables the highlight shape of the wand.
    virtual void setHighlight(bool value);

    /** Computes 2D xy coordinates in the current menu plane.
        The method returns false if the menu plane is lying
        behind the 3D wand. */
    bool getXY(SbVec2f& xy);

    /** Activates a new 2D menu plane. MI is a matrix which
        transform the current menu plane. After calling this
        method the 2D coordinates computed by getXY() refer
        to the new plane. */
    void pushXY(const SbMatrix& MI); 

    /** Activates a new translated menu plane. t is a 2D translation
        vector. After calling this method the 2D coordinates computed by
        getXY() refer to the new plane. */
    void pushXY(const SbVec2f& t); 

    /// Restores the previous menu plane.
    void popXY();

    void moveInit(const SbMatrix& M);

    void moveDelta(SbMatrix& M);

    /// Should be called by a widget if a menu event was handled.
    void setHandled(Qx3DWidget* w, int grab=0, int callFocusLost=1);

    /// Returns true if the current menu event has been handled.
    bool isHandled() const { return isHandledFlag; }

    /// Returns a pointer to the widget which handled the current event.
    Qx3DWidget* getHandled() const;

    bool handleGrabWidget(HxVREvent* event); 

    /// Updates the 3D wand position (called by HxTracking).
    virtual void update(const SbVec3f& pos, const SbRotation& rot, unsigned int b);

  protected:
    McHandle<SoSeparator> root;
    McHandle<SoMatrixTransform> wandXform;

    struct State {
        int flag;
        SbVec2f xy;
        SbMatrix MI;
    };

    SbMatrix refMat;
    SbVec3f refPos;
    SbRotation refRotInverse;

    McDArray<State> stack;
    State grabState;
    unsigned int grabFlag:1;
    unsigned int grabStateFlag:1;
    unsigned int isHandledFlag:1;

  friend class HxTracking;
};

#endif

/// @}
