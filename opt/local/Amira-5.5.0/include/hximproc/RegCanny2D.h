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
#ifndef REG_CANNY_2D
#define REG_CANNY_2D

#include <math.h>
#include <mclib/McListQueue.h>

#include "ImConvFilter2D.h"

#define REG_HYST_MASK_SIZE 1089

/** Canny edge detector: 
    1. Application of Gauss filter.
    2. Application of Sobel filter (gradient filter).
    3. Along the gradient direction (normal to edges), a non-maximal
       suppression (thinning) is performed.
    4. A so-called "hysteresis thresholding": Edges are connected
       w.r.t. to lower and upper bounds provided by the user.
*/

class RegCanny2D : public ImConvFilter2D
{
	
    typedef enum 
    { 
        REG_NORTH_WEST = 0, 
        REG_NORTH = 1, 
        REG_NORTH_EAST = 2, 
        REG_EAST = 3
    } RegGradientDirection;

public:
    ///Constructor
    RegCanny2D(int supLength, int hystMask, int hystT2, int hystT1):
        mSuppressionLength(supLength), 
        mConnectEdgesThresholdUpper(hystT2), mConnectEdgesThresholdLower(hystT1)
    {
        mConnectEdgesMaskSize = hystMask;
        // only uneven mask sizes are valid
        if ( mConnectEdgesMaskSize < 3 )
            mConnectEdgesMaskSize = 3;
        if ( mConnectEdgesMaskSize % 2 == 0 )		  
            mConnectEdgesMaskSize++;		   
    }

    ///Destructor
    ~RegCanny2D(){}

    /** The algorithm calculates four temporary images using each of
        the kernels as parameter to ImConvFilter2D::convolve(class
        McTypedData2D*, class McTypedData2D*, float *kernel, int,
        int).  Afterwards the result is calculated taking the maximum
        of the absolute values of each temporary image.
    */
    void apply2D(class McTypedData2D* src, 
                 class McTypedData2D* dst=NULL);



private:
    void computeMaxGradientDirection(class McTypedData2D* src, class McTypedData2D* dst, short* pMaxDirection);

    template<class Type> void writeResult(  const int* dims, 
                                            Type *in_E, Type *in_N, Type *in_NE, Type *in_NW, Type *dst, short *maxDirection);


    template<class Type> void compare_NE_NW(Type *in_NE, Type *in_NW, Type *dst, RegGradientDirection &dir);

    template<class Type> void compare_N_NE_NW(Type *in_N, Type *NE_NW, RegGradientDirection &dir);

    template<class Type> void compare_E_N_NE_NW(Type *in_E, Type *N_NE_NW, RegGradientDirection &dir);


    template<class Type> void performNonmaximalSuppression(const int* dims, Type *pConvImg, short *maxDirection);

    template<class Type> void doSuppression(int i, const int* dims, Type *pConvImg, short *pMaxDirection);

    int getSuppressionLengthDiagonal()
	{
            return static_cast<int> ( mSuppressionLength * mSuppressionLength 
                                      / sqrt( pow((float)mSuppressionLength, 2) + pow((float)mSuppressionLength, 2) ) );
	}


    /// This part of the algo is sometimes called "hysteresis thresholding".
    template<class Type> void performConnectEdgesThresholding(const int* dims, Type *pEdgeMap);
	


    /// Defines the range in which non-maximal suppression is performed (pixels in normal direction).
    int mSuppressionLength;

    /// Mask size determines to which degree holes between edges are filled.
    int mConnectEdgesMaskSize;

    /// Start connecting edges from all points with value > mConnectEdgesThresholdUpper;
    int mConnectEdgesThresholdUpper;

    /** Mark points as edge, where value > mConnectEdgesThresholdLower 
        AND point within mConnectEdgesMaskSize from a point
        with value > mConnectEdgesThresholdUpper.*/
    int mConnectEdgesThresholdLower;

    /// For hysteresis thresholding: holds all point where value > mConnectEdgesThresholdUpper.
    McListQueue<int> mListTrueEdgePoints;
};

#endif

/// @}
