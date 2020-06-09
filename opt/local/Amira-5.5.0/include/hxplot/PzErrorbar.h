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
#ifndef PZ_ERRORBAR
#define PZ_ERRORBAR

#include <hxplot/PzCurve.h>

/**
   Class featuring a curve plot object with possible errorbars.

@author Olaf Paetsch
*/
class HXPLOT_API PzErrorbar : public PzCurve {

  public:

    ///
    enum PzErrorbarType  { PzMAINLINE, PzBARLINE, PzHOSE, PzBOX, PzHISTOGRAM };
 
  private:

    void initDefaults();

    /// arrays containing x-y-values for filling
    McDArray<float> xx;
    McDArray<float> yy;

  protected:

    PzErrorbarType  howtoRender;
    PzCol           errorbarcolour;
    int             errorlinetype;
    float           errorlinewidth;
    bool            withErrorValues;

    ///
    void doCartesianError(int n, float* x, float* y, float* lowx, float* highx,
                          float* lowy, float* highy, PzErrorbarType renderType);

    ///
    void doPolarError(int n, float* pv, float* rv, float* lowr, float* highr,
                      PzErrorbarType renderType, bool pDeg = false);


    /// saves the data plot's own format
    virtual void saveAmpl(FILE* fp);

    /// saves the data in Amira's HxSpreadsheet format
    virtual void saveHxSpreadsheet(FILE* fp);

  public:

    ///
    PzErrorbar(const char* name, PzErrorbarType howto = PzBARLINE);

    ///
    PzErrorbar(const char* name, int len, float* vals, float* delta,
               PzErrorbarType howto = PzBARLINE);

    ///
    PzErrorbar(PzBaseObject* parent, const char* name,
               PzErrorbarType howto = PzBARLINE);

    ///
    PzErrorbar(PzBaseObject* parent, const char* name, int len, float* vals,
               float* delta, PzErrorbarType howto = PzBARLINE);

    virtual const char* className() { return "PzErrorbar"; }
            
    /// static object type
    static int getTypeId() { return PzERRORBAR; }

    ///
    ~PzErrorbar();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object 
    virtual void render(PzGenDraw* drawable);

    /// copies errorbar object
    virtual PzBaseObject* copy();

    /** creates at least one Errorbar and appends it to the given group.
        Assures unique names.
    */
    static PzErrorbar* create(McDArray<char*>names, PzPlotGroup* group,
                              PzPlotGroup* anchor, char* format,
                              McDArray< McDArray<float> > datain,
                              McDArray<int> segs, bool againstFirst = true);

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    /// sets the Y error values as deltas from main values
    int setDeltaY(int len, float* delta);

    /// sets the X error values as deltas from main values
    int setDeltaX(int len, float* delta);

    /// sets the low Y error values as absolute values
    int setLowY(int len, float* values);

    /// returns the low Y values (first set)
    int getLowY(float** values, bool log = false)
        { return theData->getValues(4,values,log); }

    /// returns the low Y values (next sets, call theData->incNext() before!)
    int getNextLowY(float** values, bool log = false)
        { return theData->getNextValues(4,values,log); }

    /// sets the high Y error values as absolute values
    int setHighY(int len, float* values);

    /// returns the high Y values (first set)
    int getHighY(float** values, bool log = false)
        { return theData->getValues(5,values,log); }

    /// returns the high Y values (next sets, call theData->incNext() before!)
    int getNextHighY(float** values, bool log = false)
        { return theData->getNextValues(5,values,log); }

    /// sets the low X error values as absolute values
    int setLowX(int len, float* values);

    /// returns the low X values (first set)
    int getLowX(float** values, bool log = false)
        { return theData->getValues(1,values,log); }

    /// returns the low X values (next sets, call theData->incNext() before!)
    int getNextLowX(float** values, bool log = false)
        { return theData->getNextValues(1,values,log); }

    /// sets the high X error values as absolute values
    int setHighX(int len, float* values);

    /// returns the high X values (first set)
    int getHighX(float** values, bool log = false)
        { return theData->getValues(2,values,log); }

    /// returns the high X values (next sets, call theData->incNext() before!)
    int getNextHighX(float** values, bool log = false)
        { return theData->getNextValues(2,values,log); }

    bool hasErrorValues() { return withErrorValues; }

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);
};

#endif /* PZ_ERRORBAR */

/// @}
