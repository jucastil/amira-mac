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
#ifndef REG_CORRELATION_RATIO
#define REG_CORRELATION_RATIO

#include <hxregistration/RegMetric.h>
//#include <hxregistration/RegHistogram2D.h>


///Voxel metric using "correlation ratio"
class HXREGISTRATION_API RegCorrelationRatio : public RegMetric
{
public:
/** Constructor.
* The inherited ructor is called to initialize the given datasets.
* Afterwards, the original (untransformed) probability distribution 
* functions of model and reference are calculated.
*@param ref The reference (fixed) volume.
*@param model The model (transformed) volume.
*@param numRefBins The desired number of bins to classify the 
* reference data. If this parameter is zero (default), a suitable value
* is automatically determined.
*@param numModBins The desired number of bins to classify the 
* floating data. If this parameter is zero (default), a suitable value
* is automatically determined.
    */	
    RegCorrelationRatio(double minR, double maxR, double minM, double maxM, double maxCov = 1.);
    
    /// Destructor.
    virtual ~RegCorrelationRatio () { }

	virtual void getState(RegMetric* clone)
	{
		RegMetric::getState(clone);

		dynamic_cast<RegCorrelationRatio*>(clone)->squareReference = squareReference;
		dynamic_cast<RegCorrelationRatio*>(clone)->squareModel = squareModel;
		dynamic_cast<RegCorrelationRatio*>(clone)->product = product;
		dynamic_cast<RegCorrelationRatio*>(clone)->meanReference = meanReference;
		dynamic_cast<RegCorrelationRatio*>(clone)->meanModel = meanModel;
	}  
    
    //wird fuer BestDirectionOptimizer gebraucht!
    virtual RegMetric *clone() ;
    
    virtual void increment( double a, double b ) ; 
    
    virtual void decrement( double a, double b ) ;
    
    virtual void getMarginalEntropies( double& reference, double& model ) ;
    
    virtual double getResult() ;
    
    virtual void reset() ;  
    
    void accumulate(mclong s, mclong sT,
        double squareRef, double squareMod, double prod, double meanRef, double meanMod)
    {
        squareReference += squareRef;
        squareModel     += squareMod;
        product         += prod;
        meanReference   += meanRef;
        meanModel       += meanMod;
        RegMetric::accumulateSamples(s, sT);
    }

    void getRanges(double &minR, double &maxR, double &minM, double &maxM)
    {
        minR = minRef;
        maxR = maxRef;
        minM = minMod;
        maxM = maxMod;
    }

    void getLastMeanValues(double &lastMeanR, double &lastMeanM)
    {
        lastMeanR = lastMeanRef;
        lastMeanM = lastMeanMod;
    }

private:
	//Needed for deep copy
    RegCorrelationRatio(mclong s, mclong sT, 
        double minR, double maxR, double minM, double maxM, 
        double maxCov, double squareReference, 
        double squareModel, double product, double meanReference, double meanModel,
        double lastMeanR, double lastMeanM) :
    RegMetric(s, sT, maxCov), 
        squareReference(squareReference), squareModel(squareModel), product(product), 
        meanReference(meanReference), meanModel(meanModel),
        minRef(minR), maxRef(maxR), minMod(minM), maxMod(maxM),
        lastMeanRef(lastMeanR), lastMeanMod(lastMeanM) {}

    double squareReference;
    
    double squareModel;
    
    double product;
    
    double meanReference;
    
    double meanModel;
    
    double minRef, maxRef, minMod, maxMod;

    double lastMeanRef, lastMeanMod;

};


#endif

/// @}
