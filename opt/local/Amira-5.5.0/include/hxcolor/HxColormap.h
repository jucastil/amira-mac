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
#ifndef HX_COLORMAP_BASE_H
#define HX_COLORMAP_BASE_H

#include <hxcolor/HxColorWinDLLApi.h>
#include <hxcolor/HxEditMinMax.h>

#include <hxcore/HxData.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>

#include <mclib/McColor.h>
#include <Inventor/SbColor.h>

#include <mclib/McDArray.h>

class QMenu;
class QPixmap;
class McVec4f;

/** Base class for Amira colormaps. A colormap is a function which
    defines RGBA values for numbers between 0 and 1. For convenience,
    the range 0...1 can be mapped to xmin...xmax, where xmin and xmax
    are arbitrary user-supplied coordinates.

    Several methods are provided, allowing to access color values in
    different formats. However, derived classes merely have to 
    implement the method <tt>void getRGBA1(float u, float rgba[4])</tt> in
    order to define a new colormap. The default implementation of
    all other methods rely on this one.
*/

class HXCOLOR_API HxColormap : public HxData {

    HX_ABSTRACT_HEADER(HxColormap);

  public:
    /// Enumeration type for color channels.
    enum {
        /// Red channel.
        RED=0,
        /// Green channel.
        GREEN=1,
        /// Blue channel.
        BLUE=2,
        /// Alpha channel (0=transparent, 1=opaque).
        ALPHA=3
    };

    /// Constructor.
    HxColormap();

    /// Returns lower limit of coordinate range.
    float minCoord() const { return theMin; }

    /// Return upper limit of coordinate range.
    float maxCoord() const { return theMax; }
    
    /// Set coordinate range
    void setMinMax(float min, float max);

    /// Returns whether colormap has (semi-)transparent entries.
    virtual int isTransparent();

    /**name Interpolate unit coordinates */
    //@{

    /// Linearly interpolates single component for @c u in 0..1.
    virtual float getChannel1(float u, int which) const;

    /// Linearly interpolates RGB components for @c u in 0..1.
    virtual SbColor getColor1(float u) const;

    /// Returns McColor instead of SbColor.
    McColor getMcColor1(float u) const { return McColor(getColor1(u).getValue()); }

    /// Linearly interpolates packed color for @c u in 0..1.
    virtual unsigned int getPackedColor1(float u) const;

    /** Linearly interpolates RGBA components for @c u in 0..1.
        Overload this method in derived colormap classes! */
    virtual void getRGBA1(float u, float res[4]) const;

    //@}

    /**@name Interpolate arbitrary coordinates */
    //@{

    /// Linearly interpolates a single component.
    float getChannel(float x, int which) const {
        return getChannel1((x-theMin)*theScale, which);
    }

    /// Linearly interpolates color corresponding to @c x.
    SbColor getColor(float x) const {
        return getColor1((x-theMin)*theScale);
    }

    /// Returns McColor instead of SbColor.
    McColor getMcColor(float x) const { return McColor(getColor(x).getValue()); }

    /// Linearly interpolates packed color corresponding to @c x.
    unsigned int getPackedColor(float x) const {
        return getPackedColor1((x-theMin)*theScale);
    }

    /// Linearly interpolates RGBA components corresponding to @c x.
    void getRGBA(float x, float res[4]) const {
        getRGBA1((x-theMin)*theScale, res);
    }

    //@}

    /// Port displaying colormap and min max values.
    HxEditMinMax editMinMax;
    
    /// Port for Data defining min max of color map
    HxConnection Dataport; 

    /// Options for dynamic color maps (const min/max, data dependent min/max)
    HxPortRadioBox Flags;

    /// Scaling factors for min and max
    HxPortFloatSlider ScaleCenter, ScaleSize;
  
    /// Update method, shows or hides ports, updates min max values.
    virtual void update();

    /// Saves the ports of a colormap object.
    void savePorts(FILE* fp);
        
    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Assignment operator.
    HxColormap& operator=(const HxColormap& source);

    /// Equality operator
    bool operator==(const HxColormap& other) const;

    /** Returns pixmap representing the colormap. If showAlpha is true the
        colormap is rendered on top of a checkerboard background. box
        indicates the size of the checkerboard pattern in pixels. */
    virtual QPixmap getPixmap(int w, int h, int boxWidth = 4, bool showAlpha = true) const;

    /** Returns a pixmap representing the colormap defined by rgba. The
        vector rgba must have w entries (one per column). */ 
    static QPixmap getPixmap(int w, int h, int boxWidth, bool showAlpha, const McVec4f* rgba);

    /// This function is obsolete. It is provided to keep old source working.
    virtual QPixmap* getPixmap();

    /// This method is called after a downstream object is connected to the object.
    virtual void notifyConnect(HxConnection*);

	/// Colormaps are color in the pool.
	virtual McColor getIconColor();

  protected:
    virtual ~HxColormap();

    /** This method writes a command sequence to @c fp which, when executed,
    creates this object and sets its ports. The default implementation 
    simply calls the following methods saveCreation, savePorts... */
    virtual void saveState(FILE* fp, const char* dataDir, int saveFlags);


    float theMin, theMax, theScale; // coordinates
    QPixmap* pixmap;
};

#endif

/// @}
