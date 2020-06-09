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

/// @addtogroup hxcolor hxcolor
/// @{
#ifndef HX_COLORMAP256_H
#define HX_COLORMAP256_H

#include <hxcolor/HxColormap.h>

class AmiraMesh;

/** This data class represents a simple RGBA colormap. The number of
    entries is variable. For each colormap entry a RGB triple may be
    defined as well as an opacity A. All entries are stored as float
    values internally. Beside the raw RGBA values the colormap also
    stores two coordinates, defining a range used for color interpolation.
    Color lookup request for a parameter smaller than the minimum
    coordinates evaluate to the first colormap entry. Request for a
    parameter bigger than the maximum coordinate value evaluate to
    the last entry. */

class HXCOLOR_API HxColormap256 : public HxColormap {

  HX_HEADER(HxColormap256); 

  public:
    /// Types of alpha curves as used in setAlphaCurve()
    enum AlphaCurve {
        AC_SOFT_RAMP,
        AC_LINEAR,
        AC_HARD_RAMP,
        AC_GAMMA,
        AC_SAW_TOOTH
    };

    /// Default constructor.
    HxColormap256(int size = 256);

    /// Constructor.
    HxColormap256(int size, unsigned short* red, unsigned short* green,
	    unsigned short* blue, unsigned short* alpha=0);

    //@{ Access individual table entries.

    /// Returns one component of @c ith colormap entry.
    inline float getChannel(int i, int which) const {
	    return rgba[i][which];
    }

    /// Returns RGB components of @c ith colormap entry.
    inline const SbColor& getColor(int i) const {
	    return *((SbColor*)rgba[i]);
    }

    /// Returns @c ith colormap entry in packed form.
    inline unsigned int getPackedColor(int i) const {
	    return ((unsigned int)(255*rgba[i][0]) << 24) +
               ((unsigned int)(255*rgba[i][1]) << 16) +
	           ((unsigned int)(255*rgba[i][2]) << 8) +
                (unsigned int)(255*rgba[i][3]);
    }

    /// Returns @c ith colormap entry.
    inline void getRGBA(int i, float res[4]) const {
	    res[0] = rgba[i][0]; res[1] = rgba[i][1];
	    res[2] = rgba[i][2]; res[3] = rgba[i][3];
    }

    //@}

    /**name Interpolate unit coordinates */
    //@{

    /** Linearly interpolates single component for @c u in 0..1.
        If @c is lesser than 0. or greater than 1., no interpolation
        is done and the returned color is one of the 2
        colors representing the out of range color.
    */
    virtual float getChannel1(float u, int which) const;

    /** Linearly interpolates RGB components for @c u in 0..1.
        If @c is lesser than 0. or greater than 1., no interpolation
        is done and the returned color is one of the 2
        colors representing the out of range color.
    */
    virtual SbColor getColor1(float u) const;

    /** Linearly interpolates packed color for @c u in 0..1.
        If @c is lesser than 0. or greater than 1., no interpolation
        is done and the returned color is one of the 2
        colors representing the out of range color.
    */
    virtual unsigned int getPackedColor1(float u) const;

    /** Linearly interpolates RGBA components for @c u in 0..1.
        If @c is lesser than 0. or greater than 1., no interpolation
        is done and the returned color is one of the 2
        colors representing the out of range color.
    */
    virtual void getRGBA1(float u, float res[4]) const;

    /** Returns a pointer to a new allocated copy of the whole colormap
      (must be freed, not deleted) */
    float (*getWholeRGBA() const)[4];

    //@}

    /// Set colormap entry from SbColor, alpha isn't changed.
    void setColor(int i, const SbColor& color);
    
    /// Set colormap entry from float vector.
    void setRGBA(int i, const float rgbanew[4]);

    /// Set colormap entry from individual components.
    void setRGBA(int i, float r, float g, float b, float a);

    /// Set value of a particular channel of a colormap entry.
    void setChannel(int i, int channel, float v);

    /// Returns number of colormap entries.
    int getLength() const { return size; }

    /// Returns pointer to colormap data.
    float* getDataPtr() const { return (float*) rgba; }

    /// Read colormap file in icol format (always has 256 entries)
    static int readIcol(const char* filename);

    /// Read a colormap from a AmiraMesh structure.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Save in AmiraMesh format.
    int saveAmiraMesh(const char* filename);

    /// Save in IRIS Explorer format.
    int saveExplorer(const char* filename);

    /// Save in indexed icol format (no alpha!).
    int saveIndexedIcol(const char* filename);

    /// Save in non-indexed icol format (no alpha!).
    int saveNonIndexedIcol(const char* filename);

    /// Duplicates the current colormap
    virtual HxData *duplicate() const;

    /// Copies the contents of a HxColormap object
    HxColormap256& operator=(const HxColormap256& source);

    /// Equality comparison operator
    bool operator==(const HxColormap256& other) const;

    /// Equality comparison within given tolerance 
    bool equals(const HxColormap256& other, float tolerance = 1e-6f) const;

    /// Returns whether this colormap has (semi-)transparent entries.
    int isTransparent();

    /// Change number of entries, all entries are reset.
    void resize(int nSize);

    /// Convert into a piece-wise constant function with n steps.
    void makeSteps(int n);
    
    /// Whether colors should be interpolated or not.
    void setInterpolate(bool flag=true) { interpolate=flag; }

    /// Whether colors should be interpolated or not.
    int getInterpolate() const { return interpolate; }

    /// Create colormap useful for volume rendering.
    void makeVolren(const SbColor& baseColor, float power, float huewidth=0.1);

    /// Sets the opacity channel of the color map.
    void setAlphaCurve(AlphaCurve mode, float param=1.f);
    
    /// Sets a constant opacity for the color map.
    void setOpacity( float opacity );

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    virtual ~HxColormap256();

    int	size;
    float (*rgba)[4];
    bool interpolate;

    ///Get a color map index form a normalized value + the interpolation factor.
    ///Return false if the value is outside the defined data range.
    bool getColorIndex(float v, int& colorIndex, float& interpolationFactor) const;
};

#endif

/// @}
