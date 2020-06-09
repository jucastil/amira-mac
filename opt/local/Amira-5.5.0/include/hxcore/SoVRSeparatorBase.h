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
#ifndef SO_VR_SEPARATOR_BASE_H
#define SO_VR_SEPARATOR_BASE_H

//---------------------------------------------------------------------------//
#include <Inventor/SbMatrix.h>
#include <Inventor/SbViewVolume.h>
#include <Inventor/nodes/SoSeparator.h>

//---------------------------------------------------------------------------//
#include <mclib/McString.h>
#include <mclib/McStringTokenizer.h>

#include <hxcore/HxAmiraWinDLLApi.h>

//---------------------------------------------------------------------------//
class HXCORE_API SoVRSeparatorBase : public SoSeparator {
  
public:
    SoVRSeparatorBase();

    void constrainViewing(bool b) { m_constrainedViewing = b; }
    bool isViewingConstrained() const { return m_constrainedViewing; }

    virtual bool isImmersive() const { return false; }

    virtual McString encodeImmersiveEnv();
    static McString doNotEncodeImmersiveEnv();
    void decodeImmersiveEnv(McStringTokenizer& t);
    void resetImmersiveEnv() { m_constrainedImmersiveEnv = false; }

    virtual SbBool affectsState() const;

    virtual void  callback(SoCallbackAction *action);
    virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void  handleEvent(SoHandleEventAction *action);
    virtual void  rayPick(SoRayPickAction *action);
    virtual void  getMatrix(SoGetMatrixAction *action);

    virtual void getViewPoint(SbVec3f& pos, SbRotation& ori) const;

    const SbMatrix& getSceneToVRTransform() { return m_sceneToVR; }
    const SbMatrix& getVRToSceneTransform() { return m_vrToScene; }

    virtual bool hasWand() const { return false; }
    virtual void getWand(SbVec3f& pos, SbRotation& ori) const {}
    virtual void updateWandMatrices() {}

protected:
    void pushImmersiveElements(SoAction *action);

    bool            m_constrainedViewing;
    bool            m_constrainedImmersiveEnv;
    bool            m_forceFlat;
    SbViewVolume    m_viewVolume;
    SbMatrix        m_modelMatrix;
    SbMatrix        m_sceneToVR;
    SbMatrix        m_vrToScene;
};

#endif // SO_VR_SEPARATOR_BASE_H


/// @}
