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

/// @addtogroup hxcluster hxcluster
/// @{
#ifndef HX_CLUSTER_VIEW_H
#define HX_CLUSTER_VIEW_H

#include <mclib/McHandle.h>
#include <mclib/McColor.h>
#include <mclib/McBitfield.h>
#include <mclib/McDArray.h>
#include <hxcore/HxDisplay.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxGLPolyLine.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HxRangeSet.h>
#include <hxvertexset/SoSphereSet.h>
#include <hxcluster/HxCluster.h>
#include <hxcluster/SoClusterView.h>
#include <Inventor/nodes/SoEventCallback.h>

/// 
class HXCLUSTER_API HxClusterView : public HxModule {

  HX_HEADER(HxClusterView);
  
private:
    class HxRangeSetModuleImpl : public HxRangeSetModule {
      public:
        HxRangeSetModuleImpl(HxClusterView* o)
            : HxRangeSetModule(o->getOwner(), McInterfaceOwner::STATIC_IFACE)
            , mOuter(o)
        {}

        /** Returns the index of the current data set as selected in the given
            display module. Returns -1 if there is no current data set selected. */
        virtual int getCurrentSet(const HxData* data, const HxPortColormap& colormap) const;

      private:
        HxClusterView* mOuter;
    };

  public:
    /// Constructor.
    HxClusterView ();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// save method
    virtual void savePorts(FILE* fp);

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    HxPortColormap portColormap;

    /// Specifies which data column is used for coloring.
    HxPortMultiMenu portColorize;

    // String to mark the special "Id" entry for mapping the colors.
    static const char* P_COLOR_MODE_MAP_ID;

    /// Options: 0=plates, 1=filter, 2=opaque, 3=bonds, 4=scale plates.
    HxPortToggleList portOptions;

    enum { C_PLATES=0, C_OPAQUE=2, C_FILTER=1, C_BONDS=3, C_SCALE_PLATES=4 };

    ///
    HxPortText portFilter;

    ///
    HxPortIntSlider portPointSize;

    /// Specifies which data column is used for scaling spheres.
    HxPortMultiMenu portScaleData;

    ///
    HxPortFloatSlider portSphereScale;

    /// Action: 0=Export, 1=Select, 2=Reset
    HxPortButtonList portAction;

    enum { C_EXPORT=0, C_SELECT=1, C_RESET=2, C_UNDO=3 };

    void doExport();

    /// Redefine this method to add specific picking information.
    virtual void gatherPickInfo(
        const SoPickedPoint* pickedPt, 
        McHashTable<McString, McString>& cbArguments);

    // Increments the counter for WorkArea control
    void incrementWorkAreaCounter() {m_theWorkAreaEnableCounter++;}

    //  Decreases the counter for WorkArea control
    void decreaseWorkAreaCounter() {m_theWorkAreaEnableCounter--;}

  protected:
    ~HxClusterView();

    McHandle<SoEventCallback> soEventCB;
    McHandle<SoClusterView> soCluster;
    McHandle<SoSphereSet> soSphereSet;
    McDArray<unsigned int> color;

    McBitfield selection;
    float sphereScale;
    HxGLPolyLine polyLine;
    unsigned int pointsInitialized:1;
    unsigned int platesInitialized:1;
    unsigned int filterInitialized:1;
    unsigned int pointsColorOk:1;
    unsigned int platesColorOk:1;

    McBitfield filterBits;
    McBitfield roiBits;
    McDArray<McBitfield> undoStack;

    void doPlates(HxCluster*);
    void doPoints(HxCluster*);
    void updateColors(HxCluster*);
    void applyFilter(HxCluster*);
    void mouseClick(SoEventCallback *eventCB);
    void viewerSelect();
    void setSelection();
    static void viewerSelectCB(void* userdata);
    static void mouseClickCB(void *p, SoEventCallback *eventCB);

    friend class SoClusterView;

    // Counter negative when the WorkArea should be disabled
    int m_theWorkAreaEnableCounter;
  private:
    HxRangeSetModuleImpl mRangeSetModule;
};

#endif

/// @}
