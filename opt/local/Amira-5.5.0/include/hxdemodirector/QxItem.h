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
#ifndef QXITEM_H
#define QXITEM_H

#include <QBrush>
#include <QPen>
#include <QObject>
#include <QMouseEvent>
#include <QMenu>

namespace hxdemodirector
{
/** 
    This class stores the transformation data that maps between the logical coordinate
    system of the items and the device coordinate sytem for their graphical representation.
    The transformation conists of a scaling and a translation.
    Functions for the translation are provided. The scale* methods consider  
    the scaling only, the map* functions also the translation.
*/
class Transform
{
public:
    Transform() : mScaling(1.0, 1.0), mTopLeftCorner(0.0, 0.0)
    {}
    void setScaling(const QPointF &scaling) {
        mScaling = scaling;
    }
    QPointF getScaling() const {
        return mScaling;
    }
    void setTopLeftCorner(const QPointF &corner) {
        mTopLeftCorner = corner;
    }
    QPointF getTopLeftCorner() const {
        return mTopLeftCorner;
    }
    // scene to device
    QRectF mapLToD(const QRectF &rect) const {
        return QRectF(rect.left()*mScaling.x()-mTopLeftCorner.x(), rect.top()*mScaling.y()-mTopLeftCorner.y(), 
                      rect.width()*mScaling.x(), rect.height()*mScaling.y());
    }
    QPointF mapLToD(const QPointF &point) const {
        return QPointF(point.x()*mScaling.x()-mTopLeftCorner.x(), point.y()*mScaling.y()-mTopLeftCorner.y());
    }
    qreal mapLToDX(qreal value) const {
        return value*mScaling.x()-mTopLeftCorner.x();
    }
    qreal mapLToDY(qreal value) const {
        return value*mScaling.y()-mTopLeftCorner.y();
    }
    QPointF scaleLToD(const QPointF &point) const {
        return QPointF(point.x()*mScaling.x(),point.y()*mScaling.y());
    }
    qreal scaleLToDX(qreal value) const {
        return value*mScaling.x();
    }
    qreal scaleLToDY(qreal value) const {
        return value*mScaling.y();
    }
    // device to scene
    QRectF mapDToL(const QRectF &rect) const {
        return QRectF((rect.left()+mTopLeftCorner.x())/mScaling.x(), (rect.top()+mTopLeftCorner.y())/mScaling.y(),
            rect.width()/mScaling.x(), rect.height()/mScaling.y());
    }
    QPointF mapDToL(const QPointF &point) const {
        return QPointF((point.x()+mTopLeftCorner.x())/mScaling.x(), (point.y()+mTopLeftCorner.y())/mScaling.y());
    }
    qreal mapDToLX(qreal value) const {
        return (value+mTopLeftCorner.x())/mScaling.x();
    }
    qreal mapDToLY(qreal value) const {
        return (value+mTopLeftCorner.y())/mScaling.y();
    }
    QPointF scaleDToL(const QPointF &point) const {
        return QPointF(point.x()/mScaling.x(), point.y()/mScaling.y());
    }
    qreal scaleDToLX(qreal value) const {
        return value/mScaling.x();
    }
    qreal scaleDToLY(qreal value) const {
        return value/mScaling.y();
    }
protected:
    QPointF mScaling;
    QPointF mTopLeftCorner; // device coordinates

};

class QxItem;

/**
    This class stores a selected item together with some associated information. 
    These are the selected part of the item and an offset. The offset is used while
    dragging the item and stores the distance between a defined point of the item and
    the mouse cursor start position.
*/
class Selection
{
public:
    Selection(QxItem *item, int component, QPointF offset=QPointF(0,0)) : mItem(item), 
        mComponent(component), mOffset(offset) 
    {}
    bool operator==(Selection p) {
        return (mItem == p.mItem) && (mComponent == p.mComponent);
    }
    QxItem *mItem;
    int mComponent;
    QPointF mOffset;
};

/**
    This class is the parent class for all items stored in a timeline.
    All coordinate positions are expected in logical coordinates.
*/
class QxItem 
{
public:
    QxItem();
    virtual ~QxItem();

    /// Paints the Item. Derived classes have to implement this method.
    virtual void paint(QPainter &painter) const = 0;

    // Getter/setter
    virtual void setParent(QxItem *parent);
    virtual QxItem* getParent() const;
    virtual void setIdentifier(int identifier);
    virtual int getIdentifier() const;
    virtual void setLabel(const QString &label);
    virtual QString getLabel() const;
    virtual QString getToolTip() const;
    virtual QRectF getBoundingBox() const;
    virtual qreal getLeft() const;
    virtual qreal getRight() const;
    virtual void setTransform(Transform *trans);
    virtual QPointF getPosition() const;
    virtual void setFloating(bool floating);
    virtual bool getFloating() const;
    
    /// Change enabled state (affects draw style and accessibility).
    virtual void setEnabled(bool enabled);
    virtual bool getEnabled() const;

    /// Checks whether a point is inside the item's bounding box.
    virtual bool contains(const QPointF &point) const;
    /// Returns the item at the requested position.
    virtual QxItem* getItemAt(const QPointF &point);

    /// Accesses the corresponding Qt function via the item's parent.
    virtual void setCursor(const QCursor &cursor);

    /// Move the item to the given point.
    virtual void moveTo(const QPointF &pos);
    /// Move the item to the given point.
    virtual void moveTo(qreal x, qreal y) {
        moveTo(QPointF(x, y));
    }
    /// Translate the item by the given offset.
    virtual void translate(const QPointF &offset);
    /// Translate the item by the given offset.
    virtual void translate(qreal x, qreal y) {
        translate(QPointF(x, y));
    }
    
    // Moving as selection
    /// Should be called before moving a selection. Updates the offset member of selection, 
    /// which is later on needed by moveTo.
    virtual void beginMoving(const QPointF &pos, Selection &selection);
    /// Moves the item to a new position.
    virtual void moveTo(const QPointF &pos, Selection &selection);
    /// Subclasses can use this method to perform actions after a move activity has finished.
    virtual void endMoving(const QPointF &pos, Selection &selection);
    
    // Snapping stuff    
    /// Returns the distance(s) between the passed position and snapping position(s) this item provides.
    virtual QList<QPointF> getSnapPosCandidateDists(const QPointF &pos, const Selection &selection);
    // Returns the closest snapping position.
    virtual QPointF getClosestSnapPos(const QPointF &pos) const;
    // Shows an item's snapping position if it is equal to the passed position (using an epsilon comparison).
    virtual void showSnapPos(const QPointF &pos);
    // Hide all snapping positions of this item.
    virtual void hideSnapPos();

    // Selection stuff
    /// Depending on the passed position this method creates a selection or return an empty list.
    virtual QList<Selection> createSelections(const QPointF &pos);
    /// Depending on the passed rectangle this method creates a selection or return an empty list.
    virtual QList<Selection> createSelections(const QRectF &selectionArea);
    /// Subclasses should tests whether the passed point is inside the passed selection.
    /// This method only returns false.
    virtual bool inSelection(const QPointF &pos, const Selection &selection) const;
    /// Visualizes the item (or the selected part) as selected.
    virtual void showSelection(const Selection &selection);
    /// Hides any selection.
    virtual void hideSelection(const Selection &selection);
    
    // communication with DemoMaker
    /// Passes a command string to the item's parent.
    virtual const char* sendCmd(const QString &command, bool setDirtyFlag) const;
    /// Creates a command string containing information about the item's position (and size if necessary).
    virtual QString createPositionCmd() const;
    
    // mouse events
    virtual void mousePressEvent(QMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent); 
    virtual void mouseReleaseEvent(QMouseEvent *mouseEvent);
    virtual void leaveEvent(QMouseEvent *mouseEvent);

    /// Methods should call this method every time the item's geometry has changed. Changes will be propagated to the parent item.
    virtual void geometryChanged();
    /// Force the item to recalculate its geometry.
    virtual void recalcGeometry();
    /// Rearrange the item's content.
    virtual void arrange();
    /// Recalculate height of this item.
    virtual void reheight();

protected:
    /// Recalculates the bounding box. This method is called from geometryChanged().
    virtual void updateBoundingBox();

    // coordinate transformation
    QRectF mapLToD(const QRectF &rect) const;
    QPointF mapLToD(const QPointF &point) const;
    qreal mapLToDX(qreal value) const;
    qreal mapLToDY(qreal value) const;
    QPointF scaleLToD(const QPointF &point) const;
    qreal scaleLToDX(qreal value) const;
    qreal scaleLToDY(qreal value) const;
    QRectF mapDToL(const QRectF &rect) const;
    QPointF mapDToL(const QPointF &point) const;
    qreal mapDToLX(qreal value) const;
    qreal mapDToLY(qreal value) const;
    QPointF scaleDToL(const QPointF &point) const;
    qreal scaleDToLX(qreal value) const;
    qreal scaleDToLY(qreal value) const;
    bool equal(qreal v1, qreal v2, qreal epsilon=0.001) const;
    qreal squareDist(const QPointF &p1, const QPointF &p2) const;

    QString numberToString(int number)const;
    QString numberToString(qreal number, qreal epsilon=0.01)const;

    enum DrawMode {Normal, Selected, Disabled};

    // Variables
    QRectF mBoundingRect; ///< Bounding box of this item.
    QxItem* mParent;      ///< The item's parent.
    int mIdentifier;      ///< Unique numeric identifier used for communication with the DemoMaker.
    QString mLabel;       ///< Label.
    bool mEnabled;        ///< Is this item enabled (for future use).
    DrawMode mDrawMode;   ///< Visualize the item either normal or selected.
    bool mFloating;       ///< Floating items are ignored by the GroupItem's arrange and bounding box methods.
    Transform *mTrans;  ///< Pointer to a global Transform object .
    QPen mPenSnapLine;    ///< Pen for drawing snap lines.

    // Selection modes
    static const int WholeItemSelected = 1;

    // GUI representation
    static const int cHeight = 20;          ///< Height of an item.
    static const int cSnapDistance = 10;    ///< Range in which the item snaps to the next snapping position.
    static const int cSelectPartRegion = 10; ///< Range in which only the affected part of an item is selected.
    static const int cSnapLineExtend = 10;  ///< Overlap for showing snapping lines.
};

} // namespace

#endif // QXITEM_H

/// @}
