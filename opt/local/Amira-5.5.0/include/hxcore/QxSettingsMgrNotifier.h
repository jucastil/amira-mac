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
#ifndef QX_SETTINGS_MGR_NOTIFIER_H
#define QX_SETTINGS_MGR_NOTIFIER_H

#include <qobject.h>
#include "HxAmiraWinDLLApi.h"

class HxPreferences;
class QxSettingsMgr;

class HXCORE_API QxSettingsMgrNotifier : public QObject {

    Q_OBJECT

  signals:
    /**
     *   Notify listeners that product/edition preferences has changed.
     *   Those preferences are registered into the system just before
     *   this listener is called.
     *   @param oldPreferences The preferences state just before that new ones have been registered.
     *   @param newPreferences The new preferences which have been registered.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

    /**
     *  Notify listeners that GUI layouts have been reset.
     */
    virtual void layoutsReset();

    /**
     *  Notify listeners that recent documents have been reset.
     */
    virtual void recentDocumentsReset();

    /**
     * Notify listeners that default preferences have been restored.
     */
    void defaultPreferencesRestored();

    /**
     * Notify listeners that preferences have been loaded from a file.
     */
    void preferencesLoaded();

    friend class HxSettingsMgr;
};

#endif

/// @}
