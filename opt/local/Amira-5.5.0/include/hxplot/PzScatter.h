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
#ifndef PZ_SCATTER
#define PZ_SCATTER

#include <hxplot/PzCurve.h>

class PzColormap;

/**
   Class featuring a scatter plot object with a third value used for colouring

   Defines attributes for setAttr/getAttr:

   @li color (values = r, g, b [0 .. 1])

   @li markertype (value =

         @li 0 = x
         @li 1 = +
         @li 2 = box
         @li 3 = rhomb
         @li 4 = triangle
         @li 5 = reverse triangle
         @li 6 = o
         @li 7 = dot
         @li ...

   @li inLegend (value = 0, 1)
   @li firstmarker (value = [0 .. n])
   @li markerfrequency (value = [1 .. n/2])
   @li inlegend (value = 0, 1)
   @li usecolormap (value = 0, 1)

@author Olaf Paetsch
*/

class HXPLOT_API PzScatter : public PzCurve {

  public:

    ///
    enum PzScatterType  { PzSIZEDPOINTS, PzCOLOREDPOINTS, PzCOLSIZEDPOINTS };
 
  private:

    void initDefaults();

  protected:

    PzScatterType  howtoRender;

    ///
    void doCartesianScatter(int n, float* x, float* y, float* z,
                            PzScatterType renderType);

    ///
    void doPolarScatter(int n, float* pv, float* rv, float* z,
                        PzScatterType renderType, bool pDeg = false);


    /// saves the data plot's own format
    virtual void saveAmpl(FILE* fp);

    /// saves the data in Amira's HxSpreadsheet format
    virtual void saveHxSpreadsheet(FILE* fp);

    PzColormap* currCmap;
    int cmapAutomatic;
    float zmin, zmax;

  public:

    ///
    PzScatter(const char* name, PzScatterType howto = PzCOLOREDPOINTS);

    ///
    PzScatter(const char* name, int len, float* xv, float* yv, float* zv,
              PzScatterType howto = PzCOLOREDPOINTS);

    ///
    PzScatter(PzBaseObject* parent, const char* name,
              PzScatterType howto = PzCOLOREDPOINTS);

    ///
    PzScatter(PzBaseObject* parent, const char* name, int len, float* xv,
              float* yv, float* zv, PzScatterType howto = PzCOLOREDPOINTS);

    virtual const char* className() { return "PzScatter"; }
            
    /// static object type
    static int getTypeId() { return PzSCATTER; }

    ///
    ~PzScatter();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object 
    virtual void render(PzGenDraw* drawable);

    /// copies errorbar object
    virtual PzBaseObject* copy();

    /// sets object's name together with the name of the data object
    virtual void setName(const char* name);

    /// shows a legend entry for 'this'. Called by PzLegend.
    virtual bool showLegend(PzGenDraw* drawable, float& xend, float& yend,
                            float x, float y, int legendtype);

    ///
    virtual void doLegendEntry(PzGenDraw* drawable, float x, float y,
                               float length, int normtr = 0);

    /** creates at least one Scatter object and appends it to the given group.
        Assures unique names.
    */
    static PzScatter* create(McDArray<char*>names, PzPlotGroup* group,
                              PzPlotGroup* anchor, char* format,
                              McDArray< McDArray<float> > datain,
                              McDArray<int> segs, bool againstFirst = true);

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

    ///
    PzColormap* getTheColormap();
};

#endif /* PZ_SCATTER */

/// @}
