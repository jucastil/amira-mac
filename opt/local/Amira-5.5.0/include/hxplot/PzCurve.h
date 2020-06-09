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
#ifndef PZ_CURVE
#define PZ_CURVE

#include <hxplot/PzPlotObject.h>
#include <hxplot/PzPlotData.h>


/**
   Class featuring a curve plot object.

   Defines attributes for setAttr/getAttr:
   
   @li curvetype (value = 
         
         @li 0 = line curve
         @li 1 = histogram
         @li 2 = marked curve
         @li 3 = marker
         @li 4 = impuls
         
   @li color (values = r, g, b [0 .. 1])
   @li linewidth (value = 0 .. 7)
   @li linetype (value = 
         
         @li 0 = no line
         @li 1 = line
         @li 2 = dashed line
         @li 3 = dash-dotted line
         @li 4 = dotted line
         
   @li markertype (value = 
         
         @li 0 = x
         @li 1 = +
         @li 2 = box
         @li 3 = rhomb
         @li 4 = triangle
         @li 5 = reverse triangle
         @li 6 = o
         @li 7 = dot
         
   @li markercolor (values = r, g, b [0 .. 1])
   @li inLegend (value = 0, 1)
   
@author Olaf Paetsch
*/
class HXPLOT_API PzCurve : public PzPlotObject {

  public:

    ///
    enum PzCurveType  { PzLINECURVE, PzHISTOGRAM, PzMARKEDCURVE, PzMARKER,
                        PzIMPULS };
 
  private:

    void initDefaults();

  protected:

    float theOrigMin[2], theOrigMax[2];
    int axisType[2];
    PzPlotData::PzTimeUnit axisTimeUnit;
    float axisTimeBase;
    PzCurveType  howtoRender;
    PzCol        colour, markercolour;
    int          linetype, markertype;
    int          markerfrequency, firstmarker, lastmarker;
    float        linewidth;
    int          inLegend, closed;

    McDArray<PzCol> datacolor;

    /** the data in x,y is the date to be displayed (maybe log), whereas
        xorg, yorg contains the original data.
    */
    void doCartesianShow(int n, float* x, float* y, float* xorg, float* yorg,
                         PzCurveType renderType);

    /** the data in pv,rv is the date to be displayed (maybe log), whereas
        xorg, yorg contains the original data.
    */
    void doPolarShow(int n, float* pv, float* rv, float* xorg, float* yorg,
                     PzCurveType renderType, bool pDeg = false);

    ///
    void getSettings();

    ///
    PzCurve(const char* name, PzCurveType howto, const int type);

    /// saves the data plot's own format
    virtual void saveAmpl(FILE* fp);

    /// saves the data in gnuplot format
    virtual void saveGnuplot(FILE* fp);

    /// saves the data in CSV (Comma Separated Values) format
    virtual void saveCSV(FILE* fp);

    /// saves the data in Amira's HxSpreadsheet format
    virtual void saveHxSpreadsheet(FILE* fp);

  public:

    ///
    PzCurve(const char* name, PzCurveType howto = PzLINECURVE);

    ///
    PzCurve(const char* name, int len, float* yv,
            PzCurveType howto = PzLINECURVE);

    ///
    PzCurve(const char* name, int len, float* xv, float* yv,
            PzCurveType howto = PzLINECURVE);

    ///
    PzCurve(PzBaseObject* parent, const char* name,
            PzCurveType howto = PzLINECURVE);

    ///
    PzCurve(PzBaseObject* parent, const char* name, int len, float* yv,
            PzCurveType howto = PzLINECURVE);

    ///
    PzCurve(PzBaseObject* parent, const char* name, int len, float* xv,
            float* yv, PzCurveType howto = PzLINECURVE);

    virtual const char* className() { return "PzCurve"; }
            
    /// static object type
    static int getTypeId() { return PzCURVE; }

    ///
    ~PzCurve();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object 
    virtual void render(PzGenDraw* drawable);

    /// copies curve object
    virtual PzBaseObject* copy();

    /// sets all attributes according to fromObj 
    virtual bool setAllAttr(PzBaseObject* fromObj);

    /// sets object's name together with the name of the data object
    virtual void setName(const char* name);

    /// sets the color for every data item
    virtual void setColors(int len, const float* rgba);

    /// shows a legend entry for 'this'. Called by PzLegend.
    virtual bool showLegend(PzGenDraw* drawable, float& xend, float& yend,
                            float x, float y, int legendtype);

    ///
    virtual void doLegendEntry(PzGenDraw* drawable, float X, float Y,
                               float length, int normtr = 0);

    /** creates at least one curve and appends it to the given group.
        Assures unique names.
    */
    static PzCurve* create(McDArray<char*>names, PzPlotGroup* group, 
                           PzPlotGroup* anchor,
                           McDArray< McDArray<float> > datain,
                           McDArray<int> segs, bool againstFirst = true);

    /** creates one curve and appends it to the given group.
        Assures unique name.
    */
    static PzCurve* create(const char* name, PzPlotGroup* group,
                           PzPlotGroup* anchor, McDArray<float> x,
                           McDArray<float> y, McDArray<int> segs);

    ///
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual void saveData(FILE* fp, int format);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);
};

#endif /* PZ_CURVE */

/// @}
