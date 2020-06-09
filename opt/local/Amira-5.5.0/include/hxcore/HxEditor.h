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
#ifndef HX_EDITOR_H
#define HX_EDITOR_H

#include <tcl.h>
#include <hxcore/HxBase.h>

class QWidget;
class HxObject;
class HxData;

/** Base class for all editors. Basically, there are two types of editors,
    once making use of ports and once using their own dialog window. Ports
    can be used in derived classes just as in ordinary modules. You should
    overload the editor's update() method in order to react on port changes.

    If you want to use a separate window, then you have to fire the data
    being edited for yourself, namely by calling theData->fire(), whenever
    you need to. Standalone editors usually allow the user to quit the
    editor by some menu entry or "Ok" or "Cancel" button. In this case
    detach() has to be called in reaction of a quit request. Notice the
    remarks referring to detach(). The utility class QxEditorNotifier
    may be helpful when writing standalone editors.
*/

class HXCORE_API HxEditor : public HxBase {

  HX_ABSTRACT_HEADER(HxEditor);

  public:
    /** Same as data->setEditor(this). Call this method if you
        want to edit a data object. */
    void attach(HxData* data);

    /** Same as this->getData()->setEditor(0).

       <b> WARNING:</b> The portMaster of a data object is the only place where
        a handle to an editor is stored. Therefore, disconnecting portMaster
        usually causes the editor to be deleted. Keep this in mind if you
        want to call detach from the editor itself, e.g., in reaction of
        a cancel button click. The call to detach() should be the very last
        action in a member routine of an editor. */
    void detach();

    /// This method is called whenever a port has changed.
    virtual void update();

    /// First calls update(), then fires() the data object being edited.
    virtual void fire();

    /// Returns 1 if given object can be edited.
    virtual int typeCheck(HxObject* data);

    /// Tcl command interface of the editor.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Create widgets for all ports in interface widget of data.
    void createPortWidgets(HxData *data);

    /** Add a geometry node to the viewers. This function will use the
	transformation of the currently connected data-object. If this
	is not desired, HxBase::showGeom should be used.*/
    virtual void showGeom(SoNode *node);

    /// Returns the object to be edited.
    HxData* getData() const { return theData; }

    virtual void checkRemoteMode() {}

  protected:
    // Constructor is protected - this is an abstract class
    HxEditor(const McTypeInfo* t);

    // Destructor.
    virtual ~HxEditor();

    // The object to be edited.
    HxData* theData;
    
    // This editor can be applied to objects of @c theType.
    const McTypeInfo* theType;

  private:
    /// The master connection calls this method in connect().
    virtual void startEditing(HxData *data);

    /// The master connection calls this method in disconnect().
    virtual void stopEditing();

    // The master connection uses this method to update the edited object gui.
    void updateDataGUI(bool isEditing);

    friend class HxData;
    friend class HxMasterConnection;
};

#endif

/// @}
