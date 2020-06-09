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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GI_FILTER_FACTORY_H
#define GI_FILTER_FACTORY_H


#include <mclib/McDArray.h>
#include <mclib/McString.h>

#include "HxGiWinDLLApi.h"


class Gi;
class GiFilter;

/** The FilterFactory creates plugin filter objects.

    The Segmentation Editor provides a mechanism to register external 
    selection and label filters if you are using the Amira Developer Pack.

    On start up of the Segmentation Editor all plugins are added that provide:

    - A widget interface inherited from the class GIFilter
    - An external registration function
    - A function call in an .rc2 file providing the name of the filter, 
    the name of the registration function and the name of the library 

    If the above requirements are fulfilled a new menu entry is created in the 
    Selection filters tab with the name of the filter. By clicking on the 
    dynamically generated menu entry the filter's widget shows up, which then 
    allows developer specified manipulation of the selection and materials.

    In the following a minimal example is given to further explain the approach, 
    when creating your own plugin.

    #include <hxsegeditor/GiFilter.h>

    class HXEXAMPLE_API GiExampleFilter : public QObject, public GiFilter {
    Q_OBJECT
    public:
    GiExampleFilter(Gi* gi);

    ~GiExampleFilter();

    protected:

    /// Implementation of the virtual function create widget
    /// This function is called on creation of the filter object
    virtual QWidget* createWidget(QWidget* parent);

    /// A base widget that holds the user interface of the filter
    /// This widget usually is returned by createWidget(QWidget* parent)
    QWidget* _wBase;

    /// Some filter specific widgets
    QRadioButton* _wMode;      
    QLineEdit* _wFilename;    

    /// A filter specific function
    void someFunction();

    protected slots:
    /// This section holds Qt SLOTS for the specific widget
    void computeSomething();

    };

    // Function to register the Filter Plugin at the Segmentation Editor SubApp.
    //  We use extern "C" to avoid name mangling so HxDSO can find it.
    extern "C" {
    void HXEXAMPLE_API GiExampleFilter_init_plugin(Gi* gi);
    }

    The above listed class is a very basic example for the structure of an 
    inherited Segmentation Editor filter plugin. The Segmentation Editor 
    will check for the filters widget by calling GiFilter::getWidget. 
    Therefore you need to reimplement the virtual function createWidget.

    # -----------------------------------------------
    #   filter registration to hxsegeditor
    # -----------------------------------------------
    hxsegeditor::declareFilterClass  ExampleFilter  GiExampleFilter_init_plugin  hxexamplepackage

    To make the filter available to the Segmentation Editor, you have to 
    add the above lines to the package's .rc2 file. The TCL function 
    hxsegeditor::declareFilterClass adds the name of the filter, the name 
    of the external registration function and the library name to a list 
    which is evaluated on start up of the Segmentation Editor.

    The filter's protected variable theGi provides access to the Segmentation 
    Editor's data objects, i.e. current selection, materials, etc. 
*/

class HXSEGEDITOR_API GiFilterFactory
{

  public:

    /// Get the names of all available filter algorithms
    static McDArray< McString > getNames(void);

    /// Construct a filter object
    static int createFilter(const char* label, Gi* gi);

};

#endif

/// @}
