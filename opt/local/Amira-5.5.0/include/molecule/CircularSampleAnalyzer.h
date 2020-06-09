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

/// @addtogroup molecule molecule
/// @{
#ifndef CircularSampleAnalyzer_H
#define CircularSampleAnalyzer_H

#include "MoleculeWinDLLApi.h"
#include "SampleAnalyzer.h"

#include <mclib/McDMatrix.h>

///
class MOLECULE_API CircularSampleAnalyzer : public SampleAnalyzer
{
public: 
    ///
    CircularSampleAnalyzer() {}
    
    ///
    float mean();

    ///
    virtual void distFunc(McDArray<float> & xValues, 
                          McDArray<float> & yValues, 
                          float winWidth = 0);

    void findModes(McDArray<float> & modes, int numBins);

    void fitWrappedNormal(McDArray<float> & mu, 
                          McDArray<float> & rho, 
                          McDArray<float> & coeff,
                          McDArray<float> & xValues, 
                          McDArray<float> & yValues,
                          McDArray<float> & xModel, 
                          McDArray<float> & yModel,
                          McDArray<float> & xData, 
                          McDArray<float> & yData,
                          McDArray<float> & ydmu, 
                          McDArray<float> & ydsig);


    int nModes;

    void levenbergMarquardtMin(float x[], float y[], float sig[], int ndata, 
                               float a[], int ia[], int ma, 
                               McDMatrix<float> & covar, 
                               McDMatrix<float> & alpha, double & chisq);
    
    void funcs(float x, float a[], float &y, McDArray<float> & dyda);
    void funcsOld(float x, float a[], float &y, McDArray<float> & dyda);

    void checkNextStep(float atry[], float da[]);

    ///
    bool isEmpty() { return size() == 0; }

    ///
    float findBestCut();
};


#endif

/// @}
