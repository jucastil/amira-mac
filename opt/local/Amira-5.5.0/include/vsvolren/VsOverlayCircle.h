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
#ifndef VS_OVERLAY_CIRCLE_H
#define VS_OVERLAY_CIRCLE_H

#include "VsOverlayEllipse.h"


/** \if UNDOCUMENTED An ellipse has a horizontal and vertical radius 
and a center. As a Overlayment feature the line strip knows about
its units.

(The class is for internal use only and will not be exported. Therefore it
does not hide any implementation detail.)
*/
class VSVOLREN_API VsOverlayCircle : public VsOverlayEllipse
{
    VsOverlayCircle(const VsOverlayCircle&);

public:
    VsOverlayCircle ( class VsOverlay * inContext );
    virtual void init(const McVec3f& pos, const VsCamera* camera, const McVec2i& windowSize, bool grab);

    virtual void grab(const VsOverlay::OverlayEvent* event);
    virtual int  pickedPoint(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);
    float computePerimeter();
    float computeArea();

protected:
    virtual void computeRenderElements( VsViewState & inState );
};

#endif
/// @}
