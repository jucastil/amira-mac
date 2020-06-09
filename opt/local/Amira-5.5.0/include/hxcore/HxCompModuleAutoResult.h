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
#ifndef HXCOMPMODULEEX_H
#define HXCOMPMODULEEX_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxWorkArea.h>
#include <mclib/McWatch.h>

#include "HxAmiraWinDLLApi.h"


/** Extends a compute module to easier deal with more than one result slot.

    @author Tino Weinkauf
*/
class HXCORE_API HxCompModuleAutoResult : public HxCompModule
{
    HX_ABSTRACT_HEADER(HxCompModuleAutoResult);

//Friends
//Types
public:
    /** Holds a create cmd for a slot - needs to be integrated into
        HxCompModule::ResultSlot later.  At the moment, this is a
        hack.
    */
    struct CreateCmdItem
    {
        CreateCmdItem()
            :slotID(0),
             cmd(""),
             bAddName(true),
             GlobalIndicator(0)
        {}

        CreateCmdItem(int argID, const McString& argCmd, bool argAddName, int argIndicator)
            :slotID(argID),
             cmd(argCmd),
             bAddName(argAddName),
             GlobalIndicator(argIndicator)
        {}

        int slotID;
        McString cmd;
        bool bAddName;
        int GlobalIndicator;
    };

    typedef McDArray<CreateCmdItem> SlotCmdArray;
    
//Construction / Deconstruction
protected:
    HxCompModuleAutoResult(const McTypeInfo* dataType)
        :HxCompModule(dataType)
    {};
    
    virtual ~HxCompModuleAutoResult(){};

//Methods
public:

    /** Adds a new result slot.

        The result slot gets a name.  Furthermore, the implementation
        keeps track of how to re-create the result.

        @returns ID of the new result slot. Save this id for future reference.
    */
    int addResultSlot(const char* name, bool bCanCreate,
                      const McString& slotStartCreateCmd,
                      const McString& slotEndCreateCmd);

    /** Invalidates a certain result.

        This indicates, that the module is not able to restore the
        result.  Call this function, if your internal structures are
        about to change due to e.g. a call to compute.
    */
    void invalidateResultSlot(int id = 0);

    /** Invalidates all result slots.

        This indicates, that the module is not able to restore the
        results.  Call this function, if your internal structures are
        about to change due to e.g. a call to compute.
    */
    void invalidateAllResultSlots(bool bGlobal = false);

    /** Adds a TCL-Command to restore the result of a certain slot.

        If id refers to a known result slot (id >= 0), then this
        command is added in order to restore this slot.

        If id refers to an unknown result slot (id >= 0), then the
        function simply returns without doing something.
        
        If id == -1, then the given commands are interpreted as being
        global.  These commands are meant to be issued independent of
        a certain result slot.  They will be issued before any
        result-dependent commands.  In the end it will look like this:

        \verbatim
        GlobalCreateCmds
        
        slot1StartCreateCmd
        slot1CreateCmd1
        slot1CreateCmd2
        ...
        slot1EndCreateCmd
        
        slot2StartCreateCmd
        slot2CreateCmd1
        slot2CreateCmd2
        ...
        slot2EndCreateCmd
        \endverbatim
    */
    void addResultSlotCreateCmd(const McString& slotCreateCmd, bool bAddName, int id = 0);

    void addResultSlotCreateCmd(const char* slotCreateCmd, bool bSplitAndAddName, int id = 0);


    void setResult(HxData* result, unsigned int mask=0xffffffff)
    {
        HxCompModule::setResult(0, result, mask);
    }

    void setResult(int id, HxData* result, unsigned int mask=0xffffffff)
    {
        HxCompModule::setResult(id, result, mask);
    }

    /** Sets the result and stores the TCL-Commands to reproduce it.

        @todo This func should invalidate the result slot (the
        TCL-Commands of it) prior to setting it. This makes handling
        in a lot of cases easier, where the slots are not used in a
        "appending" manner.  Furthermore, there should be a func
        called "addToResult" or "appendToResult", which appends the
        given TCL-Commands to the already existing ones.
    */
    void setResult(int id, HxData* result, const char* CreateCmd, unsigned int mask=0xffffffff);

    void setResult(HxData* result, const char* CreateCmd, unsigned int mask=0xffffffff)
    {
        setResult(0, result, CreateCmd, mask);
    }
    

    /** Checks, if result can be re-created.
     */
    int canCreateData(HxData* pData, McString& createCmd);

    /** Issues the global creation command.
     */
    void savePorts(FILE* fp);

    ///Start counting and show progress bar 
    void startProgress(int numSteps, const char* message,
                       const float updateIntervalTime = 1.0f,
                       const float updateIntervalData = 0.05f);

    ///Stop progress bar 
    void stopProgress();

    static bool progressStatic(void* userData, const int n = 1, const char* message = NULL);
    static bool progressStaticNoTime(void* userData, const int n = 1, const char* message = NULL);

    /** Sometimes show the progress and test for interrupt.

        @returns false, if computation shall be interrupted.
        @returns true, if computation may go on.
    */
    bool progress(const int n = 1, const char* message = NULL);

    bool progressNoTime(const int n = 1, const char* message = NULL)
    {
        //Go forward
        progSoFar += n;
        
        //Calculate difference between now and last update
        float progCurrentData = float(progSoFar) / progTotal;

        //Update the progress bar, if enough data has been processed
        if ( (progCurrentData >= progLastUpdateData + progMinUpdateIntervalData))
        {
            //Remember current values
            progLastUpdateData = progCurrentData;

            //Update the progress bar
            theWorkArea->setProgressValue(progCurrentData);

            //Update the message displayed in the progress bar
            if (message)
            {
                McString ProgressString(progStrBase);
                ProgressString += message;
                theWorkArea->setProgressInfo(ProgressString.getString());
            }

            //Return whether the user interrupted the computation or not
            return !(theWorkArea->wasInterrupted());
        }

        //Return true to indicate, that the computation may go on
        return true;
    }


private:
    McString GatherSlotCmds(const int id, const int indicator) const;

    McString lastProgressMessage;

//Attributes
protected:
    //Result Slot stuff:

    /// A Hack to hold the commands for each slot. Needs to be merged with HxCompModule::ResultSlot.
    SlotCmdArray SlotCmds;
    SlotCmdArray GlobalCmds;


    //Progress stuff:

    ///The max Value to where the progress bar goes
    float progTotal;
    ///The actual Value where the progress bar is at the moment
    int progSoFar;
    ///The (base) string to be shown in the progress bar
    McString progStrBase;
    ///Minimum time interval to be elapsed before the progress bar is updated
    float progMinUpdateIntervalTime;
    ///Minimum data interval (between 0 and 1) to be elapsed before the progress bar is updated
    float progMinUpdateIntervalData;
    ///Last Update Time
    float progLastUpdateTime;
    ///Last Update Value (between 0 and 1)
    float progLastUpdateData;
    ///Timer for the progress bar
    McWatch progTimer;
    ///Time needed for last computation
    float statComputationTime;
};



#endif // HXCOMPMODULEEX_H


/// @}
