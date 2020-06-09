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
#ifndef MOLTOOLS_ATOMEXPRPARSER_H
#define MOLTOOLS_ATOMEXPRPARSER_H

#include "MolChemWinDLLApi.h"
#include <molchem/Exception.h>
#include <mclib/McHandable.h>

class McBitfield;
class Molecule;
namespace AE {
    class Expression;
}

/** Passes on internal or parser error as an exception object
*/

class MOLCHEM_API AtomExpressionException : public molchem::Exception {
public:
    AtomExpressionException(const char* text, ...);
    AtomExpressionException(const McString& txt) : molchem::Exception(txt) {}
};

/** This class parses and represents an atom expression
    The first instance of this class will read in the file
    of aliases as a static HashTable.
*/

class MOLCHEM_API AtomExpression : public McHandable {
public:
    /** Initialized AtomExpression from string
    \throws AtomExpressionException upon parse error */
    AtomExpression(const char* string);
    ~AtomExpression();
    /** Matches expression to molecule
    \param[in] currentSelection Current Selection (used by the CS literal). If null pointer, it will be unset for all atoms.
    \param[out] res Matching result
    \throws AtomExpressionException
    */
    void match(const Molecule& m,const McBitfield* currentSelection,McBitfield& res) const;
    void match(const Molecule& m,const McBitfield* currentSelection,McDArray<int>& res) const;
private:
    AE::Expression* expression;
};

/** This class is deprecated. Use class AtomExpression instead. */
class MOLCHEM_API AtomExpressionParser {
public:
    /** Contructor. Reads AtomExpression aliases if neccessary and possible.
        If @c handleException is true, possible exceptions due to parse of
        internal errors are caught and the error text is printed to the 
        console. Else no text is printed and the exception is passed on.
        Note: A failure to read the alias file will not cause an exception
        but only a log message. Use hasAliases() to check success.*/
    AtomExpressionParser(const Molecule* mol,bool handleException=true);
    /** Parse atomExpression @c argstr and return matching atoms in
        Bitfield @c res. Returns false if parsing did not succeed.
        May throws AtomExpressionException if handleException is true.
        In order for the keyword CS to work properly, res needs to contain the
        current selection.*/
    bool parse(const char* argstr, McBitfield& res) const;
    
    /** Parse atomExpression @c argstr and return matching atom indices in
        McDArray @c res. Returns false if parsing did not succeed.
        May throws AtomExpressionException if handleException is true.
        In order for the keyword CS to work properly, res needs to contain the
        current selection.*/
    bool parse(const char* argstr, McDArray<int>& res) const;
private:
    Molecule* mol;
    bool handleException;
};

#endif

/// @}
