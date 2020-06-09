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
#ifndef FLIC_IMAGE_H
#define FLIC_IMAGE_H

#include <flic/HxFlicWinDLLApi.h>
class FlicVectorField;

/** A simple image class. The class provides basic IO operations and
    image filters. Images may be grey scale or color. However, color
    images are not yet supported in all methods. */

class HXFLIC_API FlicImage {

  public:
    /** Allocates a grey image of given size. */
    FlicImage(int nx, int ny);

    /** Memory interface for grey images. A non-zero pointer @c imageData
	can be used to reference an image directly. No data is copied, no
	memory is allocated, and no memory is freed later on. */
    FlicImage(int nx, int ny, int bytesPerLine, unsigned char* imageData);
	
    /** Allocates a multi-channel image of given size. While grey images
        are represented by a single byte per pixel, color images are
	stored as a sequence of 3-byte RGB triples. */
    FlicImage(int nx, int ny, int nc);
	
    /** Memory interface for multi-channel images. A non-zero pointer
	@c imageData can be used to reference an image directly. No data is
	copied, no memory is allocated, and no memory is freed later on. */
    FlicImage(int nx, int ny, int nc, int bytesPerLine, unsigned char* data);

    /// Copy constructor.
    FlicImage(const FlicImage& other);

    /// Default constructor.
    FlicImage();

    /// Destructor.
    ~FlicImage();

    /// Assignment operator.
    void operator= (const FlicImage& other);

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

    /// Set all pixels to given value.
    void clear(int value=0);

    /** Create a random noise image. If the parameter @c binary is true,
        only the values 0 and 255 are used. Otherwise, the pixels may
	take any value in the range of 0 and 255. */
    void createRandom(int binary=1, int seed=0);

    /// Compose multi-channel image from independent greyscale images.
    int glue(const FlicImage& r, const FlicImage& g, const FlicImage& b);

    /// Zoom this image or store zoomed version in @c result.
    void zoom(int nx, int ny, FlicImage* result=0);

    void medianFilter(FlicImage* result=0);

    /// Blur this image or store blurred version in @c result.
    void gaussBlur(int size, FlicImage* result=0);

    /// General convolution with separable kernel.
    void convolve(int n, float* kernel, FlicImage* result=0);

    /// Extract given channel from a multi-channel image.
    void oneband(int channel, FlicImage* result);

    /// Enlarge contrast by stretching intensity range.
    void brighten(int black, int white, FlicImage* result=0);

    /// Apply relief filter.
    void emboss(float phi, float elevation, int width, FlicImage* result=0);
    void emboss(FlicVectorField& field, FlicImage* result=0);

    /// Flood fill algorithm.
    int floodFill(int x, int y, int newVal, int* box=0, FlicImage* result=0);

    /// Create grey scale image (uses 0.3*R+0.59*G+0.11*B).
    void colorToGrey(FlicImage* result=0);

    /** Multiply two images pixel by pixel. Pixel values are scaled to
        range 0...1 before multiplication and are scaled back to 0...255
	afterwards. */
    int multiply(const FlicImage& other, FlicImage* result=0);

    /** Apply the @c mask. The mask is applied by adding a new alpha channel
        to the current image if necessary. All pixels with a value equal to 0 
        in the @c mask will create a full transparent pixel in this image.
        @c mask must have a number of component equal to 1.
     */
    int applyMask(const FlicImage& mask, FlicImage* result=0);

    /// Mix two images.
    int mix(const FlicImage& other, FlicImage* result=0);

    /// Computes thisImage - otherImage + 128 (clamped to 0...255)
    int subtract(const FlicImage& other, FlicImage* result=0);

    /// Crop image.
    int crop(int xmin, int ymin, int xmax, int ymax, FlicImage* result=0);

    /// Computes mean and standard deviation of all pixels.
    void getStatistics(float& mean, float& standardDeviation);

    /// Rescales image histogram.
    void autoAdjust(float mean, float standardDeviation, FlicImage* result=0);

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

    unsigned char interp(float x, float y);

    unsigned char interpConst(float x, float y);

    unsigned char& value(int i, int j) {
	if (i<0) i=0;
	if (i>=nx) i=nx-1;
	if (j<0) j=0;
	if (j>=ny) j=ny-1;
	return data[j*bytesPL+i];
    }

  protected:
    unsigned char* toFree;
    unsigned char* data;
    int nx, ny, nc, bytesPL;
};

#endif

/// @}
