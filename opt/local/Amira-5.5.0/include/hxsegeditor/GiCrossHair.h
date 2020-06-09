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
#ifndef GI_CROSS_HAIR_H
#define GI_CROSS_HAIR_H

#include <mclib/McDArray.h>
#include "GiShape.h"
#include "HxGiWinDLLApi.h"

class GiCrossHair;

typedef void (*GiCrossHairCB)(GiCrossHair* crossHair, void* userData);

///
class HXSEGEDITOR_API GiCrossHair : public GiShape {

  public:
    /// Constructor.
    GiCrossHair();

    /// Destructor.
    ~GiCrossHair();

    /// Overloaded render method.
    virtual void render(GiFrameBuffer* frameBuffer, const McBox2i&);

    /// Overloaded event handler.
    virtual int handleEvent(GiFrameBuffer*, McEvent* event);

    /// Sets crosshair position but does not invoke valueChangedCallback.
    void setPosition(const McVec2i& pos);

    /// Returns positions of crosshair.
    const McVec2i& getPosition() const { return pos; }

    /// Returns effective position taking into account height scale.
    McVec2i getEffPosition();

    /// Allows the user to register a callback method.
    void setValueChangedCallback(GiCrossHairCB callback, void* userData);

    /// Set color (which==0 -> horizontal, which==1 -> vertical).
    void setColor(int which, int r, int g, int b);

  protected:
    McVec2i pos;
    void* userData;
    GiCrossHairCB callback;
    unsigned char rgbVert[3];
    unsigned char rgbHorz[3];
};

#endif

/// @}
