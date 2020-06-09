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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef HX_MOL_SUBSAMPLED_TRAJECTORY_H
#define HX_MOL_SUBSAMPLED_TRAJECTORY_H

#include <hxcore/HxPortIntSlider.h>

#include <hxmolecule/HxMoleculeWinDLLApi.h>
#include <hxmolecule/HxMolTrajectory.h>

#include "HxMoleculeWinDLLApi.h"

/** The class @c HxSubsampledTrajectory contains a subset of time steps of
    some trajectory. All the information is retrieved from this
    trajectory file. */

class HXMOLECULE_API HxSubsampledTrajectory : public HxMolTrajectory
{
    HX_HEADER(HxSubsampledTrajectory);

    ///
    McHandle<HxMolTrajectory> hxtraj;
    
public:
    /// Connection to trajectory from which the actual information is got.
    HxConnection portMainTrajectory;

    ///
    HxPortIntSlider portFactor, portOffset;

public:
    /// Create from data handle.
    HxSubsampledTrajectory();
    /// Destructor.
    ~HxSubsampledTrajectory();

    ///
    void update();

    // Overloaded function - connect portData to @c HxMolTrajectory.
    int autoConnect(HxObject* primary);

    /// Parses tcl commands (overloaded).
    int parse(Tcl_Interp* t, int argc,char **argv);
    ///
    int saveCreation(FILE* fp, const char* dataDir, int saveFlags);
    /// 
    void savePorts(FILE* fp);

protected:
};

#endif

/// @}
