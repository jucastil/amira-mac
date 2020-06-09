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
#ifndef HX_PORT_TOGGLE
#define HX_PORT_TOGGLE

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <hxcore/HxPort.h>


class QCheckBox;

/** This port provides multiple toggle buttons.
    The number of toggles is set in the constructor or with the setNum() method.
    In addition to the port's label ( which is set by @c HxPort::setLabel)
    you can set a label for each toggle using setLabel(). It is also
    possible to set the sensitivity for each toggle.
    A toggle might also be handled in tri-state mode.

    See the @htmlonly <a href= ../usersguide/HxPortToggleList.html> usersguide </A> @endhtmlonly 
    for a detailed view of the port's GUI.
*/
class HXCORE_API HxPortToggleList : public HxPort {

  MC_ABSTRACT_HEADER(HxPortToggleList);

  public:
    /// Constructor.
    HxPortToggleList(HxObject *object, const char* name, int nItems=1);

    /// Constructor.
    HxPortToggleList(HxEditor *editor, const char* name, int nItems=1);

    /// Destructor.
    virtual ~HxPortToggleList();

    /// Set number of toggles.
    void setNum(int nItems);

    /// Returns the number of toggles.
    int getNum() const { return nItems; }

    /** Returns state of given toggle.
        If the toggle is in tri-state mode, then the value of getMask() must be considered as well.
        @see getMask()
    */
    int getValue(int which=0) const;

    /// Sets state of first toggle.
    void setValue(int onOrOff) { setValue(0,onOrOff); }

    /// Sets value of given toggle.
    void setValue(int which, int onOrOff);

    /// Checks if specified toggle is sensitive.
    int getSensitivity(int which=0) const;

    /// Makes first toggle sensitive or insensitive.
    void setSensitivity(int onOrOff) { setSensitivity(0,onOrOff); }

    /// Makes given toggle sensitive or insensitive.
    void setSensitivity(int which, int onOrOff);

    /// Sets label of port.
    void setLabel(const char* l) { HxPort::setLabel(l); }

    /// Returns label of port.
    const char* getLabel() const { return HxPort::getLabel(); }

    /// Sets label of specified toggle.
    void setLabel(int which, const char* label);

    /// Returns label of specified toggle.
    const char* getLabel(int which) const { return labels[which]; }

    /// Sets visibility of specified toggle.
    void setToggleVisible(int which, bool onOrOff);

    /// Returns visibility of specified toggle.
    bool isToggleVisible(int which);

    /// Parse method.
    virtual int parse(Tcl_Interp*, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    /// Looks through all labels and replaces \c currentString with \c newString if the first could be found.
    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);

    /// Overloaded untouch method also untouches all items.
    virtual void untouch( bool untouchConnectedPorts = true );

    /** Check if specified element is new. While the standard method
        HxPort::isNew() returns true is any element has been modified
        the method allows you to detect which element was modified. */
    bool isItemNew(int id);


    /** @name Tri-State Functions

        Functions dealing with the tri-state mode of a toggle
        --
        You can safely ignore those functions,
        if you want to have "normal" checkboxes with two states.
    */
    //@{

    /** Sets value and mask of first toggle.
        @see getMask(), setIsTristate()
    */
    void setValueAndMask(int valueOnOrOff, int maskOnOrOff)
        {setValueAndMask(0, valueOnOrOff, maskOnOrOff);};

    /** Sets value and mask of given toggle.

        \code
        //"On" state
        setValueAndMask(i, 1, 1);

        //"Off" state
        setValueAndMask(i, 0, 1);

        //"No Change" state
        setValueAndMask(i, 1, 0);
        \endcode

        If you pass zero for @c maskOnOrOff then @c valueOnOrOff will always be set to 1.

        @see getMask(), setIsTristate()
    */
    void setValueAndMask(int which, int valueOnOrOff, int maskOnOrOff);

    /** Sets mask of first toggle.
        @see getMask(), setIsTristate()
    */
    void setMask(int onOrOff) {setMask(0, onOrOff);};

    /** Sets mask of given toggle.
        @see getMask(), setIsTristate()
    */
    void setMask(int which, int onOrOff);

    /** Returns mask of given toggle.
        If the mask is non-zero, then getValue() returns the boolean state of the toggle.
        If the mask is zero, then this represents the third state of the button.
        This third state can be interpreted as <b><tt>No Change</tt></b>;
        it is neither \b On nor \b Off.
        The following examplifies the correct usage of getValue() and getMask()
        if the toggle \c i is in tri-state mode:

        \code
        if (portToggles.getMask(i))
        {
            if (portToggles.getValue(i))
            {
                //"On" state
            }
            else
            {
                //"Off" state
            }
        }
        else
        {
            //"No Change" state
        }
        \endcode


        The following examplifies the usage of the three states in a more compact form:

        \code
        bool bMyParam = portToggles.getMask(i) ? portToggles.getValue(i) : DefaultValueOfMyParam;
        \endcode

        @note The mask is always non-zero if the toggle is \b not in tri-state mode.
    */
    int getMask(int which=0) const;

    ///Set or Unset the tri-state mode of the first toggle.
    void setIsTristate(int onOrOff) {setIsTristate(0, onOrOff);};

    /** Set whether the given toggle should be a tri-state check box or not.
        By default toggles are \b not in tri-state mode.
        If the toggle is in tri-state mode, then it can have the states

            - On
            - Off
            - No Change
        
        The interpretation of the third state is up to the programmer.
        For retrieving the current state in this mode see getMask().
    */
    void setIsTristate(int which, int onOrOff);

    ///Returns, whether the toggle is in tri-state mode or not.
    int getIsTristate(int which=0) const;

    //@}

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );



  protected:
    int nItems;
    McBitfield state;
    McBitfield mask;
    McBitfield isTristate;
    McBitfield isVisibleList;
    McBitfield sensitivity;
    McBitfield newFlags;
    McDArray<McString> labels;
    McDArray< QxGuardedPtr<QCheckBox> > toggleList;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
    virtual void destroyWidget();

    void setUIToggleState(int which);

    void commonInit();
};

#endif // HX_PORT_TOGGLE

/// @}
