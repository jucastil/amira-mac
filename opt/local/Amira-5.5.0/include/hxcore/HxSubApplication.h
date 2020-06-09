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
#ifndef HX_SUBAPPLICATION_H
#define HX_SUBAPPLICATION_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxBase.h>
#include <mclib/McTypedObject.h>
#include <mclib/McHandable.h>

class HxObject;
struct HxSubApplicationInfo;

/** Base class of Amira sub-applications. */
class HXCORE_API HxSubApplication : public HxBase
{
    MC_ABSTRACT_HEADER(HxSubApplication);

  public:

    /** Returns true if sub-applications are enabled. This is the case for
        Amira but not for Avizo. */
    static bool hasSubApplications();

    /** Called by the GUI when the sub-application should be started.
        Derived sub-application classes need to reimplement this method
        and call this method from their own start() method. */
    virtual void onStart();

    /** Called by the GUI when the the sub-application should be stopped.
        Derived sub-application classes need to reimplement this method
        and call this method from their own stop() method. */
    virtual void onStop();

    /** Returns true if the sub-application is active (has been started) */
    bool running() const;

    virtual void newObjectsCreated(const McDArray<HxObject*>& newObjects);

    virtual void aboutToDeleteObjects(const McDArray<HxObject*>& objectsToBeDeleted);

    /** Create sub-applications for pool and tree-view (if available). */
    static void init();

    /** Returns the sub-application which is currently active (running). */
    static HxSubApplication* current();

    /** Returns the previously active sub-application different than this one. */
    static HxSubApplication* previous();

    /** Makes a new sub-application active. The sub-application is created
        automatically if it does not already exist. Before the new application
        is activated, the onStop() method is called for the currently
        active sub-application. Also, onStart() is called for the new
        sub-application. */
    static HxSubApplication* makeCurrent(HxSubApplicationInfo* info);

    /** Makes a new sub-application active. */
    static HxSubApplication* makeCurrent(HxSubApplication* subApplication);

    /** Makes a new sub-application active. */
    static HxSubApplication* makeCurrent(const char* subAppInfoName);
    
    // Returns the width of the work area
    int getMainWidth();
    // Returns the width of the viewer panel
    int getViewerWidth();

    // Returns whether a sub-application specific help exists and optionally
    // gets the path to its index file.
    bool hasHelpFile(McString* const helpfile=NULL) const;

    // Sets the help index file for this sub-application.
    void setHelpFile(McString const& package,McString const& filename,McString const& anchor=McString());

  protected:

    /// Constructor is protected since this is an abstract class.
    HxSubApplication();

    /// Destructor, declared virtual.
    virtual ~HxSubApplication();

    static HxSubApplication* sCurrentSubApplication;
    static HxSubApplication* sPreviousSubApplication;

    bool mIsRunning;

    int mMainRectWidth;
    int mViewerRectWidth;

    McString m_help_file;
    McString m_help_file_anchor;
};

#endif

/// @}
