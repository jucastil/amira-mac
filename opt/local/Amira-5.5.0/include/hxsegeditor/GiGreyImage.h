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
#ifndef GiGREYIMAGE_H
#define GiGREYIMAGE_H

#include <mclib/McDArray.h>
#include <hxcolor/HxColormap.h>
#include "GiShape.h"
#include "HxGiWinDLLApi.h"

class GiFrameBuffer;
class GiEvent;

/** Represents a rectangular object, that can be drawn into a frame buffer.*/
class HXSEGEDITOR_API GiGreyImage : public GiShape { 

  protected:
    mculong width;
    mculong height;
    unsigned char* data8;
    unsigned int* data32;
    McDArray<float> heightScales;
    McHandle<HxColormap> colormap;
    bool mMaskingEnabled;
    bool mMaskingOverlay;
    float mMaskingWindow[2];

  public:
    /// Default constructor.
    GiGreyImage();

    /// Destructor.
    ~GiGreyImage();

    /// Position of lower left corner in framebuffer.
    McVec2i origin;

    /// Returns pointer to mapped grey image data.
    unsigned char* dataPtr8() const { return data8; }

    /// Returns pointer to mapped RGBA image data.
    unsigned int* dataPtr32() const { return data32; }

    /// Returns image size.
    McVec2i getSize() { return McVec2i(width,height); }

    /// Resets the images, frees all resources.
    void clear();

    /** Sets a colormap used for pseudo-coloring. If a colormap is set
        a colormap lookup is performed by the different setImage()
        methods declared below. If no colormap is set, a grey image
        will be produced. */
    void setColormap(HxColormap* colormap);

    void setMaskingEnabled(bool value);
    void setMaskingOverlay(bool value);

    bool maskingEnabled() const { return mMaskingEnabled; }
    bool maskingOverlay() const { return mMaskingOverlay; }

    void setMaskingWindow(float vmin, float vmax);

    const float* getMaskingWindow() const { return mMaskingWindow; }

    /// Create image from non-contigous memory using min max window.
    template<class T>
    void setImage(mculong width, mculong height, float vmin, float vmax,
        const T* image, int bytesPerPixel, mculong bytesPerLine);

    /// Define uniform scaling in y-direction.
    void setHeightScales(float scaleFactor);

    /// Define non-uniform scaling in y-direction.
    void setHeightScales(const float boxX[2], const float* coordY);
    
    /** Draw this shape into the specified frame buffer. */
    void render(GiFrameBuffer* frameBuffer, const McBox2i&);

    /** Draw this shape into the specified frame buffer.
      @return true if event has been handled by this object */
    int handleEvent(GiFrameBuffer*, McEvent* event);
    
    ///
    McBox2i getBoundingBox() {
		McBox2i bb;
		bb.setOriginAndSize(origin,McVec2i(width,height)); 
		return bb;
    }
};

#endif

/// @}
