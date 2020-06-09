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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GiQTISSUELISTITEM_H
#define GiQTISSUELISTITEM_H

#include <QTableWidget>
#include <qframe.h>
#include <qtoolbutton.h>
#include <QCheckBox>
#include <QIcon>

class HxParamBundle;
class GiQTissueList;


/// Qt version of toolbox
class GiQTissueListItem : public QObject
{
    Q_OBJECT

public:
    GiQTissueListItem(GiQTissueList* tl, HxParamBundle* mat, int row);
    
    void setColor(QColor& c);
    
    void setName(const char* c);

    // Updates the state of the 3D check box without triggering any action.
    void setShow3D(bool value);

    // Updates the state of the 3D color check box without triggering any action.
    void setColor3D(bool value);

    const QString getName() const{ return textLabel->text(); }
    
    const QColor& getColor() {return colorFrame->palette().background().color();}

    void setLock(bool l);

    void setDrawStyle2D(unsigned int style);

    bool isColor3DButtonChecked();

public slots:
    void setShow2D(bool state);
    void selectMaterial();

private slots:
    // Called when the 3D check box is toggled, shows or hides a label in 3D.
    void slotShow3D(bool value);

    // Called when the "Show Color" check box is toggled.
    void slotShowColor(bool state);

private:

    static const QIcon& getLockIcon();
    static const QIcon& getUnlockIcon();

    GiQTissueList* tissuelist;

    QFrame      * colorFrame;
    QTableWidgetItem  * textLabel;
    QTableWidgetItem  * lockPixmap;
    QToolButton * selectButton;

    QCheckBox* show2D;
    QCheckBox* show3D;
    QCheckBox* showColor;

    static QIcon iconLock;
    static QIcon iconUnlock;
};

#endif

/// @}
