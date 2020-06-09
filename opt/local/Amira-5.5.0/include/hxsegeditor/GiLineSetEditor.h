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
#ifndef GiLINESETEDITOR_H
#define GiLINESETEDITOR_H

#include <qobject.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec2f.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

#include "Gi.h"
#include "GiTool.h"
#include "IScissors.h"

class GiViewer;
class GiFrameBuffer;
class HxNeuronTree;
class HxUniformScalarField3;
class QxPushButton;

/** Implements a lasso tool. Free hand drawing, straight line segments,
    and constrained drawing are supported. Constrained drawing makes
    use of the Intelligent Scissors algorithm.
*/

class GiLineSetEditor :  public QObject, public GiTool {
  Q_OBJECT

  public:
    /** Constructor. */
    GiLineSetEditor(Gi* theGi);

    /** Destructor. */
    ~GiLineSetEditor();

    virtual const char* getIconName() const{ return "SegLineSetEditorIcon.png"; }

    /** Draw this shape into the specified frame buffer. */
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box);

    /** Draw this shape into the specified frame buffer.
        @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer* frameBuffer, McEvent* event);

    /** Returns bounding box of shape. */
    //McBox2i getBoundingBox();

protected:
    void findPickedLine(McVec2i& p, int o, int&line, int& pidx,
                        float &mindist);
    //HxUniformScalarField3* getScalarField();
    HxLattice* getImageLattice();
    McVec2f pointReal3DTo2D(McVec3f& p3,int o);
    void removeLine(int which);
    void setHighlighted(int lidx, int shift=0, int ctrl=0);
    virtual void createWidget(QWidget* parent);
    void getHighlighted(McDArray<int>& hl);
    void setGroup(int group,int define,int clear);
    void selectSubTree();
    QxPushButton* gb1,*gb2;
protected slots:
    void joinLines();
    void removeLines();
    void splitLines();
    void setRoot();
    void groupButton1();
    void groupButton2();
};

#endif

/// @}