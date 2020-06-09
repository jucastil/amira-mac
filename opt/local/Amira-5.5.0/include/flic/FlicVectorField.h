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
#ifndef FLIC_VECTORFIELD_H
#define FLIC_VECTORFIELD_H

#include <flic/HxFlicWinDLLApi.h>

class FlicImage;
class FlicScalarField;

/// Represents a two-dimensional vector field.

class  HXFLIC_API FlicVectorField {

  public:
    /** Memory interface. A non-zero pointer @c vectorData can be used
	to reference the vector data directly. In this case no data is
	copied, no memory is allocated, and no memory is freed later on.
	On the other hand, if @c vectorData is zero, memory for the
	field is allocated dynamically. */
    FlicVectorField(int nx, int ny, float* vectorData=0);

    /// Default constructor.
    FlicVectorField();

    /// Destructor.
    ~FlicVectorField();

    /// Allocates memory for a vector field of given size.
    void setSize(int nx, int ny);

    /** Reads a vector field from file. The file format is very simple.
	The file is expected to start with a header "FLIC VECTOR ASCII"
	or "FLIC VECTOR BINARY". The second line of the file should
	contain two ascii integer numbers @c nx and @c ny, denoting the
	x- and y-dimension of the field. Starting with the next line,
	@c nx times @c ny pairs of floating point numbers are read. These
	number may either be specified in ascii format or in 32-bit
	IEEE big-endian binary format, depending whether the header
	included the string ASCII or BINARY. The data is assumed to be in
	row order. The first vector is the one in the lower left corner. */
    int read(const char* filename);

    /// Write vector field to file
    int write(const char* filename, int ascii=0);

    /// Read triangular vector field in UCD format and resample it.
    int readUCD(const char* filename, int width, int height);

    /** Same as above but clip field with specified box. This is useful
        if only a part of the field should be visualized. */
    int readUCD(const char* filename, int width, int height, float* box);

    /** Creates a vector field from an image. The image is interpreted
        as a stream function. The vector flow is directed parallel to
	lines of equal intensity. A non-vanishing value of @c phi rotates
	the vectors. If @c phi equals pi/2 a pure gradient field is
	obtained. Often it is necessary to blur or down-zoom the image.
	Otherwise the resulting vector field will be very noisy and
	inhomogenous. */
    void fromImage(const FlicImage& image, float phi=0);

    void fromScalarField(const FlicScalarField& field, float phi=0);

    ///
    void setSaddle();

    /** Defines a circular vector field. If @c phi is zero a pure circular
        field is generated. A non-vanishing value of @c phi causes the
	vectors to be rotated towards the center. */
    void setCircle(float phi=0);

    /** This method defines the field to be a linear one Ax+b.
	The coordinates of the corners at assumed to +-2. */
    void setLinear(const float A[2][2], const float b[2]);

    /** Defines a vector field from the the so-called Brusselator system:
        vx = a + x*x*y - (b+1)*x
	vy = b*x - x*x*y
	The coordinate range starts at 0,0. The coordinates of the upper
	right corner as well as the value of the parameters a and b can
	be defined by the user. */
    void setBrusselator(float xmax=4, float ymax=5, float a=1, float b=3);

    /// Normalize all vectors to unit length.
    void normalize();

    /// Returns pointer to vector data.
    float* dataPtr() const { return data; }

    /// X-resolution of the field.
    int xSize() const { return nx; }
     
    /// Y-resolution of the field.
    int ySize() const { return ny; }

    /// Bilinear interpolation.
    inline void interp(float x, float y, float& vx, float& vy) {
	int i = (int) x;
	int j = (int) y;
	float u = x - i;
	float v = y - j;
/* CB-GKW: */
/* Absturz (DEC-Version oder LINUX mit libefence, wenn j=ny */
/* wegen Feldueberschreitung bei                            */
/* float *r00 = src; src+=2;    -> &data[2*(190*222+1)];    */
/* float *r10 = src; src+=2*nx; -> &data[2*(191*222+1)]; XX */
/* CB-GKW auskommentiert:
	float *src = &data[2*(j*nx+i)];
	float *r00 = src; src+=2;
	float *r10 = src; src+=2*nx;
	float *r11 = src; src-=2;
	float *r01 = src;
*/
/* CB-GKW neu:*/
	float *src = &data[2*(j*nx+i)];
	float *r00 = src; if (i<nx-1) src+=2;    else src-=2;
	float *r10 = src; if (j<ny-1) src+=2*nx; else src-=2*nx;
	float *r11 = src; if (i<nx-1) src-=2;    else src+=2;
	float *r01 = src;
/* CB-GKW neu (Ende) */
        vx = r00[0] + u*(r10[0] - r00[0]) + v*(r01[0] - r00[0])
		+ u*v*(r00[0] - r01[0] - r10[0] + r11[0]);

        vy = r00[1] + u*(r10[1] - r00[1]) + v*(r01[1] - r00[1])
		+ u*v*(r00[1] - r01[1] - r10[1] + r11[1]);
    }

    /** Computes the maximum vector magnitude. This can be used to control
        variable speed LIC animations. */
    float getMax();

    /** Visualize vector field by color. Directions are mapped to
        colors of the HSL color circle. */
    void vecToColor(FlicImage& result, int resize=1);

    /** Compute magnitude of vector field. If @c resize is non-zero, the
	size of the resulting scalar field is reset to match the size of
	the vector field. Otherwise, the vector field is interpolated to
	obtain magnitude at all points of the incoming scalar field. */
    void magnitude(FlicScalarField& result, int resize=1);

    /** Resample vector field to match given resolution. */
    void resample(int nx, int ny, FlicVectorField* result=0);

  protected:
    float* toFree;
    float* data;
    int nx, ny;

    static void pixelCallback(int x, int y, float* f, void* userData);
};

#endif

/// @}
