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
#ifndef HX_ALIGNMENT_EVALUATOR_H
#define HX_ALIGNMENT_EVALUATOR_H

#include<mclib/McHandable.h>
#include "SliceInfo.h"

/**
 * Abstract interface for the rating of the alignment of two image slices. 
 * The rating can be calculated for different resolutions of the input fields. 
 * Resolutions are given in terms of "levels". Level 0 stands for the given image, and each subsequent
 * level cuts the width and height of the image in half, e.g., level 2 images have a fourth of the original
 * width and height. The computed quality has not to be consistent accross different image levels.
 **/
class HxAlignmentEvaluator : public McHandable {
public:
	/**
         * Sets parameters which are constant for all images in the stack.
         *
         * @param[in] width  widths of the images in the image stack.
         * @param[in] height heights of the images in the image stack.
         * @param[in] nChannels number of channels.
         */
        virtual void setImageStackParams(int width, int height, int nChannels) = 0;

        /**
         * @param[in] data data of the image 0.
         */
        virtual void setImage0(unsigned char* data) = 0;

        /**
         * @param[in] data data of image 1.
         */
        virtual void setImage1(unsigned char* data) = 0;

        /**
         * @param[in] mask for image 0.
         */
        virtual void setMask0(unsigned char* data) = 0;
        /**
         * @param[in] mask for image 1.
         */
        virtual void setMask1(unsigned char* data) = 0;

        /**
         * Measures the alignment of two image slices. The higher the quality is, the 
         * better is the match of the two images.
         *
         * @param[in] xform0
         * @param[in] xform1
         * @param[in] level
         * @return the quality of the alignment.
         */
        virtual float quality(const SliceXForm xform0, const SliceXForm xform1, int level=0) = 0;
	
        /**
         * Indicate that only level 0 will be used in the next time.
         */
        virtual void releaseSubsampled() {};
};

#endif

/// @}
