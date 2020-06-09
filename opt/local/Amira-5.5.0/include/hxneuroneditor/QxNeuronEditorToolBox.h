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
#ifndef QX_NEURON_EDITOR_TOOL_BOX_H
#define QX_NEURON_EDITOR_TOOL_BOX_H

#include "hxneuroneditorAPI.h"

#include <mclib/McString.h>

class HxNeuronEditorSubApp;
class QAction;
class QWidget;
class QKeySequence;
class QScrollArea;

/**
    @brief Base class for neuron editor toolboxes.

    A neuron editor toolbox can be registered within the neuron editor.
    @see HxNeuronEditorSubApp::registerToolBox()
*/
class HXNEURONEDITOR_API QxNeuronEditorToolBox
{
public:
    virtual ~QxNeuronEditorToolBox();

    /**
       Function needs to be implement by derived classes!

       Within this function derived classes should implement all necessary
       tasks in order to update the toolBox's toolcard.
       @see toolcard()
    */
    virtual void updateToolcard()= 0;

    /// @return Returns the toolBox's tool button shortcut key sequence.
    QKeySequence keySequence() const;

    void setKeySequence(const QKeySequence& shortCuts);

    /// @param toolTip Sets the toolBox's tool button tool tip text.
    void setToolTip(const char* toolTip);

    /// @return Returns the toolBox's tool button tool tip text.
    McString toolTip() const;
    
    /// @param text Sets the toolBox's tool button text to be 
    ///             displayed within the toolBox toolbar.
    void setText(const char* text);

    /// @return Returns the toolBox's descriptive text set via setText().
    McString text() const;

    /** Internal use only!
        @return Returns a QScrollArea widget containing
                the widget returned by toolcard().
        @see toolcard()
    */
    QWidget* widget();

    /** Internal use only!
        @return Returns an action which is used
                to register the toolbox within the neuron editor's
                toolBox toolbar.
    */
    QAction* action();

protected:
    QxNeuronEditorToolBox(HxNeuronEditorSubApp* editor);
    QxNeuronEditorToolBox();

    HxNeuronEditorSubApp* mEditor;

private:

    /**
        This function has to be implemented by derived classes.

        @return The widget containing the actual GUI of the toolBox.
    */
    virtual QWidget* toolcard() { return NULL; }

    QAction     *mAction;
    QScrollArea *mScrollArea;
};

#endif

/// @}
