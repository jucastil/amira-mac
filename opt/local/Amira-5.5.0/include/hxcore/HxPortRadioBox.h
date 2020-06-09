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
#ifndef HX_PORT_RADIO_BOX
#define HX_PORT_RADIO_BOX

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <hxcore/HxPort.h>

class QWidget;
class QRadioButton;

/** Radio box port for one-of-may selections.
    In addition to the port's label ( which is set by @c HxPort::setLabel)
    you can set a label for each radio box using setLabel(). It is also
    possible to set the sensitivity for each radio button individually. */
class HXCORE_API HxPortRadioBox : public HxPort {

  MC_ABSTRACT_HEADER(HxPortRadioBox);

  public:
    /// Constructor.
    HxPortRadioBox(HxObject *object, const char* name, int nItems);

    /// Constructor.
    HxPortRadioBox(HxEditor *editor, const char* name, int nItems);

    /// Destructor.
    ~HxPortRadioBox();

    /// Returns the number of toggles.
    int getNum() const { return nItems; }

    /// Sets current selection.
    void setValue(int index);

    /// Gets current selection.
    int getValue() const { return index; }

    // Included for backward compatibility only, use setValue() instead.
    void setIndex(int _index) { setValue(_index); }

    // Included for backward compatibility only, use getValue() instead.
    int	getIndex() const { return index; }

    /// Sets label of port.
    void setLabel(const char* _label) { HxPort::setLabel(_label); }

    /// Returns label of port.
    const char* getLabel() const { return HxPort::getLabel(); }

    /// Sets label of specified radio button.
    void setLabel(int item, const char* label);

    /// Gets label of specified radio button.
    const char* getLabel(int item) const;

    /// Activates or deactivates a toggle.
    void setSensitivity(int item, int isOn);

    /// Checks whether the specified radio button is active or not.
    int getSensitivity(int item) const;

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );

  protected:
    McDArray< QxGuardedPtr<QRadioButton> > radioList;
    McDArray<McString> labels;
    McBitfield sensitivity;
    int index, nItems;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
    virtual void destroyWidget();
};

#endif


/// @}
