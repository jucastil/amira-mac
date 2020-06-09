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
#ifndef MC_OCTREE_H
#define MC_OCTREE_H

#include "McWinDLLApi.h"

#include "McVec3f.h"
#include "McBox3f.h"
#include "McDArray.h"
#include "McBitfield.h"

#define MEMINCREMENT 15

/** This class implements an octree suitable for point location in 3D.
    Elements (cells) of type T can be inserted. The octree provides a
    method @c lookup which returns a list of candidate cells a given point
    might be contained in. The template class T has to provide the method

    @code
    int intersect(const McBox3f &box, void* userData);
    @endcode

    This method should return 1 if the element intersects the box specified
    by the array @c box, or 0 otherwise. The value of @c userData passed over to
    the intersection test method can be specified by setUserData.

    Elements to be inserted into the octree are not copied. Instead, a
    pointer to the original element is stored. Consequently, elements must
    not be moved or deleted after they have been inserted into the tree.
    @see McQuadtree
*/

template <class T>
class McOctree {

  public:
    /** Constructor. The argument @c bbox specifies the spatial region
        covered by the octree. During insertion of elements this region
        is successively subdivided into smaller subregions. Elements which
        do not intersect the original domain specified by @c bbox will not
        be inserted into any leaf of the octree.

        The optional argument @c maxDepth denotes the maximum depth of
        the octree, while @c maxElemPerLeaf denotes the maximum number of
        elements stored in a leaf node. If this number is exceeded after
        a new element has been inserted and if the maximum depth of the
        octree has not yet been reached, 8 new leafs are created and the
        elements are distributed among the new leafs. A single element
        might be inserted into multiple leafs if the intersection test
        passes multiple times. */
    McOctree(const McBox3f &bbox, int maxDepth=6, int maxElemPerLeaf=10);

    /// Default constructor.
    McOctree();

    /// Destructor (frees all memory).
    virtual ~McOctree();

    /** Inserts multiple elements into the octree. Elements are not copied,
        but are referenced via a pointer. Therefore, elements must not be
        moved or deleted after insertion. */
    void insert(int n, T* elements);

    /** Inserts a single element into the octree. Elements are not
        copied, but are referenced via a pointer. Therefore, elements must
        not be moved or deleted after insertion. */
    void insert(T& element) { insert(0,0,box,&element); }

    /** This method removes an element from the octree */
    void remove(T& element) { remove(0, box, &element); }

    /**@name lookup methods */
    //@{
    /** This method appends all elements which potentially may contain
        point @c pos to the dynamic array @c result. The array is not cleared
        in advance allowing you to collect results for multiple points. */
    void lookup(const McVec3f& pos, McDArray<T*>& result);

    /** Same as lookup except that indices instead of pointers are
        returned. Requires prior call to enableUniqueLookup. */
    void lookupIndex(const McVec3f& pos, McDArray<int>& result);

    /** This methods appends all elements that intersect a given box. */
    void lookup(const McBox3f &queryBox, McDArray<T*>& result);

    /** Same as lookup except that indices instead of pointers are
        returned. Requires prior call to enableUniqueLookup. */
    void lookupIndex(const McBox3f& queryBox, McDArray<int>& result);
    //@}

    /// Removes all elements and deletes all leafs of the octree.
    void clear();

    /// Calls @c clear and initializes octree from scratch.
    void init(const McBox3f &bbox, int maxDepth=6, int maxElemPerLeaf=10);

    /// Print some statistics to stdout.
    void info();

    /// Returns size of complete octree in bytes.
    int memSize();

    /// Returns true if octree contains no elements.
    int isEmpty() const { return (allElements[0].n==0); }

    /// Returns maximum depth of octree.
    int getMaxDepth() const { return maxDepth; }

    /** Sets maximum depth of octree. The tree is not restructured
        in this call, so call this method before inserting elements. */
    void setMaxDepth(int val) { maxDepth = val; }

    /// Returns maximum number of elements per leaf.
    int getMaxElemPerLeaf() const { return maxElemPerLeaf; }

    /** Sets maximum number of elements per leaf. The tree is not restructured
        in this call, so call this method before inserting elements. */
    void setMaxElemPerLeaf(int val) { maxElemPerLeaf = val; }

    /** Since elements may be inserted into multiple leafs, it is possible
        that a single element is reported multiple times by lookup.
        This behavior can be suppressed if all elements inserted into
        the octree are arranged subsequently in a single array. In this
        case a bitfield of the size of the array is allocated. The bitfield
        is used to mark an element the first time it is found.

        The details: @c baseAddress denotes the address of the first element
        of the array, while @c nElements denotes the total size of the
        array. The array index of some element @c elem is computed using
        pointer arithmetic via <tt>&elem - baseAddress</tt>. */
    void enableUniqueLookup(int nElements, const T* baseAddress);

    /// This methods disables unique lookup of octree elements.
    void disableUniqueLookup();

    /// Returns current base address.
    const T* getBaseAddress() const { return baseAddress; }

    /// This pointer is passed in any call of @c T::intersect().
    void setUserData(void* userData) { this->userData = userData; }

    /// Returns global bounding box as defined in constructor or @c init.
    void getBoundingBox(McBox3f &bb) const { bb = box; }

    /** for each cell call the virtual function workProc,
        which may be overloaded by derived classes. Returns 1 if operation was interrupted.*/
    int iterateCells(int leafsOnly=1);

    /// Called for each (leaf) cell (elem) from iterateCells. The depth
    /// and box as well as a (virtual) 3D cell index on this depth is
    /// provided. returns 1 to break iteration
    virtual int workProc(int elem, int depth, const McBox3f &elemBox, int i, int j, int k) { return 0; }

  protected:

    int iterateCells(int elem, int depth, const McBox3f &elemBox,
                     int leafsOnly, int i,int j,int k);

    struct Element {
        unsigned int isLeaf:1;
        unsigned int n:31;
        T** indices;

        Element() { isLeaf=1; n=0; indices=0; }
        ~Element() { if (indices) free(indices); }

        void remove(int remN, McBitfield &remElems) {
            int oldN = n;
            n -= remN;
            if ((n % MEMINCREMENT) == 0) { // decrease size of memory
                T** oldIndices = indices;
                indices = (T**) malloc(n*sizeof(T*));
                for (int oldI=0, i=0; oldI<oldN; oldI++) {
                    if (!remElems[oldI]) {
                        indices[i] = oldIndices[oldI]; i++;
                    }
                }
                free(oldIndices);
            }
            else { // just move items (same size of memory)
                for (int oldI=0, i=0; oldI<oldN; oldI++) {
                    if (!remElems[oldI]) {
                        indices[i] = indices[oldI]; i++;
                    }
                }
            }
        }
    };

    McDArray<Element> allElements;

    void insert(int elem, int depth, const McBox3f &elemBox, T* idx);

    void remove(int elem, const McBox3f &elemBox, const T* toBeDeleted);

    void lookup(int elem, McBox3f &elemBox, const McVec3f& pos, McDArray<T*>& result);

    void lookup(int elem, const McBox3f &elemBox, const McBox3f& queryBox, McDArray<T*>& result);

    void subdivide(int elem, const McBox3f &elemBox);

    McBox3f box;
    int maxDepth;
    unsigned int maxElemPerLeaf;
    void* userData;
    const T* baseAddress;
    McBitfield lookupFlags;
};

/// @if EXCLUDETHIS

template <class T>
McOctree<T>::McOctree(const McBox3f &box, int maxDepth, int maxElemPerLeaf)
{
    userData = 0;
    init(box, maxDepth, maxElemPerLeaf);
}

template <class T>
McOctree<T>::McOctree()
{
    userData = 0;
    baseAddress = 0;
    maxDepth = 0;
    maxElemPerLeaf = 0;
    allElements.resize(1);
}

template <class T>
McOctree<T>::~McOctree()
{
    // Empty, new McDArray frees all memory automatically
}

template <class T>
void McOctree<T>::enableUniqueLookup(int n, const T* addr)
{
    baseAddress = addr;
    lookupFlags.resize(n);
    lookupFlags.clearAll();
}

template <class T>
void McOctree<T>::disableUniqueLookup()
{
    baseAddress = 0;
    lookupFlags.resize(0);
}

template <class T>
void McOctree<T>::clear()
{
    baseAddress = 0;
    lookupFlags.resize(0);

    // Just keep the root node. remax(1,1) is wrong since the root node
    // then would not be marked as a leaf.
    allElements.remax(0,0);
    allElements.resize(1);
}

template <class T>
void McOctree<T>::init(const McBox3f &b, int depth, int elemPerLeaf)
{
    box = b;

    baseAddress = 0;
    lookupFlags.resize(0);
    maxDepth = depth;
    maxElemPerLeaf = elemPerLeaf;

    // Create root node.
    allElements.resize(0);
    allElements.resize(1);
}

template <class T>
void McOctree<T>::insert(int n, T* e)
{
    for (int i=0; i<n; i++)
        insert(0,0,box,e+i);
}

template <class T>
void McOctree<T>::insert(int elem, int depth, const McBox3f &elemBox, T* idx)
{
    if (allElements[elem].isLeaf) {
        Element& element = allElements[elem];

        if (depth<maxDepth && element.n>=maxElemPerLeaf) {
            subdivide(elem, elemBox);
            goto DESCEND;
        }

        if (element.n % MEMINCREMENT == 0) {
            int newSize = element.n + MEMINCREMENT;
            if (element.indices) element.indices =
                (T**) realloc(element.indices, newSize*sizeof(T*));
            else element.indices = (T**) malloc(newSize*sizeof(T*));
        }

        element.indices[element.n++] = idx;
        return;
    }

    DESCEND:

    int firstChild = allElements[elem].n;

    McVec3f center = elemBox.getCenter();

    depth++;

    McBox3f childElemBox(elemBox.getMin(), center);

    if (idx->intersect(childElemBox,userData))
        insert(firstChild+0, depth, childElemBox, idx);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+1, depth, childElemBox, idx);

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = center.y;
    childElemBox[3] = elemBox[3];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+2, depth, childElemBox, idx);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+3, depth, childElemBox, idx);

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = elemBox[2];
    childElemBox[3] = center.y;
    childElemBox[4] = center.z;
    childElemBox[5] = elemBox[5];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+4, depth, childElemBox, idx);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+5, depth, childElemBox, idx);

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = center.y;
    childElemBox[3] = elemBox[3];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+6, depth, childElemBox, idx);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+7, depth, childElemBox, idx);
}

template <class T>
int McOctree<T>::iterateCells(int leafsOnly)
{
    return iterateCells(0,0,box,leafsOnly,0,0,0);
}

template <class T>
int McOctree<T>::iterateCells(int elem, int depth, const McBox3f &elemBox,
                               int leafsOnly, int i, int j, int k)
{
    Element& element = allElements[elem];
    if (element.isLeaf || !leafsOnly) {
        if (workProc(elem, depth, elemBox,i,j,k))
            return 1;
    }
    if (element.isLeaf)
        return 0;

    int firstChild = element.n;

    McVec3f center = elemBox.getCenter();

    depth++;
    i*=2; j*=2; k*=2;
    McBox3f childElemBox(elemBox.getMin(), center);

    if (iterateCells(firstChild+0, depth, childElemBox, leafsOnly,i,j,k))
        return 1;

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (iterateCells(firstChild+1, depth, childElemBox, leafsOnly,i+1,j,k))
        return 1;

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = center.y;
    childElemBox[3] = elemBox[3];
    if (iterateCells(firstChild+2, depth, childElemBox, leafsOnly,i,j+1,k))
        return 1;

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (iterateCells(firstChild+3, depth, childElemBox, leafsOnly,i+1,j+1,k))
        return 1;

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = elemBox[2];
    childElemBox[3] = center.y;
    childElemBox[4] = center.z;
    childElemBox[5] = elemBox[5];
    if (iterateCells(firstChild+4, depth, childElemBox, leafsOnly,i,j,k+1))
        return 1;

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (iterateCells(firstChild+5, depth, childElemBox, leafsOnly,i+1,j,k+1))
        return 1;

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = center.y;
    childElemBox[3] = elemBox[3];
    if (iterateCells(firstChild+6, depth, childElemBox, leafsOnly,i,j+1,k+1))
        return 1;

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (iterateCells(firstChild+7, depth, childElemBox, leafsOnly,i+1,j+1,k+1))
        return 1;
    return 0;
}

template <class T>
void McOctree<T>::subdivide(int elem, const McBox3f &elemBox)
{
    int childIndex = allElements.size();

    allElements.appendSpace(8);
    Element& element = allElements[elem];

    int nIndices = element.n;

    element.isLeaf = 0;
    element.n = childIndex;

    int i;
    for (i=childIndex; i<childIndex+8; i++) {
        allElements[i].isLeaf = 1;
        allElements[i].n = 0;
        allElements[i].indices = 0;
    }

    for (i=0; i<nIndices; i++)
        insert(elem,999,elemBox,element.indices[i]);

    if (element.indices) {
        free(element.indices);
        element.indices = 0;
    }
}

template <class T>
int McOctree<T>::memSize()
{
    int bytes = allElements.size() * sizeof(Element);

    for (int i=allElements.size()-1; i>=0; i--) {
        Element& element = allElements[i];
        if (element.isLeaf) {
            int n = element.n / MEMINCREMENT;
            bytes += (n+1)*MEMINCREMENT*sizeof(int);
        }
    }

    return bytes;
}

template <class T>
void McOctree<T>::info()
{
    int nNodes = allElements.size();
    int nLeafs = 0;
    int nElements = 0;
    int minNumElements = 999999;
    int maxNumElements = 0;

    for (int i=0; i<nNodes; i++) {
        Element& node = allElements[i];
        if (node.isLeaf) {
            nLeafs++;
            int n = node.n;
            if (n < minNumElements)
                minNumElements = n;
            if (n > maxNumElements)
                maxNumElements = n;
            nElements += n;
        }
    }

    printf("McOctree: %d nodes, %d leafs (%.2f MB)\n",
        nNodes-nLeafs, nLeafs, (float) memSize()/(1024*1024));
    printf("McOctree: %d elements, (%.2f per leaf, %d...%d)\n",
        nElements, (float)nElements/nLeafs, minNumElements, maxNumElements);
}

template <class T>
void McOctree<T>::lookup(const McVec3f& pos, McDArray<T*>& result)
{
    McBox3f b(box);

    if (b.contains(pos))
        lookup(0,b,pos,result);

    // Ensure that lookupFlags is clean again...
    if (baseAddress) {
        for (int i=result.size()-1; i>=0; i--) {
            int n = result[i] - baseAddress;
            lookupFlags.unset(n);
        }
    }
}

template <class T>
void McOctree<T>::lookup(const McBox3f& queryBox, McDArray<T*>& result)
{
    McBox3f b(box);

    if (b.intersects(queryBox))
        lookup(0, b, queryBox, result);

    // Ensure that lookupFlags is clean again...
    if (baseAddress) {
        for (int i=result.size()-1; i>=0; i--) {
            int n = result[i] - baseAddress;
            lookupFlags.unset(n);
        }
    }
}

template <class T>
void McOctree<T>::lookupIndex(const McBox3f& queryBox, McDArray<int>& result)
{
    McDArray<T*> tmpResult;
    lookup(queryBox, tmpResult);

    int n = tmpResult.size();
    for (int i=0; i<n; i++)
        result.append(tmpResult[i] - baseAddress);
}

template <class T>
void McOctree<T>::lookup(int elem, const McBox3f &elemBox, const McBox3f& queryBox, McDArray<T*>& result)
{
    Element& element = allElements[elem];

    if (element.isLeaf) {
        for (unsigned int i=0; i<element.n; i++) {
            T* t = element.indices[i];

            if (t->intersect(queryBox,userData)) {
                if (baseAddress) { // this indicates unique lookup strategy
                    int k = t - baseAddress;
                    if (lookupFlags[k] == 0) {
                        result.append(t);
                        lookupFlags.set(k);
                    }
                } else
                    result.append(t); // t may be appended multiple times
            }
        }
        return;
    }

    int firstChild = element.n;

    McVec3f center = elemBox.getCenter();

    // These intersection tests are faster than the generic McBox3f member function
    // ---
    if (queryBox.getMin().x < center.x && queryBox.getMin().y < center.y && queryBox.getMin().z < center.z){
        McBox3f childElemBox(elemBox.getMin(), center);
        lookup(firstChild+0, childElemBox, queryBox, result);
    }

    //
    if (queryBox.getMax().x > center.x && queryBox.getMin().y < center.y && queryBox.getMin().z < center.z){
        McBox3f childElemBox(center.x, elemBox.getMax().x, elemBox.getMin().y, center.y, elemBox.getMin().z, center.z);
        lookup(firstChild+1, childElemBox, queryBox, result);
    }

    //
    if (queryBox.getMin().x < center.x && queryBox.getMax().y > center.y && queryBox.getMin().z < center.z){
        McBox3f childElemBox(elemBox.getMin().x, center.x, center.y, elemBox.getMax().y, elemBox.getMin().z, center.z);
        lookup(firstChild+2, childElemBox, queryBox, result);
    }

    //
    if (queryBox.getMax().x > center.x && queryBox.getMax().y > center.y && queryBox.getMin().z < center.z){
        McBox3f childElemBox(center.x, elemBox.getMax().x, center.y, elemBox.getMax().y, elemBox.getMin().z, center.z);
        lookup(firstChild+3, childElemBox, queryBox, result);
    }

    //
    if (queryBox.getMin().x < center.x && queryBox.getMin().y < center.y && queryBox.getMax().z > center.z){
        McBox3f childElemBox(elemBox.getMin().x, center.x,  elemBox.getMin().y, center.y, center.z, elemBox.getMax().z);
        lookup(firstChild+4, childElemBox, queryBox, result);
    }

    //
    if (queryBox.getMax().x > center.x && queryBox.getMin().y < center.y && queryBox.getMax().z > center.z){
        McBox3f childElemBox(center.x, elemBox.getMax().x, elemBox.getMin().y, center.y, center.z, elemBox.getMax().z);
        lookup(firstChild+5, childElemBox, queryBox, result);
    }

    //
    if (queryBox.getMin().x < center.x && queryBox.getMax().y > center.y && queryBox.getMax().z > center.z){
        McBox3f childElemBox(elemBox.getMin().x, center.x, center.y, elemBox.getMax().y, center.z, elemBox.getMax().z);
        lookup(firstChild+6, childElemBox, queryBox, result);
    }

    //
    if (queryBox.getMax().x > center.x && queryBox.getMax().y > center.y && queryBox.getMax().z > center.z){
        McBox3f childElemBox(center, elemBox.getMax());
        lookup(firstChild+7, childElemBox, queryBox, result);
    }
}

template <class T>
void McOctree<T>::lookupIndex(const McVec3f& pos, McDArray<int>& result)
{
    McDArray<T*> tmpResult;
    lookup(pos, tmpResult);

    int n = tmpResult.size();
    for (int i=0; i<n; i++)
        result.append(tmpResult[i] - baseAddress);
}

template <class T>
void McOctree<T>::lookup(int elem, McBox3f &elemBox, const McVec3f& pos, McDArray<T*>& result)
{
    Element& element = allElements[elem];

    if (element.isLeaf) {
        for (unsigned int i=0; i<element.n; i++) {
            T* t = element.indices[i];
            if (baseAddress) { // this indicates unique lookup strategy
                unsigned int k = t - baseAddress;
                if (lookupFlags[k] == 0) {
                    result.append(t);
                    lookupFlags.set(k);
                }
            } else result.append(t); // t may be appended multiple times
        }

        return;
    }

    int firstChild = element.n;

    McVec3f center = elemBox.getCenter();

    int config = 0;

    if (pos.x > center.x){
        elemBox[0] = center.x;
        config |= 1;
    } else
        elemBox[1] = center.x;

    if (pos.y > center.y){
        elemBox[2] = center.y;
        config |= 2;
    } else
        elemBox[3] = center.y;

    if (pos.z > center.z){
        elemBox[4] = center.z;
        config |= 4;
    } else
        elemBox[5] = center.z;

    lookup(firstChild+config, elemBox, pos, result);
}

template <class T>
void McOctree<T>::remove(int elem, const McBox3f &elemBox, const T* toBeDeleted)
{
    Element& element = allElements[elem];

    if (element.isLeaf) {
        McBitfield remElems(element.n);
        remElems.unsetAll();
        const T* t;
        int remN = 0;
        // always remove all appearances of elemPtr
        for (unsigned int i=0; i<element.n; i++) {
            t = element.indices[i];
            if (t == toBeDeleted) { remElems.set(i); remN++; }
        }
        if (remN) element.remove(remN, remElems);
        return;
    }

    int firstChild = allElements[elem].n;

    McVec3f center = elemBox.getCenter();

    McBox3f childElemBox(elemBox.getMin(), center);

    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+0, childElemBox, toBeDeleted);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+1, childElemBox, toBeDeleted);

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = center.y;
    childElemBox[3] = elemBox[3];
    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+2, childElemBox, toBeDeleted);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+3, childElemBox, toBeDeleted);

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = elemBox[2];
    childElemBox[3] = center.y;
    childElemBox[4] = center.z;
    childElemBox[5] = elemBox[5];
    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+4, childElemBox, toBeDeleted);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+5, childElemBox, toBeDeleted);

    childElemBox[0] = elemBox[0];
    childElemBox[1] = center.x;
    childElemBox[2] = center.y;
    childElemBox[3] = elemBox[3];
    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+6, childElemBox, toBeDeleted);

    childElemBox[0] = center.x;
    childElemBox[1] = elemBox[1];
    if (toBeDeleted->intersect(childElemBox,userData))
        remove(firstChild+7, childElemBox, toBeDeleted);

}

/// @endif

#endif

/// @}
