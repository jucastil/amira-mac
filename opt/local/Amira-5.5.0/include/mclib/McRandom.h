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

/// @addtogroup mclib mclib
/// @{
#ifndef MCRANDOM_H
#define MCRANDOM_H

#include <time.h>

#include "McWinDLLApi.h"

const int  McRandomNTAB = 32;
const long McRandomIM   = 2147483647;

//// A Pseudo Random Number Generator (PRNG) class to replace CRT's rand().
class MCLIB_API McRandom
{
  public:

    /// Convenience replacement method for CRT's rand().
    static double rand();

    /** Generates standard normally distributed random numbers by using rand() and 
        applying polar Box-Muller transform. Distributions with other mean mu 
        and variance sigma^2 can be obtained by the transformation 
        mu+sigma*randNormalDistribution().
    */
    static double randNormalDistribution();


    /// Default constructor; initializes the random generator.
    McRandom()
    {
        iy=0;

        initialize((int)time(0));
    }

    /// Constructor to initialize the random generator with a given seed.
    McRandom(int newIdum)
    {
        iy=0;

        initialize(newIdum);
    }

    /// Initializes the random generator's shuffle table.
    void initialize(int newIdum)
    {
        m_isValue2Left = false;

        idum = newIdum;
        if(idum == 0){
            idum = 1;
        }

        int j;

        // Warm-up; results get overwritten below.
        for(j=(McRandomNTAB-1)/4; j>=0; j--)
            parkMillerRand();

        // Initialize the shuffle table.
        for(j=McRandomNTAB-1; j>=0; j--)
            iv[j] = parkMillerRand();

        iy = iv[0];
    }

    /// Returns the next random number in range [0,1[.
    double nextNumber()
    {
        const long   NDIV = 1 + (McRandomIM-1)/McRandomNTAB;
        const double AM   = 1.0/McRandomIM;
        const double EPS  = 1.2e-7;
        const double RNMX = 1.0-EPS;

        // Perform the shuffle.
        int j = iy / NDIV;
        iy = iv[j];
        iv[j] = parkMillerRand();

        double temp = AM*iy;
        if(temp > RNMX)
            return RNMX;

        return temp;
    }

    /** Generates standard normally distributed random numbers by using rand() and
        applying polar Box-Muller transform. Distributions with other mean mu
        and variance sigma^2 can be obtained by the transformation
        mu+sigma*nextNormalDistributedNumber().
    */
    double nextNormalDistributedNumber();

  private:

    /// Park-Miller minimal standard random number
    long parkMillerRand()
    {
        const long IA = 16807;
        const long IQ = 127773;
        const long IR = 2836;

        long k = idum / IQ;
        idum = IA * (idum - k*IQ) - IR*k;
        if(idum < 0)
            idum += McRandomIM;

        return idum;
    }

    /**
        Access singleton static random number generator.
    */
    static McRandom* getTheRandom();

    long idum;
    long iy;
    long iv[McRandomNTAB];

    /**
        Normal distributed random numbers always produce two values. This is
        the second, not yet delivered value.
    */
    double m_value2;

    /**
         Normal distributed random numbers always produce two values. This
         flag indicats if a second value has already been produced that can
         be delivered.
    */
    bool   m_isValue2Left;

};

#endif

/// @}
