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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef EX_VIEWER_MANAGER_H
#define EX_VIEWER_MANAGER_H

#include <QObject>
#include <QTimer>

#include <vsvolren/VsRenderQueue2.h>

#include "mclib/McHandle.h"
#include "mclib/McHandable.h"
#include "mclib/McDArray.h"

#include "VisageViewerWinDLLApi.h"

class ExBaseViewer;

class HXVISAGEVIEWER_API ExViewerManager : public McHandable {
    
public:
    ExViewerManager(); 
    ~ExViewerManager() { mViewers.clear(); }

    int getNumViewers() { return mViewers.size(); }

    void clearViewers() { mViewers.clear(); }

    ExBaseViewer* getViewer(int idx) { return mViewers[idx]; }

    void addViewer(ExBaseViewer* viewerToAdd) { mViewers.append(viewerToAdd); }
    
    void removeViewer(ExBaseViewer* viewerToDelete);

protected:
    ExViewerManager(const ExViewerManager&);
    ExViewerManager& operator= (const ExViewerManager&);

private:
    McDArray<ExBaseViewer *> mViewers;
};

///////////////////////////////////////////////////////////////////////////////////////
class HXVISAGEVIEWER_API ExRepainter : public QObject
{
    Q_OBJECT

public:
    ~ExRepainter(){};

    static ExRepainter* instance() {
        static ExRepainter* pInstance = 0;
        if (!pInstance)
            pInstance = new ExRepainter;
        return pInstance;
    }

    void start();
    void stop();
    bool isRunning(); 

    
protected:
    ExRepainter();
protected slots:
    void repaintCB();
private:
    bool mRunning;
    QTimer mTimer;
    
};

#endif

/// @}
