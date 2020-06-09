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
#ifndef  _HX_QT_STOPBUTTON_H
#define  _HX_QT_STOPBUTTON_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <QPushButton>

class QEvent;
class QPixmap;

/** This class is a pushbutton, that blocks all events when activated.
*/
    
class HXCORE_API QxStopButton : public QPushButton {

    Q_OBJECT

public:
    QxStopButton(QWidget* parent = NULL, const char* name=NULL);
    ~QxStopButton();

    int wasPressed() const { return stopFlag; }
    int isInterruptable() const { return interruptable; }
    void setStopFlag(unsigned int s) { stopFlag = s; }

    void busy(bool interruptable);
    void notBusy();
    
    void setEventFilter();
    void unsetEventFilter();

    void setClone(QAbstractButton* button);
    QAbstractButton* getClone();

public slots:
    void setEnabled(bool enabled);
    void setBusyCursor();
    void unsetBusyCursor();
signals:
    void setEnabledSig(bool enabled);
    void setBusyCursorSig();
    void unsetBusyCursorSig();
    void setEventFilterSig();
    void unsetEventFilterSig();
protected slots:
    void originalClicked();
    void setEnabledSlot(bool enabled);
    void setBusyCursorSlot();
    void unsetBusyCursorSlot();
    void setEventFilterSlot();
    void unsetEventFilterSlot();
protected:
    unsigned int stopFlag:1;
    unsigned int buttonActive:1;
    unsigned int interruptable:1;
    unsigned int busyCursor:1;
    unsigned int eventFilterSet:1;

    QAbstractButton* mClone;

    bool eventFilter(QObject*, QEvent*);
    virtual void enterEvent(QEvent*);
    virtual void leaveEvent(QEvent*);
};

#endif 

/// @}
