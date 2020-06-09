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

/// @addtogroup molecule molecule
/// @{
#ifndef MTGROUP_H
#define MTGROUP_H

#include <mclib/McDArray.h>

#include "MoleculeWinDLLApi.h"
#include "MtGroupRef.h"

class MolTopology;
class MtGroupRefTranslator;

// ----------------------------------------------------
//                MtGroup

/** Abstract base class for all classes describing an element of
        the topology hierarchy. */
class MOLECULE_API MtGroup {
protected:
    /// Default constructor
    MtGroup()  {}
    
    /// Copy constructor
    MtGroup(const MtGroup& ){ }
public:
    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const = 0;
    /** reset all GroupRefs of (*this) according to  the mapping in @c t
        if @c complete is true it will return whether all subgroups
        are set in @c t, 
        if @c complete is false it will return whether
        at least one of the subgroup (if any) is set in @c t and will remove
        all non set subgroups out of (*this)
        this virtual method of MtGroup does implement this action assuming
        that the group size is fixed, if not this method must be overridden
    **/
    virtual bool translate(MtGroupRefTranslator * t, bool complete=true);
    
    /// Destructor
    virtual ~MtGroup() { }
    
    /// Return the group's number of elements
    virtual int size() const =0;
    /// Return a reference to the @c ixth element
    virtual MtGroupRef operator[](int ix) const =0;
    /// Set the @c ixth element to @c ref
    virtual void setElement(int ix, MtGroupRef ref) = 0;
    /// Print the group's contents to an ostream
    void list(ostream &os, const MolTopology * topo, 
              bool lineBreaks=false) const;
    /// Write group's contents to @c word.
    //    void list(McString &word, MolTopology * topo) const;
    /// Return an empty group adequate for an number of @c N elements
    static MtGroup * createGroup(int N); 
    /// Return a group containing the contents of @c el
    static MtGroup * createGroup(const McDArray<MtGroupRef> & el);

    /// Auxiliary function for listing purposes
    static bool sequenceTest(const char * name1, const char * name2);
};

/** Class describing a single atom as an element of the topology
        hierarchy */
class MOLECULE_API MtAtom : public MtGroup {
public:
    /// Default constructor
    MtAtom() : MtGroup() {}
    /// Copy constructor
    MtAtom(const MtAtom& a) : MtGroup(a) { }

    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const 
    { return new MtAtom(*this); }
    /// Translate the contained MtGroupRefs using t
    virtual bool translate(MtGroupRefTranslator * t, bool complete=true) {return true;}
    /// Return the group's number of elements. In this case =0. 
    int size() const { return 0;}
    /** Return a reference to the @c ixth element. Should never be
        called, as there are no elements. */
    MtGroupRef operator[](int ix) const { assert(0); return MtGroupRef();}
    ///
    void setElement(int ix, MtGroupRef ref) { assert(0); }
};

/** Class describing a small group of atoms, i.e. referencing a
        small number of atoms. Contains a fixed size array for
        storing the atom indices. */
template<int N>
class MtGroupOfAtoms : public MtGroup {
public:
    /// Default constructor
    MtGroupOfAtoms(){}
    /// Copy constructor
    MtGroupOfAtoms(const MtGroupOfAtoms & ga) : MtGroup(ga) {
        memcpy(elements, ga.elements, N*sizeof(int)); 
    }
    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const 
    { return new MtGroupOfAtoms(*this); }
    /// Translate the contained MtGroupRefs using t
    virtual bool translate(MtGroupRefTranslator * t, bool complete=true); 
    /// Return the mtGroup's number of elements 
    int size() const { return N; }
    /// Return a reference to the @c ixth element
    MtGroupRef operator[](int ix) const { 
        assert(0<=ix && ix<N); 
        return MtGroupRef(MtGroupRef::atomLevel,elements[ix]);
    }
    /// Set the @c ixth element to @c ref
    void setElement(int ix, MtGroupRef ref) { 
        assert(0<=ix && ix<N);
        assert(ref.level == MtGroupRef::atomLevel);
        elements[ix]=ref.ix;
    }
    /// List of components
    int elements[N];   
};

template<int N>
bool MtGroupOfAtoms<N>::translate(MtGroupRefTranslator * t, bool complete) { 
    int ix;
    MtGroupRef gRef(MtGroupRef::atomLevel,-1);
    for(ix=0; ix<N; ix++){
        gRef.ix=elements[ix];
        MtGroupRef tRef = t->translate(gRef);
        if(!(tRef.ok()))
            return false;
        assert(tRef.level == MtGroupRef::atomLevel);
        elements[ix] = tRef.ix; 
    }
    return true;
}
// ----------------------------------------------------
//                MtBond

/// Bonds are described as groups of two atoms
class MOLECULE_API MtBond : public MtGroupOfAtoms<2> {
public:
    enum IndexType { SINGLE  =1,
                     DOUBLE  =2,
                     TRIPLE  =3,
                     AROMATIC=4,
                     UNKNOWN =8};
    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const 
    { return new MtBond(*this); }
};
    
    
/** Class describing a small mtGroup, i.e. referencing a small
        number of general elements. Contains a fixed size array for
        storing the references. */
template<int N>
class MOLECULE_API MtSmallGroup : public MtGroup {
public:
    /// Default constructor
    MtSmallGroup(){}
    /// Copy constructor
    MtSmallGroup(const MtSmallGroup & sg) : MtGroup(sg) {
        memcpy(elements, sg.elements, N*sizeof(MtGroupRef)); 
    }
    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const 
    { return new MtSmallGroup(*this); }
    /// Return the mtGroup's number of elements. In this case: N
    int size() const { return N; }
    /// Return a reference to the @c ixth element
    MtGroupRef operator[](int ix) const 
    { assert(0<=ix && ix<N); return elements[ix];}
    /// Set the @c ixth element to @c ref
    void setElement(int ix, MtGroupRef ref) { 
        assert(0<=ix && ix<N);
        elements[ix]=ref;
    }
    /// Fixed size array of components
    MtGroupRef elements[N];   
};

// ----------------------------------------------------
//                IntraLevelRange

/** Class describing a group of general elements from one
        hierarchy level by a range of indices. Contains the index of
        the level and the indices of the first and the last element of
        that level belonging to the group.*/
class MOLECULE_API MtIntraLevelRange : public MtGroup { 
public:
    /// Constructor
    MtIntraLevelRange(int level_) 
        :  level(level_),
           first(0),
          last(0) 
    {}

    /// Constructor
    MtIntraLevelRange(const MtIntraLevelRange & ilr) 
        : MtGroup(ilr),
          level(ilr.level),
          first(ilr.first),
          last(ilr.last) 
    {}
          
    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const
    { return new MtIntraLevelRange(*this); }
    /// Translate the contained MtGroupRefs using t
    virtual bool translate(MtGroupRefTranslator * t,bool complete=true);
    /// Return the group's number of elements
    int size() const { return last-first+1; }
    /// Return a reference to the @c ixth element
    MtGroupRef operator[](int ix) const { 
        assert(0<=ix && ix<=(last-first)); 
        return MtGroupRef(level, first+ix);
    }
    ///
    void setElement(int ix, MtGroupRef ref) {assert(0);}
    /// Level of the contained groups
    int level,
        /// Level-oriented index of the first contained group 
        first, 
        /// Level-oriented index of the last contained group 
        last;
};

// ----------------------------------------------------
//                FixedGroup
    
/** Class describing a general group with an arbitrary number of
        elements from multiple levels. */
class MOLECULE_API MtFixedGroup : public MtGroup { 
public:
    /// Constructor
    MtFixedGroup(int N_) : N(N_)
    { elements = new MtGroupRef[N]; }
    /// Constructor
    MtFixedGroup(const MtFixedGroup & dg) : MtGroup(dg) {
        // cerr << "This is the copy constructor of class MtFixedGroup\n";
        N = dg.N;
        elements = new MtGroupRef[N]; 
        int i;
        for(i=0; i<N; i++){
            elements[i] = dg.elements[i];
        }
    }
    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const 
    { return new MtFixedGroup(*this); }
    /// Destructor
    ~MtFixedGroup() { 
        if(elements)
            delete [] elements; 
    }
    /// Return the group's number of elements
    int size() const { return N;}

    /// Return a reference to the @c ixth element
    MtGroupRef operator[](int ix) const 
    { assert(0<=ix && ix<N); return elements[ix];}
    /// Set the @c ixth element to @c ref
    void setElement(int ix, MtGroupRef ref) { 
        assert(0<=ix && ix<N);
        elements[ix]=ref;
    }
    ///
    int N;
    /// List of components
    MtGroupRef * elements;   
};

// ----------------------------------------------------
//                DynamicGroup

/** Class describing a general group with an arbitrary number of
        elements from multiple levels. */
class MOLECULE_API MtDynamicGroup : public MtGroup { 

    McDArray<MtGroupRef> elements;
public:
    /// Constructor
    MtDynamicGroup() { }

    /// Constructor
    MtDynamicGroup(const MtDynamicGroup & dg) 
        : MtGroup(dg),
          elements(dg.elements)
    {
    }

    /// Duplicate this MtGroup regarding polymorphy
    virtual MtGroup * clone() const 
    { return new MtDynamicGroup(*this); }
    
    /// Destructor
    ~MtDynamicGroup() { 
    }
    
    /** translate all group refs of this group by using a MtGroupRefTranslator
        if complete==false all groups that had no translation will be removed
        else if complete==true the translation will be halted and false 
        will be returned
    */
    virtual bool translate(MtGroupRefTranslator * t, bool complete=true);
    
    /// Return the group's number of elements
    int size() const { return elements.size();}
    
    /// Return a reference to the @c ixth element
    MtGroupRef operator[](int ix) const { return getElement(ix);}
    
    /// Set the @c ixth element to @c ref
    MtGroupRef getElement(int ix) const { 
        assert(0<=ix && ix<elements.size());
        return elements[ix];
    }

    /// add ref at the end of array
    void addElement(MtGroupRef ref) { elements.push_back(ref); }
    ///
    void removeElement(int ix) { elements.remove(ix);}

    /// set the ix'th element of array to ref
    void setElement(int ix, MtGroupRef ref) { 
        assert(0<=ix && ix<elements.size());
        elements[ix]=ref;
    }

    /// remax the array
    void remax(int max) {
        elements.remax(max);
    }
    void resize(int size) {
        elements.resize(size);
    }
};    
    
#endif

/// @}
