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
#ifndef SURF_EDIT_TOOL_H
#define SURF_EDIT_TOOL_H

#include <QObject>
#include <QPixmap>
#include <mclib/McString.h>
#include <mclib/McHandable.h>
#include "HxSurfEdit.h"
#include "Undoable.h"

#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/details/SoFaceDetail.h>
#include <Inventor/SoPickedPoint.h>

class QToolButton;

/// Base class for tools providing a dialog window
class SurfEditTool : public QObject {

  Q_OBJECT

  public:
    /// Constructor.
    SurfEditTool(HxSurfEdit* surfEdit);

    /// Destructor.
    ~SurfEditTool();

    /** This is called when the tool is selected. A tool can either be
        selected from the tools menu or by pressing the corresponding
        tool button. The @c fromMenu argument indicates in which way
        selection took place. This allows tools which provide both a
        menu entry and a tool bar to pop up a config dialog when they
        were selected using the menu entry. */
    virtual void activate(int fromMenu);

    virtual void deactivate(){}

    /** This is called after the surface has been modified by some other
        tool. Mouse tools may check the surface's edge array or the
        triangles per point. Tools displaying a dialog window usually
        won't do anything unless the dialog window is open. */
    virtual void surfaceChanged();

    /** This is called after the selection or highlight buffer has been
        modified. Dialog tools may update an info label indicating the
        number of highlighted triangles. */
    virtual void selectionChanged();

    /** */
    virtual bool isExclusive(){ return false; }

    QAction* getToolAction(){ return toolAction; }
  protected:
    /// Pointer to surface editor, will be set in constructor.
    HxSurfEdit* surfEdit;

    /// Pointer to Inventor node, set before tool is activated.
    SoTriSurface* soTriSurface;

    /// If label is non-zero the tool is listed in the tools menu.
    const char* label;

    /// If xpm is non-zero a button in the tools menu is created.
    QPixmap xpm;

    /// special button (with a small black triangle in right lower corner) for pulldown menus
    QPixmap xpm_pulldown;

    /// The tooltip message to be displayed for the tool button.
    const char* toolTip;

    /// 

    /// Provides easy access to the surface being edited.
    HxSurface* getSurface() const { return (HxSurface*) surfEdit->getData(); }

    /// Convenience method for highlighting triangles.
    void highlightTriangle(int which, int state) {
        soTriSurface->highlightTriangle(which, state); }

  private:

  /// The tool button will be created by the surface editor.
  QAction* toolAction;

  friend class HxSurfEdit;
};

#endif

/// @}
