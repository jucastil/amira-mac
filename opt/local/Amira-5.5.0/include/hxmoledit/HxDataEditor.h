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

/// @addtogroup hxmoledit hxmoledit
/// @{
#ifndef HX_Data_EDITOR_H
#define HX_Data_EDITOR_H

#include "HxMolEditWinDLLApi.h"
#include <hxcore/HxEditor.h>
#include <mclib/McHandle.h>
#include <mclib/McBitfield.h>
#include <hxmolecule/ComputeListener.h>

class HxMolecule;
class SoEventCallback;
class QxDataEditor;
class QxEditorNotifier;
class readOperation;
class MtGroupData;

/** HxDataEditor is the interface between the
    outside world and the QT user interface 
    as implemented in QxDataEditor. It
    contains all editor functions that can 
    be accessed by external libraries as static methods. 
    An instance of it should only be created by
    Amira. The QxDataEditor will be created as soon
    as the data object is known (when startEditing
    is called)
    It uses an HxMoleculeEvenCB to ensure that it is
    notified in case of selection event
    A QxEditorNotifier is used for passing the exit
    signal of the QxMolEditor on to this object
**/

class HXMOLEDIT_API HxDataEditor : public HxEditor, public ComputeListener {

    HX_HEADER(HxDataEditor);

public:
    /// Default constructor.
    HxDataEditor();
  
    /// Called whenever a port changes.
    virtual void fire();

    /// Parse method
    int parse(Tcl_Interp* t, int argc, char **argv);


    /// function used for the source objects compute events
    void computeCalled(HxObject* hxMol);

protected:
    ~HxDataEditor();

    virtual void molChanged();

private:
    McHandle<HxMolecule> molecule;
    QxDataEditor* qxEditor;
    QxEditorNotifier* qxNotifier;

    /// Initialize ports here.
    void startEditing(HxData *data);

    /// Remove selection callbacks here.
    void stopEditing();

};

#endif


/// @}
