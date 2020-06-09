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
#ifndef VsFFSNetworkInStream_FILE_H
#define VsFFSNetworkInStream_FILE_H


#include <mclib/McMemArray.h>
#include <mclib/McPrimType.h>


/////////////////////////////////////////////////////////////////////////////
// a stream class for receiving from a socket
class VsFFSNetworkInStream
{
public:
	VsFFSNetworkInStream(	int a_socket, 
							unsigned int a_buffer = 3, 
							unsigned int a_bufferSize = 1048576 );

	~VsFFSNetworkInStream();



	/**

	a_enable == true -> stream receive and buffer as much as can received
	a_enable == false -> stream buffer nothing

	*/
	void FFS_FASTCALL accumulateStream( bool a_enable );


	/**

	skip some bytes

	*/
	bool FFS_FASTCALL pop( int a_len );

	/**

	return a character an remove it from the stream

	*/
	bool FFS_FASTCALL popChar( unsigned char & a_char );


	/**

	return a short an remove it from the stream

	*/
	bool FFS_FASTCALL popShort( unsigned short & a_short );
	/**

	return a int an remove it from the stream

	*/
	bool FFS_FASTCALL popInt( unsigned int & a_int );
	/**

	return a int64 an remove it from the stream

	*/
	bool FFS_FASTCALL popInt64( mcuint64 & a_int );
	/**

	return some memory an remove it from the stream

	*/
	bool FFS_FASTCALL popMem( char * a_mem, int a_len );


	
	/**

	return a character 

	*/
	bool FFS_FASTCALL getChar( unsigned char & a_char );
	/**

	return a int 

	*/
	bool FFS_FASTCALL getInt( unsigned int & a_int );


	
	/**

	reset and clear the internal buffers

	*/
	void clear();


protected:
	int		size();
	int		actReadBufferSize();
	void	FFS_FASTCALL setSocket( int a_socket );
	int		getSocket(){ return m_socket; }
	


private:
	
	bool			m_accumulate;
	int				m_socket;
	unsigned int	m_actReadBuffer,
					m_actWriteBuffer,
					m_bufferSize;

	char  * m_readPtr, 
		  *	m_writePtr;


	McMemArray<char *> m_buffer;



	/**

	receive bytes from the socket into the buffer

	*/
	bool	FFS_FASTCALL accumulateBuffer( int a_maximalSize );

	/**

	increment the read pointer with respect to the ring buffer

	*/
	bool	FFS_FASTCALL incReadPointer( int distance );
};
/////////////////////////////////////////////////////////////////////////////



#endif


/// @}
