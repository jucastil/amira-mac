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

/// @addtogroup hxdistmap hxdistmap
/// @{
#ifndef HX_COMPUTEDISTANCEMAP
#define HX_COMPUTEDISTANCEMAP

#include <mclib/McBitfield.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPort3DPointList.h>

#include <hxfield/HxUniformScalarField3.h>
#include <hxdistmap/HxNeighborIndexing3.h>
#include <mclib/McTypedPointer.h>

class HxUniformLabelField3;
 
/*
  This module computes a 3D distance map of a binary image.
  You can choose a 3-4-5 chamfer metric or true euclidian distances.
  When euclidian distance is chosen the voxelsize is taken into account.
  The output is a UniformSkalarField (with the same box and dimensions of
  the input image) containing the distance values
*/


class HXDISTMAP_API HxComputeDistanceMap : public HxCompModule {

  HX_HEADER(HxComputeDistanceMap);
  
  public:
    HxComputeDistanceMap();
    ~HxComputeDistanceMap();

    /// update things when the user has changed any settings
    virtual void update();

    /// computes the currently chosen transformations
    virtual void compute();

    /// distance metrics: Chamfer (3,4,5), 
    ///	true Euclidean distance to the associated background voxel
    HxPortRadioBox portType;
    
    /// Metric in chamfer mode: 123, 345, float
    HxPortRadioBox portChamferMetric;

    /// region: inside, outside, both
    HxPortMultiMenu portRegion;

    ///
    HxPort3DPointList portSeed;

    /// "do it" button 
    HxPortDoIt portAction;

    ///
    virtual int canCreateData (HxData* data, McString& createCmd);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
  protected:

    /// input binarized scalar field
    HxUniformScalarField3* source;

    /// dimensions of the field (input and output)
    mculong dims[3];

    /// true if the input image consists of only one slice
    int is2D;

    /// gets a value only if (is2D==1) 
    /// (0 if dims[0] = 1, 1 if dims[1]=1, 2 if dims[2]=1)
    int whichOrientation;

    /// bounding box
    float *bbox;
    float voxelSize[3];
    McPrimType outType;

    /// if true, remeber which voxels did propagate
    int markPropagating;

    McBitfield didPropagate;

    /// array storing index of closest boundary point for each voxel
    McDArray <int> boundaryPoint;

    template<class T>
    void startup(HxUniformScalarField3 *source, HxUniformScalarField3 *dest);


    /// compute distance field using chamfer (3-4-5) metric
    template<class T>
    void computeBSfieldChamfer(void* dist, T* src, const int* dims);

    /// initialize distance field, extract boundary voxels and
    /// initialize bucket-front 
    template<class T>
    void findBoundaryVoxelsChamfer(float* dist,
				   T* src,
				   McDArray <McDArray<int> >& front);
    
    /// propagate distance field using chamfer metric
    template<class T>
    void propagateBSFieldChamfer(float* dist,
				 T* src,
				 McDArray <McDArray<int> >&front,
                                 int neighb=N26);

    /// set inside, outside, sign depending on mode
    template<class T>
    void postProcessChamfer(McTypedPointer dist, T* src);

    /// compute distance field using true euclidian distance
    template<class T>
    void computeBSfieldEuclid(float* dist, 
			      T* src);

    /// initialize distance field, extract boundary voxels and
    /// initialize front 
    template<class T>
    void findBoundaryVoxelsEuclid(float* dst, T* src,
				  McDArray <int>& front);


    /// propagate distance field using euclid metric
    template<class T>
    void propagateBSFieldEuclid(float* dist, 
				T* src,
				McDArray <int>& front);

    /// compute voxels with largest distance to boundary 
    /// (skeletonization) is not used
    template<class T>
    void computeBoundaryPointDistance(float* dist, 
				      T* src);

};

#endif /* HX_DISTANCEMAP */


/// @}
