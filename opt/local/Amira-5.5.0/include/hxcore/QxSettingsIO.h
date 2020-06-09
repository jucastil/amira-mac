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
#ifndef QX_SETTINGS_H
#define QX_SETTINGS_H

#include "HxAmiraWinDLLApi.h"

#include "HxSettingsIO.h"

#include <QSettings>
#include <QSet>
#include <QString>

#include <mclib/McDArray.h>

class QStringList;
class HxRecentFilesEntry;

/** This class is in charge of witting and reading preferences. */
class HXCORE_API QxSettingsIO : public QSettings, public HxSettingsIO {

public:

    QxSettingsIO(const McString& organization, const McString& application);

    /**
     *  Return the preferences version. 0 if preferences doesn't exist.
     */
    virtual int getPreferencesVersion();

    /**
     *  Tell if preferences exist on the system (registry or .ini file).
     */
    virtual bool systemHasPreferences();

    /**
     *  Set preferences.
     */
    virtual void setPreferences(const HxPreferences& preferences);

    /**
     *  Get preferences.
     */
    virtual void getPreferences(HxPreferences& preferences);

    /**
     *  Set that the EULA has been accepted.
     */
    virtual void setEULAAccepted();

    /**
     *  Get the EULA acceptance date for this particular version number.
     *  Return an empty string if no EULA has been accepted.
     */
    virtual McString getEULAAcceptance();

    /**
     *  Get recent loaded files.
     */
    virtual McDArray<HxRecentFilesEntry> getRecentFiles();

    /**
     *  Set recent loaded files.
     */
    virtual void setRecentFiles(const McDArray<HxRecentFilesEntry>& recentFiles);

    /**
     *  Get recent loaded networks.
     */
    virtual McDArray<McString> getRecentNetworks();

    /**
     *  Set recent loaded networks.
     */
    virtual void setRecentNetworks(const McDArray<McString>& recentNetworks);

    /**
     *  Set recent paths.
     */
    virtual void setRecentPaths(const McString& pathListName, const McDArray<McString>& recentPaths);

    /**
     *  Get recent paths.
     */
    virtual void getRecentPaths(const McString& pathListName, McDArray<McString>& recentPaths) const;

    /**
     *  Restore default recent documents.
     */
    virtual void restoreDefaultRecentDocuments();

    /**
     *  Set a widget geometry information.
     */
    virtual void setGeometry(const McString& objectName, const McBox2i& geometry);

    /**
     *  Get a widget geometry information.
     */
    virtual void getGeometry(const McString& objectName, McBox2i& geometry) const;

    /**
     *  Restore default GUI layout settings.
     */
    virtual void restoreDefaultLayoutSettings();

    /**
     *  Set a custom setting (to be used with XPand).
     */
    virtual void setCustom(const McString& settingName, const McString& value);

    /**
     *  Get a custom setting (to be used with XPand).
     */
    virtual void getCustom(const McString& settingName, McString& value) const;

    /**
     *  Set a custom setting array (to be used with XPand).
     */
    virtual void setCustom(const McString& settingName, const McDArray<McString>& arrayValue);

    /**
     *  Get a custom setting array (to be used with XPand).
     */
    virtual void getCustom(const McString& settingName, McDArray<McString>& arrayValue) const;

    /**
     *  Save preferences to a file.
     */
    virtual void savePreferences(const McString& fileName, const HxPreferences& preferences);

    /**
     *  Load preferences from a file.
     */
    virtual bool loadPreferences(const McString& fileName, HxPreferences& preferences);

    /**
     *  Set the active edition name
     */
    virtual void setEdition(const McString& editionName);

protected:

    /**
     *  Get the EULA entry in the system.
     */
    QString getEULAEntry() const;

    /**
     *  Build a QStringList from a McDArray.
     */
    void buildStringListFromArray(const McDArray<McString>& stringArray, QStringList& stringList) const;

    /**
     *  Build a McDArray from a QStringList.
     */
    void buildArrayFromStringList(const QStringList& stringList, McDArray<McString>& stringArray) const;

    /**
     *  Build a HxRecentFilesEntry from a QVariantMap.
     */
    bool buildFilesEntryfromVariantMap(const QVariantMap& vm, HxRecentFilesEntry& filesEntry) const;

    /**
     *  Build a QVariantMap from a HxRecentFilesEntry.
     */
    void buildVariantMapFromFilesEntry(const HxRecentFilesEntry& filesEntry, QVariantMap& vm) const;

    /**
     *  Return the path list setting name.
     */
    QString getRecentPathListSettingName(const McString& pathListName) const;

    /**
     *  Get the geometry setting name for @c objectName.
     */
    QString getGeometrySettingName(const McString& objectName) const;

    /**
     *  Return the custom settings name.
     */
    QString getCustomSettingName(const McString& customName) const;

    /**
     *  Set preferences to a specific @c settingsIO
     */
    void setPreferences(const HxPreferences& preferences, QSettings* settingsIO);

    /**
     *  Read preferences from a specific @c settingsIO
     */
    void getPreferences(HxPreferences& preferences, QSettings* settingsIO);


private:

    /**
     * List of custom preferences keys.
     * Used to save/restore also custom preferences when setting/getting preferences.
     */
    mutable QSet<QString> m_customPreferences;
};
#endif

/// @}
