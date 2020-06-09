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

/// @addtogroup molalign molalign
/// @{
#ifndef MULTIALIGNMENTPRECOMPUTER_H
#define MULTIALIGNMENTPRECOMPUTER_H

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>

#include <molecule/MolTrajectory.h>
#include "PrecomputedAlignment.h"
#include "MolAlignWinDLLApi.h"

#include <mclib/McDMatrix.h>
#include <mclib/McMat4f.h>
#include <mclib/McMat3f.h>

///
class MOLALIGN_API MultiAlignmentPrecomputer
{
private:
    ///
    McHandle<MolTrajectory> trajectory;
    
    ///
    McDArray<McDMatrix<float> > configurations;

    //
    McHandle<Molecule> master;

    //
    McDArray<int> selection;

public:
    ///
    MultiAlignmentPrecomputer(MolTrajectory * t, Molecule * m = 0);
    
    ///
    MultiAlignmentPrecomputer(MolTrajectory * t, Molecule * m, const McDArray<int> & sel);
    
    ///
    void compute(PrecomputedAlignment & alignment,  McBitfield & active, 
                 const float * weights, McProgressInterface * progress=0);
    
 private:
    ///
    void multiAlign(PrecomputedAlignment & alignment,  McBitfield & active, 
                    McProgressInterface * progress=0);
    
    ///
    void initMulti(PrecomputedAlignment & alignment,  McBitfield & active, 
                   const float * weights, McProgressInterface * progress=0);
    
    ///
    static float calcUfromR(const McMat3f & r, McMat3f & u, bool calcValue=false);
};

#endif

/// @}
