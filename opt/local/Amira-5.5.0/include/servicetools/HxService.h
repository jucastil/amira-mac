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

/// @addtogroup servicetools servicetools
/// @{
#ifndef HX_SERVICE_H
#define HX_SERVICE_H

#include <qstring.h>
#include <qprocess.h>

#include <servicetools/HxServiceAPI.h>

typedef int HxServiceMainFunc(int,char**);

//-----------------------------------------------------------------------------
class HXSERVICE_API HxService
{
public:

    // return true if the current user has access to the services configuration privileges
    static bool canConfigureServices();

    static HxService* newInstance(const QString& name, const QString& host = QString::null);

    virtual ~HxService() {}

    virtual const QString host() const { return QString::null; }

    virtual bool isInstalled() = 0;
    virtual bool install(const QString& desc,
                         const QString& cmd,
                         const QString& user) = 0;
    virtual bool uninstall() = 0;

    virtual bool isRunning() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;

    // call this method in the main function of the service application
    // the given "f" function must run the Qt main loop qApp->exec()
    // (at least on windows platforms, since it uses qApp->quit() to exit)
    virtual int main(HxServiceMainFunc* f, int argc, char** argv) = 0;

    void setAttachedProcess( QProcess* proc){ m_proc = proc; }

protected:

    //Associated process
    QProcess* m_proc;
};

#endif // HX_SERVICE_H

/// @}
