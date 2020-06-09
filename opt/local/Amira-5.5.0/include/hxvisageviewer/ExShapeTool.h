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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef  EX_SHAPETOOL_H
#define  EX_SHAPETOOL_H

#include "ExBase.h"
#include "ExModal.h"

/** Tools that are always active and allow for user interactions with
    graphical scene elements. */
class HXVISAGEVIEWER_API ExShapeTool : public ExModal
{
public:
    ExShapeTool(int activeState = 0, bool exclusive = false) : ExModal(activeState, exclusive) {};

    /** This method is called on mouse move events. If the shape where this tool is active 
        is hit by the mouse cursor the tool indicates this by returning TRUE.
        This method is called on all registered shape-tools. If any of this tools returns TRUE
        the process*Event() metods are invoked only on this tool. If multiple tools
        return TRUE, the one that returned the smallest value in outDistance is chosen.
        If none of the tools returned TRUE, the process*Event() methods are called on all tools. (ask Florian ^^)

        \param  inViewer
                If nonzero, viewer where the mouse cursor is in.
        \param  inX
                Mouse cursor horizontal pixel-position relative to the viewers upper left origin.
        \param  inY
                Mouse cursor vertical pixel-position relative to the viewers upper left origin.
        \param  outDistance
                Pixel-distance of the mouse cursor to the tools ideal pick-shape. If multiple tools indicate 
                simultaneously that they are active the tool with the smallest distance is chosen.
        \return 
                TRUE if the tools shape was hit, FALSE if not.
    */
    virtual bool pick( ExBaseViewer * inViewer, int inX, int inY, float & outDistance) = 0;

    virtual bool buttonPressed(Vs::MouseEvent event, Vs::ButtonState state) const; 

    virtual bool buttonReleased(Vs::MouseEvent event, Vs::ButtonState state) const; 

    static const float sPickingToleranceOffset;
    
    /** This method computes and returns the picking tolerance
        according to the given initial @c tolerance and the 
        @c sPickingToleranceOffset. 
    */
    static float getPickingTolerance(const float tolerance);
};

#endif // EX_SHAPETOOL_H


/// @}
