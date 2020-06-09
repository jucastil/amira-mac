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

/// @addtogroup hximproc hximproc
/// @{
#ifndef NLM_CPU_H
#define NLM_CPU_H

#include <mclib/McDArray.h>

class McVec3i;
class McPrimType;
class McProgressInterface;
class HxUniformScalarField3;

namespace nlm
{
    void getExtendedBlock(const McDArray<float> & inData,
                          const McVec3i & dims,
                          const McVec3i & blockDims,
                          const McVec3i & blockOffset,
                          const int searchWindowDiameter,
                          const int neighbourhoodDiameter,
                          const bool is2D,
                          McVec3i & extendedDims,
                          McVec3i & offset,
                          McDArray<float> & croppedDataBlock);

    void normalize(const void* const inField,
                   const McPrimType& primType,
                   McDArray< float >& outField,
                   const mclong nNodes,
                   float& meanValue,
                   float& standardDeviation);

    template <class PrimDataType>
    void normalize(const PrimDataType* inField,
                   McDArray< float >& outField,
                   const mclong nNodes,
                   float& meanValue,
                   float& standardDeviation);

    void undoNormalize(float* const field,
                       const mclong nNodes,
                       const float meanValue,
                       const float standardDeviation);

    void insertData(const McDArray<float>& outDataBlock,
                    const McVec3i& blockOffset,
                    const McVec3i& blockDims,
                    const McVec3i& dims,
                    void* const outData,
                    const McPrimType& primType);

    template <class PrimDataType>
    void insertFloatData(const McDArray<float>& outDataBlock,
                         const McVec3i& blockOffset,
                         const McVec3i& blockDims,
                         const McVec3i& dims,
                         PrimDataType* const outData);

    template <class PrimDataType>
    void insertIntegerData(const McDArray<float>& outDataBlock,
                           const McVec3i& blockOffset,
                           const McVec3i& blockDims,
                           const McVec3i& dims,
                           PrimDataType* const outData);

    McDArray< float > computeGaussKernel(const McVec3i window,
                                         const float sigma);
    
    void nlm(const McDArray<float> &       inData,
             const McVec3i         &       dims,
             const McVec3i         &       searchRadius,
             const McVec3i         &       neighborhoodRadius,
             const float           &       sigma,
             const bool            &       isAdaptive,
             const int             &       numThreads,
             McProgressInterface   *       progressInterface,
             float                 * const outData);

    void fixNaN(const mclong size, float* const data);

    McVec2i getRelativeStartAndEndIdx(const int & dim,
                                      const int & pos,
                                      const int & radius);

    McVec3i computeWindowRadius(const int  window,
                                const bool is2D);

    void updateProgressInterface(const float overallWork,
                                 const float currentWorkDone,
                                 McProgressInterface * progressInterface);

    bool wasInterrupted(McProgressInterface * progressInterface);
}

#endif

/// @}
