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

/// @addtogroup hxplot hxplot
/// @{
#ifndef PZ_PLOTAREA
#define PZ_PLOTAREA

#include <hxplot/PzPlotGroup.h>

class PzGenDraw;

/**
   Class featuring a drawing area plot object within plot window.
   The class acts also as a grouping object for plot objects.
@author Olaf Paetsch
*/
class HXPLOT_API PzPlotArea: public PzPlotGroup {

  private:

    /// Contains given area.
    PzBndBox  Area;

    /// Contains given area relative to surrounding (previously given) area.
    PzBndBox  relArea;

    void initDefaults();

    void drawHandle(float x, float y, int size = 8);

    /// Used as callback axis if in interactive mode
    static void moved(float startx, float starty, float dx, float dy,
                      int modifier, PzPlotObject* pobj);

  protected:

    /// Destructor.
    ~PzPlotArea();

    void updateSettings();

  public:

    /// Constructor.
    PzPlotArea(const char* name, PzBndBox area);

    /// Constructor.
    PzPlotArea(const char* name);

    /// Constructor with parent plotgroup.
    PzPlotArea(PzBaseObject* parent, const char* name, PzBndBox area);

    /// Constructor with parent plotgroup.
    PzPlotArea(PzBaseObject* parent, const char* name);

    virtual const char *className() { return "PzPlotArea"; }

    /// Static object type.
    static int getTypeId() { return PzPLOTAREA; }

    ///
    virtual bool isGraphicsObject() { return true; }

    /** Updates plot object and global settings prior to rendering.
        Calls 'update' to all objects in group before.
    */
    virtual void update(PzGenDraw *theDrawable);

    /// Renders plot object. Before that it renders all objects in group.
    virtual void render(PzGenDraw *theDrawable);

    /// Copies this object.
    virtual PzBaseObject *copy();

    /// Saves this objects properties.
    virtual void save(FILE* fp, char* globalName);

    /// Sets all attributes according to fromObj.
    virtual bool setAllAttr(PzBaseObject* fromObj);

    /** Sets the plotting area in normalized coordinates.
        x|y bl = bottom left, x|y tr = top right.
    */
    void setArea(float xbl, float ybl, float xtr, float ytr);

    /// Sets the plotting area in normalized coordinates.
    void setArea(PzBndBox area) { Area = area; }

    /** Gets the plotting area in normalized coordinates.
        x|y bl = bottom left, x|y tr = top right.
    */
    void getArea(float &xbl, float &ybl, float &xtr, float &ytr);

    /// Returns the plotting area in normalized coordinates.
    PzBndBox getArea() { return Area; }

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

};

#endif /* PZ_PLOTAREA */

/// @}
