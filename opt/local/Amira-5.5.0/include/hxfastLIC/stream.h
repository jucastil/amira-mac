/*
 *  Copyright (c) 1995 Konrad-Zuse-Zentrum fuer Informationstechnik
 *  Berlin  (ZIB). This software is provided as is without express or
 *  implied warranty. Redistribution in source or binary forms is not
 *  allowed without the permission of ZIB. All copyright notices must
 *  remain intact in all files.
 */
///////////////////////////////////////////////////////////////////
//
//  File: stream.h
//
//  Provides various streamline integrator classes
//
///////////////////////////////////////////////////////////////////
#ifndef STREAM_H
#define STREAM_H

#include <hxfastLIC/HxFastLICWinDLLApi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define DOMAINERROR  1
#define ZEROVELOCITY 2
#define SINGULARITY  3

#ifdef FASTSQRT
extern "C" { extern float fastsqrt(float val); }
#else
#define fastsqrt sqrtf
#endif

struct Vec2f
{
    float x, y;
    Vec2f() { }
    Vec2f(float xx, float yy) : x(xx), y(yy) { }
};

///////////////////////////////////////////////////////////////////
//
//  Abstract base class for all integrators
//
class HXFASTLIC_API Streamline {

  public:
    Streamline() { } 	// constructor
    ~Streamline() { }	// destructor

    // Set vector field (dimensions and coordinates)
    void setField(int Nx, int Ny, float xmax, float ymax, Vec2f* data);

    // Initialize streamline with start point r.
    // f is the derivative at this point.
    virtual void init(const Vec2f& r, const Vec2f& f) = 0;

    // Interpolate equidistant sample points. ret is false if
    // solution has been continued artifically (because a
    // singularity was encounterd or the grid domain was left)
    virtual Vec2f& next(int& ret) = 0;

  protected:
    float	hSampling;	// width for equidistant interpolation
    int		error;		// true if streamline is continued artifically
    float	orientation;	// forward or backward tracing
    int	        Nx, Ny;		// dimensions of vector field
    float	xmax, ymax;	// coordinates of upper right corner
    Vec2f*	data;		// pointer to the vector data

    // Get derivative at point r
    inline void derivs(const Vec2f& r, Vec2f& f);
};

///////////////////////////////////////////////////////////////////
//
//  Base class for all fixed stepsize integrators
//
class HXFASTLIC_API StreamFixed : public Streamline {

  public:
    StreamFixed() { }
    ~StreamFixed() { }

    void setParameters(float hSampling, int orientation);

    virtual void init(const Vec2f& r, const Vec2f& f);

  protected:
    Vec2f r, f;
};

///////////////////////////////////////////////////////////////////
//
//  Midpoint rule
//
class StreamMidpoint : public StreamFixed {

  public:
    StreamMidpoint() { }
    ~StreamMidpoint() { }

    virtual Vec2f& next(int& ret);
};

///////////////////////////////////////////////////////////////////
//
//  Euler rule
//
class StreamEuler : public StreamFixed {

  public:
    StreamEuler() { }
    ~StreamEuler() { }

    virtual Vec2f& next(int& ret);

    // This is an inline version of next()
    inline Vec2f& next2(int &ret) {
	r.x += hSampling*f.x;
	r.y += hSampling*f.y;
	derivs(r, f);
	ret = error;
	return r;
    }
};

///////////////////////////////////////////////////////////////////
//
//  Abstract base class for adaptive integrators with cubic interpolation
//
class StreamAdaptive : public Streamline {

  public:
    StreamAdaptive() { }
    ~StreamAdaptive() { }

    void setParameters(
	float _hSampling,	// width for equidistant interpolation
	float tol, 		// accuracy of integration
	float htry,		// initial step size
	float hMin,		// minimum step size (prevents dead lock)
	float hMax,		// maximum step size
	int orientation);	// forward or backward tracing

    virtual void init(const Vec2f& r, const Vec2f& f);

    virtual Vec2f& next(int& ret);

  protected:
    Vec2f 		r1;	// first point of current interval
    Vec2f 		r2;	// second point of current interval
    Vec2f 		F1;	// derivative dr1/ds
    Vec2f 		F2;	// derivative dr2/ds
    Vec2f 		f1;	// normalized derivative dr1/dt
    Vec2f 		f2;	// normalized derivative dr2/dt
    float		S1;	// accumulated arc length at r1
    float		S2;	// accumulated arc length at r2
    float		T;
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

///////////////////////////////////////////////////////////////////
//
//  RK4(3) - Fourth-order Runge-Kutta
//
class StreamRK43 : public StreamAdaptive {

  public:
    StreamRK43() { }
    ~StreamRK43() { }

  protected:
    // single forth-order Runge-Kutta step
    void rkstep(const Vec2f& r, const Vec2f& f, const float h,
	Vec2f& rnew, Vec2f& fnew, Vec2f& err);

    // forth-order Runge-Kutta step with error monitoring
    void step(const Vec2f& r, const Vec2f& f, float& h,
	float& hdid, Vec2f& rnew, Vec2f& fnew);
};

///////////////////////////////////////////////////////////////////
//
//  RK5(4) - Fith order Runge-Kutta with Cash-Karp coefficients
//
class StreamRKCK : public StreamAdaptive {

  public:
    StreamRKCK() { }
    ~StreamRKCK() { }

  protected:
    // single Cash-Karp Runge-Kutta step
    void rkck(const Vec2f& r, const Vec2f& f, const float h,
	Vec2f& rnew, Vec2f& err);

    // fith-order Runge-Kutta step with error monitoring
    void step(const Vec2f& r, const Vec2f& f, float& h,
	float& hdid, Vec2f& rnew, Vec2f& fnew);
};

///////////////////////////////////////////////////////////////////
//
//  RK5(4) - Fith order Runge-Kutta with Dormand-Prince coefficients
//
class StreamRKDP : public StreamAdaptive {

  public:
    StreamRKDP() { }
    ~StreamRKDP() { }

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

// This is true if vec is outside the vector field domain
#define isOutside(vec) \
    ((vec.x<0) || (vec.x>xmax) || (vec.y<0) || (vec.y>ymax))

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
inline void Streamline::derivs(const Vec2f& r, Vec2f& f)
{
    if (error) return; // do nothing

    if (isOutside(r)) { error = DOMAINERROR; return; }

    int i = (int) r.x;  float u = r.x - i;
    int j = (int) r.y;  float v = r.y - j;

    Vec2f g;
    interpol(i,j,u,v,g);
    float d = fastsqrt(g.x*g.x+g.y*g.y);

    if (d < 1e-10) { error = ZEROVELOCITY; return; }

    d = orientation/d;
    f.x = g.x*d;
    f.y = g.y*d;
}

// Special version for adaptive integrators
inline void StreamAdaptive::derivsN(const Vec2f& r, Vec2f& f)
{
    if (isOutside(r)) longjmp(env, DOMAINERROR);

    int i = (int) r.x;  float u = r.x - i;
    int j = (int) r.y;  float v = r.y - j;

    interpol(i,j,u,v,f);
    float d = fastsqrt(f.x*f.x+f.y*f.y);

    if (d < 1e-10) longjmp(env, ZEROVELOCITY);

    d = orientation/d;
    f.x *= d;
    f.y *= d;
}

#undef isOutside
#undef interpol

#endif
