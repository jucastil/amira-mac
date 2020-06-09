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
#ifndef MOLCHEM_RIGIDDYNAMICS_H
#define MOLCHEM_RIGIDDYNAMICS_H

#include "MolChemWinDLLApi.h"
#include "Function.h"
#include <mclib/McDArray.h>

class McVec3d;

namespace mmff94 {
    class ForceField;
}

namespace molchem {
    
    class Molecule;
    class ForceField;

    /** \brief RigidDynamic Wrapper for ForceField 
    
        RigidDynamics wraps a cartesian coordinate ForceField and represents its energy hypersurface
        in a different coordinate space that better describes the degrees of freedom of rigid bodies.
        Input and output coordinates and gradient consist of several 6 tuples describing
        the translation and orientation of the modeled rigid bodies.
        The 6 tuple has the following order: (x,y,z,phi_x,phi_y,phi_z)
        where (x,y,z) is the translation of the center of the body from the original position and 
        (phi_x,phi_y,phi_z) is a vector containing the euler angles which describe the rotation from
        the original orientation around the 3 coordinate axes.
    */
    class MOLCHEM_API RigidDynamics : public GradientFunction {
    public: 
        /// Force field will be destroyed when dectructor is called
        RigidDynamics(ForceField* f);
        virtual ~RigidDynamics();
        /// Sets fixed and rigid in force field and calls setup function of force field
        void setup(Molecule* m,McDArray<McDArray<int> > & parts);
        /// 
        virtual bool computeValue(const double * p,int num,double& value);
        ///
        virtual bool computeGradient(const double * p,int num,double * grad);    
        ///
        virtual bool computeValueAndGradient(
            const double * p,int num,
            double& value,
            double * grad);
        /// converts 6D description of all rigid bodies to coodinates of molecule
        void transrot2Coords(const double* tp,int num1, double* coords,int num2) const;
        /// converts energy gradient with respect to cartesian coordinates to energy gradient with respect to trans 
        void coordGrad2transrotGrad(const double* co1, int num1, const double* grad1, double* grad2, int num2) const;
    private:    
        // the rigid parts
        McDArray< McDArray<int> > parts;
        // the used force field
        ForceField* field;
        // the original coordinates (from the molecule when calling setup)
        McDArray<McVec3d> origCoords;
    };
}

#endif

/// @}
