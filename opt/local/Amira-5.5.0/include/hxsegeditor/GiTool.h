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
#ifndef GiTOOL_H
#define GiTOOL_H

#include <hxcore/HxResource.h>

#include <mclib/McVec3i.h>
#include "Gi.h"
#include "GiShape.h"

#include <qbitmap.h>
#include <qcursor.h>

class QWidget;
class HxViewerModalTool;

class GiTool : public GiShape {

  public:
    GiTool(Gi* );

    virtual QWidget* getWidget(QWidget * parent);

    const char* getName() const { return theName; }

    virtual const char* getIconName() const = 0;

    virtual void init();

    virtual void select();

    virtual void deselect(class GiFrameBuffer*);

    enum {
        SELECTION_CLEAR=0,
        SELECTION_ADD=1,
        SELECTION_REPLACE=2,
        SELECTION_SUBTRACT=3,
        MODE3D_TOGGLED=4,
        ZOOMALL_TOGGLED=5
    };

    virtual void selectionNotify(int operation);

    virtual const QCursor & getToolCursor() const{ return cursor;}

    void setToolCursor(const QCursor & c){ cursor = c; }

    McVec3i getPoint3D(int x, int y) { return theGi->getPoint3D(x,y); }

    Gi* gi() const { return theGi; }

    virtual HxViewerModalTool* wrapper();
    
    virtual void dataWindowChanged(float, float) { } ;

  protected:
    Gi* theGi;
    QCursor cursor;
    const char* theName;
    virtual void createWidget(QWidget* parent);

  private:
    QWidget* _baseWidget;
};

#endif

/// @}
