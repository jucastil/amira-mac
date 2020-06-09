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
#ifndef SO_TRACKER_H
#define SO_TRACKER_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFRotation.h>

class SoTrackerAmiraVR : public SoNode {

    SO_NODE_HEADER(SoTrackerAmiraVR);

  public:
    SoTrackerAmiraVR();

    SoSFString server;
    SoMFVec3f calibration;
    SoMFVec3f referencePoints;
    SoSFVec3f defaultCameraPosition;
    SoSFVec3f defaultObjectPosition;
    SoSFVec3f leftEyeOffset;
    SoSFVec3f rightEyeOffset;
    SoSFRotation rotGlasses;
    SoSFRotation rotWand;
    SoSFVec3f wandOffset;
    SoSFInt32 wandTrackerId;
    SoSFInt32 headTrackerId;
    SoSFBool headTrackingEnabled;
    SoSFString wandFile;
    SoSFString highlightWandFile;
    SoSFFloat wandScale;
    SoSFVec3f menuPosition;
    SoSFFloat menuSize;
    SoSFRotation menuOrientation;
    SoSFBool autoConnect;
    SoSFString onLoad;
    SoSFString onUnload;
    SoSFString onConnect;
    SoSFString onDisconnect;

  SoINTERNAL public:
    static void	initClass();

  protected:
    virtual ~SoTrackerAmiraVR();
};

#endif


/// @}
