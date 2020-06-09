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
#ifndef VsFFSBuffer_FILE_H
#define VsFFSBuffer_FILE_H



#include <mclibthreaded/McMutex.h>
#include <vsvolren/VsFFSPacket.h>


/////////////////////////////////////////////////////////////////////////////
// encaps a buffer with some edit functionality
class VsFFSBuffer
{
public:
	VsFFSBuffer( unsigned int a_size = 0 );
	~VsFFSBuffer();

	/**

	set a new size and can preserve the content of the old buffer

	*/
	void			FFS_FASTCALL resize( unsigned int a_size, bool a_preserveContent = false );

	/**

	returns the size if the buffer

	*/
	unsigned int	size();

	/**
		
	set the size to 0

	*/
	void			clear();

	/**

	crop out a chunk of the buffer

	*/
	void			FFS_FASTCALL crop( unsigned int a_position, unsigned int a_length );

	
	/**

	crop only from the front 

	*/
	void			FFS_FASTCALL cropFront( unsigned int a_position );

	/**

	crop only from the back

	*/
	void			FFS_FASTCALL cropBack( unsigned int a_length );

	/**

	appends an another buffer

	*/
	void			FFS_FASTCALL append( VsFFSBuffer & a_appendMe, unsigned int a_bytes );


	


	unsigned char * operator * ();
	unsigned char & operator []( int a_index );
	unsigned char & operator []( unsigned int a_index );
	VsFFSBuffer &	operator += ( VsFFSBuffer & a_appendMe );
	VsFFSBuffer &	operator = ( VsFFSBuffer & a_appendMe );
	


private:
	

	McMutex			m_access;

	unsigned char * m_internalBuffer;
	unsigned int	m_size;
	unsigned int	m_realSize;

};
/////////////////////////////////////////////////////////////////////////////



#endif


/// @}
