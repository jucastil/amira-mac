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
#ifndef PZ_PLOTOBJECT
#define PZ_PLOTOBJECT

#include <hxplot/PzPlotWinDLLApi.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <hxplot/PzBaseObject.h>
#include <hxplot/PzPlotData.h>
#include <hxplot/PzSettings.h>
#include <hxplot/PzGenDraw.h>

class PzAnnotation;
/**
   @brief Base class for all plot objects.

   Plot objects are objects which
   display something or which are grouping objects.

   This class maintains an optional Tcl-Script which will be evaluated
   every time the object is updated. (PzPlotObject::setScript) 

   Within that Tcl-script the string \e this is substituted by the
   name of the current plot object.
   A script snippet which echoes the mean value of a curve (here \e LineProbe
   of Amira's LineProbe module) can be set by means of the Tcl-commands like
   this:
   \verbatim
   $thePlot LineProbe setScript {set mean [eval this getMean]; echo "mean of [eval this getLabel] = $mean"}
   \endverbatim

   There may be also a Tcl-procedure defined which is called whenever
   a plot object is instantiated. The naming conventions for that
   procedure are <em>classname</em><tt>.init</tt> (e.g. \c PzCurve.init ).
   This procedure has one parameters: \a objname which is the name
   of the just created plot object.
   The procedure
   is called after the setting of the default values and can be used for
   instance to set different colours for curves if there are more than one.
   A procedure skeleton which sets the colour for all curves to yellow 
   on creation looks like this:
   \verbatim
   proc PzCurve.init { objname } {
        global thePlot

        echo This is PzCurve.init for $objname
        eval $thePlot $objname setAttr color 1 1 0
   }
   \endverbatim


@author Olaf Paetsch
*/


class HXPLOT_API PzPlotObject: public PzBaseObject {

  private:

    void initDefaults();

  protected:

    // Pointer to the global settings
    PzSettings* theSettings;

    /// Pointer to the graphics device
    PzGenDraw* theDrawable;

    /// Pointer to the label used in legends.
    PzAnnotation* labelAnno;

    /// Constructor
    PzPlotObject(const char* name, const int type);

    /// Destructor
    ~PzPlotObject();

    ///
    static void setSettings(PzPlotObject* obj, PzSettings* settingPtr);

    ///
    static void copySettings(PzPlotObject* obj, PzSettings* settingPtr);

    /// Evaluates a Tcl-procedure (if defined) iff object is instantiated.
    const char* evalInitProc(int typid);

    bool callInitProc;

    /// Contains Tcl-script.
    McString theScript;

    /// Pointer to the data.
    PzPlotData* theData;

    /// Object's label which will displayed in e.g. a legend.
    char* theLabel;

    /// Contains the number of the currently used normalization transformation.
    int myNormTr;

  public:

    virtual const char* className() { return "PzPlotObject"; }

    /// Updates plot object and global settings prior to rendering.
    virtual void update(PzGenDraw* theDrawable = NULL);

    /// Renders plot object.
    virtual void render(PzGenDraw* theDrawable = NULL);

    /** Saves the object's state as Tcl-commands. Derived classes should call
        this method as well together with saving their specific state.
    */
    virtual void save(FILE* fp, char* globalName);

    /// Shows a legend entry for \e this. Called by PzLegend..
    virtual bool showLegend(PzGenDraw *, float& xend, float& yend,
                            float x, float y, int legendtype)
                 { return false; }

    /// Returns the group the object belongs to.
    PzPlotGroup* getGroup() { return theSettings->getCurrGroup(); }

    /// Sets theScript which is executed whenever update is invoked.
    void setScript(const char* script);

    /// Returns theScript.
    const char* getScript() { return theScript.getString(); }

    /// Sets all attributes according to fromObj.
    virtual bool setAllAttr(PzBaseObject* fromObj);

    /// Returns object's parent.
    PzPlotGroup* getParent();

    /// Sets object's \a name together with the label.
    virtual void setName(const char* name);

    /// Sets object's \a label which will displayed in e.g. a legend.
    virtual void setLabel(const char* label);

    /// Returns object's label.
    const char* getLabel() { return theLabel; }

    /// Returns object's label as an PzAnnotation object.
    PzAnnotation* getLabelAsAnnotation() { return labelAnno; }

    /// Always returns true.
    virtual bool isGraphicsObject() { return true; }

    /// Returns true if object contains data as e.g. curves do.
    virtual bool hasData() { return (theData && theData->hasData()); }

    /// Saves the data of object in a given format into file \a fp.
    virtual void saveData(FILE* fp, int format) { }

    /// Resets the new flag for the object and for the data object.
    virtual void untouch();

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns pointer to theData.
    PzPlotData* getTheData() { return theData; }

    /// Sets theData object associated with this plotobject.
    void setTheData(PzPlotData* data);

    /// Returns the current drawable.
    PzGenDraw* getDrawable() { return theDrawable; }

};

#endif /* PZ_PLOTOBJECT */

/// @}
