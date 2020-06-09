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
#ifndef MOLCHEM_FUNCTION_H
#define MOLCHEM_FUNCTION_H

#include "MolChemWinDLLApi.h"

#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McDArray.h>

class McBitfield;

namespace molchem {

    /** \brief Interface for multidimensional scalar functions.
    */
    class MOLCHEM_API Function : public McHandable {
    public:
        /** Computes value of the function.
        
        \param[in] p Point in space at which the function will be evaluated.
        \param[in] num Size of array p
        \param[out] v Value of the function at p.
        \return Was the computation successful? 
        */
        virtual bool computeValue(
            const double * p, int num,
            double& v) = 0;
    };

    /** \brief Interface for multidimensional scalar functions which have a gradient.
    */    
    class MOLCHEM_API GradientFunction : public Function {
    public:
        GradientFunction(double stepSize=1.);

        /** Computes gradient of the function with the finite difference (FD) method. 
            This method usually should not be overloaded. Modules using GradientFunction
            should call computeGradient instead, which exposes the best method
            for the computation of the gradient. This method should only be called
            if it is explicitly desired use a numerically generated gradient.

            \param[in] p Point in space at which the function will be evaluated.
            \param[in] num Size of array p
            \param[out] grad Gradient of the function at p.
            \return Was the computation successful? 
        */
        virtual bool computeGradientFD(
            const double * p,int num,
            double * grad);

        /** Computes gradient of the function. 
            The default implementation calls computeGradientFD.
            Overload this method if you know the analytic gradient.

            \param[in] p Point in space at which the function will be evaluated.
            \param[in] num Size of array p
            \param[out] grad Gradient of the function at p.
            \return Was the computation successful? 
        */

        virtual bool computeGradient(
            const double * p, int num,
            double * grad);

        /** Computes value and gradient of the function. 
            The default implementation calls computeGradient and computeValue.
            Usually computing the gradient and the value of the function have a lot of
            computations in common, which leaves room for optimization when computing both together.
            Overload this method if you have such an optimized method.

            \param[in] p Point in space at which the function will be evaluated.
            \param[in] num Size of array p
            \param[out] value Value of the function at p.
            \param[out] grad Gradient of the function at p.
            \return Was the computation successful? 
        */
        virtual bool computeValueAndGradient(
            const double * p, int num,
            double& value,
            double * grad);

        /// Sets the step size used in finite different evaluation of the gradient
        void setFDStepSize(double step) { mStepSize = step;}

    private:
        /* Stepsize for the numerical approximation of the gradient using FD */
        double mStepSize;
    };


    /** Represents a multi variable gradient function which has a set of fixed degrees of freedom 
        as another gradient function of lower dimension.

        This function can be used as a wrapper of another gradient function.
        A bitfield may be supplied which specifies which elements of the space are fixed.
        This is helpful for gradient minimization because the gradient optimizers are more efficient
        if only used with the minimal degrees of freedom.

    */
    class MOLCHEM_API GradientFunctionFixed : public GradientFunction {
    public:
    	// -- the function is not owned by this object
        GradientFunctionFixed(GradientFunction* f); 
        ~GradientFunctionFixed();
        ///
        virtual bool computeValue(
            const double * p, int num,
            double& value);
        ///
        virtual bool computeGradient(
            const double * p,int num,
            double * grad);
        ///
        virtual bool computeValueAndGradient(
            const double * p,int num,
            double& value,
            double * grad);        
        /// Specifies mask of degrees of freedom. For all set bits the corresponding element of the gradient will be set to 0.
        void setFixed(const McBitfield* fixed,const McDArray<double>& fixedValues);
    protected:
        // Will set certain elements of grad to 0, as specified by the mask bitfield
        void setG(const McDArray<double>& grad,double * g, int num);
        void setP(const double * p, int num);
        McDArray<double> fixedVal;
        McDArray<int> nonFixed;
        GradientFunction* f;
    };

    /** Masks certain entries of the gradient with 0.

        This function can be used as a wrapper of another gradient function.
        A bitfield may be supplied which specifies which elements of the gradient
        will be set to 0 whenever the gradient has been computed. 
        This is useful in conjunction with a GradientOptimizer,
        as it will keep the masked degrees of freedom fixed.
    */
    class MOLCHEM_API GradientFunctionMask : public GradientFunction {
    public:
    	// -- the function ise not owned by this object
        GradientFunctionMask(GradientFunction* f,const McBitfield*); 
        ~GradientFunctionMask();
        ///
        virtual bool computeValue(
            const double * p, int num,
            double& value);
        ///
        virtual bool computeGradient(
            const double * p,int num,
            double * grad);
        ///
        virtual bool computeValueAndGradient(
            const double * p,int num,
            double& value,
            double * grad);        
        /// Specifies mask of degrees of freedom. For all set bits the corresponding element of the gradient will be set to 0.
        void setMask(const McBitfield* b);
    protected:
        // Will set certain elements of grad to 0, as specified by the mask bitfield
        void maskGradient(double * grad, int num);
        McBitfield* mask;
        GradientFunction* f;
    };

    /** \brief Function that is a linerar combintation of several individual terms.

        GradientFunctionContainer is a gradient function that can cobime
        several gradient function by multiplying them with a factor and adding them up.
    */    

    class MOLCHEM_API GradientFunctionLinearCombination : public GradientFunction {
    protected:
        McDArray<McHandle<GradientFunction> > functions;
        McDArray<double> factors;
    public:
        GradientFunctionLinearCombination(); 
        ~GradientFunctionLinearCombination();
        ///
        virtual bool computeValue(
            const double * p, int num,
            double& value);
        ///
        virtual bool computeGradient(
            const double * p,int num,
            double * grad);
        
        virtual bool computeValueAndGradient(
            const double * p,int num,
            double& value,
            double * grad);        
            // -- the functions are not owned by this object
        void appendFunction(GradientFunction* f, double fac=1.);
        int getNumFunctions() const;
        GradientFunction* getFunction(int i) const;
    };

}
#endif

/// @}
