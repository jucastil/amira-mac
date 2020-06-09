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
#ifndef HX_SLICE_TRAJECTORY
#define HX_SLICE_TRAJECTORY

#include <hxlattice/HxLatticeWinDLLApi.h>

#include <hxcore/HxArbitraryCut.h>
#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>

class HxLineSetInterface;
class HxSpatialGraphInterface;

/// This class modifies the data window (contrast settings) of an OrthoSlice
class HXLATTICE_API HxSliceTrajectory : public HxOverlayModule {

  HX_HEADER(HxSliceTrajectory);

  public:

    /// Constructor
    HxSliceTrajectory (void);

    /// User information
    HxPortInfo  portInfo;

    /// line within a lineset
    HxPortIntSlider  portLineSelection;

    /// slice position on the curve
    HxPortIntSlider  portSlicePosition;

	/// toggle button for camera adjustment (up front view)
	HxPortToggleList  portView;

    /// GUI update
    virtual void  update (void);

    /// computational part
    virtual void  compute (void);

    /// Tcl command interface.
    virtual int  parse (Tcl_Interp *t, int argc, char **argv);

  protected:

    /// Destructor of Class HxSliceTrajectory
    virtual  ~HxSliceTrajectory (void);

	float cameraDistance;

  private:

    /// adjust min and max value of the slice slider. Respects if segement centers or vertices are to be used.
    void adjustSlicePositionMinMax();

    /// gets the current center and tangent (uses port values)
    void getCenterAndTangent(HxLineSetInterface* trajectory, McVec3f& center, McVec3f& tangent);
    void getCenterAndTangent(HxSpatialGraphInterface* trajectory, McVec3f& center, McVec3f& tangent);



};

#endif




/// @}
