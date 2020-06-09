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
#ifndef MC_BYTE_PATTERN_H
#define MC_BYTE_PATTERN_H

#include "McWinDLLApi.h"
#include "McPrimType.h"
#include "McDataSpace.h"
#include "McAssert.h"
#include "McDataType.h"

/** Describes a pattern of bytes:

   The pattern is described as
     - Offset representation: (c_n, o_n, ... , (c_0, o_0)...)
       - On level 0: use first byte, move o_0 bytes, move c_0 times
       - On level 1: apply level 0 at first byte, move o_1 bytes from 0 to new base,
                    apply level 0, move o_1 bytes from last base,
                    repeat c_1 times
       - ...

    e.g:
\verbatim

    XoXoX
    XoXoX   (2, 15, (2, 5, (3, 2))), offset rep.
    ooooo
    XoXoX   [2, 5, [2, -1, [3, 2]]], delta rep. (see below)
    XoXoX

    XoXoX
    ooooo   (3, 10, (3, 2)))
    XoXoX
    ooooo   [3, 4, [3, 2]]
    XoXoX

\endverbatim

     - You can easily change to the delta representation which is more
        suitable for iterators: [c_n, d_n, ..., [c_0, d_0]...].
        It only stores the deltas which have to be added after applying
        all lower levels:
\verbatim
        repeat c_n times
          ...
            repeat c_1 times
              repeat c_0 times
                use byte
                move d_0
              move d_1
          ...
          move d_n
\endverbatim
        The transformation is:
            - [c_n] = (c_n)
            - d_0 = o_0
            - d_n = o_n - c_n-1 * o_n-1
        Note: the d_n can become negative

    - You can reduce the nesting if d_n == 0 <=> o_n == c_n-1 * o_n-1, e.g.
\verbatim

    XoXoXo   (3, 6, (3, 2)) = (9, 2)
    XoXoXo
    XoXoXo   [3, 0, [3, 2]] = [9, 2]

\endverbatim

    You might want to use a McBytePattern::Iterator to iterate over
    all bytes in this pattern.

 */
class McBytePattern {
    public:
        enum {
            MAX_NESTING = 8
        };

        static McBytePattern CreateContigousBlock (mclong size) {
            mclong off = 1;
            return McBytePattern (1, &size, &off);
        }

        McBytePattern (int nesting, const mclong* count, const mclong* offset) {
            init (nesting, count, offset);
        }

        McBytePattern () {
            mynesting = 0;
        }

        McBytePattern (const McMemorySelection& sel) {
            mcrequire (sel.nDims () < MAX_NESTING);
            mclong count[MAX_NESTING];
            mclong offset[MAX_NESTING];

            count[0] = sel.dataElemSize ();
            offset[0] = 1;
            for (int i = 0; i < sel.nDims (); i++) {
                count[i + 1] = sel.selectionSize()[i];
                offset[i + 1] = sel.offsets()[i] * sel.dataElemSize ();
            }
            init (sel.nDims() + 1, count, offset);
        }

        mclong byteCount () const {
            mclong count = 1;
            for (int i = 0; i < mynesting; i++) {
                count *= mycount[i];
            }
            return count;
        }

        class Iterator;

        int nesting () const {
            return mynesting;
        }

        /** Changes the pattern from bytes to memory
         *  elements of size. This is only possible
         *  if size contiguous bytes are available
         *  at each position.
         *
         * \todo a McBytePattern is perhaps not the right place
         *          for this. Rename McBytePattern -> McMemPattern?
         *          The class basically provides only offsets.
         *          Therefore it's perhaps a McOffsetPattern.
         *          But this method also checks if the elem size is
         *          compatible with the byte pattern.
         */
        void changeElemSize (int size) {
            mcrequire ((mycount[0] / size) * size == mycount[0]);
            mcrequire (myoffset[0] == 1);
            mycount[0] /= size;
            for (int i = 1; i < mynesting; i++) {
                mcrequire ((myoffset[i] / size) * size == myoffset[i]);
                myoffset[i] /= size;
            }
        }

        /** Calculate and return the mimal amout of
         *  linear memory required by this pattern.
         */
        mclong minMemRequirement () const {
            // we need at least 1 byte, even if all count are 1
            mclong count = 1;
            for (int i = 0; i < mynesting; i++) {
                count += (mycount[i] - 1) * myoffset[i];
            }
            return count;
        }
    private:
        void init (int nesting, const mclong* count, const mclong* offset) {
            mcenter3 ("McBytePattern::init");
            mcrequire (nesting <= MAX_NESTING);

            int level = 0;
            mycount[0] = count[0];
            myoffset[0] = offset[0];

            // reduce nesting if possible
            for (int i = 1; i < nesting; i++) {
                if (mycount[level] * myoffset[level] == offset[i]) {
                    mycount[level] *= count[i];
                } else {
                    level++;
                    mycount[level] = count[i];
                    myoffset[level] = offset[i];
                }
            }
            mynesting = level + 1;
        }
        mclong mycount[MAX_NESTING];
        mclong myoffset[MAX_NESTING];
        int mynesting;

        friend class Iterator;
};

/** This class provides a framework to build iterators
 *  over McBytePattern.
 *  E.g. in mcmemcpy it is used to iterate over two
 *  McBytePattern at the same time:
\code
void mcmemcpy (void* dest, const McBytePattern& destpat, const void* src, const McBytePattern& srcpat) {
    McBytePattern::Iterator destiter (destpat);
    McBytePattern::Iterator srciter (srcpat);
    unsigned char* destrun = (unsigned char*)dest;
    const unsigned char* srcrun = (const unsigned char*)src;
    while (destiter.more ()) {
        int cont = destiter.contiguous();
        int test = srciter.contiguous();
        if (test < cont) {
            cont = test;
        }

        if (cont > 1) {
            memcpy (destrun, srcrun, cont);
        } else {
            *destrun = *srcrun;
        }
        destiter.forward (cont);
        srciter.forward (cont);

        destrun += destiter.delta ();
        srcrun += srciter.delta ();
    }
}
\endcode
 */
class McBytePattern::Iterator {
    public:
        /// Init.
        Iterator (const McBytePattern& pat)
            : mypattern(pat) {
            reset ();
        }

        /// Restart.
        void reset () {
            memset (pos, 0, mypattern.mynesting * sizeof (mclong));
            linearoffset = 0;
            lineardelta = 0;
        }

        /** Move to a specific element in the pattern and continue
         *  iterating from there.
         */
        void move (mclong linindex) {
            mcenter3 ("McBytePattern::Iterator::move");
            reset ();

            int level = 0;
            mclong num = 1;
            // find largest level we have to use
            while (linindex >= num) {
                num *= mypattern.mycount[level];
                level++;
            }
            // from this level down init all things
            // and calculate our starting offset
            linearoffset = 0;
            while (level) {
                level--;

                num /= mypattern.mycount[level];
                pos[level] = linindex / num;
                linindex -= num * pos[level];

                linearoffset += pos[level] * mypattern.myoffset[level];
            }
        }

        /** More to do?
         */
        bool more () const {
            return (pos[mypattern.mynesting - 1] < mypattern.mycount[mypattern.mynesting - 1]);
        }

        /** Move forward by count.
         */
        void forward (mclong count) {
            mcrequire (pos[0] + count <= mypattern.mycount[0]);
            // move level 0
            pos[0] += count;
            lineardelta = mypattern.myoffset[0] * count;
            // move higher levels if necessary
            if (pos[0] >= mypattern.mycount[0]) {
                int iterlevel = 1;
                while (iterlevel && iterlevel < mypattern.mynesting) {
                    pos[iterlevel]++;
                    const mclong d_iterlevel = mypattern.myoffset[iterlevel] - mypattern.mycount[iterlevel - 1] * mypattern.myoffset[iterlevel - 1];
                    lineardelta += d_iterlevel;
                    // reset lower levels
                    if (pos[iterlevel] < mypattern.mycount[iterlevel]) {
                        while (iterlevel > 0) {
                            iterlevel--;
                            pos[iterlevel] = 0;
                        }
                    } else {
                        iterlevel++;
                    }
                }
            }
            linearoffset += lineardelta;
        }

        /** Return the linear offset to the
         *  current element of the iterator.
         */
        mclong offset () const {
            return linearoffset;
        }
        /** Return number of elements to increase a linear
         *  offset to reflect the last #forward call.
         */
        mclong delta () const {
            return lineardelta;
        }

        /** How many contiguous elements are available
         *  including the current position?
         */
        mclong contiguous () const {
            if (mypattern.myoffset[0] == 1) {
                return mypattern.mycount[0] - pos[0];
            }
            return 1;
        }
    private:
        const McBytePattern& mypattern;
        mclong pos[McBytePattern::MAX_NESTING];
        mclong linearoffset;
        mclong lineardelta;
};

#endif

/// @}
