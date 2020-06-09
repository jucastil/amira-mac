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
#ifndef HX_PORT_BUTTON_LIST
#define HX_PORT_BUTTON_LIST

#include <mclib/McDArray.h>
#include <hxcore/HxPort.h>

class QWidget;
class QxPushButton;

/** This port provides an arbitrary number of push buttons.
    When the port HxPort::isNew, use wasHit to
    find out which button was pressed. There are also methods to 
    detect if the @c SHIFT, @c ALT, or @c CTRL key was down when last 
    button was pressed.

    In addition, it is possible to mark a button insensitive, i.e. the
    button will not receive mouse clicks anymore, but may still be "pushed"
    using hit or setValue.

    Furthermore a button may have a snap toggle. If enabled, one can snap the
    button by clicking at the red area displayed on top of it or using the
    snap method. Use enableSnapToggle to let a button have a snap toggle.

    See the  @htmlonly <a href= ../usersguide/HxPortButtonList.html> usersguide </A> @endhtmlonly 
    for a detailed view of the port's GUI.
*/
class HXCORE_API HxPortButtonList : public HxPort {

  MC_ABSTRACT_HEADER(HxPortButtonList);

  public:
    /// Constructor.
    HxPortButtonList(HxObject *object, const char* name, int nItems);

    /// Constructor.
    HxPortButtonList(HxEditor *object, const char* name, int nItems);

    /// Destructor.
    virtual ~HxPortButtonList();

    /// Returns the number of buttons.
    int getNumButtons() const { return elements.size(); }

    /// Sets the number of buttons.
    void setNumButtons(int num);

    /** Returns index of button which has been pushed last or -1 if
        @c HxPort::isNew() is false. This method doesn't interprete the
        snap toggle. If a button is snapped but the port is not new
        this method still returns -1. In order to handle snapped buttons
        you better should use the method wasHit(int). */
    int getValue() const { return newFlag ? index : -1; }
    
    /// Same as getValue().
    int getIndex() const { return newFlag ? index : -1; }

    /// Mark given button to be pushed.
    void setValue(int btn) { index = btn; newFlag = 1; }

    /// Same as setValue().
    void setIndex(int btn) { index = btn; newFlag = 1; }

    /// Set sensitivity of given button. @c state may be 0 or 1.
    void setSensitivity(int btn, int state);

    /// Returns senisitivity of given button.
    int getSensitivity(int btn) const;

    /// Sets label of specified button.
    void setLabel(int btn, const char* label);

    /// Returns label of specified button.
    const char* getLabel(int btn) const;

    /// Set label of port.
    void setLabel(const char* label) { HxPort::setLabel(label); }

    /// Returns label of port.
    const char* getLabel() const { return HxPort::getLabel(); }

    /// Returns 1 if shift key was down when last button was pushed.
    int wasShiftDown() { return modifierFlags & 1; };
    
    /// Returns 1 if ctrl key was down when last button was pushed.
    int wasCtrlDown() { return (modifierFlags & 2) != 0; };

    /// Returns 1 if alt key was down when last button was pushed.
    int wasAltDown() { return (modifierFlags & 4) != 0; };

    /// If @c state is 1 the snap toggle is shown for the given button.
    void enableSnapToggle(int btn=0, int state=1);

    /// Check if given button has a snap toggle or not.
    int isSnapToggleEnabled(int btn=0) const;

    /** Sets the snap toggle for the given button to @c state.
	Makes only sense if snap toggle is enabled. */
    void snap(int btn=0, int state=1);

    /// Simulate button hit.
    void hit(int btn=0);

    /// Returns the state of the snap toggle of the specified button.
    int isSnapped(int btn=0);

    /** Returns 1 if the button has been hit or if its snap toggle is on.
        Unlike this method getValue() ignores the snap toggle. */
    int wasHit(int btn=0);

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    /** Sets a Tcl command which is executed when a button is pressed. This
        feature is especially useful in script objects. If a command has been
        specified for a button the owning module will not be fired and the
        port will not be touched when the button is pressed. The command will
        be executed in the global Tcl namespace. The variable this refers to
        the owning module. */
    void setCmd(int whichButton, const char* tclCommand);

    /// Returns the Tcl command associated with the button or null.
    const char* getCmd(int whichButton) const;

    /// Sets the minimum width of all buttons.
    void setButtonWidth(int width);

    /// Sets the minimum width of a single button.
    void setButtonWidth(int whichButton, int width);

    /// Returns the minimum width of a button;
    int getButtonWidth(int whichButton) const;

    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );

  protected:    
    struct HXCORE_API Element {
        void initFrom( const Element* ref );
        unsigned int sensitivity:1;
        unsigned int hasSnapToggle:1;
        unsigned int isSnapped:1;
        unsigned int buttonWidth:8;
        McString label;
        McString cmd;
        QxGuardedPtr<QxPushButton> button;
        Element();
    };
    
    short index;
    McDArray<Element> elements;
    unsigned short modifierFlags;
        
    void initWidgets();
    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
};

#endif


/// @}
