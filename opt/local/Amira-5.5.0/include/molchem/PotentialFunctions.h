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
#ifndef MOLCHEM_POTENTIALFUNCTIONS_H
#define MOLCHEM_POTENTIALFUNCTIONS_H

#include "MolChemWinDLLApi.h"


#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec3d.h>
#include "Function.h"

namespace molchem {
    
    class Molecule;
    
    /** \brief Potential representing Hook's law.
    
        Hooks Law is a simple two body potential: E(12) = k * ( | r(1) - r(2) | - deq(12) ) ^ 2.
        This implementation is primarily intended to be used for bond stretching interaction.

        The bond array may be initialized via the init method or directly by the client.

   */

    class MOLCHEM_API HooksLaw : public GradientFunction {
    public:
        HooksLaw() : GradientFunction(.00001), k(1) {}
        ~HooksLaw() {}
        /** Initializes the bond array with bonds of the given molecule.
            
            \param[in] mol The molecule whose bonds will be used.
            \param[in] flexibleAtoms Optional mask of flexible atoms.
                       Only bonds which have at least one atom set in the mask will be added as an interaction.
            \param[in] deq_default The default equilibrium distance. The equilibrium distance (deq) 
                       of each bond will be set accoring to the bond lenght table. If the tabulated value is 0, 
                       the default value is used.
        */
        void init(const Molecule* mol,const McBitfield* flexibleAtoms=0,double deq_default = 1.5);
        ///
        virtual bool computeValue(
            const double * p,int num,
            double& value);
        ///
        virtual bool computeGradient(
            const double * p,int num,
            double * grad);
        /// force constant (default is 1)
        double k;
        /// Structure to contain data of one bond
        struct Bond {
            /// equivalence distance
            double deq;
            /// atom indices
            int atom1,atom2;
        };
        /// Array of bonds that whose potential will be evaluated.
        McDArray<Bond> bonds;
    };

    /** \brief Potential representing of Coulombs's law.
    
        Coulombs Law is a simple two body potential: E(12) =  q(1) * q(2) / ( D | r(1) - r(2) | )
        This implementation is primarily intended to be used for coulombic interactions between atoms.

   */

    class MOLCHEM_API CoulombPotential : public GradientFunction {
    public:
        ///
        CoulombPotential() : GradientFunction(.00001), D(1) {}
        ///
        virtual bool computeValue(
            const double * p,int num,
            double& value);
        ///
        virtual bool computeGradient(
            const double * p,int num,
            double * grad);
        /// Charge per atom in molecule. Corrresponds to indices in pairlist atoms.
        McDArray<double> charge;
        /// List of indices of all atom pairs.
        McDArray<McVec2i> pairList;
        /// dielectic constant
        double D;

    };

    /** \brief Lennard Jones Potential.

        E(12) = c1(12) * | r(1) - r(2) | ^ (-exp1) - c2(12) * | r(1) - r(2) | ^ (-exp2) 
        With c1 = exp2/(exp1-exp2)  *  emin * req^exp1
             c2 = exp1/(exp1-exp2)  *  emin * req^exp2
        this can be equivalently written in terms of minimum well depth (emin) 
        and equilibrium distasnce req. For the conversion to c1 and c2
        the class has a conversion method.

   */

    class MOLCHEM_API LennardJonesPotential : public GradientFunction {
    public:
        LennardJonesPotential() : GradientFunction(.00001), exp1(12), exp2(6) {}
        ~LennardJonesPotential() {}
        ///
        virtual bool computeValue(
            const double * p,int num,
            double& value);
        ///
        virtual bool computeGradient(
            const double * p,int num,
            double * grad);
        virtual bool computeValueAndGradient(
            const double * p,int num,double& value,
            double * grad);

        //
        McDArray<McVec2i> pairList;
        // force constant 1 per pair
        McDArray<double> c1;
        // force constant 2 per pair
        McDArray<double> c2;
        // 
        int exp1;
        // 
        int exp2;
        // converts equilibrium distance and well depth parameters to force constants
        static void re2c(double req,double emin,int exp1, int exp2,double& c1, double& c2);
    };
}

#endif


/// @}
