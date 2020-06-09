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
#ifndef HX_PORT_BUTTON_MENU_H
#define HX_PORT_BUTTON_MENU_H

#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>

#include <mclib/McDArray.h>

class QComboBox;

/** This port provides an option menu in addition to a button list.
    In the moment, it is possible to have one to three options
    displayed as pull down menus at the right side of the
    button list in the same order as given in the constructor.

    Each time an option has been changed by the user ( or a button was pressed)
    the @c port is marked to be @c new.
    Then, you can use getOptValue() to find out which value is set for
    each option or HxPortButtonList::wasHit to detect if a button was pressed.

    Just as for buttons it is possible to make options @c insensitive
    using setOptSensitivity(). You also can set the sensitivity of a
    particular item of a menu.

    See the  @htmlonly <a href= ../usersguide/HxPortButtonMenu.html> usersguide </A> @endhtmlonly 
    for a detailed view of the port's GUI.
*/
class HXCORE_API HxPortButtonMenu : public HxPortButtonList {

  MC_ABSTRACT_HEADER(HxPortButtonMenu);

  public:
    /// Object constructor.
    HxPortButtonMenu(HxObject *object, const char* name, int nButtons);

    /// Object constructor.
    HxPortButtonMenu(HxObject *object, const char* name,
                     int nButtons, int nOptEntries);
    
    /// Object constructor.
    HxPortButtonMenu(HxObject *object, const char* name,
                     int nButtons, int nOptEnt1, int nOptEnt2);
    
    /// Object constructor.
    HxPortButtonMenu(HxObject *object, const char* name,
                     int nButtons, int nOptEnt1, int nOptEnt2, int nOptEnt3);
    
    /// Editor constructor.
    HxPortButtonMenu(HxEditor *object, const char* name, int nButtons);

    /// Editor constructor.
    HxPortButtonMenu(HxEditor *object, const char* name,
                     int nButtons, int nOptEntries);
    
    /// Editor constructor.
    HxPortButtonMenu(HxEditor *object, const char* name,
                     int nButtons, int nOptEnt1, int nOptEnt2);
    
    /// Editor constructor.
    HxPortButtonMenu(HxEditor *object, const char* name,
                     int nButtons, int nOptEnt1, int nOptEnt2, int nOptEnt3);
    
    /// Destructor.
    virtual ~HxPortButtonMenu();

    /// Returns index of option menu.
    int getOptValue(int which=0) const { return menus[which].current; }

    /// Set index of first option menu.
    void setOptValue(int i) { setOptValue(0, i); }

    /// Set index of option menu @c which.
    void setOptValue(int which, int i);

    /** Select item which specified label in first option menu. If no item
        with such a label exists 0 is returned. Otherwise 1 is returned. */
    int setOptValue(const char* label) { return setOptValue(0, label); }

    /** Select item which specified label in an option menu. If no item
        with such a label exists 0 is returned. Otherwise 1 is returned. */
    int setOptValue(int which, const char* label);

    /// Set name of menu entry item in first menu.
    void setOptLabel(int i, const char* label) { setOptLabel(0, i, label); }

    /// Set name of menu entry item in menu which.
    void setOptLabel(int which, int item, const char* label);

    /// Set menu entry name items in menu which.
    void setOptLabels(int which, const McDArray<McString> & labels);

    /// Get label of given item in first menu.
    const char* getOptLabel(int item) const { return getOptLabel(0,item); }

    /// Get label of given item in first menu.
    const char* getOptLabel(int which, int item) const;

    /// Sets sensitivity of a particular item of a menu.
    void setOptSensitivity(int whichMenu, int item, int isOn);

    /// Sets sensitivity of a whole menu.
    void setOptSensitivity(int whichMenu, int isOn);

    /// Returns the sensitivity of an entry in given menu.
    int getOptSensitivity(int whichMenu, int item) const;

    /// Returns the sensitivity of a whole menu.
    int getOptSensitivity(int whichMenu) const;
    
    /// Set number of menu entries.
    void setNumOptEntries(int nEntries) { setNumOptEntries(0, nEntries); }

    /// Set number of menu entries.
    void setNumOptEntries(int which, int nEntries);

    /// Returns number of menu entries.
    int getNumOptEntries(int which=0) const 
        { return menus[which].labels.size(); }

    /// Resets the last item chosen of option menu
    void resetOptValue(int which = 0);

    /// Returns the number of menus.
    int getNumMenus() const { return menus.size(); }

    /// Called after changing the ports labels.
    void recomputeWidth();
    
    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Overloaded save method.
    virtual void saveState(FILE* fp);

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
    int nMenus;
    McDArray<HxPortMultiMenu::Menu > menus;

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
};

#endif

/// @}
