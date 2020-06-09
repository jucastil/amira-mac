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
#ifndef PZ_AXIS
#define PZ_AXIS

#include <hxplot/PzBaseAxis.h>

class PzPlotObject;

/**
   Class for cartesian (both X and Y) Axis (linear and logarithmic).
@author Olaf Paetsch
*/
class HXPLOT_API PzAxis : public PzBaseAxis {

  public:

    ///
    enum PzAxisIntersectmode { min_int, mid_int, max_int, zero_int, user_int };
 
  protected:

    PzAxisIntersectmode theIntersection[2];
    float thePosition[2], theOppPosition[2];
    int showBox;

    /// used as callback for a cartesian axis if in interactive mode
    static void zoom(float startx, float starty, float dx, float dy,
                     int modifier, PzPlotObject* pobj);

    /// used as callback for a cartesian axis if in interactive mode
    static void resetZoom(float startx, float starty, int modifier,
                          PzPlotObject* pobj);

    /// used as callback for a cartesian axis if in interactive mode
    static void zoomInOut(const char* key, float x, float y, int modifier,
                          PzPlotObject* pobj);

    virtual bool prepareAxis(int xORy, float lFac, float lExpo,
                             bool logsubticks);

    virtual void initDefaults();

    virtual void doHorizontalAxis(float factor, float offset, float posFactor,
                                  float posOffset, bool reverse,
                                  bool labelIt = true);

    virtual void doVerticalAxis(float factor, float offset, float posFactor,
                                float posOffset, bool reverse,
                                bool labelIt = true);

    virtual void updateSettings();

  public:

    ///
    PzAxis(const char* name, PzAxisType xType = LIN, PzAxisType yType = LIN,
           PzBndBox world = PzBndBox(0,0,1.,1.));

    /// Constructor with parent group
    PzAxis(PzBaseObject* parent, const char* name, PzAxisType xType = LIN,
           PzAxisType yType = LIN, PzBndBox world = PzBndBox(0,0,1.,1.));

    virtual const char *className() { return "PzAxis"; }

    /// static object type
    static int getTypeId() { return PzAXIS; }
            
    ///
    ~PzAxis();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw *drawable);

    /// renders plot object 
    virtual void render(PzGenDraw *drawable);

    /// copies this object
    virtual PzBaseObject *copy();

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    ///
    void setIntersection(int xORy, int mode, float intersect = 0);

    ///
    void getIntersection(int xORy, int &mode, float &intersect);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
};

#endif /* PZ_AXIS */

/// @}
