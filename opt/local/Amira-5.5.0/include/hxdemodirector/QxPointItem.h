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
#ifndef QXPOINTITEM_H
#define QXPOINTITEM_H

#include "hxdemodirector/QxItem.h"

namespace hxdemodirector {

/**
 Base class for all events corresponding to a point in time.
*/
class QxPointItem : public QxItem
{
public:
    QxPointItem(qreal pos);
    
    void setPoint(qreal point);
    virtual QPointF getPosition() const;

    virtual void moveTo(const QPointF &pos);
    virtual void translate(const QPointF &offset);
    
    // Moving via selections
    virtual void beginMoving(const QPointF &pos, Selection &selection);
    virtual void moveTo(const QPointF &pos, Selection &selection);
    
    // Snapping stuff  (see base class)
    virtual QList<QPointF> getSnapPosCandidateDists(const QPointF &pos, const Selection &selection);
    QPointF getClosestSnapPos(const QPointF &pos) const;
    virtual void showSnapPos(const QPointF &pos);
    virtual void hideSnapPos();
    
    // Selection stuff
    /// Creates an selection which consists of the whole item or is empty.
    virtual QList<Selection> createSelections(const QPointF &pos);
    /// Creates an selection which consists of the whole item or is empty.
    virtual QList<Selection> createSelections(const QRectF &selectionArea);
    virtual bool inSelection(const QPointF &pos, const Selection &selection) const;

protected:
    
    QPointF mPos;
    bool mShowSnapLine;
};

/**
 Base class for events corresponding to a point in time which are visualized
 as a rectangle.
*/
class QxRectanglePointItem : public QxPointItem
{
public:
    QxRectanglePointItem(qreal point);
    
    /// Paints the item as a rectangle with a spike in the middle.
    virtual void paint(QPainter &painter) const;

protected:
    virtual void updateBoundingBox();
  
    static const int mItemWidth = 60;
};

/**
 Represents a DemoDirector toggle event. In addition to the base class it stores
 the toggle value.
*/
class QxToggleItem : public QxRectanglePointItem
{
public:
    QxToggleItem(qreal point, bool toggleTo);

    void setToggleTo(bool toggleTo);

    virtual QString getToolTip() const;

    virtual QString createPositionCmd() const;

protected:
    bool mToggleTo;
};

/**
 Represents a DemoDirector select event. In addition to the base class it stores
 the old and new value.
*/
class QxSelectItem : public QxRectanglePointItem
{
public:
    QxSelectItem(qreal point, int newValue, int oldValue);

    void setNewOldValues(int newValue, int oldValue);

    virtual QString getToolTip() const;

    virtual QString createPositionCmd() const;

protected:
    int mOldValue;
    int mNewValue;
};

/**
 Represents a DemoDirector button event. In addition to the base class it stores
 the modifer values.
*/
class QxButtonItem : public QxRectanglePointItem
{
public:
    QxButtonItem(qreal point, bool shiftPressed, bool ctrlPressed, bool altPressed);

    void setModifierStates(bool shiftPressed, bool ctrlPressed, bool altPressed);

    virtual QString getToolTip() const;

    virtual QString createPositionCmd() const;

protected:
    bool mShiftPressed;
    bool mCtrlPressed;
    bool mAltPressed;
};

/**
 Base class for events corresponding to a point in time which are visualized
 as a vertical line.
*/
class QxVerticalLineItem : public QxPointItem
{
public:
    QxVerticalLineItem(qreal point);

    virtual bool contains(const QPointF &point) const;

    virtual QList<Selection> createSelections(const QPointF &pos);

    virtual bool inSelection(const QPointF &pos, const Selection &selection) const;

protected:
    virtual void updateBoundingBox();
    static const int mItemWidth = 6;
};

/**
 Represents a DemoDirector break event.
*/
class QxBreakItem : public QxVerticalLineItem
{
public:
    QxBreakItem(qreal point);

    /// Paints the event as vertical line with a pause symbol at its lower end. 
    virtual void paint(QPainter &painter) const;

    virtual QString getToolTip() const;

    virtual QString createPositionCmd() const;

protected:
};

/**
 Represents a DemoDirector pause event.
*/
class QxPauseItem : public QxVerticalLineItem
{
public:
    QxPauseItem(qreal point, qreal waitingTime);

    /// Paints the event as vertical line with a clock symbol at its lower end.
    virtual void paint(QPainter &painter) const;

    void setWaitingTime(qreal waitingTime);

    virtual QString getToolTip() const;

    virtual QString createPositionCmd() const;

protected:
    qreal mWaitingTime;
};

/**
 Represent the left/right boundary or the current time.
*/
class QxTimelineControlItem : public QxVerticalLineItem
{
public:
    enum Type {LeftBoundary, RightBoundary, CurTime};

    QxTimelineControlItem(qreal point, Type type);

    /// Paints the event as vertical line with an arrow depiciting the actual event type.
    virtual void paint(QPainter &painter) const;

    virtual QString getToolTip() const;

    virtual QString createPositionCmd() const;
protected:
    Type mType;
};

} // namespace

#endif //QXPOINTITEM_H

/// @}
