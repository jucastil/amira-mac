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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef SURF_EDIT_MAGIC_WAND_H
#define SURF_EDIT_MAGIC_WAND_H

#include <QAction>

#include <hxsurfedit/SurfEditMouseTool.h>
#include <hxsurfedit/BufferUndo.h>
#include <QAction>
#include "SurfEditMouseTool.h"
#include "BufferUndo.h"

class QDialog;
class QLabel;
class QSlider;
class QMenu;

/// Tool for picking triangles.
class SurfEditMagicWand : public SurfEditMouseTool {

    Q_OBJECT

  public:
    /// Constructor.
    SurfEditMagicWand(HxSurfEdit* surfEdit);

    /// Destructor.
    ~SurfEditMagicWand();

    /// Checks if edgesPerPoint is ok.
    virtual void activate(int);

    /// Hides dialog if necessary.
    virtual void deactivate();

    /// Event handler.
    virtual void mouseClick(SoEventCallback *eventCB);

    bool getCurrentPatchFlag() const;

    bool getIncludeInvisibleFlag() const;

    float getCreaseAngleRadians() const;

protected:

  int creaseAngle;

  QDialog* dialog;
  QCheckBox* currentPatchToggle;
  QCheckBox* includeInvisibleToggle;
  QSlider* creaseAngleSlider;
  QLabel* creaseAngleLabel;

  void createDialog(QWidget* parent);

  /// popupmenu:
  QMenu* pmenu;
  QAction* item_patch_select;
  QAction* item_invisible_trngls;
  QSlider*  item_slider;
  QLabel* item_num;

  /// the implementation of undoable
  BufferUndo* bufferUndo;


protected slots:
  void close();
  ///konsistenz mit popupmenu
  void setOptionPatch(bool state){
    item_patch_select->setChecked( state );
  }
  void setOptionInvisible(bool state){
    item_invisible_trngls->setChecked( state );
  }
  void setNum(int num);

};

#endif

/// @}
