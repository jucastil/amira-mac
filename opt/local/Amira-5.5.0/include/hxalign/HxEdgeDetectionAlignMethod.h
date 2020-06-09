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

/// @addtogroup hxalign hxalign
/// @{
#ifndef HX_EDGE_DETECTION_ALIGN_METHOD
#define HX_EDGE_DETECTION_ALIGN_METHOD

#include <hxalign/HxAutoAlignMethod.h>
#include <hxcore/HxPortMultiMenu.h>


class HxAlignSlices;
class HxPortMultiMenu;
;


/** Abstract class for auto align methods. */
class HxEdgeDetectionAlignMethod : public HxAutoAlignMethod
{

public:
    /** Parameterconstructor
     *  @param parent - pointer to the belonging align manager
     */
    HxEdgeDetectionAlignMethod(HxAlignSlices* parent);

    /** Destructor */
    virtual ~HxEdgeDetectionAlignMethod(){};

    static const char* getMethodName();

    static HxAutoAlignMethod* createMethod(HxAlignSlices* parent);

    virtual bool doLayout();

    
protected:
   
    
    bool sample(unsigned char* srcData, unsigned char* destData);

 private:
    	void BresenhamLine(int x1, int y1, int x2, int y2,  unsigned char* data, int& xMax, int& yMax, bool invert);

	int getThreshold(unsigned char* srcData);
	int calculateHistogramAverage(unsigned char* srcData);
	int calculateHistogramMax(unsigned char* srcData);
	int calculateHistogramMedian(unsigned char* srcData);
	bool checkNeighbourhood( unsigned char* data, int x, int y, bool invert);

	void calcCenter(unsigned char* data,const int* dim,int border,float* mX,float* my,bool invert);

	int calcEntropy(unsigned char* data,int slice);


	const int* dims;
	int matrixX;
	int matrixY;
	int matrixRaster;
	int imageRaster;
	float matPerc;
	int threshold;
	int nDataVar;
 
	HxEdgeDetectionAlignMethod();

	static const char* methodName;
};

#endif

/// @}
