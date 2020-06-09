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
#ifndef MC_STATIC_OCTREE_H
#define MC_STATIC_OCTREE_H

#include "McWinDLLApi.h"
#include "McVec3f.h"
#include "McDArray.h"

#include <stdio.h>

/** This class provides a static octree for point location purposes.
    Regardless of how many elements are being inserted into the data
    structure always @f$2^{(3*n)}@f$ leafs will be created for an octree with
    n levels. Compared to an adaptive octree like McOctree memory
    requirements and time needed for insertion can be better for a
    static tree if the elements are homogeneously distributed in space.

    Insertion of elements into the leafs is done by considering their
    bounding box. Elements will be inserted into multiple leafs if they
    intersect the bounding boxes of all these leafs. The bounding box
    of an element need not to be stored permanently, but is specified as
    an argument of the insertion method.
*/

template <class T>
class McStaticOctree
{
  public:
    /// Initializes octree.
    McStaticOctree(float box[6], int nLevels=2);

    /// Default constructor.
    McStaticOctree();

    /// Destructor.
    ~McStaticOctree();

    /// Reinitializes octree.
    void init(float box[6], int levels=2);

    /// Insert element into all intersecting leafs of octree.
    void insert(const T& element, float bBoxOfElement[6]);

    /// Return all elements stored in leaf @c pos is located in.
    McDArray<T>* lookup(const McVec3f& pos) const;

    /// Returns spatial region covered by octree.
    void getBoundingBox(float box[6]) const;

    /// Prints some information about the octree to stdout.
    void info() const;

    /// Deletes all elements and leafs of octree.
    void clear() { nLevels=0; allElements.remax(0,0); }

    /// Returns number of octree levels.
    int getNumLevels() const { return nLevels; }

    /// Remax dynamic arrays in all leafs.
    void remax();

  protected:
    int nLevels;
    float bb[6];
    McDArray< McDArray<T> > allElements;

    void insert(const T& element, float ebox[6], int index,
        float x0, float y0, float z0, float x1, float y1, float z1, int lev);
    McDArray<T>* lookup(const McVec3f& pos, int index,
        float x0, float y0, float z0, float x1, float y1, float z1, int) const;
};

/// @if EXCLUDETHIS

template <class T>
McStaticOctree<T>::McStaticOctree(float box[6], int nLevels)
{
    init(box,nLevels);
}

template <class T>
McStaticOctree<T>::McStaticOctree()
{
    nLevels = 0;
}

template <class T>
McStaticOctree<T>::~McStaticOctree()
{
}

template <class T>
void McStaticOctree<T>::init(float box[6], int n)
{
    for (int k=allElements.size()-1; k>=0; k--)
        allElements[k].resize(0);

    nLevels = n;
    for (int i=0; i<6; i++)
        bb[i] = box[i];

    int nElements = 1 << (3*n);
    allElements.resize(nElements);
}

template <class T>
void McStaticOctree<T>::insert(const T& element, float ebox[6])
{
    insert(element,ebox,0,bb[0],bb[2],bb[4],bb[1],bb[3],bb[5],nLevels-1);
}

template <class T>
McDArray<T>* McStaticOctree<T>::lookup(const McVec3f& pos) const
{
    return lookup(pos,0,bb[0],bb[2],bb[4],bb[1],bb[3],bb[5],nLevels-1);
}

template <class T>
void McStaticOctree<T>::getBoundingBox(float box[6]) const
{
    for (int i=0; i<6; i++)
        box[i] = bb[i];
}

template <class T>
void McStaticOctree<T>::info() const
{
    int nElements = 0;
    int minNumElem = 100000;
    int maxNumElem = 0;
    size_t nLeafs = 1 << (3*nLevels);
    size_t bytes = sizeof(*this) + nLeafs*sizeof(McDArray<T>);

    for (int i=0; i<allElements.size(); i++) {
        int nElem = allElements[i].size();
        nElements += nElem;
        if (nElem < minNumElem) minNumElem = nElem;
        if (nElem > maxNumElem) maxNumElem = nElem;
        bytes += allElements[i].getMax()*sizeof(T);
    }

    printf("McStaticOctree: %d levels, %d leafs (%.2f MB)\n",
        nLevels, (int)nLeafs, (float) bytes/(1024.*1024.));
    printf("McStaticOctree: %d elements (%.2f per leaf, %d...%d)\n",
        nElements, (float) nElements/nLeafs, minNumElem, maxNumElem);
}

template <class T>
void McStaticOctree<T>::remax()
{
    for (int i=0; i<allElements.size(); i++)
        allElements[i].remax();
}

template <class T>
void McStaticOctree<T>::insert(const T& element, float ebox[6], int index,
    float x0, float y0, float z0, float x1, float y1, float z1, int level)
{
    float x = 0.5f*(x0+x1);
    float y = 0.5f*(y0+y1);
    float z = 0.5f*(z0+z1);

    if (level) {
        int k = 1 << (3*level);

        if (ebox[0]<x && ebox[2]<y && ebox[4]<z)
            insert(element, ebox, index+0*k, x0, y0, z0, x, y, z, level-1);
        if (ebox[1]>=x && ebox[2]<y && ebox[4]<z)
            insert(element, ebox, index+1*k, x, y0, z0, x1, y, z, level-1);
        if (ebox[0]<x && ebox[3]>=y && ebox[4]<z)
            insert(element, ebox, index+2*k, x0, y, z0, x, y1, z, level-1);
        if (ebox[1]>=x && ebox[3]>=y && ebox[4]<z)
            insert(element, ebox, index+3*k, x, y, z0, x1, y1, z, level-1);
        if (ebox[0]<x && ebox[2]<y && ebox[5]>=z)
            insert(element, ebox, index+4*k, x0, y0, z, x, y, z1, level-1);
        if (ebox[1]>=x && ebox[2]<y && ebox[5]>=z)
            insert(element, ebox, index+5*k, x, y0, z, x1, y, z1, level-1);
        if (ebox[0]<x && ebox[3]>=y && ebox[5]>=z)
            insert(element, ebox, index+6*k, x0, y, z, x, y1, z1, level-1);
        if (ebox[1]>=x && ebox[3]>=y && ebox[5]>=z)
            insert(element, ebox, index+7*k, x, y, z, x1, y1, z1, level-1);
    } else {
        if (ebox[0]<x && ebox[2]<y && ebox[4]<z)
            allElements[index+0].append(element);
        if (ebox[1]>=x && ebox[2]<y && ebox[4]<z)
            allElements[index+1].append(element);
        if (ebox[0]<x && ebox[3]>=y && ebox[4]<z)
            allElements[index+2].append(element);
        if (ebox[1]>=x && ebox[3]>=y && ebox[4]<z)
            allElements[index+3].append(element);
        if (ebox[0]<x && ebox[2]<y && ebox[5]>=z)
            allElements[index+4].append(element);
        if (ebox[1]>=x && ebox[2]<y && ebox[5]>=z)
            allElements[index+5].append(element);
        if (ebox[0]<x && ebox[3]>=y && ebox[5]>=z)
            allElements[index+6].append(element);
        if (ebox[1]>=x && ebox[3]>=y && ebox[5]>=z)
            allElements[index+7].append(element);
    }
}

template <class T>
McDArray<T>* McStaticOctree<T>::lookup(const McVec3f& pos, int index,
    float x0, float y0, float z0, float x1, float y1, float z1, int level) const
{
    float x = 0.5f*(x0+x1);
    float y = 0.5f*(y0+y1);
    float z = 0.5f*(z0+z1);

    if (level) {
        int k = 1 << (3*level);

        if (pos[0]<x && pos[1]<y && pos[2]<z)
            return lookup(pos, index+0*k, x0, y0, z0, x, y, z, level-1);
        if (pos[0]>=x && pos[1]<y && pos[2]<z)
            return lookup(pos, index+1*k, x, y0, z0, x1, y, z, level-1);
        if (pos[0]<x && pos[1]>=y && pos[2]<z)
            return lookup(pos, index+2*k, x0, y, z0, x, y1, z, level-1);
        if (pos[0]>=x && pos[1]>=y && pos[2]<z)
            return lookup(pos, index+3*k, x, y, z0, x1, y1, z, level-1);
        if (pos[0]<x && pos[1]<y && pos[2]>=z)
            return lookup(pos, index+4*k, x0, y0, z, x, y, z1, level-1);
        if (pos[0]>=x && pos[1]<y && pos[2]>=z)
            return lookup(pos, index+5*k, x, y0, z, x1, y, z1, level-1);
        if (pos[0]<x && pos[1]>=y && pos[2]>=z)
            return lookup(pos, index+6*k, x0, y, z, x, y1, z1, level-1);
        if (pos[0]>=x && pos[1]>=y && pos[2]>=z)
            return lookup(pos, index+7*k, x, y, z, x1, y1, z1, level-1);
    } else {
        if (pos[0]<x && pos[1]<y && pos[2]<z)
            return (McDArray<T>*) &allElements[index+0];
        if (pos[0]>=x && pos[1]<y && pos[2]<z)
            return (McDArray<T>*) &allElements[index+1];
        if (pos[0]<x && pos[1]>=y && pos[2]<z)
            return (McDArray<T>*) &allElements[index+2];
        if (pos[0]>=x && pos[1]>=y && pos[2]<z)
            return (McDArray<T>*) &allElements[index+3];
        if (pos[0]<x && pos[1]<y && pos[2]>=z)
            return (McDArray<T>*) &allElements[index+4];
        if (pos[0]>=x && pos[1]<y && pos[2]>=z)
            return (McDArray<T>*) &allElements[index+5];
        if (pos[0]<x && pos[1]>=y && pos[2]>=z)
            return (McDArray<T>*) &allElements[index+6];
        if (pos[0]>=x && pos[1]>=y && pos[2]>=z)
            return (McDArray<T>*) &allElements[index+7];
    }

    return 0;
}

/// @endif

#endif

/// @}
