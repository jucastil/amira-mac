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
#ifndef QX_HISTORY_LINEEDIT_H
#define QX_HISTORY_LINEEDIT_H

#include <qlineedit.h>
#include <qstring.h>
//Added by qt3to4:
#include <QKeyEvent>

#include <mclib/McDArray.h>

#include "HxMoleculeWinDLLApi.h"

class QKeyEvent;

/** This class implements a lineedit widget with history. New items
    are added to the history by pressing the RETURN
    button. Furthermore, items can be added by using the function
    @c addToHistory. On default, the size of the history is restricted
    to 100 items. However, you can change the limit with the function
    @c setHistoryLimit. You can step through the history with the UP
    and DOWN keys. */

class HXMOLECULE_API QxHistoryLineEdit: public QLineEdit
{
    Q_OBJECT

protected:              
    // Maximum size of history.
    int historyLimit;
    // Where in the history are we currently.
    int curHistItem;
    // History array.
    McDArray<QString> history;

public:
    /// Constructor.
    QxHistoryLineEdit(QWidget * parent, const char * name=0);
    /// Constructor.
    QxHistoryLineEdit(const QString & string, QWidget * parent, const char * name=0);
    /// Destructor.
    ~QxHistoryLineEdit();

    /// Add a new string to the history.
    void addToHistory(const QString & string);
    /// Set new history limit. If the list has to be shortened, items at
    /// the beginning of the list will be removed.
    void setHistoryLimit(int limit);

signals:
    void keyEvent(int key);         

protected:
    // Overloaded function to catch UP and DOWN key events.
    virtual void keyPressEvent(QKeyEvent * event);
};

#endif

/// @}
