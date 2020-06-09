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
#ifndef SO_RENDER_AREA_SWITCH_H
#define SO_RENDER_AREA_SWITCH_H

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/fields/SoSFBool.h>

#include <hxcore/HxAmiraWinDLLApi.h>

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
// non � DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable:4251 4275)

class HxBase;
class HxRenderArea;

// Callback functions registered with this node should be of this type.
typedef int SoRenderAreaSwitchCB(void* userData, HxBase* moduleBase, SoSwitch* traversingSwitch, HxRenderArea* viewer, SoAction* action);

/**
 *  SoRenderAreaSwitch is a subclass of SoSwitch that allow
 *  some drawing restrictions to given render areas.
 *  This can be useful for preventing annotations and logos from
 *  be rendered on all screens.
 *  To determine which child has to be traversed, a callback is called
 *  each time that this node is traversed. The callback has to return,
 *  the child to traverse and invalidating render and bounding box caching
 *  depending on the behavior that the user wants to have:
 *      1. If user wants that this node is traversed all the time,
 *         he will have to invalidate cache each time that the callback will be called.
 *      2. If he wants that OIV creates caching ( e.g.: bounding box caching which may be
 *         stored in a non shared separator (between viewers or remote render areas) )
 *         during viewer interaction the cache invalidation will be done only if the
 *         if the new whichChild value is different than the current one.
 *  Like a SoBlinker, user has to start this node. When the node is started, the callback is called.
 *  When the user stops this node, whichChild value is automatically set back to SO_SWITCH_ALL.
 */
class HXCORE_API SoRenderAreaSwitch : public SoSwitch
{
    SO_NODE_HEADER( SoRenderAreaSwitch );

public:


    /**
     * Allows applications to enable or disable the switch process easily.
     */
    SoSFBool on;

    /**
     *  Sets pointer to callback function and user data. By default, the function
     *  pointer in the node is NULL and does nothing.
     *  This callback function is in charge of returning the child to traverse:
     *  SO_SWITCH_ALL, SO_SWITCH_NONE or 'childIndex'.
     */
    void setCallback(SoRenderAreaSwitchCB* func, HxBase* base, void* userData=0)
    { callbackFunc = func; callbackModuleBase = base; callbackUserData = userData; }

    SoRenderAreaSwitch();

    static void initClass();

    virtual void GLRender(SoGLRenderAction* action);
    virtual void callback(SoCallbackAction* action);
    virtual void pick(SoPickAction* action);
    virtual void getBoundingBox(SoGetBoundingBoxAction* action);
    virtual void handleEvent(SoHandleEventAction* action);
    virtual void getMatrix(SoGetMatrixAction* action);
    virtual void search(SoSearchAction* action);
    virtual void getPrimitiveCount(SoGetPrimitiveCountAction* action);
    virtual void notify(SoNotList* list);

protected:

    /**
     *  This method is in charge of calling the callback function.
     */
    virtual void doAction(SoAction* action);
    void beforeDoAction(SoAction* action);

    /**
     *  Output some traversal debug informations.
     */
    void displayTraversedAction(SoAction* action);

    class SoFieldSensor* onSensor;

    static void onSensorCB(void* data, class SoSensor* sensor);

    /**
     *  Call the ldm valuation action method.
     */
    static void ldmAction(SoAction *action, SoNode* node);

private:

    // Function to call
    SoRenderAreaSwitchCB* callbackFunc;
    // The HxBase class from which this node is used
    HxBase* callbackModuleBase;
    // User data to pass it
    void* callbackUserData;
};

#pragma warning(pop)

#endif

/// @}
