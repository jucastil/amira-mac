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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_PORT_MEASURE_TOOLS
#define HX_PORT_MEASURE_TOOLS

#include <hxmeasure/HxMeasureWinDLLApi.h>

#include <hxcore/HxPort.h>
#include <mclib/McColor.h>

class QxMTForm;
class HxMeasureTools;
class HxMeasureGUIElem;

/** This is a very special port. It can exist only once in active state
and directly controls HxMeasureGUIElems and is controlled by them.
There is NO other usage.
*/
class HXMEASURE_API HxPortMeasureTools : public HxPort
{
     MC_ABSTRACT_HEADER(HxPortMeasureTools);

public:
    ///
    HxPortMeasureTools(HxMeasureTools* measure, const char* name);
    ///
    virtual ~HxPortMeasureTools ();

    /// get number of elements in the ListBox.
    int getNum ();
    /// check wether elem i is selected.
    bool getIsSelected (int i);
    /// get the color.
    McColor getColor ();
    /**
    *  Set the color
    */
    void setColor(const McColor& color);
    /// get the pointsize.
    float getPointSize ();
    ///
    void deleteSelected();

    ///
    void deleteUninitialized();

    // enable or disable shape export button
    void enableExportShapeButton( bool enable );

    // enable or disable font size button
    void enableFontSizeButton( bool enable );

    /**
    *  Delete all creating measures
    */
    void deleteAll();

    /**
    *  Select a tool in the list.
    */
    void selectTool(int itemID);

    /**
    *  Deselect the current selected tool.
    */
    void deselectTool();

    /**
    *  Convenience method to set the format string of tool @c i.
    *  If the tool is @c HxMeasureGUIAnnotation, this method set the displayed string.
    */
    void setFormatString(const char* format, int itemID);

    /**
    *  Get the tool at index @c i in the list
    */
    HxMeasureGUIElem* getTool(int i);

    /**
    *  Deselect everything in the tools list and remove un-initialized tools from the list.
    */
    void cleanState();

    /**
    *  TCL.
    **/
    int parse(Tcl_Interp* t, int argc, char **argv); 

    /**
    * Update the form's create button
    **/
    void updateExportButton();

    /**
    * Create the spreadsheet module 
    **/
    void exportSpreadSheet();

protected:

    QxGuardedPtr<QxMTForm> form;
    ///
    HxMeasureTools* measure;

    ///
    virtual void createWidget (QWidget* parent);

    McColor m_defaultColor;

    /**
    *  Check the validity of an index in the list.
    *  Return true if index exists.
    */
    bool checkToolIndex(int itemID);

private:
    ///
    static void* theActivePort;
    ///
    bool active;

    friend class HxMeasureGUI;
};

#endif

/// @}
