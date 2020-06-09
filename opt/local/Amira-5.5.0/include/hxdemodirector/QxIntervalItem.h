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
#ifndef QXINTERVALITEM_H
#define QXINTERVALITEM_H

#include "hxdemodirector/QxItem.h"

namespace hxdemodirector {

/**
  Base class for events describing a time interval.
*/
class QxIntervalItem : public QxItem
{
public:
    QxIntervalItem(qreal begin, qreal end);
    
    /// Paints the item as a rectangle with spikes at the left and right border.
    virtual void paint(QPainter &painter) const;

    void setTime(qreal begin, qreal end);
    /// Checks whether a point is inside the item's bounding box.
    virtual bool contains(const QPointF &point) const;
    
    // Moving via selections
    virtual void beginMoving(const QPointF &pos, Selection &selection);
    
    // Snapping stuff (see base class)
    virtual QList<QPointF> getSnapPosCandidateDists(const QPointF &pos, const Selection &selection);
    virtual QPointF getClosestSnapPos(const QPointF &pos) const;
    virtual void showSnapPos(const QPointF &pos);
    virtual void hideSnapPos();
    
    // Selection stuff
    /// Creates an selection depending on the passed point. Possible selection are the left/right
    /// border (for resizing) or the whole item (for moving).
    virtual QList<Selection> createSelections(const QPointF &pos);
    /// Creates an selection depending on the passed point. Possible selection are the left/right
    /// border (for resizing) or the whole item (for moving).
    virtual QList<Selection> createSelections(const QRectF &selectionArea);
    virtual bool inSelection(const QPointF &pos, const Selection &selection) const;
    virtual void showSelection(const Selection &selection);
    virtual void hideSelection(const Selection &selection);
    
    // Mouse events
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent); 
    virtual void leaveEvent(QMouseEvent *mouseEvent);

protected:
    enum DragMode {None, Move, ResizeLeft, ResizeRight};

    virtual void updateBoundingBox();
    virtual DragMode calcDragMode(const QPointF &pos) const;

    bool mShowSnapLineLeft;
    bool mShowSnapLineRight;

    DrawMode mDrawModeLeft;
    DrawMode mDrawModeRight;

    // selection constants
    static const int LeftEdgeSelected = 2;
    static const int RightEdgeSelected = 3; 
};

/**
 Represents a DemoDirector interval event. In addition to the base class it takes
 care that the value of the left edge is always smaller than the value of the right
 edge.
*/
class QxOrderedIntervalItem : public QxIntervalItem
{
public:
    QxOrderedIntervalItem(qreal begin, qreal end);
    // Moving via selections
    virtual void moveTo(const QPointF &pos, Selection &selection);
};

/**
 Represents a DemoDirector numeric event. In addition to the base class it stores
 a start value and an end value.
*/
class QxNumericItem : public QxOrderedIntervalItem
{
public:
    QxNumericItem(qreal begin, qreal end, qreal startValue, qreal endValue);

    void setStartEndValues(qreal startValue, qreal endValue);
    
    virtual QString getToolTip() const;
    virtual QString createPositionCmd() const;

protected:
    qreal mStartValue, mEndValue;
};

/**
 Represents a DemoDirector command event. In addition to the base class it stores
 lists of start values and end values.
*/
class QxCommandItem : public QxOrderedIntervalItem
{
public:
    QxCommandItem(qreal begin, qreal end, const QString &startValue, const QString &endValue);
    
    void setStartEndValues(const QString &startValue, const QString &endValue);
    
    virtual QString getToolTip() const;
    virtual QString createPositionCmd() const;

protected:
    QString mStartValue, mEndValue;
};

/**
 Represents a DemoDirector goto event.
*/
class QxGotoItem : public QxIntervalItem
{
public:
    QxGotoItem(qreal begin, qreal end);

    /// Paints the item as an arrow.
    virtual void paint(QPainter &painter) const;

    virtual QString getToolTip() const;

    virtual QString createPositionCmd() const;

      // Moving via selections
    virtual void moveTo(const QPointF &pos, Selection &selection);
};

} // namespace

#endif // QXINTERVALITEM_H

/// @}
