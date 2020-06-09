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
#ifndef REG_MUTUALINFORMATION
#define REG_MUTUALINFORMATION

#include <hxregistration/RegMetric.h>
#include <mclib/McDVector.h>

///Abstract base class for voxel metrics using "mutual information"
class HXREGISTRATION_API RegMutualInformation : public RegMetric
{
public:
/** Constructor.
* For reference and model volume, init1D is called.
*@param ref The reference volume.
*@param mod The model (transformed) volume.
*@param interpolator The interpolation mechanism to be used. Currently not
*implemented
*@param minRef The minimal grey value of the reference to be considered in
*the histogram.
*@param maxRef The maximal grey value of the reference to be considered in
*the histogram.
*@param minMod The minimal grey value of the model to be considered in
*the histogram.
*@param minMod The maximal grey value of the model to be considered in
*the histogram.
    */
    RegMutualInformation(McPrimType pTRef, McPrimType pTMod, double minRef,double maxRef,double minMod,
        double maxMod, int binsRef, int binsMod, double maxCov = 1.);
    
	virtual void getState(RegMetric* clone)
	{
		RegMetric::getState(clone);

		dynamic_cast<RegMutualInformation*>(clone)->histogram2D = histogram2D;
	}    
    
    virtual void reset() 
	{
        RegMetric::resetSamples();
        histogram2D.fill(0);
    }
    
    virtual void increment( double a, double b ); 
    
    virtual void decrement( double a, double b );
    
    virtual void getMarginalEntropies(double& hRef, double& hMod);

    void getNumBins(int &binsRef, int &binsMod) 
    {
        binsRef = numBinsRef; 
        binsMod = numBinsMod;
    }
   
    McDVector<double>* getHistogram()
    {
        return &histogram2D;
    }
     
    void getParams(double &minRef, double &sclRef, double &minMod, double &sclMod, 
                   int &nBinsRef, int &nBinsMod, int &histoSize)
    {
        minRef = baseRef;
        sclRef = scaleRef;
        minMod = baseMod;
        sclMod = scaleMod;
        nBinsRef = numBinsRef;
        nBinsMod = numBinsMod;
        histoSize = histogram2D.size();
    }

    void accumulate(mclong s, mclong sT) 
    {
        RegMetric::accumulateSamples(s, sT);
    }
    
protected:
	///Is needed for method clone
    RegMutualInformation(McPrimType pTRef, McPrimType pTMod, mclong s, mclong sT, 
        double maxCov,	
        double minRef, double maxRef,
        double minMod,double maxMod, McDVector<double> hist, 
        int numRefBins , int numModBins, 
        double sR, double sM):
        RegMetric(s, sT, maxCov), primTypeRef(pTRef), primTypeMod(pTMod), histogram2D(hist),
        baseRef(minRef), scaleRef(sR), baseMod(minMod), scaleMod(sM), maxRef(maxRef), maxMod(maxMod), 
        numBinsRef(numRefBins), numBinsMod(numModBins) {}


    McPrimType primTypeRef, primTypeMod;
    
    void init1D(McPrimType primType, int& numBins, 
        double& min, double& factor, double max);
    
    void getJointEntropy(double& hRefMod);
    
    McDVector<double> histogram2D;
    
    double baseRef;
    
    double scaleRef;
    
    double baseMod;
    
    double scaleMod;
    
    double maxRef, maxMod;
    
    int numBinsRef, numBinsMod;
    
};


#endif

/// @}
