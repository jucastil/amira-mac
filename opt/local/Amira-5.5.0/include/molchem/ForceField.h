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
#ifndef MOLCHEM_FORCEFIELD_H
#define MOLCHEM_FORCEFIELD_H

template<class T> class McDArray;
class McBitfield;
class McVec3d;

#include "MolChemWinDLLApi.h"
#include "Function.h"

namespace molchem {
    
    class Molecule;


    /** \brief Interface for force fields. 
       
       This class defines shared functionality of molecular force fields implemented in Amira.
       Configuration methods include the selection of active components.
       Computation methods include the computation of global energy and forces per atoms.

       Units of the computation methods: 
       Input Coordinates: Angstroem.
       Output energy: kJ/mol.
       Output gradient: kJ/(mol*Angstroem) which is 1E-10*kN/mol.
    */

    class MOLCHEM_API ForceField : public GradientFunction {
    public:

        ///
        ForceField();
        
        ///
        virtual ~ForceField();

        /// Name of the force field.
        virtual const char* getName()const =0;

        /// Return number of components of force field.
        virtual int getNumComponents()const =0;

        /// Return component name of index componentIndex.
        virtual const char* getComponentName(int componentIndex) const=0;

        /// Returns index of component of given name. Comparison is case sensitive. If name is not found, -1 is returned.
        int getComponentIndex(const char* componentName) const;

        /** Sets molecule. 
            The setup method needs to be called in order for this change to take effect.
            The methods returns false if the molecule could not be correctly parameterized by the force field.*/
        virtual bool setMolecule(Molecule* m)=0;

        /** Rescales a component. Both energy values and gradient of this component will 
            be multiplied with the scale factor. All scalefactors are disabled by default.*/
        virtual void setComponentScale(int componentIx, double scaleFac);

        /** Activates/deactivates a component. All components are active by default.
            The setup method of that component needs to be called in order for this change to take effect. */
        virtual void setComponentActive(int componentIx, bool active);

        /** Set certain sets of atoms of the molecule as rigid.
            
            Parts needs to contain an index for each atom. Index 0 means
            that the atoms does not belong to a rigid part. 
            For rigid parts, no intramolecular interaction will be calculated 
            -> rigid body dynamics. 0 will deactivate any rigid parts.
            This method is primarily of use for the RigidBodyDynamic Wrapper.
            The setup method needs to be called in order for this change to take effect.*/
        virtual void setRigidParts(const McDArray<int>* parts=0);

        /** Sets certain sets of atoms as fixed in space. Fixed parts will be considered
        as rigid, i.e. no inter atoms interactions. Additionally the force on them will
        be set to 0.The setup method needs to be called in order for this change to take effect.*/
        virtual void setFixedPart(const McBitfield* part=0);
        
        /** Enables or disables the nonbonded cutoff. If activated, only nonbonded interaction smaller
            than cutoff will be computed. 
            The setup or updateNeighborList method needs to be called in order for this change to take effect. */
        virtual void setCutoff(bool active, double cutoff=10.);
        
        /** Result structure.
            When computing, the force field uses the bit information in computeWhat in order to determine
            which result fields to update. After calling compute, the information in the related fields will
            contain the results, all other fields are invalid.
        */
        struct Result {
            int computeWhat;
            double energy; 
            McDArray<double> energyPerComponent;
            McDArray<McDArray<double> > energyPerInteractionPerComponent;
            McDArray<McVec3d> gradient;
            McDArray<McDArray<McVec3d> > gradientPerComponent;
            enum {
                ENERGY                                      = 0x010,
                ENERGY_PER_INTERACTION                      = 0x020,
                GRADIENT                                    = 0x001,
                GRADIENT_PER_COMPONENT                      = 0x002
            };

        } result;

        ///
        virtual bool compute(const McDArray<McVec3d>&) = 0;
        
        ///
        virtual bool computeValue(const double * co,int num,double& value);
        
        ///
        virtual bool computeGradient(const double * co,int num,double * grad);    
        
        ///
        virtual bool computeValueAndGradient(
            const double * co,int num,
            double& value,
            double * grad);

        /// Initializes the forcefield to prepare for computation. This method must be called once before computation.
        virtual void setup(const McDArray<McVec3d>& co) =0;
        
        /** Initializes the nonbonded neighbor list of the force field to prepare for computation. 
            This method is called by setup and can additionally be called by the client later to 
            adjust the neighbor list to coordinate changes. The list is not automatically updated.
            The client has to decide when (if at all) an update is neccessary.*/
        virtual void updateNeighborList(const McDArray<McVec3d>& co)=0;
    protected:
        bool areAtomsRigid(int ix1,int ix2) const;
        bool areAtomsRigid(int ix1,int ix2,int ix3) const;
        bool areAtomsRigid(int ix1,int ix2,int ix3,int ix4) const;
        bool areAtomsFixed(int ix1,int ix2) const;
        bool areAtomsFixed(int ix1,int ix2,int ix3) const;
        bool areAtomsFixed(int ix1,int ix2,int ix3,int ix4) const;
        bool isComponentActive(int ix) const;
        // Optional scale factors. If the pointer is not null the array contains a scale factor for each component index.
        McDArray<double>* scaleFactors;
        // Optional rigid parts. If the pointer is not null, it contains a rigid part index for each atom. Index 0 means that the atom is not in a rigid part. 
        McDArray<int>* rigidParts;
        // Optional fixed part. If the pointer is valid, atoms set in the bitfield will be fixed in space.
        McBitfield* fixedPart;
        // Optional activity of components
        McBitfield* componentActive;
        bool useCutoff;
        double cutoff; 
    };
}
#endif





/// @}
