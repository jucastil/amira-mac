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
#ifndef MC_COLOR_H
#define MC_COLOR_H

#include "McWinDLLApi.h"

#include <assert.h>

#include "McDArray.h"

/** This class represents an RGB color vector. */
class MCLIB_API McColor
{
  public:
    /// The color's r component.
    float r;
    /// The color's g component.
    float g;
    /// The color's b component.
    float b;

    /// Default constructor doesn't initialize anything.
    McColor() {}

    /// Initializes color from string, see setValue for details.
    McColor(const char* text);

    /// Initializes color from multiple strings, see setValue for details.
    McColor(int n, char** argv);

    /// Constructor.
    McColor(float R, float G, float B) { setValue(R,G,B); }

    /// Constructor.
    McColor(const float rgb[3]) { setValue(rgb); }

    /// Copy constructor.
    McColor(const McColor& c) { setValue(c.r,c.g,c.b); }

    /// Assignment.
    McColor& operator=(const McColor& c) { r=c.r; g=c.g; b=c.b; return *this; }

    /// Compare operator.
    int operator==(const McColor& c) const { return r==c.r && g==c.g && b==c.b;}

    /// Compare operator.
    int operator!=(const McColor& c) const { return !(*this == c); }

    /** Initialize color from text string.<tt>"0.3 0.5 1.0"</tt>, <tt>"255 100 0"</tt>,
	or <tt>"white green black"</tt> are possible inputs.*/
    int setValue(const char* text);

    /// Concatenate multiple strings and interprete them as a color.
    int setValue(int n, char** argv);

    /// Initialize color from multiple text strings.
    int setValue(int argc, const char* const* argv);

    /// Initialize color from RGB numbers.
    void setValue(const float rgb[3]) { r=rgb[0]; g=rgb[1]; b=rgb[2]; }

    /// Initialize color from RGB numbers.
    void setValue(float rr, float gg, float bb) { r=rr; g=gg; b=bb; }

    /** Initialize color from packed RGB number.
	Red is encoded in the most significant byte, then green, blue.*/
    void setValue(unsigned int rgb);

    /// Initialize color from HSV numbers.
    void setHSVValue(const float hsv[3]) { setHSVValue(hsv[0],hsv[1],hsv[2]); }

    /// Initialize color from HSV numbers.
    void setHSVValue(float h, float s, float v);

    /// Return HSV color values.
    void getHSVValue(float hsv[3]) const { getHSVValue(hsv[0],hsv[1],hsv[2]); }

    /// Return HSV color values.
    void getHSVValue(float& h, float& s, float& v) const;

    /** Return color in packed format.
	Red is encoded in the most significant byte, then green, blue
	and alpha. If casted to (unsigned char[]), the result of course
	is byte-order dependent: On little endian(linux) c[3] will
	be red, while on big endian (sgi,...) c[0] is red.*/
    unsigned int getPackedColor(float t) const {
	return ((unsigned int)(255*r)<<24) +
	       ((unsigned int)(255*g)<<16) +
	       ((unsigned int)(255*b)<< 8) +
	       ((unsigned int)(255*(1-t)));
    }

    /// Index operator. Performs index check via assert().
    float& operator[](int i) { assert(i>=0&&i<=2); return (&r)[i]; }

    /// Const index operator. Performs index check via assert().
    const float& operator[](int i) const {assert(i>=0&&i<=2); return (&r)[i];}

    /// Sets color randomly.
    void setRandomColor();

    /** Returns a McColor with most differing color based on a RGB cube
    and a given list of already existing colors (cList).*/
    static McColor mostDifferentColorRGB( const McDArray<McColor> & cList );

    /** Returns a McColor with most differing color based on a HSV circle
    and a given list of already existing colors (cList).*/
    static McColor mostDifferentColorHSV( const McDArray<McColor> & cList );

    /** Returns an array with numColors colors, which are distributed equidistantly
    on a HSV circle. If mix is true, the colors are permuted so that neighbouring
    colors are as different as possible. */
    static McDArray<McColor> mostDifferentColorsHSV(int numColors, bool mix=false);

    /// scalar mulitiplication operator
    McColor& operator *= (const float d) { r*=d; g*=d; b*=d; return *this; } 

    /// scalar division operator
    McColor& operator/=(const float d) { r/=d; g/=d; b/=d; return *this; } 

    /// Scalar division.
    friend McColor operator/(const McColor& c, const float d)
	{ return McColor(c.r/d, c.g/d, c.b/d); }

    /// Scalar multiplication from right.
    friend McColor operator*(const McColor& c, const float d)
	{ return McColor(d*c.r, d*c.g, d*c.b); }

    /// Scalar multiplication from left.
    friend McColor operator*(const float d, const McColor& c)
	{ return McColor(d*c.r, d*c.g, d*c.b); }

    /// Addition.
    friend McColor operator+(const McColor& a, const McColor& b)
	{ return McColor(a.r+b.r, a.g+b.g, a.b+b.b); }

    static void (*getColorFromName)(float&,float&,float&,const char*);

    /** Constructs a named color using the given HTML 4 name. 
    The color is left invalid if the name cannot be parsed. 
    http://www.w3schools.com/HTML/html_colornames.asp */
    static McColor fromHtmlColorName(const char * name);

    /** Successively returns all HTML 4 colors, cycling if there are no more entries. */
    static McColor nextHtmlColor();
};

#endif

/// @}
