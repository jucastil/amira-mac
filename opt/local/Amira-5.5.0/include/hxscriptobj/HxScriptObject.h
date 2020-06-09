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

/// @addtogroup hxscriptobj hxscriptobj
/// @{
#ifndef HX_SCRIPT_OBJECT
#define HX_SCRIPT_OBJECT

#include <hxscriptobj/HxScriptobjWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <hxcore/HxCompModule.h>
#include <hxscriptobj/HxPortScript.h>

/** Computational module to encapsulate scripts. */

class HXSCRIPTOBJ_API HxScriptObject : public HxCompModule {

  HX_HEADER(HxScriptObject);
  
  public:
    /// Constructor.
    HxScriptObject();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Required in order to customize save networks.
    void savePorts(FILE* fp);

    /// Required in this case in order to customize save networks.
    int saveCreation(FILE* fp, const char* dataDir, int savingFlags);

    /// look for local help page
    void getHelpFilename (McFilename& name);
    
    /// Provides restart button and filename text field.
    HxPortScript portScript;

    int parse(Tcl_Interp* t, int argc, char** argv);

    static int readScriptObject(const char* file);

  protected:
    /// Destructor.
    ~HxScriptObject();

    /// Icon color
    virtual McColor getIconColor();

    float version;

    McDArray<McString> values,valueNames;
    unsigned int lockScript:1;
    unsigned int firstCall:1;
    void callScript();
    void reset();
    void callTclDestructor();
    McDArray<HxPort*> dynamicPorts;
};
#endif

/// @}
