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
#ifndef GiVIEWER_H
#define GiVIEWER_H

#include "Gi.h"
#include "McEvent.h"
#include "GiFrameBuffer.h"
#include "HxGiWinDLLApi.h"

#include <hxcore/HxViewerBase.h>
#include <hxcolor/HxColormap.h>

class Gi;
class GiGreyImage;
class GiLabelImage;
class GiSelection2D;
class QCursor;

/** This class contains a GiFrameBuffer. The class knows the Gi class it
    belongs to. It provides a method to select a particular slice from
    a 3D volume data set. */

class HXSEGEDITOR_API GiViewer : public HxViewerBase {

  public:
    /// Constructor.
    GiViewer(const char* name, Gi* gi, QWidget* parent);

    /// Select new slice or update current one, e.g. if size has changed.
    virtual void setSlice(int n=-1, bool notify=true);

    ///
    mculong getSliceNumber() const { return sliceNumber; }

    ///
    int getNumSlices() { return (gi?gi->getNumSlices(getOrientation()):0); }

    /// Select new zoom factor.
    virtual void setZoomFactor(float f);

    /// Sets the window used for mapping data values to intensities
    virtual void setDataWindow(float min, float max, bool redraw=true);

    ///
    void getDataWindow(float& min, float& max) const;

    ///
    void storeSelection(int tissue);

    ///
    GiGreyImage* getGreyImage() { return image; }

    ///
    GiLabelImage* getLabelImage() { return label; }

    ///
    GiSelection2D* getSelection() { return selection; }

    ///
    GiFrameBuffer* getFrameBuffer() { return frameBuffer;}

    ///
    void paste() const { frameBuffer->paste(); }

    ///
    void render() const { frameBuffer->render(); }

    /// Get orientation of this viewer, 0=yz, 1=xz, 2=xy
    int getOrientation();

    /// Set orientation of this viewer (0=yz, 1=xz, 2=xy).
    virtual void setOrientation(int o);

    /// Set flip mode of this viewer (depends on orientation).
    virtual void setFlip(int flipx, int flipy, int flipz);

    virtual void setRotate(int rotccw, int rotcw);

    ///
    float getZoomFactor();

    void setColormap(HxColormap* colormap);

    void setMaskingWindow(float vmin, float vmax, bool redraw=true);

    const float* getMaskingWindow() const;

    void setMaskingEnabled(bool value); // selection within data range mask
    void setMaskingOverlay(bool value); // visualize data range mask as overlay

    bool maskingEnabled() const;

    static void computeReplicUniform(int dim, int virtSize, int* nReplic);
    static void computeReplicStacked(int dim, int virtSize, float* zVals, int* nReplic);
    static void computeZoomedSizes(float zf,const int* dims,float* bbox,int multiViewer, McVec2i size[3]);

    void setCursor(const QCursor&);

protected:
    ///
    virtual ~GiViewer();

    virtual void setNumSlices(int nz);
    McDArray<int>       nReplicX;
    McDArray<int>       nReplicY;
    int                 orientation;
    unsigned int        flipx:1;
    unsigned int        flipy:1;
    unsigned int        flipz:1;
    unsigned int        rotcw:1;
    unsigned int        rotccw:1;
    Gi*                 gi;
    GiFrameBuffer*      frameBuffer;
    GiGreyImage*        image;
    GiLabelImage*       label;
    GiSelection2D*      selection;
    mculong             sliceNumber;
    float               zoomFactor;
    float               dataWindow[2];

    void createShapes();
    void setupCoordinateSystem();
};

#endif

/// @}
