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
#ifndef _SO_MOVING_COMPLEXITY_H_
#define _SO_MOVING_COMPLEXITY_H_

#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/sensors/SoAlarmSensor.h> 

#include <map>

#include "HxVolumeVizAPI.h"

/** Moving Complexity Node.
    The complexity value vary from maxValue to minValue when the camera move.
    Values range from 0 to 1, where 0 means minimum complexity and 1 means maximum complexity.
    Default values:
    minValue = 0.1f;
    maxValue = 0.5f; 
*/

class HXVOLUMEVIZ_API SoMovingComplexity : public SoComplexity
{
  SO_NODE_HEADER(SoMovingComplexity);
public:
  SoMovingComplexity();

  SoSFFloat           minValue; //<! minimum complexity value.
  SoSFFloat           maxValue; //<! maximum complexity value.
SoINTERNAL public:
  // Initializes this class for use in scene graphs. This
  // should be called after database initialization and before
  // any instance of this node is constructed.
  static void initClass();
  static void exitClass(){}

SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
protected:
  // Destructor. Protected to keep people from trying to delete
  // nodes, rather than using the reference count mechanism.
  virtual ~SoMovingComplexity();
private:
  SoAlarmSensor sensor;
  SbTime        scheduleTime;

  static void sensorCB(void *data, SoSensor *sensor);

  // Elements are viewer dependent, so, use a map.
  std::map<SoAction*,SbViewVolume>  m_viewVolume;
  std::map<SoAction*,SbMatrix>      m_modelMatrix;
};

#endif

/// @}
