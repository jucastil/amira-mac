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

/// @addtogroup hxalign hxalign
/// @{
#ifndef HX_DEFAULT_ALIGNMENT_EVALUATOR_H
#define HX_DEFAULT_ALIGNMENT_EVALUATOR_H

#include "HxAlignmentEvaluator.h"
#include <hxalign/HxAlignWinDLLApi.h>

class HXALIGN_API HxDefaultAlignmentEvaluator : public HxAlignmentEvaluator {
public:
    
    HxDefaultAlignmentEvaluator();
    virtual void setImageStackParams(int width, int height, int nChannels);
    virtual void setImage0(unsigned char* data);
    virtual void setImage1(unsigned char* data);
    virtual void setMask0(unsigned char* data);
    virtual void setMask1(unsigned char* data);
    virtual void setDimensions0(int width, int height);
    virtual void setDimensions1(int width, int height);
    virtual float quality(const SliceXForm xform0, const SliceXForm xform1, int level=0);
	virtual void releaseSubsampled();

protected:
    int m_width0;
    int m_height0;
    int m_width1;
    int m_height1;

    int m_nChannels;

    unsigned char* m_data0;
    unsigned char* m_data1;

    unsigned char* m_mask0;
    unsigned char* m_mask1;

    float computeQuality(unsigned char* data1,
                         unsigned char* data2,
                         int width0,
                         int height0,
                         int width1,
                         int height1,
                         const SliceXForm& xform0,
                         const SliceXForm& xform1);

    float computeQuality(unsigned char* data1,
                         unsigned char* data2,
                         int width,
                         int height,
                         const SliceXForm& xform0,
                         const SliceXForm& xform1);

    void createSubsampledImages(int level);

    int m_cached_level;
    McDArray<unsigned char> m_cached_data[2];
    int m_cached_width0;
    int m_cached_height0;
    int m_cached_width1;
    int m_cached_height1;


};

#ifndef min 
template<class T>
T min(T arg1, T arg2) {
    return arg1 < arg2 ? arg1 : arg2;
}
#endif

#ifndef max
template<class T>
T max(T arg1, T arg2) {
    return arg1 > arg2 ? arg1 : arg2;
}
#endif



#endif

/// @}
