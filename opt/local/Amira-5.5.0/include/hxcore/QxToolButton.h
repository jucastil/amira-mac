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
#ifndef  QX_TOOLBUTTON_H
#define  QX_TOOLBUTTON_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <qtoolbutton.h>

class QMouseEvent;

/// Tool button which remembers the modifier state
/// This class also manages buttons which has defined a pressed pixmap stored 
/// QIconSet::On by switching from a normal pixmap to pressed pixmap when the button is
/// pressed.
class HXCORE_API QxToolButton : public QToolButton {

  Q_OBJECT

  public:
    /// Constructor.
    QxToolButton(QWidget* parent, const char *name=NULL);

    /// Destructor
    ~QxToolButton();

    /// Return modifier state at time of last mouse press.
    int state() const { return modifierState; }

    /// Activates the two-pixmap mode.
    void setPixmaps(const QPixmap& pixmap1, const QPixmap& pixmap2);
  protected:
    int modifierState;
    virtual void mousePressEvent(QMouseEvent* e);
};

#endif 

/// @}
