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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_COMBINATORICS_H
#define MOLCHEM_COMBINATORICS_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>

namespace molchem {
    
    /** \brief Generator for Variations */
    class MOLCHEM_API Variation {
    public:
        // sel must be <= num
        Variation(int num,int sel);
        int num;
        int sel;
        McDArray<int> ix;
        void first();
        bool next();
    };

    /** \brief Generator for Permutations */
    class MOLCHEM_API PermutationGenerator {
    public:

        PermutationGenerator(int n);

        void reset();

        /**
        *  Gets the numLeft attribute of the PermutationGenerator object
        *
        * @return    The numLeft value
        */
        int getNumLeft() const;

        /**
        *  Gets the total attribute of the PermutationGenerator object
        *
        * @return    The total value
        */
        int getTotal() const;


        /**
        *  Description of the Method
        *
        * @return    Description of the Return Value
        */
        bool hasMore() const;


        /**
        *  Gets the factorial attribute of the PermutationGenerator class
        *
        * @param  n  Description of the Parameter
        * @return    The factorial value
        */
        unsigned long getFactorial(int n) const;


        /**Generate next permutation (algorithm from Rosen p. 284)
        *  
        *
        * @return    The next value
        */
        void getNext();

        McDArray<int> a;
        unsigned long numLeft;
        unsigned long total;
    };
}
#endif




/// @}
