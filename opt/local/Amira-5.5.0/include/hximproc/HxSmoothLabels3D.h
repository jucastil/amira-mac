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
#ifndef HxSmoothLabels3D_H
#define HxSmoothLabels3D_H
#include <qobject.h>

#include <hxfield/HxFieldWinDLLApi.h>
#include <mclib/McDArray.h>
#include <mclib/McProgressInterface.h>
#include <mclib/McBox2i.h>
#include <mclib/McBitfield.h>

class QRadioButton;
class QLineEdit;
class HxLattice3;


/** This class smoothes a label field */
template<class T>
class HxSmoothLabels3D {

 public:
    
    /** constructor 
        \param Lattice lattice 
        \param nMaterials no of materials
	    \param labels pointer to labels 
        \param weights pointer to weights 
        \param smoothMatWeights pointer to weights for smooth material (optional)
        \param smoothMat id of smooth material (optional) */
    HxSmoothLabels3D(HxLattice3*, 
		     int nMaterials,
		     T* labels, 
		     unsigned char* weights,
             unsigned char* smoothMatWeights=0,
             int smoothMat=0);
    
    /** starts the smoothing \param kernelSize size of Gaussian kernel
        \param isLocked field of locked bits
        \param progress optional progress bar */
    void smoothAll(float kernelSize, int constrainLabels, 
		   McBitfield& isLocked,
		   McProgressInterface* progress=0);

private:

    HxLattice3* result;
    T* labels;
    unsigned char* weights;
    // optional: label of selected material for which a smooth surface
    // should be generated
    int const mSmoothMat;
    // optional: special weights for selected smooth material
    unsigned char* const mSmoothMatWeights;
    const int nMat;
    const int sizeType;

    int constrained;

    unsigned int mNumThreads;

    bool mParallelMaterials;
    int mNumBuffers;

    void CopyAndSmoothMat(T* src, unsigned char** temp,
		       float* kernel, int kernelSize, int slice, int mat,
		       unsigned char** buffer,
		       McBitfield& isLocked);

    void CopyAndSmooth(T* src, unsigned char** temp,
		       float* kernel, int kernelSize, int slice, 
		       unsigned char** buffer,
		       McBitfield& isLocked);

    void fast3DSmooth(int kernelSize, float* kernel,
		      McBitfield& isLocked, 
		      McProgressInterface* progress=0);

    void computeSlice(int slice, unsigned char** temp0,
		      unsigned char** temp1, unsigned char** temp2,
		      McDArray<McBox2i> &boxes0,McDArray<McBox2i> &boxes1,
		      McDArray<McBox2i> &boxes2,
		      McBitfield& isLocked,
              T* orgLabels);

    void createKernel(float kernelSize, float* kernel);

    McDArray<McDArray<McBox2i > > minmaxes;
    McDArray<McDArray<T > > matFlag;
    McDArray<McBox2i> maxboxes;    

};



#include <hximproc/HxSmoothLabels3D_impl.h>








#endif

/// @}
