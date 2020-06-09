/*
 *  Copyright (c) 1995 Konrad-Zuse-Zentrum fuer Informationstechnik
 *  Berlin  (ZIB). This software is provided as is without express or
 *  implied warranty. Redistribution in source or binary forms is not
 *  allowed without the permission of ZIB. All copyright notices must
 *  remain intact in all files.
 */
#ifndef __FastLIC_h_
#define __FastLIC_h_

#ifdef __cplusplus
extern "C" {
#endif

extern int fastLIC(
    int		    inWidth,
    int		    inHeight,
    float*	    vectorData,
    int		    outWidth,
    int		    outHeight,
    unsigned char*  outImage,
    unsigned char*  inputTexture);

extern int fastLICAnim(
    int		    inWidth,
    int		    inHeight,
    float*	    vectorData,
    int		    outWidth,
    int		    outHeight,
    int		    nFrames,
    unsigned char** outImage,
    unsigned char*  inputTexture);

extern int fastLICSetParamf(int param, float value);
extern int fastLICGetParamf(int param, float* value);

extern int fastLICSetParami(int param, int value);
extern int fastLICGetParami(int param, int* value);

/* Parameter names */
#define LIC_FILTER_LENGTH	1
#define LIC_STREAMLINE_LENGTH	2
#define LIC_HSAMPLING		3
#define LIC_TOLERANCE		4
#define LIC_HTRY		5
#define LIC_HMIN		6
#define LIC_HMAX		7
#define LIC_SEED		8
#define LIC_ALGORITHM		9
#define LIC_OFFSET_LENGTH      10

/* Integrator types */
#define LIC_RKCK		0
#define LIC_RKDP		1
#define LIC_RK43		2
#define LIC_EULER		3
#define LIC_MIDPOINT		4

#ifdef __cplusplus
}
#endif

#endif
