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
#ifndef HX_MASTER_CONNECTION_H
#define HX_MASTER_CONNECTION_H

#include <mclib/McHandle.h>
#include <hxcore/HxEditor.h>
#include <hxcore/HxConnection.h>

class HxCompModule;

/** Special connection port used for editing data objects. All data objects
    have one master connection. This connection is used to connect the data
    object to an upstream compute module or editor which modifies the data
    object. In this sense, the compute module or the editor is said to be
    the master of the data object. */

class HXCORE_API HxMasterConnection : public HxConnection {

  MC_ABSTRACT_HEADER(HxMasterConnection);

  public:
    /// Constructor.
    HxMasterConnection(HxObject* object, const char* name);
    
    /// Destructor.
    virtual ~HxMasterConnection();
    
    /** Overloaded connect method. The method calls the base class's
        HxConnection::connect method and then checks if @c master is a 
        compute module. If so, it sets the result pointer of @c master to
        the owner of the master connection. */
    virtual int connect(HxObject* master);

    int connect(HxCompModule* master, int resultSlotId);
    
    /** Connect method used by editors. Editors are not represented by
        icons in the object pool. Nevertheless, they may be attached to
        data objects in upstream direction via this method. */
    int connect(HxEditor* editor);
    
    /// Disconnect from attached compute module or editor.
    virtual void disconnect(bool disconnectedDuringConnection=false);
    
    /// Returns the editor the port is connected to.
    HxEditor* getEditor() const { return editor; }
    
    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Overloaded save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

  protected:
    McHandle<HxEditor> editor;
};

#endif

/// @}
