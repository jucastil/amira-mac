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
#ifndef MC_FHEAP
#define MC_FHEAP

#include "McWinDLLApi.h"
#include "McDArray.h"

#include <stdio.h>
#include <assert.h>

/// Base class for all elements to be inserted in McFHeap.
class McFHeapElement {
public:
    /// Default constructor.
    McFHeapElement() { touched=0;}
    /// Parent.
    McFHeapElement* parent;
    /// Child.
    McFHeapElement* child;
    /// Next sibling.
    McFHeapElement* nextSib;
    /// Previous sibling.
    McFHeapElement* prevSib;
    ///
    unsigned int rank:31;
    ///
    unsigned int flag:1;
    ///
    int touched;
};

/** This class implements a Fibonacci heap. The template parameter should
    be derived from McFHeapElement and should provide an
    @c operator<(). The major characteristics of the heap are constant time
    complexity (amortized) for the methods @c deleteElem(), @c insert() and @c getMin().
    The method @c deleteMin() has complexity @c O(log(N)). */

template <class T>
class McFHeap {

  public:
    /// Constructor.
    McFHeap() { root=0; ctr=0; }

    /// This methods inserts an element into the heap.
    void insert(T*);

    /// Returns pointer to minimal element or NULL, if heap is empty.
    T* getMin() { return ((T*)root); }

    /// Deletes and returns minimal element, if heap is not empty.
    T* deleteMin();

    /// Deletes and returns an arbitrary element of the heap.
    T* deleteElem(McFHeapElement* a);

  protected:
    int ctr;
    McFHeapElement* root;
    McDArray < McFHeapElement* > A;

    void addChild(McFHeapElement* a, McFHeapElement* b);
    void deleteChild(McFHeapElement* a);
    McFHeapElement* link(McFHeapElement* a, McFHeapElement* b);
    void cascadeCut(McFHeapElement* a);

    int isSmaller(McFHeapElement* a, McFHeapElement* b) {
	return ((*(T*)a) < (*(T*)b));
    }

  public:
    int isConsistent();

    int isConsistent(McFHeapElement* r);

    void untouch(McFHeapElement* r);
};

/// @if EXCLUDETHIS

template < class T >
void McFHeap<T>::untouch(McFHeapElement* r) {
    McFHeapElement* a = r;

    do {
	a->touched=0;
	a = a->nextSib;
    } while(a!=r);

    do {
	if (a->child)
	    untouch(a->child);
	a = a->nextSib;
    } while(a!=r);
}

template < class T >
int McFHeap<T>::isConsistent() {
    int r =  1;//isConsistent(root);
    //untouch(root);
    return r;
}

template < class T >
int McFHeap<T>::isConsistent(McFHeapElement* r) {

	McFHeapElement* a = r;

	int cnt=0;
	do {
	  if (a->touched) {
	    fprintf(stderr,"McFHeap: inconsistency detected\n");
	    assert(0);
	    return 0;
	  }
	  a->touched=1;
	  a = a->nextSib;
	    cnt++;
 	} while(a!=r && cnt<=ctr);

	if (cnt>ctr) {
	    fprintf(stderr,"McFHeap: inconsistency 2\n");
	    assert(0);
	    return 0;
	}
	cnt=0;
	do {
	    int ok =1;
	    if (a->child)
		ok = isConsistent(a->child);
	    if (!ok)
		return(0);
 	    a = a->nextSib;
	    cnt++;
 	} while(a!=r && cnt<=ctr);

	return 1;
    }

template < class T >
McFHeapElement* McFHeap<T>::link(McFHeapElement* a, McFHeapElement* b)
{
    isConsistent();

  McFHeapElement* hilf;
  int elemBfound=0;
  //sind a und b beide in der root-Liste?
  hilf = a;

  do{

    hilf=hilf->nextSib;
    if (hilf == b){
	elemBfound=1;
	break;
    }

  }
  while (hilf!=a);

  if (elemBfound != 1){
      printf("This never happens\n");
    //a and b are not both in root-list
    if (isSmaller(a,b)) {
      addChild(a,b);
      return a;
    }

    else {
      addChild(b,a);
      return b;
    }

  }
  else{

      //a and b are Sibs
      if (a==root || (isSmaller(a,b) && b!=root)) {
	  if (a==root)
	      assert(!isSmaller(b,a));

	  assert(b!=root);
	  deleteChild(b);
	  b->nextSib=b;
	  b->prevSib=b;
	  addChild(a,b);
	  return a;

      } else {
	  assert(a!=root);
	  deleteChild(a);
	  a->nextSib=a;
	  a->prevSib=a;
	  addChild(b,a);
	  return b;
      }
  }
}


template < class T >
void McFHeap<T>::addChild(McFHeapElement* a, McFHeapElement* b)
  //b has no Sibs
  //b becomes child of a
{
  if (a->rank == 0){
    a->child=b;
    b->nextSib=b;
    b->prevSib=b;
  }
  else{
    a->child->nextSib->prevSib=b;
    b->nextSib=a->child->nextSib;
    a->child->nextSib=b;
    b->prevSib=a->child;

  }
  a->rank++;
  b->parent=a;
}


template < class T >
void McFHeap<T>::deleteChild(McFHeapElement* a)
  //deletes a in its own Sibs-list (= root-list)
{
    assert(a!=root);
    a->prevSib->nextSib=a->nextSib;
    a->nextSib->prevSib=a->prevSib;
}


template < class T >
void McFHeap<T>::insert(T* elem)
  //inserts element without children into root-list
{
  elem->flag=0;
  elem->child=0;
  elem->rank=0;
  elem->parent=0;

  if (root == 0){
    elem->nextSib=elem;
    elem->prevSib=elem;
    root=elem;
  }
  else{
    elem->nextSib=root->nextSib;
    root->nextSib->prevSib=elem;
    root->nextSib=elem;
    elem->prevSib=root;

    if (isSmaller(elem,root))
      root = elem;
  }

  ctr++;

}


template < class T >
T* McFHeap<T>::deleteMin()
  //deletes minimum element (=root element)
  //and does necessary linking
{
  McFHeapElement* hilf;
  McFHeapElement* start;
  McFHeapElement* min;

  if (root->child !=0){
    //all children get parent=0
    hilf=root->child;

    do{
      hilf->parent=0;
      hilf=hilf->nextSib;
    }
    while (hilf->parent != 0);

    if (root->nextSib != root){
      start = root->nextSib;
      //concatenate childrens list with root list
      McFHeapElement* a=root->nextSib;
      McFHeapElement* b=root->prevSib;

      b->nextSib = root->child;
      a->prevSib = root->child->prevSib;
      root->child->prevSib->nextSib = a;
      root->child->prevSib = b;
    }

    else {
      //root has no Sibs
      //childrens list automatically = new root list
      start = root->child;
      }
  }

  else {
    //root has no children
    if (root->nextSib == root) {
      root=0;
      return 0;
    }
    else{
      start = root->nextSib;
      McFHeapElement* tmp = root;
      root=0;
      deleteChild(tmp);
    }

  }


  //search for new minimum in root list

  min = start;
  hilf = start;

  do{

    hilf=hilf->nextSib;
    if (isSmaller(hilf,min))
      min = hilf;
  }
  while (hilf !=start);
  root = min;
  isConsistent();

  //linking step:

  int r,stop;
  A.resize(0);

  hilf = root;
  do {

    stop=0;
    McFHeapElement* nextElem;

    nextElem = hilf->nextSib;
    do {
	r=hilf->rank;

        if (r >= A.size()) {
	  int n = A.size();
	  A.resize(r+1);
          for (int i=n; i<=r; i++)
	    A[i] =0;
	}

	if (A[r]==0){
	  A[r]=hilf;
	  stop=1;
	}
	else{
	    //printf("link: %f  %f \n",A[r]->value,hilf->value);
	    isConsistent();
	    hilf=link(A[r],hilf);
	    isConsistent();
	    A[r]=0;
	}
    } while (stop==0);
    hilf = nextElem;

  } while (hilf!=root);

  return (T*) root;
}

template < class T >
void McFHeap<T>::cascadeCut(McFHeapElement* a)
{
  // cuts links between a and a->parent and puts a into root-list
    assert(a!=root);
    assert(a->parent);

    McFHeapElement* par;
    par = a->parent;

    assert(a->parent->rank>0);

    a->parent->rank--;

    if (a->nextSib ==a){
	a->parent->child = 0;
    }
    else{
	if (a->parent->child==a) {
	    a->parent->child = a->nextSib;
	}
	deleteChild(a);
    }
    a->parent=0;
    McFHeapElement* n = root->nextSib;
    n->prevSib = a;
    a->nextSib = n;
    a->prevSib = root;
    root->nextSib = a;

    if (par!=0){

	if (par->flag == 0) par->flag=1;
	else{
	    // par lost its 2nd child
	    par->flag = 0;
	    if (par->parent)
		cascadeCut(par);
	}
    }

}


template < class T >
T* McFHeap<T>::deleteElem(McFHeapElement* a)
{
  McFHeapElement* h;

  isConsistent();

  if (a==root){
    deleteMin();
  }

  else{
    int stop=0;
    h=root->nextSib;
    while (h != root) {
      if (a==h){
	stop=1;
	break;
      }
      h=h->nextSib;
    }
    if (stop == 1){
      //element is in root-list

      if (a->child !=0){
	//all children get parent=0
	h=a->child;
	do{
	  h->parent=0;
	  h=h->nextSib;
	}
	while (h->parent != 0);


	//concatenate childrens list with root list
	//and deleting a
	McFHeapElement* n=a->nextSib;
	McFHeapElement* p=a->prevSib;

	p->nextSib = a->child;
	n->prevSib = a->child->prevSib;
	a->child->prevSib->nextSib = n;
	a->child->prevSib = p;
      }
      else{
	//a has no children
	deleteChild(a);
      }

    }

    else{
      // not in root-list

      McFHeapElement* par = a->parent;
      a->parent->rank--;


      if (a->child !=0){
	//a has children
	//all children get parent=0
	h=a->child;
	do{
	    h->parent=0;
	    h=h->nextSib;
	}
	while (h->parent != 0);

	//concatenate childrens list with root list
	//without deleting in root list
	McFHeapElement* n=root->nextSib;

	n->prevSib=a->child->prevSib;
	a->child->prevSib->nextSib=n;
	root->nextSib=a->child;
	a->child->prevSib=root;

	if (a->parent->rank ==0){
	    //a was only child
	   a->parent->child=0;
	   a=0;
	}
	else{
	    //a had Sibs
	    if (a->parent->child ==a) a->parent->child = a->nextSib;
	    a->parent = 0;
	    a->child=0;
	    deleteChild(a);
	}

      }//if a has children

      else {
	//a has no children
	if (a->parent->rank ==0){
	  //a was only child
	  a->parent->child=0;
	  a=0;
	}
	else{
	  //a had Sibs
	  if (a->parent->child ==a) a->parent->child = a->nextSib;
	  a->parent = 0;
	  a->child=0;
	  deleteChild(a);
	}
      }//a has no children

      if (par!=0){

	if (par->flag == 0) par->flag=1;
	else{
	  // par lost 2nd child
	  par->flag = 0;
	  if (par->parent)
	      cascadeCut(par);
	}
      }


    }// a not in root list

  }//a != root
  return (T*) root;
}

/// @endif

#endif

/// @}
