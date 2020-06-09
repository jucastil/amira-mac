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
#ifndef HX_PORT_TEXT
#define HX_PORT_TEXT

#include <mclib/McString.h>
#include <hxcore/HxPort.h>
#include <hxcore/HxModule.h>

class QLineEdit;
class HxEditor;

/// Port for text input
class HXCORE_API HxPortText : public HxPort {

  MC_ABSTRACT_HEADER(HxPortText);

  public:

    /// echo types
    enum EchoMode {
        /// "abc"
        Normal,
        /// "***"
        Password,
        /// ""
        NoEcho
    };

    /// Constructor for objects.
    HxPortText(HxObject* object, const char* name);

    /// Constructor for editor.
    HxPortText(HxEditor* editor, const char* name);

    /// Destructor
    virtual ~HxPortText();

    /// Get the current text value
    const char* getValue() const { return value; }

    /// Set the text value.
    void setValue(const char* value);

    /// Sets width of text field to fit desired number of columns.
    void setNumColumns(int nColumns);

    /// Returns number of columms, i.e., width of text field.
    int getNumColumns() const { return nColumns; }

    /// Sets the port's sensitivity (enabled or disabled).
    void setSensitivity(bool state);

    /// Gets the port's sensitivity (enabled or disabled).
    bool getSensitivity() const { return sensitivity; }

    /// set echo mode (<Normal|NoEcho|Password>)
    bool setEchoMode (EchoMode mode = Normal);

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );


  protected:
    QxGuardedPtr<QLineEdit> lineEdit;

    unsigned int nColumns:16;
    unsigned int sensitivity:1;
    McString value;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);

    /**
     * To set the text into the Qt line edit.
     * Inherited by HxPortTextUTF8 for UTF8 management.
     */
    virtual void setLineEditText(const char* str);

    void commonInit();
};

#endif

/// @}
