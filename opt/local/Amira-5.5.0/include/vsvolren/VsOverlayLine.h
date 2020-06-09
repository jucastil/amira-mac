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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_OVERLAY_LINE_
#define _VS_OVERLAY_LINE_

#include "Vs.h"

#include "VsHandable.h"
#include "VsOverlay.h"
#include "VsOverlayElement.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>

#include "McViewVolume.h"

#ifdef CursorShape
#undef CursorShape
#endif

/** \if UNDOCUMENTED A line strip consisting of two or more points. As a
    Overlayment feature the line strip knows about his length.

    (The class is for internal use only and will not be exported. Therefore it
     does not hide any implementation detail.)
  */
class VSVOLREN_API VsOverlayLine : public VsOverlayElement 
{
    VsOverlayLine(const VsOverlayLine&);

public:

    ///
    VsOverlayLine (class VsOverlay* context);

    /// performs a deep copy of an overlay element
    virtual VsOverlayElement* clone() const;

    /// If line is empty, sets two points to given position
    virtual void init(const McVec3f& pos, const VsCamera* camera, const McVec2i& windowSize, bool grab);

    float displacement() const;

    /// Upon a mouse move event with the left button down, we start grabbing
    virtual bool handleStartGrabbingEvent(const VsOverlay::OverlayEvent* event);

    /// Continues grabbing a line
    virtual void grab(const VsOverlay::OverlayEvent* event);

    /// Check whether the line has been picked
    virtual bool picked(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);

    /// Check whether the a point of the line has been picked, returns the index of that
    /// point, or, in case no point was picked, -1
    virtual int pickedPoint(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);

protected:
    virtual void getAlignment(int& horizontal, int& vertical) const;

    virtual McVec3f textAnchorPoint() const;

    virtual void computeTextPosition( VsViewState & st );

    /// called inside render() to collect all primitives to render
    virtual void computeRenderElements( VsViewState & inState );

    virtual bool isPoint(const VsCamera* camera, const McVec2i& windowSize) const;

    virtual McVec3f pointPosition(const VsOverlay::OverlayEvent* event);

public:

    double length() const;

    /// Array of Points
    McDArray<McVec3f> mPoints;

    float             mDisplacement;
    bool              mLineMovementAllowed;
    VsInteractionManager::CursorShape mLineMovementMouseCursor;

    enum LineStyle {
        LINE_FRONT   = 1,  
        LINE_TAIL    = 2,
        ARROW_FRONT  = 4,
        ARROW_TAIL   = 8,
        ARROW_LEFT   = 16,
        ARROW_RIGHT  = 32
    };

    int               mStyle;
};

/// \endif

#endif

/// @}
