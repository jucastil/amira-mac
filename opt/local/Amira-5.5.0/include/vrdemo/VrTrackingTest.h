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
#ifndef VR_TRACKING_TEST_H
#define VR_TRACKING_TEST_H

#include <mclib/McHandle.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortButtonList.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMultipleCopy.h>
#include <hxtracking/HxVREvent.h>

#include <vrdemo/vrdemoAPI.h>

/** Example showing how to access a tracking system on a low level.
    Instead of using an amiraVR configuration file, in this module
    the class HxVREnvironment is used to directly connect to a
    tracking system and to read tracking data from it. The module
    displays little cubes indicating the current positions of all
    trackers.
*/
class VRDEMO_API VRTrackingTest : public HxModule {

  HX_HEADER(VRTrackingTest);
  
  public:
    /// Constructor.
    VRTrackingTest();

    /// Text field containg the name of the tracking driver.
    HxPortText portTracking;

    /// Provides a connect/disconnect button and a clear button.
    HxPortButtonList portAction;

    /// Compute method.
    virtual void compute();

  protected:
    virtual ~VRTrackingTest();

    void createScene();
    void updateScene(HxVREvent* event);

    McHandle<SoSeparator> scene;
    McHandle<SoMultipleCopy> current;
    McHandle<SoMultipleCopy> all;
    McHandle<SoCube> cube;

    static void eventCallback(void *userData, HxVREvent* event);
};

#endif

/// @}
