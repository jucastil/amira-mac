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
#ifndef HX_RELABEL_TETRAS_H
#define HX_RELABEL_TETRAS_H

#include <hxtetra/HxTetraWinDLLApi.h>

#include <mclib/McMat3f.h>
#include <mclib/McVec4f.h>

#include <hxfield/HxTetraGrid.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortInfo.h>


class  HxGridVolume;


/// Tool for relabeling tetras using selection by GridVolume
class HXTETRA_API HxRelabelTetras : public HxCompModule {

  HX_HEADER(HxRelabelTetras);
  
  public:

    HxRelabelTetras (void);

    virtual void update (void);
    virtual void compute (void);

    /// Connection to secondary input (GridVolume or Label Field)
    HxConnection portLabelField;

    /// Info Port
    HxPortInfo  portInfo;

    /// Material menu.
    HxPortMultiMenu portMaterials;

    /// Resampling depth.
    HxPortIntSlider  portResample;

    /// Action: reset = 0, set label = 1.
    HxPortButtonList portAction;

    enum  enAction {RESET = 0, SET = 1, NUM_ACTIONS, NONE = -1};

    int  canCreateData (HxData * data, McString & createCmd);


  protected:

    ~HxRelabelTetras (void);

    /// Reset labels of tetrahedral grid
    bool  reset (void);

    /// Assign labels.to (selected) tetrahedra
    bool  assign (void);

    /// compute sampling points for all sampling levels
    void  createSamplingPoints (int  maxSamplingLevel);

    /// converts a given sampling location of a unit tetrahedron
    /// to an arbitrary tetrahedron
    McVec3f  getSampleLoc(McVec3f sample, HxTetraGrid *, const TetraGrid::Tetra &);

    /// converts a given sampling location of a unit tetrahedron
    /// into barycentric coordinates for an arbitrary tetrahedron
    McVec4f  getSampleLoc(const McVec4f & sample, 
                          const McVec3f & p0, const McVec3f & p1,
                          const McVec3f & p2, const McVec3f & p3) const;


  private:

    // Initialize result.
    void  initResult (const char * label = 0);

    // Update material menu.
    void  updateMaterialList (HxTetraGrid * inGrid, HxTetraGrid * outGrid = 0, 
                              HxParamBundle * materials = 0);

    // retrieve a connected GridVolume module
    HxGridVolume  * getAttachedGridVolume (HxTetraGrid *);

    // sampling points (centroids) in barycentric coordinates
    // for subsequent levels of refinement
    McSmallArray<McDArray<McVec4f>, 4>  samplingPoints;

    // Jacobian matrix of a given tetrahedron
    McMat3f  jacobian (HxTetraGrid *, const HxTetraGrid::Tetra &);

};

#endif

/// @}
