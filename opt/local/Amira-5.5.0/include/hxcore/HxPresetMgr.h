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
#if !defined HX_PRESET_MGR_H
#define HX_PRESET_MGR_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxInterpreter.h>
#include <hxcore/HxPreset.h>

#include <mclib/McString.h>
#include <mclib/McDArray.h>

/*** 
    This class is used to manage the different presets of the
    application.  A preset defines what is to be shown in the GUI.  It
    does not reduce any functionality, but just hides some
    Modules/Editors etc from the user.
*/

class HXCORE_API HxPresetMgr 
{

public:

    /** 
    * Returns pointer to global instance.
    */
    static HxPresetMgr* getGlobalInstance(bool create = true);

    /** 
    * Interface to Tcl scripting language.
    */
    static int staticParse(ClientData data, Tcl_Interp* t, int argc, char** argv);

    /**
    * To register a preset.
    */
    void registerPreset(HxPreset* preset);

    /**
    * To set the current preset by its name.
    */
    void setCurrentPreset(McString presetName);

    /** 
    * To get the current preset.
    */
    HxPreset* getCurrentPreset()
    {
        return m_currentPreset;
    }

    const McDArray< HxPreset* >& getAvailablePresets() const
    {
        return m_availablePresets;
    }

private:

    /** 
     * Constructor.
     */
    HxPresetMgr();

    /** 
     * Destructor.
     */
    virtual ~HxPresetMgr();

    /** 
     * The available presets.
     */
    McDArray< HxPreset* > m_availablePresets; 

    /** 
     * The current preset.
     */
    HxPreset* m_currentPreset;

    /**
     * Name of old preset stored in registry
     **/
    McString m_oldPreset;
    bool m_hasOldPreset;

    /** 
     * Instance.
     */
    static HxPresetMgr* s_theInstance;

    /**
     *  Set the preset preference
     */
    void setPresetPreference(const McString& presetName);
};

//------------------------------------------------------------------------------
#define thePresetMgr HxPresetMgr::getGlobalInstance()

#endif // HX_PRESET_MGR_H

/// @}
