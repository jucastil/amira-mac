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
#ifdef REG_USE_HX_OPTIMIZE


#ifndef REGOBJFUNCTION_H
#define REGOBJFUNCTION_H


#include <hxoptimize/McObjectiveFunction.h>
#include <hxregistration/RegTimer.h>
#include <hxregistration/RegOptimizerCallback.h>
#include "RegFunctional.h"
#include "hxregistrationAPI.h"
#include <mclib/McDVector.h>


/** this class encapsulates a number of RegFunctionals and creates
a hierachy from these. Provides the interface to hxoptimize
*/
class HXREGISTRATION_API RegObjFunction : public McObjectiveFunction 
{

public:

	/// std constructor
	RegObjFunction (RegOptimizerCallback *r, RegTimer *t = NULL):
	  computeObject(r), timer(t), result_counter(0), print_time(true) {}

	  /// destructor
	  virtual ~RegObjFunction ()
	  {
		  for(int i = 1; i<mFunctionals.size();++i)
		  {
			  if ( mFunctionals[i] )
				  delete mFunctionals[i];
			  mFunctionals[i] = NULL;
		  }
	  }

	  /// this function allows a callback to the application in each iteration of an optimizer.
	  virtual void callback(const McOptVector& params, int level, const char
                          *trace = NULL); 

    void setTransformParameters(const McOptVector &in, McDVector<float> &out) ;

    void getTransformParameters(const McDVector<float> &in, McOptVector &out) ;
    
    /** Returns the value of the objective function with 
    the given set of @c value at a certain @c level. */
    virtual double value( const McOptVector& params, 
        int level=0 );

    /** Returns the gradient of the objective function with 
    the given set of @c params at a certain @c level. */
    virtual void gradient( const McOptVector& params, 
    McOptVector& grad, int level=0 );

    
    virtual double explore( const McOptVector& params, 
    McOptVector& grad, int level=0 );

    
    virtual void prolongate( const McOptVector& params1, int level1, 
        McOptVector& params2, int level2 ) ;


    /** Maps the parameters from a finer to a coarser level.
    \param params1 Parameters at the fine level
    \param level1 Fine level
    \param params2 Parameters at the coarse level
    \param level2 Coarse level 
    */
    virtual void restriction( const McOptVector& params1, int level1, 
        McOptVector& params2, int level2 ) ;


    /** add another functional. Extends the hierachy by one level 
        \return number of levels */
    int push(RegFunctional*);

	virtual float getExploreStepFactor(int level, int param) const { 
		return mFunctionals[level]->getTransform()->getParamStep( param, mFunctionals[level]->getModelSize() ); 
	}
    
    virtual int getNumLevels() const { return mFunctionals.size(); }

    
    /** returns the size of the input parameter vector for level */
    virtual int getDim(int level) const 
    {   return mFunctionals[level]->getTransform()->paramVector.size(); }


    inline RegFunctional* getFunctional(int i) { return mFunctionals[i]; }


protected:

    McDArray<RegFunctional*> mFunctionals;

    RegTimer *timer;

    ///The object implementing the compute method
    RegOptimizerCallback *computeObject;

    ///Needed to print every 10th result only.
    int result_counter;

    ///Results are supposed to be followed by time.
    bool print_time;

};






#endif
#endif


/// @}
