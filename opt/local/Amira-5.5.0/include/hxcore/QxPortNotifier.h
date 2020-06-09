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
#ifndef  QX_PORT_NOTIFIER_H
#define  QX_PORT_NOTIFIER_H

#include <QObject>
#include <QPoint>

/** This class provides several slots for Qt signals which have to be
    interpreted in classes of type HxPort. Since HxPort itself is not
    derived from QObject HxPort cannot have its own slots. Instead, every
    port owns a QxPortNotifier. The notifier's slots will call the virtual
    function @c guiCallback() of the port. Arguments are stored locally and
    can be accessed from @c guiCallback(). */

class HxPort;
class QAction;
class HxPreferences;
class QxPortNotifier : public QObject {
    
    Q_OBJECT

  public:
    /// Constructor.
    QxPortNotifier(HxPort* owner) { this->owner = owner; }

    /** Enum describing the different slot types. Compare the
        result of getSlot with one of these values in order
        to find out which slot actually invoked the gui callback. */
    enum SlotType {
        /// Stands for @c slot().
        SLOT_,
        /// Stands for <tt>slot(const char*)</tt>.
        SLOT_STR,
        /// Stands for @c slot(bool).
        SLOT_BOOL,
        /// Stands for @c slot(int).
        SLOT_INT,
        /// Stands for @c slot(float).
        SLOT_FLOAT,
        /// Stands for <tt>slot(bool, int)</tt>.
        SLOT_BOOL_INT,
        /// Stands for <tt>slot(int, int)</tt>.
        SLOT_INT_INT,
        /// Stands for <tt>slot(float, float)</tt>.
        SLOT_FLOAT_FLOAT,
        /// Stands for <tt>slot(QAction*)</tt>.
        SLOT_ACTION,
        /// Stands for <tt>slot(const QPoint &)</tt>.
        SLOT_QPOINT

    };
    
  public slots:
    /// Slot with no args.
    void slot();

    /// Sets @c arg1.str.
    void slot(const char* str);

    /// Sets @c arg1.b.
    void slot(bool b);

    /// Sets @c arg1.b and @c arg2.i.
    void slot(bool b, int i);

    /// Sets @c arg1.i.
    void slot(int i);

    /// Sets @c arg1.x.
    void slot(float x);

    /// Sets @c arg1.i and @c arg2.i.
    void slot(int x, int y);

    /// Sets @c arg1.x and @c arg2.x.
    void slot(float min, float max);

    /// Sets @c arg1.action.
    void slot(QAction*);

    /// Sets @c arg1.qpoint.
    void slot(const QPoint &);

    // Special-purpose slot used by the port's pin button.
    void pinToggled(bool b);

    /**
     *  To be notified that preferences changed.  The signal will not be delivered
     *  to the generic callback, but directly to HxPort::preferencesChanged().
     */
    void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

  signals:
    void toBeDeleted(bool ownerToo);

    void valueChanged();

    void valueChanged(unsigned int mask);

  public:
    /// Allows you to find out who emitted the signal.
    const QObject* sender() { return QObject::sender(); }

    /// Allows you to find out which slot was used last.
    int getSlot() { return lastSlot; }

    /**
     * To get the owner port.
     */
    HxPort * getOwner() const;

    /// Union type for representing slot arguments.
    union Arg {
        /// Integer value.
        int i;
        /// Boolean value.
        bool b;
        /// Floating point value.
        float x;
        /// Character string.
        char* str;
        /// Void pointer.
        void* ptr;
        /// QAction pointer
        QAction* action;
        /// QPoint Pointer
        const QPoint * qpoint;
    };

    /// Stores the first argument of a slot.
    Arg arg1;

    /// Stores the second argument of a slot.
    Arg arg2;
        
  protected:
    HxPort* owner;
    int lastSlot;

  friend class HxPort;
  friend class HxObject;
};


// INLINE methods.
inline HxPort*
QxPortNotifier::getOwner() const
{
    return owner;
}


#endif


/// @}
