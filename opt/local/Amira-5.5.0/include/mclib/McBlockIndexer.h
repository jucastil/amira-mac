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
#ifndef MC_BLOCK_INDEXER
#define MC_BLOCK_INDEXER

#include "McDataSpace.h"

/** divide in blocks (arbitrary number of dims <= MC_MAX_NDIMS), helper class.

E.g. visit a 4D volume block by block with a blocksize of 32, 32, 32, 32 or smaller:
\code
    int bs[4] = {32, 32, 32, 32}
    int dims[4] = {1024, 1024, 512, 50};
    McBlockIndexer indexer(4, 0, dims, bs);
    while (indexer.next ()) {
        ds.selectHyperslab (indexer.blockStart(), indexer.blockSize(), 0);
    }
\endcode

*/
class McBlockIndexer {
    public:
        ///
        McBlockIndexer (int numdims, const int* start, const int* count, const int* blocksize = 0) 
                        : myndims (numdims) {
        
            mcenter ("McBlockIndexer");
            mcrequire (myndims > 0 && myndims <= MC_MAX_NDIMS);
            mcrequire (count);

            if (start) {
                memcpy (org, start, myndims * sizeof (int));
                memcpy (act, start, myndims * sizeof (int));
            } else {
                memset (org, 0, myndims * sizeof (int));
                memset (act, 0, myndims * sizeof (int));
            }
            memcpy (cnt, count, myndims * sizeof (int));

            if (blocksize) {
                memcpy (bsize, blocksize, myndims * sizeof (int));
            } else {
                // the default is 64, 64, 64, 1, 1, ....
                for (int d = 0; d < myndims; d++) {
                    bsize[d] = (d < 3) ? 64 : 1;
                }
            }
            act[0] -= bsize[0]; // one back cause first next will step one forward
        };

        ///
        const int* blockStart () {
            return act;
        }
       
#ifndef HX_WITHOUT_DEPRECATED
        /// [DEPRECATED] use blockStart
        const int* blockOrg () {
            mcenter ("McBlockIndexer::blockOrg");
            mcdebug (MCDL_WARNING, "use of deprecated method");

            return blockStart ();
        }
#endif

        ///
        const int* blockSize () {
            return actcnt;
        }
       
        /// 
        bool next () {
            for (int d = 0; d < myndims; d++) {
                // move one
                act[d] += bsize[d];
                // check for wrap
                if (act[d] >= org[d] + cnt[d]) { 
                    // if last dim wraps, we're completely done
                    if (d == myndims - 1) {
                        return false;
                    }
                    // ... else reset this dim and continue with next one
                    act[d] = org[d];
                } else {
                    // ... if no wrap, we're done
                    break;
                }
            }
            for (int i = 0; i < myndims; i++) {
                if (act[i] + bsize[i] - org[i] > cnt[i]) { // check size
                    actcnt[i] = org[i] + cnt[i] - act[i];
                } else {
                    actcnt[i] = bsize[i];
                }
            }
            return true;
        }

        /** \brief walk to next block and copy org and size to user buffer.
                   You might want to use next(), blockStart(), blockSize() instead, to avoid memcopies.
          */
        bool next (int* start, int* size) {
            if (next ()) {
                memcpy (start, act, myndims * sizeof(int));
                memcpy (size, actcnt, myndims * sizeof(int));
                return true;
            }
            return false;
        }

        /** \brief the maximal number of elements used by one block.
                    Useful for buffer allocation.
          */
        mclong maxBlockElemCount () {
            mclong ret = 1;
            for (int i = 0; i < myndims; i++) {
                ret *= bsize[i];
            }
            return ret;
        }

        /** Return the number of blocks that will be generated during iteration.

            \todo analytical formula instead of brute force counting
          */
        mclong numBlocks () {
            McBlockIndexer helper (myndims, org, cnt, bsize);
            int num = 0;
            int o[MC_MAX_NDIMS];
            int bs[MC_MAX_NDIMS];
            while (helper.next (o, bs)) {
                num++;
            }
            return num;
        }
    private:
        /** \brief This is a local helper class and doesn't like to be copied. 
                    There's no principal problem with being copied except
                    for the size of this class which might be unexpectetly large. 
          */
        McBlockIndexer (const McBlockIndexer&);
        /** 
         */
        McBlockIndexer& operator= (const McBlockIndexer&);
        
        const int myndims;

        int act[MC_MAX_NDIMS];
        int actcnt[MC_MAX_NDIMS];

        int org[MC_MAX_NDIMS];
        int cnt[MC_MAX_NDIMS];
        int bsize[MC_MAX_NDIMS];
};

#endif

/// @}
