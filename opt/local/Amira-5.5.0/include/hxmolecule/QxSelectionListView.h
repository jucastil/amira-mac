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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef QX_SELECTION_LISTVIEW_H
#define QX_SELECTION_LISTVIEW_H

#include <q3listview.h>
//Added by qt3to4:
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>

#include <hxmolecule/HxMoleculeWinDLLApi.h>
#include <molecule/MtGroupRef.h>

class QWidget;
class QString;
class QxMolSelectionBrowser;

/** From Qt class @c QListViewItem derived class to overload functions
    @c paintCell, @c paintFocus and @c setSelected, and to store
    additional information in the items, such as partial selection and
    the item's group ref. */

class QxSelectionListViewItem : public Q3ListViewItem {
    
public:
    /// Information about which group in the molecule's topology is
    /// associated with the item.
    MtGroupRef gr;
    /// An item is partially selected if some but not all of its
    /// subitems are selected or partially selected.
    bool partiallySelected;

protected:
    // Used in @c setSelected to prevent item from automatically being
    // selected.
    bool isSelectable;

public:
    /// Constructor if @c QListView is parent.
    QxSelectionListViewItem(Q3ListView * parent, QString name, 
                            MtGroupRef &gr);
    /// Constructor if @c QxSelectionListViewItem is parent.
    QxSelectionListViewItem(QxSelectionListViewItem * parent, 
                            QString name, MtGroupRef &gr);
    /// Destructor.
    ~QxSelectionListViewItem();

    /// Select item.
    void mySetSelected(bool onOff);

    // used for better sorting
    //QString key( int column, bool ascending ) const;

    int compare( Q3ListViewItem* item, int column, bool ascending ) const;

protected:
    /// Overloaded function. If selected, item is painted in red, if
    /// partially selected it is painted in green, otherwise
    /// @c QListViewItem::paintCell is called.
    void paintCell(QPainter* p, const QColorGroup& cg,
                   int column, int width, int align);
    /// Overloaded function. If item is selected the font color is set
    /// to red, otherwise @c QListViewItem::paintFocus is called.
    void paintFocus(QPainter* p, const QColorGroup& cg, const QRect& r);
    /// Overloaded function to select item.
    void setSelected(bool onOff);
};

/** QListView subclass with a couple of overloaded member functions
    and special signals. */

class HXMOLECULE_API QxSelectionListView : public Q3ListView
{
    Q_OBJECT

    QxMolSelectionBrowser * mBrowser;

public:
    /// Constructor.
    QxSelectionListView(QWidget * parent, QxMolSelectionBrowser * browser = 0);

    /// Destructor.
    ~QxSelectionListView();
    
    /// Overloaded function to filter some events that need special
    /// treatment.
    bool eventFilter(QObject * o, QEvent * e);

    /// 
    QxMolSelectionBrowser * browser() { return mBrowser; }
    void setBrowser(QxMolSelectionBrowser* browser) { mBrowser = browser; }

    signals:
    // Signal is emitted if any of the headers of the list view is
    // clicked with the right mouse button.
    void rightMouseButtonPressedOnHeader(int col);
    // Signal is emitted if the mouse is moved inside the content of
    // the list view with the mouse button pressed.
    void mouseMoved(int button, Q3ListViewItem * item, 
                    const QPoint & p, int col);
    // Signal is emitted if space key is pressed. 
    void spacePressed(unsigned int ctrlPressed);

protected:
    // some overloaded functions
    void contentsMousePressEvent(QMouseEvent * e);
    void contentsMouseReleaseEvent(QMouseEvent * e);
    void contentsMouseMoveEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent * e);
    void keyReleaseEvent(QKeyEvent * e);

public:
    // Store if Ctrl or Shift button is pressed.
    // QMouseEvent::ButtonState buttonState;
    Qt::ButtonState buttonState; // QT4
    // Store current button event type, such as @c QEvent::MouseButtonPress.
    QEvent::Type buttonEventType;
    // Last current item.
    Q3ListViewItem * oldCurItem;
    // New current item.
    Q3ListViewItem * curItem;
    // Last mouse click position.
    QPoint mouseClickPosition;

    unsigned int ctrlKeyPressed:1;
    int curTooltipSection:31;
};

#endif

/// @}
