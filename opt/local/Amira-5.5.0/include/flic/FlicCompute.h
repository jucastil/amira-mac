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
#ifndef FLIC_COMPUTE_H
#define FLIC_COMPUTE_H

#include <flic/HxFlicWinDLLApi.h>
#include <mclib/McWatch.h>
#include <flic/FlicImage.h>
#include <flic/FlicIntegrator.h>
#include <flic/FlicVectorField.h>
#include <flic/FlicScalarField.h>

/// This class implements the fast line integral convolution algorithm.

class HXFLIC_API FlicCompute
{
  public:
    /// Enumeration indicating different seed point selection strategies.
    enum SeedSelection {
        /// Scanline ordering.
        S_SCANLINE,
        /// 4x4 block strategy.
        S_BLOCK4,
        /// Sobol quasi-random sequence.
        S_SOBOL
    };

    /// Enumeration indicating different filter types.
    enum FilterKernel {
        /// Box filter.
        F_BOX=0,
        /// Triangle filter.
        F_TRIANGLE,
        /// Third-order B-spline.
        F_CUBIC
    };

    /// Enumeration indicating different source interpolation methods.
    enum InterpolationMethod {
        /// Nearest-neighbour interpolation.
        I_CONSTANT,
        /// Bilinear interpolation.
        I_BILINEAR
    };

    /// Constructor.
    FlicCompute();

    /// Destructor.
    ~FlicCompute();

    /** Specifies the convolution length in pixels. Internally a symmetric
        box filter kernel of length @c 2*L+1 is used. The default value of
        @c L is 20. Higher values result in smoother images. */
    void setFilterLength(float L);

    /** Maximum filter offset in animations. In LIC animation sequences
        the filter kernels are shifted @c offset pixels from their center
        positions in both directions. The default value is 25. The larger
        the filter offset, the faster the flow appears. */
    void setOffsetLength(float offset);

    /** Sets the number of subpixels to be used. Super-sampling can be used
        to reduce alias-artifacts which otherwise might be present in LIC
        images. A value of @c n results in a @c nxn sampling mask. The
        default value is 1 (no super-sampling). */
    void setNumSubPixels(int n);

    /// Set vector field normalization.
    void setNormalization(float threshold);

    /** Sets the seed point selection strategy. */
    void setSeedSelection(SeedSelection mode);

    /** Set the type of filter kernel to be used. */
    void setFilterKernel(FilterKernel mode);

    ///
    void setInterpolationMethod(InterpolationMethod mode);

    /** Specifies simple Euler integration. Euler's method should be
        used for discontinuous or noisy vector fields. For example, such
        fields are often obtained when interpreting a arbitrary raster
        image as a stream function and computing a vector field from it. */
    void useEuler();

    /** Specifies adaptive fourth-order Runge-Kutta integration. This is
        the default. For smooth data RK43 usually is faster than simple
        Euler integration. In addition singularities, e.g. sinks or
        sources, are detected properly. The step size is adjusted to
        automatically within the range @c hMin and @c hMax. @c hTry specifies
        the initial step size. The values correpsond to cells widths in
        the vector field. The default values are 4, 0.5, 25, and 0.005. */
    void useRK43(float hTry, float hMin, float hMax, float tolerance);

    /** Compute a static LIC image. @c input is the input image to be
        convolved. Usually this is a random noise image, but any other
        type of image can be used as well. The resulting LIC image is
        stored in @c output. The size of the output image is automatically
        adjusted to the size of the input image. The resolution of the
        vector field is totally independent from this. Ignoring aspect
        ratios, the vector field is assumed to cover the whole input
        image. Convolution of color images is supported.
        Optionally, during computation, an image transformation can be done from
        field space to resulting image space. It can be useful to convert mask from one space to another.
        In this case @c imageInFieldSpace is the input image and @c imageInOutputSpace is the image transformed
        into the @c output space.*/
    int compute(FlicVectorField* field, FlicImage* input, FlicImage* output, 
                FlicImage* imageInFieldSpace=0, FlicImage* imageInOutputSpace = 0);

    /** Compute a periodic constant speed LIC animation. The @c field and
        @c input parameters have the same meaning as in the ordinary
        @c compute() method. Instead of a single image, @c nFrames are
        computed by shifting the LIC filter kernel in time. The sizes
        of all output images are adjusted automatically. To obtain a
        periodic animation sequence, a special blending technique is
        applied. Note, that for random noise input the grey values of the
        convolved images are distributed gaussian. If @c adjustContrats is
        true intensities of the output images are rescaled so that the
        histograms look similar and all images have equal contrast.  The
        method assumes that the mean gray value of the input noise is
        centered around 128. Color images are not supported yet. */
    int compute(FlicVectorField* field, FlicImage* input,
    int nFrames, FlicImage** output);

    /** Computes a periodic variable speed LIC animation. No color yet. */
    int compute(FlicVectorField* field, FlicImage* input,
    int nFrames, FlicImage** output, FlicScalarField* velocity);

    /// Returns accumulated user and system time of last LIC computation.
    float getTime() { return watch.getTime(); }

  protected:
    float m_filterLength;	// Size of filter kernel in pixels
    float m_updateLength;	// Size of update interval in pixels
    float m_hSampling;		// Stepsize for texture sampling
    float m_offsetLength;	// Maximum filter offset in animation
    float m_normalize;
    int	m_numSubPixels;
    FilterKernel m_filterKernel;
    SeedSelection m_seedSelection;
    InterpolationMethod m_interpolationMethod;

    int     nx, ny, nc;		// Number of image pixels in x and y
    float   xmax, ymax;		// Used for domain adjustment
    float   xscale, yscale;  	// Coordinate transformation
    int     filterSize;		// Size of filter kernel in steps
    int     updateSize;		// How many steps to proceed along a line
    int     filterOffset;	// Filter offset in samples
    int	    bufferSize;		// Size of stream line buffer
    int     iBufferTab;
    int     numSubPixels2;
    int	    numHits;
    int     numStreamlines;

    FlicVectorField* field;
    FlicImage* input;
    FlicIntegrator* forward;
    FlicIntegrator* backward;
    int* ibuffer;
    int* fbuffer[2];

    struct SBuffer {
        int adr;
        int subpixel;
        int err;
    } *sbuffer;

    struct { int nNew, nAll; } zaehlrohr[256];

    void (*getPixel)(FlicImage*, float x, float y, int* values);
    static void getPixelConstN(FlicImage*, float x, float y, int* values);
    static void getPixelConst1(FlicImage*, float x, float y, int* values);
    static void getPixelBilinearN(FlicImage*, float x, float y, int* values);
    static void getPixelBilinear1(FlicImage*, float x, float y, int* values);

    McWatch watch;

    void start(FlicVectorField* vectorField, FlicImage* inputImage);
    void stop();
    void sample(const Vec2f& r);
    void evalZaehlrohr();

    inline int getHitCount(int i, int j, int subpixel) {
        return ibuffer[(j*nx+i)*iBufferTab+subpixel];
    }

    inline void addSample(int addr, int subpixel, int*& values) {
        ibuffer[addr*iBufferTab+subpixel]++;
        values = &ibuffer[addr*iBufferTab+numSubPixels2];
    }

    inline int getIndex(Vec2f& vec, int doBoundCheck) {
        if (doBoundCheck) {
            Vec2f tmp = vec; // preserve vec
            if (tmp.y < 0) tmp.y += ymax;
            else if (tmp.y > ymax) tmp.y -= ymax;
            if (tmp.x < 0) tmp.x += xmax;
            else if (tmp.x > xmax) tmp.x -= xmax;
            return ((int)(yscale*tmp.y))*nx + (int)(xscale*tmp.x);
        }
        return ((int)(yscale*vec.y))*nx + (int)(xscale*vec.x);
    }

    inline void getIndex(Vec2f& vec, int& idx, int& subPixel) {
        Vec2f tmp = vec;
        if (tmp.y < 0) tmp.y += ymax;
        else if (tmp.y > ymax) tmp.y -= ymax;
        if (tmp.x < 0) tmp.x += xmax;
        else if (tmp.x > xmax) tmp.x -= xmax;

        int j = (int)(yscale*tmp.y);
        int i = (int)(xscale*tmp.x);
        idx = j*nx+i;

        j = (int)(m_numSubPixels*yscale*tmp.y) % m_numSubPixels;
        i = (int)(m_numSubPixels*xscale*tmp.x) % m_numSubPixels;
        subPixel = j*m_numSubPixels+i;
    }

    inline int getIndexNoCheck(const Vec2f& vec) {
        return ((int)(yscale*vec.y))*nx + (int)(xscale*vec.x);
    }

    static const int offset[16][2];
};

#endif

/// @}
