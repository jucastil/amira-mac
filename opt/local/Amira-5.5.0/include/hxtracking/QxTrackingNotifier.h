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

/// @addtogroup hxtracking hxtracking
/// @{
#ifndef HX_TRACKING_NOTIFIER_H
#define HX_TRACKING_NOTIFIER_H

#include <QObject>
#include <mclib/McString.h>

class HxTracking;
class QMenu; 
class QDir;
class QAction;

/**  Helper class derived from QObject. This class provides some
     slots which can't be members of HxVREnvironment or HxTracking. */
class QxTrackingNotifier : public QObject {

  Q_OBJECT

  public:
    /// Returns pointer to global tracking notifier object.
    static QxTrackingNotifier* getGlobalInstance();

    /** Searches all *.cfg files in $AMIRA_ROOT/share/config/vr and
        $AMIRA_LOCAL/share/config/vr. These configurations are stored in
        @c configFiles. They are also inserted into the config menu
        of the Amira main window. If the method is called multiple
        times and if the config files have changed in the meantime
        the config menu is updated accordingly. */
    void searchConfigFiles();

    int getNumConfigFiles() const { return configFiles.size(); }

    const char* getConfigFile(int k) const { return configFiles[k].dataPtr(); }

    /** Retrieves the absolute path of a configuration file from 
        its base name. Returns NULL if none is found. */
    const char* getConfigFullPath(const char* configBaseName) const;

    QMenu* vrMenu();

  public slots:

    /** This slot is triggered by a qtimer in HxTracking::compute */
    void configure();

    /** This slot is connected to the triggered(QAction*) signal of the
        config menu. The method creates a tracking module if necessary
        and uses it to load the specified VR configuration. */
    void configure(QAction * action);
    
    void mouseMode();
    
    void redraw();

    void autoConnect();

    void changeConfigsPath();

  protected:
    /** Constructor. The constructor calls @c searchConfigFiles() and
        thus automatically initializes the config menu of the amira
        main window. No HxTracking object is created. This happens
        later when calling @c loadConfig() or @c configure(). */
    QxTrackingNotifier();

    void configure(const QString & config);
    void appendConfigs(QDir& dir);

    QMenu* mVRMenu;
    QMenu* mConfigMenu;

    McDArray<McString> configFiles;
    McString configDir;
};

#define theTrackingNotifier QxTrackingNotifier::getGlobalInstance()

#endif

/// @}
