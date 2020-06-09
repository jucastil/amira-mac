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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_CRASHCLEANUP_H
#define HX_CRASHCLEANUP_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <mclib/McDArray.h>

/** This class provides a clean-up functionality. CleanUp functions can be registered
    in the array @c cleanUpFuncs. These functions will be executed if a class runs the member function
    @c cleanUp. An example can be found in the main.cpp of ZIBAmira. Here, the @c cleanUp function is 
    executed if ZIBAmira crashes.

    CleanUp functions can be added by the member function @c addCleanUpFunctionCB and removed by 
    @c removeCleanUpFunctionCB. An example can be found in HxMatlabEng.cpp.

    Only one instance of this class will be created. This instance can be accessed via the global
    pointer @c theCrashCleanUp. 

    authors: David Guenther, Falko Marquardt
*/

// CleanUp functions have a single input: the class object. Thus, internal
// class routines are called by the class object.
typedef void CrashCleanUpCB(void * userData);

class HXCORE_API HxCrashCleanUp
{
  //Constructor
  public:
    HxCrashCleanUp();

  //Methods
  public:
    ///Provides the global singleton instance @c theCrashCleanUp
    static HxCrashCleanUp * getCleanUp();

    ///Adds a cleanUp function to the list. 
    //We need a pointer to the class object itself @c userData, and a function pointer
    //to the cleanUp function.
    void addCrashCleanUpCB(CrashCleanUpCB * func, void * userData);

    ///Removes a cleanUp function.
    void removeCrashCleanUpCB(CrashCleanUpCB * func, void * userData);

    ///Main cleanUp routine. Every cleanUp function will be executed.
    void cleanUp();

  //Attributes
  private:
    ///CleanUp functions and their class objects are stored in a struct @c cleanUpFunc.
    struct cleanUpFunc
    {
        CrashCleanUpCB * func;
        void * userData;
    };

    ///All cleanUp-functions are stored in this array 
    McDArray<cleanUpFunc> cleanUpFuncs;
};

//This global define provides the instance @c theCrashCleanUp
#define theCrashCleanUp (HxCrashCleanUp::getCleanUp())

#endif

/// @}
