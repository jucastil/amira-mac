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

/// @addtogroup hxcore hxcore
/// @{
#ifndef AVL_H
#define AVL_H

template<class T> class AvlTree;

/** node to be inserted into AvlTree.
    This class represents a node to be inserted into an AvlTree
    structure. The class keeps a pointers to some object of type @c T,
    which has to be allocated separatly. This object is used as a key
    within the tree. It has to support the operators @c == (equality)
    and @c > (greater than).
    
    There are also pointers
    to the parent node as well as to the left and right child nodes.
    Finally, the class has an additional integer variable, which says
    something about how good the subtree under this node is balanced.
    The balance information as well as the pointers to the neighbouring
    nodes are all maintained by @c AvlTree.
*/

template<class T> class AvlNode {

    public:
	/// contructor takes pointer to an object of type @c T
	AvlNode(T *i) : ind(i), bal(0), p(0), nr(0), nl(0) { }

	/// returns reference to actual object
	T &	     index() {return *ind;}

	/// returns balancing information for subtree
	int 	     balance() {return bal;}

	/// get right child node
	AvlNode<T>*  rnext() {return nr;}

	/// get left child node
	AvlNode<T>*  lnext() {return nl;}

	/// get parent node
	AvlNode<T>*  parent() {return p;}

    private:
	T *ind;
	int bal;
	AvlNode<T> *p,*nr,*nl;

    friend class AvlTree<T>;
};

/// class representing a balanced binary tree

template<class T> class AvlTree {

    public:
	/// constructor
	AvlTree() { root=0; anz=0; }

	/// reinitializes tree
	void init() { anz=0; root=0; }

	/// these are different traversal strategies
	enum Strategie {before, middle, after};

	/** apply some function to all nodes.
	    The given function is called for every node in the tree.
	    @c strategy determines, if the function is called befor,
	    between, or after recursively traversing the child nodes. */
	void forall(void(*)(AvlNode<T>*,void*),void *user=0,int strategie=middle);

	/// returns total number of nodes
	int number() { return anz; }

	/// returns root node
	AvlNode<T>* troot() { return root; }

	/** insert a new element.
	    This method first checks, if a node with the same key
	    as pointed to by the parameter node is already being
	    present in the tree. If
	    so, the address of that other node is returnd. Otherwise,
	    the given node is inserted into the tree structure and
	    the return value will be equal to the parameter value. */
	AvlNode<T>* insert(AvlNode<T>*);

	/// removes node corresponding to given tree
	void erase(AvlNode<T>*);

	/// search for an object pointed to by the parameter node
	AvlNode<T> *search(AvlNode<T>*);

	/// look for given key
	AvlNode<T> *search(T);

    private:
	int anz;
	AvlNode<T> *root;
	void d_rotation_lr(AvlNode<T>*,AvlNode<T>*,AvlNode<T>*);
	void d_rotation_rl(AvlNode<T>*,AvlNode<T>*,AvlNode<T>*);
	void r_rotation_lr(AvlNode<T>*,AvlNode<T>*,AvlNode<T>*);
	void r_rotation_rl(AvlNode<T>*,AvlNode<T>*,AvlNode<T>*);
	AvlNode<T> *symsucc(AvlNode<T>*);
	void upin(AvlNode<T>*);
	void upout(AvlNode<T>*);
	void fa_before(AvlNode<T>*, void(*)(AvlNode<T>*,void*),void*);
	void fa_middle(AvlNode<T>*, void(*)(AvlNode<T>*,void*),void*);
	void fa_after(AvlNode<T>*, void(*)(AvlNode<T>*,void*),void*);

    friend class AvlNode<T>;
};

/////////////////////////////////////////////////////////////////
//
//  Implementation
//
template<class T>
void AvlTree<T>::forall(void (*fkt)(AvlNode<T>*,void*),void *userptr, 
			int  s)
{
    switch (s) {
	case before : fa_before(root,fkt,userptr); break;
	case middle : fa_middle(root,fkt,userptr); break;
	case after  : fa_after(root,fkt,userptr); break;
    }
}

template<class T>
void AvlTree<T>::fa_before(AvlNode<T> *k, void (*fkt)(AvlNode<T>*,void*),void *userptr)
{
    if(k) {
	(*fkt)(k,userptr);
	fa_before(k->nl,fkt,userptr);
	fa_before(k->nr,fkt,userptr);
    }
}

template<class T>
void AvlTree<T>::fa_middle(AvlNode<T> *k, void (*fkt)(AvlNode<T>*,void*),void *userptr)
{
    if(k) {
	fa_middle(k->nl,fkt,userptr);
	(*fkt)(k,userptr);
	fa_middle(k->nr,fkt,userptr);
    }
}

template<class T>
void AvlTree<T>::fa_after(AvlNode<T> *k, void (*fkt)(AvlNode<T>*,void*),void *userptr)
{
    if(k) {
	fa_after(k->nl,fkt,userptr);
	fa_after(k->nr,fkt,userptr);
	(*fkt)(k,userptr);
    }
}

template<class T>
AvlNode<T> *AvlTree<T>::search(AvlNode<T> *k)
{
    AvlNode<T> *tmp1=root, *tmp2=root;
    while((tmp1) && !(tmp1->index()==k->index())) {
	tmp2=tmp1;
	if(k->index()>tmp1->index()) tmp1=tmp1->nr;
	else tmp1=tmp1->nl;
    }
    if(tmp1) return tmp1; 
    else return tmp2;
}

template<class T>
AvlNode<T> *AvlTree<T>::search(T k)
{
    AvlNode<T> *tmp1=root,*tmp2=root;
    while((tmp1)&&!(tmp1->index()==k)) {
	    tmp2=tmp1;
	    if(k>tmp1->index()) tmp1=tmp1->nr;
	    else tmp1=tmp1->nl;
    }
    if(tmp1) return tmp1;
    else return tmp2;
}

template<class T>
AvlNode<T> *AvlTree<T>::symsucc(AvlNode<T> *k)
{
    AvlNode<T> *tmp=k->nl;
    if(tmp) {
	while(tmp->nr) tmp=tmp->nr;
	return tmp;
    }
    else return k;
}

template<class T>
AvlNode<T>* AvlTree<T>::insert(AvlNode<T> *k)
{
    AvlNode<T> *tmp=search(k);
    if((tmp)&&(tmp->index()==k->index())) return tmp;
    anz++;
    k->p=tmp;
    k->nl=k->nr=0;
    k->bal=0;
    if (tmp) {
	if(k->index()>tmp->index()) tmp->nr=k;
	else tmp->nl=k;
	if((tmp->bal==-1)||(tmp->bal==1)) tmp->bal=0;
	else {
		if(k->index()>tmp->index()) {
			tmp->bal=1;
			upin(tmp);
		}
		else {
			tmp->bal=-1;
			upin(tmp);
		}
	}
    }
    else root=k;
    return k;
}

template<class T>
void AvlTree<T>::d_rotation_lr(AvlNode<T> *k,AvlNode<T> *father,AvlNode<T> *tmp) {
	if(tmp->bal==-1) {
		tmp->bal=0;
		k->bal=0;
		father->bal=1;}
	else if(tmp->bal==1) {
			tmp->bal=0;
			k->bal=-1;
			father->bal=0;}
		else tmp->bal=k->bal=father->bal=0;
	k->nr=tmp->nl;
	father->nl=tmp->nr;
	if(tmp->nl) tmp->nl->p=k;
	if(tmp->nr) tmp->nr->p=father;
	tmp->nl=k;
	tmp->nr=father;
	tmp->p=father->p;
	father->p=tmp;
	k->p=tmp;
	if(tmp->p)
		if(tmp->index()>tmp->p->index()) tmp->p->nr=tmp;
		else tmp->p->nl=tmp;
	else root=tmp;}

template<class T>
void AvlTree<T>::r_rotation_lr(AvlNode<T> *k,AvlNode<T> *father,AvlNode<T> *tmp) {
	father->bal=k->bal=0;
	father->nl=tmp;
	k->p=father->p;
	father->p=k;
	k->nr=father;
	if(tmp) tmp->p=father;
	if(k->p)
		if(k->index()>k->p->index()) k->p->nr=k;
		else k->p->nl=k;
	else root=k;}

template<class T>
void AvlTree<T>::d_rotation_rl(AvlNode<T> *k,AvlNode<T> *father,AvlNode<T> *tmp) {
	if(tmp->bal==1) {
		tmp->bal=0;
		k->bal=0;
		father->bal=-1;}
	else if(tmp->bal==-1) {
			tmp->bal=0;
			k->bal=1;
			father->bal=0;}
		else tmp->bal=k->bal=father->bal=0;
	k->nl=tmp->nr;
	father->nr=tmp->nl;
	if(tmp->nr) tmp->nr->p=k;
	if(tmp->nl) tmp->nl->p=father;
	tmp->nr=k;
	tmp->nl=father;
	tmp->p=father->p;
	father->p=tmp;
	k->p=tmp;
	if(tmp->p)
		if(tmp->index()>tmp->p->index()) tmp->p->nr=tmp;
		else tmp->p->nl=tmp;
	else root=tmp;}

template<class T>
void AvlTree<T>::r_rotation_rl(AvlNode<T> *k,AvlNode<T> *father,AvlNode<T> *tmp) {
	father->bal=k->bal=0;
	father->nr=tmp;
	k->p=father->p;
	father->p=k;
	k->nl=father;
	if(tmp) tmp->p=father;
	if(k->p)
		if(k->index()>k->p->index()) k->p->nr=k;
		else k->p->nl=k;
	else root=k;}

template<class T>
void AvlTree<T>::upin(AvlNode<T> *k) {
	AvlNode<T> *father=k->p;
	while(father){
		if(father->nl==k) {					//linker Sohn
			if(father->bal==1) {
				father->bal=0;
				return;}
			else if(father->bal==0) {
				father->bal=-1;}
				else if(k->bal==-1) {			//Rotation nach rechts
					r_rotation_lr(k,father,k->nr);
					return;}
					else {				//Doppelrotation
						d_rotation_lr(k,father,k->nr);
						return;}}
		else {										//rechter Sohn
			if(father->bal==-1) {
				father->bal=0;
				return;}
			else if(father->bal==0) {
				father->bal=1;}
				else if(k->bal==1) {			//Rotation nach rechts
					r_rotation_rl(k,father,k->nl);
					return;}
					else {				//Doppelrotation
						d_rotation_rl(k,father,k->nl);
						return;}}
		k=father;
		father=k->p;}}

template<class T>
void AvlTree<T>::erase(AvlNode<T>* tmp) {
		if((tmp->nr)&&(tmp->nl)) {
			AvlNode<T> *sym=symsucc(tmp);
			AvlNode<T> *sym_father=sym->p;
			int sym_bal=sym->bal;
			AvlNode<T>* sym_nr=sym->nr;
			AvlNode<T>* sym_nl=sym->nl;

			if (sym_father!=tmp) 
				if(sym_father->nr==sym) sym_father->nr=tmp;
				else sym_father->nl=tmp;
			if(sym->nl) sym->nl->p=tmp;
			tmp->nr->p=sym;
			tmp->nl->p=sym;
			sym->p=tmp->p;
			sym->nr=tmp->nr;
			if (sym_father!=tmp) sym->nl=tmp->nl;
			else sym->nl=tmp;
			sym->bal=tmp->bal;
			if (sym_father!=tmp) tmp->p=sym_father;
			else tmp->p=sym;
			tmp->nl=sym_nl;
			tmp->nr=sym_nr;
			tmp->bal=sym_bal;
			if(sym->p)
				if(sym->p->nr==tmp) sym->p->nr=sym;
				else sym->p->nl=sym;
			else root=sym;}
		if(tmp->nr) {
			tmp->nr->p=tmp->p;
			tmp->nr->bal=0;
			if(tmp->p) {
				if(tmp->p->nr==tmp) tmp->p->nr=tmp->nr;
				else tmp->p->nl=tmp->nr;
				upout(tmp->nr);}
			else root=tmp->nr;}
		else if(tmp->nl) {
				tmp->nl->p=tmp->p;
				tmp->nl->bal=0;
				if(tmp->p) {
					if(tmp->p->nr==tmp) tmp->p->nr=tmp->nl;
					else tmp->p->nl=tmp->nl;
					upout(tmp->nl);}
				else root=tmp->nl;}
			else {
				if(tmp->p) {
					AvlNode<T> *father=tmp->p;
					if(father->nr==tmp) {
						switch(father->bal) {
							case 1: {
								father->nr=0;
								father->bal=0;
								upout(father);
								break;}
							case 0: {
								father->bal=-1;
								father->nr=0;
								break;}
							case -1: {
								AvlNode<T> *left=father->nl;
								father->nr=0;
								switch (left->bal) {
									case 1: {
										AvlNode<T> *y=left->nr;
										left->bal=father->bal=y->bal=0;
										y->nl=left;
										y->nr=father;
										father->nl=0;
										left->nr=0;
										y->p=father->p;
										father->p=y;
										left->p=y;
										if(y->p) {
											if(y->p->nr==father) y->p->nr=y;
											else y->p->nl=y;
											upout(y);}
										else root=y;
										break;}
									case -1: {
										AvlNode<T> *y=left->nl;
										left->bal=father->bal=y->bal=0;
										left->nr=father;
										father->nl=0;
										left->p=father->p;
										father->p=left;
										if(left->p) {
											if(left->p->nr==father) left->p->nr=left;
											else left->p->nl=left;
											upout(left);}
										else root=left;
										break;}
									case 0: {
										AvlNode<T> *tmp=left->nr;
										tmp->nl=left;
										tmp->nr=father;
										left->nr=0;
										father->nl=father->nr=0;
										father->bal=0;
										left->bal=-1;
										tmp->bal=-1;
										tmp->p=father->p;
										left->p=tmp;
										father->p=tmp;
										if(tmp->p) {
											if(tmp->p->nr==father) tmp->p->nr=tmp;
											else tmp->p->nl=tmp;
										}
										else root=tmp;
										break;}}}}}
					else {
						switch(father->bal) {
							case -1: {
								father->bal=0;
								father->nl=0;
								upout(father);
								break;}
							case 0: {
								father->bal=1;
								father->nl=0;
								break;}
							case 1: {
								AvlNode<T> *right=father->nr;
								father->nl=0;
								switch (right->bal) {
									case -1: {
										AvlNode<T> *y=right->nl;
										right->bal=father->bal=y->bal=0;
										y->nr=right;
										y->nl=father;
										father->nr=0;
										right->nl=0;
										y->p=father->p;
										father->p=y;
										right->p=y;
										if(y->p) {
											if(y->p->nr==father) y->p->nr=y;
											else y->p->nl=y;
											upout(y);}
										else root=y;
										break;}
									case 1: {
										AvlNode<T> *y=right->nr;
										right->bal=father->bal=y->bal=0;
										right->nl=father;
										father->nr=0;
										right->p=father->p;
										father->p=right;
										if(right->p) {
											if(right->p->nr==father) right->p->nr=right;
											else right->p->nl=right;
											upout(right);}
										else root=right;
										break;}
									case 0: {
										AvlNode<T> *tmp=right->nl;
										tmp->nr=right;
										tmp->nl=father;
										right->nl=0;
										father->nl=father->nr=0;
										father->bal=0;
										right->bal=1;
										tmp->bal=1;
										tmp->p=father->p;
										right->p=tmp;
										father->p=tmp;
										if(tmp->p) {
											if(tmp->p->nr==father) tmp->p->nr=tmp;
											else tmp->p->nl=tmp;
											}
										else root=tmp;
										break;}}}}}}
					else root=0;}
		anz--;
		}

template<class T>
void AvlTree<T>::upout(AvlNode<T> *k) {
	if(k->p) {
		AvlNode<T> *father=k->p;
		if(k->p->nl==k) {
			switch(father->bal) {
				case -1: {
					father->bal=0;
					upout(father);
					break;}
				case 0: {
					father->bal=1;
					break;}
				case 1: {AvlNode<T> *right=father->nr;
					switch(right->bal) {
						case 0: {
							right->bal=-1;
							father->bal=1;
							k->bal=0;
							father->nr=right->nl;
							right->nl=father;
							right->p=father->p;
							father->p=right;
							if(father->nr) father->nr->p=father;
							if(right->p)
								if(right->p->nr==father) right->p->nr=right;
								else right->p->nl=right;
							else root=right;
							break;}
						case 1: {
							right->bal=0;
							father->bal=0;
							k->bal=0;
							father->nr=right->nl;
							right->nl=father;
							right->p=father->p;
							father->p=right;
							if(father->nr) father->nr->p=father;
							if(right->p) {
								if(right->p->nr==father) right->p->nr=right;
								else right->p->nl=right;
								upout(right);}
							else root=right;
							break;}
						case -1: {
							AvlNode<T> *top=right->nl;
							k->bal=0;
							switch(top->bal) {
								case -1: {
									father->bal=0;
									right->bal=1;
									break;}
								case 0: {
									father->bal=0;
									right->bal=0;
									break;}
								case 1:{
									father->bal=-1;
									right->bal=0;
									break;}}
							top->bal=0;
							right->nl=top->nr;
							top->nr=right;
							father->nr=top->nl;
							top->nl=father;
							top->p=father->p;
							father->p=top;
							right->p=top;
							if(right->nl) right->nl->p=right;
							if(father->nr) father->nr->p=father;
							if(top->p) {
								if(top->p->nr==father) top->p->nr=top;
								else top->p->nl=top;
								upout(top);}
							else root=top;
							break;}}}}} 
		else {
			switch(father->bal) {
				case 1: {
					father->bal=0;
					upout(father);
					break;}
				case 0: {
					father->bal=-1;
					break;}
				case -1: {
					AvlNode<T> *left=father->nl;
					switch(left->bal) {
						case 0: {
							left->bal=1;
							father->bal=-1;
							k->bal=0;
							father->nl=left->nr;
							left->nr=father;
							left->p=father->p;
							father->p=left;
							if(father->nl) father->nl->p=father;
							if(left->p)
								if(left->p->nr==father) left->p->nr=left;
								else left->p->nl=left;
							else root=left;
							break;}
						case -1: {
							left->bal=0;
							father->bal=0;
							k->bal=0;
							father->nl=left->nr;
							left->nr=father;
							left->p=father->p;
							father->p=left;
							if(father->nl) father->nl->p=father;
							if(left->p) {
								if(left->p->nr==father) left->p->nr=left;
								else left->p->nl=left;
								upout(left);}
							else root=left;
							break;}
						case 1: {
							AvlNode<T> *top=left->nr;
							k->bal=0;
							switch(top->bal) {
								case 1: {
									father->bal=0;
									left->bal=-1;
									break;}
								case 0: {
									father->bal=0;
									left->bal=0;
									break;}
								case -1:{
									father->bal=1;
									left->bal=0;
									break;}}
							top->bal=0;
							left->nr=top->nl;
							top->nl=left;
							father->nl=top->nr;
							top->nr=father;
							top->p=father->p;
							father->p=top;
							left->p=top;
							if(left->nr) left->nr->p=left;
							if(father->nl) father->nl->p=father;
							if(top->p) {
								if(top->p->nr==father) top->p->nr=top;
								else top->p->nl=top;
								upout(top);}
							else root=top;
							break;}}}}}}}


#endif

/// @}
