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
#ifndef HX_NETRESOURCEMANAGER_H
#define HX_NETRESOURCEMANAGER_H

#include <mclib/McString.h>

class HxNetResourceManager;
class QxNetResource;
class QxNetResourceDialog;
struct Tcl_Interp;

typedef void HxNetResourceFinishCB(HxNetResourceManager* netman, int state,
    void* userdata);

/* Utility class to manage net resource calls.
*/
class HxNetResourceManager  {
  public:

    HxNetResourceManager(Tcl_Interp* inter, int argc, char** argv,
                         bool withGui = true);

    ~HxNetResourceManager();

    int loadData(int n, char** argv, int* pos);

    const char* getErrorMsg() { return errorMsg.getString(); }

    Tcl_Interp* getInter() { return loadInter; }

    int getArgc() { return loadArgc; }

    char** getArgv() { return &loadArgv[0]; }

    // sets the callback to be invoked when all remote accesses are finished
    void setFinishCallback(HxNetResourceFinishCB* clientFunc, void* clientData);

    // unsets the callback above
    void unsetFinishCallback() { finishCallback = NULL; }

    // returns the number of pending remote load requests
    int getNumPendingLoads() { return theNetResources.size(); }

    // interrupts all remote load requests
    void interrupt();

    // returns the global state (1 = everything was ok, 0 = something went wrong
    int getGlobalState() { return globalState; }

  protected:

    void createGui();

  private:

    static void dataLoadedCB(QxNetResource* res, int state, void* userdata);

    void remoteDataLoaded(QxNetResource* res, int state);

    static void stateChangedCB(QxNetResource* res, char* state, void* userdata);

    void remoteStateChanged(QxNetResource* res, char* state);

    McDArray<QxNetResource*> theNetResources;

    Tcl_Interp*     loadInter;
    McDArray<char*> loadArgv;
    int             loadArgc;
    McDArray<int>   argvPos;

    int globalState;

    McString errorMsg;

    McDArray<McString> urlList;
    McDArray<McString> stateList;

    HxNetResourceFinishCB* finishCallback;
    void*                  finishUserdata;

    QxNetResourceDialog* myDialog;

}; // HxNetResourceManager

#endif

/// @}
