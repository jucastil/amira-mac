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
#ifndef HX_CLUSTER_DENSITY_H
#define HX_CLUSTER_DENSITY_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortMultiMenu.h>

/// This module display slices of a regular grid in wireframe.

class HXCLUSTER_API HxClusterDensity : public HxCompModule {

  HX_HEADER(HxClusterDensity);
  
  public:
    /// Constructor.
    HxClusterDensity ();

    /// Compute method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Choose the algorithm
    HxPortMultiMenu portAlgo;

    /// Influence radius.
    HxPortFloatTextN portRadius;

    /// specify which data column in the input represents the mass of each point
    HxPortMultiMenu portMass;

    /// Start computation.
    HxPortDoIt portAction;

    int canCreateData(HxData* data, McString& createCmd);

  protected:
    /// For algorithm 2 this specifies the number of boxes the volume is separated into
    McVec3i flatTreeSize;
    /// For algorithm 3 this specifies the depth of the octree (7 should be a good number)
    int octreeDepth;
    /// For algorithm 3 this specifies how many points can be in one tiny box of the octree
    int octreeLeafNumber;
};

#endif

/// @}
