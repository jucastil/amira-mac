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
#ifndef PZ_LEGEND
#define PZ_LEGEND

#include <hxplot/PzPlotObject.h>
#include <hxplot/PzBaseGroup.h>

class PzAnnotation;

/**
   Class featuring a legend plot object.
@author Olaf Paetsch
*/
class HXPLOT_API PzLegend: public PzPlotObject, public PzBaseGroup {

  public:

    ///
    enum PzLegendType { LEGENDBLOCK = 0,
                        NAMEBLOCK   = 1,
                        NAMELIST    = 2
                      };

  private:

    float currX, currY;
    float maxX, maxY;
    int   currRow, currCol;
    int   prevLegendtype;
    PzBndBox currArea;

    void initValues();

    /// used as callback for a cartesian axis if in interactive mode
    static void moved(float startx, float starty, float dx, float dy,
                      int modifier, PzPlotObject* pobj);

  protected:

    float startX, startY;
    float delta;
    int   numRows, numCols;

    /// Destructor
    ~PzLegend();

    void updateSettings();

  public:

    /// Constructor
    PzLegend(const char* nameOfObject, float x, float y);

    /// Constructor
    PzLegend(const char* nameOfObject);

    /// Constructor with parent group
    PzLegend(PzBaseObject* parent, const char* nameOfObject, float x, float y);

    /// Constructor
    PzLegend(PzBaseObject* parent, const char* nameOfObject);

    virtual const char *className() { return "PzLegend"; }

    /// static object type
    static int getTypeId() { return PzLEGEND; }

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw *theDrawable = NULL);

    /// render plot object 
    virtual void render(PzGenDraw *theDrawable = NULL);

    /// Copies this
    virtual PzBaseObject* copy();

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual bool setAllAttr(PzBaseObject* fromObj);

    ///
    void setStart(float x, float y) { startX = x; startY = y; }

    ///
    void getStart(float &x, float &y) { x = startX; y = startY; }

    ///
    void setDelta(float d) { delta = d; }

    ///
    float getDelta() { return delta; }

    /** sets the number of rows or columns the legend uses.

        Assures that only one of \p rows or \p cols is positiv.
        A negative value means that there are as meny entries as needed
        in the legend.
    */
    void setRowCol(int rows, int cols);

    ///
    void getRowCol(int &rows, int &cols) { rows = numRows; cols = numCols; }

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

};

#endif /* PZ_LEGEND */

/// @}
