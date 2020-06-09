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
#ifndef HX_PORT_MULTIOPTIONS_H
#define HX_PORT_MULTIOPTIONS_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxPort.h>
#include <hxcore/QxGuardedPtr.h>

class QListView;
class QComboBox;
class QPushButton;
class QStandardItemModel;
/** Provides multiple checkable options.
    In the moment, it is possible to have the options displayed as a
    list view (default) or as pull down menus.

    Each option item has a text and an associated check state which can be set
    using the setValue(int, bool) method.

    If an option has been changed by the user the @c port is marked to be @c new.
    Then, you can use getValue() to find out which value is set for each menu.
*/
class HXCORE_API HxPortMultiOptions : public HxPort
{
    MC_ABSTRACT_HEADER( HxPortMultiOptions );
public:
    enum DisplayType{ LISTVIEW, COMBOBOX };

    enum CheckState {
        UNCHECKED = 0,
        PARTIALLY_CHECKED = 1,
        CHECKED = 2
    };

    /**
     * Constructor.
     */
    HxPortMultiOptions(HxObject* object, const char* name, DisplayType = LISTVIEW, bool isTristate = false);

    /**
     * Destructor.
     */
    virtual ~HxPortMultiOptions();

    /// Returns the number of elements.
    int getNum() const;

    /// Adds an item with the given text and check state.
    void addItem(const McString & text, bool checkstate) { addItem(text, checkstate ? CHECKED : UNCHECKED); }

    /// Adds an item with the given text and check state.
    void addItem(const McString & text, CheckState checkstate);

    /// Removes the item at the given index.
    void removeItem(int index);

    /// Sets the value of the specified element.
    void setValue(int index, bool checkstate) { setValue(index, checkstate ? CHECKED : UNCHECKED); }

    /// Sets the value of the specified element.
    void setValue(int index, CheckState checkstate);

    using HxPort::setLabel;
    /// Sets the label of the specified element.
    void setLabel(int id, const char* text);

    /// Get value of the specified element.
    CheckState getValue(int index) const;

    /// Get text of the specified element.
    McString getText(int index) const;

    /// Sets all items to be checked if state is true
    void selectAll(CheckState state);

    /// Removes all items.
    void clear();

    /// Resize the ListView height to show the specified number of rows.
    void setNumRows(int rows);

    /**
    *  Copy values from refPort and update GUI.
    *  
    */
    virtual void initFrom( HxPort* refPort );

protected:
    /**
     * Inherited from HxPort.
     */
    virtual void createWidget(QWidget* parent);
    virtual void guiCallback();
    virtual int parse(Tcl_Interp* interpreter, int argc, char** argv);
    virtual void getState(McString& state);
    virtual int setState(const McString& state);

private:
    void disableNotifications(bool state);

    DisplayType m_displayType;

    QxGuardedPtr<QListView> m_listView;
    QxGuardedPtr<QComboBox> m_comboBox;
    QxGuardedPtr<QPushButton> m_selectAllBtn;
    QxGuardedPtr<QPushButton> m_deselectAllBtn;

    QStandardItemModel * m_model;

    int m_numRows;
    bool m_isTristate;
};

#endif

/// @}
