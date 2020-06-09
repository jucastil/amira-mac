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
#ifndef MC_QUADTREE_H
#define MC_QUADTREE_H

#include "McWinDLLApi.h"

#include "McVec2f.h"
#include "McBox2f.h"
#include "McDArray.h"
#include "McBitfield.h"

#define MEMINCREMENT 15

/** This class implements a quadtree suitable for point location in 2D.
    Elements (cells) of type T can be inserted. The quadtree provides a
    method @c lookup which returns a list of candidate cells a given point
    might be contained in. The template class T has to provide the method

    @code
    int intersect(float box[4], void* userData);
    @endcode

    This method should return 1 if the element intersects the box specified
    by the array @c box, or 0 otherwise. The four entries of @c box denote
    <em> xmin</em>, <em> xmax</em>, <em> ymin</em>, <em> ymax</em>,
    respectively, in that order. The value of @c userData passed over to
    the intersection test method can be specified by setUserData.

    Elements to be inserted into the quadtree are not copied. Instead, a
    pointer to the original element is stored. Consequently, elements must
    not be moved or deleted after they have been inserted into the tree.
    @see McOctree
*/

template <class T>
class McQuadtree {

  public:
    /** Constructor. The argument @c bbox specifies the spatial region
        covered by the quadtree. During insertion of elements this region
        is successively subdivided into smaller subregions. Elements which
        do not intersect the original domain specified by @c bbox will not
        be inserted into any leaf of the quadtree.

        The optional argument @c maxDepth denotes the maximum depth of
        the quadtree, while @c maxElemPerLeaf denotes the maximum number of
        elements stored in a leaf node. If this number is exceeded after
        a new element has been inserted and if the maximum depth of the
        quadtree has not yet been reached, 4 new leafs are created and the
        elements are distributed among the new leafs. A single element
        might be inserted into multiple leafs if the intersection test
        passes multiple times. */
    McQuadtree(float bbox[4], int maxDepth=6, int maxElemPerLeaf=10);

    /// Default constructor.
    McQuadtree();

    /// Destructor (frees all memory).
    ~McQuadtree();

    /** Inserts multiple elements into the quadtree. Elements are not copied,
        but are referenced via a pointer. Therefore, elements must not be
        moved or deleted after insertion. */
    void insert(int n, T* elements);

    /** Inserts a single element into the quadtree. Elements are not
        copied, but are referenced via a pointer. Therefore, elements must
        not be moved or deleted after insertion. */
    void insert(T& element) { insert(0,0,box,&element); }

    /** This methods appends all elements which potentially may contain
        point @c pos to the dynamic array @c result. The array is not cleared
        in advance allowing you to collect results for multiple points. */
    void lookup(const McVec2f& pos, McDArray<T*>& result);

    /**
        This method gives a pointer to elements which potentially may
        contain point @c pos. This method does not use dynamic memory management.
        This method ignores the unique lookup flag.
    */
    void lookupDirect(const McVec2f& pos, unsigned int& nCandidates, T**& candidates);


    /** Same as lookup except that indices instead of pointers are
        returned. Requires prior call to enableUniqueLookup. */
    void lookupIndex(const McVec2f& pos, McDArray<int>& result);

    /** This methods appends all elements which intersect box @c box
        to the dynamic array @c result. The array is not cleared
        in advance allowing you to collect results for multiple boxes. */
    void lookup(const McBox2f& box, McDArray<T*>& result);

    /** Same as lookup except that indices instead of pointers are
        returned. Requires prior call to enableUniqueLookup. */
    void lookupIndex(const McBox2f& bbox, McDArray<int>& result);

    /// Removes all elements and deletes all leafs of the quadtree.
    void clear();

    /// Calls @c clear and initializes quadtree from scratch.
    void init(float bbox[4], int maxDepth=6, int maxElemPerLeaf=10);

    /// Print some statistics to stdout.
    void info();

    /// Returns size of complete quadtree in bytes.
    int memSize();

    /// Returns true if quadtree contains no elements.
    int isEmpty() const { return (allElements[0].n==0); }

    /// Returns maximum depth of quadtree.
    int getMaxDepth() const { return maxDepth; }

    /** Sets maximum depth of quadtree. <b> Note</b>, that the tree is <b> NOT</b>
        reconstructed after call of this method. Therefore, it should be called
        before inserting elements. */
    void setMaxDepth(int val) { maxDepth = val; }

    /// Returns maximum number of elements per leaf.
    int getMaxElemPerLeaf() const { return maxElemPerLeaf; }

    /** Sets maximum number of elements per leaf. <b> Note</b>, that the tree
        is <b> NOT</b> reconstructed after call of this method. Therefore, it
        should be called before inserting elements. */
    void setMaxElemPerLeaf(int val) { maxElemPerLeaf = val; }

    /** Since elements may be inserted into multiple leafs, it is possible
        that a single element is reported multiple times by lookup.
        This behavior can be suppressed if all elements inserted into
        the quadtree are arranged subsequently in a single array. In this
        case a bitfield of the size of the array is allocated. The bitfield
        is used to mark an element the first time it is found.

        The details: @c baseAddress denotes the address of the first element
        of the array, while @c nElements denotes the total size of the
        array. The array index of some element @c elem is computed using
        pointer arithmetic via <tt>&elem - baseAddress</tt>. */
    void enableUniqueLookup(int nElements, const T* baseAddress);

    /// This methods disables unique lookup of quadtree elements.
    void disableUniqueLookup();

    /// Returns current base address.
    const T* getBaseAddress() const { return baseAddress; }

    /// This pointer is passed in any call of @c T::intersect().
    void setUserData(void* userData) { this->userData = userData; }

    /// Returns global bounding box as defined in constructor or @c init.
    void getBoundingBox(float bb[4]) const {
        for (int i=0; i<4; i++) bb[i] = box[i];
    }
    /** Renders all quadtree cells. The array will be filled with line
        segments. Two consecutive points form one line.*/
    void render(McDArray<McVec2f>& points);

    /** Renders all quadtree cells to a postscript file */
    void renderPostscript(const char* file, float magnification=100);

  protected:

    void render(int elem,float elemBox[4], McDArray<McVec2f>& points);

    struct Element {
        unsigned int isLeaf:1;
        unsigned int n:31;
        T** indices;

        Element() { isLeaf=1; n=0; indices=0; }
        ~Element() { if (indices) free(indices); }
    };

    McDArray<Element> allElements;

    void insert(int elem, int depth, const float elemBox[4], T* idx);

    void lookup(int elem, float elemBox[4], const McVec2f& pos,
                McDArray<T*>& result);

    void lookupDirect(int elem, float elemBox[4], const McVec2f& pos,
                      unsigned int& nCandidates, T**& candidates);

    void lookup(int elem, float elemBox[4], const McBox2f& pos,
                McDArray<T*>& result);

    void subdivide(int elem, const float elemBox[4]);

    float box[4];
    int maxDepth;
    int maxElemPerLeaf;
    void* userData;
    const T* baseAddress;
    McBitfield lookupFlags;
};

/// @if EXCLUDETHIS
template <class T>
McQuadtree<T>::McQuadtree(float* box, int maxDepth, int maxElemPerLeaf)
{
    userData = 0;
    init(box, maxDepth, maxElemPerLeaf);
}

template <class T>
McQuadtree<T>::McQuadtree()
{
    userData = 0;
    baseAddress = 0;
    maxDepth = 0;
    maxElemPerLeaf = 0;
    allElements.resize(1);
}

template <class T>
McQuadtree<T>::~McQuadtree()
{
    // Empty, new McDArray frees all memory automatically
}

template <class T>
void McQuadtree<T>::enableUniqueLookup(int n, const T* addr)
{
    baseAddress = addr;
    lookupFlags.resize(n);
    lookupFlags.clearAll();
}

template <class T>
void McQuadtree<T>::disableUniqueLookup()
{
    baseAddress = 0;
    lookupFlags.resize(0);
}

template <class T>
void McQuadtree<T>::clear()
{
    baseAddress = 0;
    lookupFlags.resize(0);

    // Just keep the root node. remax(1,1) is wrong since the root node
    // then would not be marked as a leaf.
    allElements.remax(0,0);
    allElements.resize(1);
}

template <class T>
void McQuadtree<T>::init(float b[4], int depth, int elemPerLeaf)
{
    for (int i=0; i<4; i++)
        box[i] = b[i];

    baseAddress = 0;
    lookupFlags.resize(0);
    maxDepth = depth;
    maxElemPerLeaf = elemPerLeaf;

    // Create root node.
    allElements.resize(0);
    allElements.resize(1);
}

template <class T>
void McQuadtree<T>::insert(int n, T* e)
{
    for (int i=0; i<n; i++)
        insert(0,0,box,e+i);
}

template <class T>
void McQuadtree<T>::insert(int elem, int depth, const float elemBox[4], T* idx)
{
    if (allElements[elem].isLeaf) {
        Element& element = allElements[elem];

        if (depth<maxDepth && (int)element.n>=maxElemPerLeaf) {
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

    float childElemBox[4];
    float xCenter = 0.5f*(elemBox[0]+elemBox[1]);
    float yCenter = 0.5f*(elemBox[2]+elemBox[3]);

    depth++;

    childElemBox[0] = elemBox[0];
    childElemBox[1] = xCenter;
    childElemBox[2] = elemBox[2];
    childElemBox[3] = yCenter;

    if (idx->intersect(childElemBox,userData))
        insert(firstChild+0, depth, childElemBox, idx);

    childElemBox[0] = xCenter;
    childElemBox[1] = elemBox[1];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+1, depth, childElemBox, idx);

    childElemBox[0] = elemBox[0];
    childElemBox[1] = xCenter;
    childElemBox[2] = yCenter;
    childElemBox[3] = elemBox[3];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+2, depth, childElemBox, idx);

    childElemBox[0] = xCenter;
    childElemBox[1] = elemBox[1];
    if (idx->intersect(childElemBox,userData))
        insert(firstChild+3, depth, childElemBox, idx);

}

template <class T>
void McQuadtree<T>::subdivide(int elem, const float elemBox[4])
{
    int childIndex = allElements.size();

    allElements.appendSpace(4);
    Element& element = allElements[elem];

    int nIndices = element.n;

    element.isLeaf = 0;
    element.n = childIndex;

    int i;
    for (i=childIndex; i<childIndex+4; i++) {
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
int McQuadtree<T>::memSize()
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
void McQuadtree<T>::info()
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

    printf("McQuadtree: %d nodes, %d leafs (%.2f MB)\n",
        nNodes-nLeafs, nLeafs, (float) memSize()/(1024*1024));
    printf("McQuadtree: %d elements, (%.2f per leaf, %d...%d)\n",
        nElements, (float)nElements/nLeafs, minNumElements, maxNumElements);
}

template <class T>
void McQuadtree<T>::lookup(const McVec2f& pos, McDArray<T*>& result)
{
    float b[4];
    b[0] = box[0];
    b[1] = box[1];
    b[2] = box[2];
    b[3] = box[3];

    if (pos[0]>=b[0] && pos[0]<=b[1] && pos[1]>=b[2] && pos[1]<=b[3])
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
void McQuadtree<T>::lookupDirect(const McVec2f& pos, unsigned int& nCandidates, T**& candidates)
{
    float b[4];
    b[0] = box[0];
    b[1] = box[1];
    b[2] = box[2];
    b[3] = box[3];

    nCandidates = 0;

    if (pos[0]>=b[0] && pos[0]<=b[1] && pos[1]>=b[2] && pos[1]<=b[3])
        lookupDirect(0,b,pos,nCandidates,candidates);
}

template <class T>
void McQuadtree<T>::lookupIndex(const McVec2f& pos, McDArray<int>& result)
{
    McDArray<T*> tmpResult;
    lookup(pos, tmpResult);

    int n = tmpResult.size();
    for (int i=0; i<n; i++)
        result.append(tmpResult[i] - baseAddress);
}


template <class T>
void McQuadtree<T>::render(McDArray<McVec2f>& points)
{

    McVec2f bb0(box[0],box[2]);
    McVec2f bb1(box[1],box[2]);
    McVec2f bb2(box[1],box[3]);
    McVec2f bb3(box[0],box[3]);
    points.append(bb0); points.append(bb1);
    points.append(bb1); points.append(bb2);
    points.append(bb2); points.append(bb3);
    points.append(bb3); points.append(bb0);
    float b[4];
    b[0] = box[0];
    b[1] = box[1];
    b[2] = box[2];
    b[3] = box[3];
    render(0,b,points);
}


template <class T>
void McQuadtree<T>::lookup(const McBox2f& mbox, McDArray<T*>& result)
{
    float b[4];
    b[0] = box[0];
    b[1] = box[1];
    b[2] = box[2];
    b[3] = box[3];

    lookup(0,b,mbox,result);

    // Ensure that lookupFlags is clean again...
    if (baseAddress) {
        for (int i=result.size()-1; i>=0; i--) {
            int n = result[i] - baseAddress;
            lookupFlags.unset(n);
        }
    }
}

template <class T>
void McQuadtree<T>::lookupIndex(const McBox2f& mbox, McDArray<int>& result)
{
    McDArray<T*> tmpResult;
    lookup(box, tmpResult);

    int n = tmpResult.size();
    for (int i=0; i<n; i++)
        result.append(tmpResult[i] - baseAddress);
}

template <class T>
void McQuadtree<T>::render(int elem,float elemBox[4],McDArray<McVec2f>& points)
{
    Element& element = allElements[elem];
    if (element.isLeaf)
        return;
    int firstChild = element.n;
    float xCenter = 0.5*(elemBox[0]+elemBox[1]);
    float yCenter = 0.5*(elemBox[2]+elemBox[3]);

    points.append(McVec2f(elemBox[0],yCenter));
    points.append(McVec2f(elemBox[1],yCenter));
    points.append(McVec2f(xCenter,elemBox[2]));
    points.append(McVec2f(xCenter,elemBox[3]));

    float ebox[4];
    ebox[0] = elemBox[0];
    ebox[2] = elemBox[2];


    ebox[1] = xCenter;
    ebox[3] = yCenter;
    render(firstChild+0,ebox,points);

    ebox[0] = xCenter;
    ebox[1] = elemBox[1];
    render(firstChild+1,ebox,points);

    ebox[0] = elemBox[0];
    ebox[2] = yCenter;
    ebox[3] = elemBox[3];

    ebox[1] = xCenter;
    render(firstChild+2,ebox,points);

    ebox[0] = xCenter;
    ebox[1] = elemBox[1];
    render(firstChild+3,ebox,points);

}

template <class T>
void McQuadtree<T>::lookup(int elem, float elemBox[4],
                           const McVec2f& pos, McDArray<T*>& result)
{
    Element& element = allElements[elem];

    if (element.isLeaf) {
        for (unsigned int i=0; i<element.n; i++) {
            T* t = element.indices[i];
            if (baseAddress) { // this indicates unique lookup strategy
                int k = t - baseAddress;
                if (lookupFlags[k] == 0) {
                    result.append(t);
                    lookupFlags.set(k);
                }
            } else result.append(t); // t may be appended multiple times
        }

        return;
    }

    int firstChild = element.n;
    float xCenter = 0.5*(elemBox[0]+elemBox[1]);
    float yCenter = 0.5*(elemBox[2]+elemBox[3]);

    int config = 0;
    if (pos[0] > xCenter) config |= 1;
    if (pos[1] > yCenter) config |= 2;

    switch (config) {
        case 0:
            elemBox[1] = xCenter;
            elemBox[3] = yCenter;
            lookup(firstChild+0,elemBox,pos,result);
            break;

        case 1:
            elemBox[0] = xCenter;
            elemBox[3] = yCenter;
            lookup(firstChild+1,elemBox,pos,result);
            break;

        case 2:
            elemBox[1] = xCenter;
            elemBox[2] = yCenter;
            lookup(firstChild+2,elemBox,pos,result);
            break;

        case 3:
            elemBox[0] = xCenter;
            elemBox[2] = yCenter;
            lookup(firstChild+3,elemBox,pos,result);
            break;

    }
}

template <class T>
void McQuadtree<T>::lookupDirect(int elem, float elemBox[4],
                           const McVec2f& pos, unsigned int& nCandidates, T**& candidates)
{
    Element& element = allElements[elem];

    if (element.isLeaf)
    {
        nCandidates  = element.n;
        candidates  = element.indices;
        return;
    }

    int firstChild = element.n;
    float xCenter = 0.5*(elemBox[0]+elemBox[1]);
    float yCenter = 0.5*(elemBox[2]+elemBox[3]);

    int config = 0;
    if (pos[0] > xCenter) config |= 1;
    if (pos[1] > yCenter) config |= 2;

    switch (config) {
        case 0:
            elemBox[1] = xCenter;
            elemBox[3] = yCenter;
            lookupDirect(firstChild+0,elemBox,pos,nCandidates,candidates);
            break;

        case 1:
            elemBox[0] = xCenter;
            elemBox[3] = yCenter;
            lookupDirect(firstChild+1,elemBox,pos,nCandidates,candidates);
            break;

        case 2:
            elemBox[1] = xCenter;
            elemBox[2] = yCenter;
            lookupDirect(firstChild+2,elemBox,pos,nCandidates,candidates);
            break;

        case 3:
            elemBox[0] = xCenter;
            elemBox[2] = yCenter;
            lookupDirect(firstChild+3,elemBox,pos,nCandidates,candidates);
            break;

    }
}

template <class T>
void McQuadtree<T>::renderPostscript(const char* file,float magstep)
{
    McDArray<McVec2f> vertices;
    FILE* f = fopen(file,"w");
    if (!f){
        fprintf(stderr,"Cant open file %s\n", file);
        return;
    }
    fprintf(f,"%%!PS-Adobe-2.0 EPSF-2.0\n");
    fprintf(f,"%%%%BoundingBox: %f %f %f %f\n",
            box[0]*magstep,box[2]*magstep,
            box[1]*magstep,box[3]*magstep);
#ifndef __linux //needarch
    render(vertices);
#endif
    for (int i=0 ; i<vertices.size() ; i+=2)
        fprintf(f,"%f %f moveto %f %f lineto stroke\n",
                vertices[i].x*magstep,vertices[i].y*magstep,
                vertices[i+1].x*magstep,vertices[i+1].y*magstep);

    fclose(f);
}



template <class T>
void McQuadtree<T>::lookup(int elem, float elemBox[4],
                           const McBox2f& mbox, McDArray<T*>& result)
{
    Element& element = allElements[elem];

    if (element.isLeaf) {
        float tb[4];
        for (int i=0; i<(int)element.n; i++) {
            T* t = element.indices[i];
            tb[0] = mbox.min.x;
            tb[1] = mbox.max.x;
            tb[2] = mbox.min.y;
            tb[3] = mbox.max.y;
            if (!t->intersect(tb,userData))
                continue;
            if (baseAddress) { // this indicates unique lookup strategy
                int k = t - baseAddress;
                if (lookupFlags[k] == 0) {
                    result.append(t);
                    lookupFlags.set(k);
                }
            } else result.append(t); // t may be appended multiple times
        }

        return;
    }

    int firstChild = element.n;
    float xCenter = 0.5*(elemBox[0]+elemBox[1]);
    float yCenter = 0.5*(elemBox[2]+elemBox[3]);

    float ebox[4];
    ebox[0] = elemBox[0];
    ebox[2] = elemBox[2];


    ebox[1] = xCenter;
    ebox[3] = yCenter;
    if (McBox2f(ebox[0],ebox[1],ebox[2],ebox[3]).intersect(mbox))
        lookup(firstChild+0,ebox,mbox,result);

    ebox[0] = xCenter;
    ebox[1] = elemBox[1];
    if (McBox2f(ebox[0],ebox[1],ebox[2],ebox[3]).intersect(mbox))
        lookup(firstChild+1,ebox,mbox,result);

    ebox[0] = elemBox[0];
    ebox[2] = yCenter;
    ebox[3] = elemBox[3];

    ebox[1] = xCenter;
    if (McBox2f(ebox[0],ebox[1],ebox[2],ebox[3]).intersect(mbox))
        lookup(firstChild+2,ebox,mbox,result);

    ebox[0] = xCenter;
    ebox[1] = elemBox[1];
    if (McBox2f(ebox[0],ebox[1],ebox[2],ebox[3]).intersect(mbox))
        lookup(firstChild+3,ebox,mbox,result);

}

/// @endif

#endif

/// @}
