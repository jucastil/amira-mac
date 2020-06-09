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
#ifndef PZ_ANCURVE
#define PZ_ANCURVE

#include <hxplot/PzCurve.h>
#include <mclib/McSmallArray.h>
#include <mclib/McString.h>

#include <anna/AnnaExpression.h>

/**
   Class featuring a analytical curve plot object.

@author Olaf Paetsch
*/
class HXPLOT_API PzAnCurve : public PzCurve {

  private:

    //McDArray<char*> myVarnames; does not work! No idea why!?
    McSmallArray<McString,32> myVarnames;
    McSmallArray<PzCurve*,32> myCurves;

    void initDefaults();

    void findVarnames();

    void findCurves(PzPlotGroup* group);

    bool newFunction;
    bool functionChecked;

    /// evaluates the function on a given array of x-values
    void evalFunction(int n, double* xv);

  protected:

    AnnaExpression theExpression;
    McString theFunction;

    double _from, _to, _delta;

    /// evaluates the function
    void evalFunction();

    /// evaluates the function within a given interval
    void evalFunction(const double from, const double to, const double delta);

  public:

    ///
    PzAnCurve(const char* name, PzCurveType howto = PzLINECURVE);

    ///
    PzAnCurve(PzBaseObject* parent, const char* name,
              PzCurveType howto = PzLINECURVE);

    ///
    PzAnCurve(const char* name, const char* function,
              PzCurveType howto = PzLINECURVE);

    ///
    PzAnCurve(PzBaseObject* parent, const char* name, const char* function,
              PzCurveType howto = PzLINECURVE);

    virtual const char* className() { return "PzAnCurve"; }
            
    /// static object type
    static int getTypeId() { return PzANCURVE; }

    ///
    ~PzAnCurve();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object 
    virtual void render(PzGenDraw* drawable);

    /// copies curve object
    virtual PzBaseObject* copy();

    /// sets all attributes according to fromObj
    virtual bool setAllAttr(PzBaseObject* fromObj);

    /// sets a new function to be evaluated, returns 0 if function is ok
    virtual int setFunction(const char* f, bool checkfunc = true);

    /// returns the current function
    const char* getFunction() { return theFunction.getString(); }

    /// sets the function range explicitly 
    void setExplicitRange(const double from, const double to,
                          const double delta);

    /// returns the function range and the value of the 'explicit' attribute
    int getExplicitRange(double& from, double& to, double& delta);

    ///
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);
};

#endif /* PZ_CURVE */

/// @}
