/*
 *  Copyright (c) 1995 Konrad-Zuse-Zentrum fuer Informationstechnik
 *  Berlin  (ZIB). This software is provided as is without express or
 *  implied warranty. Redistribution in source or binary forms is not
 *  allowed without the permission of ZIB. All copyright notices must
 *  remain intact in all files.
 */
///////////////////////////////////////////////////////////////////////////////
//
//  File: rangen.h
//
//  Declaraction of a pseudo random number generator class
//
///////////////////////////////////////////////////////////////////////////////
#ifndef RANGEN_H
#define RANGEN_H

class HXFASTLIC_API RanGen {
  protected:
    long    seed1, seed2;

  public:
    void    seed (long s1, long s2) { seed1 = s1; seed2 = s2; }
    long    ranmax () { return 2147483563L; }

    long    asLong ();		// returns value between [1..ranmax]
    float   asFloat ();		// returns value between (0..1)
    double  asDouble ();	// returns value between (0..1)

    long    asLong (long low, long high);
    float   asFloat (float low, float high);
    double  asDouble (double low, double high);

    RanGen(long s1=802475L, long s2=139473L) { seed (s1, s2); }
};

///////////////////////////////////////////////////////////////////////////////

inline long RanGen::asLong()  // returns integer random value
{
    long k = seed1/53668L;
    seed1 = 40014L*(seed1-k*53668L) - k*12211L;
    if (seed1<0L) seed1 += 2147483563L;
    k = seed2/52774L;
    seed2 = 40692L*(seed2-k*52774L) - k*3791L;
    if (seed2<0L) seed2 += 2147483399L;
    k = seed1-seed2;
    if (k<1) k += 2147483562L;
    return k;
}

inline float RanGen::asFloat()
    { return asLong()*4.656613e-10; } 

inline double RanGen::asDouble()
    { return asLong()*4.656613e-10; }

inline long RanGen::asLong(long low, long high)
    { return low + (long)( asDouble()*(high+1-low) ); }

inline float RanGen::asFloat (float low, float high)
    { return low + asFloat()*(high-low); }

inline double RanGen::asDouble (double low, double high)
    { return low + asDouble()*(high-low); }

///////////////////////////////////////////////////////////////////////////////

#endif /* RANGEN_H */
