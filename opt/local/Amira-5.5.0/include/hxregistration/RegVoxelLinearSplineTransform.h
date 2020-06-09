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

/// @addtogroup hxregistration hxregistration
/// @{
#ifndef REG_VOXEL_LINEAR_SPLINE_TRANSFORM
#define REG_VOXEL_LINEAR_SPLINE_TRANSFORM


#include <mclib/McMalloc.h>
#include <hxregistration/RegSplineTransform.h>

/// RegParametricTransform subclass for linear spline transforms.
class RegVoxelLinearSplineTransform : public RegSplineTransform
{
public:
    RegVoxelLinearSplineTransform(bool fastMode = false);
    
    virtual ~RegVoxelLinearSplineTransform()
    {
        if (Cx)
            mcfree(Cx);
        if (Cy)
            mcfree(Cy);
        if (Cz)
            mcfree(Cz);        
    }

    virtual void setReference( HxSpatialData *reference );

    virtual HxLandmarkSet *createControlPoints(HxLandmarkSet *controlPoints = NULL);
    
    virtual void refineNoInterpolants ( const int factor = 2 ) ;
    
    virtual void precomputeInterpolants();
    
    virtual void getTransformedGrid( int *pos, McVec3f& tpos, McDVector<double> &pV );

    virtual void getTransformedGridSequence ( McVec3f *v, const int numPoints, int *pos );

    virtual void getTransformedGridSequence ( McVec3f *tPointV, 
        const int numPoints, int *pos, McDVector<double> &pV );

    virtual void getTransformedGridComplete ( McVec3f *v, float **conv_x, float **conv_y ) {};
   
    /// Get volume influenced by one parameter.
    virtual void getVolumeOfInfluence ( int idx, float *fromVoI, float *toVoI, int fastMode=-1 );
    
    virtual void getGridSpacing();
    
private:
    ///Depends on resolution level because of precomputation of interpolants
    HxRegScalarField3 *ReferenceField;

    int referenceDims[3];

    struct _TCoeff : public RegSplineTransform::TCoeff
    {
        float i;
    };
    
    _TCoeff* Cx;
    _TCoeff* Cy;
    _TCoeff* Cz;
    
};

#endif	

/// @}
