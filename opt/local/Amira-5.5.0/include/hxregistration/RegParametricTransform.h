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
#ifndef REG_PARAMETRIC_TRANSFORM
#define REG_PARAMETRIC_TRANSFORM

#include <math.h>
#include <Inventor/SbLinear.h>
#include <mclib/McDArray.h>
#include <mclib/McDVector.h>
#include <hxregistration/RegTypesAndMacros.h>

/// transform base class.
class RegParametricTransform
{
public:
    virtual ~RegParametricTransform() {};
    
    /// Clone inverse of this transformation.
    virtual RegParametricTransform* makeInverse () {return NULL;};
    
    double radToDeg(const double rad){return static_cast<double>(rad*(180.0/M_PI));}
    
    double degToRad(const double deg){return static_cast<double>(deg*(M_PI/180.0));} 
    
    /// Visualize current state of transformation
    virtual void update() = 0; 
    
    /// Get dimension of parameter vector.
    virtual int getParamVectorDim () = 0;
    
    /** Get number of variable parameters in parameter vector.
    * The variable parameters are those that may be modified i.e. for an
    * optimization. They are located at the beginning of the complete parameter
    * vector.
    */
    virtual int getVariableParamVectorDim () = 0;
    
    /// Get parameter stepping.
    virtual double getParamStep ( int, SbVec3d*  ) = 0;
    
    
    /** precomputer the step vector. 
    should be called in init method of RegFunctional.
    Later, this function should be made abstract */
    virtual void computeParamStep (SbVec3d* volSize=0){}
    
    /// modified access to parameter step.	
    inline const McDVector<double>&  getParamStep (); 
    
    /**The parameter Vector representing the transformation of the model.
    * This is the vector to be optimized
    */
    McDVector<double> paramVector; 
    
    /// the precomputed parameter step size 
    McDVector<double> paramStep; 
    
};

inline const McDVector<double>&  RegParametricTransform::getParamStep ()
{ return paramStep; }

#endif

/// @}
