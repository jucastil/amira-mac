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
#ifndef QXORTHOVIEWMANAGER_H
#define QXORTHOVIEWMANAGER_H

#include<mclib/McHandable.h>
#include <mclib/McDArray.h>
#include <hxcore/HxThread.h>


class McBox2i;
class QxViewAlignSlicesSagittal;
class QxViewAlignSlicesCoronal;
class QxViewAlignSlicesOrthogonalToolbar;
class QxViewAlignSlicesOrthogonalCommonToolBar;
class QxAlignSlices;
class SliceInfo;
class HxLattice;
class UpdateOrthogonalViewsThread;

class QxOrthoViewManager  : public McHandable {
    
public:

    enum OrthoDisplayMode {CROSS_SECTION, MAX_INT_PROJECTION};
    enum OrthoOrientation {SAGITTAL, CORONAL, BOTH};
    enum OrthoUpdateAction {NONE, CLEAR, UPDATE};

    QxOrthoViewManager(QxAlignSlices* gui, HxLattice* lat, const bool useMaxIntProj);
    ~QxOrthoViewManager();

    void init(HxLattice* lat, const bool useMaxIntProj);

    void setSliceNumberAxial (int s);
    void setSliceNumberSagittal (int s);
    void setSliceNumberCoronal (int s);

    int getSliceNumberAxial() const {return sliceNumberAxial;};
    int getSliceNumberSagittal() const {return sliceNumberSagittal;};
    int getSliceNumberCoronal() const {return sliceNumberCoronal;};

    void showSagittalView(bool show);
    void showCoronalView(bool show);

    void setUseMaxIntProj(bool useMaxIntProj);

    /* Show only subset of size zRange above and below sliceNumberAxial*/
    void setShowZRange(bool show);
    void setZRange(int r);

    /* Set the width (in percent) of the red line indicating the axial slice number */ 
    void setOrthoViewLineWidth(const int value);

    OrthoDisplayMode getDisplayMode() {return displayMode;};

    void zoomIn();
    void zoomOut();

    void updateImageData();
    bool updateLine(const int z);

    void getRangeToUpdate(int& minZ, int& maxZ) const;
    void updateView();
    void updateView(int minZ, int maxZ, const OrthoOrientation which,
        const int tx = 0, const int ty = 0, const bool trans = false, const bool rot = false, const bool mirror = false);



    HxMutex& getDataMutex() {return dataMutex;}
    HxMutex& getUpdateListMutex() {return updateListMutex;}

    void lockMutex (HxMutex& m) {m.lock();}
    void unlockMutex (HxMutex& m) {m.unlock();}

    /** 
     * Accessor to the coronalView member.
     */
    const QxViewAlignSlicesCoronal* getCoronalView() const;

    /** 
     * Accessor to the sagittalView member.
     */
    const QxViewAlignSlicesSagittal* getSagittalView() const;

private:

    enum Coordinate {X, Y};

    const int updateFreqCrossSectionMode;
    const int updateFreqMaxIntProjectionMode;
    int updateFreq;

    // Members
    int sliceNumberAxial, sliceNumberSagittal, sliceNumberCoronal;
    int dims[3];
    int visibleRangeZMin, visibleRangeZMax;
    bool showZRange;
    int zRange;
    float zoom;

    UpdateOrthogonalViewsThread* updateViewsThread;

    OrthoDisplayMode displayMode;

    QxViewAlignSlicesSagittal* sagittalView;
    QxViewAlignSlicesCoronal* coronalView;
    QxViewAlignSlicesOrthogonalCommonToolBar* commonOrthoToolbar;

    QxAlignSlices* alignGUI;
    HxLattice* lattice;
    //McDArray<SliceInfo>& transforms;

    HxMutex dataMutex;
    HxMutex updateListMutex;

    /* List of (MinX, MaxX) and (MinY, MaxY) pairs
       indicating which part of the coronal resp. sagittal line
       is up to date. The range [0, Min-1] and [Max+1, dims[n]-1]
       need to be updated. A value of -1 for x resp y indicates that everything needs
       to be updated for coronal resp. sagittal views.
       The boxes only exits when the display mode is MAX_INT_PROJECTION*/
    McDArray<McBox2i*> updateListUpToDateBox;
    McDArray<OrthoUpdateAction> updateListCoronal;
    McDArray<OrthoUpdateAction> updateListSagittal;

    // Methods
    void setOrthoDisplayModeToCrossSection() {displayMode = CROSS_SECTION;};
    void setOrthoDisplayModeToMaxIntProjection(){displayMode = MAX_INT_PROJECTION;};

    void setVisibleRangeZMin(const int z);
    void setVisibleRangeZMax(const int z);
    void getVisibleRangeZ(int& minZ, int&maxZ) {minZ = visibleRangeZMin; maxZ = visibleRangeZMax;};

    void clearSlices(const int zMin, const int zMax, const OrthoOrientation which);
    void translateSlices(const int zMin, const int zMax, const int tx, const int ty, const OrthoOrientation which);
    void updateSlices(const int zMin, const int zMax, const OrthoOrientation which);

    bool useThread();

    void updateLines();

    void updateLineCrossSection(const int z);
    void updateLineMaximumIntensityProjection(const int z);
    void clearLine (const int z);
    void clearLineImmediate (const int zMin, const int zMax, const OrthoOrientation which);

    void clearSlices(const int zMin, const int zMax);
    void translateSlices(const int zMin, const int zMax, const int tx, const int ty);
    void updateSlices(const int zMin, const int zMax);

    void resetUpToDateBoxes(const int zMin, const int zMax, const OrthoOrientation which);
    void createUpToDateBoxes();
    void deleteUpToDateBoxes();

    /* Calls setVisibleRangeZMin and setVisibleRangeZMax with appropriate  values. */
    void updateZRange();

    //returns the intersection bounding box of the line {X|Y}==value with the image bounding box
    bool getIntersectionBoxOfLineWithImage(const int z, const Coordinate coord, const int value, McBox2i& box); 
};


#endif

/// @}
