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
#ifndef QX_VIEW_ALIGN_SLICES_ORTHOGONAL_H
#define QX_VIEW_ALIGN_SLICES_ORTHOGONAL_H


#include <QDockWidget>
#include <mclib/McBoundingBox.h>


class QxAlignSlices;
class SliceInfo;
class HxLattice;
class McTypedData2D;
class QxImageViewer;
class QxViewAlignSlicesOrthogonalLineShape;
class QxOrthoViewManager;


/** \class QxViewAlignSlicesOrthogonal QxViewAlignSlicesOrthogonal.h "hxalign/QxViewAlignSlicesOrthogonal.h"
 *  \brief This class provides an orthogonal view (sagittal or coronal) to the current alignment in the aligment editor.
 *
 *  This class provides an orthogonal view (sagittal (ZY) or coronal(XZ) orientation) to the current alignment in the aligment editor. 
 *  It is a dockwindow docking to the alignment editor window and containing an image area (QxImageViewer). 
 *  The orientation is set when the object is created. The image shows the cross-section at z=sliceNumber. 
 *  The lineShape (QxViewAlignSlicesOrthogonalLineShape) indicates the current slice in the main alignment editor.
 *  In order to improve performance, one can provide a minimum and maximum z-value, thus reducing the number of 
 *  slices that has to be rendered.
 */

class QxViewAlignSlicesOrthogonal : public QDockWidget {

  Q_OBJECT

  public:
    /** Constructor */
    QxViewAlignSlicesOrthogonal(QxOrthoViewManager* orthoMan, HxLattice* lattice, QxAlignSlices *parent = 0, const char *name = 0);
    //QxViewAlignSlicesOrthogonal(McDArray<SliceInfo>& trans, QxAlignSlices *parent = 0, const char *name = 0);

    /** Destructor */
    ~QxViewAlignSlicesOrthogonal();

    virtual void clearLine(const int z) = 0;

    void updateImageData();
    void updateLineShape(const int slice);
    void setOrthoViewLineWidth(const int value);
    void setZoom (const float zoom);

    McTypedData2D* getImageData() const {return imageData;};
    

protected:
    int getMinimumZSize () const;

    QxAlignSlices* mQxAlignSlices;
    QxOrthoViewManager* alignGUI;

    HxLattice* lat;                    /**< input lattice */
    McTypedData2D* imageData;           /**< data for image */

    int dims[3];    /**< input lattice dimensions */
    McBoundingBox bb; /**< input lattice bounding box */
    int margin;         /**< space between image and widget boundary */
    int decoSize;
    bool colorImage;    /**< color image yes/no */


    float pixelScale[2];

    QxImageViewer* drawView;                            /**< the image widget */
    QxViewAlignSlicesOrthogonalLineShape* lineShape;    /**< line indicating the current slice in the main alignment window */


};

#endif



/// @}
