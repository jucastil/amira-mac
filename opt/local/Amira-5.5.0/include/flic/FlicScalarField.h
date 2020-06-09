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
#ifndef FLIC_SCALARFIELD_H
#define FLIC_SCALARFIELD_H

#include <flic/HxFlicWinDLLApi.h>

class FlicImage;
class FlicColormap;

/// Represents a two-dimensional scalar field.

class HXFLIC_API FlicScalarField {

  public:
    /** Memory interface. A non-zero pointer @c data can be used
	to reference the data directly. In this case no data is
	copied, no memory is allocated, and no memory is freed later on.
	On the other hand, if @c data is zero, memory for the
	field is allocated dynamically. */
    FlicScalarField(int nx, int ny, float* data=0);

    /// Default constructor.
    FlicScalarField();

    /// Destructor.
    ~FlicScalarField();

    /// Allocates memory for a vector field of given size.
    void setSize(int nx, int ny);

    /** Reads a scalar field from file.  The file format is very simple.
        The file is expected to start with a header "FLIC SCALAR ASCII"
        or "FLIC SCALAR BINARY". The second line of the file should
        contain two ascii integer numbers @c nx and @c ny, denoting the
        x- and y-dimension of the field. Starting with the next line,
        @c nx times @c ny floating point numbers are read. These numbers may
	either be specified in ascii format or in 32-bit IEEE big-endian
	binary format, depending whether the header included the string
	ASCII or BINARY. The data is assumed to be in row order. The first
	scalar value is the one in the lower left corner. */
    int read(const char* filename);

    /// Write field in ascii format.
    int write(const char* filename, int ascii=0);

    /// Read triangular vector field in UCD format and resample it.
    int readUCD(const char* filename, int width, int height);

    /** Creates a circular data field. */
    void createCircle();

    /** Create a dipole field. */
    void createDipole(float range=2, float time=0);

    /** Visualize scalar field using pseudo-coloring. */
    void pseudoColor(const FlicColormap& colormap, FlicImage& result,
	int resize=1);

    /// Returns pointer to data.
    float* dataPtr() const { return data; }

    /// X-resolution of the field.
    int xSize() const { return nx; }
     
    /// Y-resolution of the field.
    int ySize() const { return ny; }

    /// Bilinear interpolation.
    inline void interp(float x, float y, float& res) {
	int i = (int) x;
	int j = (int) y;
	float u = x - i;
	float v = y - j;
	float* src = (float*) data + j*nx+i;
	float& r00 = *src; if (i<nx-1) src++;   else src--;
	float& r10 = *src; if (j<ny-1) src+=nx; else src-=nx;
	float& r11 = *src; if (i<nx-1) src--;   else src++;
	float& r01 = *src;
        res = r00 + u*(r10-r00) + v*(r01-r00) + u*v*(r00-r01-r10+r11);
    }

    /** Computes the minimum and maximum data values. */
    void getRange(float& min, float& max);

  protected:
    float* toFree;
    float* data;
    int nx, ny;

    static void pixelCallback(int x, int y, float* f, void* userData);
};

#endif

/// @}
