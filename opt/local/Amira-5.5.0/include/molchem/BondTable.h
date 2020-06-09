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
#ifndef MOLCHEM_BONDTABLE_H
#define MOLCHEM_BONDTABLE_H

#include "MolChemWinDLLApi.h"

template <class T1, class T2> class McHashTable;
class McString;

namespace molchem {
    class Logger;

    /** \brief Contains static information about bonds.

    BondTable can be used as interface to the information
    in  the file bondLengths.cfg. It offers methods to
    get bond lengths and orders for element combinations.
    The first instance of it will read in the file as static HashTable.

    The keys for finding bonds are stored internally as strings in
    the format "<atomicNumber1><bondOrderChar><atomicNumber2>"
    where bondOrderChar is the same as defined in bondLengths.cgf
    (e.g. "6=6" for a C=C bond).

    Design patterns: Singleton
    **/
    class MOLCHEM_API BondTable {
    public:
        /// Return the static BondTable object
        static const BondTable* getBondTable() {
            if (!singletonObject)
                singletonObject = new BondTable();
            return singletonObject;
        }
        /** returns the bond lenght of a bond of order @c bondOrder
        between elements @c atomicNum1 and @c atomicNum2
        if this bond is not found in the database 0 will be returned **/
        float getBondLength(int atomicNum1,int atomicNum2, int bondOrder) const;
        
        /** returns the bond lenght of the bond @c bondStr
        if this bond is not found in the database 0 will be returned **/
        float getBondLength(char* bondStr) const;
        
        /** will return whether there is a bond od any order between elements
        @c atomicNum1 and @c atomicNum2 whose bond lengths does not deviate
        more that @c maxDeviation form @c dist **/
        bool isBonded(int atomicNum1,int atomicNum2,float dist,float maxDeviation=.1) const;
        
        /** will return bestBondLen and bestBondOrder of a bond between elements
        @c atomicNum1 and @c atomicNum2 which are @c dist away from each other **/
        void getBestBond(int atomicNum1,int atomicNum2,float dist, float& bestBondLen,int& bestBondOrder) const;
        
        /** will return the bondOrder of the bond between elements
        @c atomicNum1 and @c atomicNum2 whose bond lengths does not deviate
        more that @c maxDeviation form @c dist 
        if none is found 0 will be returned **/
        int getBondOrder(int atomicNum1,int atomicNum2,float dist,float maxDeviation=.1) const;
        
        /** rotates the bond string <atomicNum1><bondChar><atomicNum2> to
        <atomicNum2><bondChar><atomicNum1> and returns result in static char array **/
        char* rotateBondString(const char* bondStr) const;
        
        /** returns the bond string of bond of order @c bondOrder between 
        elements @c atomicNum1 and @c atomicNum2 **/
        static void getBondString(int atomicNum1,int atomicNum2, int bondOrder,McString& res);

        /** returns the bond string of bond of order @c bondOrder between 
        elements @c atomicNum1 and @c atomicNum2 while using the atom symbol for the elements **/
        static void getBondStringSymbolic(int atomicNum1,int atomicNum2, int bondOrder,McString& res);

        static char getBondSymbol(int bondOrder);

    protected:
        /* constructor, will read in bondLengths.cfg if not already
        done by another instance, paths will give possible paths to 
        look for the file */
        BondTable();
        
        // destructor
        ~BondTable();
        static BondTable* singletonObject;
        
        // static list of bond lengths of bondLength.cfg file
        McHashTable<McString,float>* bondLengths;
        bool readBondLengths();
        static Logger* logger;
    };
}

///  macro to obtain the static BondTable object
#define theBondTable molchem::BondTable::getBondTable()

#endif




/// @}
