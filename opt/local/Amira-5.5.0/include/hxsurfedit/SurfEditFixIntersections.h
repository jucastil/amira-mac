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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef SURF_FIX_INTER_H
#define SURF_FIX_INTER_H

#include "SurfEditTool.h"
#include "SurfaceUndo.h"

class QDialog;
class QRadioButton;
class QRadioButton;
class QxLineEdit;

/// Tool for automatically repairing intersections
class SurfEditFixIntersections : public SurfEditTool {

  Q_OBJECT

  public:
    SurfEditFixIntersections(HxSurfEdit* surfEdit);

    ~SurfEditFixIntersections();

    virtual void activate(int);

    void close();

    virtual void selectionChanged();

    int doIt();

  public slots:
    void fix();

  protected:
    QDialog* dialog;
    QRadioButton* highlightBtn;
    QRadioButton* allBtn;

    void sortEdgeList(McDArray<int> &edgeList,
		      McDArray<McVec3f> &intsctPnts);

    void collectVertices(McDArray<int> &edgeList,
			 McDArray<McVec2i> &vertList);

    void updateEdgeList(int center,
			McDArray<int> &edgeList,
			McDArray<McVec3f> &intsctPnts);

    McVec3f getCenterOfIntersections(McDArray<McVec3f> &intsctPnts);

    int findOrientation(int jTri, int i1, int i2);

    int findOrientation2(int iTri, McVec3f &normal);

    void processStack(int &center, McVec3f &normal, McDArray<int> &stack,
		      McSmallArray<int,6> &triList, McDArray<int> &markTri,
		      McDArray<int> &patchOrientations);

    int findSeed(McDArray<int> &markTri, int &seed);

    McVec3f getNormal(int center, McDArray<int> &edgeList);

    void updateMode();
    void createDialog(QWidget* parent);

  private:

    /// the implementation of undoable
    SurfaceUndo* surfaceUndo;
};

#endif

/// @}
