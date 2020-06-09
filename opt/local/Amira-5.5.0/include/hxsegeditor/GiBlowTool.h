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
#ifndef GiBLOWTOOL_H
#define GiBLOWTOOL_H

#include <qobject.h>
#include <qcombobox.h>

#include <mclib/McVec2i.h>
#include <mclib/McVec2f.h>
#include <mclib/McDArray.h>
#include "Gi.h"
#include "GiTool.h"
#include <hxsegeditor/McBlowRegion.h>

class GiViewer;
class GiFrameBuffer;
class QLineEdit;

class GiBlowTool : public QObject, public GiTool{
    Q_OBJECT
  public:
    /** Constructor. */
    GiBlowTool(Gi* theGi);

    /** Destructor. */
    ~GiBlowTool();

    virtual const char* getIconName() const{ return "SegBlowerIcon.png"; }

    /** Draw this shape into the specified frame buffer. */
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box);

    int handleMouseUp(GiFrameBuffer* frameBuffer);

    /** Draw this shape into the specified frame buffer.
        @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer* frameBuffer, McEvent* event);

    /** Returns bounding box of shape. */
    McBox2i getBoundingBox();

    McBlowRegion* blower;

  protected:
    void getParams();
    void redraw(GiFrameBuffer* frameBuffer);
    int mode; // SUBTRACT (ctrl), ADD (shift), REPLACE (none)
    McVec2i currPos;
    McDArray<McVec2i> path;

    McBox2i oldBox,box;

    QLineEdit* gaussTextF,*toleranceTextF;
    QComboBox *snapList;

    virtual void createWidget(QWidget* parent);

    /// Position of mouse click
    McVec2i initialPos;
    /// Current position of mouse
    McVec2i  currentPos;
    /// Distance of initialPos from currentPos
    float dist;
    /// Flag to ignore mouse up event
    bool  mouseUp;

    /// Time step computed currently
    int currentTimeStep;

    /// Current contour is drawn as long as mouse button is down
    int drawContour;

    /// used to set tolerance in McBlowRegion
    int tolerance;

    /// used to set gaussWidth in McBlowRegion
    int gauss;

    /// used to set edge preference
    int snap;

  public slots:
    //void toleranceChange();
    //void gaussChange();
};

#endif

/// @}
