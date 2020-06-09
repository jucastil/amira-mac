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

/// @addtogroup hxdemodirector hxdemodirector
/// @{
#ifndef QXGROUPITEM_H
#define QXGROUPITEM_H

#include "hxdemodirector/QxItem.h"

namespace hxdemodirector {

/**
    This class stores items and groups them together. The group item's size is
    calculated automatically according to its members. Most method calls (e.g., moveTo,
    createSelection, ...) are sent to the members. Groups may be nested.
*/
class QxGroupItem : public QxItem
{
public:
    QxGroupItem();
    virtual ~QxGroupItem();

    /// Paints a semi-transparent gray rectangle and the group's members in it.
    virtual void paint(QPainter &painter) const;

    /// Change enabled state (affects draw style and accessibility).
    virtual void setEnabled(bool enabled);
    
    /// If a member contains the mouse cursor (\see{QxGroupItem::mouseMoveEvent}), the member's 
    /// tooltip text is added to the tooltip text of the group. Otherwise only the group's
    /// tooltip text is returned.
    virtual QString getToolTip() const;
    
    /// Returns a pointer to the member item at the given point or the group itself.
    virtual QxItem* getItemAt(const QPointF &point);
    /// Returns the item with the leftmost left border.
    virtual QxItem* getLeftmostItem(bool ignoreFloatingItems=false, QList<QxItem*> *ignoreItems=0);
    /// Returns the item with the rightmost right border.
    virtual QxItem* getRightmostItem(bool ignoreFloatingItems=false, QList<QxItem*> *ignoreItems=0);
    
    // Moving
    virtual void setMoveable(bool moveable);
    virtual bool getMoveable() const;
    /// Move all items to the given point.
    virtual void moveTo(const QPointF &pos);
    /// Translate all items by the given offset.
    virtual void translate(const QPointF &offset);
    
    // Moving via selections
    /// Move the group to the new position.
    virtual void moveTo(const QPointF &pos, Selection &selection);
    /// For each member a position command (\see{QxItem::createPositionCmd}) is created
    /// and send to the DemoDirector via \see{QxItem::sendCmd}.
    virtual void endMoving(const QPointF &pos, Selection &selection);
    
    // Snapping stuff
    /// Returns the closest snapping position of all items.
    virtual QPointF getClosestSnapPos(const QPointF &pos, const QList<Selection> &selections) const;
    /// \copydoc QxItem::showSnapPos
    virtual void showSnapPos(const QPointF &pos);
    /// \copydoc QxItem::hideSnapPos
    virtual void hideSnapPos();
    
    // Selection stuff
    /// Calls iteratively the createSelection method of all member items and returns the
    /// first non-emtpy result. If no item returns a result, a selection for the group is created.
    virtual QList<Selection> createSelections(const QPointF &pos);
    /// Calls iteratively the createSelection method of all member items and returns the
    /// concatenation of all results. The group item itself is not considered.
    virtual QList<Selection> createSelections(const QRectF &selectionArea);
    /// Tests wheter the given point is inside the group's bounding box.
    virtual bool inSelection(const QPointF &pos, const Selection &selection) const;
    
    // Group stuff
    virtual void addItem(QxItem *item);
    /// Returns a pointer to the item with the given id or 0.
    virtual QxItem* getItem(int id);
    /// Returns a pointer to the item with the given label or 0.
    virtual QxItem* getItem(const QString &label);
    /// Returns a list of all items.
    virtual QList<QxItem*> getItems() const;
    /// Deletes an item.
    virtual void deleteItem(QxItem *item);
    virtual bool isEmpty() const;
    /// Deletes all items of the group. 
    virtual void clear();
    
    // Layout stuff
    /// Calls \see{findAndProcessIntersections} and propagates changes to the parent.
    virtual void geometryChanged();
    /// Force all items to recalculate their geometry.
    virtual void recalcGeometry();
    /// Arrange all (non-floating) items so that they are not intersecting each other.
    virtual void arrange();
    /// Recalculate height of this group.
    virtual void reheight();
    /// Tests wheter some items are intersecting and rearrange them if necessary.
    virtual void findAndProcessIntersections();
    
    // Mouse events
    virtual void mousePressEvent(QMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent); 
    virtual void mouseReleaseEvent(QMouseEvent *mouseEvent);
    virtual void leaveEvent(QMouseEvent *mouseEvent);
protected:
    virtual void updateBoundingBox();
    virtual void calcBorders();
   
    // destination for mouse events
    // while moving (with/without button pressed)
    QxItem *mContainsMouse;
    // while button pressed
    QxItem *mItemHasMouse;
    
    // is group moveable?
    bool mMoveable;
    // group items
    QList<QxItem*> mItems;

    // borders/distances in logical coordinates
    qreal mTopBorder;
    qreal mBottomBorder;
    qreal mVerticalDistance;

    // GUI representation constants
    static const int cLeftBorder = 5;
    static const int cRightBorder = 5;
    static const int cTopBorder = 20; 
    static const int cBottomBorder = 5;
    static const int cHorizontalDistance = 10; 
    static const int cVerticalDistance = 5;
};

} // namespace

#endif

/// @}
