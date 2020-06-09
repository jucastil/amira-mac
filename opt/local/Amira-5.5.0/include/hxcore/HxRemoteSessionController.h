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
#ifndef HX_REMOTE_SESSION_CONTROLLER_H
#define HX_REMOTE_SESSION_CONTROLLER_H

#include <qobject.h>

#include <mclib/McString.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class Q3Socket;

//---------------------------------------------------------------------------//
class HXCORE_API HxRemoteSessionController : public QObject
{
    Q_OBJECT

public:

    HxRemoteSessionController();
    virtual ~HxRemoteSessionController();

    bool isActive() const;
    virtual bool isMaster() const = 0;
    virtual bool isSlave() const = 0;
	
    virtual void sendTo(int remoteID, const McString& msg) = 0;
    virtual void sendToAll(const McString& msg) = 0;
    McString receive();

    virtual void render() = 0;

    virtual bool handleDelayedMessage(const McString& msg) = 0;

    virtual void initConnection(HxRemoteSessionController* ctrl, int remoteID) = 0;

signals:

    void stateChanged();
    void newMessage();
    void newConnection(int remoteID);

protected slots:

    void socketReadyRead();
    virtual void socketError() = 0;

protected:

    void setActive(bool);

    static void socketSend(Q3Socket* socket, const McString& msg);
    static int  socketRecv(Q3Socket* socket, McString& msg, int msecs = -1);

    virtual bool handleImmediateMessage(const McString& msg) = 0;

    virtual Q3Socket* mainSocket() = 0;

private:

    bool m_active;
    McDArray<McString> m_pendingMessages;
    bool m_reading;
};

#endif // HX_REMOTE_SESSION_CONTROLLER_H


/// @}
