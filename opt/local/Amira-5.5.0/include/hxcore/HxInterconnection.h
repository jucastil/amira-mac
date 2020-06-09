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
#ifndef HX_INTERCONNECTINTERFACE_H
#define HX_INTERCONNECTINTERFACE_H

#include <mclib/McInterface.h>
#include <tcl.h>

#include "HxAmiraWinDLLApi.h"

/** Manager for objects or ports interconnection.
When ports are interconnected, any modification to a port is spread to connected ones.

Objects are implicitly connected. We use 1 HxInterconnection per port to avoid recursive loops
during fire methods.

A port is connected to another port either by the "connect" TCL command, or connect() function of HxPort.
The "connect" TCL command has the following syntax :
<module label> <port name> connect <module2 label> [<port2 name>]
If <port2 label> is not given, the command will use <port name> to retrieve the port of module2.

When connecting ports, objects are automatically connected so that fire() is spread to all connected objects.

A derived HxPort implementation must follow rules if the port can be interconnected :
- call PORT_SPREAD ( <port dynamic type> , <port function> ) in each function setting a value and in guiCallback()

Interconnected ports are saved at the end of an .hx file, because all the modules must be created.

When interconnecting ports, a check is done to forbid loops.
*/

class HxPort;

//Macros for modifications spreading

#define START_SPREADING \
    for (int spreading_i=0; spreading_i < cnx->getNumConnections(); spreading_i++ ){   \
    HxInterconnection* portCnx = cnx->getConnection(spreading_i);    \
    if ( !cnx->canSpread( portCnx ) )  \
    continue;   \
    portCnx->setSpreading( cnx, false );  

#define END_SPREADING   \
    portCnx->setSpreading( cnx, true );}}  \

#define PORT_SPREAD( dyntype, expression ){  \
    HxInterconnection* cnx = getInterconnection(false); \
    if ( cnx && cnx->getSpreading() ){ \
    START_SPREADING \
    ((dyntype*)portCnx->getPort())->expression;\
    END_SPREADING }

class HXCORE_API HxInterconnection 
{

  public:

    HxInterconnection();

    //Constructor for a port interconnection
    HxInterconnection( HxPort* port );

    //Constructor for an object interconnection
    HxInterconnection( HxObject* obj );

    //Destructor
    ~HxInterconnection();

    //Disconnect cnx from connections
    void disconnect( HxInterconnection* cnx );

    /*
    Interconnection routine
    Port interconnection is only possible between ports of the same typeID.
    When port p0 connect to port p1, p0 and p1 become interconnected.
    p1 is added to p0 connections, and reverse.
    Port typeID validity is checked at connection.
    */
    bool interconnect( HxInterconnection* obj, bool state = true, bool connectReverse = true );

    //Return if spreading is enabled to given connection
    bool canSpread( HxInterconnection* cnx );

    //Sets an interconnected object to which spreading is allowed or not 
    void setSpreading( HxInterconnection* cnx, bool spread );

    //Sets if spreading is enabled
    void setSpreading( bool spread ){ m_spreading = spread; }

    //Returns spreading state
    bool getSpreading(){ return m_spreading; }

    //Returns number of connections
    int getNumConnections(){ return m_connections.size(); }

    //Returns connection at position pos
    HxInterconnection* getConnection( int pos ){ return m_connections[pos]; }

    //Returns connected object (owner if HxObject or object() is HxPort)
    HxObject* getObject();

    //Returns connected port 
    HxPort* getPort(){ return m_port; }

    //Returns related port 
    HxPort* getRelatedPort(){ return m_relatedPort; }
    
    //Set related port
    void setRelatedPort( HxPort* port ){ m_relatedPort = port; }

    /**
    Save connected ports. As connected ports will also call saveConnectionState,
    save "connectTo" instead of "connect" .
    */
    void saveConnectionState( FILE* fp );

    //Return true if there would be a connection loop between this and cnx
    bool connectionLoop( HxInterconnection* cnx, HxInterconnection* emitter  );

    /// Spread fire method for owner object
    /// emitter is the original emitter for fire()
    /// firedObjects stores fired objects
    void spreadFire( HxObject* emitter, McDArray<HxObject*>& firedObjects );

protected:

    void commonInit();

    //Connected objects
    McDArray<HxInterconnection* > m_connections;

    //Object to which no spreading is allowed (generally emitter of spreading)
    HxInterconnection* m_noSpreadingConnection;

    //Global spreading state
    bool m_spreading;

    //Port owner
    HxPort* m_port;

    //Object owner
    HxObject* m_obj;
    
    //Port owner (if owner is object)
    HxPort* m_relatedPort;
};

#endif




/// @}
