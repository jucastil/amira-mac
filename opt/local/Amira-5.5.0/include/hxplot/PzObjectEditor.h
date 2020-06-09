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
#ifndef PZ_OBJECTEDITOR
#define PZ_OBJECTEDITOR

#include <hxplot/PzPlotWinDLLApi.h>

class PzObjectEditor;
class QzObjectEditor;

class PzBaseObject;
class PzPlot;
class PzPlotGroup;
class PzCurve;
class QWidget;

typedef void PzObjectEditorCB(int result, void* calldata, void* userdata);

/**
   Object editor for plot objects
@author Olaf Paetsch
*/
class HXPLOT_API PzObjectEditor {

private:

    QzObjectEditor   *editorWindow;
    PzObjectEditorCB *editorCallback;
    void             *editorUserdata;
    PzPlotGroup      *objectAnchor;
    PzPlotGroup      *selObjGroup;
    PzPlot           *thePlot;
    PzBaseObject     *selObj;
    PzBaseObject     *bufObj;
    PzBaseObject     *undoObj;

    bool             showFlag, applyFlag;

    void commonInit();

    static void editorWindowCB(int result, const QzObjectEditor& edwin,
                               void* userdata);

    static void selectedCB(const char* objName, const QzObjectEditor& edwin,
                           void* userdata);

    static void showitCB(bool showit, const QzObjectEditor& edwin,
                         void* userdata);

    static void menuCB(int itemno, const QzObjectEditor& edwin,
                       void* userdata);

protected:

    void selected(const char* objName);

    /// shows the attributes in the editorWindow
    void showAttr(PzBaseObject* obj);

    void applyAttr(PzBaseObject* obj);

    void undoAttr(PzBaseObject* obj, PzBaseObject* undoObj);

    void copyObj();

    void cutObj();

    void pasteObj();

    void appendObj();

    void createObj(int type);

    void prepareUndo(PzBaseObject* obj);

public:

    /// Constructor
    PzObjectEditor(QWidget* parent, const char* name, PzPlot* plot);

    /// Destructor
    virtual ~PzObjectEditor();

    virtual const char* className() { return "PzObjectEditor"; }

    ///
    virtual void update();

    ///
    virtual void show();

    ///
    virtual void hide();

    ///
    virtual bool isVisible();

    /// sets the window title in the title bar
    void setTitle(const char* title);

    /// returns the selected Object
    PzBaseObject* getSelectedObject() { return selObj; }

    /// sets the selected object
    void setSelectedObject(PzBaseObject* obj);

    ///
    void setEditorCallback(PzObjectEditorCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetEditorCallback() { editorCallback = (PzObjectEditorCB*)0; }

    /// sets the plot group where to start editing
    void setObjectAnchor(PzPlotGroup* anchor);

};

#endif

/// @}
