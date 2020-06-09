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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef QX_IMAGE_CROP_H
#define QX_IMAGE_CROP_H

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>

#include <hxlattice/HxLatticeWinDLLApi.h>
#include <hxlattice/ui_QxImageCropDialogBase.h>
#include <hxfield/HxLattice3.h>

#include <Inventor/draggers/SoTabBoxDragger.h>
#include <Inventor/nodes/SoAnnotation.h>

class HxLattice3CropInterface;
class HxImageCrop;
class QPushButton;
class QxLineEdit;

// GUI class used by the crop editor
class HXLATTICE_API QxImageCrop : public QDialog, public Ui::QxImageCropDialogBase
{
    Q_OBJECT

  public:
    // Constructor
    QxImageCrop(HxImageCrop* editor, QWidget *parent=0);

    // Destructor
    ~QxImageCrop();

    // Init dialog, called from HxImageCrop::startEditing()
    void setLattice(HxLattice3*);

    // Enumerates all text fields
    enum TextField {
        IMIN,
        IMAX,
        JMIN,
        JMAX,
        KMIN,
        KMAX,
        THRESHOLD,
        REPLICATE,
        XMIN,
        XMAX,
        YMIN,
        YMAX,
        ZMIN,
        ZMAX,
        LastId
    };

    /* Set (integer) value of a text field. Used to set IMIN...
       KMAX via the Tcl-command interface. Actually this is not
       needed anymore since now a crop command is provided by
       the Hxlattice3 interface. */
    void setValue(int which, int value);

    // Simply calls accept(), only used by HxImageCrop::parse()
    void doIt();

    void getMinMax(int min[3], int max[3]);

    //cause the dragger to be displayed as a SoAnnotation
    void displayAsAnnotation( bool annot );

    //Return dragger node
    SoTabBoxDragger* getDragger();

  public slots:
    /* Crops duplicated instance of coordinate object, adjusts
       the min max text fields (to overwrite illegal input) as
       well as the dragger. */
    void crop();
    void autoCrop();

  protected slots:
    void accept();
    void reject();

    void flipX();
    void flipY();
    void flipZ();

    void swapXY();
    void swapXZ();
    void swapYZ();

    void bbox();
    void modeChanged(bool);
    /** Calls if replication mode button is pressed. */
    void repModeBtnPressed();

    void fillInCoordinates(int);
    void comboBoxCheckBoxStateChanged(bool checked);

    void mouseMoveEvent(QMouseEvent *e);

    /** 
     * Called to show the image crop editor help.
     */
    void showHelp();

  protected:
    HxImageCrop* editor;
    HxLattice3CropInterface* lattice;
    int dataMin[3], dataMax[3];
    float minValue;
    float saveVoxelSize[3];
    QxLineEdit* t[LastId];
    QPushButton* b[7];
    McDArray<int> flipsAndSwaps;
    
    //In case dragger is displayed under an SoAnnotation.
    //In that case the dragger is always visible upon all geometries.
    bool m_displayAsAnnotation;
    McHandle<SoAnnotation> annotation;
    
    //Return dragger root (annotation or dragger)
    SoNode* getDraggerRoot();

    McHandle<SoTabBoxDragger> dragger;
    float maxScale[3];
    float constrainBox[6];
    float currentBox[6];
    int minSave[3], maxSave[3];
    unsigned int blockDragger:1;
    unsigned int boxChanged:1;
    unsigned int isInitialized:1;
    unsigned int boxMode:1;


    void setMinMax(const int min[3], const int max[3]);
    void getBoundingBox(float b[6]);
    void setBoundingBox(const float b[6]);
    void adjustDragger();
    void finishDragging();
    void constrainDragger();
    void getIndex(int, float, float, int& iMin, int& iMax);
    void reset();

    static void finishDraggingCB(void* userData, SoDragger*);
    static void constrainDraggerCB(void* userData, SoDragger*);
    void fillComboBox(void);

private:
    float dataSize[6];
};

#endif

/// @}
