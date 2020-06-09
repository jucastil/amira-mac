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

/// @addtogroup hxmoledit hxmoledit
/// @{
#ifndef HX_BONDCALC_H
#define HX_BONDCALC_H

#include <hxmoledit/HxMolEditWinDLLApi.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxmolecule/MolFilter.h>

class HxData;
class McString;

class HXMOLEDIT_API HxBondCalc : public HxCompModule {

    HX_HEADER(HxBondCalc);

   
public:

#define NUM_MODES 4
    enum  BC_MODE {
        BCM_STANDARD=0,
        BCM_LENGTHTABLE=1,
        BCM_DISTANCE=2,
        BCM_ALL=3,
    };

#define NUM_ACTIONS 3
    enum  BC_ACTION {
        BCA_ADD=0,
        BCA_REMOVE=1,
        BCA_REPLACE=2,
    };

    /// Constructor.
    HxBondCalc();
  
    /// Destructor.
    virtual ~HxBondCalc();

    /// Maximal distance under that bonds are recognized
    HxPortRadioBox portMode;

    /// Maximal distance under that bonds are recognized
    HxPortFloatSlider portMaxDist;

    /// Do it button.
    HxPortButtonList portAction;
    
    /// Filter
    MolFilter filter;

    /// Update method.
    virtual void update();
    
    /// Compute method.
    virtual void compute();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

protected:    
    /// Compute interface between atoms.
    int computeInterface();
    
    /// This function does the actual computation.
    void doIt();
    
    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    int updateAction;
};

#endif

/// @}
