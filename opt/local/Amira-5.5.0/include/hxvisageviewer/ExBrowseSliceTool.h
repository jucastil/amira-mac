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
#ifndef  EX_BROWSESLICETOOL_H
#define  EX_BROWSESLICETOOL_H

#include "ExModal.h"
#include "VisageViewerWinDLLApi.h"

#include <mclib/McPlane.h>

/** The image stack browsing tools allows to use the mouse to navigate through
    an image stack, e.g. an MPR stack in an MPR viewer. The increment for 
    scrolling is the original DICOM slice distance for thin slices, or the 
    virtual slice thickness for thick slices. Dragging btn1 up increases slice
    number (depending on sorting within the image set), dragging btn1 down
    decreases. The increment is the original slice distance. If a wheel mouse 
    is used, the wheel is permanantly used for this tool (wheel up/down 
    increases/decreases slice number by 1), except if explicitly mentioned. 
    Cursor up/down and left/right keys can also be used in the same way in all
    modes. If thick slicing is active, PgUp/PgDown increase/decrease slice 
    position by current slice thickness. 
*/
class HXVISAGEVIEWER_API ExBrowseSliceTool : public ExModal 
{
protected:

    /** Call to begin mouse-browsing process.
    \param  viewer
            viewer where the tool is applied to
    \param  x
            current horizontal mouse position
    \param  y
            current vertical mouse position
    */
    void startBrowsing( ExBaseViewer * viewer, int x, int y );


    /** call to stop mouse-browsing process
    */
    void stopBrowsing();

    /** mouse-browse slices according to the current mouse position.
    \param  viewer
            viewer where the tool is applied to
    \param  x
            current horizontal mouse position
    \param  y
            current vertical mouse position
    \return 
            If the method succeeds, the return value is VS_OK.
    */
    VSRESULT browse( ExBaseViewer * viewer, int x, int y );


public:

    /** constructor
    \param  activeState
            The button state that has to be present that the tool gets into mouse-browsing mode.
    */
    ExBrowseSliceTool( int /* Vs::ButtonState */ activeState = Vs::BS_LeftButton );

    /** destructor
    */
    virtual ~ExBrowseSliceTool();


    ////////////////////////////////////////
    // virtual override methods of ExTool
    ////////////////////////////////////////

    virtual bool isStandard() const;
    virtual const McString identifier() const;
    virtual bool supports( Ex::ViewerType inType ) const;


    ////////////////////////////////////////
    // virtual override methods of ExModal
    ////////////////////////////////////////

    virtual bool processMouseEvent(ExBaseViewer* viewer, Vs::MouseEvent inEvent, int inX, int inY, Vs::ButtonState inState, Ex::CursorShape& outCursor);
    virtual bool processKeyEvent(ExBaseViewer* viewer, Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState);
    virtual bool processWheelEvent(ExBaseViewer* viewer, int inX, int inY, int inDelta);


private:

    /// true as long mouse-browsing is performed
    bool    mBrowsing;

    /// current mouse position in the moment when mouse-browsing started
    int     mLocator[2];

    /// current slice number in the moment when mouse-browsing started
    float   mRefSlice;

    /// current plane in the moment when mouse-browsing started
    McPlane mRefPlane;

    /// accumulated mouse wheel delta, necessary for devices supporting pixel accuracy
    int mWheelDelta;
};

#endif // EX_BROWSESLICETOOL_H

/// @}
