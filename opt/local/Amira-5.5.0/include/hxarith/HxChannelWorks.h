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

/// @addtogroup hxarith hxarith
/// @{
#ifndef HX_CHANNELWORKS
#define HX_CHANNELWORKS

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxRegVectorField3.h>
#include <hxarith/HxArithWinDLLApi.h>

/// Module for rearranging individual channels of multiple input objects.
class HXARITH_API HxChannelWorks : public HxCompModule {

  HX_HEADER(HxChannelWorks);

  protected:

    struct Entry {
        int input;
        int channel;
        char text[32];
    };

    enum { NINP=3 };

  public:

    /// Constructor.
    HxChannelWorks();

    /// Update method initializes channel menus properly.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Connections to input objects.
    HxConnection* inputs[NINP];

    /// Defines number of channels of output object (1,2,3,6).
    HxPortMultiMenu portOutput;

    /// These menus define the mapping from input to output channels.
    HxPortMultiMenu* channels[6];

    /// Do it button.
    HxPortDoIt* portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Check if given data object can be created by this module.
    virtual int canCreateData(HxData* data, McString& createCmd);

  protected:

    HxObject* objInp[NINP];
    McTypedObject* lattInp[NINP];
    McDArray<Entry> entries;

    int nEntries;
    int nChannels;

    /// Destructor.
    ~HxChannelWorks();

    /// Save ports.
    virtual void savePorts(FILE* fp);

    void checkUndefinedValuesConsitency(bool& currentHasUndefinedValue,
                                        bool newHasUndefinedValue,
                                        double& currentUndefinedValue,
                                        double newUndefinedValue);
};

#endif

/// @}
