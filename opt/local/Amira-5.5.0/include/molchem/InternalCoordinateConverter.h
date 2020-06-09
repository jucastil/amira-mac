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
#ifndef MOLCHEM_ZMATRIX_H
#define MOLCHEM_ZMATRIX_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>
#include <mclib/McVec3d.h>
#include <molchem/Function.h>
#include <molchem/helpers.h>
class McString;
namespace molchem {

    class Molecule;
    /** \brief Converter between cartesian coordinates and internal coordinates (also called zmatrix)

    Internal coordinate array: 
    transX,transY,transZ,q1,q2,q3,q4, i1, ...
    Trans is the translation vector of the first atom in the atoms array.
    Q is the quarternion representing the rotation of frame (1,0,0) (0,1,0) to the frame
    determined by the vector between atom 1 and 2 and between atom 2 and 3. 
    I are the internal coordinates ordered as indexed in the atoms array by
    bondIxZ, int angleIxZ and, dihedralIxZ. Thus the index of the first internal coordinate
    is 7. If no rotation and translation is used it is 0.

    Angles of internal coordinates are in the interval [0,2Pi]
    

    */
    class MOLCHEM_API InternalCoordinateConverter {
    public:
        /** Create an internal coordinate converted from the molecule.     
        Molecule must not have multiple connection components.
        With fixedBonds, the bond lengths will be set fixed and
        won't be part of the internal coordinate string, same for angles and torsion (for torsion the option is to set non-rotatable
        torsion as fixed, ie torsion with a central bond that is not a single bond). WIth useRotTrans the first 7 values will be usde
        for translation vector and quartenion*/
        InternalCoordinateConverter(molchem::Molecule& mol,bool fixedBonds,bool fixedAngles,bool fixedNRTorsions,bool useRotTrans);
        ~InternalCoordinateConverter();
        void cartesianToInternal(const McDArray<McVec3d>& co,McDArray<double>& zmatrix);
        void internalToCartesian(const McDArray<double>& zmatrix,McDArray<McVec3d>& co);
        /** Atom contains all information of one atom in internal coordinate representation. 
        
        It contains the indices of the other atoms that are used to define the bond, angle and dihedral with this atom and
        it contains the index of each internal coordinate of the atom in the zmatrix array and 
        If internal coordinates are kept fixed it also contains their fixed value. 
        */
        struct Atom {
            // value if the bond length remains fixed. 
            double fixedBondValue;
            // value if the angle remains fixed. 
            double fixedAngleValue;
            // value if the dihedral remains fixed. 
            double fixedDihedralValue;
            /// first atom in 4-tuple. This index will be -1 if undefined (for the first 3 atoms)
            int atom1;
            /// second atom in 4-tuple. This index will be -1 if undefined (for the first 2 atoms)
            int atom2;
            /// second atom in 4-tuple. This index will be -1 if undefined (for the first atom)
            int atom3;
            /// index of bond length value in the zmatrix array, -1 if undefined or fixed
            int bondIxZ;
            /// index of angle value in the zmatrix array, -1 if undefined or fixed
            int angleIxZ;
            /// index of angle value in the zmatrix array, -1 if undefined or fixed
            int dihedralIxZ;
            /// the atoms index in cartesian coordinates. -1 if a dummy atom
            int ixC;
        };
        double getBondV(const McDArray<McVec3d>& co,int a1,int a2);
        double getDihedralV(const McDArray<McVec3d>& co,int a1,int a2,int a3,int a4);
        double getAngleV(const McDArray<McVec3d>& co,int a1,int a2,int a3);
        /** number of zmatrix internal coordinates. Usually 3*nAtoms-6 
            (+7 if rotation and trnslation is used) but less  if some internal coordinates are kept fixed */
        int numZ;
        /** Internal coordinate representation of each atoms. This is not the same order as atoms in cartesian coordinates.
           The atoms are ordered so that their reference atoms for bonds angles and dihedrals always appear left
           in the list. */
        McDArray<Atom> atoms;
        /// mapping from cartesian coordinate atom indices to internal coordinat atoms indices. The opposite mapping is contained in the ixC entry of the atoms array.
        McDArray<int> ixC2I;
        /// generates a string representation of the internal coordinates structure
        void print(McString& s) const;
        /// determines whether rotation and translation are used
        bool useRotTrans;
    };

    /** \bried Wraps a function converting coordinates from internal to cartesian  for function evaluation.
        
        This allows to represent the molecule in internal coordinate space while using a 
        cartesian coordinate force field for energy evaluation. */
    class MOLCHEM_API InternalCoordinateWrapper : public Function {
    private:
        Function *f;
        InternalCoordinateConverter* conv;
    public:
        /// 
        InternalCoordinateWrapper(InternalCoordinateConverter* conv,Function* f);
        ///
        virtual bool computeValue(
            const double * p, int num,
            double& v);
    };
}

#endif

/// @}
