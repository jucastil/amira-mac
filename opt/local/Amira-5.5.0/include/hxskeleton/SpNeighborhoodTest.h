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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef SP_NEIGHBORHOOD_TEST_H
#define SP_NEIGHBORHOOD_TEST_H

#include <mclib/McDArray.h>
#include <mclib/McData3D.h>
#include <mclib/McBitfield.h>

template <class Enc>
class SpNeighborhoodTest {
    public:
        SpNeighborhoodTest (const int* dims) 
            : dE (1)
            , dN (dims[0])
            , dT (dims[0] * dims[1]) {};
        SpNeighborhoodTest (int i, int j, int k)
            : dE (1)
            , dN (i)
            , dT (i * j) {};
        
#include "simplePointNoEndTest.h"
  
        // needs at least 1 voxel border 
        bool isNotSimpleOrIsEnd (Enc* p, Enc m = Enc(0xffffffff)) {
            return (testKeepEndNoSimple(p, m) ? true : false); 
        }


#include "noSimplePointTest.h"
        
        // needs at least 1 voxel border 
        bool isNotSimple (Enc* p, Enc m = Enc(0xffffffff)) {
            return (testKeepNotSimple (p, m) ? true : false);
        }

        // this is only a hack
        // needs at least len border.
        // needs improvement in checking the chain
        // differ between simple and only one neighbor
        // return:
        //   - true: keep the point
        //   - false: delete the point
        bool isNotSimpleOrIsEndWithLen (Enc* p, Enc m = Enc(0xffffffff)
                                                            , int len = 2) {
            if (!isNotSimple (p, m)) { 
                // for simple points check if they are endpoint
                if (len > 20) {
                    len = 20;
                }
                Enc save[20];
                Enc* savePos[20];
                int idx = 0;

                Enc* current = p;
                int toGo = len;
                while (toGo > 0) {
                    int count = 0;
                    // check if it has exactly one neighbor
                    Enc* next = 0;
                    for (int z = -1; z <= 1; z++) {
                     for (int y = -1; y <= 1; y++) {
                      for (int x = -1; x <= 1; x++) {
                        if (x == 0 && y == 0 && z == 0) {
                            continue;
                        }
                        
                        Enc* neighbor =  current + x * dE + y * dN + z * dT;
                        if (*(neighbor) & m) {
                            count++;
                            next = neighbor; 
                        }
                      }
                     }
                    }
                    // if not one neighbor then no endpoint 
                    if (count != 1) {
                        while (idx > 0) {
                            idx--;
                            *savePos[idx] = save[idx];
                        }
                        return false;
                    }
                    // save the current 
                    save[idx] = *current;
                    savePos[idx] = current;
                    idx++;
                    // remove it
                    *current = 0;
                    // and check the only neighbor
                    toGo--;
                    current = next;
                }
                // len connected endpoints 
                // return keepEndPoint
                while (idx > 0) {   
                    idx--;
                    *savePos[idx] = save[idx];
                }
                return true;
            }
            // is not simple, can't be deleted
            return true;
        }

        bool isFaceEndInPlane (Enc* p, Enc m, const int pl) {
            int sum = 0;
            switch (pl) {
                case 0:
                    sum =   ((*(p - dE - dN) & m) != 0)
                          + ((*(p      - dN) & m) != 0)
                          + ((*(p + dE - dN) & m) != 0)
                          + ((*(p - dE     ) & m) != 0)
                          + ((*(p + dE     ) & m) != 0)
                          + ((*(p - dE + dN) & m) != 0)
                          + ((*(p      + dN) & m) != 0)
                          + ((*(p + dE + dN) & m) != 0);
                    break;
                case 1:
                    sum =   ((*(p - dE - dT) & m) != 0)
                          + ((*(p      - dT) & m) != 0)
                          + ((*(p + dE - dT) & m) != 0)
                          + ((*(p - dE     ) & m) != 0)
                          + ((*(p + dE     ) & m) != 0)
                          + ((*(p - dE + dT) & m) != 0)
                          + ((*(p      + dT) & m) != 0)
                          + ((*(p + dE + dT) & m) != 0);
                    break;
                case 2:
                    sum =   ((*(p - dN - dT) & m) != 0)
                          + ((*(p      - dT) & m) != 0)
                          + ((*(p + dN - dT) & m) != 0)
                          + ((*(p - dN     ) & m) != 0)
                          + ((*(p + dN     ) & m) != 0)
                          + ((*(p - dN + dT) & m) != 0)
                          + ((*(p      + dT) & m) != 0)
                          + ((*(p + dN + dT) & m) != 0);
                    break;
                case 3: // dN == dT
                    sum =   ((*(p - dE - dN - dT) & m) != 0)
                          + ((*(p      - dN - dT) & m) != 0)
                          + ((*(p + dE - dN - dT) & m) != 0)
                          + ((*(p - dE          ) & m) != 0)
                          + ((*(p + dE          ) & m) != 0)
                          + ((*(p - dE + dN + dT) & m) != 0)
                          + ((*(p      + dN + dT) & m) != 0)
                          + ((*(p + dE + dN + dT) & m) != 0);
                    break;
                case 4: // dN == -dT
                    sum =   ((*(p - dE - dN + dT) & m) != 0)
                          + ((*(p      - dN + dT) & m) != 0)
                          + ((*(p + dE - dN + dT) & m) != 0)
                          + ((*(p - dE          ) & m) != 0)
                          + ((*(p + dE          ) & m) != 0)
                          + ((*(p - dE + dN - dT) & m) != 0)
                          + ((*(p      + dN - dT) & m) != 0)
                          + ((*(p + dE + dN - dT) & m) != 0);
                    break;
                case 5: // dE == dN
                    sum =   ((*(p - dE - dT - dN) & m) != 0)
                          + ((*(p      - dT     ) & m) != 0)
                          + ((*(p + dE - dT + dN) & m) != 0)
                          + ((*(p - dE      - dN) & m) != 0)
                          + ((*(p + dE      + dN) & m) != 0)
                          + ((*(p - dE + dT - dN) & m) != 0)
                          + ((*(p      + dT     ) & m) != 0)
                          + ((*(p + dE + dT + dN) & m) != 0);
                    break;
                case 6: // dE == -dN
                    sum =   ((*(p - dE - dT + dN) & m) != 0)
                          + ((*(p      - dT     ) & m) != 0)
                          + ((*(p + dE - dT - dN) & m) != 0)
                          + ((*(p - dE      + dN) & m) != 0)
                          + ((*(p + dE      - dN) & m) != 0)
                          + ((*(p - dE + dT + dN) & m) != 0)
                          + ((*(p      + dT     ) & m) != 0)
                          + ((*(p + dE + dT - dN) & m) != 0);
                    break;
                case 7: // dE == dT
                    sum =   ((*(p - dE - dN - dT) & m) != 0)
                          + ((*(p      - dN     ) & m) != 0)
                          + ((*(p + dE - dN + dT) & m) != 0)
                          + ((*(p - dE      - dT) & m) != 0)
                          + ((*(p + dE      + dT) & m) != 0)
                          + ((*(p - dE + dN - dT) & m) != 0)
                          + ((*(p      + dN     ) & m) != 0)
                          + ((*(p + dE + dN + dT) & m) != 0);
                    break;
                case 8: // dE == -dT
                    sum =   ((*(p - dE - dN + dT) & m) != 0)
                          + ((*(p      - dN     ) & m) != 0)
                          + ((*(p + dE - dN - dT) & m) != 0)
                          + ((*(p - dE      + dT) & m) != 0)
                          + ((*(p + dE      - dT) & m) != 0)
                          + ((*(p - dE + dN + dT) & m) != 0)
                          + ((*(p      + dN     ) & m) != 0)
                          + ((*(p + dE + dN - dT) & m) != 0);
                    break;
            }
            if (sum == 1) {
                return true;
            }
            return false;
        }
        
        bool isFaceEnd (Enc* p, Enc m = Enc(0xffffffff)) {
            for (int i = 0; i < 9; i++) {
                if (isFaceEndInPlane (p, m, i)) {
                    return true;
                }
            }
            return false;
        }

        /* the next functions are for 2thick -> 1thick
           See an article by Borgefors PattRecogn 32 (1999) pp 1225
           */
        bool condBorgeforsA2 (Enc* p) {
            return (*p) &&
                (
                   (*(p + dE + dN) && !*(p + dE) && !*(p + dN)) 
                || (*(p + dE - dN) && !*(p + dE) && !*(p - dN)) 
                || (*(p - dE + dN) && !*(p - dE) && !*(p + dN)) 
                || (*(p - dE - dN) && !*(p - dE) && !*(p - dN)) 

                || (*(p + dE + dT) && !*(p + dE) && !*(p + dT)) 
                || (*(p + dE - dT) && !*(p + dE) && !*(p - dT)) 
                || (*(p - dE + dT) && !*(p - dE) && !*(p + dT)) 
                || (*(p - dE - dT) && !*(p - dE) && !*(p - dT)) 

                || (*(p + dN + dT) && !*(p + dN) && !*(p + dT)) 
                || (*(p + dN - dT) && !*(p + dN) && !*(p - dT)) 
                || (*(p - dN + dT) && !*(p - dN) && !*(p + dT)) 
                || (*(p - dN - dT) && !*(p - dN) && !*(p - dT)) 
                );
        };

        bool condBorgeforsA3 (Enc* p) {
            return (*p) && 
                (
      (*(p + dE + dN + dT) && !*(p + dE) && !*(p + dN) && !*(p + dT) && !*(p + dE + dN) && !*(p + dE + dT) && !*(p + dN + dT))
   || (*(p + dE + dN - dT) && !*(p + dE) && !*(p + dN) && !*(p - dT) && !*(p + dE + dN) && !*(p + dE - dT) && !*(p + dN - dT))
   || (*(p + dE - dN + dT) && !*(p + dE) && !*(p - dN) && !*(p + dT) && !*(p + dE - dN) && !*(p + dE + dT) && !*(p - dN + dT))
   || (*(p + dE - dN - dT) && !*(p + dE) && !*(p - dN) && !*(p - dT) && !*(p + dE - dN) && !*(p + dE - dT) && !*(p - dN - dT))
   || (*(p - dE + dN + dT) && !*(p - dE) && !*(p + dN) && !*(p + dT) && !*(p - dE + dN) && !*(p - dE + dT) && !*(p + dN + dT))
   || (*(p - dE + dN - dT) && !*(p - dE) && !*(p + dN) && !*(p - dT) && !*(p - dE + dN) && !*(p - dE - dT) && !*(p + dN - dT))
   || (*(p - dE - dN + dT) && !*(p - dE) && !*(p - dN) && !*(p + dT) && !*(p - dE - dN) && !*(p - dE + dT) && !*(p - dN + dT))
   || (*(p - dE - dN - dT) && !*(p - dE) && !*(p - dN) && !*(p - dT) && !*(p - dE - dN) && !*(p - dE - dT) && !*(p - dN - dT))
                );
        };

        bool partOfCondBorgeforsA2 (Enc* p, int dT, int dE, int dN) {
            return (*p) &&
                (
                   (*(p + dE + dT) && !*(p + dE) && !*(p + dT)) 
                || (*(p - dE + dT) && !*(p - dE) && !*(p + dT)) 

                || (*(p + dN + dT) && !*(p + dN) && !*(p + dT)) 
                || (*(p - dN + dT) && !*(p - dN) && !*(p + dT)) 
                );
        }

        bool partOfCondBorgeforsA3 (Enc* p, int dT, int dE, int dN) {
            return (*p) && 
                (
      (*(p + dE + dN + dT) && !*(p + dE) && !*(p + dN) && !*(p + dT) && !*(p + dE + dN) && !*(p + dE + dT) && !*(p + dN + dT))
   || (*(p + dE - dN + dT) && !*(p + dE) && !*(p - dN) && !*(p + dT) && !*(p + dE - dN) && !*(p + dE + dT) && !*(p - dN + dT))
   || (*(p - dE + dN + dT) && !*(p - dE) && !*(p + dN) && !*(p + dT) && !*(p - dE + dN) && !*(p - dE + dT) && !*(p + dN + dT))
   || (*(p - dE - dN + dT) && !*(p - dE) && !*(p - dN) && !*(p + dT) && !*(p - dE - dN) && !*(p - dE + dT) && !*(p - dN + dT))
                );
        }
        
        // needs at least 2 voxel border
        bool is2ThickTD (Enc* p) {
            return (!*(p + dT) && *p && *(p - dT) && !*(p - 2 * dT) 
                    && !partOfCondBorgeforsA2 (p, dT, dE, dN) 
                    && !partOfCondBorgeforsA3 (p, dT, dE, dN));
        };

        bool is2ThickDT (Enc* p) {
            return (!*(p - dT) && *p && *(p + dT) && !*(p + 2 * dT) 
                    && !partOfCondBorgeforsA2 (p, -dT, dE, dN) 
                    && !partOfCondBorgeforsA3 (p, -dT, dE, dN));
        };

        bool is2ThickEW (Enc* p) {
            return (!*(p + dE) && *p && *(p - dE) && !*(p - 2 * dE)
                    && !partOfCondBorgeforsA2 (p, dE, dT, dN) 
                    && !partOfCondBorgeforsA3 (p, dE, dT, dN));
        };

        bool is2ThickWE (Enc* p) {
            return (!*(p - dE) && *p && *(p + dE) && !*(p + 2 * dE)
                    && !partOfCondBorgeforsA2 (p, -dE, dT, dN) 
                    && !partOfCondBorgeforsA3 (p, -dE, dT, dN));
        };

        bool is2ThickNS (Enc* p) {
            return (!*(p + dN) && *p && *(p - dN) && !*(p - 2 * dN)
                    && !partOfCondBorgeforsA2 (p, dN, dE, dT) 
                    && !partOfCondBorgeforsA3 (p, dN, dE, dT));
        };

        bool is2ThickSN (Enc* p) {
            return (!*(p - dN) && *p && *(p + dN) && !*(p + 2 * dN)
                    && !partOfCondBorgeforsA2 (p, -dN, dE, dT) 
                    && !partOfCondBorgeforsA3 (p, -dN, dE, dT));
        };

        /* boundary points, kind of ++0 is a east boundary.
         */

        bool isWSBBoundary (Enc* p, Enc mask = Enc(0xffffffff)) {
            for (int i = 0; i < 13; i++) {
                if (isSubIt (p, mask, i)) {
                    return true;
                }
            }
            return false;
        }

        bool isENTBoundary (Enc* p, Enc mask = Enc(0xffffffff)) {
            for (int i = 13; i < 26; i++) {
                if (isSubIt (p, mask, i)) {
                    return true;
                }
            }
            return false;
        }

        // subit 0..25, 
        // checks wether voxel is a face, edge, corner voxel
        // 26 neighbors --> 26 different checks.

        // not a good idea, edges and corner are remove too early
        bool isSubItFast (Enc* p, Enc mask = Enc(0xffffffff), int subIt = 0) {
            if (subIt >= 13) {
                subIt++;
            }
            int z = -1 + subIt / 9;
            int y = -1 + (subIt / 3) % 3;
            int x = -1 + subIt % 3;

            return
              (((*(p + x*dE + y*dN + z*dT) & mask) != 0) == 1) // subIts set ?
           && (((*(p - x*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
            ;
        }

        // subit 0..25, 
        // checks wether voxel is a face, edge, corner voxel
        // 26 neighbors --> 26 different checks.
        bool isSubIt (Enc* p, Enc mask = Enc(0xffffffff), int subIt = 0) {
            if (subIt >= 13) {
                subIt++;
            }
            int z = -1 + subIt / 9;
            int y = -1 + (subIt / 3) % 3;
            int x = -1 + subIt % 3;

            int notZero = 0;
            if (x != 0) {
                notZero++;
            }
            if (y != 0) {
                notZero++;
            }
            if (z != 0) {
                notZero++;
            }
            switch (notZero) {
                default:
                case 0:
                    return false;
                case 1:
                    return
              (((*(p + x*dE + y*dN + z*dT) & mask) != 0) == 1) // subIts set ?
           && (((*(p - x*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
                       ;
                    break;
                case 2:
                    if (x == 0) {
                        return
              (((*(p + x*dE + y*dN + z*dT) & mask) != 0) == 1) // subIts set ?
           && (((*(p - x*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - x*dE - y*dN - 0*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - x*dE - 0*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
                            ;
                    } else if (y == 0) {
                        return
              (((*(p + x*dE + y*dN + z*dT) & mask) != 0) == 1) // subIts set ?
           && (((*(p - x*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - x*dE - y*dN - 0*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - 0*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
                            ;
                    } else {
                        return
              (((*(p + x*dE + y*dN + z*dT) & mask) != 0) == 1) // subIts set ?
           && (((*(p - x*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - x*dE - 0*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - 0*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
                            ;
                    }
                    break;
                case 3:
                    return
              (((*(p + x*dE + y*dN + z*dT) & mask) != 0) == 1) // subIts set ?
           && (((*(p - x*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - 0*dE - y*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - x*dE - 0*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - x*dE - y*dN - 0*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - 0*dE - 0*dN - z*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - x*dE - 0*dN - 0*dT) & mask) != 0) != 1) // subIts unset ?
           && (((*(p - 0*dE - y*dN - 0*dT) & mask) != 0) != 1) // subIts unset ?
                       ;
                    break;
            }
            return false;
        }

    private:
        const int dE;
        const int dN;
        const int dT;
};

/** alpha versions of neighberhood checks.
  */
namespace Connectivities {
    struct N26 {
        const int* getVoi () {
            static int box[6] = {-1, 1, -1, 1, -1, 1};
            return box;
        };

        bool isNH (int i, int j, int k) {
            if (   (i >= -1) && (i <= 1) 
                && (j >= -1) && (j <= 1) 
                && (k >= -1) && (k <= 1)) {
                if (i == 0 && j == 0 && k == 0) {
                    return false; // central voxel is not in neighborhood
                }
                return true;
            }
            return false;
        };
    };

    struct N18 {
        const int* getVoi () {
            static int box[6] = {-1, 1, -1, 1, -1, 1};
            return box;
        };

        bool isNH (int i, int j, int k) {
            if (   (i >= -1) && (i <= 1) 
                && (j >= -1) && (j <= 1) 
                && (k >= -1) && (k <= 1)) {
                if (i == 0 && j == 0 && k == 0) {
                    return false; // central voxel is not in neighborhood
                }
                if (i != 0 && j != 0 && k != 0) { 
                    return false; // corners not 
                }
                return true;
            }
            return false;
        };
    };

    struct N6 {
        const int* getVoi () {
            static int box[6] = {-1, 1, -1, 1, -1, 1};
            return box;
        };

        bool isNH (int i, int j, int k) {
            if (   (i >= -1) && (i <= 1) 
                && (j >= -1) && (j <= 1) 
                && (k >= -1) && (k <= 1)) {
                int notZero = 0;
                if (i != 0) {
                    notZero++;
                }
                if (j != 0) {
                    notZero++;
                }
                if (k != 0) {
                    notZero++;
                }
                if (notZero != 1) {
                    return false;
                }
                return true;
            }
            return false;
        };
    };

    template<int N>
    struct PLANE {
        const int* getVoi () {
            static int box[6] = {-1, 1, -1, 1, -1, 1};
            return box;
        };

        bool isNH (int i, int j, int k) {
            if (   (i >= -1) && (i <= 1) 
                && (j >= -1) && (j <= 1) 
                && (k >= -1) && (k <= 1)) {
                if (i == 0 && j == 0 && k == 0) {
                    return false; // central voxel is not in neighborhood
                }
                switch (N) {
                    case 0:
                        if (i == 0) {
                            return true;
                        }
                        break;
                    case 1:
                        if (j == 0) {
                            return true;
                        }
                        break;
                    case 2:
                        if (k == 0) {
                            return true;
                        }
                        break;
                    case 3:
                        if (i == j) {
                            return true;
                        }
                        break;
                    case 4:
                        if (i == -j) {
                            return true;
                        }
                        break;
                    case 5:
                        if (i == k) {
                            return true;
                        }
                        break;
                    case 6:
                        if (i == -k) {
                            return true;
                        }
                        break;
                    case 7:
                        if (j == k) {
                            return true;
                        }
                        break;
                    case 8:
                        if (j == -k) {
                            return true;
                        }
                        break;
                }
            }
            return false;
        };
    };
};

namespace Neighborhoods {
    template <class VOI, class CONN, class SEEDS> 
    class NeiHood {
        public:
            NeiHood (const int* d) {
                init (d[0], d[1], d[2]);
            };
            
            NeiHood (int i, int j, int k) {
                init (i, j, k);
            };

            void init (int i, int j, int k) {
                dPtr[0] = 1;
                dPtr[1] = i; 
                dPtr[2] = i * j;

                // setup offsets to nh
                offsets.clear ();
                VOI voi;
                CONN con;
                SEEDS seed;
                const int* v = voi.getVoi ();
                // for all voxels that might be in the neighborhood
                // calc offsets and mapping
                McData3D<int> mapping (  v[1] - v[0] + 1
                                       , v[3] - v[2] + 1
                                       , v[5] - v[4] + 1);

                int x, y, z, xxx, yyy, zzz;
                for (x = v[0]; x <= v[1]; x++) {
                 for (y = v[2]; y <= v[3]; y++) {
                  for (z = v[4]; z <= v[5]; z++) {
                    if (voi.isNH (x, y, z)) { // check if in
                      mapping.get (x - v[0], y - v[2], z - v[4]) = offsets.size ();
                      if (seed.isNH (x, y, z)) {
                          seeds.append (offsets.size ());
                      }
                      offsets.append (x * dPtr[0] + y * dPtr[1] + z * dPtr[2]);
                    }
                  } 
                 } 
                } 

                // go through all points and calc connectivity
                for (x = v[0]; x <= v[1]; x++) {
                 for (y = v[2]; y <= v[3]; y++) {
                  for (z = v[4]; z <= v[5]; z++) {
                    if (voi.isNH (x, y, z)) { // check if in
                      // for all connected voxels
                      const int* c = con.getVoi ();
                      for (xxx = c[0]; xxx <= c[1]; xxx++) {
                       for (yyy = c[2]; yyy <= c[3]; yyy++) {
                        for (zzz = c[4]; zzz <= c[5]; zzz++) {
                          if (   con.isNH (xxx, yyy, zzz) 
                              && voi.isNH (x + xxx, y + yyy, z + zzz)) {
                              connArray.append (mapping.get (
                                            x + xxx - v[0]
                                          , y + yyy - v[2]
                                          , z + zzz - v[4]
                                          ));
                          }    
                        }
                       }
                      }
                      connArray.append (-1);
                    }
                  } 
                 } 
                } 

                // build direct conn list
                conn.append (connArray.dataPtr ());
                for (int n = 0; n < connArray.size () - 1; n++) {
                    if (connArray[n] == -1) {
                        conn.append (&connArray [n + 1]);
                    }
                }
                assert (offsets.size () == conn.size ());
            };

            int getDim () const {
                return offsets.size ();
            };

            const int* getOffsets () const {
                return offsets.dataPtr ();
            };

            const int* getConn (int i) const {
                return conn[i];
            };

            int getDimSeeds () const {
                return seeds.size ();
            };

            int getSeed (int i) const {
                return seeds[i];
            };

        private:
            int dPtr[3];
            McDArray<int> offsets;
            McDArray<int> connArray;
            McDArray<int*> conn;
            McDArray<int> seeds;
    };

    template<class ENC, class NH> 
    int calcCC (ENC* p, const NH& nh, ENC mask = ENC(0xffffffff), bool fg = 1
            , int* comps = 0) {
        int dim = nh.getDim ();
        const int* off = nh.getOffsets ();

        McBitfield vis (dim);
        vis.unsetAll ();

        if (comps) {
            memset (comps, 0, nh.getDim () * sizeof (int));
        }

        int nCC = 0;
        for (int i = 0; i < nh.getDimSeeds (); i++) {
            int s = nh.getSeed(i);
            if (!vis[s] && (((*(p + off[s]) & mask) != 0) == fg)) {
                nCC++; // start new cc
                // fill cc 
                McDArray<int> stack;
                stack.push (s);
                vis.set (s);
                if (comps) {
                    comps[s] = nCC;
                }

                int pos;
                while (stack.pop (pos)) {
                  const int* con = nh.getConn (pos); 
                  while (*con >= 0) {
                    if (!vis[*con] && (((*(p + off[*con]) & mask) != 0) == fg)) {
                        stack.push (*con);
                        vis.set (*con);
                        if (comps) {
                            comps[*con] = nCC;
                        }
                    }
                    con++;
                  }
                }
            }
        }
        return nCC;
    }
};

#endif

/// @}
