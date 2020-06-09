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

/// @addtogroup hxtetra hxtetra
/// @{
#ifndef SMOOTH_TETRAGRID_H
#define SMOOTH_TETRAGRID_H

#include <mclib/McProgressInterface.h>

#include <hxcore/HxMessage.h>

#include <hxfield/HxTetraGrid.h>
#include <hxtetra/HxGridVolume.h>

#include <hxtetra/HxTetraWinDLLApi.h>  // ??

/// Vertex smoothing for tetrahedral grid.
class HXTETRA_API SmoothTetraGrid {

  public:

    /// Constructor.
    SmoothTetraGrid(HxTetraGrid* tetraGrid);

    /// Destructor.
    virtual ~SmoothTetraGrid();

    /// Set grid volume.
    void setGridVolume(HxGridVolume* gridVol);

    /// Improve grid by moving inner vertices.
    int smooth(int mode, int nLoops, float threshold, 
	       int qualityMeasure=0, int tppExists=0,
	       McProgressInterface *progress=NULL,
	       HxMessage *hxMsg=NULL);

    /// Move inner vertex.
    int smoothVertex(int iVertex, int mode, float threshold, 
		     McDArray<float>& quality,
		     int qualityMeasure=0);

    /// Move vertex in order to optimize (worst) quality of 
    /// surrounding tetras.
    virtual int optimizationSmoothing(int iVertex, 
				      float threshold, 
				      McDArray<float>& quality,
				      int &starShaped,
				      int nLoops,
				      int qualityMeasure=0);

  protected:
    HxTetraGrid* grid;
    HxGridVolume* gridVolume;

    /// Move vertex towards center of mass of surrounding vertices.
    virtual int laplaceSmoothing(int iVertex, 
				 McDArray<float>& quality);
};

#endif

/// @}
