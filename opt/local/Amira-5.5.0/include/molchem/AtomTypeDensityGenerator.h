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
#ifndef ATOMTYPEDENSITYGENERATOR_H
#define ATOMTYPEDENSITYGENERATOR_H

#include "MolChemWinDLLApi.h"

#include <mclib/McBitfield.h>
#include <mclib/McString.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

class RegularGrid3f1;
class MolTrajectoryMem;

namespace molchem {
    class Logger;

    /** /brief Computes spatial densities of atom types of a set of MolTrajectories.

    */

    class MOLCHEM_API AtomTypeDensityGenerator {

    public:
        ///
        AtomTypeDensityGenerator();
        /// Input data which will be processed
        void setData(const McDArray<MolTrajectoryMem*>& traj) {trajectories = traj;}
        /** Options for atomic vdw radii. 
            ARO_FIXED uses one radius for all atoms (default)
            ARO_ATTRIBUTER takes the radii from an attribute of the atoms level, radii will be mnultiplied with the atom radius set with setAtomRadius.
            ARO_TABLE takes the radii from the standard vdw radius of the element table, radii will be mnultiplied with the atom radius set with setAtomRadius.
            ARO_MMFF uses minimum vdw distances from the mmff94 parameterization of interaction with the same atom type.
        */
        enum { ARO_FIXED, ARO_ATTRIBUTE,ARO_TABLE, ARO_MMFF };
        void setAtomRadiusOption(int i) {atomRadiusOption=i;}
        void setAtomRadius(float f) {atomRadius=f;}
        void setAtomRadiusAttribute(const McString& f) {atomRadiusAttribute=f;}

        /// Weighting of one timestep in a trajectory
        enum { EWO_NONE, EWO_WEIGHT,EWO_SUM, EWO_BOLTZMANN ,EWO_LINEARMINMAX };
        void setEnergyWeightingOption(int i) {energyWeightingOption=i;}
        void setEnergyWeightingObservable(const char* name) {energyWeightingObservable = name;}
        /// Conditional densities: Point condition
        enum { PCO_NONE,PCO_SET };
        void setPointConditionOption(int i) {pointConditionOption=i;}
        void setPointConditionPoint(const McVec3f& p) { pointConditionPoint = p;}
        void setPointConditionTypeMask(const McBitfield& bf) { pointConditionTypeMask = bf;}
        /// Weighting of each atom in a timestep
        enum { AWO_NONE,AWO_OVERALLFREQUENCY };
        void setAtomWeightingOption(int i) { atomWeightingOption=i;}
        /// selection of atoms
        enum { ASO_NONE,ASO_MMFFTYPE};
        void setAtomSelectionOption(int i) { atomSelectionOption=i;}
        void setAtomTypeAttribute(const char* attrName) {atomTypeAttribute = attrName;}
        void setAtomSelectionTypeMask(const McBitfield& bf) {atomSelectionTypeMask = bf;}
        /** Weighting of Trajectories. This are bits which may be set */
        enum { TWO_NONE = 0x00, // No Weighting (default)
               TWO_NUM  = 0x01, // Divide by number of trajectories 
               TWO_DATA = 0x02, // Multiply with the number in the float data entry (name is determined by setTrajectoryWeightingData)
               TWO_SIZE = 0x04 // Divide by number of atoms of the molecule
               };
        enum { TNO_NONE,TNO_SUM };
        void setTrajectoryNormalizationOption(int i) { trajectoryNormalizationOption=i;}
        void setTrajectoryWeightingOption(int i) { trajectoryWeightingOption=i;}
        void setTrajectoryWeightingData(const char* name) {trajectoryWeightingData = name;}
        enum { DNO_NONE,DNO_SUM };
        void setDensityNormalizationOption(int i) { densityNormalizationOption=i;}

        // returns array with overall number of atom types in all data
        void computeAtomTypeNumber(McDArray<int>& n) const;
        /// iterates over all input data and writes the density grid
        void computeDensity(RegularGrid3f1& g);

    private:    
        McString energyWeightingObservable;
        McString trajectoryWeightingData;
        McDArray<MolTrajectoryMem*> trajectories;
        //
        int atomSelectionOption;
        McBitfield atomSelectionTypeMask;
        //
        McBitfield pointConditionAtomTypeMask;
        // 
        int atomRadiusOption;
        float atomRadius;
        McString atomRadiusAttribute;

        // Conditional densities: Point condition
        int pointConditionOption;
        McVec3f pointConditionPoint;
        McBitfield pointConditionTypeMask;
        float pointConditionRadius;

        // Weighting of one timestep in a trajectory
        int energyWeightingOption;
        McString energyWeightingObserbable;

        // Weighting of each atom in a timestep
        int atomWeightingOption;



        // selection of atoms
        McString atomTypeAttribute;

        int trajectoryWeightingOption;
        int trajectoryNormalizationOption;

        int densityNormalizationOption;
        
        // grid specification - taken from input field
        McVec3i dims;
        McBox3f bbox;
        McVec3f spacing;

        // computes density for one specific atom
        void handleInsideSpherePointsS(RegularGrid3f1* g,McVec3f &atomPos, int bboxInx[6],
            float radius2, McBitfield & bf, double weight);
        
        // converts spatial bounding box into bounding box of grid indices
        void compBBoxInx(float bb[6], int bboxInx[6]) const;
        //
        static molchem::Logger* logger;
    };
}

#endif

/// @}
