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
#ifndef PZ_BASEAXIS
#define PZ_BASEAXIS

#include <hxplot/PzPlotObject.h>
#include <hxplot/PzGrid.h>
#include <hxplot/PzAnnotation.h>

#define LOGMIN 10e-12
#define DEG2RAD 0.017453293

#define ALIGN_FREE  -1
#define ALIGN_BOTTOM 0
#define ALIGN_CENTER 1
#define ALIGN_TOP    2
#define ALIGN_UPPER  0
#define ALIGN_INNER  0
#define ALIGN_LOWER  2
#define ALIGN_OUTER  2
#define ALIGN_ABOVE  3
#define ALIGN_UNDER  4

#ifndef PzCASE3
#define PzCASE3(s, c0, c1, c2) (((s)==0) ? (c0) : (((s)==1) ? (c1) : (c2)))
#endif

#define AXIS_MTICK_LENGTH 0.02
#define AXIS_STICK_LENGTH 0.01
#define ARROW_LENGTH 0.04
#define ARROW_WIDTH_FAC 0.20

#define Xdc2nc(dc) (float)dc / (float)currView.width
#define Ydc2nc(dc) (float)dc / (float)currView.height

/**
   Baseclass for Axes of different type
@author Olaf Paetsch
*/
class HXPLOT_API PzBaseAxis : public PzPlotObject {

  public:

    ///
    enum PzAxisType {               SHO=  1,
                      NONE_LIN=  2, LIN=  3,
                      NONE_LOG=  4, LOG=  5,
                      NONE_RAD=  8, RAD=  9,
                      NONE_DEG= 16, DEG= 17,
                      NONE_TIME=32, TIME=33 };

  private:

    void initDefaults();

  protected:

    PzBndBox   currWorld, currAutoWorld;
    PzBndBox   currArea;
    float      ncCharWidth, ncCharHeight; 
    PzCol colour;
    int linetype;
    float linewidth;
    PzAxisType theType[2];
    float theMin[2], theMax[2];
    float firstTick[2], deltaTick[2];
    int numTicks[2], numSubticks[2];
    int innerTicks[2], niceNum[2], arrow[2];
    int autoLabel[2], autoTicks[2], automatic[2];
    char* labelFormat[2];
    char* axisLabel[2];
    char** Tlabels[2];
    McDArray<float> Tvalues[2];
    PzFont* theFont;
    PzViewport currView;

    McDArray<PzAnnotation*> axisLabels;

    McDArray<PzBndBox> minmaxStack;

    void updateSettings();

    ///
    PzBaseAxis(const char* name, const int type,
               PzAxisType xType, PzAxisType yType, PzBndBox world);

    ///
    ~PzBaseAxis();

  public:

    virtual const char* className() { return "PzBaseAxis"; }
            
    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object
    virtual void render(PzGenDraw* drawable);

    /// sets object's name together with the name of the annotation objects
    virtual void setName(const char *);

    ///
    virtual bool setAllAttr(PzBaseObject* fromObj);

    ///
    void setType(int xORy, PzAxisType type) { theType[xORy] = type; }

    ///
    PzAxisType getType(int xORy) { return theType[xORy]; }

    ///
    void setMinMax(int xORy, float min, float max);

    ///
    void setMinMax(PzBndBox world);

    ///
    void setMinMax(float xmin, float xmax, float ymin, float ymax);

    ///
    PzBndBox getMinMax();

    ///
    int getMinMax(float &xmin, float &xmax, float &ymin, float &ymax);

    ///
    int getAutoMinMax(float &xmin, float &xmax, float &ymin, float &ymax);

    ///
    void setDeltaTick(int xORy, float delta);

    ///
    float getDeltaTick(int xORy) { return deltaTick[xORy]; }

    /// sets the position/value of the first tick of axis @p xORy
    void setFirstTick(int xORy, float first);

    /** set the positions/values of the first tick of axis @p xORy to the min
        vals.
    */
    void setFirstTick(int xORy);

    /// set the positions/values of the first ticks of all axes to the min vals
    void setFirstTicks();

    ///
    float getFirstTick(int xORy) { return firstTick[xORy]; }

    ///
    void setTickLabels(int xORy, char **tlabels = NULL);

    /// sets the values where to place the main tickmarks
    void setTickValues(int xORy, int num, float* values);

    /// returns the tick values
    int getTickValues(int xORy, float** values);

    /// sets the label of axis @ xORy
    void setAxisLabel(int xORy, const char* label);

    /// returns the label of axis @ xORy
    char* getAxisLabel(int xORy) { return axisLabel[xORy]; }

    /// returns the label of axis @ xORy as a pointer to the annotation object
    PzAnnotation* getAxisLabelAsAnnotation(int xORy);

    /// sets the format for labelling the axis ticks of axis @ xORy
    void setTickFormat(int xORy, char* format);

    /// returns the format for labelling the axis ticks of axis @ xORy
    char* getTickFormat(int xORy) { return labelFormat[xORy]; }

    /// returns pointer to the grid child
    PzGrid* getGrid();

    ///
    static void makeTickValues(McDArray<float> &values, float start, float end,
                               int num, float delta);

    ///
    static char** makeLinTickLabels(McDArray<float> values,
                                    char*  format = "%f",
                                    float  factor = 1.0,
                                    float  offset = 0.0);

    ///
    static char** makeLogTickLabels(McDArray<float> values,
                                    char*  format = "%5.1e",
                                    float  factor = 1.0,
                                    float  offset = 0.0);

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

};

#endif /* PZ_BASEAXIS */

/// @}
