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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef QX_NEURON_EDITOR_TOOL_H
#define QX_NEURON_EDITOR_TOOL_H

#include "VisageViewerWinDLLApi.h"
#include <QKeySequence>
#include <QObject>
#include <QAction>

#include <hxcore/HxViewerTool.h>
#include <mclib/McHandle.h>

class HxVisageViewerSubApplication;

////////////////////////////////////////////////////////////////////////////////
class HXVISAGEVIEWER_API QxVisageViewerTool  : public QObject
{

    Q_OBJECT

public:
    
    virtual ~QxVisageViewerTool();
    
    McString text(); 
    void  setText(const char *name); 
    
    void setTooltip(const char *toolTip) { 
        mAction->setToolTip(toolTip);
    }
    McString tooltip() { return McString(mAction->toolTip().toAscii()); }

    void setIconFile(const char* iconFileName);
    McString iconFile() { return mIconFileName; }

    QKeySequence keySequence() { return QKeySequence::fromString(mAction->shortcut()); }
    void setKeySequence(QKeySequence& shortCuts) { mAction->setShortcut(shortCuts); }
    
    QAction* action() { return mAction; }
    

    // returns wether a tool is modal or a trigger
    // modal tools -> toggle button
    // non-modal tools -> push button
    bool isModal();
    
    virtual QWidget* toolcard() { return 0; }
    
    virtual void updateToolcard() {} 

    virtual const char* toolBarName() { return 0; } // default is "" - then button will be inserted inside the editor GUI
    
    //virtual bool supportsViewer(HxViewerBase* baseViewer) {return true; }
    //virtual void updateUI(HxViewerBase* activeViewer);
    

protected:
    QxVisageViewerTool(HxVisageViewerSubApplication* editor);

    HxVisageViewerSubApplication* mEditor;
    
    McString mIconFileName;

    QAction* mAction;
};

////////////////////////////////////////////////////////////////////////////////
class HXVISAGEVIEWER_API QxVisageViewerTriggerTool : public QxVisageViewerTool 
{

public:
    QxVisageViewerTriggerTool(HxVisageViewerSubApplication* editor);
    ~QxVisageViewerTriggerTool();
    
    virtual void setCheckable(bool inFlag) { mAction->setCheckable(inFlag); }
    virtual bool isCheckable() { return mAction->isCheckable(); }
    virtual void setChecked(bool inFlag) { mAction->setChecked(inFlag); }

    virtual void process() = 0;
};

////////////////////////////////////////////////////////////////////////////////
class HXVISAGEVIEWER_API QxVisageViewerModalTool : public QxVisageViewerTool  
{

public:
    QxVisageViewerModalTool(HxVisageViewerSubApplication* editor);
    ~QxVisageViewerModalTool();
    
    virtual void onActivate() = 0;
    virtual void onDeactivate() = 0;

    virtual bool isNavigationTool() const { return false; }
    void setActivateAllEnabled(bool flag);
};

#endif

/// @}
