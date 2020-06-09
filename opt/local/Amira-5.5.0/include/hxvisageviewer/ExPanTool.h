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
#ifndef  EX_PANTOOL_H
#define  EX_PANTOOL_H

#include "ExModal.h"
#include <mclib/McPlane.h>
#include <mclib/McVec2f.h>
#include "VisageViewerWinDLLApi.h"

/** TODO: document this class
*/
class HXVISAGEVIEWER_API ExPanTool : public ExModal
{
protected:

    /** Call to begin mouse-panning process.
    \param  viewer
            viewer where the tool is applied to
    \param  x
            current horizontal mouse position
    \param  y
            current vertical mouse position
    */
    void startPanning( ExBaseViewer * viewer, int x, int y );

    /** call to stop mouse-panning process
    */
    void stopPanning();

    /** mouse-pan according to the current mouse position.
    \param  viewer
            viewer where the tool is applied to
    \param  x
            current horizontal mouse position
    \param  y
            current vertical mouse position
    \return 
            If the method succeeds, the return value is VS_OK.
    */
    VSRESULT panCamera( ExBaseViewer * viewer, int x, int y );


public:

    /** camera-pan according to the given relative mouse coordinates
    \param  viewer
            viewer where the tool is applied to
    \param  deltax
            relative horizontal mouse movement
    \param  deltay
            relative vertical mouse movement
    \param  dummy
            parameter to make the two panCamera methods distinguishable
    \return 
            If the method succeeds, the return value is VS_OK.
    */
    static VSRESULT panCamera( ExBaseViewer * viewer, int deltax, int deltay, void * dummy );

    /** camera-pan according to a given increment defined in normalized viewport coordinates
    \param  viewer
            viewer where the tool is applied to
    \param  delta
            vector that defines panning (given in normalized viewport coordinates (0 ... 1)
    \return 
            If the method succeeds, the return value is VS_OK.
    */
    static VSRESULT panCamera( ExBaseViewer * viewer, McVec2f delta);


public:

    /** constructor
    \param  activeState
            The button state that has to be present that the tool gets into mouse-panning mode.
    */
    ExPanTool(int /* Vs::ButtonState */ activeState = Vs::BS_LeftButton);

    /** destructor
    */
    virtual ~ExPanTool();


    ////////////////////////////////////////
    // virtual override methods of ExTool
    ////////////////////////////////////////
    
    virtual bool supports(Ex::ViewerType) const;
    virtual bool isStandard() const { return true; }
    virtual const McString identifier() const;


    ////////////////////////////////////////
    // virtual override methods of ExModal
    ////////////////////////////////////////

    virtual bool processMouseEvent(ExBaseViewer* viewer, Vs::MouseEvent inEvent, int inX, int inY, Vs::ButtonState inState, Ex::CursorShape& outCursor);
    virtual bool processKeyEvent(ExBaseViewer* viewer, Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState);
    virtual bool processWheelEvent(ExBaseViewer* viewer, int inX, int inY, int inDelta);


private:
    
    /// true as long mouse-panning is performed
    bool    mPanning;

    /// current mouse position in the moment when mouse-panning started
    int     mLocator[2];

    /// current position of the cross point of the camera view ray and mFocalPlane in the moment when mouse-panning started
    McVec3f mLocator3D;

    /// plane on which the camera is projected to and moved along
    McPlane mFocalPlane;
};

#endif // EX_PANTOOL_H


/// @}
