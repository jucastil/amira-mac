/*
 *  Copyright (c) 1995 Konrad-Zuse-Zentrum fuer Informationstechnik
 *  Berlin  (ZIB). This software is provided as is without express or
 *  implied warranty. Redistribution in source or binary forms is not
 *  allowed without the permission of ZIB. All copyright notices must
 *  remain intact in all files.
 */
///////////////////////////////////////////////////////////////////////
//
// Global declarations and inline functions for fastLIC library
//
///////////////////////////////////////////////////////////////////////
#ifndef GLOBAL_H
#define GLOBAL_H

#include <hxfastLIC/HxFastLICWinDLLApi.h>
#include "stream.h"
#include "fastLIC.h"

typedef unsigned char byte;

class HXFASTLIC_API FastLIC
{
  public:
    FastLIC();

    float   FilterLength;	// Size of filter kernel
    float   StreamlineLength;	// Limit for convolution update
    float   HSampling;		// Stepsize for texture sampling
    float   Tolerance;		// Specifies required accuracy
    float   HTry;		// Initial stepsize
    float   HMin;		// Minimum stepsize
    float   HMax;		// Maximum stepsize
    int     Seed;		// Seed for random number generator
    int     Algorithm;		// Algorithm of streamline integration
    float   OffsetLength;	// Maximum filter offset in animation

    int compute(		// This computes the convolution
	int             inWidth,
	int             inHeight,
	float*          vectorData,
	int             outWidth,
	int             outHeight,
	unsigned char*  outImage,
	unsigned char*  inputTexture);

    int computeN(		// Computes animated convolution
	int             inWidth,
	int             inHeight,
	float*          vectorData,
	int             outWidth,
	int             outHeight,
	int		nFrames,
	unsigned char** outImage,
	unsigned char*  inputTexture);

  protected:
    Vec2f*  data;		// Pointer to vector data
    int     nx, ny;		// Number of image pixels in x and y
    int	    Nx, Ny;		// Total number of field nodes in x and y
    float   xmax, ymax;		// Used for domain adjustment
    float   xscale, yscale;  	// Needed for coordinate transformation

    Streamline* forward;	// Forward integrator
    Streamline* backward;	// Backward integrator
    StreamEuler fastForward;	// These euler integrator are used in the
    StreamEuler fastBackward;	//   no-update phase (-> sampleFast)

    // Transforms field coordinates to pixel index
    inline int getIndex(Vec2f& vec, int doBoundCheck);

    void initIntegrators(); // Create desired integrators
    void sampleStreamline(const Vec2f& r);
    void sampleFast(const Vec2f& r);
    void createRandomTexture(int nx, int ny, int* dst);
    void copyRandomTexture(int, int, int* dst, unsigned char* src);
    void sampleStreamlineN(const Vec2f& r);
};

inline int FastLIC::getIndex(Vec2f& vec, int doBoundCheck)
{
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

#define getIndexN(vec) \
    (((int)(yscale*vec.y))*nx + (int)(xscale*vec.x))

#ifdef FASTSQRT
extern "C" {
    extern void buildtable();
    extern float fastsqrt(float val);
}
#else
    #define fastsqrt sqrtf
#endif

extern FastLIC global;

#endif
