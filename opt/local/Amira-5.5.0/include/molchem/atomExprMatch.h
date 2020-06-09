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
#ifndef ExpressioN_MATCH_H
#define ExpressioN_MATCH_H

#include <mclib/McString.h>
#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <molchem/Molecule.h>
class MolObject;
class McBitfield;
class MolTopology;
class MtGroupAttribute;

namespace AE {
    class MolInput {
    public:
        MolInput() {}
        MolObject* mol;
        McHandle<molchem::Molecule> mcmol;
        McBitfield* currentSelection;
    };

    /** An atom expression contains a tree of attributes an atom must suffice */
    class Expression : public McHandable
    {
    public:
        // this method will return whether the atom matches the expression tree
        virtual void match(MolInput& input,
            McBitfield& result) const =0;
    };


    class Constant : public Expression {
    public:
        enum TYPE {
            ALL,
            NONE,
            CS
        };
        Constant(Constant::TYPE t) {
            this->t = t;
        }
        virtual void match(MolInput& input,
            McBitfield& result) const;
    protected:
        TYPE t;
    };

    class UnaryOperator : public Expression {
    public:
        enum TYPE {
            NOT
        };
        UnaryOperator(const McHandle<Expression>& e,UnaryOperator::TYPE t) {
            this->t = t;
            this->e = e;
        }
        virtual void match(MolInput& input,
            McBitfield& result) const;
    protected:
        TYPE t;
        McHandle<Expression> e;

    };

    class BinaryOperator : public Expression {
    public:
        enum TYPE {
            AND,
            OR,
            XOR
        };
        BinaryOperator(const McHandle<Expression>& el,const McHandle<Expression>& er,BinaryOperator::TYPE t) {
            this->t = t;
            this->er = er;
            this->el = el;
        }
        virtual void match(MolInput& input,
            McBitfield& result) const;
    protected:
        TYPE t;
        McHandle<Expression> el;
        McHandle<Expression> er;
    };

    class DataSpecifier : public Expression {
    public:
        DataSpecifier(const char* name,const char* comparison, const char* value) {
            assert(name);
            this->name = name;
            assert(comparison);
            this->comparison = comparison;
            assert(value);
            this->value = value;
        }

        virtual void match(MolInput& input,
            McBitfield& result) const;
    protected:
        McString name;
        McString value;
        McString comparison;

    };

    class AtomSpecifier : public Expression {
    public:
        AtomSpecifier(const char* level,const char* attribute,const char* comparison, const char* value);
        virtual void match(MolInput& input,
            McBitfield& result) const;
    protected:
        McString level;
        McString attribute;
        // first index: list item as speratated by ;
        // second index: range as seperated by : (will be size 1 if no range or 2 if range)
        McDArray<McDArray<McString> > values;
        McString comparison;

        void atomSpecifierSimple(MolTopology* t,const char* level,const char* id,McBitfield& result) const;
        void atomSpecifierSimpleRange(MolTopology* t,const char* level,const char* id1,const char* id2,McBitfield& result) const;
        void atomSpecifier(MolTopology* t,const char* level,const char* at,const char* eqnOp,const char* id1,const char* id2,McBitfield& result) const;
        int getLevel(MolTopology* t,const char* lev) const;
        const MtGroupAttribute* getAttribute(MolTopology* t,int levelIx,const char* attr) const;

    };

    class SmartsOperator : public Expression {
    public:
        SmartsOperator(const char* smarts,bool includeH=false) {
            this->smartsString = smarts;
            this->includeH= includeH;
        }
        virtual void match(MolInput& input,
            McBitfield& result) const;
    protected:
        McString smartsString;
        bool includeH;
    };

    class WithinOperator : public Expression {
    public:
        WithinOperator(const McHandle<Expression>& e,float radius) {
            this->e = e;
            this->radius = radius;
        }
        WithinOperator(float x,float y,float z,float radius) {
            this->e = 0;
            this->x = x;
            this->y = y;
            this->z = z;
            this->radius = radius;
        }
        virtual void match(MolInput& input,
            McBitfield& result) const;
    protected:
        McHandle<Expression> e;
        float x,y,z;
        float radius;
    };

    class BondedOperator : public Expression {
    public:
        BondedOperator(const McHandle<Expression>& e,int depth) {
            this->e = e;
            this->depth = depth;
        }
        virtual void match(MolInput& input,
            McBitfield& result) const;
    private:
        McHandle<Expression> e;
        int depth;
        void getBondedAtoms(int atomIx, McDArray<McDArray<int> >& bl,
                                    McBitfield& res, McDArray<int>& remDepth,
                                    int depth)  const;
        void getBondedAtoms(int atomIx, McDArray<McDArray<int> >& bl,
                                    McBitfield& res) const;
    };
    class ExpressionParser2 {
    public:
        McString getStringInBracket(const McString& str,int& ix);
        McHandle<Expression> parse(const McString& str);
        McHandle<Expression> parse(const McString& str, int& ix);
        McHandle<Expression> parseWithin(const McString& str,int ix);
        McHandle<Expression> parseBonded(const McString& str,int ix);
        McHandle<Expression> parseSmarts(const McString& str,int ix);
        McHandle<Expression> parseSpecifier(const McString& token);
    };
}

   
#endif

/// @}
