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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HX_DISPLAY_BOUNDARY_ID
#define HX_DISPLAY_BOUNDARY_ID

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatTextN.h>

#include <hxsurftools/HxDisplaySurface.h>

#include <mclib/McDArray.h>

#include <hxsurface/HxSurface.h>
#include <hxfield/HxTetraGrid.h>


/** Display module for objects of type HxSurface. */

class HXSURFTOOLS_API HxDisplayBoundaryId : public HxDisplaySurface {

  HX_HEADER(HxDisplayBoundaryId);

  public:

    /// Constructor.
    HxDisplayBoundaryId (void);

    /// Update method.
    virtual void update (void);

    /// Compute method.
    virtual void compute (void);

    /// Allows the module to be connected directly to surface scalar fields.
    virtual int autoConnect (HxObject *);

    /// boundary id selection via text input
    HxPortFloatTextN  portBoundaryId;

    /// boundary id selection via slider
    HxPortIntSlider  portSelection;

    /// boundary selection method
    void selectBoundary (int boundaryId = 0);

    /// Parse method.
    int parse (Tcl_Interp *, int, char **);

  protected:

    /// retrieve number of different boundary ids of the connected data
    int getNumBoundaryIds (void);

    /// Destructor.
    virtual ~HxDisplayBoundaryId (void);

    /// show or hide portMaterial
    void showMaterials (short show = 1);

  private:

    // flag for displaying portMaterials
    short  matDisplayFlag;
    int    currentSelection;

    // internal array of boundary ids
    McDArray<short>  boundaryId;

    // number of unique boundary ids for different vertex sets
    // boundary conditions for HxTetraGrid is not implemented.
    int  getNumBoundaryIds (HxSurface *);
    int  getNumBoundaryIds (HxTetraGrid *);
    void selectBoundary (HxSurface  *, int);
    void selectBoundary (HxTetraGrid  *, int);
    bool boundaryIdInList (const short);
    int  getIndexOfBoundaryId (short);

};

#endif

/// @}
