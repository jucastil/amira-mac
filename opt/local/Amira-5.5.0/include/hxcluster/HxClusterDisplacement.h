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
#ifndef HX_CLUSTER_DISPLACEMENT_H
#define HX_CLUSTER_DISPLACEMENT_H

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxGLPolyLine.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcluster/HxCluster.h>
#include <hxcluster/SoClusterDisplacement.h>

/// This module display slices of a regular grid in wireframe.

class HXCLUSTER_API HxClusterDisplacement : public HxModule {

  HX_HEADER(HxClusterDisplacement);
  
  public:
    /// Constructor.
    HxClusterDisplacement ();

    /// Compute method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// The other cluster.
    HxConnection portData2;

    /// Colormap used for pseudo-coloring.
    HxPortColormap portColormap;

    /// Color mode: 0=Length, 1=Id, data columns of both clusters.
    HxPortMultiMenu portColorize;

    /// Options: 0=opaque mode.
    HxPortToggleList portOptions;

    enum { C_FILTER=0, C_OPAQUE=1 };

    ///
    HxPortText portFilter;

    /// Action: 0=Export A, 1=Export B, 2=Select, 3=Reset
    HxPortButtonList portAction;

    enum { C_EXPORT_A=0, C_EXPORT_B=1, C_SELECT=2, C_RESET=3, C_UNDO=4 };

  protected:
    ~HxClusterDisplacement();

    struct Info {
        unsigned int color;
        int other;
    };

    McDArray<Info> info;
    McBitfield selection;
    McHandle<SoClusterDisplacement> so;
    HxGLPolyLine polyLine;
    unsigned int filterInitialized:1;
    unsigned int noFilter:1;

    McBitfield filterBits;
    McBitfield roiBits;
    McDArray<McBitfield> undoStack;

    float lineWidth;
    float maxDist;
    int lineSmooth;

    void exportA();
    void exportB();
    void doExport(HxCluster* src, McBitfield& selection);
    void colorize(HxCluster* set1, HxCluster* set2);
    void identify(HxCluster* set1, HxCluster* set2);
    void select(HxCluster* set1, HxCluster* set2);
    void defaultSelection(HxCluster* set1, HxCluster* set2);
    void viewerSelect();
    void setSelection();
    static void viewerSelectCB(void* userdata);

    friend class SoClusterDisplacement;
};

#endif

/// @}
