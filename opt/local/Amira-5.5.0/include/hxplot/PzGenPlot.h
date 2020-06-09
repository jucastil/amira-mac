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
#ifndef PZ_GENPLOT
#define PZ_GENPLOT

#ifdef _WIN32
#include <windows.h>
#endif

#include <hxplot/PzPlotWinDLLApi.h>

#include <stdlib.h>
#include <mclib/McHandable.h>
#include <mclib/McDArray.h>

#include <hxplot/PzPlotArea.h>

class PzSettings;
class PzPlot;

typedef void PzPlotUpdateCB(PzPlot* plot, void* userdata);

typedef void PzPlotInputCB(PzPlot* plot, void* userdata, PzPlotObject* pobj,
                           McDArray<float>x, McDArray<float>y);

typedef void PzPlotAreaCB(PzPlot* plot, void* userdata, PzPlotArea* area,
                          float x, float y, int ix, int iy);

/**
   Plot base class.
@author Olaf Paetsch
*/
class HXPLOT_API PzGenPlot: public McHandable {

private:

    const char *_name;

protected:

    /// Constructor
    PzGenPlot(const char *name);

    /// Destructor
    ~PzGenPlot();

    PzPlotArea *theAnchor;
    PzSettings *theSettings;

    McDArray<PzPlotUpdateCB*> updateCallbacks;
    McDArray<void*>           updateUserdata;

    McDArray<PzPlotInputCB*>  inputCallbacks;
    McDArray<void*>           inputUserdata;

    PzPlotAreaCB*             areaCallback;
    void*                     areaUserdata;

    // set a new name. Should only be used by derived classes.
    void setName(const char* newname);

public:

    virtual const char* className() { return "PzGenPlot"; }

    ///
    const char *theName() { return _name; }

    ///
    virtual void update();

    ///
    PzPlotArea *getAnchor() { return theAnchor; }

    /// returns reference count
    int getRefCount() { return refcount; }

    /** Sets the callback to be invoked whenever the plot is updated.
        Update callbacks from different module instances are distinguished
        by the clientdata.
        The callback is invoked as:
        (*PzPlotUpdateCB)(PzPlot* plotmodule, void* clientdata);
    */
    void setUpdateCallback(PzPlotUpdateCB* clientFunc, void* clientdata);

    /// Unsets the callback above if the clientdata is the same
    void unsetUpdateCallback(void* clientdata);

    /** Sets the callback to be invoked whenever lines resp. polygons are
        entered interactively. I.e after hitting the Escape-key to end
        the input.
        Input callbacks from different module instances are distinguished
        by the clientdata.
        The callback is invoked as:
        (*PzPlotInputCB)(PzPlot* plotmodule, void* clientdata,
                         McDArray<float>x, McDArray<float>y);
    */
    void setInputCallback(PzPlotInputCB* clientFunc, void* clientdata);

    /// Unsets the callback above if the clientdata is the same
    void unsetInputCallback(void* clientdata);

};

#endif

/// @}
