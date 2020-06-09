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
#ifndef MOLCHEM_MOLRELAXER_H
#define MOLCHEM_MOLRELAXER_H

#include "MolChemWinDLLApi.h"

#include "OptimizerListener.h"

#include <mclib/McHandle.h>
#include "Optimizer.h"
#include "Function.h"
class McBitfield;

namespace molchem {

    class Molecule;
    class Optimizer;
    class MolRelaxingFunction;

    /** \brief High efficiency molecular potential which is used by MolRelaxer

        MolRelaxingFuncyion is an easy to compute potential which models stretch bend interaction and atomic repulsion.
        It is used as a potential by MolRelaxer.

        Design Pattern: Decorator for GradientFunction
    */
    class MOLCHEM_API MolRelaxingFunction : public GradientFunction {
    public:
        /** Constructor

            \param[in] mol Molecule that is described by this relaxing function
            \param[in] flexibleAtoms Bitfield indicating which atoms are flexible.
                       For non flexible atoms the gradient is always set to 0, so that
                       they are not moved. If flexibleAtoms is 0 all atoms will be flexible.
        */
        MolRelaxingFunction(const Molecule *m,const McBitfield* flexibleAtoms=0);
        
        ///
        ~MolRelaxingFunction();
        
        /** Update the list of neighbors which is needed to compute the potential.
            This function MUST be called to initialize the list before 
            any of the compute functions is called for the first time.
            It MAY be called again later to update the list.

            \param[in] p array of coordinates
            \param[in] num size of p array
         */
        void updateNeighborList(double cutoff,const double* p,int num);

        ///
        virtual bool computeValue(
            const double * p,int num,
            double& value);

        ///
        virtual bool computeGradient(
            const double * p,int num,
            double * grad);

        ///
        virtual bool computeValueAndGradient(
            const double * p,int num,double& value,
            double * grad);
    private:
        
        Molecule* m;
        // Bitfield of flexible atoms
        McBitfield* atomMask;
        // FunctionLinearCombination. If an atomMask is used a GradientFunctionMask will be put in between
        McHandle<GradientFunction> f;
        // Pairwise potential 
        McHandle<GradientFunction> fpp;
    };

    /** \brief  High efficiency minimizer for molecular geometries. 

        MolRelaxer uses an easy to compute potential which models stretch bend interaction and atomic overlap repulsion.
        It also uses a strict cutoff and continually updates the neighbour lists.
        This relaxation is primarily useful for distorted structues (for example due to editing).
        The result has good local geometries but poor global ones. 
        It can be used as a starting point for more elaborate energy functions.
        
        Design pattern: Facade for GradientFunction, PairListGenerator
    */
    
    class MOLCHEM_API MolRelaxer :  public GradientOptimizer, public OptimizerListener {
    public:
        ///
        bool optimize(double * p,int num);
        /** Initializes MolRelaxer

            \param[in] mol Molecule that is to be relaxed.
            \param[in] flexibleAtoms Bitfield indicating which atoms are flexible.
                       If flexibleAtoms is 0 all atoms will be flexible.
        */
        void init(const Molecule* mol,const McBitfield* flexibleAtoms=0);
        ///
        MolRelaxer();
        ///
        ~MolRelaxer();
    private:
        void setFunction(molchem::GradientFunction* g) {}
        OptimizerListener* cb;
        virtual bool notifyOptimizerStep(const Optimizer* o,int i,const double* p,int num,double value, const double * grad);
        virtual void notifyOptimizerEnd(const Optimizer* o,int i,const double* p,int num,bool succ);
        // The used optimizer
        GradientOptimizer* opt;
        // The used function
        MolRelaxingFunction* func;
    };
}

#endif

/// @}
