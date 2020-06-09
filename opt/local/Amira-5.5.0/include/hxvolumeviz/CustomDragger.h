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

/// @addtogroup hxvolumeviz hxvolumeviz
/// @{
#ifndef CUSTOM_DRAGGER_H
#define CUSTOM_DRAGGER_H

#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <Inventor/SbLinear.h>

#include <Inventor/nodes/SoSeparator.h> 
#include <Inventor/nodes/SoTransform.h> 

class SoDragger;
class SoTranslate1Dragger;
class HxOrthoSliceLDM;
class SoCoordinate3;
class SoIndexedFaceSet;
class SoSwitch;
class SoMaterial;

class CustomDragger : public McHandable
{
public:
  enum Orientation {
    X_AXIS = 0,
    Y_AXIS,
    Z_AXIS
  };

  CustomDragger(HxOrthoSliceLDM* orthoSlice);
  virtual ~CustomDragger();

  SoSeparator* getSceneGraph() {return m_sceneGraph;};

  void setOrientation(CustomDragger::Orientation orientation);

  void updateTranslationFromSlice(float trans);

  void setFrameColor(const SbColor& color);

  void setFrameVisibility(bool onOff);

  void enableDragging(bool onOff);

private:
  static void motionCB(void* userData, SoDragger* dragger);
  static void finishCB(void* userData, SoDragger* dragger);

  void updateCoords(CustomDragger::Orientation orientation);


  McHandle<SoSeparator> m_sceneGraph;
  McHandle<SoTransform> m_transform;
  HxOrthoSliceLDM* m_orthoSlice;
  SoTranslate1Dragger* m_dragger;
  SoCoordinate3* m_coords;
  SoIndexedFaceSet* m_faceSet;
  SoMaterial* m_mat;
  SoSwitch*   m_translatorSwitch;
  SoSwitch*   m_draggerSwitch;
};

#endif



/// @}
