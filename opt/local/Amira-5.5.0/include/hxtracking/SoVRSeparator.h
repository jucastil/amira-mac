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
#ifndef SO_VR_SEPARATOR_H
#define SO_VR_SEPARATOR_H

#include <hxcore/SoVRSeparatorBase.h>

class HxTracking;

class SoVRSeparator : public SoVRSeparatorBase {

  public:
    SoVRSeparator(HxTracking* t=0);

    virtual bool isImmersive() const;
    virtual McString encodeImmersiveEnv();

    virtual void  callback(SoCallbackAction *action);
    virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void  handleEvent(SoHandleEventAction *action);
    virtual void  rayPick(SoRayPickAction *action);
    virtual void  GLRender(SoGLRenderAction *action);
    virtual void  GLRenderBelowPath(SoGLRenderAction *action);
    virtual void  GLRenderInPath(SoGLRenderAction *action);
    virtual void  GLRenderOffPath(SoGLRenderAction *action);
    virtual void  getMatrix(SoGetMatrixAction *action);

    virtual SbBool affectsState() const;

    SoGroup* getLightGroup() const { return lightGroup; }

    virtual void getViewPoint(SbVec3f& pos, SbRotation& ori) const;

    virtual bool hasWand() const;
    virtual void getWand(SbVec3f& pos, SbRotation& ori) const;
    virtual void updateWandMatrices();

  protected:
    virtual ~SoVRSeparator();

    // In some action traversal, the screen used may not be the current one, 
    // but the master node. This is the case in event handling.
    bool setVRCoords(SoAction *action, SoScreenAmiraVR* screen = NULL);
    bool setVRCoordsStereo(SoAction *action);
    void setSceneCoords(SoAction *action);
    void setSceneCoordsStereo(SoAction *action);

    SbViewVolume createViewVolume(SoScreenAmiraVR* screen, SbVec3f cameraPos);

    /** Return current SbViewVolume stereo mode according to given screen */
    SbViewVolume::StereoMode getCurrentStereoMode(SoScreenAmiraVR* screen);

    HxTracking* t;
    SoGroup* lightGroup;
};

#endif


/// @}
