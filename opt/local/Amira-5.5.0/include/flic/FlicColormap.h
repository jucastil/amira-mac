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

/// @addtogroup flic flic
/// @{
#ifndef FLIC_COLORMAP_H
#define FLIC_COLORMAP_H
#include <flic/HxFlicWinDLLApi.h>

extern "C" void RGB_to_HSL(const float rgb[3], float hsv[3]);
extern "C" void HSL_to_RGB(const float hsl[3], float rgb[3]);

/// Represents a colormap.
class HXFLIC_API FlicColormap {

  public:
    /** Default constructor. */
    FlicColormap() { min=0; max=1; scale=1; }

    /** Copy constructor. */
    FlicColormap(const FlicColormap& other);

    /** Destructor. */
    ~FlicColormap() { }

    /** Assignment operator. */
    void operator=(const FlicColormap& other);

    /** Return @c ith colormap entry. */
    void getColor(int i, float rgb[3]) const {
	rgb[0] = theData[i][0];
	rgb[1] = theData[i][1];
	rgb[2] = theData[i][2];
    }

    /** Interpolate color for value @f$u \in [0,1]@f$. */
    void getColor1(float u, float rgb[3]) const;

    /** Interpolate color for given value. */
    void getColor(float x, float rgb[3]) const {
	getColor1(scale*(x-min), rgb);
    }

    /** Set coordinate range. */
    void setMinMax(float min, float max);

    /** Get coordinate range. */
    void getMinMax(float& min, float& max);

    /** Returns pointer to color data. */
    float (*dataPtr())[3] { return theData; }

    /** Create grey ramp map. */
    void createGreyRamp();

    /** Create red-yellow-white map. */
    void createHotIron();

    /** Create hue ramp (red - yellow - green - magenta - blue - pink). */
    void createHueRamp();

    /** Create colormap suitable for plus-minus distinction. */
    void createBlueWhiteRed();

    /** Create rgb band */
    // void createRGBBand(int nCycles=8);

    /** Flip color map. */
    void flip(FlicColormap* result=0);

    /// Multiply each color by a constant factor.
    void multiply(float factor, FlicColormap* result=0);

    /// Apply gamma correction
    void gamma(float exp, FlicColormap* result=0);

    /** Read colormap in icol format. */
    int readIcol(const char* filename);

    /** Save colormap in icol format. */
    int writeIcol(const char* filename);

  protected:
    float theData[256][3];
    float min, max, scale;
};

#endif

/// @}
