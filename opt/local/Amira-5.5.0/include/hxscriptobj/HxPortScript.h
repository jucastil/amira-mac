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

/// @addtogroup hxscriptobj hxscriptobj
/// @{
#ifndef HX_PORT_SCRIPT_H
#define HX_PORT_SCRIPT_H

#include <mclib/McString.h>
#include <hxcore/HxPort.h>
#include <hxcore/HxModule.h>
#include <hxscriptobj/HxScriptobjWinDLLApi.h>

class QxLineEdit;
class QxPushButton;
class HxEditor;

/// Special port used by script objects.
class HXSCRIPTOBJ_API HxPortScript : public HxPort {

  public:
    /// Constructor for objects.
    HxPortScript(HxObject* object, const char* name);

    /// Constructor for editor.
    HxPortScript(HxEditor* editor, const char* name);

    /// Destructor
    ~HxPortScript();

    /// Get the current text value
    const char* getValue() const { return value; }

    /// Set the text value.
    void setValue(const char* value);

    /// Set width of text field to fit desired number of columns.
    void setNumColumns(int nColumns);

    /// Set the port's label.
    void setLabel(const char* l) { HxPort::setLabel(l); }

    /// Set label of push button.
    void setButtonLabel(const char* l);

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

  protected:
    QxGuardedPtr<QxPushButton> browseBtn;
    QxGuardedPtr<QxPushButton> pushBtn;
    QxGuardedPtr<QxLineEdit> lineEdit;

    int nColumns;
    McString value;
    McString btnLabel;

    int exec();
    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
};

#endif

/// @}
