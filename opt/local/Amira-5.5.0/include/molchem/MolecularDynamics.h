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
#ifndef MOLCHEM_MD_H
#define MOLCHEM_MD_H

#include "MolChemWinDLLApi.h"

#include <mclib/McDArray.h>
#include <mclib/McString.h>

class McFilename;
class Molecule;
class MolTrajectoryMem;
class McProgressInterface;

namespace molchem {
    class Logger;
    /** \brief MD Simulator Engine
    *
    */
    class MOLCHEM_API MolecularDynamics {
    public:
        ///
        MolecularDynamics();
        virtual ~MolecularDynamics();
        MolTrajectoryMem* simulate();
        void setTau(double val);
        void setTime(int val);
        void setTemperature(int val);
        void setStepsPerSave(int val);
        void setMolecule(const ::Molecule& mol);
    private:
        static molchem::Logger* logger;
        float normDistRand();
        // energy must be in J per mol. temperature in kelvin
        double getTemperature(int nAtoms,double kineticEnergy);
        // energy must be in J per mol
        double getTemperature(const McDArray<double>& v, const McDArray<double>& mass);
        // v in m/s mass in kg returns energy in J/mol
        double getKineticEnergy(const McDArray<double>& v, const McDArray<double>& mass);
        // v will be randomized in a normal distribution
        void setRandomVelocities(McDArray<double>& v);
        // scale velocities so that system which is currently at systemT is now at targetT
        void scaleVelocities(McDArray<double>& v,double systemT, double targetT);

        float tau; //fs default .5
        int time; //fs default 100
        float temperature; //K default 298.15
        int stepsPerSave; // default 1
        const Molecule   *mol;
        MolTrajectoryMem *traj;
    };
}
#endif

/// @}
