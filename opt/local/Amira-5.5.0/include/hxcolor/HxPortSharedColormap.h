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

/// @addtogroup hxcolor hxcolor
/// @{
#ifndef HX_PORT_SHARED_COLORMAP_H
#define HX_PORT_SHARED_COLORMAP_H

#include <hxcolor/HxColorWinDLLApi.h>
#include <hxcolor/HxPortColormap.h>

class HXCOLOR_API HxPortSharedColormap : public HxPortColormap {

    MC_ABSTRACT_HEADER(HxPortSharedColormap);

public:

    /// Constructor.
    HxPortSharedColormap(HxObject * obj, const char * name, int localRange = 0, bool enableColormap = true);

    /// Destructor.
    virtual ~HxPortSharedColormap();

    /// Connects the port to given colormap.
    virtual int connect(HxObject * colormapObj);

    /// Removes connection.
    virtual void disconnect(bool disconnectedDuringConnection=false);

    /// Creates the "Edit" menu
    virtual void createMenu();
    
    /// Overloaded touch method adjusts min-max test.
    void touch(unsigned int mask=0xffffffff);

    /// Actions of the "Edit" menu
    void actionMenu(QAction * action);

    void showColormap(bool show = true);

    void createWidget(QWidget* parent);

    bool isColormapEnabled() const {return m_isEnabled;}

    void saveState(FILE* fp);

    /** Returns true if shared colormap ports are enabled in the
        application. By default this is the case in Avizo but not
        in Amira. This default can be overwritten by setting the
        global Tcl variable "hasPortSharedColormap" to either 1 or
        0 (e.g. in the Amira.init file under share/resources). If
        disabled, HxPortSharedColormap objects are still created
        but are hidden by default.
    */
    static bool hasPortSharedColormap();

    /// To update the port colormap for all the owner's downstream objects.
    void updateDSCColormaps(HxObject * object);
protected:
    bool m_isEnabled;
};

#endif


/// @}
