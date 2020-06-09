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

/// @addtogroup hxisl hxisl
/// @{
#ifndef _PARTICLE_SET_H
#define _PARTICLE_SET_H

#include <hxisl/HxISLWinDLLApi.h>
#include <hxfield/HxVectorField3.h>
#include <hxfield/HxScalarField3.h>

#include <mclib/McDArray.h>

class HxColormap;
class Particle;
class HxVectorField3;
struct Fragment;
class HxScalarField3;

/**
    This class must be reworked. Deriving from McDArray is not a good idea. 
    * The McDArray-interface can not be used: resize allocates memory and differs therefor from McDArray::resize
    * TODO: Memory-Leak: The destructor does not free the particle data. 

    What does this class do?
    - Computation of the seeding points, taking into account an optional scalarfield for distribution.
    - The vectorfield: Checks for every seedpoint if it is in the domain of the flowfield.
    - As Input this class gets:
        * The Number of seeding points (by resize)
        * Optional: A scalarfield that can be used to steer the distribution
        * Dims: For the sampling size of the scalarfield.
        * A bounding Box: The seeding box of the particles.

*/
class HXISL_API ParticleSet : private McDArray<Particle *>
{
protected:
    float               bbox[6];
    
    /// Used for proportional seeding.
    McDArray<float>     probs;

    HxVectorField3*     vectorField;

    void positionate(Particle *);

    //return 0 if particle can't be evaluated
    int positionateHomogene(Particle *,HxLocation3*);

    void initProbList();

    /**
        Searches for the largest index in [from,to] in the array @a where a[idx] < val. Uses a binary search algorithm.
    */
    inline int search(McDArray<float>& ,float val,int from=0, int to=-1);
    int distMode,probStatus;

    /**
        Initializes the random numer generator, does also the necessary cluster sync stuff.
    */
    void initSRand();

    /**
        Seed value to be set by srand. If Value is 0, another random value is
        used in each initialization of the random number generator. 0 is the
        default value as set in the constructor.
    */
    int m_srandSeed;

public:
    HxScalarField3*	scalarField;
    enum DISTRIBUTION {HOMOGENE,PROPORTIONAL,HISTOGRAM};
    void setDistMode(int d, int invalidateProbList = 0);
    ParticleSet();
    ~ParticleSet();
    void setBoundingBox(const float bb[6]);
    void init(HxVectorField3*, HxScalarField3*, int numParticles=0,int a=15);
    void resize(int);
    void positionateAll();
    void positionateHomogene();
    void normalizeProbs();
	McVec3i dims;

    /*
        Before i added these two lines, ParticleSet was derived public from McDArray<T>.
    */
    using McDArray<Particle*>::size;
    using McDArray<Particle*>::operator[];
    
    /**
        Sets a seed for the random number generator. If 0, each initialization of the particles gets
        a different seed value.
    */
    void setSRandSeed(int srandSeed);

};

#endif


/// @}
