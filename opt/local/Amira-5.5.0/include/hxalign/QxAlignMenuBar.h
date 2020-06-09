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

/// @addtogroup hxalign hxalign
/// @{
#ifndef QX_ALIGN_MENU_BAR_H
#define QX_ALIGN_MENU_BAR_H

#include <QMenuBar>
#include <QVector> 
#include <hxalign/QxAutoAlignToolBar.h>

class QxAlignSlices;
class QMenu;
class QAction;

class QxAlignMenuBar : public QObject
{
  Q_OBJECT

  public:
    QxAlignMenuBar(QxAlignSlices *parent = 0, const char *name = 0);
    ~QxAlignMenuBar();

    void addMenu();
    void removeMenu();
    void disableTransformAll();
    void enableTransformAll();
    void disableFixReference();
    void enableFixReference();
    
  public slots:
    void zoomIn();
    void zoomOut();

    void cancel();

    void resetAll();
    void reset();

    void redGreen();
    void chess();
    void avg();
    void invert();
    
    /** Called when "Transform parameters" in the view menu has been clicked. Emits
     *  a signal that the transform parameter toolbar should be shown/hidden. */
    void transformParametersToolBar();

    void transformAll();
    void fixReference();

    void read();
    void save();

    void undo();
    void redo();

    void undoEmpty();
    void undoNotEmpty();
    void redoEmpty();
    void redoNotEmpty();

    void centers();
    void gray();
    void landmarks();
    void edgeDetection();
    void changeMode(int);

    void doIt();
    void doAll();

    void addLandmark();
    void removeLandmark();

    void showParameters(){emit showParametersSignal();}

    void menuUsersguide();
    void enableLandmarkAdd(bool);
    void enableLandmarkRemove(bool);

    void sagittal();
    void coronal();

    void viewMenuConfig();
    void showExtraViewer();
  signals:
    void zoomInSignal();
    void zoomOutSignal();

    void cancelSignal();

    void resetAllSignal();
    void resetSignal();

    void redGreenSignal();
    void chessSignal();
    void avgSignal();
    void invertSignal();

    void transformToolBarSignal(bool);

    void coronalSignal(bool);
    void sagittalSignal(bool);

    void transformAllSignal();
    void fixReferenceSignal();

    void readSignal();
    void saveSignal();

    void undoSignal();
    void redoSignal();

    void alignModeChanged(int);

    void showParametersSignal();

    void doItSignal();
    void doAllSignal();

    void addLandmarkSignal();
    void removeLandmarkSignal();

    void showViews();


  protected:
     QMenu *optionsMenu;
     QMenu *viewMenu;
     QMenu *alignMenu;
     QMenu *landmarksMenu;
     QMenu *landmarksEditMenu;

     QxAlignSlices* alignView;

     QAction *transformAllID, *fixReferenceID;
     QAction *redGreenID, *chessID, *avgID, *invertID;
     QAction *transformParamID;
     QAction *parametersID;
     QAction *undoID, *redoID;
     QAction *centersID, *grayID, *landmarksID, *edgeDetectionID;
     QAction *landmarkAddID, *landmarkRemoveID;
     QAction *sagittalID, *coronalID;
     QAction *extraViewerID;

     QVector<QAction*> menuId;
};

#endif

/// @}
