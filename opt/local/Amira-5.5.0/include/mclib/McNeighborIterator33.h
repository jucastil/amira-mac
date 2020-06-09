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
#ifndef MC_NEIGHBORITERATOR33_H
#define MC_NEIGHBORITERATOR33_H

#include "McDArray.h"
#include "McProgressInterface.h"
#include "McWinDLLApi.h"

#if 0

#ifndef _WIN32
    #include <values.h>
#endif

#endif

struct MCLIB_API McNeighborIterator33 {
        // Set weights. A 3x3x3 array in canonical C order is expected
        // (x varies fastest).
	// Note that the internal order of points does not need to be this way.
	void setWeights(int weights[27], int dosort=0);
	void setWeights(short weights[27], int dosort=0);

    void setWeights(char weights[27], int dosort=0);
    void setWeights(float weights[27], int dosort=0);

    /// sort the neighbors according to the (previously set) weights in
    /// ascending order. The index of the first neighbor with weight >0
    /// is returned.
    int sort_iweights();
    int sort_fweights();

    McNeighborIterator33(int c, const int* di);

    inline unsigned char borderstatus(int i,int j,int k) {
	unsigned char flag;
	flag   = ((i==0)*BORDERX1) | ((j==0)*BORDERY1) | ((k==0)*BORDERZ1);
	flag  |= ((i==dims[0]-1)*BORDERX2) | ((j==dims[1]-1)*BORDERY2) | ((k==dims[2]-1)*BORDERZ2);
	return flag;
    }
    int ctype;
    int dims[3];
    int offsets[26];
    int iweights[26];
    float fweights[26];
    signed char delta[26][3];
    enum {BORDERX1 = 1, BORDERX2 = 2,BORDERY1 = 4, BORDERY2 = 8,
	  BORDERZ1 = 16, BORDERZ2 = 32 };
    unsigned char bordered[26];
};

inline void getWeight(const McNeighborIterator33& iter, int l, short& res) {
    res=iter.iweights[l];
}
inline void getWeight(const McNeighborIterator33& iter, int l, int& res) {
    res=iter.iweights[l];
}
inline void getWeight(const McNeighborIterator33& iter, int l, float& res) {
    res=iter.fweights[l];
}

#endif

/// @}
