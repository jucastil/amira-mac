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
#ifndef QX_NEURON_EDITOR_TOOL_H
#define QX_NEURON_EDITOR_TOOL_H

#include "hxneuroneditorAPI.h"

#include <QObject>

#include <hxcore/HxViewerTool.h>
#include <mclib/McHandle.h>

class QKeySequence;
class HxNeuronEditorSubApp;
class SoEvent;
class SoEventCallback;
class SpatialGraphViewNode;
class HxViewerTool;

////////////////////////////////////////////////////////////////////////////////
/** 
    @brief Base class of neuron editor tools

    Neuron editor tools can by registered within the Amira neuroneditor.
    @see HxNeuronEditorSubApp::registerTool()

*/
class HXNEURONEDITOR_API QxNeuronEditorTool  : public QObject
{
    Q_OBJECT

public:
    virtual ~QxNeuronEditorTool();

    /// @return Returns whether a tool is modal or not
    /// @see QxNeuronEditorModalTool
    /// @see QxNeuronEditorTriggerTool
    bool isModal();

protected:
    /// Allow no instances of type QxNeuronEditorTool 
    QxNeuronEditorTool(HxNeuronEditorSubApp* editor);
    QxNeuronEditorTool();

    HxNeuronEditorSubApp* mEditor;
};

////////////////////////////////////////////////////////////////////////////////
/**
    @brief The QxNeuronEditorTriggerTool represents a class of tools which trigger
           a single event. e.g. typical trigger tools are clear or reset tools.

    @see HxViewerTriggerTool on how trigger tools are used within Amira
*/

class HXNEURONEDITOR_API QxNeuronEditorTriggerTool 
    : public QxNeuronEditorTool,
      public HxViewerTriggerTool
{
public:
    QxNeuronEditorTriggerTool(HxNeuronEditorSubApp* editor);
    virtual ~QxNeuronEditorTriggerTool();

    /// Convenience function
    /// @return Returns the tool's tool button shortcut key sequence.
    QKeySequence keySequence();

    /// Convenience function
    /// @param shortCuts Sets the tool's tool button shortcut.
    void setKeySequence(const QKeySequence& shortCuts);

private:
    /// No default constructor available
    QxNeuronEditorTriggerTool();
};

////////////////////////////////////////////////////////////////////////////////
/**
    @brief The QxNeuronEditorModalTool represents a class of interactive
           tools. Typically these tools provide some user interaction within the
           neuron editor viewers.

    @see HxViewerModalTools on how trigger tools are used within Amira
*/
class HXNEURONEDITOR_API QxNeuronEditorModalTool
    : public QxNeuronEditorTool,
      public HxViewerModalTool
{
public:
    QxNeuronEditorModalTool(HxNeuronEditorSubApp* editor);
    virtual ~QxNeuronEditorModalTool();

    /// @return Returns the tool's tool button shortcut key sequence.
    QKeySequence keySequence();

    /// Convenience function
    /// @param shortCuts Sets the tool's tool button shortcut.
    void setKeySequence(const QKeySequence& shortCuts);

    /**
        Callback function, to be implemented by derived classes.
        Called by the nueron editor whenever a node within the oiv scene 
        graph of the neuron editor's 3D viewer has been picked.

        The default implementation returns immediately.
    */
    virtual void pickCallback(const SpatialGraphViewNode*, SoEventCallback*);

private:
    /// No default constructor available
    QxNeuronEditorModalTool();
};

#endif

/// @}
