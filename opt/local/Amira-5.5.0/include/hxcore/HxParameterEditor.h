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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_PARAMETER_EDITOR
#define HX_PARAMETER_EDITOR

#include <hxcore/HxEditor.h>

class QxParamDialog;
class QxEditorNotifier;

/** Amira's parameter editor.
    The <tt>Parameter Editor</tt> lets you view and modify the hierarchical
    parameter list associated with a data object.
    Use HxEditor::attach<tt>(HxData* data)</tt> to pop up
    the editor and attach the data object to it.
    See the  @htmlonly <a href= ../usersguide/HxParameterEditor.html> usersguide </A> @endhtmlonly 
    for a detailed view of the editor's GUI.
 */
class HXCORE_API HxParameterEditor : public HxEditor {

  HX_HEADER(HxParameterEditor);
   
public:
    /// Constructor
    HxParameterEditor();

  protected:
    /// Destructor
    virtual ~HxParameterEditor();

    // Pops up the editor showing the given data's parameter list. 
    virtual void startEditing( HxData * data );
    // Closes the editor and finishes edit session. 
    virtual void stopEditing();

    QxParamDialog* dialog;
    QxEditorNotifier* notifier;
};


#endif


/// @}
