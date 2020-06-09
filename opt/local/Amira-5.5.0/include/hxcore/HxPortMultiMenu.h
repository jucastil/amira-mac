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
#ifndef HX_PORT_MULTI_MENU_H
#define HX_PORT_MULTI_MENU_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxPort.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>

class QComboBox;

/** Provides one or multiple option menus (combo boxes) in one line.
    In the moment, it is possible to have one to three menus displayed
    as pull down menus in the same order as given in the constructor.

    Each option menu has its label and a list of items which can be set
    using one of the setLabel() methods. Remember that the port's label
    can be set by calling @c HxPort::setLabel.

    If an option has been changed by the user the @c port is marked to be @c new.
    Then, you can use getValue() to find out which value is set for each menu.

    Just as for ports it is possible to make menus @c insensitive.
    You also can set the sensitivity of a particular item of a menu.

    See the  @htmlonly <a href= ../usersguide/HxPortMultiMenu.html> usersguide </A> @endhtmlonly
    for a detailed view of the port's GUI. */
class HXCORE_API HxPortMultiMenu : public HxPort {
    MC_ABSTRACT_HEADER(HxPortMultiMenu);

  public:
    /// Constructor for objects, creates one menu with n1 items.
    HxPortMultiMenu(HxObject *object, const char* name, int n1);

    /// Constructor for objects, creates two menus with given number of items.
    HxPortMultiMenu(HxObject *object, const char* name, int n1, int n2);

    /// Constructor for objects, creates three menus with given number of items.
    HxPortMultiMenu(HxObject *object, const char* name, int n1, int n2, int n3);

    /// Constructor for editors, creates one menu with n1 items.
    HxPortMultiMenu(HxEditor *editor, const char* name, int n1);

    /// Constructor for editors, creates two menus with given number of items.
    HxPortMultiMenu(HxEditor *editor, const char* name, int n1, int n2);

    /// Constructor for editors, creates three menus with given number of items.
    HxPortMultiMenu(HxEditor *editor, const char* name, int n1, int n2, int n3);

    /// Destructor.
    ~HxPortMultiMenu();

    /// Sets the number of menus.
    void setNumMenus( int numMenus );

    /// Returns the number of menus.
    int getNumMenus() const { return data.size(); }

    /// Returns value of a particular menu.
    int getIndex(int whichMenu=0) const;

    /// Sets value of first menu.
    void setIndex(int value);

    /// Sets value of given menu.
    void setIndex(int whichMenu, int value, int forceNew = 0);

    /** Sets index with text @c label in first menu. If the menu does not
        an entry with text @c label 0 is returned, otherwise 1. */
    int setIndex(const char* label);

    /** Sets index with text @c label ingiven menu. If the menu does not
        an entry with text @c label 0 is returned, otherwise 1. */
    int setIndex(int whichMenu, const char* label);

    /// Same as getIndex(int).
    int getValue(int whichMenu=0) const { return getIndex(whichMenu); }

    /// Same as setIndex(int).
    void setValue(int value) { setIndex(value); }

    /// Same as setIndex(int,int).
    void setValue(int whichMenu, int value) { setIndex(whichMenu,value); }

    /// Same as setIndex(const char*).
    int setValue(const char* label) { return setIndex(label); }

    /// Same as setIndex(int, const char*).
    int setValue(int whichMenu, const char* label) { return setIndex(whichMenu,label); }

    /// Sets number of items of first menu.
    void setNum(int nItems) { setNum(0,nItems); }

    /// Sets number of items of specified menus.
    void setNum(int whichMenu, int nItems);

    /// Returns number of items of given menu.
    int getNum(int whichMenu=0) const;

    /// Sets port's label.
    void setLabel(const char* label) { HxPort::setLabel(label); }

    /// Returns label of port.
    const char* getLabel() const { return HxPort::getLabel(); }

    /// Sets text of entry specified by @c item in first menu to label.
    void setLabel(int item, const char* label) { setLabel(0,item,label); }

    /// Gets the @c item'th label in the menu specified by @c whichMenu.
    const char* getLabel(int item) const { return getLabel(0,item); }

    /// Sets a label in the menu specified by @c whichMenu.
    void setLabel(int whichMenu, int item, const char* label);

    /// Gets the @c item'th label in the menu specified by @c whichMenu.
    const char* getLabel(int whichMenu, int item) const;

    /// Sets sensitivity of first menu.
    void setMenuSensitivity(int isOn) { setMenuSensitivity(0,isOn); }

    /// Sets sensitivity of a whole menu.
    void setMenuSensitivity(int whichMenu, int isOn);

    /// Gets sensitivity of a whole menu.
    int getMenuSensitivity(int whichMenu=0) const;

#ifndef PORTMULTIMENU_NO_SET_SENSITIVITY
    /** Sets sensitivity of a particular item in first menu.
        Warning: This method had a different meaning in Amira 2.x. It
        was there use to set the sensitivity of a whole menu. */
    void setSensitivity(int item, int isOn) { setSensitivity(0,item,isOn); }
#endif

    /// Sets sensitivity of a particular item in any menu.
    void setSensitivity(int whichMenu, int item, int isOn);

    /// Gets sensitivity of a particular item in first menu.
    int getSensitivity(int item) const { return getSensitivity(0,item); }

    /// Gets sensitivity of a particular item in any menu.
    int getSensitivity(int whichMenu, int item) const;

    /// Command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    /// returns the number of "sensitive" items in given menu
    int getNumSelectableItems(int whichMenu) const;

    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );

  public:
    struct HXCORE_API Menu {
        Menu();
        void setNum(int nItems);
        void initFrom( Menu* refMenu );
        QxGuardedPtr<QComboBox> menu;
        unsigned int current:15;
        unsigned int sensitivity:1;
        McDArray<McString> labels;
        McBitfield itemSensitivity;
        McDArray<int> comboItems;
    };

  protected:
    McDArray<Menu> data;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
};

#endif

/// @}
