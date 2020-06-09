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
#ifndef MC_INDEXER_3D_H
#define MC_INDEXER_3D_H

#include "McVec3i.h"
#include "Mc64Bit.h"

/** The class gives a functionality like iterators over 3D arrays but
    coded explicitly. It only provides all the indices to a container
    in a way that all data will be visited.
    example:
    @code
    int x = 100;
    int y = 50;
    int z = 10;
    int nnn = x * y * z;

    McDArray data (nnn);
    McBitfield mask (nnn);

    // only indices
    McIndexer3D idx (x, y, z);
    int pos;
    while (idx.next (pos)) {
        if (data[pos]) {
            mask.set (pos);
        }
    }

    // with position
    McIndexer3D idx2 (x, y, z);
    int pos;
    McVec3i coord;
    while (idx2.next (pos, coord)) {
        if (coord[0] > 10) {
            data[pos] = 1;
            mask.unset (pos);
        }
    }
    @endcode
    Some Remarks:

        @li The Indexers are for one time use only. So far they don't have
              a reset method. Don't use them again after they once
              got invalid.
        @li only use next (pos) or next (pos, coord). Don't mix them up
                in a run. Results would be unpredictable.

  */
class McIndexer3D {
    public:
        /// construct with dims in an array d[3]
        McIndexer3D (const int* d) {
            init (d[0], d[1], d[2]);
        };

        /// construct with dims (i, j, k)
        McIndexer3D (int i, int j, int k) {
            init (i, j, k);
        };

        /// get next index (64 bit supported)
        bool nextLong (mclong& p) {

           p = pos;
           if (pos < num) {
               pos++;
               return true;
           } else {
               return false;
           }
        }

        /// get next index (32 bit only)
        bool next (int& p) {
           mcrequire (!mcNeeds64BitIndex3D (dims));

           mclong lp;
           bool ret = nextLong (lp);
           p = int(lp);

           return ret;
        }

        /// get next index (64 bit supported) and coordinate
        bool nextLong (mclong& p, McVec3i& coord) {
           mcrequire (!mcNeeds64BitIndex3D (dims));

            p = pos;
            coord = index;
            if (pos < num) {
                pos++;
                index[0]++;
                if (index[0] >= dims[0]) {
                    index[0] = 0;
                    index[1]++;
                    if (index[1] >= dims[1]) {
                        index[1] = 0;
                        index[2]++;
                    }
                }
                return true;
            } else {
                return false;
            }
        }

        /// get next index (32 bit only) and coordinate
        bool next (int& p, McVec3i& coord) {
           mcrequire (!mcNeeds64BitIndex3D (dims));

           mclong lp;
           bool ret = nextLong (lp, coord);
           p = int(lp);
           return ret;
        }

        /// test wether given index lies inside the volume.
        bool inside (mclong pos) {
            if (pos >=0 && pos < num) {
                return true;
            }
            return false;
        }
    private:
        void init (int i, int j, int k) {
            mcrequire (!mcNeeds64BitIndex3D (i, j, k));
            dims[0] = i;
            dims[1] = j;
            dims[2] = k;

            pos = 0;
            num = mclong(i) * mclong(j) * mclong(k);

            index = McVec3i (0);
        };

        McVec3i dims;
        McVec3i index;
        mclong pos;
        mclong num;
};

/** See McIndexer. This one only iterates over a
    given subvolume of the data. You can substract a border
    of given width or you can specify a box inside the volume.
  */
class McIndexer3DBoxed {
    public:
        /// construct with dims and border
        McIndexer3DBoxed (const int* d, int border) {
            mcrequire (2 * border + 1 < d[0]);
            mcrequire (2 * border + 1 < d[1]);
            mcrequire (2 * border + 1 < d[2]);
            int b[6];
            b[0] = border;
            b[1] = d[0] - 1 - border;
            b[2] = border;
            b[3] = d[1] - 1 - border;
            b[4] = border;
            b[5] = d[2] - 1 - border;
            init (d[0], d[1], d[2], b);
        };

        /// construct with dims and border
        McIndexer3DBoxed (int i, int j, int k, int border) {
            mcrequire (2 * border + 1 < i);
            mcrequire (2 * border + 1 < j);
            mcrequire (2 * border + 1 < k);
            int b[6];
            b[0] = border;
            b[1] = i - 1 - border;
            b[2] = border;
            b[3] = j - 1 - border;
            b[4] = border;
            b[5] = k - 1 - border;
            init (i, j, k, b);
        };

        /** construct with dims and box.
            give the box as {xmin, xmax, ymin, ymax, zmin, zmax}
            The point (xmax, ymax, zmax) is contained in the box.
          */
        McIndexer3DBoxed (const int* d, const int* box) {
            mcrequire (box[0] <= box[1]);
            mcrequire (box[2] <= box[3]);
            mcrequire (box[4] <= box[5]);
            mcrequire (box[1] < d[0]);
            mcrequire (box[3] < d[1]);
            mcrequire (box[5] < d[2]);

            init (d[0], d[1], d[2], box);
        }

        /** construct with dims and box.
            give the box as {xmin, xmax, ymin, ymax, zmin, zmax}
            The point (xmax, ymax, zmax) is contained in the box.
          */
        McIndexer3DBoxed (int i, int j, int k, const int* box) {
            mcrequire (box[0] <= box[1]);
            mcrequire (box[2] <= box[3]);
            mcrequire (box[4] <= box[5]);
            mcrequire (box[1] < i);
            mcrequire (box[3] < j);
            mcrequire (box[5] < k);

            init (i, j, k, box);
        }

        /// get next index (64 bit supported)
        bool nextLong (mclong& p) {
            if (nextIndex()) {
                p = pos;
                return true;
            }
            return false;
        }

        /// get next index (64 bit supported) and coordinate
        bool nextLong (mclong& p, McVec3i& coord) {
            if (nextIndexAndCoordinate()) {
                p = pos;
                coord = index;
                return true;
            }
            return false;
        }

        /// get next index (32 bit only)
        bool next (int& p) {
            mcrequire (!mcNeeds64BitIndex3D (dims));

            if (nextIndex()) {
                p = pos;
                return true;
            }
            return false;
        }

        /// get next index (32 bit only) and coordinate
        bool next (int& p, McVec3i& coord) {
            mcrequire (!mcNeeds64BitIndex3D (dims));

            if (nextIndexAndCoordinate()) {
                p = pos;
                coord = index;
                return true;
            }
            return false;
        }

        /// test wether given index lies inside the box.
        bool inside (int pos) {
            mcrequire (!mcNeeds64BitIndex3D (dims));

            const int z = pos / (dims[0] * dims[1]);
            const int rest = pos % (dims[0] * dims[1]);
            const int y = rest / dims[0];
            const int x = rest % dims[0];
            if (x >= border[0] && x <= border[1]
                    && y >= border[2] && y <= border[3]
                    && z >= border[4] && z <= border[5]) {
                return true;
            }
            return false;
        }
    private:
        bool nextIndex () {
            mcrequire (togo[2] > 0); // check if we're still valid
            pos++;
            togo[0]--;
            if (togo[0] <= 0) {
                togo[0] = (border[1] - border[0]) + 1;
                pos += dims[0] - togo[0];
                togo[1]--;
                if (togo[1] <= 0) {
                    togo[1] = (border[3] - border[2]) + 1;
                    pos += dims[0] * (dims[1] - togo[1]);
                    togo[2]--;
                    if (togo[2] <= 0) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool nextIndexAndCoordinate () {
            mcrequire (togo[2] > 0); // check if we're still valid
            pos++;
            index[0]++;
            togo[0]--;
            if (togo[0] <= 0) {
                togo[0] = (border[1] - border[0]) + 1;
                pos += dims[0] - togo[0];
                index[0] -= togo[0];
                index[1]++;
                togo[1]--;
                if (togo[1] <= 0) {
                    togo[1] = (border[3] - border[2]) + 1;
                    pos += dims[0] * (dims[1] - togo[1]);
                    index[1] -= togo[1];
                    index[2]++;
                    togo[2]--;
                    if (togo[2] <= 0) {
                        return false;
                    }
                }
            }
            return true;
        }

        void init (int i, int j, int k, const int* const b) {
            dims[0] = i;
            dims[1] = j;
            dims[2] = k;
            border[0] = b[0];
            border[1] = b[1];
            border[2] = b[2];
            border[3] = b[3];
            border[4] = b[4];
            border[5] = b[5];

            index[0] = border[0] - 1;
            index[1] = border[2];
            index[2] = border[4];
            pos = index[0] + dims[0] * (index[1] + index[2] * dims[1]);
            togo[0] = (border[1] - border[0]) + 1;
            togo[0]++;
            togo[1] = (border[3] - border[2]) + 1;
            togo[2] = (border[5] - border[4]) + 1;
            // consistency check
            if ((border[1] < border[0])
                    || (border[3] < border[2])
                    || (border[5] < border[4]) ) {
                togo[0] = togo[1] = togo[2] = 0;
            }
        };

        McVec3i dims;
        int border[6];
        McVec3i index;
        McVec3i togo;
        mclong pos;
};

/** See McIndexer. This one only iterates over a
    given subvolume of the data. You can substract a border
    of given width or you can specify a box inside the volume.
    The volume is indexed in subfields +..+..+.., .+..+..+., ...
    Specify the number of subfields per dimension.
  */
class McIndexer3DBoxedSubfields {
    public:
        /// construct with dims and border
        McIndexer3DBoxedSubfields (const int* d, int border, int nSub) {
            int b[6];
            b[0] = border;
            b[1] = d[0] - 1 - border;
            b[2] = border;
            b[3] = d[1] - 1 - border;
            b[4] = border;
            b[5] = d[2] - 1 - border;
            init (d[0], d[1], d[2], b, nSub);
        };

        /// construct with dims and border
        McIndexer3DBoxedSubfields (int i, int j, int k, int border, int nSub) {
            int b[6];
            b[0] = border;
            b[1] = i - 1 - border;
            b[2] = border;
            b[3] = j - 1 - border;
            b[4] = border;
            b[5] = k - 1 - border;
            init (i, j, k, b, nSub);
        };

        /** construct with dims and box.
            give the box as {xmin, xmax, ymin, ymax, zmin, zmax}
            The point (xmax, ymax, zmax) is contained in the box.
          */
        McIndexer3DBoxedSubfields (const int* d, const int* box, int nSub) {
            init (d[0], d[1], d[2], box, nSub);
        }

        /** construct with dims and box.
            give the box as {xmin, xmax, ymin, ymax, zmin, zmax}
            The point (xmax, ymax, zmax) is contained in the box.
          */
        McIndexer3DBoxedSubfields (int i, int j, int k
                                        , const int* box, int nSub) {
            init (i, j, k, box, nSub);
        }

        /// get next index (64 bit supported)
        bool nextLong (mclong& p) {
            assert (togo[2] > 0); // check if we're still valid
            pos += mclong(delta);
            togo[0] -= delta;
            if (togo[0] <= 0) {
                pos += mclong(togo[0]); // go back
                togo[0] = (border[1] - border[0]) + 1 - subfield % delta;
                pos += mclong(dims[0] - togo[0]);
                pos += mclong((delta - 1) * dims[0]);
                togo[1] -= delta;
                if (togo[1] <= 0) {
                    pos += togo[1] * dims[0]; // go back
                    togo[1] = (border[3] - border[2]) + 1
                                            - (subfield / delta) % delta;
                    pos += mclong(dims[0] * (dims[1] - togo[1]));
                    pos += mclong(delta - 1) * mclong(dims[0] * dims[1]);
                    togo[2] -= delta;
                    if (togo[2] <= 0) {
                        subfield++;
                        if (subfield >= (delta * delta * delta)) {
                            return false;
                        }
                        index[0] = border[0] - delta + subfield % delta;
                        index[1] = border[2] + (subfield / delta) % delta;
                        index[2] = border[4] + (subfield / (delta * delta));
                        pos = index[0] + dims[0] * (index[1] + index[2] * dims[1]);
                        togo[0] = (border[1] - index[0]) + 1;
                        togo[1] = (border[3] - index[1]) + 1;
                        togo[2] = (border[5] - index[2]) + 1;
                    }
                }
            }
            p = pos;
            return true;
        }

        /// get next index (32 bit only)
        bool next (int& p) {
            mcrequire (!mcNeeds64BitIndex3D (dims));

            mclong lp;
            bool ret = nextLong (lp);
            p = int(lp);
            return ret;
        }


#if 0
        /// get next index and coordinate
        // TODO
        bool next (int& p, McVec3i& coord);
#endif

        /// test wether given index lies inside the box.
        bool inside (mclong pos) {
            const int z = pos / mclong(dims[0] * dims[1]);
            const int rest = int(pos % mclong(dims[0] * dims[1]));
            const int y = rest / dims[0];
            const int x = rest % dims[0];
            if (x >= border[0] && x <= border[1]
                    && y >= border[2] && y <= border[3]
                    && z >= border[4] && z <= border[5]) {
                return true;
            }
            return false;
        }
    private:
        void init (int i, int j, int k, const int* const b, int nSub) {
            dims[0] = i;
            dims[1] = j;
            dims[2] = k;
            border[0] = b[0];
            border[1] = b[1];
            border[2] = b[2];
            border[3] = b[3];
            border[4] = b[4];
            border[5] = b[5];

            subfield = 0;
            delta = nSub;
            index[0] = border[0] - delta;
            index[1] = border[2];
            index[2] = border[4];
            pos = mclong(index[0]) + mclong(dims[0]) * mclong(index[1] + index[2] * dims[1]);
            togo[0] = (border[1] - index[0]) + 1;
            togo[1] = (border[3] - index[1]) + 1;
            togo[2] = (border[5] - index[2]) + 1;
            // consistency check
            if ((border[1] < border[0])
                    || (border[3] < border[2])
                    || (border[5] < border[4]) ) {
                togo[0] = togo[1] = togo[2] = 0;
            }
        };

        McVec3i dims;
        int border[6];
        McVec3i index;
        McVec3i togo;
        mclong pos;
        int delta;
        int subfield;
};

/** See McIndexer. This one only iterates over a subvolume
    which is the inverse to the volume used in McIndexer3DBoxed.
    You can interate over the border or over all point not inside a
    given box.
 */
class McIndexer3DNotBoxed {
    public:
        /// construct with dims and border
        McIndexer3DNotBoxed (const int* d, int border) {
            int b[6];
            b[0] = border;
            b[1] = d[0] - 1 - border;
            b[2] = border;
            b[3] = d[1] - 1 - border;
            b[4] = border;
            b[5] = d[2] - 1 - border;
            init (d[0], d[1], d[2], b);
        };

        /// construct with dims and border
        McIndexer3DNotBoxed (int i, int j, int k, int border) {
            int b[6];
            b[0] = border;
            b[1] = i - 1 - border;
            b[2] = border;
            b[3] = j - 1 - border;
            b[4] = border;
            b[5] = k - 1 - border;
            init (i, j, k, b);
        };

        /** construct with dims and box.
            give the box as {xmin, xmax, ymin, ymax, zmin, zmax}
            The point (xmax, ymax, zmax) is contained in the box.
          */
        McIndexer3DNotBoxed (const int* d, const int* box) {
            init (d[0], d[1], d[2], box);
        }

        /** construct with dims and box.
            give the box as {xmin, xmax, ymin, ymax, zmin, zmax}
            The point (xmax, ymax, zmax) is contained in the box.
          */
        McIndexer3DNotBoxed (int i, int j, int k, const int* box) {
            init (i, j, k, box);
        }

        /// get next index
        bool nextLong (mclong& p) {
            if (nextIndexAndCoordinate()) {
                p = pos;
                return true;
            }
            return false;
        }

        /// get next index and coordinate
        bool nextLong (mclong& p, McVec3i& coord) {
            if (nextIndexAndCoordinate()) {
                p = pos;
                coord = index;
                return true;
            }
            return false;
        }

        /// get next index
        bool next (int& p) {
            mcrequire (!mcNeeds64BitIndex3D (dims));

            if (nextIndexAndCoordinate()) {
                p = pos;
                return true;
            }
            return false;
        }

        /// get next index and coordinate
        bool next (int& p, McVec3i& coord) {
            mcrequire (!mcNeeds64BitIndex3D (dims));

            if (nextIndexAndCoordinate()) {
                p = pos;
                coord = index;
                return true;
            }
            return false;
        }

        /// test wether given index lies outside the box, but inside the array.
        bool inside (int pos) {
            mcrequire (!mcNeeds64BitIndex3D (dims));

            const int z = pos / (dims[0] * dims[1]);
            const int rest = pos % (dims[0] * dims[1]);
            const int y = rest / dims[0];
            const int x = rest % dims[0];
            if (x >= border[0] && x <= border[1] && y >= border[2] && y <= border[3]
                    && z >= border[4] && z <= border[5]) {
                return false;
            }
            if (pos >= 0 && pos < (dims[0] * dims[1] * dims[2])) {
                return true;
            }
            return false;
        }
    private:
        bool nextIndexAndCoordinate () {
            assert (index[2] < dims[2]); // check if we're still valid
            pos++;
            index[0]++;
            bool inside;
            do {
                if (index[0] >= dims[0]) {
                    index[0] = 0;
                    index[1]++;
                    if (index[1] >= dims[1]) {
                        index[1] = 0;
                        index[2]++;
                        if (index[2] >= dims[2]) {
                            return false;
                        }
                    }
                }
                inside = index[0] >= border[0] && index[0] <= border[1]
                          && index[1] >= border[2] && index[1] <= border[3]
                          && index[2] >= border[4] && index[2] <= border[5];
                if (inside) {
                    index[0] += border[1] - border[0] + 1;
                    pos += border[1] - border[0] + 1;
                }
            } while (inside) ;
            return true;
        }

        void init (int i, int j, int k, const int* const b) {
            dims[0] = i;
            dims[1] = j;
            dims[2] = k;
            border[0] = b[0];
            border[1] = b[1];
            border[2] = b[2];
            border[3] = b[3];
            border[4] = b[4];
            border[5] = b[5];

            index = McVec3i (0);
            index[0]--;
            pos = index[0] + dims[0] * (index[1] + index[2] * dims[1]);
            // consistency check not needed, we want to be outside
            // if no valid box, everything's outside.
//            if ((border[1] < border[0])
//                    || (border[3] < border[2])
//                    || (border[5] < border[4]) ) {
//                dims = McVec3i (0);
//            }
        };

        McVec3i dims;
        int border[6];
        McVec3i index;
        mclong pos;
};

#endif

/// @}
