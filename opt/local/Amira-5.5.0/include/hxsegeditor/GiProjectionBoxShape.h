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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GiPROJECTIONBOXSHAPE_H
#define GiPROJECTIONBOXSHAPE_H

#include "GiShape.h"

class GiFrameBuffer;
class GiEvent;
class GiProjector;
class Gi;

/** Represents a rectangular object, that can be drawn into a frame buffer.*/
class GiProjectionBoxShape : public GiShape {

  public:
    /** Constructor*/
    GiProjectionBoxShape(GiProjector* p, Gi* s);

    ///
    ~GiProjectionBoxShape() {}

    /** Draw this shape into the specified frame buffer*/
    void render(GiFrameBuffer* frameBuffer,const McBox2i&);

    /** handle events
      @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer*, McEvent* event);

    int * getBox(){ return &box[0]; }

    void setActive(int flag){ isActive = flag; }

protected:
    void getCorners(GiFrameBuffer* frameBuffer,McVec2i& p00,McVec2i& p10,McVec2i& p01,McVec2i& p11);
    GiProjector* projector;
    Gi* theGi;
    int grabx,graby;
    int box[6];
    int isActive;
};

#endif

/// @}
