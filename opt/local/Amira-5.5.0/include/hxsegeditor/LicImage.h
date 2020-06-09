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
#ifndef LIC_IMAGE_H
#define LIC_IMAGE_H

#include <mclib/McBox2i.h>
#include "HxGiWinDLLApi.h"

/** A simple image class. The class provides basic IO operations and
    image filters. Images may be grey scale or color. However, color
    images are not yet supported by most methods. */
class HXSEGEDITOR_API LicImage {

  public:
    /** Memory interface for grey images. A non-zero pointer @c imageData
        can be used to reference an image directly. In this case no data
        is copied, no memory is allocated, and no memory is freed later
        on. On the other hand, if @c imageData is zero, memory for the
        image is allocated dynamically. */
    LicImage(int nx, int ny, unsigned char* imageData=0);
    LicImage(int nx, int ny, int bytesPerLine, unsigned char* imageData=0);

    /** Memory interface for multi-channel images. While grey images
        are represented by a single byte per pixel, color images are
        stored as a sequence of 3-byte RGB triples. */
    LicImage(int nx, int ny, int nc, int bytesPerLine, unsigned char* data=0);

    /// Copy constructor.
    LicImage(const LicImage& other);

    /// Default constructor.
    LicImage();

    /// Destructor.
    ~LicImage();

    /// Assignment operator.
    void operator= (const LicImage& other);

    /// Allocates memory for a vector field of given size.
    void setSize(int nx, int ny, int nc=1);

    /// Read image from pgm or ppm file.
    int readPNM(const char* filename);

    /// Write image to pgm or ppm file.
    int writePNM(const char* filename, int ascii=0);

    /// Read image from IRIS rgb file.
    int readRGB(const char* filename);

    /// Write image to IRIS rgb file (run-length encoded).
    int writeRGB(const char* filename);

    /// Make black image.
    void clear();

    /// Create random noise image using srand().
    void createRandom(int seed=0);

    /// Zoom this image or store zoomed version in @c result.
    void zoom(int nx, int ny, LicImage* result=0);

    /** Blur this image or store blurred version in @c result.
        \return returns false if not enough temporary memory could
        be allocated, returns true on success */
    bool gaussBlur(int size, LicImage* result=0);

    /** General convolution with separable kernel.
        \return returns false if not enough temporary memory could
        be allocated, returns true on success */
    bool convolve(int n, float* kernel, LicImage* result=0);

    /// General convolution, but within @c minmaxes.
    void boundedconvolve(int n, float* kernel, McBox2i& minmaxes, LicImage* result=0);

    /// Enlarge contrast by stretching intensity range.
    void brighten(int black, int white, LicImage* result=0);

    /// Flood fill algorithm.
    int floodFill(int x, int y, int newVal, int* box=0, LicImage* result=0);

    /// Create grey scale image.
    void colorToGray(LicImage* result=0);

    /// Compute the region which contains pixels of given value.
    int subBox(int& xmin, int& ymin, int& xmax, int& ymax, int v, int neq=0);

    /// Returns pointer to image data.
    unsigned char* dataPtr() const { return data; }

    /// Returns image width.
    int xSize() const { return nx; }

    /// Returns image height.
    int ySize() const { return ny; }

    /// Returns number of channels of the image.
    int nChannels() const { return nc; }

    /// Returns bytes per line.
    int bytesPerLine() const { return bytesPL; }

    int writeHistogram(const char* filename);

  protected:
    unsigned char* toFree;
    unsigned char* data;
    int nx, ny, nc, bytesPL;
};

#endif

/// @}
