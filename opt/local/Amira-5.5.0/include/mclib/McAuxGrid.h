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
#ifndef MC_AUXGRID_H
#define MC_AUXGRID_H

#include <stdio.h>
#include <stdlib.h>

#include <mclib/McException.h>
#include <mclib/McBox3f.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

/** This class represents a simple uniform grid which is useful to
    quickly find close point, e.g. atoms. First, all points are
    inserted into the grid once. Then the @c search methods can be used
    to find all points in a specified cell and its neighboring
    cells. If no longer needed, points may also be removed from the
    grid. The indices of all points contained in one grid cell are
    stored in a @c McDArray. In order to be efficient, the cell size
    needs to be chosen appropriately. */

template<class Value> class McAuxGrid {
private:
    // Bounding box.
    McBox3f bbox;
    // Bounding box.
    McVec3f bboxMin;
    // Length of the grid cell edges.
    float gridCellLength;
    // Grid size.
    int dims[3];
    // The actual grid.
    McDArray<McDArray<Value> > grid;
    
public:
    /// Default constructor.
    McAuxGrid();
    /// Constructor that takes grid size as argument.
    McAuxGrid(int dims[3]);
    /// Constructor that takes bounding box and dist between two
    /// neighbored cells. Notice, that the bounding box will be
    /// enlarged to fit a multiple of @c cellLength. The dimensions of
    /// the grid will be computed from these parameters.
    McAuxGrid(const McBox3f & bb, float cellLength);
    /// Destructor.
    ~McAuxGrid();

    /// Set grid dimension.
    inline void setDims(int dims[3]);
    /// Compute @c key from @c pos, taking into account the bounding
    /// box of the grid and the length of the cell edges.
    inline void computeKey(const McVec3f & pos, int key[3]);
    /// Insert value @c info into grid cell with indices @c key.
    inline void insert(int key[3], Value info);
    /// Insert value @c info into grid cell containing @c pos. Notice,
    /// that this function will only work correctly if the bounding
    /// box was correctly initialized in the constructor.
    inline void insert(const McVec3f & pos, Value info);
    /// Remove @c info from grid cell.
    inline void remove(int key[3], Value info);
    /// Removes all elements from grid.
    inline void removeAll();
    /// Return array of values contained in grid cell.
    inline McDArray<Value>* search(int key[3]);
    /// Same as above accept that the key is computed automatically.
    inline McDArray<Value>* search(const McVec3f & pos);
    /// Find all values contained in grid cell @c key and adjacent grid
    /// cells that are @c plusMinus-neighbors of center grid cell.
    int  search(int key[3], int plusMinus, McDArray<McDArray<Value> *> &list);
    /// Same as above accept that the key is computed automatically.
    int  search(const McVec3f & pos, int plusMinus, McDArray<McDArray<Value> *> &list);
    /// Similar to above, only that plusMinus may take different values.
    int  search(int key[3], int pm[6], McDArray<McDArray<Value> *> &list);
    /// Same as above accept that the key is computed automatically.
    int  search(const McVec3f & pos, int pm[6], McDArray<McDArray<Value> *> &list);
    /// Convenience function.
    void search(int key[3], int plusMinus, McDArray<Value> &list);
    /// Same as above accept that the key is computed automatically.
    void search(const McVec3f & pos, int plusMinus, McDArray<Value> &list);
    /// Get size of grid.
    int  getSize() { return grid.size(); }
};

template<class Value> 
McAuxGrid<Value>::McAuxGrid(int d[3])
{
    dims[0] = d[0]; dims[1] = d[1]; dims[2] = d[2];

    int size = dims[0]*dims[1]*dims[2];
    if ( size < 0 || size > 10000000 ) 
        throw McException("Wrong McAuxGrid dimension: %d",size);

    grid.resize(dims[0]*dims[1]*dims[2]);

    // default initialization
    bbox = McBox3f(0.0, float(dims[0]), 
                   0.0, float(dims[1]), 
                   0.0, float(dims[2]));
    bboxMin = bbox.getMin();
    gridCellLength = 1;
}

template<class Value> 
McAuxGrid<Value>::McAuxGrid(const McBox3f & bb, float cellLength)
{
    bbox = bb;
    bboxMin = bbox.getMin();
    gridCellLength = cellLength;
    
    // enlarge bounding box to fit multiple of gridCellLength and
    // compute dims
    bbox.enlargeBBoxForIsotropicGrid(gridCellLength, 
                                     0.1*gridCellLength, // epsilon
                                     dims);

    int size = dims[0]*dims[1]*dims[2];
    if ( size < 0 || size > 10000000 ) 
        throw McException("Wrong McAuxGrid dimension: %d",size);

    grid.resize(dims[0]*dims[1]*dims[2]);
}

template<class Value> 
McAuxGrid<Value>::McAuxGrid()
{
    // empty
}

template<class Value> 
McAuxGrid<Value>::~McAuxGrid() 
{
    grid.clear();
}

template<class Value> 
void McAuxGrid<Value>::computeKey(const McVec3f & pos, int key[3])
{
    int i;
    for (i=0; i<3; i++) {
        key[i] = (int)((pos[i] - bboxMin[i]) / gridCellLength);
    }
}

template<class Value> 
void McAuxGrid<Value>::setDims(int d[3])
{
    grid.clear();
    dims[0] = d[0]; dims[1] = d[1]; dims[2] = d[2];
    grid.resize(dims[0]*dims[1]*dims[2]);
}

template<class Value> 
void McAuxGrid<Value>::insert(int idx[3], Value info) 
{
    grid[idx[0]+dims[0]*(idx[1]+idx[2]*dims[1])].append(info);
}

template<class Value> 
void McAuxGrid<Value>::insert(const McVec3f & pos, Value info)
{
    int key[3];
    computeKey(pos, key);
    insert(key, info);
}

template<class Value> 
void McAuxGrid<Value>::remove(int idx[3], Value info) 
{
    McDArray<Value> &l = grid[idx[0]+dims[0]*(idx[1]+idx[2]*dims[1])];
    for (int i=0; i<l.size(); i++) {
        if (l[i] == info) l.remove(i);
    }
}

template<class Value> 
void McAuxGrid<Value>::removeAll() 
{
    int i;
    for ( i=0; i<grid.size(); i++ ) {
        grid[i].clear();
    }
}

template<class Value> 
McDArray<Value>* McAuxGrid<Value>::search(int idx[3]) 
{
    return &(grid[idx[0]+dims[0]*(idx[1]+idx[2]*dims[1])]);
}

template<class Value> 
McDArray<Value>* McAuxGrid<Value>::search(const McVec3f & pos) 
{
    int key[3];
    computeKey(pos, key);
    return search(key);
}

template<class Value> 
void McAuxGrid<Value>::search(int idx[3], int plusMinus, 
                            McDArray<Value> &list) 
{
    int i, j, c;
    McDArray<McDArray<Value> *> tmpList;
    int nElems = search(idx, plusMinus, tmpList);
    list.resize(nElems);
    for ( i=0,c=0; i<tmpList.size(); i++ ) {
        for ( j=0; j<tmpList[i]->size(); j++ ) {
            list[c++] = (*tmpList[i])[j];
        }
    }
}

template<class Value> 
void McAuxGrid<Value>::search(const McVec3f & pos, int plusMinus, 
                            McDArray<Value> &list) 
{
    int key[3];
    computeKey(pos, key);
    search(key, plusMinus, list);
}

template<class Value> 
int McAuxGrid<Value>::search(int idx[3], int plusMinus, 
                           McDArray<McDArray<Value> *> &list) 
{
    // resize list and initialize all entries to zero
    int length =(2*plusMinus)+1;
    int size   = length*length*length;
    int nElems = 0;
    list.remax(size);

    int tIdx[3], sIdx[3];
    int i, j, k, gid;
    
    gid = idx[0]+dims[0]*(idx[1]+idx[2]*dims[1]);
    list.append(&grid[gid]);
    nElems += grid[gid].size();
    
    int major, minor1, minor2;

    for ( i=1; i<plusMinus+1; i++ ) {

        // find the cells on the six sides of the cube
        for ( k=0; k<3; k++ ) { // x, y and z
            major  = k;
            minor1 = (major+1)%3;
            minor2 = (major+2)%3;
            // (1) positive major-direction
            sIdx[major]  = idx[major]+i; 
            sIdx[minor1] = idx[minor1]; 
            sIdx[minor2] = idx[minor2];
            if ( sIdx[major] < dims[major] ) { 
                gid = sIdx[0]+dims[0]*(sIdx[1]+sIdx[2]*dims[1]);
                if ( grid[gid].size() ) {
                    list.append(&grid[gid]);
                    nElems += grid[gid].size();
                }
                tIdx[major] = sIdx[major];
                for ( j=1; j<i; j++ ) {
                    // minor1-direction
                    tIdx[minor2] = sIdx[minor2];
                    tIdx[minor1] = sIdx[minor1]+j; // positive minor1-direction
                    if ( tIdx[minor1] < dims[minor1] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[minor1] = sIdx[minor1]-j; // negative minor1-direction
                    if ( tIdx[minor1] > -1 ) { 
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                
                    // minor2-direction
                    tIdx[minor1] = sIdx[minor1];
                    tIdx[minor2] = sIdx[minor2]+j; // positive minor2-direction
                    if ( tIdx[minor2] < dims[minor2] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[minor2] = sIdx[minor2]-j; // negative minor2-direction
                    if ( tIdx[minor2] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    
                    // minor1- and minor2-direction
                    // (a) positive minor1- and minor2-direction
                    tIdx[minor1] = sIdx[minor1]+j; 
                    tIdx[minor2] = sIdx[minor2]+j;
                    if ( tIdx[minor1] < dims[minor1] && 
                         tIdx[minor2] < dims[minor2] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    // (b) positive minor1-direction, negative minor2-direction
                    tIdx[minor1] = sIdx[minor1]+j; 
                    tIdx[minor2] = sIdx[minor2]-j;
                    if ( tIdx[minor1] < dims[minor1] && 
                         tIdx[minor2] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    // (c) negative minor1- and minor2-direction
                    tIdx[minor1] = sIdx[minor1]-j; 
                    tIdx[minor2] = sIdx[minor2]-j;
                    if ( tIdx[minor1] > -1 && 
                         tIdx[minor2] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    // (d) negative minor1-direction, positive minor2-direction
                    tIdx[minor1] = sIdx[minor1]-j; 
                    tIdx[minor2] = sIdx[minor2]+j;
                    if ( tIdx[minor1] > -1 && 
                         tIdx[minor2] < dims[minor2] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                }      
            }

            // (2) negative major-direction
            sIdx[major]  = idx[major]-i; 
            sIdx[minor1] = idx[minor1]; 
            sIdx[minor2] = idx[minor2];
            if ( sIdx[major] > -1 ) { 
                gid = sIdx[0]+dims[0]*(sIdx[1]+sIdx[2]*dims[1]);
                if ( grid[gid].size() ) {
                    list.append(&grid[gid]);
                    nElems += grid[gid].size();
                }
                tIdx[major] = sIdx[major];
                for ( j=1; j<i; j++ ) {
                    // minor1-direction
                    tIdx[minor2] = sIdx[minor2];
                    tIdx[minor1] = sIdx[minor1]+j; // positive minor1-direction
                    if ( tIdx[minor1] < dims[minor1] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[minor1] = sIdx[minor1]-j; // negative minor1-direction
                    if ( tIdx[minor1] > -1 ) { 
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    
                    // minor2-direction
                    tIdx[minor1] = sIdx[minor1];
                    tIdx[minor2] = sIdx[minor2]+j; // positive minor2-direction
                    if ( tIdx[minor2] < dims[minor2] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[minor2] = sIdx[minor2]-j; // negative minor2-direction
                    if ( tIdx[minor2] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    
                    // minor1- and minor2-direction
                    // (a) positive minor1- and minor2-direction
                    tIdx[minor1] = sIdx[minor1]+j; 
                    tIdx[minor2] = sIdx[minor2]+j;
                    if ( tIdx[minor1] < dims[minor1] && 
                         tIdx[minor2] < dims[minor2] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    // (b) positive minor1-direction, negative minor2-direction
                    tIdx[minor1] = sIdx[minor1]+j; 
                    tIdx[minor2] = sIdx[minor2]-j;
                    if ( tIdx[minor1] < dims[minor1] && 
                         tIdx[minor2] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    // (c) negative minor1- and minor2-direction
                    tIdx[minor1] = sIdx[minor1]-j; 
                    tIdx[minor2] = sIdx[minor2]-j;
                    if ( tIdx[minor1] > -1 && 
                         tIdx[minor2] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    // (d) negative minor1-direction, positive minor2-direction
                    tIdx[minor1] = sIdx[minor1]-j; 
                    tIdx[minor2] = sIdx[minor2]+j;
                    if ( tIdx[minor1] > -1 && 
                         tIdx[minor2] < dims[minor2] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                }      
            }
        }
        
        // find the cells on the 12 edges 
        for ( k=0; k<3; k++ ) { // x, y and z
            // add cells for all four edges corresponding to one axis
            major  = k;
            minor1 = (major+1)%3;
            minor2 = (major+2)%3;

            sIdx[major]  = idx[major]; 

            // 1. edge
            sIdx[minor1] = idx[minor1]+i; 
            sIdx[minor2] = idx[minor2]+i;
            if ( sIdx[minor1] < dims[minor1] && 
                 sIdx[minor2] < dims[minor2] ) {
                gid = sIdx[0]+dims[0]*(sIdx[1]+sIdx[2]*dims[1]);
                if ( grid[gid].size() ) {
                    list.append(&grid[gid]);
                    nElems += grid[gid].size();
                }
                tIdx[minor1] = sIdx[minor1];
                tIdx[minor2] = sIdx[minor2];
                for ( j=1; j<i; j++ ) {
                    // minor1-direction
                    tIdx[major] = sIdx[major] + j;
                    if ( tIdx[major] < dims[major] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[major] = sIdx[major] - j;
                    if ( tIdx[major] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                }
            }

            // 2. edge
            sIdx[minor1] = idx[minor1]+i; 
            sIdx[minor2] = idx[minor2]-i;
            if ( sIdx[minor1] < dims[minor1] && 
                 sIdx[minor2] > -1 ) {
                gid = sIdx[0]+dims[0]*(sIdx[1]+sIdx[2]*dims[1]);
                if ( grid[gid].size() ) {
                    list.append(&grid[gid]);
                    nElems += grid[gid].size();
                }
                tIdx[minor1] = sIdx[minor1];
                tIdx[minor2] = sIdx[minor2];
                for ( j=1; j<i; j++ ) {
                    // minor1-direction
                    tIdx[major] = sIdx[major] + j;
                    if ( tIdx[major] < dims[major] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[major] = sIdx[major] - j;
                    if ( tIdx[major] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                }
            }

            // 3. edge
            sIdx[minor1] = idx[minor1]-i; 
            sIdx[minor2] = idx[minor2]-i;
            if ( sIdx[minor1] > -1 && 
                 sIdx[minor2] > -1 ) {
                gid = sIdx[0]+dims[0]*(sIdx[1]+sIdx[2]*dims[1]);
                if ( grid[gid].size() ) {
                    list.append(&grid[gid]);
                    nElems += grid[gid].size();
                }
                tIdx[minor1] = sIdx[minor1];
                tIdx[minor2] = sIdx[minor2];
                for ( j=1; j<i; j++ ) {
                    // minor1-direction
                    tIdx[major] = sIdx[major] + j;
                    if ( tIdx[major] < dims[major] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[major] = sIdx[major] - j;
                    if ( tIdx[major] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                }
            }

            // 4. edge
            sIdx[minor1] = idx[minor1]-i; 
            sIdx[minor2] = idx[minor2]+i;
            if ( sIdx[minor1] > -1 && 
                 sIdx[minor2] < dims[minor2] ) {
                gid = sIdx[0]+dims[0]*(sIdx[1]+sIdx[2]*dims[1]);
                if ( grid[gid].size() ) {
                    list.append(&grid[gid]);
                    nElems += grid[gid].size();
                }
                tIdx[minor1] = sIdx[minor1];
                tIdx[minor2] = sIdx[minor2];
                for ( j=1; j<i; j++ ) {
                    // minor1-direction
                    tIdx[major] = sIdx[major] + j;
                    if ( tIdx[major] < dims[major] ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                    tIdx[major] = sIdx[major] - j;
                    if ( tIdx[major] > -1 ) {
                        gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
                        if ( grid[gid].size() ) {
                            list.append(&grid[gid]);
                            nElems += grid[gid].size();
                        }
                    }
                }
            }
        }
        
        // 8 corners

        // 1. corner
        tIdx[0] = idx[0]+i; 
        tIdx[1] = idx[1]+i; 
        tIdx[2] = idx[2]+i;
        if ( tIdx[0] < dims[0] &&
             tIdx[1] < dims[1] &&
             tIdx[2] < dims[2] ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ) {
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
        // 2. corner
        tIdx[0] = idx[0]-i; 
        tIdx[1] = idx[1]+i; 
        tIdx[2] = idx[2]+i;
        if ( tIdx[0] > -1 &&
             tIdx[1] < dims[1] &&
             tIdx[2] < dims[2] ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ) {
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
        // 3. corner
        tIdx[0] = idx[0]+i; 
        tIdx[1] = idx[1]-i; 
        tIdx[2] = idx[2]+i;
        if ( tIdx[0] < dims[0] &&
             tIdx[1] > -1 &&
             tIdx[2] < dims[2] ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ) {
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
        // 4. corner
        tIdx[0] = idx[0]+i; 
        tIdx[1] = idx[1]+i; 
        tIdx[2] = idx[2]-i;
        if ( tIdx[0] < dims[0] &&
             tIdx[1] < dims[1] &&
             tIdx[2] > -1 ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ){
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
        // 5. corner
        tIdx[0] = idx[0]-i; 
        tIdx[1] = idx[1]-i; 
        tIdx[2] = idx[2]+i;
        if ( tIdx[0] > -1 &&
             tIdx[1] > -1 &&
             tIdx[2] < dims[2] ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ) {
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
        // 6. corner
        tIdx[0] = idx[0]+i; 
        tIdx[1] = idx[1]-i; 
        tIdx[2] = idx[2]-i;
        if ( tIdx[0] < dims[0] &&
             tIdx[1] > -1 &&
             tIdx[2] > -1 ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ) {
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
        // 7. corner
        tIdx[0] = idx[0]-i; 
        tIdx[1] = idx[1]+i; 
        tIdx[2] = idx[2]-i;
        if ( tIdx[0] > -1 &&
             tIdx[1] < dims[1] &&
             tIdx[2] > -1 ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ) {
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
        // 8. corner
        tIdx[0] = idx[0]-i; 
        tIdx[1] = idx[1]-i; 
        tIdx[2] = idx[2]-i;
        if ( tIdx[0] > -1 &&
             tIdx[1] > -1 &&
             tIdx[2] > -1 ) {
            gid = tIdx[0]+dims[0]*(tIdx[1]+tIdx[2]*dims[1]);
            if ( grid[gid].size() ) {
                list.append(&grid[gid]);
                nElems += grid[gid].size();
            }
        }
    }
    return nElems;
}

template<class Value> 
int McAuxGrid<Value>::search(const McVec3f & pos, int plusMinus, 
                           McDArray<McDArray<Value> *> &list) 
{
    int key[3];
    computeKey(pos, key);
    return search(key, plusMinus, list);
}

template<class Value> 
int McAuxGrid<Value>::search(int idx[3], int pm[6], 
                           McDArray<McDArray<Value> *> &list)
{
    // resize list and initialize all entries to zero
    int size = (pm[1]-pm[0]+1)*(pm[3]-pm[2]+1)*(pm[5]-pm[4]+1);
    list.resize(size);
    
    // int tmpIdx[3];
    int i, j, k, gid;
    int curItem=0, nElems=0;
    for ( i=idx[0]+pm[0]; i<=idx[0]+pm[1]; i++ ) {
        for ( j=idx[1]+pm[2]; j<=idx[1]+pm[3]; j++ ) {
            for ( k=idx[2]+pm[4]; k<=idx[2]+pm[5]; k++ ) {
                list[curItem++] = &grid[i+dims[0]*(j+k*dims[1])]; 
                nElems += list[curItem++]->size();
            }
        }
    }
    return nElems;
}

template<class Value> 
int McAuxGrid<Value>::search(const McVec3f & pos, int pm[6], 
                           McDArray<McDArray<Value> *> &list)
{
    int key[3];
    computeKey(pos, key);
    return search(key, pm, list);
}

#endif

/// @}
