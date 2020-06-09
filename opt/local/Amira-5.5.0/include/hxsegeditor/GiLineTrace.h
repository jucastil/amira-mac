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
#ifndef GiLINETRACE_H
#define GiLINETRACE_H

#include <mclib/McVec2i.h>
#include <mclib/McVec2f.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <qobject.h>

#include "Gi.h"
#include "GiTool.h"
#include "IScissors.h"

class GiViewer;
class GiFrameBuffer;
class HxNeuronTree;
class HxUniformScalarField3;
class QCheckBox;

/** Implements a lasso tool. Free hand drawing, straight line segments,
    and constrained drawing are supported. Constrained drawing makes
    use of the Intelligent Scissors algorithm.
*/

class GiLineTrace : public QObject, public GiTool {
    Q_OBJECT
  public:
    /** Constructor. */
    GiLineTrace(Gi* theGi);

    /** Destructor. */
    ~GiLineTrace();

    virtual const char* getIconName() const{ return "SegLineTraceIcon.png"; }

    /** Draw this shape into the specified frame buffer. */
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box);

    /** Draw this shape into the specified frame buffer.
        @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer* frameBuffer, McEvent* event);

    /** Returns bounding box of shape. */
    McBox2i getBoundingBox();

    void handlePath(McDArray<McVec2i>& path);
    
    McVec2f pointReal3DTo2D(McVec3f& p3,int orientation);
    HxNeuronTree* getLineSet() { return lineSet;}
    void prepareLineSet();
  protected:
    inline int getCosts(int v1, int v2) {
	int costs = (2*dataWindow[1]) - (v1+v2);
	if (costs<1) costs=1;
	return costs;
    }
    float dataWindow[2];
    int startIdx;
    int traceOrientation;
    int getHighlighted();
    void setHighlighted(int l);
    void removeLine(int which);
    void findPickedLine(McVec2i& p, int orientation, int&line, int& point,float&);
    HxNeuronTree* lineSet;
    //HxUniformScalarField3* getScalarField();
    HxLattice* getImageLattice();

    int mode; // SUBTRACT (ctrl), ADD (shift), REPLACE (none)
    McVec2i currPos;
    McDArray<McVec2i> path;
    int autoTrace; // 0=free hand drawing, 1=intelligent scissors
    int sliceNumber; // slice for which iScissors are initialized
    IScissors iScissors;
    
    QCheckBox* wShow1,*wShow2,*wShow3, *wShow4;

    void finishInteraction(GiFrameBuffer*); // calls path.resize(0)

    void renderAutoTrace(GiFrameBuffer*, int, int, int, int, McBox2i&);
    void initAutoTracing(GiViewer* viewer);
    int startAutoTracing(GiFrameBuffer* frameBuffer, McVec2i& pos);
    int stopAutoTracing(GiFrameBuffer* frameBuffer, McEvent*, McVec2i& pos);
    int resetAutoTracing(GiFrameBuffer* frameBuffer, McEvent*, McVec2i& pos);
    int updateAutoTracing(GiFrameBuffer* frameBuffer, McVec2i& pos);
    void appendAutoTraceToPath(GiFrameBuffer* frameBuffer, const McVec2i&);

    virtual void createWidget(QWidget* parent);

  public slots:
    void setMMode(int);
    
};

#endif

/// @}
