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
#ifndef PZ_TIMEAXIS
#define PZ_TIMEAXIS

#include <hxplot/PzAxis.h>
#include <hxplot/PzPlotData.h>

class PzPlotObject;

/**
   Class for cartesian (both X and Y) Axis (linear and logarithmic).
   Uses a horizontal (x) axis specially adopted to display time values,
   like minutes, hours, days, month, and the like.
@author Olaf Paetsch
*/
class HXPLOT_API PzTimeAxis : public PzAxis {

  private:

  protected:

    PzAxisIntersectmode theIntersection[2];
    float thePosition[2], theOppPosition[2];

    PzPlotData::PzTimeUnit theTimeUnit;
    float theTimeBase;
    int theTimeRange;

    void initDefaults();

    virtual bool prepareTimeAxis(float lFac, float lExpo);

    void doHorizontalAxis(float factor, float offset, float posFactor,
                          float posOffset, bool reverse, bool labelIt = true);

    void doDateText(float x, float y, float dy, char* label, char** l1,
                    char** l2, char** l3, int linebreak = 0);

    void updateSettings();

  public:

    ///
    PzTimeAxis(const char* name, PzAxisType xType = LIN,
               PzBndBox world = PzBndBox(0,0,1.,1.));

    /// Constructor with parent group
    PzTimeAxis(PzBaseObject* parent, const char* name,
               PzAxisType yType = LIN, PzBndBox world = PzBndBox(0,0,1.,1.));

    virtual const char *className() { return "PzTimeAxis"; }

    /// static object type
    static int getTypeId() { return PzTIMEAXIS; }
            
    ///
    ~PzTimeAxis();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw *drawable);

    /// renders plot object 
    virtual void render(PzGenDraw *drawable);

    /// copies this object
    virtual PzBaseObject *copy();

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    ///
    static char** makeTimeTickLabels(McDArray<float> values,
                                     PzPlotData::PzTimeUnit timeunit,
                                     float timebase, int timerange,
                                     char* timeformat = NULL,
                                     char* format = "%f",
                                     float factor = 1.0,
                                     float offset = 0.0);
 
    ///
    static void makeniceTime(float& min, float& max, int& numticks,
                             float& firsttick, float& deltatick,
                             PzPlotData::PzTimeUnit timeunit,
                             float timebase, int timerange);

    ///
    static void makeTimeTickValues(McDArray<float> &values, int& nsubticks,
                                   float start, float end, int num, float delta,
                                   bool nicenums,
                                   PzPlotData::PzTimeUnit timeunit,
                                   float timebase, int timerange);


    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

};

#endif /* PZ_TIMEAXIS */

/// @}
