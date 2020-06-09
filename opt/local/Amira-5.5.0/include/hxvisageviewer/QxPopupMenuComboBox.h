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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef  QX_POPUP_MENU_COMBO_BOX_H
#define  QX_POPUP_MENU_COMBO_BOX_H

#include <QLineEdit>
#include <QString>
#include <QMenu>
#include <QPushButton>

#include <mclib/McDArray.h>

////////////////////////////////////////////////////////////////////////////////
class QxPopupMenuLineEdit
:   public QLineEdit
{
    Q_OBJECT
    
public:

    QxPopupMenuLineEdit( QWidget * parent = 0 );
    ~QxPopupMenuLineEdit();

    // synced QxLineEdit widgets hover together on mouse enter / release events
    void syncWith(QxPopupMenuLineEdit*);
    //void unsyncWith(QxLineEdit*);
    

public slots:

    void acceptText();
//    void paletteChanged();


signals:

    void textAccepted(const QString&);


protected:

    virtual void highlight( bool inFlag = false );
    virtual bool event( QEvent * e ); // required to intercept tab press, those are not forwarded to keyPressEvent()
    virtual void mousePressEvent( QMouseEvent * e );
    virtual void enterEvent( QEvent * );
    virtual void leaveEvent( QEvent * );
    virtual void focusOutEvent( QFocusEvent * );


protected:

    McDArray<QxPopupMenuLineEdit*> mSync;
    bool                           mNoRecursiveFocusOut;
};


////////////////////////////////////////////////////////////////////////////////
class QxPopupMenuComboBox
:   public QxPopupMenuLineEdit
{
    Q_OBJECT
    
public:

    QxPopupMenuComboBox( QWidget * parent = 0, QMenu * menu = 0 );
    ~QxPopupMenuComboBox();

    QMenu * popupMenu() const;
    void setPopupMenu(QMenu*);

public slots:
    void emitPopupActivated(QAction* action);

    void popup();
    void unsetButton();

//    void paletteChanged();

signals:
    void popupAboutToShow();
    void popupActivated(QAction*);

protected:

    virtual void highlight( bool inFlag = false );
    virtual void mousePressEvent ( QMouseEvent * e );
    virtual void mouseReleaseEvent ( QMouseEvent * e );
    virtual void enterEvent ( QEvent * );
    virtual void leaveEvent ( QEvent * );
    virtual void resizeEvent( QResizeEvent * e );

protected:

    QMenu       * mMenu;
    QPushButton * mButton;
};


#endif // QX_POPUP_MENU_COMBO_BOX_H

/// @}
