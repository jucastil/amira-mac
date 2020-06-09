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
#ifndef HX_SAMPLE_TO_TETRA
#define HX_SAMPLE_TO_TETRA


#include <hxtetra/HxTetraWinDLLApi.h>

#include <mclib/McVec4f.h>
#include <mclib/McBox3f.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>

#include <hxfield/HxTetraData.h>
// #include <hxcas/McIvBox.h>


class HxField3;
class HxGridVolume;
class HxTetraGrid;
class HxScalarField3;


/// This class assigns scalar values to a tetrahedral grid
/// either a scalar field will be produced with mean values
/// or a vector field with minimum, mean, and maxium value
class HXTETRA_API HxSampleToTetraGrid : public HxCompModule
{

  HX_HEADER(HxSampleToTetraGrid);

  public:

    /// Default constructor.
    HxSampleToTetraGrid (void);

    /// Destructor.
   ~HxSampleToTetraGrid (void);

    /// Second input port.
    HxConnection  portScalarField;

    /// Info ports
    HxPortInfo  portInfo;

    /// Sampling depth (refinement level)
    HxPortIntSlider  portSamplingLevel;

    /// Result type (scalar or vector field)
    HxPortRadioBox  portResultType;

    /// Default values for unsampled grid elements
    HxPortFloatTextN  portDefaultValue;

    /// Intersection box
    // HxPortToggleList  portShowBox;

    /// Button for starting calculation 
    HxPortButtonList  portAction;
    
    /// Update method of the user interface components.
    virtual void  update (void);

    /// Compute method: generates field.
    virtual void  compute (void);

    /// Parse method.
    int  parse (Tcl_Interp *, int, char **);


  protected:

    /// Command line info (short module description).
    virtual void  info (const char *);

    /// enumerated values for toggle buttons
    enum {SCALAR = 0, VECTOR = 1, TETRA = 1};

    // create a scalar or vector field on tetrahedral elements
    HxField3  * createField (int type = SCALAR);

    // initialize the given field
    void  initialize (HxTetraData &);

    // the computational part
    bool  sampleValues (HxTetraData &, HxGridVolume * = NULL);

    /// compute sampling points for all sampling levels
    void  createSamplingPoints (int  maxSamplingLevel);

    /// converts a given sampling location of a unit tetrahedron
    /// into barycentric coordinates for an arbitrary tetrahedron
    McVec4f  getSampleLoc(const McVec4f & sample, 
                          const McVec3f & p0, const McVec3f & p1,
                          const McVec3f & p2, const McVec3f & p3) const;

    // retrieve a connected GridVolume module
    HxGridVolume  * getAttachedGridVolume (HxTetraGrid *);

    // sampling points (centroids) in barycentric coordinates
    // for subsequent levels of refinement
    McSmallArray<McDArray<McVec4f>, 4>  samplingPoints;

    // show or hide bounding box of intersection
    void  showIntersectionBox (bool);


  private:

    // intersection between bounding boxes of input data
    McBox3f  intersection(HxTetraGrid *, HxScalarField3 *);

    // get new bounding box for new transformation
    void getNewBox(McBox3f& box, float* bbox, SbMatrix& trafo);

    // Inventor geometry representing a box
    // McIvBox  boxFrame;

    // enumerated values for internal use
    enum {X = 0, Y, Z};
    enum {MIN_X = 0, MAX_X, MIN_Y, MAX_Y, MIN_Z, MAX_Z};
    enum {MIN = 0, MEAN, MAX};
};

#endif

/// @}
