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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLSIM_OPTIMIZER_CALLBACK_H
#define MOLSIM_OPTIMIZER_CALLBACK_H

#include "MolChemWinDLLApi.h"


namespace molchem {

    class Optimizer;

    /** Listener that can be supplied to a molchem::Optimizer
        which will then report each optimization step .

        Design Pattern: Observer
    */
    class MOLCHEM_API OptimizerListener {
    public:
        virtual ~OptimizerListener() {}
        /** Will be called after each step of optimization.
        
        \param[in] i Index of optimiztaion step (counting from 0, which is before first step).
        \param[in] p Point after the i'th optimization step
        \param[in] num Size of p
        \param[in] value Value after the i'th optimization step.
        \param[in] grad Gradient after the i'th optimization step. Pointer may be 0, if Optimizer does not evaluate gradients.
        \return If false, the optimization will terminate.
        */
        virtual bool notifyOptimizerStep(const Optimizer* o,int i,const double * p,int num,double value, const double* grad) = 0;
        virtual void notifyOptimizerEnd(const Optimizer* o,int i,const double * p,int num,bool suc) = 0;
    };

}

#endif





/// @}
