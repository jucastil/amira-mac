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
#ifndef MC_SOBOL_SEQUENCE_H
#define MC_SOBOL_SEQUENCE_H

/** This class calculates a Sobol sequence in the range [0, n[.
    A Sobol sequence is a quasi random sequence that contains
    every value exactly once.
    Usage:
    @code
    McSobolSequence seq (100);
    int pos;
    while (seq.next (pos)) {
        cout << pos;
    }
    @endcode
  */
class McSobolSequence {
    public:
        ///
        McSobolSequence (int n)
            : length (n) {
            maxBit = 0;
            while ((1 << maxBit) < length) {
                maxBit++;
            }

            iv[0] = 1 << (maxBit-1);
            for (int k=1; k<maxBit; k++) {
                int i = iv[k-1];
                i ^= (i >> 1);
                iv[k] = i;
            }
            count = seeder = acc = 0;
        };

        /** writes the next value into pos and returns true. 
            Returns false if no more values are available.
          */
        bool next (int& pos) {
            if (count >= length) {
                return false;
            }
            do {
                int i = seeder++;
                int k;
                for (k=0; k<maxBit-1; k++) {
                    if (!(i & 1)) break;
                    i >>= 1;
                }
                acc ^= iv[k];
            } while (acc >= length);
            count++;
            pos = acc;
            return true;
        };
    private:
        int maxBit;
        int iv[32];
        int count, seeder, acc;
        int length;
};

#endif

/// @}
