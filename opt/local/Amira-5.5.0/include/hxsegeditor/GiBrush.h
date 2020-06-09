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
#ifndef GiBRUSH_H
#define GiBRUSH_H

#include <qobject.h>
#include <mclib/McVec2i.h>

#include "Gi.h"
#include "GiTool.h"
#include <hxsegeditor/ui_GiBrush.h>
#include "GiModifySelection.h"

class GiFrameBuffer;

/// This class implements a circular brush.

class GiBrush : public QObject, public GiTool { 
  
    Q_OBJECT
  
  public:
    /// Constructor.
    GiBrush(Gi* theGi);

    /// Destructor.
    ~GiBrush();
    
    virtual const char* getIconName() const{ return "SegBrushIcon.png"; }

    /** Draw this shape into the specified frame buffer*/
    void render(GiFrameBuffer* frameBuffer,const McBox2i&);

    /** Draw this shape into the specified frame buffer.
      @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer* frameBuffer,McEvent* event);

    /** Clears the circle. */
    void clear(GiFrameBuffer* frameBuffer);

    /// Sets diameter of brush in pixels.
    void setBrushSize(int size);
    
    ///
    virtual void deselect(GiFrameBuffer*);

    static int morphologicalMode;
    static bool autoHide;
    static bool squareBrush;

  protected:
    Ui::GiBrush ui;

    int lock;
    int buttonDown;
    unsigned char* brush;
    McVec2i size, brushSize, currentPos, lastPos, lastSize;
    GiViewer* lastViewer; // viewer, where last mouse event occured
    void brushChange();
    void startInteraction(GiViewer*);
    void putBrush(GiFrameBuffer* frameBuffer, McVec2i pos, int put=1);
    
    McDArray<McVec2i> path;
    void finishInteraction(GiFrameBuffer* frameBuffer, McEvent* event);

    unsigned int sliderIsMoving:1;

    /* This one is used in an experimental mode.*/
    void putBrush2(GiFrameBuffer* frameBuffer, McVec2i pos, int put=1,
		   int initial=0);
    
    virtual void createWidget(QWidget* Parent);
	virtual void select(void);

  protected slots:
    void slotBrushSizeChanged(int value);
    void slotHideBrush(int state);
    void slotCircularBrush();
    void slotSquareBrush();
};

#endif

/// @}
