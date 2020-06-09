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

/// @addtogroup hxregistration hxregistration
/// @{
#ifndef HX_GRADIENT_OPTIMIZER_H
#define HX_GRADIENT_OPTIMIZER_H

#include <mclib/McDArray.h>
#include <hxregistration/RegTypesAndMacros.h>
#include <hxregistration/HxOptimizer.h>

/// Optimizer derived from Optimizer.
class  HXREGISTRATION_API HxGradientOptimizer : public HxOptimizer 
{
public:

    HxGradientOptimizer( RegOptimizerCallback *r, double tol = 0.0001, // ??? orig: 1.e-10
        double s = 0.5) ;
    
    virtual ~HxGradientOptimizer() {}
    
    virtual void optimize( double exploration = 1, double accuracy = 1 );

    void setStrategy(RegGradientStrategies s = REG_QUASI_NEWTON) { 
	strategy = s; 
    }
    
    struct EntryLinmin {
	double x;
	double f;
	
    };

private:
    RegGradientStrategies strategy; 

    double ftol;

    int getDirection(double deltaX,
		     McDVector<double> &direction,
		     double &current);
    
    void steepestDescent( const double exploration, const double accuracy);
    
    void conjugateGradients(const double exploration, const double accuracy,
			    const double ftol, double *fret, int *iter);
    
    void cg_experimental(const double exploration, const double accuracy,
			 const double ftol, double *fret, int *iter);
    
    void quasiNewton( const double exploration, const double accuracy,
		      const double ftol, double *fret, int *iter);
    
    double f1dim(int ncom, 
		 const McDVector<double> &pcom, 
		 const McDVector<double> &xicom, 
		 double x);
    
    void mnbrak(int ncom, 
		const McDVector<double> &pcom, 
		const McDVector<double> &xicom, 
		double *ax, double *bx, double *cx,
		double *fa, double *fb, double *fc);

    double brent(int n,
		 const McDVector<double> &p, 
		 const McDVector<double> &xi, 
		 double ax, double bx, double cx,
		 double tol, double *xmin);


    double golden(const McDVector<double> &p,
		  const McDVector<double> &xi,
		  double ax, double bx, double cx, 
		  double tol, double &xmin);
    
    void linmin(McDVector<double> &p, 
		McDVector<double> &xi, 
		double xmax,
		int n, 
		double *fret,
		double *xmin);

    // not to be used
    void dlinmin(McDVector<double> &p, 
		 McDVector<double> &xi, 
		 int n, 
		 double *fret,
		 double *xmin,
		 double maxStepLen,
		 double minStepLen);

    /// Factor by which the step size is reduced after each pass.  
    double stepFactor;

    McDArray<EntryLinmin> historyLinmin;

};


#endif
    

    

    

/// @}
