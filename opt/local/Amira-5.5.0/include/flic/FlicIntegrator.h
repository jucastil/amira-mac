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
#ifndef FLIC_INTEGRATOR_H
#define FLIC_INTEGRATOR_H

#include <flic/HxFlicWinDLLApi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include <mclib/McStdlib.h>

#define DOMAINERROR  1
#define ZEROVELOCITY 2
#define SINGULARITY  3

#if defined __sun || defined HX_OS_MACX
#define sqrtf sqrt
#endif

struct Vec2f
{
    float x, y;
    Vec2f() { }
    Vec2f(float xx, float yy) : x(xx), y(yy) { }
};

/// Abstract base class for 2D ODE integrators.
class HXFLIC_API FlicIntegrator {

  public:
    /// Constructor.
    FlicIntegrator() { normalize=0; }

    virtual ~FlicIntegrator();

    /// Set vector field (dimensions and coordinates)
    void setField(int Nx, int Ny, Vec2f* data);

    /// Set sampling width.
    void setSamplingWidth(float val) { hSampling = val; }

    /// Select forward or backward integration.
    void setOrientation(int val) { orientation = (float) val; }

    void setNormalization(float val) { normalize = val; }

    /** Initialize integrator with derivative f at start point r. If the
        integrator is configured for backward integration, the vector f is
        automatically multiplied by -1. */
    virtual void init(const Vec2f& r, const Vec2f& f) = 0;

    /** Interpolate equidistant sample points. @c ret is false if
        solution has been continued artifically because a
        singularity was encounterd or the grid domain was left. */
    virtual Vec2f& next(int& ret) = 0;

    /** Use this method, if vector magnitude is to be interpolated. */
    virtual void init(const Vec2f& r, const Vec2f& f, float mag) = 0;

    /** Step forward and compute vector magnitude at new position. */
    virtual Vec2f& next(float& mag, int& ret) = 0;

  protected:
    float   hSampling;   // width for equidistant interpolation
    int     error;       // true if streamline is continued artifically
    float   orientation; // forward or backward tracing
    int     Nx, Ny;  // dimensions of vector field
    float   xmax, ymax;  // coordinates of upper right corner
    Vec2f*  data;        // pointer to the vector data
    float   mag;         // Vector magnitude
    float   normalize;

    // Get derivative at point r
    inline void derivs(const Vec2f& r, Vec2f& f);

    // This is true if vec is outside the vector field domain
    bool isOutside(const Vec2f& vec)
    {
        return !(vec.x>=0 && vec.x<=xmax && vec.y>=0 && vec.y<=ymax);
    }

};

/// Base class for fixed step size integrators.
class HXFLIC_API FixedIntegrator : public FlicIntegrator {

  public:
    ///
    FixedIntegrator() { }

    ///
    virtual void init(const Vec2f& r, const Vec2f& f);

    ///
    virtual void init(const Vec2f& r, const Vec2f& f, float mag);

  protected:
    Vec2f r, f;
};

/// Midpoint rule.
class Midpoint : public FixedIntegrator {

  public:
    /// Constructor.
    Midpoint(int ori) { orientation = (float) ori; }

    ///
    virtual Vec2f& next(int& ret);

    ///
    virtual Vec2f& next(float& mag, int& ret);
};

/// Euler rule.
class Euler : public FixedIntegrator {

  public:
    ///
    Euler(int ori) { orientation = (float) ori; }

    ///
    virtual Vec2f& next(int& ret);

    ///
    virtual Vec2f& next(float& mag, int& ret);
};

/// Abstract base class for adaptive integrators with cubic interpolation.
class AdaptiveIntegrator : public FlicIntegrator {

  public:
    ///
    AdaptiveIntegrator() { }

    ///
    virtual void init(const Vec2f& r, const Vec2f& f);

    ///
    virtual void init(const Vec2f& r, const Vec2f& f, float mag);

    ///
    virtual Vec2f& next(int& ret);

    ///
    virtual Vec2f& next(float& mag, int& ret);

  protected:
    Vec2f 		r1;	// first point of current interval
    Vec2f 		r2;	// second point of current interval
    Vec2f 		F1;	// derivative dr1/ds
    Vec2f 		F2;	// derivative dr2/ds
    Vec2f 		f1;	// normalized derivative dr1/dt
    Vec2f 		f2;	// normalized derivative dr2/dt
    float		S1;	// accumulated arc length at r1
    float		S2;	// accumulated arc length at r2
    float		T, m1, dm0, dm1;
    Vec2f		a, b, c, d;
    Vec2f		d0, d1, d2, d3;

    float		tol;	// accuracy
    float		htry;	// initial step size
    float		h;	// current step size
    float		hMin;	// minimum step size
    float		hMax;	// maximum step size
    int			euler;  // do Euler integration ?
    jmp_buf		env;	// needed by setjmp and longjmp

    // step forward as far as possible
    virtual void step(const Vec2f& r, const Vec2f& f, float& h,
	float& hdid, Vec2f& rnew, Vec2f& fnew) = 0;

    inline void derivsN(const Vec2f& r, Vec2f& f);
};

/// RK4(3) - Fourth-order Runge-Kutta
class RK43 : public AdaptiveIntegrator {

  public:
    ///
    RK43(
	float tol, 		// accuracy of integration
	float htry,		// initial step size
	float hMin,		// minimum step size (prevents dead lock)
	float hMax,		// maximum step size
	int orientation);	// forward or backward tracing

  protected:
    // single forth-order Runge-Kutta step
    void rkstep(const Vec2f& r, const Vec2f& f, const float h,
	Vec2f& rnew, Vec2f& fnew, Vec2f& err);

    // forth-order Runge-Kutta step with error monitoring
    void step(const Vec2f& r, const Vec2f& f, float& h,
	float& hdid, Vec2f& rnew, Vec2f& fnew);
};

///  RK5(4) - Fith order Runge-Kutta with Cash-Karp coefficients
class RKCK : public AdaptiveIntegrator {

  public:
    RKCK(
	float tol, 		// accuracy of integration
	float htry,		// initial step size
	float hMin,		// minimum step size (prevents dead lock)
	float hMax,		// maximum step size
	int orientation);	// forward or backward tracing

  protected:
    // single Cash-Karp Runge-Kutta step
    void rkck(const Vec2f& r, const Vec2f& f, const float h,
	Vec2f& rnew, Vec2f& err);

    // fith-order Runge-Kutta step with error monitoring
    void step(const Vec2f& r, const Vec2f& f, float& h,
	float& hdid, Vec2f& rnew, Vec2f& fnew);
};

///  RK5(4) - Fith order Runge-Kutta with Dormand-Prince coefficients
class RKDP : public AdaptiveIntegrator {

  public:
    RKDP(
	float tol, 		// accuracy of integration
	float htry,		// initial step size
	float hMin,		// minimum step size (prevents dead lock)
	float hMax,		// maximum step size
	int orientation);	// forward or backward tracing

  protected:
    // single Dormand-Prince Runge-Kutta step
    void rkdp(const Vec2f& r, const Vec2f& f, const float h,
	Vec2f& rnew, Vec2f& fnew, Vec2f& err);

    // fith-order Runge-Kutta step with error monitoring
    void step(const Vec2f& r, const Vec2f& f, float& h,
	float& hdid, Vec2f& rnew, Vec2f& fnew);
};

///////////////////////////////////////////////////////////////////
//
//  Implementation of inline methods follows
//
///////////////////////////////////////////////////////////////////



// Bilinear interpolation
#define interpol(i,j,u,v,res) {         \
    Vec2f* src = &data[(j)*Nx+i];       \
    Vec2f r00 = *src++;                 \
    Vec2f r10 = *src; src += Nx;        \
    Vec2f r11 = *src--;                 \
    Vec2f r01 = *src;                   \
    res.x = r00.x + (u)*(r10.x - r00.x) + (v)*(r01.x - r00.x) + \
        (u)*(v)*(r00.x - r01.x - r10.x + r11.x);                \
    res.y = r00.y + (u)*(r10.y - r00.y) + (v)*(r01.y - r00.y) + \
        (u)*(v)*(r00.y - r01.y - r10.y + r11.y);                \
}

// Compute derivative. In case of an error f is preserved.
inline void FlicIntegrator::derivs(const Vec2f& r, Vec2f& f)
{
    if (error) return;
    if (isOutside(r)) { error = DOMAINERROR; return; }

    int i = (int) r.x;  float u = r.x - i;
    int j = (int) r.y;  float v = r.y - j;

    Vec2f g;
    interpol(i,j,u,v,g);

    mag = (float) sqrtf(g.x*g.x+g.y*g.y);
    if (mag < 1e-10 || MC_isnan(mag)) {
	error = ZEROVELOCITY;
	return;
    }

    float d;
    if (mag > normalize)
	d = orientation/mag;
    else 
	d = orientation/normalize;

    f.x = g.x*d;
    f.y = g.y*d;
}

// Special version for adaptive integrators
inline void AdaptiveIntegrator::derivsN(const Vec2f& r, Vec2f& f)
{
    if (isOutside(r)) longjmp(env, DOMAINERROR);

    int i = (int) r.x;  float u = r.x - i;
    int j = (int) r.y;  float v = r.y - j;

    interpol(i,j,u,v,f);

    if (MC_isnan(f.x) || MC_isnan(f.y))
    {
        f.x = 0.0f;
        f.y = 0.0f;
        longjmp(env, ZEROVELOCITY);
    }

    mag = (float) sqrtf(f.x*f.x+f.y*f.y);
    if (mag < 1e-10) longjmp(env, ZEROVELOCITY);

    float d;
    if (mag > normalize)
	d = orientation/mag;
    else 
	d = orientation/normalize;

    f.x *= d;
    f.y *= d;
}

#undef interpol

#endif

/// @}
