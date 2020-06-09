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
#ifndef IM_FILTER_PARAMETERS_H
#define IM_FILTER_PARAMETERS_H

#include <mclib/McString.h>
#include <mclib/McVec3f.h>

class HxPortFloatSlider;
class HxPortIntSlider;
class HxRegScalarField3;

class ImFilterParameters
{
public:

    struct SliderParam    
    {
        float smin;
        float smax;
        float svalue;
        McString format;

        void setSlider(HxPortFloatSlider *slider) const;
        void updateFrom(HxPortFloatSlider *slider);

        void setSlider(HxPortIntSlider *slider) const;
        void updateFrom(HxPortIntSlider *slider);
    };

    struct RangeParam
    {
        float rmin;
        float rmax;
    };

    /// Constructor 
    /// It initializes the parameters
    ImFilterParameters();

    /// The neighbourhood index
    /// Used in Noise reduction minimum
    /// Used in Noise reduction maximum
    int neighbourhood;

    /// The kernel size
    /// Used in Unsharp Masking
    /// Used in Noise reduction median
    /// Used in Statistical feature detection
    float kernelsize;

    /// Used in Gaussian smoothing
    /// Used in Resampling/Low pass
    McVec3f kernel;

    // The sharpness slider parameters
    /// Used in Unsharp Masking
    SliderParam sharpness;

    /// The relative sigma
    /// Used in Gaussian smoothing
    /// Used in Resampling/Low pass
    McVec3f sigmaRel;

    /// The contrast limit parameters
    /// Used in Equilize
    SliderParam contrastLimit;

    /// The stop time
    /// Used in Edge Preserving smoothing
    float timeStop;

    /// The step time
    /// Used in Edge Preserving smoothing
    float timeStep;

    /// The contrast value
    /// Used in Edge Preserving smoothing
    float contrast;

    /// The sigma value
    /// Used in Edge Preserving smoothing
    float sigma;

    /// The alpha value
    /// Used in Intensity remapping
    float alpha;

    /// The beta value
    /// Used in Intensity remapping
    float beta;

    /// The remapping range
    /// Used in Intensity remapping
    RangeParam remapping;
    
    /// The brightenss value
    /// Used in brightess & contrast
    float brightness;

    /// The contrast exponent
    /// Used in brightess & contrast
    float contrastExp;

    /// The inertia moment
    /// Used in Statistical feature detection
    int moment;

    /// The gamma
    /// Used in Lighten/Darken
    float gamma;

    /// The lighten filter range
    /// Used in Lighten/Darken
    RangeParam lighten;

    /// Noise Reduction Non-Local Means
    int window;
    int localneighbor;
    float similarity;
    int adaptive;

    HxRegScalarField3* data;
};
#endif // IM_FILTER_PARAMETERS_H

/// @}
