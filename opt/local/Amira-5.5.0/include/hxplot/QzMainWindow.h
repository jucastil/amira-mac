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

/// @addtogroup hxplot hxplot
/// @{
#ifndef QZ_MAINWINDOW
#define QZ_MAINWINDOW

#include <QMainWindow>

class QMenu;
class QzObjectEditor;
class QzMainWindow;
class QToolButton;
class QShowEvent;
class QHideEvent;

typedef void QzMenuCB(int itemNo, const QzMainWindow &mwin, void* userdata);
typedef void QzDestroyCB(const QzMainWindow &mwin, void* userdata);

/**
   Class for the main window of the plotting tool
@author Olaf Paetsch
*/
class QzMainWindow: public QMainWindow {

    Q_OBJECT

private:

    QzMenuCB      *menuCallback;
    void          *menuUserdata;
    QzDestroyCB   *destroyCallback;
    void          *destroyUserdata;

    QMenuBar*     theMenu;
    QStatusBar*   theStatus;
    QToolBar*     theToolbar;
    QMenu*        fileMenu;
    QMenu*        plotMenu;
    QMenu*        editMenu;
    QMenu*        confMenu;

    QAction*      editToolbutton;
    QAction*      snapshotToolbutton;
    QAction*      printToolbutton;
    QAction*      saveToolbutton;

    QAction*      polyinToolbutton;
    QAction*      lassoinToolbutton;
    QAction*      rectinToolbutton;
    QAction*      circleinToolbutton;
 
    QAction*      drawPolygonAction;
    QAction*      drawLassoAction;
    QAction*      drawRectangleAction;

    int           decoHeight;

protected slots:

    void menuCB(QAction*);

    void editPressed();

    void snapPressed();

    void printPressed();

    void savePressed();

    void lassoinPressed();

    void polygonPressed();

    void rectanglePressed();

    void circlePressed();

    void showConfMenu();

protected:

    ///
    virtual void hideEvent(QHideEvent* event);

    ///
    virtual void showEvent(QShowEvent* event);

public:

    /// Menu items of the main window
    enum QzMainMenuItems { QzLOADDATA   = 0,
                           QzSAVEDATA   = 1,
                           QzSAVESTATE  = 2,
                           QzSNAPSHOT   = 3,
                           QzPRINT2PS   = 4,
                           QzIMPORTDATA = 5,
                           QzQUIT       = 9,
                           QzEDIT       = 10,
                           QzPLOTALL    = 11,
                           QzREMOVEALL  = 12,
                           QzPROPEDIT   = 13,
                           QzCREATEPOLY = 14,
                           QzLASSO      = 15,
                           QzCREATERECT = 16,
                           QzCREATECIRC = 17,
                           QzCONFIG     = 20 };

    /// Constructor
    QzMainWindow(const char* name, int width = 512, int height = 512);

    /// Destructor
    ~QzMainWindow();

    /// displays a message on the status bar
    void setStatus(const char *statusMsg, int milliSec = -1);

    ///
    void setMenuNotifier(QzMenuCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetMenuNotifier() { menuCallback = NULL; }

    ///
    void setDestroyNotifier(QzDestroyCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetDestroyNotifier() { destroyCallback = NULL; }

    /// hides the status bar
    void hideStatus();

    /// shows the status bar
    void showStatus();

    /// hides the menu bar
    void hideMenu();

    /// shows the menu bar
    void showMenu();

    /// shows the menu items which deal with input
    void showInputMenuItems();

    /// hides the menu items which deal with input
    void hideInputMenuItems();

    /// adds an item to the config menu
    void addConfigItem(char* string, int id);

    /// returns the height of the menu and the status bar
    int getDecorationHeight();
};

#endif

/// @}
