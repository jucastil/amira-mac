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
#ifndef HX_COLORMAP_GRADIENT_H
#define HX_COLORMAP_GRADIENT_H

#include <hxcolor/HxColormap.h>
#include <hxcolor/HxColormap256.h>

#include <mclib/McDArray.h>

/** This data class represents a color gradient.
The colors in a gradient are defined using key :
- color keys, which as a position, a color and an inflexion.
- alpha keys, which as a position, an alpha and an inflexion.
The set of key describes how the gradient area should be filled.
A diagonal linear gradient from black to white could be specified like this:

HxColormapGradient linearGrad;
linearGrad.setColorAt(0.0f, McColor(0,0,0));
linearGrad.setColorAt(1.0f, McColor(1,1,1));

Inflexion values control how interpolation increase speed: 0=highest, 1=lowest, 0.5=default
*/
class HXCOLOR_API HxColormapGradient : public HxColormap
{
    HX_HEADER(HxColormapGradient); 

public:
    struct HxColormapGradientKey
    {
        float pos, alpha, inflex;
        McColor color;

        HxColormapGradientKey(){}
        HxColormapGradientKey(float p, const McColor & c, float i) : pos(p), inflex(i), color(c) {}
        HxColormapGradientKey(float p, float a, float i) : pos(p), alpha(a), inflex(i), color(a,a,a) {}

        bool operator<( const HxColormapGradientKey & x) const { return pos < x.pos; } 
    };

    HxColormapGradient();
    HxColormapGradient(const HxColormap256 * cmap);

    /// Linearly interpolates RGBA components for @c u in 0..1.
    virtual void getRGBA1(float u, float res[4]) const;

    /// Linearly interpolates Alpha component for @c u in 0..1.
    virtual float getAlpha(float u) const;

    /// Sets a color keys at the relative position pos. The position must be in the range 0..1.
    virtual void setColor(float u, const McColor & col, float inflexion = 0.5);

    /// Sets an alpha keys at the relative position pos. The position must be in the range 0..1.
    virtual void setAlpha(float u, float alpha, float inflexion = 0.5);

    /// Remove all keys. The gradient will be white and totally opaque.(default)
    virtual void clear();

    void setColormap(const HxColormap256 * cmap);

    /// Convert gradient to an HxColormap256.
    virtual HxColormap256 * getColormap() const;
    
    virtual QPixmap getPixmap(int w, int h, int box = 4, bool showAlpha = true) const;
    
    virtual HxData* duplicate() const;

    static int readAmiraMesh(const char* filename);

    int writeGimpGradient(const char* filename);

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    virtual void info();

    const McDArray<HxColormapGradientKey> & getColorKeys() const{ return ckeys; }
    const McDArray<HxColormapGradientKey> & getAlphaKeys() const{ return akeys; }

    void getValues(McDArray<float> & values, int num = 256) const;
private:
    virtual ~HxColormapGradient();

    McDArray<HxColormapGradientKey> ckeys;  // Color keys
    McDArray<HxColormapGradientKey> akeys;  // Alpha keys
};

#endif

/// @}
