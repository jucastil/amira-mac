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

/// @addtogroup hxarith hxarith
/// @{
#ifndef HX_RESAMPLE
#define HX_RESAMPLE

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>

#include <hxarith/Resampler.h>
#include <hxarith/HxArithWinDLLApi.h>

/** This module resamples a regular scalar field and produces a new
    field of different x, y, and z resolution. */
class HXARITH_API HxResample : public HxCompModule {

  HX_HEADER(HxResample);

  public:
    /** Constructor. */
    HxResample();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** In mode Reference the data will be resampled to the grid of the
        refrence object.
      */
    HxConnection portReference;

    /// Info port to display resolution of source data set
    HxPortInfo portResInfo;

    /// Info port to display voxel size of source data set
    HxPortInfo portVoxInfo;

    /** Filter types: 0=box 1=triangle 2=Bell 3=b-spline 4=Lanczos
                      5=Mitchell 6=Minimum 7=Maximum */
    HxPortMultiMenu portFilter;

    /** How to select the new resolution. */
    HxPortRadioBox portMode;

    /** Defines desired resolution in x, y, and z direction. */
    HxPortFloatTextN portRes;

    /** The Voxel size, corresponds with portRes. */
    HxPortFloatTextN portVoxSize;

    /** For labeled volumes only: number of cells to average. */
    HxPortIntTextN portAverage;

    /** Do it button. */
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  public:
    /** Destructor. */
    ~HxResample();

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    /// Save ports.
    virtual void savePorts(FILE* fp);
  private:
    Resampler resampler;
};

#endif

/// @}
