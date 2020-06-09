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

/// @addtogroup hxlatticecompat hxlatticecompat
/// @{
#ifndef HX_LATTICE_DATA_ACCESS_H
#define HX_LATTICE_DATA_ACCESS_H

#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxRoiInterface.h>
#include <hxcore/HxCompModule.h>

#include <hxtime/HxPortTime.h>
#include <hxtime/HxTime.h>

#include <hxlatticex/HxLattice.h>

#include <hxfield/HxField3.h>

#include "HxLatticeCompatWinDLLApi.h"

class HxTabBox;

/** Provides access to a external data object.
  */
class HXLATTICECOMPAT_API HxLatticeAccess : public HxCompModule
{
    HX_HEADER (HxLatticeAccess);

  public:

    ///
    HxLatticeAccess ();

    /// If roi connected, this specifies the volume that will be loaded
    //HxTightConnection portRoi;

    ///
    HxPortMultiMenu portDataSet;
    ///
    HxPortFloatTextN portBoxMin;
    ///
    HxPortFloatTextN portBoxSize;
    ///
    HxPortButtonList portBoxMax;
    /// show box, downsample
    HxPortToggleList portOptions;
    /// downsampling factor for 3 directions.
    HxPortIntTextN portResolution;
    ///
    HxPortIntSlider portTimeSlider;
    ///
    HxPortDoIt portAction;
    ///
    HxPortTime portTime;

    ///
    virtual void update ();

    ///
    virtual void compute ();

    ///
    virtual int canCreateData (HxData* data, McString& createCmd);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:

    virtual void info();

    ///
    ~HxLatticeAccess ();
    ///

    HxTabBox* tabbox;

  private:

    /* ---------- the Roi Interface */
    void getRoi(float bbox[6]) const;

    void getTransformation( McMat4f & outTrans ) const;

    friend class HxRoiInterfaceProxyTemplate<HxLatticeAccess>;
    /* ---------- end of the Roi Interface */

    //
    static void queueNotification (HxLatticeGetQueue* queue, void* data);
    HxLatticeGetQueue* queue;
    int queuedataset;
    McHandle<HxField3> result;
    int actorig[3];

    int blocking;
};

#endif

/// @}
