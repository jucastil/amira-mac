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
#ifndef PZ_SETTINGS
#define PZ_SETTINGS

#include <hxplot/PzPlotWinDLLApi.h>

#include <amiramesh/HxParamBundle.h>
#include <hxplot/PzPlotData.h>

/**
   Class for holding a bounding box.
@author Olaf Paetsch
*/
class PzBndBox {

  public:

    /// The variables holding the bounding box
    float blX, blY, trX, trY;

    /// Constructor
    PzBndBox(float xbl, float ybl, float xtr, float ytr)
             { blX = xbl; blY = ybl; trX = xtr; trY = ytr; }

    /// Default Constructor
    PzBndBox() { blX = 0; blY = 0; trX = 1.; trY = 1.; }

    /// set bottom left corner if less than old one and top right if greater
    void update(float xbl, float ybl, float xtr, float ytr);

    /// sets new values
    void set(float xbl, float ybl, float xtr, float ytr)
            { blX = xbl; blY = ybl; trX = xtr; trY = ytr; }

    /// sets new values with center and range
    void setCenter(float xcenter, float ycenter, float xrange, float yrange)
             { blX = xcenter - xrange/2; blY = ycenter - yrange/2;
               trX = xcenter + xrange/2; trY = ycenter + yrange/2;
             }

    /// multiplies the box by the given multiplicator
    void mult(float factor);

    /// multiplies the box by the given multiplicator
    PzBndBox operator*(float factor);

    ///
    PzBndBox operator=(PzBndBox b)
             { blX = b.blX; blY = b.blY; trX = b.trX; trY = b.trY;
               return *this;
             }
};

class PzLegend;
class PzPlotGroup;
class PzColormap;
class PzBaseAxis;

/**
   Class for storing the current plot settings. An instance of that class
   is used by the plot objects to store and get attributes important for
   other plot objects.
@author Olaf Paetsch
*/
class HXPLOT_API PzSettings : public HxParamBundle {

  private:

    static int _standAlone;
    static int _clone;
    bool       iamClone;

  protected:

    PzBndBox currWorldCords;
    PzBndBox currArea;

    int objectCounter;

    PzLegend*    currLegend;
    PzColormap*  currColormap;
    PzPlotData*  currPlotData;
    PzPlotGroup* currGroup;
    PzBaseAxis*  currAxis;
    PzPlotGroup* theAnchor;

    PzPlotData::PzTimeUnit   globalTimeUnit;
    float                    globalTimeBase;
    int                      globalTimeRange;

    static void inhibitStandAlone();

    static void inhibitClone();

  public:

    int isInitialized;

    ///
    PzBndBox totalRange;
    ///
    PzBndBox groupRange;
    ///
    PzBndBox currRange;
    ///
    PzSettings(PzPlotGroup* group = NULL);

    ///
    ~PzSettings();

    ///
    void copySettings(PzSettings* from);

    ///
    void initSettings();

    ///
    void initRange();

    ///
    void setWorld(PzBndBox world) { currWorldCords = world; };

    ///
    void setArea(PzBndBox area) { currArea = area; };

    ///
    PzBndBox getWorld() { return currWorldCords; };

    ///
    PzBndBox getArea() { return currArea; };

    ///
    PzPlotData::PzTimeUnit getTimeUnit() { return globalTimeUnit; }

    ///
    float getTimeBase() { return globalTimeBase; }

    ///
    int getTimeRange() { return globalTimeRange; }

    ///
    int getObjectCounter() { return objectCounter; }

    ///
    void incrementObjectCounter() { objectCounter++; }

    ///
    void resetObjectCounter() { objectCounter = 0; }

    ///
    void setCurrLegend(PzLegend* legend) { currLegend = legend; }

    ///
    PzLegend* getCurrLegend() { return currLegend; }

    ///
    void setCurrColormap(PzColormap* colormap) { currColormap = colormap; }

    ///
    PzColormap* getCurrColormap() { return currColormap; }

    ///
    void setCurrPlotData(PzPlotData* plotdata) { currPlotData = plotdata; }

    ///
    PzPlotData* getCurrPlotData() { return currPlotData; }

    ///
    void setTheAnchor(PzPlotGroup* anchor) { theAnchor = anchor; }

    ///
    PzPlotGroup* getTheAnchor() { return theAnchor; }

    ///
    void setCurrAxis(PzBaseAxis* axis) { currAxis = axis; }

    ///
    PzBaseAxis* getCurrAxis() { return currAxis; }

    ///
    PzPlotGroup* getCurrGroup() { return currGroup; }

    ///
    void show(FILE* fp, const char* name);

    ///
    void updateRange(float xbl, float ybl, float xtr, float ytr);

    ///
    void updateTimeProps(PzPlotData::PzTimeUnit timeunit, float timebase,
                         int timerange);

    ///
    static void setStandAlone();

    ///
    static bool isStandAlone();

    /** sets, that the next created plot window is a clone.
        Only used internally.
    */
    static void setClone();

    /** returns true if the plot window is a clone of an existing plot.
        Only used internally.
    */
    bool isClone();

    /** returns true if an existing plot area can be cloned.
        Only used internally.
    */
    static bool canClone();

    ///
    friend class PzGenPlot;
};

#endif

/// @}
