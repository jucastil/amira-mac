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
#ifndef PZ_DRAWAREA
#define PZ_DRAWAREA

#include <hxplot/PzPlotObject.h>

/**
   Class featuring a drawing area plot object within plot window.
@author Olaf Paetsch
*/
class HXPLOT_API PzDrawArea: public PzPlotObject {

  private:

    /// contains given area
    PzBndBox  Area;

    /// contains given area relative to surrounding (previously given) area
    PzBndBox  relArea;

    void initValues();

  protected:

    /// Destructor
    ~PzDrawArea();

    void updateSettings();

  public:

    /// Constructor
    PzDrawArea(const char* name, PzBndBox area);

    /// Constructor
    PzDrawArea(const char* name);

    /// Constructor with parent plotgroup
    PzDrawArea(PzBaseObject* parent, const char* name, PzBndBox area);

    /// Constructor with parent plotgroup
    PzDrawArea(PzBaseObject* parent, const char* name);

    virtual const char* className() { return "PzDrawArea"; }

    /// static object type
    static int getTypeId() { return PzDRAWAREA; }

    ///
    virtual bool isGraphicsObject() { return true; }

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* theDrawable);

    /// renders plot object 
    virtual void render(PzGenDraw* theDrawable);

    /// copies this object
    virtual PzBaseObject* copy();

    /// saves the state of this object
    virtual void save(FILE* fp, char* globalName);

    ///
    void setArea(float, float, float, float);
    ///
    void setArea(PzBndBox area) { Area = area; }

    ///
    void getArea(float &xbl, float &ybl, float &xtr, float &ytr);
    ///
    PzBndBox getArea() { return Area; }

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

};

#endif /* PZ_DRAWAREA */

/// @}
