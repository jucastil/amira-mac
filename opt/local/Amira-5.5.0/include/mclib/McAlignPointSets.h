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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_ALIGNPOINTSETS_H
#define MC_ALIGNPOINTSETS_H

#include "McWinDLLApi.h"

class McVec3f;
class McMat4f;
template<class T> class McDMatrix;

/** \file
    \brief Provides routines for aligning two corresponding sets of points.

    Several methods @c mcAlignPointSets are provided which perform the
    task of least squares fitting two point sets, i.e. a rotation
    matrix is computed that transforms a given set of source points
    such that it best approximates a given set of target points in the
    sense of minimum sum of squared distances between corresponding
    points. A correspondence between target and source points must be
    given, either indirectly by the sequence of coords or directly by
    additional arrays containing the corresponding indices of the
    coords. Since pointers to all arrays are used, the number @c n of
    corresponding points pairs must be given.

    The resulting rotation matrix @c transform is passed by reference.
    In addition, the transformation matrix @c targetTransform of the
    target point set can be passed to the methods, and will be
    multiplied with the matrix @c transform such that the source
    point set best fits the transformed target point set.

    Two functions allow to assign weights to the given points to
    stress the importance of some points while others may be degraded.
 */
//@}

/// Computes the optimal alignment of n indexed points with weights.
MCLIB_API void mcAlignPointSets(McMat4f & transform,
                                const McVec3f * targetCoords,
                                const McVec3f * sourceCoords,
                                const int     * targetCoordIds,
                                const int     * sourceCoordIds,
                                const float   * targetWeights,
                                const float   * sourceWeights,
                                int       n,
                                int       trafoType=0, // rigid=0, rigid+uniform scale=1, affine=2
                                const McMat4f * targetTransform=0);

/// Computes the optimal alignment of n indexed points with weights. Weights are meant for pairs of atoms.
MCLIB_API void mcAlignPointSets(McMat4f & transform,
                                const McVec3f * targetCoords,
                                const McVec3f * sourceCoords,
                                const int     * targetCoordIds,
                                const int     * sourceCoordIds,
                                const float   * weights,
                                int       n,
                                int       trafoType=0, // rigid=0, rigid+uniform scale=1, affine=2
                                const McMat4f * targetTransform=0);

/// Computes the optimal alignment of n indexed points.
MCLIB_API void mcAlignPointSets(McMat4f & transform,
                                const McVec3f * targetCoords,
                                const McVec3f * sourceCoords,
                                const int     * targetCoordIds,
                                const int     * sourceCoordIds,
                                int       n,
                                int       trafoType=0, // rigid=0, rigid+uniform scale=1, affine=2
                                const McMat4f * targetTransform=0);

/// Computes the optimal alignment of n points with weights.
MCLIB_API void mcAlignPointSets(McMat4f & transform,
                                const McVec3f * targetCoords,
                                const McVec3f * sourceCoords,
                                const float   * targetWeights,
                                const float   * sourceWeights,
                                int       n,
                                int       trafoType=0, // rigid=0, rigid+uniform scale=1, affine=2
                                const McMat4f * targetTransform=0);

/// Computes the optimal alignment of n points, constrained to a rotation around rotCenter, with weights.
MCLIB_API void mcAlignPointSets(McMat4f & transform,
                                const McVec3f * targetCoords,
                                const McVec3f * sourceCoords,
                                const float   * targetWeights,
                                const float   * sourceWeights,
                                int       n,
                                const McVec3f rotCenter,
                                int       trafoType=0, // rigid=0, rigid+uniform scale=1, affine=2
                                const McMat4f * targetTransform=0);

/// Computes the optimal alignment of n points with weights. Weights are meant for pairs of atoms.
MCLIB_API void mcAlignPointSets(McMat4f & transform,
                                const McVec3f * targetCoords,
                                const McVec3f * sourceCoords,
                                const float   * weights,
                                int       n,
                                int       trafoType=0, // rigid=0, rigid+uniform scale=1, affine=2
                                const McMat4f * targetTransform=0);

/// Computes the optimal alignment of n points.
MCLIB_API void mcAlignPointSets(McMat4f & transform,
                                const McVec3f * targetCoords,
                                const McVec3f * sourceCoords,
                                int       n,
                                int       trafoType=0, // rigid=0, rigid+uniform scale=1, affine=2
                                const McMat4f * targetTransform=0);

MCLIB_API void mcCompRigidTransform(const McDMatrix<float> &X1,
                                    const McDMatrix<float> &X2,
                                    const McVec3f &ca, const McVec3f &cb,
                                    McMat4f &transform,
                                    int withScaling = 0);

MCLIB_API void mcCompAffineTransform(const McDMatrix<float> &X1,
                                     const McDMatrix<float> &X2,
                                     const McVec3f &ca, const McVec3f &cb,
                                     McMat4f &transform);

//@{

#endif

/// @}
