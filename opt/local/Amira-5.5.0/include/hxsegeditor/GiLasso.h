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
#ifndef GI_LASSO_H
#define GI_LASSO_H

#include <qobject.h>
#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>
#include <hxcore/HxGLPolyLine.h>

#include "Gi.h"
#include "GiTool.h"
#include "IScissors.h"

class GiViewer;
class GiFrameBuffer;
class QCheckBox;
class QRadioButton;
class QButtonGroup;
class QAbstractButton;

/** Implements a lasso tool. Free hand drawing, straight line segments,
    and constrained drawing are supported. Constrained drawing makes
    use of the Intelligent Scissors algorithm. The tool also works in
    a 3D viewer. In this case, all voxels inside the contour are
    selected. */

class GiLasso : public QObject, public GiTool
{ 
    Q_OBJECT
  
  public:
    /// Constructor.
    GiLasso(Gi* theGi);

    /// Destructor.
    ~GiLasso();
    
    /// Name of lasso tool icon file
    virtual const char* getIconName() const;

    /** Draw this shape into the specified frame buffer. */
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box);

    /** Draw this shape into the specified frame buffer.
        @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer* frameBuffer, McEvent* event);

    /** Returns bounding box of shape. */
    McBox2i getBoundingBox();

    virtual bool isDragging() const;

    virtual void createWidget(QWidget* parent);

    /// Called when tool is activated, enables contouring in 3D.
    virtual void select();

    /// Called when tool is deactivated, disables contouring in 3D.
    virtual void deselect(GiFrameBuffer*);

    static int neuroTraceMode;

  protected:
    int mode; // SUBTRACT (ctrl), ADD (shift), REPLACE (none)
    McVec2i currPos;
    McDArray<McVec2i> path;
    GiFrameBuffer* activeBuffer;

    int autoTrace; // 0=free hand drawing, 1=intelligent scissors
    int sliceNumber;     //slice and 
    float dataWindow[2]; //dw for which iScissors are initialized
    int mDrawingMode; // 0=freehand, 1=ellipse, 2=rectangle
    int mInsideOutMode; // 0=inside, 1=outside
    McVec2i mEllipseStart; // center of ellipse
    bool mEllipseIsDrawing; // true if mouse button is down and an ellipse is drawn
    bool mEllipseCenterMode; // if true mEllipseStart is interpreted as ellipse center
    McVec2i mRectangleStart; // center of rectangle
    bool mRectangleIsDrawing; // true if mouse button is down and a rectangle is being drawn
    bool mRectangleCenterMode; //if true mRectangleStart is interpreted as the rectangle's center
    
    IScissors iScissors;

    void finishInteraction(GiFrameBuffer*); // calls path.resize(0)
    int handleEventAutoTrace(GiFrameBuffer* frameBuffer, McEvent* event);
    int handleEventRectangle(GiFrameBuffer* frameBuffer, McEvent* event);
    int handleEventEllipse(GiFrameBuffer* frameBuffer, McEvent* event);
    void renderAutoTrace(GiFrameBuffer*, int, int, int, int, McBox2i&);
    void initAutoTracing(GiViewer* viewer);
    int startAutoTracing(GiFrameBuffer* frameBuffer, McVec2i& pos);
    int stopAutoTracing(GiFrameBuffer* frameBuffer, McEvent*, McVec2i& pos);
    int resetAutoTracing(GiFrameBuffer* frameBuffer, McEvent*, McVec2i& pos);
    int updateAutoTracing(GiFrameBuffer* frameBuffer, McVec2i& pos);
    void appendAutoTraceToPath(GiFrameBuffer* frameBuffer, const McVec2i&);
    int startEllipse(GiFrameBuffer* frameBuffer, McVec2i& pos);
    int stopEllipse(GiFrameBuffer* frameBuffer, McVec2i& pos, int mode);
    int moveEllipse(GiFrameBuffer* frameBuffer, McVec2i& pos);
    int startRectangle(GiFrameBuffer* frameBuffer, McVec2i& pos);
    int stopRectangle(GiFrameBuffer* frameBuffer, McVec2i& pos, int mode);
    int moveRectangle(GiFrameBuffer* frameBuffer, McVec2i& pos);

    HxGLPolyLine* mPolyLine;
    void viewerSelect();
    static bool viewerSelectCB(void* userdata);

    QButtonGroup* mDrawStyleButtonGroup;
    QButtonGroup* m3DModeButtonGroup;

    QRadioButton* wFreehandButton;
    QRadioButton* wEllipseButton;
    QRadioButton* wRectangleButton;
    QRadioButton* wInsideButton;
    QRadioButton* wOutsideButton;
    QCheckBox* wAutoTrace;
    QCheckBox* wEdgeTrace;


  public slots:
    void setAutoTrace(bool);
    void setDrawingMode(QAbstractButton*);
    void setInsideOutMode(QAbstractButton*);
};

#endif

/// @}
