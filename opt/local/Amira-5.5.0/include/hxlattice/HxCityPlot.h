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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HX_CITY_PLOT_H
#define HX_CITY_PLOT_H

#include <hxlattice/HxLatticeWinDLLApi.h>

#include <hxsurface/HxQuadBase.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/SoDecal.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxStackedScalarField3.h>

#include <hxsurface/HxQuadBase.h>

class SoShapeKit;
class HxUniformScalarField3;

/// uniform/stacked scalar field.
class HXLATTICE_API HxCityPlot : public HxQuadBase {

  HX_HEADER(HxCityPlot);
  
  public:
    /// Constructor.
    HxCityPlot ();

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    HxPortRadioBox          portSliceOrientation;
    HxPortIntSlider 	    portSliceNumber;
    HxPortFloatSlider 	    portScale;

	// HxUniformScalarField3 
	HxConnection portFilterMaskField;

	HxPortRadioBox portFilterMaskType; 
	
  protected:
    virtual ~HxCityPlot ();

    HxLattice3		    *lattice;
    int			    numSlices;
    int			    sliceNumber;
    int			    sliceOrientation;

    float		    minVal;
    float		    maxVal;
    float		    maxTrans;	// max allowed translation for dragger
    float bbox[6];

    void updateAll();

	// Get the value in grid. Set the base coordinate in coord1.
	float getValue(int &x, int &y, int &z, McPrimType dataType, void* data, const mculong* dims, float coords1[3]);

	enum FilterType {
        ALL=0,
        ON=1,
        OFF=2,        
    };

	int computeNumberOfElementsFromFilter(FilterType type, mculong dim[3], HxUniformScalarField3* filterMask);

	bool isVisibleWithFilter(int a, int b, mculong dim[3], const mculong* fDim, HxUniformScalarField3* filterMask);

	void setCityPlotElementColor(int id, unsigned int col);

  private:

};

#endif

/// @}
