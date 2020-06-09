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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef IMAGEFORCES_H
#define IMAGEFORCES_H
#include <mclib/McPrimType.h>
#include <mclib/McVec2f.h>
#include <mclib/McTypedData3D.h>
#include "Gi.h"
//---------------------------------------------------------------
class Gi;

/// Class for ImageForces: active contour models
class ImageForces {

public:

    /// Constructor.
    ImageForces();

    void init(McTypedData3D* image, int slice, 
        float dataWinMin, float dataWinMax, int orientation=2);
    
    /// Destructor.
    ~ImageForces();

    /// change to 2D or 3D mode
    void set3DGradient(int k);

    /// calculate 2D gradient force at position that lies in 
    /// currentSlice, additionally using gradient forces in 
    /// lower and upper slice.
    McVec2f gradForce3D(const McVec2f& position);

    ///set current slice in 3D-volume
    void setSlice(int which);

    /// evaluate gradient Field at position pos with bilinear 
    /// interpolation, is used for gradient extrapolation 
    McVec3f getInterpolated3DGradient(McVec2f pos);

    int use3DGradient;
    float* boundingBox;
    Gi*  theGi;

    //void test();

protected:

    ///calculate distances from position k to grid points
    void getReadyForBilinearInterpol(McVec2f k, int &i, int &j, 
        float &u, float &v);

    /// compute value of potential at (i,j) which is the abs of 
    /// gradient of the gauss smoothed image at (i,j)
    float calculatePotential(int i, int j, int k);

    /// get potential value at (i,j) in k or compute it if necessary
    inline short getPotential(int i, int j, int k){
        if ((potentialSlices[k])[i+dims2[0]*j] >= 0){
            return (potentialSlices[k])[i+dims2[0]*j];
        }
        else {
            (potentialSlices[k])[i+dims2[0]*j] =
                calculatePotential(i,j,k);
            return (potentialSlices[k])[i+dims2[0]*j];
        }
    }

    /// compute value of gauss filtered image at i,j
    float getConvImage(int i, int j, int k);

    /// precompute 2d and 3d gauss filter kernels
    void calculateKernel2D();
    void calculateKernel3D();

    /// evaluate 3d filter kernel at (i,j,k)
    inline float getKernel3D(int i, int j, int k){
        return kernel3D[i+ (j+k*kernelSize)*kernelSize];
    }

    /// evaluate 2d filter kernel at (i,j)
    inline float getKernel2D(int i, int j){
        return kernel2D[i+j*kernelSize];
    }

    /// evaluate image data at (i,j,k) and mirror components if 
    /// they are out of bounds
    inline float getImage(int i1, int j1, int k1) {

        if (i1<0) i1 = -i1;
        else if (i1>dims2[0]-1) i1 = 2*(dims2[0]-1)-i1;

        if (j1<0) j1 = -j1;
        else if (j1>dims2[1]-1) j1 = 2*(dims2[1]-1)-j1;

        if (k1<0) k1 = -k1;
        else if (k1>dims2[2]-1) k1 = 2*(dims2[2]-1)-k1;

        void* ptr;

        switch (orientation) {
            case 2:  ptr = imageVolume->address(i1,j1,k1); break;
            case 1:  ptr = imageVolume->address(i1,k1,j1); break;
            default: ptr = imageVolume->address(k1,i1,j1); break;
        }

        switch (imageVolume->primType()) {
            case McPrimType::mc_uint8:  return *(unsigned char*) ptr;
            case McPrimType::mc_uint16: return *(unsigned short*) ptr;
            case McPrimType::mc_int16:  return *(short*) ptr;
            case McPrimType::mc_int32:  return *(int*) ptr;
            case McPrimType::mc_float:  return *(float*) ptr;
            case McPrimType::mc_double: return *(double*) ptr;
        }

        return 0.f;
    }

    /// evaluate scaled image data at (i,j,k) and mirror components if 
    /// they are out of bounds
    inline float getImageScaled(int i1, int j1, int k1) {

        float denom = dataMax - dataMin;

        if (i1<0) i1 = -i1;
        else if (i1>dims2[0]-1) i1 = 2*(dims2[0]-1)-i1;

        if (j1<0) j1 = -j1;
        else if (j1>dims2[1]-1) j1 = 2*(dims2[1]-1)-j1;

        if (k1<0) k1 = -k1;
        else if (k1>dims2[2]-1) k1 = 2*(dims2[2]-1)-k1;

        void* ptr;

        switch (orientation) {
            case 2:  ptr = imageVolume->address(i1,j1,k1); break;
            case 1:  ptr = imageVolume->address(i1,k1,j1); break;
            default: ptr = imageVolume->address(k1,i1,j1); break;
        }

        switch (imageVolume->primType()) {
            case McPrimType::mc_uint8:  return 255*(*(unsigned char*) ptr - dataMin ) / denom;
            case McPrimType::mc_uint16: return 255*(*(unsigned short*) ptr - dataMin ) / denom;
            case McPrimType::mc_int16:  return 255*(*(short*) ptr - dataMin ) / denom;
            case McPrimType::mc_int32:  return 255*(*(int*) ptr - dataMin ) / denom;
            case McPrimType::mc_float:  return 255*(*(float*) ptr - dataMin ) / denom;
            case McPrimType::mc_double: return 255*(*(double*) ptr - dataMin ) / denom;
        }

        return 0.f;
    }

    /// calculate 2D gradient force at pos in current slice +-1
    McVec2f calculate2DGradForce(McVec2f pos, int k); 

    /// compute 2D gradient of gauss-smoothed image in 
    /// current slice +-1
    McVec2f get2DGrad(int i, int j, int k);

    /// arrays storing the gauss filter kernels
    McDArray<float> kernel2D;
    McDArray<float> kernel3D;

    /// size of gauss filter kernel
    int kernelSize;

    /// input image data
    McTypedData3D* imageVolume;

    /// size of input data in current orientation
    int dims2[3];

    ///
    int orientation;

    /// current slice in the viewer
    int currentSlice;

    /// arrays storing potential values of three currently 
    /// used neigboring slices
    McDArray<float> potentialSlices[3];

    float dataMin, dataMax;
};

#endif

/// @}
