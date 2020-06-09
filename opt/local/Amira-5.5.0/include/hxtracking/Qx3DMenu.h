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

/// @addtogroup hxtracking hxtracking
/// @{
#ifndef QX_3D_MENU_H
#define QX_3D_MENU_H

#include <hxtracking/hxtrackingAPI.h>

#include <qstring.h>
#include <qobject.h>
#include <Q3Signal>
#include <Q3PopupMenu>

#include <mclib/McColor.h>
#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McHandable.h>
#include <hxcore/HxObject.h>
#include <hxcore/HxInterface.h>
#include <hxcore/HxObjectPoolListener.h>
#include <amiramesh/HxParseUtils.h>

#include <hxtracking/Hx3DWand.h>
#include <hxtracking/Qx3DWidget.h>
#include <hxtracking/QxTrackingNotifier.h>

class Qx3DMenu;
class Qx3DSubMenu;

/** Represents a button in a 3D menu. In addition to the properties of an
    ordinary Hx3DButton this class stores an ID which can used to address
    the button in a submenu as well as a pointer to the submenu the button
    belongs to. */
class HXTRACKING_API Qx3DMenuItem : public Hx3DButton
{
  Q_OBJECT

  public:
    /** Constructor. Creates a 3D button widget but does not yet insert it
        into a menu. This can be done by calling Qx3DSubMenu::insertItem(). */
    Qx3DMenuItem();

    /** Destructor. If the 3D button is inserted into a submenu it will be
        automatically removed from it. */
    ~Qx3DMenuItem();

    /** Returns the ID of the button. The ID can be used to address the button
        in a menu. It can be set by the user when inserting the button into a
        submenu by calling Qx3DSubMenu::insertItem(). */
    int id() const { return theId; }

    /** Returns a pointer to the submenu associated with the button. If there
        is no submenu associated with the button NULL is returned. */
    Qx3DSubMenu* subMenu() const { return theSubMenu; }

    /** Returns a pointer to the parent menu the button belongs to. If the
        button has not yet been inserted into a submenu NULL is returned. */
    Qx3DSubMenu* parentMenu() const;

    /** List of Tcl commands to be executed when the button is pressed.
        Each command string is executed in the global Tcl namespace using
        the method theInterpreter->eval(). */
    McDArray<McString> procs;

  protected slots:
    /** This method is called when the button is pressed. The default
        implementation executes all Tcl procedures associated with the
        button. It also update the master menu if there is a submenu
        associated with this item. If you overload this method in a derived
        class you should call the original method as well. */
    virtual void activate();

  protected:
    int theId;
    Qx3DSubMenu* theSubMenu;

  friend class Qx3DSubMenu;
};

/** Represents a menu consisting of a set of 3D buttons or of additional
    submenus. The elements of the menu are derived from Qx3DMenuItem.
    When a button is selected the activate() method of this item is
    called. In addition to its 3D representation the menu also creates
    an ordinary Q3PopupMenu with the same contents. This menu will be
    inserted under the VR menu in the Amira main window. */
class HXTRACKING_API Qx3DSubMenu : public Qx3DWidget
{
    Q_OBJECT

  public:
    /** Constructor. Creates an empty submenu but does not yet insert it
        into any parent menu. This is done by calling insertItem() for the
        parent menu. */
    Qx3DSubMenu();

    /** Destructor. If the menu has a parent menu it will be automatically
        removed from that menu. If the parent menu is deleted all submenus
        will also be deleted. */
    ~Qx3DSubMenu();

    /** Adds a new button to the menu. The new button can be accessed later
        using the specified id. If id is -1, a new unused id will be used.
        The actual id of the new button will be returned. index determines
        at which position the button should be inserted. If the index is -1
        the button will be appended at the end. */
    int insertItem(const QString& text, int id=-1, int index=-1);
    
    /** Inserts a submenu into this menu. The submenu is represented by a
        new button with the specified text. */
    int insertItem(const QString& text, Qx3DSubMenu* menu, int id=-1, int index=-1);
    
    /** Inserts an existing menu item (button) into this menu. The label of
        the button will be set to the specified text. */
    int insertItem(const QString& text, Qx3DMenuItem* item, int id=-1, int index=-1);

    /** Connects the item with the specified id to some slot. If the
        respective item is selected the slot method is called. */
    bool connectItem(int id, const QObject* receiver, const char* member);
    
    /** Disconnects a slot from the item with the specified id. */
    bool disconnectItem(int id, const QObject* receiver, const char* member);
    
    /** Removes the item at position @c index. The item will be automatically
        deleted. If there is a submenu associated with the item this submenu
        as well as all items in there will be deleted too. */
    void removeItemAt(int index);
    
    /** Remove the item with the specified id. The item will be automatically
        deleted. If there is a submenu associated with the item this submenu
        as well as all items in there will be deleted too. */
    void removeItem(int id);
    
    /** Removes all items from the menu. */
    void clear();
    
    /** Returns the number of items in this menu. */
    int count() const { return mitems.size(); }
    
    /** Returns the index of the item with the specified id. The index is
        equivalent to the position of the item in the menu. */
    int indexOf(int id) const;
    
    /** Returns the id of the item at position @c index. */
    int idAt(int index) const { return mitems[index]->id(); }
    
    /** Returns the item with the specified id. */
    Qx3DMenuItem* findItem(int id) { return itemAt(indexOf(id)); }

    /** Returns the item at position @c index. */
    Qx3DMenuItem* itemAt(int index);

    /** Sets the foreground and background colors of an item. The foreground
        color is used for the label text. */
    void setItemColor(int id, const McColor& fg, const McColor& bg);

    /** Returns a pointer to the parent menu. If the menu has not yet been
        inserted into a parent menu a NULL pointer is returned. */
    Qx3DSubMenu* parentMenu() const { return mParentMenu; }

    /** Returns a pointer to the master menu. The master menu is the topmost
        menu in the hierarchy. This menu should be of type Qx3DMenu. If it
        is not a NULL pointer is returned. */
    Qx3DMenu* masterMenu();
    
  signals:
    /** This signal is emitted when the item specified by @c id is selected. */
    void activated(int id);

  protected:
    void arrange(float minwidth);
    int parse(Tcl_Interp* t, int argc, char **argv);

    int theId;
    Q3PopupMenu* popupMenu;
    Qx3DSubMenu* mParentMenu;
    McDArray<Qx3DMenuItem*> mitems;

  friend class Qx3DMenu;
  friend class Qx3DMenuItem;
};

/** Special-purpose submenu listing objects in the object pool. When this
    menu is created it automatically inserts a button for each object in
    the object pool which matches a particular type. When such a button is
    pressed the 3D version of the object's user interface will be shown.
    When new objects are inserted into the object pool new buttons will be
    created if necessary. When objects are removed from the object pool
    the associated button will also be removed from this menu. */
class HXTRACKING_API Qx3DObjectMenu : public Qx3DSubMenu, public HxObjectPoolListener
{
  public:
    /// Constructor. The menu lists all objects of type @c type.
    Qx3DObjectMenu(const McTypeInfo* type);

    /// Inherited from HxObjectPoolListener.
    void objectAdded(HxObject* object);
    void objectRemoved(HxObject* object);
    void objectRenamed(HxObject* object, const char* oldName);

  protected:
    const McTypeInfo* type;

  friend class Hx3DGuiInterface;
};

/** Represents the amiraVR top-level 3D menu. The menu will also be
    inserted as a Qt submenu under the VR menu in the amira main
    window. */
class HXTRACKING_API Qx3DMenu : public Qx3DSubMenu {

  Q_OBJECT

  public:
    /** Constructor. There will be a new Tcl routine registered with name
        @c name. This routine allows it to configure the menu via Tcl. */
    Qx3DMenu(const char* name);

    /// Destructor.
    ~Qx3DMenu();

    /** Restores the default menu. The default menu contains two submenus,
        one listing all modules in the object pool, and the other one
        listing all data objects in the object pool. */
    void reset();

    /// Sets position and orientation of the menu.
    void setPosition3D(const SbVec3f& pos, const SbRotation& rot);

    /// Handles all 3D mouse events
    virtual void handleEvent(Hx3DWand* wand, HxVREvent* event);

    /// Renders the menu.
    virtual void render(unsigned int cacheId);

    /// Unsets highlight state.
    virtual void focusLost();

    /// Layout child widgets.
    void arrange();

    /// Returns matrix defining the current position of the menu
    const SbMatrix& getMatrix() const { return M; }

    /// Scale size of menu in 3d space.
    virtual void setScale(float scaleFactor);

    /// Schedules an arrange() and redraw() action.
    virtual void touch();

    /** Pops up the 3D user interface for the specified object. If value
        is 0 the 3D user interface of the object is hidden. If value is
        -1 it will be shown if it was hidden before or it will be hidden
        if it was visible before. */
    void showGUI(HxObject* object, int value=1);
    
    /** Sets menu toggle of AmiraVR tracking module. */
    virtual void show();

    /** Unsets menu toggle of AmiraVR tracking module. */
    virtual void hide();

    /** Returns a pointer to the global 3D menu. The global 3D menu can be
        accessed on the Tcl level using the routine @c menu. */
    static Qx3DMenu* getGlobalInstance();

  public slots:
    void menuBack();
  
  protected:
    SbMatrix M, MI, refMat;
    unsigned int isMoving:1;
    unsigned int isActive:1;
    unsigned int isArranged:1;
    Hx3DLabel* label;
    Hx3DButton* closeButton;
    Hx3DButton* backButton;
    Qx3DSubMenu* currentMenu;
    float scale;

    static int staticParse(ClientData, Tcl_Interp*, int, char**);

  friend class Qx3DSubMenu;
  friend class Qx3DMenuItem;
};

#define the3DMenu Qx3DMenu::getGlobalInstance()

#endif

/// @}
