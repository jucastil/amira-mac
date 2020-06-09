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

/// @addtogroup hxteamworkserver hxteamworkserver
/// @{
#ifndef HX_TEAMWORKSERVER_H
#define HX_TEAMWORKSERVER_H

#include <qmap.h>
#include <Q3ServerSocket>
#include <Q3Socket>
#include <qstring.h>

#define TEAMWORK_DEFAULT_PORT 17345

//---------------------------------------------------------------------------//
struct HxTWSession;

struct HxTWUser {
    QString alias;
    Q3Socket* socket;
    HxTWSession* session;
};

//---------------------------------------------------------------------------//
struct HxTWSession {
    QString title;
    QString password;
    HxTWUser* op;
    QMap<QString,HxTWUser*> users;
};

//---------------------------------------------------------------------------//
class HxTeamWorkServer : public Q3ServerSocket
{
    Q_OBJECT

public:

    HxTeamWorkServer(int port);
    ~HxTeamWorkServer();

    virtual void newConnection(int socket);
    
protected slots:

    void socketReadyRead();
    void socketClosed();
    void socketError();

protected:

    void sendToAll(HxTWSession* session, const QString& msg);
    void sendToAllExcept(HxTWSession* session, HxTWUser* except, const QString& msg);
    void sendTo(HxTWUser* user, const QString& msg);

    void quit(HxTWUser* user);
    void setOperator(HxTWUser* user);

    static void socketSend(Q3Socket* socket, const QString& msg);
    static int  socketRecv(Q3Socket* socket, QString& msg, int msecs = -1);

    QMap<Q3Socket*,HxTWUser*> m_users;
    QMap<QString,HxTWSession*> m_sessions;
};

#endif // HX_TEAMWORKSERVER_H

/// @}
