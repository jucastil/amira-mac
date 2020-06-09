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
#ifndef QX_ALIGN_SLICES_H
#define QX_ALIGN_SLICES_H

#include <QMainWindow>
#include <hxalign/SliceInfo.h>
#include <mclib/McListStack.h>
#include <mclib/McHandle.h>
#include "QxOrthoViewManager.h"

class HxAlignSlices;
class QKeyEvent;
class QxDrawAlignSlices;
class QxAlignToolBar;
class QxAutoAlignToolBar;
class QxAlignMenuBar;
class QxAlignTransformToolBar;
class QxAlignSlicesOptionsDialog;
class QxAlignUndoRedo;
class McVec2f;


class resizeInfo {
    public:
        resizeInfo(float sX, float sY,bool col, int oX=-1,int oY=-1):
            scaleX(sX), scaleY(sY), offsetX(oX), offsetY(oY), color(col) {}
        ~resizeInfo(){}

        float scaleX, scaleY;
        int offsetX, offsetY;
        bool color;
};


/** \class QxAlignSlices  QxAlignSlices.h <hxalign/QxAlignSlices.h>
 *  \brief This module provides the user interface for the alignSlices module
 *
 *  This module provides the user interface for the alignSlices module
 */


class QxAlignSlices : public QMainWindow
{
  Q_OBJECT

  public:
    /** Constructor */
    QxAlignSlices(HxAlignSlices* alignSlices);

    /**Destructor */
    ~QxAlignSlices();


    void changeViewMode(int mode);

    /** Set editMode to mode. Can be landmarks or manual. */
    void changeEditMode(int mode);


    /** Gets the drawArea */
    QxDrawAlignSlices* getDrawArea() {
        return drawArea;
    }

    /** gets the auto tool bar */
    QxAutoAlignToolBar* getAutoToolBar(){
        return autoToolBar;
    }

    /** gets the main menu */
    QxAlignMenuBar* getMainMenu(){
        return mainMenu;
    }

    /** gets the alignManager */
    HxAlignSlices* getAlignManager(){
        return alignManager;
    }


    /** returns the Undo object */
    QxAlignUndoRedo* getUndo(){
        return undo;
    }

    /**
        \brief Refreshes the displayed slices in the alignEditor.
        
        updateViews hands the displayable sliceinfo over to the current drawroutine (QxDrawAlignSlices::paintSlice()).
        The data of the displayed slices are stored in the HxAlignSlices::computedEditableSlicePtr. So it is very important to refresh 
        the views to call HxAlignSlices::setRange to update the data before calling updateViews.
    */ 
    void updateViews();

    /** activates the drawroutine from QxDrawAlignSlices. */
    void draw();

    /** Reinitializes the AlignViewer. This method is called from the alignManager in those cases, when the compute module
        is attached to a new data-module and the alignViewer is active. */
    void reInit();

    int getDrawAreaWidth();
    int getDrawAreaHeight();

    int getAlignMode() {return alignMode;}

    McDArray<SliceInfo>& getTransform();

    QList<QToolBar*> getVisibleToolbar( );

    /** 
     * Accessor to the orthoViewManager member.
     */
    const QxOrthoViewManager* getOrthoViewManager() const;

public slots:
  
    void reset();
    void resetAll();
    void transformAll();
    void fixReference();
    void read();
    void save();
    void apply();
    bool cancel();
    void changeAlignMode(int);
    void showParameters();
    void doAutoAlign();
    void doAllAutoAlign();
    void sliceChange(float);
    void setActive(bool visible);
    void addPoint(QPoint);
    void removePoint(int);
    void movePoints(QPoint, int);
    void setEditableSlice(int);
    void setEditMode(int);
    void mirror();
    //void map(int slice, const McVec2f&);
    void chess();
    /** Show or hide the transformation parameter toolbar */
    void showTransformToolBar(bool);
    /** Show or hide the coronal (orthogonal) view */
    void showCoronalView(bool);
    /** Show or hide the sagittal (orthogonal) view */
    void showSagittalView(bool);

    /** Zoom both orthoviews by one step */
    void orthoViewZoomIn();
    void orthoViewZoomOut();

    /** Zoom the main panel */
    void viewZoomIn();
    void viewZoomOut();


    /** Set/get orthoview slice number */
    void setSagittalViewSliceNumber (int);
    int  getSagittalViewSliceNumber ();
    void setCoronalViewSliceNumber (int);
    int  getCoronalViewSliceNumber ();

    void setOrthoViewLineWidth(const int value);

    void setUseMaxIntProjection (bool val);

    int getEditMode() {return editMode;}


    /** Starts the resize-dialog (alignResize) */
    //void showResize();

    /** Set translation in x to t, called from transformToolBar */
    void toolBarTranslateX(int t);
    /** Set translation in y to t, called from transformToolBar */
    void toolBarTranslateY(int t);
    /** Set rotation to r, called from transformToolBar */
    void toolBarRotate(float r);
    /** Set flipping to b, called from transformToolBar */
    void toolBarFlip(bool b);

    void translate(float,float,bool);
    void rotate(float, bool);

    void calcNewImageSize(bool autoSize, bool showBorder);
    void showBorder(bool autoSize, bool showBorder, int newx, int newy);
    void changeBorderSize(int newx, int newy);

  signals:
    void chessSignal(int);

  protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void updateToolbar();
    void updateOrthoViews(int tx, int ty, bool trans, bool rot, bool mirror, bool all);


    /** The Buttons of the autoToolBar (upper/lower Slice) are disabled. This is important for the "fix reference"  */
    void disableButtons();

    /** The Buttons of the autoToolBar (upper/lower Slice) are enabled. */
    void enableButtons();

    /** Check position of slice slider and according to that value set Transformation upper/lower slice buttons on/off */
    void updateTransformLowerUpperSliceInfo(int s);

    /** get the coloured slices */
    //void getColorSlices(const unsigned char*& ptr1, const unsigned char*& ptr2);


    /** The following members are the single Objects which interact with the alignView. The alignView controls
     the communication between these modules */

    /** The alignManager: this is the "main class" which means the controlling instance of the SliceAlign Modul */
    HxAlignSlices* alignManager;

    /** This is the object which controls the Undo functionality */
    QxAlignUndoRedo* undo;


    /** The mainMenu: the pull-down Windows in the AlignEditor */
    QxAlignMenuBar* mainMenu;

    /** The drawarea is the object which displays the slices */
    QxDrawAlignSlices* drawArea;

    /** The ToolBar: here are the leftmosts objects from the sliceSlider to the resize-icon */
    QxAlignToolBar* toolBar;

    /** The autoToolBar: here are the rightmost objects of the toolbar. Thes are all icons from the
     *  alignmentmethod-selection to the align-all Button */
    QxAutoAlignToolBar* autoToolBar;

    /** Preferences dialog  */
    QxAlignSlicesOptionsDialog* optionsDialog;


    /** Toolbar containing spinboxes to indicate and change the current transformation parameters. */
    QxAlignTransformToolBar* transformToolBar;


    McHandle<QxOrthoViewManager> orthoViewManager;

    /** Edit mode, either HX_POINTS or EDIT */
    int editMode;

    /** Currently selected auto-align method (edge detection, least squares, etc.) */
    int alignMode;

    /** Indicates whether the Control (Strg) button is pressed. */
    bool ctrl;

    /** Indicates whether the Shift button is pressed. */
    bool shift;

    bool keyDown;

    int chessFieldSize;

    /** This stack defines the operations which are done in the resize-dialog.
      The single stackobjects define which borders are painted on the canvas, so that it is much more easy
      to delete the last imageboredr before a new one is painted.
      the object store the following information:
      int[5]= {scaleX,scaleY,offsetX,offsetY,color}
      scaleX,scaleY     : define the size of the borders
      offsetX, offsetY  : define where the rectangle is located according to the image
      color             : means black=0 (for deleteing an old border) or white=1 (painting a new one) 
     */
    McListStack<resizeInfo*> resizeStack;   

    SliceInfo identityTrans;

    /** Indicates whether maximum intensity images are used for alignment visualization */
    //bool useMaxIntProjection;

    /** Slice number to be displayed in sagittal and coronal views */
    int sagittalViewSliceNumber;
    int coronalViewSliceNumber;
};

#endif

/// @}
