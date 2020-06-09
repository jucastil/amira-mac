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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_SMARTS_H
#define MOLCHEM_SMARTS_H

#include "MolChemWinDLLApi.h"
#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McDArray.h>

class McString;
class McBitfield;

namespace molchem {

    class BondExpression;
    class AtomExpression;
    class Atom;
    class Bond;
    class Logger;
    class Molecule;
    class Graph;

    // -----------------------------------------------------------------------------
    // -
    // -                               AtomSpecification
    // -
    // -----------------------------------------------------------------------------

    /* An Atomspecification contains all info regarding a single atom */
    class MOLCHEM_API AtomSpecification : public McHandable
    {
    public:
        AtomSpecification(AtomExpression* a,int component,int bindingIx);
        AtomSpecification();
        AtomSpecification(AtomExpression* a);
        void setComponentIx(int ix);
        void setBindingIx(int ix);
        int getComponentIx() const { return component;}
        int getBindingIx() const { return bix; }
        bool isMasked() const {return masked;}
        void setMasked(bool m) {masked = m;}
        AtomExpression* getExpression() const { return expr;}
        bool getChiralFlag() const {return chiral_flag;}
        // Returns whether the atom matches the description in the Atom Expression
        bool test(const Atom* a) const;
        /* Searches for first Property Expression of given type. Returns its value in v.
           Returns false if not found. Search will traverse graph through AND and OR expressions but not through NOT expression.
           This method is mainly for use in SMIRKS strings where on the product side, such properties are only defined uniquely.*/
        bool getPropertyInt(int type,int& v) const;
    private:
        // The atom expression tree of the atom
        McHandle<AtomExpression> expr;
        // The component index (may indicate that atoms are on different connection components, usually just 0)
        int component;
        // Is the atom chiral ?
        int chiral_flag;
        // The binding index (may be used for smirks expressions, where left and right hand side atoms are mapped via identical binding indices 
        int bix;
        // masked flag. if this flag is set, the atom is not included in the match results (it is of course still used in determining the matching).
        bool masked;
    };

    // -----------------------------------------------------------------------------
    // -
    // -                               BondSpecification
    // -
    // -----------------------------------------------------------------------------

    /* An BondSpecification contains all info regarding a single bond */
    class MOLCHEM_API BondSpecification : public McHandable
    {
    public:
        BondSpecification();
        BondSpecification(BondExpression* b,int atom1, int atom2);
        void setAtom1(int a1);
        void setAtom2(int a2);
        int getAtom1() const { return src;}
        int getAtom2() const { return dst;}
        BondExpression* getExpression() const { return expr;}
        // 
        bool isDiscon() const;
        // Returns whether the atom matches the description in the Bond Expression
        bool test(const Bond* b) const;
        /* Searches for first Property Expression of given type. Returns its value in v.
           Returns false if not found. Search will traverse graph through AND and OR expressions but not through NOT expression.
           This method is mainly for use in SMIRKS strings where on the product side, such properties are only defined uniquely.*/
        bool getType(int& type) const;
    private:
        // The bond expression tree
        McHandle<BondExpression> expr;
        // indices of source and destination atom in the pattern to which this specification belongs
        int src;
        int dst;
    };

    // -----------------------------------------------------------------------------
    // -
    // -                               Pattern
    // -
    // -----------------------------------------------------------------------------
    /* A Pattern contains all AtomSpecifcations and BondSpecifications.
       Pattern can be initialized with a smarts string with the init method.
       and then matched with the match method. 
       Matching is wrapped in the match function in molchem::Molecule which should be preferred except
       if the additional functionality and information contained in Pattern are required.

       The bond array has the following order invariant: 
            A bond does not occur until its source atom has been either mentioned
            as the atom of index 0 or as the destincation atom of a previous bond.
            This allows some optimizations for the matching algorithm.
    */
    class MOLCHEM_API Pattern : public McHandable
    {
    public:
        Pattern();
        /* Initializes pattern with smarts string. Throws molchem::Exception on parse error */
        void init(const char* str);
        /* Writes a readable version of Pattern into a string. (for debugging)*/
        void print(McString& str) const;
        /* content of p will be appended as shallow copies to this pattern */
        void append(Pattern* p);
        int appendAtom(AtomSpecification* b);
        int appendBond(BondSpecification* b);
        /* Returns the index of atom that contains the given binding ix, -1 if not found */
        int getAtomIxByBindingIx(int bIx) const;
        /* Returns i'th atom. i must be in range. */
        AtomSpecification* getAtom(int i) const;
        /* Returns i'th bond. i must be in range. */
        BondSpecification* getBond(int i) const;
        int getNumAtoms() const {return atom.size();}
        int getNumBonds() const {return bond.size();}
        int getNumComponents() const {return numComponents;}
        // establishs invariant concerning succession of bonds after parsing
        void sortBonds();
        // atom and bond indices will correspond to their index in the pattern. 
        Graph* getGraph() const;
        void match(const Molecule* mol,McDArray<McDArray<int> >& matching, bool single,McBitfield* bf);
        int getMaxBindingIx() const;
    private:
        void print(McString& str, const Pattern* pat,int depth) const;
        McDArray<McHandle<AtomSpecification> > atom;
        McDArray<McHandle<BondSpecification> > bond;
        int numComponents;
        static Logger* logger;
    };

    // -----------------------------------------------------------------------------
    // -
    // -                               Atom Expression
    // -
    // -----------------------------------------------------------------------------

    AtomExpression* GenerateElement(int);
    AtomExpression* GenerateAromElement(int,bool);

    /** An atom expression contains a tree of attributes an atom must suffice */
    class MOLCHEM_API AtomExpression : public McHandable
    {
    public:
        // this method will return whether the atom matches the expression tree
        virtual bool test(const Atom* a) const =0;
    };

    class AtomExpressionUnaryOperator : public AtomExpression {
    public:
        enum TYPE {
            NOT
        };
        AtomExpressionUnaryOperator(TYPE t, AtomExpression* e);
        virtual bool test(const Atom* a) const;
        TYPE getType() const { return t;}
        AtomExpression* getExpression() const { return e;}
    private:
        TYPE t;
        McHandle<AtomExpression> e;

    };

    class MOLCHEM_API AtomExpressionBinaryOperator : public AtomExpression {
    public:
        enum TYPE {
            ANDHI,
            OR,
            ANDLO
        };
        AtomExpressionBinaryOperator(TYPE _t, AtomExpression* _e1, AtomExpression* _e2);
        virtual bool test(const Atom* a) const;
        TYPE getType() const { return t;}
        AtomExpression* getExpression1() const { return el;}
        AtomExpression* getExpression2() const { return er;}
    private:
        TYPE t;
        McHandle<AtomExpression> el;
        McHandle<AtomExpression> er;
    };

    class MOLCHEM_API AtomExpressionPropertyInt : public AtomExpression  {
    public:
        enum TYPE {
            MASS,
            AROM,
            ELEM,
            HCOUNT,
            CHARGE,
            DEGREE,
            IMPLICIT,
            RINGS,
            SIZE,
            VALENCE,
            CHIRAL,
            HYB,
            CONNECTIVITY,
            RINGCONNECTIVITY,
        };
        virtual bool test(const Atom* a) const;
        AtomExpressionPropertyInt(TYPE _t,int _value);
        TYPE getType() const { return t;}
        int getValue() const { return value;}
    private:
        TYPE t;
        int value;
    };

    class MOLCHEM_API AtomExpressionRecursion : public AtomExpression {
    public:
        virtual bool test(const Atom* a) const;
        AtomExpressionRecursion(Pattern* p);
        Pattern* getPattern() const { return pat;}
    private:
        McHandle<Pattern> pat;
    };
    // -----------------------------------------------------------------------------
    // -
    // -                               Bond Expression
    // -
    // -----------------------------------------------------------------------------
    
    /** A bond expression contains a tree of attributes a bond must suffice */
    class MOLCHEM_API BondExpression : public McHandable {
    public:
        virtual bool test(const Bond* b) const=0;
    };


    class MOLCHEM_API BondExpressionUnaryOperator : public BondExpression {
    public:
        enum TYPE {
            NOT,
        };
        BondExpressionUnaryOperator(TYPE tp,BondExpression* ep);
        virtual bool test(const Bond* a) const;
        TYPE getType() const { return t;}
        BondExpression* getExpression() const { return e;}
    private:
        TYPE t;
        BondExpression* e;
    };

    class MOLCHEM_API BondExpressionBinaryOperator : public BondExpression {
    public:
        enum TYPE {
            ANDHI,
            ANDLO,
            OR
        };
        BondExpressionBinaryOperator(TYPE tp,BondExpression* elp,BondExpression* erp);
        virtual bool test(const Bond* a) const;
        TYPE getType() const { return t;}
        BondExpression* getExpression1() const { return el;}
        BondExpression* getExpression2() const { return er;}
    private:
        TYPE t;
        BondExpression* el;
        BondExpression* er;
    };

    class MOLCHEM_API BondExpressionType : public BondExpression  {
    public:
        enum TYPE {
            // Bond Types
            SINGLEORAROM,
            SINGLE,
            DOUBLE,
            TRIPLE,
            AROM,
            UP,
            DOWN,
            UPUNSPEC,
            DOWNUNSPEC,
            RING,
            DISCON,
            WILDCARD
        };

        virtual bool test(const Bond* a) const;
        BondExpressionType(TYPE _t);
        TYPE getType() const { return t;}
    private:
        TYPE t;
    };

}
#endif

/// @}
