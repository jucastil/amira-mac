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
#ifndef MC_SPACE_TREE_H
#define MC_SPACE_TREE_H

#include "McVec2f.h"
#include "McVec3f.h"
#include "McBox2f.h"
#include "McBox3f.h"

#include "McScopedPtr.h"
#include "McSArray.h"
#include "McDArray.h"

#include "McAssert.h"

namespace McSpacetree_details
{
    template<int DIM, class TYPE>
    struct VecType {
    };

    template<>
    struct VecType<2,float>
    {
        typedef McVec2f Type;
    };

    template<>
    struct VecType<3,float>
    {
        typedef McVec3f Type;
    };

    template<int DIM, class TYPE>
    struct BoxType {
    };

    template<>
    struct BoxType<2,float>
    {
        typedef McBox2f Type;
    };

    template<>
    struct BoxType<3,float>
    {
        typedef McBox3f Type;
    };
}


/**
    Dynamic Quadtree/Ocrtee/... class for any dimension
*/
template<class T,int DIM, typename DATA_TYPE=float>
class McSpacetree
{
public:

    typedef typename McSpacetree_details::BoxType<DIM,DATA_TYPE>::Type BoxType;
    typedef typename McSpacetree_details::VecType<DIM,DATA_TYPE>::Type VecType;

    enum {NChildren = 1<<DIM};

    /**
        Creates an empty octree. The status is uninisitailzed.
    */
    McSpacetree() : m_maxDepth(0)
    {}

    /**
        Checks if the octree is initialized.
    */
    bool isInitialized() {
        return m_root;
    }

    /**
        Clears the octree. Push the tree back in uninitialized state.
    */
    void clear() {
        m_root = 0;
    }

    /**
        Prints some info about this octree to stdout.
    */
    void info();

    /**
        Initializes the octree with the given elements.

    */
    template<class IntersectFun>
    void init(const McDArray<T>& elements, IntersectFun intersect, BoxType bbox, int maxAllowedDepth, int nMaxLeafElements)
    {

        {
            McDArray<T> lElements = elements;
            m_root = new Node(bbox,0);
            m_root->setElements(lElements);
            m_maxDepth = 0;
        }

        McDArray<Node*> nodeStack;

        nodeStack.push(m_root.ptr());

        while (nodeStack.size() > 0) {
            Node* node;
            nodeStack.pop(node);

            // check if the current node has to be splitted up:
            if (node->size() < nMaxLeafElements ||
                node->depth() >= maxAllowedDepth) continue;

            // the given node has to be splitted up
            {
                McSArray<BoxType,NChildren> subBBoxes = calcSubBBoxes(node->bbox());
                McDArray<T> lElements;
                node->makeInnerNode(lElements);

                // distribute the elements to the child container
                McDArray<T> childElements[NChildren];
                for (int i=0;i<lElements.size();i++) {
                    for (int j=0;j<NChildren;j++) {
                        if (intersect.intersect(lElements[i],subBBoxes[j])) {
                            childElements[j].append(lElements[i]);
                        }
                    }
                }

                // create a new Node for every non-empty container:
                for (int j=0;j<NChildren;j++) {
                    if (childElements[j].size()) {
                        Node* child = new Node(subBBoxes[j],node->depth()+1);
                        if (child->depth() > m_maxDepth) m_maxDepth = child->depth();
                        child->setElements(childElements[j]);
                        node->setChild(j,child);
                        nodeStack.push(child);
                    }
                }
            }
        }
    }


    int getMaxDepth() {
        return m_maxDepth;
    }

    McDArray<T>* lookup(const VecType& pos);



protected:
    class Node;

    McScopedPtr<Node> m_root;
    int               m_maxDepth;


    McSArray<BoxType,NChildren> calcSubBBoxes(const BoxType& bbox)
    {
        McSArray<BoxType,NChildren> subBoxes;

        VecType center = bbox.getCenter();
        for (int i=0;i<NChildren;i++) {
            VecType corner;
            for (int iDim=0;iDim<DIM;iDim++)
                corner[iDim] = ((i>>iDim)%2) ? bbox.getMax()[iDim] : bbox.getMin()[iDim];

            subBoxes[i] = BoxType(center,corner);
        }

        return subBoxes;
    }

    int        idxChild(const BoxType& bbox, const VecType& pos);




    class Node {
    public:
        Node(BoxType bbox, int depth) : m_children(0)
                                       ,m_depth(depth)
                                       ,m_bbox(bbox)
        {
            m_elements = new McDArray<T>();
        }

        bool isLeaf() {
            return m_elements;
        }

        void setChild(int idxChild, Node* child) {
            mcassert(!isLeaf());
            mcassert(idxChild >=0 && idxChild<NChildren);

            (*m_children)[idxChild] = child;
        }

        Node* getChild(int idxChild) {
            mcassert(!isLeaf());
            mcassert(idxChild>=0 && idxChild<NChildren);

            return (*m_children)[idxChild].ptr();
        }

        void setElements(McDArray<T>& elements) {
            mcassert(isLeaf());
            m_elements->clear();
            m_elements->swapWith(elements);
        }

        BoxType bbox() {
            return m_bbox;
        }

        int depth() {
            return m_depth;
        }

        mclong size() {
            mcassert(isLeaf());
            return m_elements->size();
        }

        McDArray<T>* elementPtr() {
            return m_elements.ptr();
        }

        /**
            Transforms this Node from a leaf node into a inner (non leaf) node.
            Stores the elements of this leaf node into the array given by the parameter.
        */
        void makeInnerNode(McDArray<T>& elements) {
            mcassert(isLeaf());
            elements.swapWith(*m_elements);

            m_elements = 0;

            m_children = new McSArray<McScopedPtr<Node>,NChildren>();
        }

    protected:

        McScopedPtr<McSArray<McScopedPtr<Node>,NChildren> > m_children;
        McScopedPtr<McDArray<T> >      m_elements;
        int        m_depth;
        BoxType    m_bbox;
    };

    void gatherInfo(Node* node, int& nElements, int& nLeafs, int& nInner, int& minNumElem, int& maxNumElem, int& bytes);

private:
    // do not allow copy construction. Default copy constructor would
    // not work, as McScopedPtr does not has a copy constructor.
    McSpacetree(McSpacetree&);
};

template<class T,int DIM, typename DATA_TYPE>
void McSpacetree<T,DIM,DATA_TYPE>::gatherInfo(Node* node, int& nElements, int& nLeafs, int& nInner, int& minNumElem, int& maxNumElem,int& bytes)
{
    if (!node) return;

    bytes += sizeof(Node);
    if (node->isLeaf()) {
        nLeafs++;
        bytes += sizeof(McDArray<T>);
        nElements += (node->elementPtr())->size();
        bytes += (int)sizeof(T)*(node->elementPtr())->getMax();
        if (minNumElem == -1 || minNumElem > (node->elementPtr())->size())
            minNumElem = (node->elementPtr())->size();
        if (maxNumElem < (node->elementPtr())->size())
            maxNumElem = (node->elementPtr())->size();
    } else {
        nInner++;
        bytes += sizeof(McSArray<McScopedPtr<Node>,NChildren>);
        for (int i=0;i<NChildren;i++) {
            gatherInfo(node->getChild(i),nElements,nLeafs,nInner,minNumElem,maxNumElem,bytes);
        }
    }
}

template<class T,int DIM, typename DATA_TYPE>
void McSpacetree<T,DIM,DATA_TYPE>::info() {
    if (!isInitialized()) return;

    int nElements = 0;
    int nLeafs    = 0;
    int nInner    = 0;
    int minNumElem = -1;
    int maxNumElem = 0;
    int bytes = sizeof(*this);

    gatherInfo(m_root.ptr(),nElements,nLeafs,nInner,minNumElem,maxNumElem,bytes);

    printf("McSpacetree: maxDepth: %d, leafs: %d, innerNodes: %d (%.2f MB)\n",
                                m_maxDepth,nLeafs,nInner,(float) bytes/(1024.*1024.));

    printf("McSpacetree: %d elements (%.2f per leaf, %d...%d\n",
                     nElements,(float) nElements/nLeafs,minNumElem,maxNumElem);
}

template<class T,int DIM, typename DATA_TYPE>
McDArray<T>* McSpacetree<T,DIM,DATA_TYPE>::lookup(const VecType& pos) {
    mcassert(m_root);

    Node* node = m_root.ptr();

    while (node && !node->isLeaf()) {
        int idx = idxChild(node->bbox(),pos);
        node = node->getChild(idx);
    }

    if (node) {
        mcassert(node->isLeaf());
        return node->elementPtr();
    }
    return 0;

};


template<class T,int DIM, typename DATA_TYPE>
int McSpacetree<T,DIM,DATA_TYPE>::idxChild(const BoxType& bbox, const VecType& pos) {
    VecType center = bbox.getCenter();

    int idxChild = 0;
    for (int iDim=0;iDim<DIM;iDim++)
        if (center[iDim] < pos[iDim]) idxChild += (1<<iDim);

    return idxChild;
}

#endif

/// @}
