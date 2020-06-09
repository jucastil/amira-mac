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

/// @addtogroup hxlines hxlines
/// @{
#ifndef HX_LINESET_EDITOR_H
#define HX_LINESET_EDITOR_H


#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/details/SoPointDetail.h>
#include <Inventor/details/SoLineDetail.h>
#include <mclib/McHandle.h>
#include <mclib/McBox3f.h>

#include <hxcore/HxEditor.h>
//#include <hxcore/HxPortOptionMenu.h>
#include <hxcore/HxGLPolyLine.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortIntTextN.h>

#include <hxlines/HxLinesWinDLLApi.h>
//#include <hxlines/HxDisplayLineSet.h>

class QxLineSetEditorConnectDialog;
class QxLineSetEditorSetValueDialog;
class HxUniformScalarField3;
//class HxLineSet;
class HxLineSetInterface;
/// Edit a lineSet 

class HXLINES_API HxLineSetEditor : public HxEditor {

  HX_HEADER(HxLineSetEditor);

  public:
    /// Constructor
    HxLineSetEditor();

    /// Destructor
    ~HxLineSetEditor();

    ///
    HxPortInfo portInfo;

    /// Choose whether all points, endpoints lines are displayed 
    /// andcan be picked
    HxPortToggleList portDisplayOptions;

    /// This menu determines which selection mode is active currently.
    HxPortButtonList portSelectMode;

    /// This port provides buttons for various kinds of actions.
    HxPortButtonList portUndo;

    /// This port provides buttons for various kinds of actions.
    HxPortButtonList portAction;

    /// 
    virtual void startEditing(HxData *data);

    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);
   
    /// Fire method
    virtual void fire();

    ///
    virtual void stopEditing();

    /// Data type to store corresponding line and index in line 
    /// of a selected point.
    struct selectedPoint{
	int line;
	int point;
    };

    // base class for all redo/undo operations
    class Operation;
    
    /// Method to connect two selected points.
    void connectCheapest(HxUniformScalarField3* field, float mi, float ma);

    /// Method to connect two selected points.
    void connectStraight();

    /// Set values at selected points
    void setValues (int datasetidx, float val);

    protected:

      float getPointDensity();
    int hasRoi;
    McBox3f roiBox;
    /// The lineset to be edited.
    HxLineSetInterface* lineset;
    HxData* theData;
    //HxLineSet* lineset;

    ///
    McDArray<int> newIndex;

    McDArray<int> pointMapping;
    McDArray<int> lineMapping;

    /// Inventor separator to display geometry.
    McHandle<SoSeparator> separator;

    /// Inventor nodes to display the geometry.
    McHandle<SoSeparator> sepBase;
    McHandle<SoPointSet> basePointSet;
    McHandle<SoLineSet> baseLineSet;

    /// Inventor nodes to display the highlighted geometry.
    McHandle<SoSeparator> sepHigh;
    McHandle<SoPointSet> highPointSet;
    McHandle<SoLineSet> highLineSet;
    
    /// Event callback.
    McHandle<SoEventCallback> eventCallback;

    /// Array to store the indices of the selected lines.
    McDArray <int> selectedLines;

    /// Array to store information about the selected points.
    McDArray <selectedPoint> selectedPoints;

    ///
    HxGLPolyLine polyLine;
    void viewerSelect();
    static void viewerSelectCB(void* userdata);

    /// Method to construct inventor geometry.
    void buildSceneGraph();

    /// Method to construct the base geometry.
    void createBaseGeom(SoSeparator* sep);

    /// Method to construct the highlighted geometry.
    void createHighGeom(SoSeparator* sep);

    /// Callback method.
    static void pickCB(void *that, SoEventCallback* node);

    /// Method called after picking some geometry.
    void pickCallback(SoEventCallback* node);

    /// Method to select one point.
    void selectPoint(int pointIdx, int whichEvent);

    /// Method to select one line;
    void selectLine(int lineIdx, int whichEvent);

    /// Method to select all lines.
    void selectAll();

    ///
    void selectByLength();

    ///
    void selectByLineIndex();

    /// Method to connect two selected points.
    void showConnectDialog();

    /// Method to set values on the dataset
    void showSetValueDialog();


    /// Method to delete the current selection.
    void deleteSelection();

    /// Method to stretch/straighten the selected lines.
    void stretchSelection();

    /// Split lines at selected points
    void splitLine();

    /// 
    void drawLine();
  
    /// Clears the current selection.
    void clearSelection();

    McDArray<int> viewermasks;
    McDArray<HxObject*> displayMods;

    // undo redo stuff
    friend class Operation;

    McDArray<Operation*> undoStack;
    mclong undoPos;

    int execNewOp (Operation*);
    void undo ();
    void redo ();
    void updateUndoPort ();
    QxLineSetEditorConnectDialog* connectDialog;
    QxLineSetEditorSetValueDialog* setValueDialog;
};

#endif


/// @}
