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

/// @addtogroup mclib mclib
/// @{
#ifndef MCSIMULATEDANNEALER_H
#define MCSIMULATEDANNEALER_H

#include "McWinDLLApi.h"
#include "McRandom.h"


class MCLIB_API McSimAnnState 
{
    ///
    bool changeSuggested;

    /// To be overloaded by derived class : suggest a state change and return the resulting change (newValue - oldValue)
    virtual float doSuggestChange() = 0;

    /// To be overloaded by derived class : execute the last suggested state change and return the new value
    virtual float doExecuteChange() = 0;

    /// To be overloaded by derived class : return the current value of the state
    virtual float doEvaluate() = 0;

public:
    ///
    McSimAnnState() : changeSuggested(false) {}

    ///
    virtual ~McSimAnnState() {}

    /// suggest a state change and return the resulting change (newValue - oldValue)
    float suggestChange();
    
    /// execute the last suggested state change and return the new value
    float executeChange();

    /// return the current value of the state
    float evaluate();
};


class MCLIB_API McSimulatedAnnealer {
    ///
    float mTFactor, mTemp;

    ///
    int mNTries, mNSucc, mTSteps;

public:
    ///
    McSimulatedAnnealer(int nTries, int nSucc, int tSteps, float t, float tFactor=0.9) 
        : mTFactor(tFactor),
          mTemp(t), 
          mNTries(nTries),
          mNSucc(nSucc),
          mTSteps(tSteps)
    {}
    
    ///
    void anneal(McSimAnnState * state, bool silent=true);
};

#endif

/// @}
