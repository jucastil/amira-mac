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
#ifndef MOLCHEM_OPTIMIZER_H
#define MOLCHEM_OPTIMIZER_H

#include "MolChemWinDLLApi.h"

#include <mclib/McHandable.h>

namespace molchem {

    class Function;
    class GradientFunction;
    class OptimizerListener;
    class InternalCoordinateConverter;
    class Logger;
    
    /** \brief Interface for function minimiztation
    
        To use an Optimizer you have to supply a molchem::Function. The call
        of optimize will then minimize the  function
        until either an internal criterium is reached or a supplied 
        molchem::OptimizerCallback returns false.

    **/
    class MOLCHEM_API Optimizer : public McHandable {

    public:
        Optimizer();

        /** Sets the objective function. */
        virtual void setFunction(Function* f);

        /** Sets an OptimizerListener. */
        void setListener(OptimizerListener* cb);

        /** Does optimization.

        \param[in|out] p Must contain starting point and will return local minimum. 
        \return Returns false if error occured, before optimization terminated.
        
        */
        virtual bool optimize(double * p,int num)=0;

        /** Sets termination criterion: Optimization will terminate after num steps. Disabled by default.*/
        void setTerminationMaxSteps(int num);

        /** Sets termination criterion: Optimization will terminate if new and old function value differ by <= value. Disabled by default.
            This criterion can only apply after at least 1 minimization step.*/
        void setTerminationValueDiff(float value);

        /** Sets termination criterion: Optimization will terminate if (newval/oldval)/dimension <= value. Disabled by default
            This criterion can only apply after at least 1 minimization step.*/
        void setTerminationValueDiffPerDim(float value);
    protected:

        /** Must be called before first and after each optimization step and before other criteria are tested.

            Tests termination criterion and calls Listener if existant.
            Returns whether optimization has to terminate.

            This method may be overridden to add new termination criteria specific for
            the implemented optimizer. However, super::checkTerminate(...) must be called
            at the beginning of the overriding method.
        */
        virtual bool checkTerminate(int step,const double * p,int num,double value,const double * grad );
        
        /// Must be called before optimize method returns
        void callNotifyEnd(int step,const double * p,int num,bool suc);

        Function* f;
        static Logger* logger;
    private:
        OptimizerListener* cb;
        double vLast;
        // Termination criterion: difference between successive  energies. If <=0 -> not used
        double vDiff;
        // Termination criterion: difference between successive  energies per dimension. If <=0 -> not used
        double vDiffPerDim;
        // Termination criterion. If <0 -> not used
        int maxSteps;
    };

    /** \brief Interface for function minimiztation
    
        To use an Optimizer you have to supply a molchem::Function. The call
        of optimize will then minimize the  function
        until either an internal criterium is reached or a supplied 
        molchem::OptimizerCallback returns false.

    **/
    class MOLCHEM_API GradientOptimizer : public Optimizer {

    public:
        GradientOptimizer();
        
        /** Sets the objective function. */
        virtual void setFunction(GradientFunction* f);  

        /// Sets termination criterion: Optimization will terminate if rms of grad <= value. Disabled by default.
        void setTerminationGradRMS(double value);

    protected:

        /** Must be called before first and after each optimization step and before other criteria are tested.

            Tests termination criterion and calls Listener if existant.
            Returns whether optimization has to terminate.

        */
        virtual bool checkTerminate(int step,const double * p,int num,double value,const double * grad );

    private:
        // Termination criterion: rms of gradient. If <=0 -> not used
        double gradRMS;
    };

    /** \brief Standard implementation of Gradient Optimizer 
    
    **/
    class MOLCHEM_API StandardGradientOptimizer : public GradientOptimizer {
    public:
        ///
        StandardGradientOptimizer();
        ///
        bool optimize(double * p, int num);
        // Use Conjugate gradient method (default)
        void setMethodCG();
        // Use Broyden-Fletcher-Goldfarb-Shanno
        void setMethodBFGS(double linStepMax);
        // Steepest descent
        void setMethodSD();
    private:
        friend double sd_value(const double * p, int num);
        friend double sd_gradient(const double * p,int num,double * grad);
        friend bool sd_terminate(double fold,double fnew,const double * p,int num,const double * grad);
        int step;
        double linStepMax;
        int method;
    };
 

    /** Evolutionary Programming */
   class MOLCHEM_API OptimizerEP : public Optimizer {
   public:
       /// Size of the population. Must be larger than 1. Fittest individual is retained at each step
       int populationSize;
       /* Crossover probability (0..1). Default is 0. For this rate of offsprings, reproduction will be sexual,
       i.e. a second parent from the retained population will be selected and the chance for a single paremeter
       coming from one of the two is .5.
       */
       double crossoverProbability;
       double mutationProbability;
       OptimizerEP();
       bool optimize(double* p, int num);
       // Gradient function that is used for local minimization
       GradientFunction* gf;
       // Internal coordinate converter that is used to convert to cartesian coordinates for the local minimization
       InternalCoordinateConverter* conv;
    };
}

#endif

/// @}
