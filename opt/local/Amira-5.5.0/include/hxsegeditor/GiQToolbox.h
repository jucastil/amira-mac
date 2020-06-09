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
#ifndef GiQToolbox_H
#define GiQToolbox_H

#include <QMenu>
#include <QLabel>
#include <QPixmap>
#include <QWidget>

#include <hxsegeditor/ui_GiToolboxBase.h>

class GiQ;
class QToolButton;
class QPixmap;
class QCheckBox;
class QFrame;
class QLabel;
class QToolBar;
class QStackedLayout;
class GiQTissueList;
class HxParamBundle;
class HxGiEditor;
class McVec3i;
class McVec3f;

// Qt version of toolbox
class GiQToolbox : public QWidget, public Ui_GiToolboxBase
{
    Q_OBJECT

  public:

    GiQToolbox(GiQ* gi, QWidget * parent = 0);
    ~GiQToolbox();
    
    void setTissues(HxParamBundle*);

    void allZoom(bool isOn);
    bool zoomAll();

    void set3D(bool);
    bool selectionIs3D();

    void redraw();

    void updateInfo();
    void updateInfo(McVec3i& posi, McVec3f& posf, const char* mat);
    void updateInfo(McVec3i& posi, McVec3f& posf, float grey, const char* mat);

    virtual bool eventFilter ( QObject * watched, QEvent * event );

    GiQ* getGi() { return gi; }

    void activateGUI(bool value);

  protected:
    GiQ* gi;
    QToolBar* wToolBar;
    QStackedLayout* wToolStackedLayout;
    QMenu* w2DColormapMenu;
    QMenu* w3DColormapMenu;
    bool addSelectionShiftPressed;

  public slots:
    void setTool(int);
    void toggle3dChanged(bool);
    void toggleZoomChanged(bool);
    void clearSelection();
    void replaceBySelection();
    void addSelection();
    void subtractSelection();
    void handleSelectionChange();
    void handleHiddenSelection(int);
    void handleAlertMode3D(bool);
    void growSelection();
    void shrinkSelection();
    void crossHair();
    void zoomIn();
    void zoomOut();

  protected slots:
    void configure2DColormapMenu();
    void configure3DColormapMenu();
    void setColormap(QAction* action);
    void setActiveTool(QAction* action);
};

#endif

/// @}
