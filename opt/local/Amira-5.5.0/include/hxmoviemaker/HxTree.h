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

/// @addtogroup hxmoviemaker hxmoviemaker
/// @{
#ifndef _HX_TREE_h
#define _HX_TREE_h

#include <mclib/McPrimType.h>


template <class T>
class HxTree
{
  public:

    HxTree();
    virtual ~HxTree();

    /*
    add a tree node as child
    @param pt
      node to add
    */
    void  addAsChild(T * pt);

    /// unhook (not delete) this tree-node from its parent node
    void  unhookThis();

    /// unhook (not delete) all child tree-nodes
    void  unhookChilds();

    /// unhook and delete all child tree-nodes
    void  clearDelChilds();

    /**
    get parent node
    @return
      pointer to the parent node; 0 if there is none
    */
    T * getParent();

    /**
    get next sibling node (siblings have the same parent node)
    @return
      pointer to the next sibling; 0 if there is none
    */
    T * getNextSibling();

    /**
    get next sibling node (siblings have the same parent node) wrapped
    @return
      pointer to the next sibling;
      pointer to the first child of parent node if there is none;
      0 if there is none
    */
    T * getNextSiblingWrapped();

    /**
    get previous sibling node (siblings have the same parent node)
    @return
      pointer to the previous sibling; 0 if there is none
    */
    T * getPrevSibling();

    /**
    get first child node
    @return
      pointer to the first child; 0, if there is none
    */
    T * getFirstChild();

    /**
    get first node of the tree
    @return
      pointer to first tree node
    */
    T * getFirst();

    /**
    get next node of the tree
    @return
      pointer to next tree node; 0 if there is no forther node
    */
    T * getNext();

    /**
    get next node of the tree wrapped
    @return
      pointer to next tree node; 
      pointer to the first tree node if the last was the last one;
      0 if there is no first node;
    */
    T * getNextWrapped();

    /**
    get root node
    @return
      pointer to the root node
    */
    T * getRoot();

    /**
    get 
    @return
      number of nodes in this tree
    @warning look into the implementation if you want to use this method
    */
    mclong getCount();


  public:

    T * parent;
    T * sibling;
    T * child;

    T * curr; // for traversing via getFirst()/getNext()
};


////////////////////////////////////////////////////////////////////////////////
template <class T>
inline HxTree<T>::HxTree()
:parent(0), sibling(0), child(0), curr(0)
{
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline HxTree<T>::~HxTree()
{
  unhookThis();
  unhookChilds();
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline void  HxTree<T>::addAsChild(T * pt)
{
  if(pt)
  {
    if(pt->parent)
      pt->unhookThis();

    //<a> hang into tree
    pt->sibling = child;
    pt->parent  = (T *)this;
    child       = pt;
  }
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline void  HxTree<T>::unhookThis()
{
  HxTree * pt;

  //<a> Adjust sibling chain, remove this from the linear linked list
  if(parent)
  {
    pt = parent->child;

    if(pt==this)
    {
      parent->child = sibling;
    }
    else
    {
      //<a> search predecessor in sibling chain
      while(pt->sibling != this)
        pt = pt->sibling;
      pt->sibling = sibling;
    }
  }
  parent  = 0;
  sibling = 0;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline void  HxTree<T>::unhookChilds()
{
  HxTree * pt;
  
  if(child)
  {
    pt = child;
    while(pt) 
    {
      pt->parent = 0;
      pt = pt->sibling;
    }
  }
  child = 0;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getParent()
{
  return parent;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getFirstChild()
{
  return child;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getNextSibling()
{
  return sibling;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getNextSiblingWrapped()
{
  if(sibling)
    return sibling;

  if(parent)
    return parent->child;

  //<a> no way to get the first sibling in the chain
  assert(0);
  return 0;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getPrevSibling()
{
  if(!parent)
    return 0;

  HxTree * pt;
  pt = parent->child;

  if(pt==this)
    return 0;

  //<a> search predecessor in sibling chain
  while(pt->sibling != this)
    pt = pt->sibling;
  return (T *) pt;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline void  HxTree<T>::clearDelChilds()
{
  HxTree * pt;
  HxTree * ptmp;
  
  if(child)
  {
    pt = child;
    while(pt) 
    {
      pt->clearDelChilds();
      ptmp = pt;
      pt = pt->sibling;
      delete ptmp;
    }
  }
  child = 0;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getRoot()
{
  T * pe  = (T *)this;
  T * pep = parent;

  while(pep)
  {
    pe  = pep;
    pep = pe->parent;
  }

  return pe;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getFirst()
{
  curr = child;
  return (T *)this;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getNext()
{
  T * ret;

  //<a> all nodes already given
  if(!curr)
    return 0;

  //<a> first curr, then the childs
  if(curr->child)
  {
    ret  = curr;
    curr = curr->child;
    return ret;
  }

  //<ass> no more childs

  //<a> next is sibling
  if(curr->sibling)
  {
    ret  = curr;
    curr = curr->sibling;
    return ret;
  }

  //<ass> there are no more siblings
  ret = curr;
  while(!curr->sibling)
  {
    curr = curr->parent;
    if(!curr || (curr==this))
    {
      curr = 0;
      return ret; // no more nodes
    }
  }
  curr = curr->sibling;
  return ret;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline T * HxTree<T>::getNextWrapped()
{
  T * ret = getNext();

  if(ret)
    return ret;

  ret = getFirst();

  return ret;
}




////////////////////////////////////////////////////////////////////////////////
template <class T>
inline mclong HxTree<T>::getCount()
{
  T * oldCurr = curr;

  T * c = getFirst();
  // was ist das denn ??? (malte)
  //XULONG ret = 0;

  mclong ret = 0;

  while(c)
  {
    ret++;
    c = getNext();
  }
  curr = oldCurr;
  return ret;
}

#endif // _HX_TREE_h
 

/// @}
