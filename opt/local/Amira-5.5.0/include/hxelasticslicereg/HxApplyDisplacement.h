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

/// @addtogroup hxelasticslicereg hxelasticslicereg
/// @{
#ifndef HX_ELASTIC_SLICE_REG_APPLY_DISPLACEMENT
#define HX_ELASTIC_SLICE_REG_APPLY_DISPLACEMENT


#include <hxelasticslicereg/HxElasticSliceRegWinDLLApi.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxlatticex/HxLattice.h>
#include <hxlatticex/HxMutableLattice.h>
#include <hxlatticex/HxMutableLabelLattice.h>



class HXELASTICSLICEREG_API HxApplyDisplacement:public HxCompModule {

    HX_HEADER(HxApplyDisplacement);

  public:
    /** Constructor. */
    HxApplyDisplacement();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** displacement field input */
    HxConnection portDisplacement;

    /** Select interpolation method */
    HxPortMultiMenu portInterpolation;

    /** Do it button. */
    HxPortDoIt portAction;


  public:
    /** Destructor. */
    ~HxApplyDisplacement();

  private:
    void doIt();

    /** Read image slice sliceNum from lattice lat and put it in data. 
     *  Enough space has to be allocated before calling this function. */
    void readImage(HxLattice* lat, const int sliceNum, unsigned char* data);

    /* Write data into lattice at slice sliceNum */
    void writeImage(HxMutableLattice* lat, const int sliceNum, const unsigned char* data);
    void writeImage(HxMutableLabelLattice* lat, const int sliceNum, const unsigned char* data);

    /** Read slice sliceNum of pairs of floats from lattice lat and put it in data. 
     * Enough space has to be allocated before calling this function. */
    void readDeformData(HxLattice* lat, const int sliceNum, float* data);
};

#endif



/// @}
