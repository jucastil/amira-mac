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
#ifndef GI_MAGICWAND_H
#define GI_MAGICWAND_H

#include <QObject>

#include "Gi.h"
#include "GiTool.h"
#include "GiSelection2D.h"
#include <hxcore/HxViewerTool.h>

#include <mclib/McData2D.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec2f.h>
#include <mclib/McBox2i.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McColor.h>

class QCheckBox;
class QToolButton;
class GiFrameBuffer;

struct MagicWandSeed {
    float lower;
    float upper;
    int orientation;
    McVec3i seedPoint;

    unsigned int is3D:1;
    unsigned int sameMaterialOnly:1;
    unsigned int fillInterior:1;
    unsigned int lesionType:8;

    McVec2i seedPoint2(int o) {
        switch (o) {
        case 0: return McVec2i(seedPoint[1],seedPoint[2]);
        case 1: return McVec2i(seedPoint[0],seedPoint[2]);
        default: return McVec2i(seedPoint[0],seedPoint[1]);
        }
    }
};

struct MagicWandLimit {
    int id;
    int slice;
    int orientation;
    McDArray<McVec2f> points;

    void operator=(const MagicWandLimit& other) {
        id = other.id;
        slice = other.slice;
        orientation = other.orientation;
        points = other.points;
    }
};

/** Implements 2D and 3D region growing. */

class GiMagicWand : public QObject, public GiTool { 

    Q_OBJECT

  public:
    /// Constructor.
    GiMagicWand(Gi* theGi);

    /// Destructor.
    ~GiMagicWand();

    virtual const char* getIconName() const{ return "SegMagicWandIcon.png"; }

    /// 3D mode ?
    int is3D();

    /// Render method.
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box);

    /// Event handler.
    int handleEvent(GiFrameBuffer* frameBuffer, McEvent* event);

    /// Called after add, subtract, replace, or clear selection.
    virtual void selectionNotify(int mode);

    /// Called when this tool is activeted.
    virtual void select();

    /// Called before another tool is activated.
    virtual void deselect(class GiFrameBuffer*);

    /** Prevents regions covered by other seeds from being deleted. This method
        is called from GiLabelImage::subtractSelection(). Selected pixels in
        @c selection are unset if they would be set by any seed other than the
        current one. */
    void lockInactiveSeeds(GiSelection2D* selection);
    //void lockInactiveSeeds(unsigned char* selection);
    
    /// Returns the current cursor.
    virtual const QCursor & getToolCursor() const;

    /// Performs region growing from given seed voxel, called by 3D VolPick tool.
    void regionGrowingVolPick(const McVec3i& voxel, float intensity, int mode);

  protected:
    /// Interaction modes
    enum Mode {
        /** Seed mode (default). Crosshair cursor over the background, arrow
            cursor over existing seeds. Clicking on the background defines
            a new seed point, clicking on an existing seed point selects this
            seed point. */
        SEED_MODE=0,
        /** Limit mode. Pencil cursor over the background, delete cursor over
            existing limit lines. Clicking on an existing limit line deletes
            this line. Clicking on the background and moving the mouse defines
            a new limit line. */
        LIMIT_MODE=1,
    };

    /// Cursor shapes
    enum Cursor {
        /// Crosshair cursor (standard cursor in seed mode).
        CROSSHAIR_CURSOR=0,
        /// Arrow cursor (used if mouse is over existing seed point in seed mode).
        ARROW_CURSOR=1,
        /// Pencil cursor (standard cursor in limit mode).
        PENCIL_CURSOR=2,
        /// Delete cursor (used if mouse is over existing limit line in limit mode).
        DELETE_CURSOR=3
    };

    QCheckBox* _w3DMode;
    QCheckBox* _wSameMaterialOnly;
    QCheckBox* _wFillInterior;
    QToolButton* _wLimitMode;

    Mode mode;
    Cursor cursor;
    float seedValue;
    int seedToBeRendered;
    int currentSeedId;
    int currentSeedIsPermanent;
    McDArray<MagicWandSeed> seeds;
    MagicWandSeed currentSeedBackup;
    McDArray<MagicWandLimit> limits;
    unsigned int seedsLoaded:1;
    unsigned int limitModeDrawing:1;
    unsigned int showSeedsAndLimits:1;
    unsigned int mHideSeeds:1;
    unsigned int mLastOperationWas3D;
    int limitToBeDeleted;
    int lastNumberOfLimits;
    McDArray<McColor> lesionColors;
    unsigned int _mLesionType;
    McHandle<HxViewerModalTool> mVolPickTool;

    bool mMaskingSliderTracking;

    virtual void createWidget(QWidget* parent);

    void setSeedMode();
    void setLimitMode(GiFrameBuffer* frameBuffer, McEvent* event);
    void setCursor(Cursor cursor);
    void redrawSeeds(int showSeeds);
    void checkRange(McVec3i& p);
    bool getMinMax(float& min, float& max, float seedValue=0);
    void getMinMax(float& min, float& max, const MagicWandSeed& seed);
    void checkCursor(GiFrameBuffer* frameBuffer, McEvent* event);
    void checkCursorLimitMode(GiFrameBuffer* frameBuffer, McEvent* event);
    int checkForClickOnSeedPoint(GiFrameBuffer* frameBuffer, McEvent* event);
    int regionGrowing2D(GiFrameBuffer*, int mode, MagicWandSeed&);
    int regionGrowing3D(GiFrameBuffer*, int mode, const McVec3i& seedPoint);
    void grow2D(McBitfield& bitfield, McBox2i& box, MagicWandSeed&);
    void renderLimits(GiFrameBuffer* frameBuffer);
    int handleEventSeedMode(GiFrameBuffer* frameBuffer, McEvent* event);
    int handleEventLimitMode(GiFrameBuffer* frameBuffer, McEvent* event);
    int computeLimitSlice(McData2D<unsigned char>& slice, MagicWandSeed& s);
    void combineLimitsAndLabels(McData2D<unsigned char>&,McData2D<unsigned char>&);
    void saveSeed(const MagicWandSeed*);
    void deleteSeed(const MagicWandSeed*);
    void saveLimit(const MagicWandLimit*);
    void deleteLimit(const MagicWandLimit*);
    virtual void init();
    int initSeeds();
    int initLimits();
    void selectSeed(int which);
    
    virtual void dataWindowChanged(float vmin, float vmax);

    friend class MagicWandClickAction;
    friend class MagicWandLimitAction;
    
  protected slots:
    void update3D();
   
  public slots:
    void update();
    void setLimitMode(bool value);
};

#endif

/// @}
