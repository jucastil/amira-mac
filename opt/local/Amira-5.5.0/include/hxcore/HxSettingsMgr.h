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
#ifndef HX_SETTINGS_H
#define HX_SETTINGS_H

#include "HxPreferences.h"

#include "HxAmiraWinDLLApi.h"

class HxSettingsIO;
class HxRecentFilesEntry;
class McBox2i;
class QxSettingsMgrNotifier;

class QFileDialog;

/** Singleton. Use QxSettingsIO to manage preferences. */
class HXCORE_API HxSettingsMgr {

public:

    static HxSettingsMgr* getInstance();

    /**
     *  Init non configurable preferences (OIV ones).
     *  Search for user preferences and if not found, create default ones.
     */
    void initPreferences();

    /**
     *  Set default preferences.
     */
    void setDefaultPreferences();

    /**
     *  Set preferences.
     *  If @c preferences is equal to current preferences,
     *  nothing is done unless you set @c force to true.
     */
    void setPreferences(const HxPreferences& preferences, bool force = false);

    /**
     *  Get a reference on the preference class.
     *  You can safely keep a reference on it.
     */
    inline const HxPreferences& getPreferences() const {return m_preferences;}

    /**
     *  Set another settings reader/writer.
     *  By default a @c QxSettingsIO is instantiated but, you can define
     *  another one.
     *  For convenience, the new @c settingsIO will be deleted when this
     *  instance will be deleted.
     *  Furthermore, if a new @c settingsIO is set, the old one will be deleted.
     *  Automatically call @c initPreferences().
     */
    void setSettingsIO(HxSettingsIO* settingsIO);

    /**
     *  Set that the EULA has been accepted.
     */
    void setEULAAccepted();

    /**
     *  Get the EULA acceptance date for this particular version number.
     *  Return an empty string if no EULA has been accepted.
     */
    McString getEULAAcceptance() const;

    /**
     *  Get recent loaded files.
     */
    McDArray<HxRecentFilesEntry> getRecentFiles();

    /**
     *  Set recent loaded files.
     */
    void setRecentFiles(const McDArray<HxRecentFilesEntry>& recentFiles);

    /**
     *  Get recent loaded networks.
     */
    McDArray<McString> getRecentNetworks();

    /**
     *  Set recent loaded networks.
     */
    void setRecentNetworks(const McDArray<McString>& recentNetworks);

    /**
     *  Set recent paths.
     */
    void setRecentPaths(const McString& pathListName, const McDArray<McString>& recentPaths);

    /**
     *  Get recent paths.
     */
    void getRecentPaths(const McString& pathListName, McDArray<McString>& recentPaths) const;

    /**
     *  Restore default recent documents.
     */
    void restoreDefaultRecentDocuments();

    /**
     *  Set a widget geometry information.
     */
    void setGeometry(const McString& objectName, const McBox2i& geometry);

    /**
     *  Get a widget geometry information.
     */
    void getGeometry(const McString& objectName, McBox2i& geometry) const;

    /**
     *  Restore default GUI layout settings.
     */
    void restoreDefaultLayoutSettings();

    /**
     *  Set a custom setting (to only be used with XPand).
     */
    void setCustom(const McString& settingName, const McString& value);

    /**
     *  Get a custom setting (to only be used with XPand).
     */
    void getCustom(const McString& settingName, McString& value) const;

    /**
     *  Set a custom setting array (to only be used with XPand).
     */
    void setCustom(const McString& settingName, const McDArray<McString>& arrayValue);

    /**
     *  Get a custom setting array (to only be used with XPand).
     */
    void getCustom(const McString& settingName, McDArray<McString>& arrayValue) const;

    /**
     *  Load preferences from a file (automatically open a file chooser dialog)
     */
    void loadPreferences();

    /**
     *  Save preferences to a file (automatically open a file chooser dialog)
     */
    void savePreferences();

    /**
     *  Load preferences from a file.
     */
    void loadPreferences(const McString& fileName);

    /**
     *  Save preferences to a file.
     */
    void savePreferences(const McString& fileName);

    /**
     *  Set the active edition name.
     *  It allows to manages settings by edition.
     *  Automatically call @c initPreferences().
     */
    void setActiveEdition(const McString& editionName);

    /** Connection point for Qt signals and slots.
      */
    QxSettingsMgrNotifier* const mNotifier;
private:
    /**
     *  Constructor.
     */
    HxSettingsMgr();

    /**
     *  Destructor.
     */
    virtual ~HxSettingsMgr();

    HxSettingsIO*           m_settingsIO;

    HxPreferences           m_preferences;

    QFileDialog*            m_prefsFileChooserDialog;

    /**
     *  Read system preferences.
     *  If the system preferences has a version < to
     *  the current one, this method will add new ones
     *  to the system and to @c m_preferences.
     */
    void readPreferences();

    /**
     *  Initialize the file dialog.
     */
    void initFileDialog();

    typedef enum
    {
        OPEN = 0,
        SAVE
    } FileMode;

    /**
     *  Show and execute the preference chooser dialog.
     */
    bool execPreferenceDialog(const FileMode mode, McString& selectedFile);

    /**
     *  Save recent paths used by @c m_fileDialog.
     */
    void savePrefRecentPaths();

    /**
     *  Save recent paths used by @c m_fileDialog.
     */
    void loadPrefRecentPaths();
};

#define theSettingsMgr (HxSettingsMgr::getInstance())

#endif

/// @}
