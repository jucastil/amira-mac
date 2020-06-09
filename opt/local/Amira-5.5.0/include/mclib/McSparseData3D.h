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
#ifndef MC_SPARSE_DATA_3D
#define MC_SPARSE_DATA_3D

#include "McWinDLLApi.h"
#include "McDArray.h"
#include "McSmallArray.h"

/** A template class, storing very sparse 3D data.
    You need only specify the height (z direction) of the data.
    The other 2 dimensions are adjusted as needed.
    All unset elements will return UNSETVAL.

    If the template paramter SORTED is true the elements are
    stored in sorted lists, otherwise not.
  */
template<class T, T UNSETVAL = 0, bool SORTED = true>
class McSparseData3D {
    protected:
        class Entry;
        class Row;
        class Slice;
        friend class Entry;
        friend class Row;
        friend class Slice;

        struct Entry {
            public:
                Entry (int x_, const T& v) : value (v), x (x_) {};
                Entry (int x_) : x (x_) {};

                T value;
                int x;

                static int compare (const Entry& e1, const Entry& e2) {
                    return mcStandardCompare<int> (e1.x, e2.x);
                }
        };

        struct Row {
            public:
                Row (int y_) : y(y_) {
                    columns.clear ();
                };

                McSmallArray<Entry, 10> columns;
                int y;

                static int compare (const Row& e1, const Row& e2) {
                    return mcStandardCompare<int> (e1.y, e2.y);
                }
        };

        class Slice {
            public:
                Slice () {
                    rows.clear ();
                };

                McSmallArray<Row, 10> rows;
        };

        int dimZ;
        McDArray<Slice> slices;

        int dimX;
        int dimY;

    public:
        ///
        McSparseData3D () : dimZ (0), dimX (0), dimY (0) {
            slices.clear ();
        };

        ///
        McSparseData3D (int dim) : dimZ (dim), dimX (0), dimY (0) {
            slices.resize (dimZ);
        };

        /// resize height
        void resize (int dim) {
            dimZ = dim;
            slices.resize (dim);
        }

        ///
        int sizeX () { return dimX; };
        ///
        int sizeY () { return dimY; };
        ///
        int sizeZ () { return dimZ; };

        /// read only get, if elem not found 0 is returned.
        T get (int x, int y, int z) const {
            assert (z >= 0 && z < slices.size ());

            if (SORTED) { // sorted
               int row = slices[z].rows.findSorted (Row(y), &Row::compare);
               if (row >= 0) {
                int col = slices[z].rows[row].columns.findSorted (Entry (x)
                                                           , &Entry::compare);
                if (col >= 0) {
                    return slices[z].rows[row].columns[col].value;
                }
               }
               return UNSETVAL;
            } else {  // unsorted
                for (int j = 0; j < slices[z].rows.size (); j++) {
                 if (slices[z].rows[j].y == y) {
                  for (int i = 0; i < slices[z].rows[j].columns.size (); i++) {
                   if (slices[z].rows[j].columns[i].x == x) {
                      return slices[z].rows[j].columns[i].value;
                   }
                  }
                  return UNSETVAL;
                 }
                }
                return UNSETVAL;
            }
        };

        /// operator get
        T operator() (int x, int y, int z) const {
            return get (x, y, z);
        };

        /// set
        void set (int x, int y, int z, const T& newVal) {
            assert (z >= 0 && z < slices.size ());
            if (SORTED) { // sorted
               int row = slices[z].rows.findSorted (Row(y), &Row::compare);
               if (row >= 0) {
                int col = slices[z].rows[row].columns.findSorted (Entry (x)
                                                           , &Entry::compare);
                if (col >= 0) {
                    slices[z].rows[row].columns[col].value = newVal;
                    return;
                }
                slices[z].rows[row].columns.insertSorted (Entry (x, newVal)
                                                           , &Entry::compare);
                if (x >= dimX) {
                    dimX = x + 1;
                }
                return;
               }
               Row newRow = Row(y);
               if (y >= dimY) {
                   dimY = y + 1;
               }
               newRow.columns.append (Entry (x, newVal));
               if (x >= dimX) {
                   dimX = x + 1;
               }
               slices[z].rows.insertSorted (newRow, &Row::compare);
               return;
            } else {
                for (int j = 0; j < slices[z].rows.size (); j++) {
                 if (slices[z].rows[j].y == y) {
                  for (int i = 0; i < slices[z].rows[j].columns.size (); i++) {
                   if (slices[z].rows[j].columns[i].x == x) {
                      slices[z].rows[j].columns[i].value = newVal;
                      return;
                   }
                  }
                  slices[z].rows[j].columns.append (Entry (x, newVal));
                  if (x >= dimX) {
                      dimX = x + 1;
                  }
                  return;
                 }
                }
                Row newRow = Row(y);
                if (y >= dimY) {
                    dimY = y + 1;
                }
                newRow.columns.append (Entry (x, newVal));
                if (x >= dimX) {
                    dimX = x + 1;
                }
                slices[z].rows.append (newRow);
                return;
            }
        };

    public:
        /** iterator over all elements that were explicitly set (including
            explicitly set 0).
            use it as in:
            @code
                McSparseData3D<int>::iterator iter (skelVoxels);
                int i, j, k, val;
                while (iter.next (i, j, k, val)) {
                    // do something
                }
                iter.reset ();
                while (iter.next (i, j, k, val)) {
                    // do something
                }
            @endcode
          */
        class iterator {
            public:
                iterator (const McSparseData3D& array) : data (array)
                    , z(0), row(0), col(0) {
                }

                void reset () {
                    z = 0;
                    row = 0;
                    col = 0;
                }

                int next (int& i, int& j, int& k, T& val) {
                   while (1) { // find valid col
                       while (1) {  // find valid row
                           if (z >= data.dimZ) { // end
                               return 0;
                           }
                           if (row >= data.slices[z].rows.size ()) {
                               row = 0;
                               col = 0;
                               z++;
                           } else {
                               break; // valid row, break
                           }
                       }
                       if (col >= data.slices[z].rows[row].columns.size ()) {
                           col = 0;
                           row++;
                       } else {
                           break; // valid col found.
                       }
                   }
                   k = z;
                   j = data.slices[z].rows[row].y;
                   i = data.slices[z].rows[row].columns[col].x;
                   val = data.slices[z].rows[row].columns[col].value;
                   col++; // go to next
                   return true;
                }
            private:
                const McSparseData3D& data;
                int z;
                int row;
                int col;
        };

        friend class iterator;
};

#endif

/// @}
