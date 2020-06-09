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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef MPRTOOLS_H
#define MPRTOOLS_H

#include <hxcore/HxViewerTool.h>
#include <vsvolren/VsSlice.h>
#include <hxvisageviewer/ExRotateTool.h>

class HxNeuronEditorSubApp;
class HxViewerBase;

///////////////////////////////////////////////////////////////////////////////////////////////////
// mpr viewer tools
///////////////////////////////////////////////////////////////////////////////////////////////////

class MPRWindowLevelTool : public HxViewerModalTool {
public:
    MPRWindowLevelTool(HxNeuronEditorSubApp *editor);
    virtual bool supportsViewer(HxViewerBase* baseViewer);
    virtual void onActivate(HxViewerBase* activeViewer);
    virtual void onDeactivate(HxViewerBase* activeViewer);
private:
    HxNeuronEditorSubApp *mEditor;
};


class MPRBrowseTool : public HxViewerModalTool {
public:
    MPRBrowseTool(HxNeuronEditorSubApp *editor);
    virtual bool supportsViewer(HxViewerBase* baseViewer);
    virtual void onActivate(HxViewerBase* activeViewer);
    virtual void onDeactivate(HxViewerBase* activeViewer);
    virtual bool isNavigationTool() const { return true; }  
private:
    HxNeuronEditorSubApp *mEditor;
};


class MPRZoomTool : public HxViewerModalTool {
public:
    MPRZoomTool(HxNeuronEditorSubApp *editor);
    virtual bool supportsViewer(HxViewerBase* baseViewer);
    virtual void onActivate(HxViewerBase* activeViewer);
    virtual void onDeactivate(HxViewerBase* activeViewer);
    virtual bool isNavigationTool() const { return true; } 
private:
    HxNeuronEditorSubApp *mEditor;
};

class MPRTranslateTool : public HxViewerModalTool {
public:
    MPRTranslateTool(HxNeuronEditorSubApp *editor);
    virtual bool supportsViewer(HxViewerBase* baseViewer);
    virtual void onActivate(HxViewerBase* activeViewer);
    virtual void onDeactivate(HxViewerBase* activeViewer);
    virtual bool isNavigationTool() const { return true; } 
private:
    HxNeuronEditorSubApp *mEditor;
};


class MPRRotateTool : public HxViewerModalTool {
public:
    MPRRotateTool(HxNeuronEditorSubApp *editor);
    bool supportsViewer(HxViewerBase* baseViewer);
    void onActivate(HxViewerBase* activeViewer);
    void onDeactivate(HxViewerBase* activeViewer);
    virtual bool isNavigationTool() const { return true; } 
private:
    HxNeuronEditorSubApp *mEditor;
    McHandle<ExRotateTool> mExRotateTool;
};


/// Tool to restore previously stored MPR viewers camera and slice plane
class MPRSetToHomeTool : public HxViewerTriggerTool {
public:
    MPRSetToHomeTool();
    bool supportsViewer(HxViewerBase* baseViewer);
    virtual void onTrigger(HxViewerBase* activeViewer, int modifiers);
};


/// Tool to save current MPR viewers camera and slice position
class MPRSaveHomeTool : public HxViewerTriggerTool {
public:
    MPRSaveHomeTool();
    bool supportsViewer(HxViewerBase* baseViewer);
    virtual void onTrigger(HxViewerBase* activeViewer, int modifiers);
};


class MPRResetViewTool : public HxViewerTriggerTool {
public:
    MPRResetViewTool();
    void setSliceOrientation(VsSlice::Orientation orientation) { mSliceOrientation = orientation; }
    virtual bool supportsViewer(HxViewerBase* baseViewer);
    virtual void onTrigger(HxViewerBase* activeViewer, int modifiers);
private:
    VsSlice::Orientation mSliceOrientation;
};


class MPRPickTool : public HxViewerModalTool {
public:
    MPRPickTool(HxNeuronEditorSubApp *editor);
    virtual bool supportsViewer(HxViewerBase* baseViewer); 
    virtual void onActivate(HxViewerBase* activeViewer);
    virtual void onDeactivate(HxViewerBase* activeViewer);
private:
    HxNeuronEditorSubApp *mEditor;
};

#endif


/// @}
