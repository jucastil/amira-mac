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

/// @addtogroup hximproc hximproc
/// @{
#ifndef HX_UNIFORM_DIFFUSION_FILTER2D
#define HX_UNIFORM_DIFFUSION_FILTER2D


#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>

#include <hxfield/HxUniformScalarField3.h>

#include "HxImageVisionEditor.h"
#include "HxImprocWinDLLApi.h"


/// class implements a 2D diffusion filter
class HXIMPROC_API  ImDiffusionFilter2D : public ImFilter2D {
	
	MC_HEADER(ImDiffusionFilter2D);
	
public:
	
    /// Constructor
    ImDiffusionFilter2D(HxEditor* editor=0);
	
	
	
	
    virtual void apply2D( class McTypedData2D* src, 
			  class McTypedData2D* dst=NULL);
	
	/// Sets the filters parameters if any
    void setParameters(const ImFilterParameters *param);

    /// Updates the filter parameters class
    void updateParameters(ImFilterParameters *param);
		
	
    /// Update method.
    virtual void update();
    
    HxPortFloatTextN portTime;
    
    HxPortFloatTextN portLambdas;
	
    HxPortFloatTextN portSigmas;
	
    HxPortMultiMenu portFiltertype;
	
    HxPortMultiMenu portDifftype;
	
    HxPortRadioBox portRegtype;
	
    HxPortRadioBox portNumerik;
    
 

    static ImFilter3D* createFilter(HxEditor* e) {
	return new ImDiffusionFilter2D(e); }
	
	
protected:
    
    virtual ~ImDiffusionFilter2D();
    
    void filter2d();
	
    void gradient2d();
	
  
    void regularize2d();
	
   
private:
	
	
    virtual void apply( class HxUniformScalarField3* src, 
			class HxUniformScalarField3* dst ,
			class McProgressInterface* progress=NULL);


	
    HxUniformScalarField3* field; // source
    HxUniformScalarField3* res ;  // destination
	

	
	
	
	
};

#endif

/// @}
