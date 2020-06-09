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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VsFFSPacketInStream_FILE_H
#define VsFFSPacketInStream_FILE_H

#include <mclib/McPrimType.h>
#include <mclib/McString.h>


#include <vsvolren/VsFFSBuffer.h>
#include <vsvolren/VsFFSNetworkInStream.h>




/////////////////////////////////////////////////////////////////////////////
// a network stream class for receiving of FFS Packets 
class VsFFSPacketInStream: protected VsFFSNetworkInStream
{
public:
	VsFFSPacketInStream(	int a_socket = -1, 
							unsigned int a_buffer = 4, 
							unsigned int a_bufferSize = 1048576 );
	~VsFFSPacketInStream();


	
	/**

	assign a new socket to the object

	*/
	void FFS_FASTCALL attachSocket( int a_socket, bool a_accumulate = true );



	bool FFS_FASTCALL recvDataTransmit( VsFFSBuffer & a_buffer, unsigned int & a_blockNr );
	bool FFS_FASTCALL recvDataTransmitInfos( unsigned int & a_blockNr, unsigned int & a_size );
	bool FFS_FASTCALL recvDataTransmitBuffer( char * a_buffer, unsigned int a_len );
	bool recvDataTransmitEnd();
	bool recvDisconnect();
	bool FFS_FASTCALL recvError( unsigned int & a_error );
	bool FFS_FASTCALL recvConnectionInitResponse( mcuint64 & a_uid, mcuint64 & a_fileSize );
	bool recvConnectResponse();
	bool FFS_FASTCALL recvConnect( mcuint64 & a_uid );
	bool FFS_FASTCALL recvDataRequestResponse( unsigned int & a_error, unsigned int & a_firstPacketSize, unsigned int & a_packetSize, unsigned int & a_blockCount );
	bool FFS_FASTCALL recvDataRequest( mcuint64 & a_filePosition, mcuint64 & a_length );
	bool FFS_FASTCALL recvConnectionInit(  mcuint64 & a_serverKey, McString & a_file );


	/**

	get the packet type of the next packet without
	removing from the stream

	*/
	bool FFS_FASTCALL getNextPacketType( unsigned int  & a_packet );
	
};
/////////////////////////////////////////////////////////////////////////////












#endif


/// @}
