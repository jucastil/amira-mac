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
#ifndef GiSNAKES_FILTER_H
#define GiSNAKES_FILTER_H

#include <qobject.h>

#include "GiFilter.h"


#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include "Contour2D.h"
#include "GiSnakes.h"


class McBox2i;
class McEvent;
class GiViewer;
class GiFrameBuffer;
class Gi;
class QCheckBox;
class QWidget;
///
class GiSnakesFilter : public QObject,public GiFilter { 

    Q_OBJECT
  public:
    /// Constructor. 
    GiSnakesFilter(Gi* theGi);

    /// Destructor. 
    ~GiSnakesFilter();
    
    ///Draw this shape into the specified frame buffer. 
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box);

    /// Draw this shape into the specified frame buffer.
    /// @return true if the event has been handled by this object 
    int handleEvent(GiFrameBuffer* frameBuffer,McEvent* event);

    /// Returns bounding box of shape. 
    McBox2i getBoundingBox();

    /// Initializes Snakes3D Class.  
    void init();

    /// Get contour (or contour from selection) of current slice out of 
    /// contour Array and call Snakes3D's deform.
    /// Put deformed contour into contour array and convert it to selection
    void oneStep();    


    /// Extrapolated distance field from distance fields of contours 
    /// in slice (n) and (n-1) copied into selection.  
    /// If up is true, extrapolation is up otherwise down.
    void  extrapolDistField(int go, int up);

    /// Extrapolate current contour to next slice using the Gradient
    //    void  extrapolGradient(int go, int up);

    /// Extrapolate contour in slice (n+1) out of contours in slice (n) 
    /// and (n-1) and copy resulting contour into contour array.
    /// Call oneStep() if flag go is true. Extrapolate up if up is true,
    /// otherwise down.
    //    void extrapolContours(int go, int up);
    
    /// Which parametrization is used (ordinary, spline, fourier)
    static int whichSnakes3D;
    
    /// Extrapolating contours using frechet distance
    //static int frechet;
	
  protected:


    //Gi* theGi;        
    GiSnakes snakes3D;

    int whichExtrapol;

    /// Contour that has to be rendered.
    Contour2D* currentContour;

    /// All contours that have been achieved in first segmentation step.
    /// Is used for contour extrapolation
    McDArray<McHandle<Contour2D> > contours;
    
    /// checks wether init has to be executed
    int firstTime;

    int lastOrientation;

    /// Call relax from Class ContourStack to perform second segmentation
    /// step.
    //void relax3D();
    //void relax3D_2();

    /// Delete all but largest loop in contour
    //void keepLargestLoop(Contour2D& contour);

    /// Get contour in slice out of contour array.  
    /// In case it is not valid or if there is none at all, a contour will be
    /// calculated out of the current selection in that slice.
    Contour2D* getContour(int slice);
 
    /// Check whether contour in contour array is still up to date
    //int isValid(int slice);

    virtual QWidget* createWidget(QWidget* parent);    
    QCheckBox* _wExtrapol;
    QCheckBox* _w3D;
    QWidget* _wBase;
    
    void undo();
    //static void undoCB(Widget, XtPointer, XtPointer);
 
protected slots:
    void adjust();
    void relax();
    void up();
    void down();
    void hideWidget();
};

#endif

/// @}
