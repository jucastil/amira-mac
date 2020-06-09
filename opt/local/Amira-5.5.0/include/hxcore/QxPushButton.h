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
#ifndef  QX_PUSHBUTTON_H
#define  QX_PUSHBUTTON_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <QPushButton>

class QPixmap;
class QPainter;

/** More sophisticated push button class. The following features are added
    to the standard QPushButton widget:
    
    @li Two new signals toggled and clicked, which are
          essentially the same as the original ones, but they pass an
          additional id.  This is useful if a list of buttons is connected
          to the same slot. The id can be used to find out easily which
          button was hit.
    
    @li Two new modes of appearance are implemented which are useful for
          toggle buttons. The button optionally can be given two pixmaps.
          The second one is drawn if the button is on. The button does not
          draw it's frame in the two pixmap mode. If a frame is desired,
          use @c setDrawFrame(true).
    
*/
    
class HXCORE_API QxPushButton : public QPushButton {

    Q_OBJECT

  public:
    /// Default constructor.
    QxPushButton(QWidget* parent=NULL, const char *bname=NULL, int id=0);

    /// This constructor directly sets the button text.
    QxPushButton(QString text, QWidget* parent=NULL, int id=0);

    /// Destructor..
    ~QxPushButton();

    /// Activates the two-pixmap mode.
    void setPixmaps(const QPixmap& pixmap1, const QPixmap& pixmap2);

    /// Specifies that a frame should be drawn in two-pixmap mode.
    void setDrawFrame(bool value);

    /// Specify if a snap toggle should be drawn or not.
    void setDrawSnap(bool value);

    /// Set or unset the snap toggle.
    void snap(bool value);

    /// Check whether snap toggle is set.
    bool isSnapped() const { return snapFlag; }

    /// Return modifier state at time of last mouse press.
    int state() const { return modifierState; }

    /// Returns the id of the button.
    int getId() const { return id; }

  signals:
    /// This signal is emitted when button is toggled.
    void toggled(bool, int id);

    /// This signal is emitted when button is clicked.
    void clicked(int id);

  protected slots:
    void originalToggled(bool);
    void originalClicked();

  protected:
    int id;
    int modifierState;
    unsigned int doDrawFrame:1;
    unsigned int doDrawSnap:1;
    unsigned int snapFlag:1;
    unsigned int snapDown:1;
    
    void init();

    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);

    bool hitIcon( const QPoint & pos ) const;

};

#endif 

/// @}
