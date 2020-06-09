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
#ifndef VsFFSNetworkOutStream_FILE_H
#define VsFFSNetworkOutStream_FILE_H



#include <mclib/McPrimType.h>
#include <vsvolren/VsFFSPacket.h>


/////////////////////////////////////////////////////////////////////////////
// a stream for network sendings
class VsFFSNetworkOutStream
{
public:
	VsFFSNetworkOutStream(	int a_socket, 
							unsigned int a_bufferSize = 1048576 );
	~VsFFSNetworkOutStream();


	/**

	push a character on the stream and 

	*/
	bool FFS_FASTCALL pushChar( unsigned char  a_char );
	/**

	push a short on the stream and 

	*/
	bool FFS_FASTCALL pushShort( unsigned short  a_short );
	/**

	push a int on the stream and 

	*/
	bool FFS_FASTCALL pushInt( unsigned int  a_int );
	/**

	push a int64 on the stream 
	*/
	bool FFS_FASTCALL pushInt64( mcuint64  a_int );
	/**

	push memory on the stream 

	*/
	bool FFS_FASTCALL pushMem( char * a_mem, int a_len );

	/**

	clear the internal buffers

	*/
	void clear();

	/**

	flush the internal buffers to the socket
	flushes also provided additional data 
	
	This can be useful for large chunks. 
	The Chunks dont have to copied in the internal buffer

	*/
	bool FFS_FASTCALL flush( char * a_additionalData = 0, unsigned int a_len = 0 );


protected:
	/**

	return the used size of the internal buffer

	*/
	unsigned int	size();

	/**

	return the free bytes in the internal buffers

	*/
	unsigned int	freeMemory();

	/**

	assign a new socket

	*/
	void			FFS_FASTCALL setSocket( int a_socket );
private:
	
	int				m_socket;
	unsigned int	m_bufferSize;
	char  *			m_pushPtr;
	char *			m_buffer;


	/**

	send an reset the internal buffer

	*/
	bool FFS_FASTCALL sendBuffer( char * a_ptr, unsigned int a_len );
};
/////////////////////////////////////////////////////////////////////////////





#endif


/// @}
