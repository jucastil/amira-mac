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
#ifndef HX_PORT_H
#define HX_PORT_H

#include <tcl.h>
#include <mclib/McString.h>
#include <mclib/McInterface.h>
#include <hxcore/HxBase.h>
#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/QxGuardedPtr.h>




class HxObject;
class HxEditor;
class HxRemoteSessionController;
class QWidget;
class QLabel;
class QxPortLayout;
class QPixmap;
class QxLineEdit;
class QToolButton;
class QxPortNotifier;
class HxPreferences;
class HxInterconnection;
class QIcon;

/** Base class for all ports.
    This is the base class for all ports. A port can contain various
    widgets to control or define a state of the owner object. After
    a control element has been changed, the compute method of
    the object is called. A port is displayed in the work area. Widgets
    are created the first time the port becomes visible. Each port has
    an special button called Pin on its left side. The state of the pin
    controls the visibility of the port independent of the objects
    visibility state. 
*/

class HXCORE_API HxPort : public McInterface
{

   MC_ABSTRACT_HEADER(HxPort);

  public:
    /** Constructor for objects.
        The label will be generated from the port name. 
        For example:
        portMapLocation("mapLocation",...) -> label will be "Map location:"

        Rules of port names:
        - first letter is lower case
        - no blanks, no underscores ('_')
        - use upper letters to separate words
    */
    HxPort(HxObject* object, const char* name);

    /// Constructor for editors. 
    HxPort(HxEditor* editor, const char* name);
  
    /// Destructor.
    virtual ~HxPort();
    
    /** Returns the class the port belongs to. This may either be an
        instance of type HxObject or of type HxEditor, depending on which
        constructor has been used. */
    HxBase* owner() { return theOwner; }

    /** Returns the object the port is associated with. If the port
        belongs to an HxObject this is the object itself (same as the
        owner). If the port belongs to an editor, this is the object
        attached to the editor or null, if the editor has not yet been
        attached to an object. */
    HxObject* object() { return theObject; }

    /// The name of the port is used in Tcl commands.
    const char *name() const { return theName; }

    /// Changes the port's name.
    void rename(const char* newName);

    /** Sets an alias name for a port. Alias names are mainly used to
        ensure script compatibility. If you want to change the name of a
        port in some user-defined module, you should specify the old
        name as an alias. Otherwise old scripts cannot be run anymore. */
    void setAliasName(const char* name);

    /// Returns true if port has been modified.
    int isNew(unsigned int mask=0xffffffff) const { return newFlag & mask; }

    /// Returns true if port must force spread fire to interconnected 
    const bool forceSpreadFire(){ return m_forceSpreadFire;}

    /** Sets or unsets the pin. If a port is pinned it will be displayed
        in the work area even if the object itself is deselected. */
    void setPin(int state);

    /// Reports whether the pin has been set or not.
    int getPin() const { return pinFlag; }

    /// Check if port has a pin (if not setPin() and showPinButton(bool showIt) are ignored).
    int hasPin() { return hasPinFlag; }

    /**
     *  Show or hide the pin button.
     */
    void showPinButton(bool showIt);

    /** Marks port as modified, simulating a change to it. This method is
        virtual in order to allow ports to update their visual state
        whenever something is new. In particular, HxPortColormap overloads
        this method to adjust the min-max values. */
    virtual void touch(unsigned int mask=0xffffffff);

    /** Marks port as unmodified. 
        If untouchConnectedPorts is set to false, don't spread untouch to eventual connected ports.
        This can be useful when 2 ports (or more) are synchronized in a module :
        Any modification to one of the port is reported to the other. We need then to untouch the port,
        But not the interconnected ones, since really modified.
    */
    virtual void untouch( bool untouchConnectedPorts = true );

    /// Tell object to invoke computation.
    void send();

    /// Show user interface, if port has one.
    virtual void show();

    /// Hide user interface.
    virtual void hide();

    
    /// Increases hide mask by one. Port may only be visible if hide mask is zero.
    void hideMaskIncrease();

    /// Decreases hide mask by one. Port may only be visible if hide mask is zero.
    void hideMaskDecrease();

    /// Gets the value of the hide mask.
    int  getHideMask() const;

    /// Returns true if user interface is shown.
    int isVisible() { return visible; }

    void setVisible(bool state);

    /// Set text of label widget, e.g. "Options:".
    virtual void setLabel(const char* text);

    /// Returns the port's label.
    const char* getLabel() const { return labelString; }

    /// Set label width or enable autoresize if width is zero.
    void setLabelWidth(int width);

    /// Returns current label width, see also HxPort::align().
    /// If autoResize == true, it returns the label width as if
    /// autoresize is set to on.
    int getLabelWidth(bool autoResize=false);
    
    /** Change position of port in port list. On default, ports are
        shown in the same order as they are defined in the header file
        of an object. With this method the position of a port can be
        changed afterwards. This is useful if a derived class adds a
        new port which should not appear behind all other ones. */
    void reposition(int newIndex);

    /** Returns an ascii representation of the port's state. The result
        can be used to restore the port's state using setState. This
        mechanism is used in the default saveState() method. It is also
        very useful for programming Amira script objects. There is
        no common rule how the state of a port should be encoded in the
        string. This can be decided by every port on its own. */
    virtual void getState(McString& state);

    /** Restores the state of a port. The argument should have been set
        by a prior call to getState(). Returns 0 if an error occured. */
    virtual int setState(const McString& state);

    /** Save state method. This method is called for each port when the
        Amira network is saved to disk. Overloaded methods should write
        one or more Tcl commands which when executed restore the state
        of the port. The default implementation call getState() and writes
        an appropriate setState command. There is no need to overload this
        method if getState() and setState() are implemented correctly. */
    virtual void saveState(FILE* fp);

    /// Tcl command interface of port.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Returns the port notifier (internal use only).
    QxPortNotifier* portNotifier();

    /// Internal use only. Called when an editor is attached to an object.
    void createExternal(HxObject* object, int buildWidget=1);

    /** Use this method to align the labels of multiple ports. The method
        sets the label widths of all specified ports to the same value,
        namely to the width of the widest label. The label widths will not
        be adjusted automatically when the label texts are changed later. */
    static void align(int num, HxPort** ports, bool autoResize = false);

    /** Convenience method for aligning up to 15 different ports. The
        ports are aligned in the same way as in the method above. */
    static void align(HxPort* port1, HxPort* port2,
                      HxPort* port3=0, HxPort* port4=0, HxPort* port5=0,
                      HxPort* port6=0, HxPort* port7=0, HxPort* port8=0,
                      HxPort* port9=0, HxPort* portA=0, HxPort* portB=0,
                      HxPort* portC=0, HxPort* portD=0, HxPort* portE=0,
                      bool autoResize = false);


    static void switchAllPortLabels(const McString& currentString, const McString& newString);
    virtual void switchSinglePortLabels(const McString& /*currentString*/, const McString& /*newString*/) {}

    /// To get the baseWidget.
    virtual QWidget* getBaseWidget();

    /// To set the noDuplicateFlag.
    inline void setNoDuplicateFlag(bool noDuplicate = true) {noDuplicateFlag = noDuplicate;};

    /// To know if the port can be duplicated.
    inline bool canBeDuplicated() const {return !noDuplicateFlag;};

#define HX_ANY_REMOTE_CONTROLLER ((HxRemoteSessionController*)-1)

    /** specifies the controller that should synchronize this port.
        special value: use HX_ANY_REMOTE_CONTROLLER for all (default). */
    void setAllowedRemoteController(HxRemoteSessionController* ctrl);
    HxRemoteSessionController* getAllowedRemoteController() { return m_allowedRemoteCtrl; }

    virtual void checkRemoteMode();
    void setEnabled(bool);
    bool isEnabled() const { return m_enabled; }


	void blockSynchro(bool synchroEnabled);

    //interconnect port to referencePort.
    bool interconnect( HxPort* referencePort );

    //disconnect port from referencePort.
    bool disconnect( HxPort* referencePort );

    // Return interconnection manager
    HxInterconnection* getInterconnection( bool create = true );

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort ){}

    /// sets the given @c icon with the values for the pin toggle icon.
    static void setPinIcon(QIcon& icon);

    /// Returns true if port requires explicit fire() in network file.
    bool fireOnSaveNetwork() const { return m_fireOnSaveNetwork; }

    /// Set state of flag for call of explicit fire() in network file.
    void setFireOnSaveNetwork( bool state ) { m_fireOnSaveNetwork = state; } 

  protected:
    /** Creates the port's base widget, the pin, and the label. Derived
        ports should overload this method to create the widgets they need.
        In the overloaded method first HxPort::createWidget(parent) should
        be called. Then additional widgets can be created as childs of
        @c baseWidget. Additional widgets should also be added to the
        QxPortLayout @c layout provided by the base class. Finally, the
        method baseWidget->adjustSize() should be called. */
    virtual void createWidget(QWidget* parent);

    /// destroys the port's gui resources.
    virtual void destroyWidget();

    /** Called by thePortNotifier. Every port has its own notifier which
        is derived from QObject. Relevant signals of the widgets of a new
        port should be connected to the matching generic slots of the
        notifier. If the notifier receives a signal it calls the method
        guiCallback() of the port. In this method you can check which
        widget has sent the signal by calling thePortNotifier->sender(),
        update the port and then call send() in order to fire the network. */
    virtual void guiCallback();

    /** This method should be called by derived classes whenever the value
        of the port changes. It does the same as touch(), i.e., it modifies
        the new flags by @c mask, but in addition it also causes the port
        notifier to emit a valueChanged() signal. */
    virtual void valueChanged(unsigned int mask=0xffffffff);

    /** Called by thePortNotifier. This method is called when the pin of
        a port is toggled. The method updates the isPinned() flag of the
        object the port belongs to. If necessary it also remove the object
        from the list of visible objects of the work area. */
    void pinToggled(bool);

    void commonInit(const char* name);

    /**
     * Called in commonInit and rename to fix the port's label.
     */
    static McString autoLabel(const char* name);

    /**
     *  To be notified that preferences changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

    HxBase* theOwner;
    HxObject* theObject;
    McString theName;
    McString labelString;
    McDArray<McString> aliasNames;

    QxGuardedPtr<QWidget> baseWidget;
    QxGuardedPtr<QToolButton> pin;
    QxGuardedPtr<QLabel> label;
    QxGuardedPtr<QxPortLayout> layout;
    QxPortNotifier* thePortNotifier;
    
    /*
    If true, force fire spreading to interconnected modules.
    Reset after owner's call to fire().
    */
    bool m_forceSpreadFire;

    unsigned int newFlag;
    unsigned int pinFlag:1;
    unsigned int visible:1;     // the real visibility
    unsigned int hasLabel:1;
    unsigned int hasPinFlag:1;
    unsigned int labelWidth:8;
    unsigned int labelShift:4;
    unsigned int canBeAnimated:1;
    unsigned int visibleHint:1; // set by show() and hide()
    unsigned int hideMask:8;
	/// To know if the port can be duplicated.
	unsigned int noDuplicateFlag:1;
    unsigned int m_enabled:1;

    // Explicit call of fire on save network (default = false)
    // If set true this flag will lead to an additional call of
    // fire in a saved network file that leads to a forced update
    // of the Object to ensure that subsequent dynamic ports are 
    // created and initialized correctly.
    bool m_fireOnSaveNetwork;

	bool m_synchroFlag;

    bool m_showPinButton;

    //Interconnection manager
    HxInterconnection* m_interconnection;

    HxRemoteSessionController* m_allowedRemoteCtrl;

    static McDArray<HxPort*> portList;

    friend class HxObjectGUI;
    friend class HxObject;
    friend class QxPortNotifier;
};

#endif


/// @}
