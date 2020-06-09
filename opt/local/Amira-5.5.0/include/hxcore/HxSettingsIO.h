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
#ifndef HX_SETTINGSIO_H
#define HX_SETTINGSIO_H

#include "HxAmiraWinDLLApi.h"

#include <mclib/McDArray.h>
#include <mclib/McString.h>

class McBox2i;

class HxPreferences;

class HxRecentFilesEntry;

/** This class defines an interface for reading and writing settings. */
class HXCORE_API HxSettingsIO {

public:

    virtual ~HxSettingsIO() {}

    /**
     *  Return the preferences version. 0 if preferences doesn't exist.
     */
    virtual int getPreferencesVersion() = 0;

    /**
     *  Tell if preferences exist on the system.
     */
    virtual bool systemHasPreferences() = 0;

    /**
     *  Set preferences.
     */
    virtual void setPreferences(const HxPreferences& preferences) = 0;

    /**
     *  Get preferences.
     */
    virtual void getPreferences(HxPreferences& preferences) = 0;

    /**
     *  Set that the EULA has been accepted.
     */
    virtual void setEULAAccepted() = 0;

    /**
     *  Get the EULA acceptance date for this particular version number.
     *  Return an empty string if no EULA has been accepted.
     */
    virtual McString getEULAAcceptance() = 0;

    /**
     *  Get recent loaded files infos.
     */
    virtual McDArray<HxRecentFilesEntry> getRecentFiles() = 0;

    /**
     *  Set recent loaded files infos.
     */
    virtual void setRecentFiles(const McDArray<HxRecentFilesEntry>& recentFiles) = 0;

    /**
     *  Get recent loaded networks.
     */
    virtual McDArray<McString> getRecentNetworks() = 0;

    /**
     *  Set recent loaded networks.
     */
    virtual void setRecentNetworks(const McDArray<McString>& recentNetworks) = 0;

    /**
     *  Set recent paths.
     */
    virtual void setRecentPaths(const McString& pathListName, const McDArray<McString>& recentPaths) = 0;

    /**
     *  Get recent paths.
     */
    virtual void getRecentPaths(const McString& pathListName, McDArray<McString>& recentPaths) const = 0;

    /**
     *  Restore default recent documents.
     */
    virtual void restoreDefaultRecentDocuments() = 0;

    /**
     *  Set a widget geometry information.
     */
    virtual void setGeometry(const McString& objectName, const McBox2i& geometry) = 0;

    /**
     *  Get a widget geometry information.
     */
    virtual void getGeometry(const McString& objectName, McBox2i& geometry) const = 0;

    /**
     *  Restore default GUI layout settings.
     */
    virtual void restoreDefaultLayoutSettings() = 0;

    /**
     *  Set a custom setting (to be used with XPand).
     */
    virtual void setCustom(const McString& settingName, const McString& value) = 0;

    /**
     *  Get a custom setting (to be used with XPand).
     */
    virtual void getCustom(const McString& settingName, McString& value) const = 0;

    /**
     *  Set a custom setting array (to be used with XPand).
     */
    virtual void setCustom(const McString& settingName, const McDArray<McString>& arrayValue) = 0;

    /**
     *  Get a custom setting array (to be used with XPand).
     */
    virtual void getCustom(const McString& settingName, McDArray<McString>& arrayValue) const = 0;

    /**
     *  Save preferences to a file.
     */
    virtual void savePreferences(const McString& fileName, const HxPreferences& preferences) = 0;

    /**
     *  Load preferences from a file.
     */
    virtual bool loadPreferences(const McString& fileName, HxPreferences& preferences) = 0;

    /**
     *  Set the active edition name
     */
    inline virtual void setEdition(const McString& editionName) {m_editionName = editionName;}

protected:

    HxSettingsIO() {}

    McString m_editionName;

};
#endif

/// @}
