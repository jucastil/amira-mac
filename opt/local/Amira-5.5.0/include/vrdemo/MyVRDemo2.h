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

/// @addtogroup vrdemo vrdemo
/// @{
#ifndef MY_VR_DEMO2_H
#define MY_VR_DEMO2_H

#include <mclib/McHandle.h>
#include <mclib/McWatch.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortButtonList.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/collision/SoCollisionManager.h>
#include <vrdemo/vrdemoAPI.h>

class SoEventCallback;

class VRDEMO_API MyVRDemo2 : public HxModule
{
    HX_HEADER( MyVRDemo2 );

public:
    MyVRDemo2();

    ~MyVRDemo2();
    
    // override HxModule::compute()
    virtual void    compute();

    // timeout methode that performs the animation step
    void            timeout();
    
    // scene construction
    void            createScene( SoSeparator * scene );

    // callback responding to object collision
    SoCollisionManager::Resp 
                    onCollision( const SoCollidingPrimitive * inObject, const SoCollidingPrimitive * inScene );

    // callback tracker movement
    void            onTrackerEvent( SoEventCallback * inNode );


public:

    // user interface
    HxPortButtonList        _portAction;

    // animation data
    McWatch                 _timer;
    double                  _timeLast;
    SbVec3f                 _ballDir;
    double                  _ballSpeed;
    SbMatrix                _sceneXform;

    // the scene graph
    SoSeparator           * _scene;

    // ball
    SoTransform           * _ballTrans;

    // pad
    SoTransform           * _padTrans;

    // the object which checks for collisions 
    // ( for this example more or less sufficient ;)
    SoCollisionManager    * _collisionManager;

};

#endif

/// @}
