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
#ifndef QX_PROGRESSBAR_H
#define QX_PROGRESSBAR_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <QProgressBar>
#include <QString>
#include <QTime>

class HXCORE_API QxProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    QxProgressBar(QWidget* parent=0);

    virtual QString text () const{ return text_str; }

    void setText(const QString& text);

    void setProgress( int progress );
    
    int progress() const{ return value(); }

    void setTotalSteps( int totalSteps );
    int totalSteps() const{ return maximum() - minimum(); }

public slots:
    void reset();
    void update();
    void setRange(int min, int max);
    void setValue(int value);
signals:
    void resetSig();
    void updateSig();
    void setRangeSig(int min, int max);
    void setValueSig(int value);
protected slots:
    void resetSlot();
    void updateSlot();
    void setRangeSlot(int min, int max);
    void setValueSlot(int value);
private:
    QString text_str;

    // Qt4 change (sn) disable copy construction because it is blocked in Q3Progressbar

    QxProgressBar(QxProgressBar const&);
    QxProgressBar& operator=(QxProgressBar const&);

    /// Records the last time the GUI element was updated.
    QTime m_lastGuiUpdate;
};

#endif

/// @}
