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

/// @addtogroup hximview hximview
/// @{
#ifndef HX_STANDARD_VIEW_H
#define HX_STANDARD_VIEW_H

#include <hxcore/HxModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/QxViewerPanel.h>
#include <hxfield/HxLattice3.h>
#include <hximview/HxImviewWinDLLApi.h>

class QEvent;
class QWidget;
class QxImageViewer;
class QxImageViewerShape;

/// 
class HXIMVIEW_API HxStandardView : public HxModule {

  HX_HEADER(HxStandardView);
  
  public:
    /// Returns pointer to global instance of the tracking class.
    static HxStandardView* getInstance();

    /// Shows and hides ports.
    virtual void update();
    
    /// Compute method.
    virtual void compute();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    HxConnection portOverlayData;

    ///
    HxPortInfo portInfo;

    ///
    HxPortFloatTextN portRange;

    ///
    HxPortIntSlider portSliceNumberYZ;

    ///
    HxPortIntSlider portSliceNumberXZ;

    ///
    HxPortIntSlider portSliceNumberXY;

    ///
    HxPortGeneric portZoom;

    ///
    HxPortMultiMenu portOverlayMode;

    ///
    enum { OVERLAY_BLEND=0, OVERLAY_ADD=1, OVERLAY_MAX=2, OVERLAY_CHECKERBOARD=3, OVERLAY_WINDOW=4 };
    
    ///
    HxPortFloatTextN portOverlayRange;

    ///
    HxPortFloatSlider portOverlayBlendFactor;

    ///
    HxPortIntSlider portOverlayPatternSize;

    ///
    void setPosition(int i, int j, int k);

    ///
    void setPositionXYZ(float x, float y, float z);

    /// Sets zoom factor. For magnification use f>1, for minification use f<1.
    void setZoomFactor(float f);

    /// Returns current zoom factor.
    float getZoomFactor() const { return zoomFactor; }

    /// Makes the zoom factor bigger, returns new factor.
    float zoomIn();

    /// Makes the zoom factor smaller, returns new factor.
    float zoomOut();

    /// Enumerates different orientations
    enum Orientation { STANDARD=0, SUPINE=1, SIDEPOS_RIGHT=2, SIDEPOS_LEFT=3 };

    /// Set orientation
    void setOrientation(Orientation orientation);

    /// Get orientation
    Orientation getOrientation() const { return orientation; }

    ///
    void setBilinearInterpolation(bool value);

    ///
    bool getBilinearInterpolation() const { return bilinear; }

    ///
    void addShape(QxImageViewerShape* shape);

    ///
    void removeShape(QxImageViewerShape* shape);

    ///
    QxImageViewer* getViewer(int which) const { return viewers[which]; }

    ///
    void updateViewers();

    /// The user event callback definition.
    typedef bool HxStandardViewHandleEventCB(void* userData, QxImageViewer* viewer, QEvent* event);

    /// Set a user event callback. If the callback function returns true, then, 
    /// the standard process won't be performed.
    void setHandleEventCallback ( HxStandardViewHandleEventCB* f, void* userData=0 );

    /// Get the user event callback.
    HxStandardViewHandleEventCB* getHandleEventCallback () {return m_handleEventCallback;}

    /// Get the user data path threw the user event callback.
    void* getHandleEventUserData() {return m_handleEventUserData;}

  protected:
    enum Slice { XZ=1, YZ=0, XY=2 };

    void showFrameBuffers();
    void updatePosition();
    void updateInfoPort();
    void extractSlice(int which, int sliceNumber);
    void extractOverlaySlice(int which);
    void mapOverlaySlice(int which);
    void getSamplingDensity(int which, int& w, int& h);
    void savePorts(FILE *fp);

    QxImageViewer* viewers[3];
    int currentSliceNumber[3];
    HxLattice3* lattice;
    SbMatrix mat;
    SbVec2s overlaySize[3];
    McDArray<float> overlayData[3];
    int overlayStatus[3];
    unsigned int bilinear:1;

    float zoomFactor;
    Orientation orientation;
    McVec3f stereoPointWorld[3];
    unsigned int stereoPointSet[3];

    QxViewerPanel::Layout oldLayout;
    McDArray<HxViewerBase*> oldViewers;

    static void crossHairChanged(void*, QxImageViewer*);
    static bool processEvent(void*, QxImageViewer*, QEvent*);

    void* m_handleEventUserData;
    HxStandardViewHandleEventCB* m_handleEventCallback;

  private:
    /// Constructor is protected because this is a singleton.
    HxStandardView();

    /// Destructor is protected because unref() should be used.
    virtual ~HxStandardView();
};

#endif

/// @}
