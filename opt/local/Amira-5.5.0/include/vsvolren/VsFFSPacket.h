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
#ifndef VSFFSPACKET_FILE_H
#define VSFFSPACKET_FILE_H




#include <mclib/McString.h>


#define FFS_MAKEWORD( a, b ) ( (a << 8) | (unsigned char)b )
#define FFS_LOBYTE( a ) ( 0xff & a )
#define FFS_HIBYTE( a ) ( 0xff & (a >> 8) )


#ifdef WIN32
	#define FFS_FASTCALL  __fastcall
#else
	#define FFS_FASTCALL  
#endif





/**

convert a hex number string into a int64

*/
static mcint64 FFS_FASTCALL ffs_hex_to_int64( McString & a_buffer )
{
	mcint64 l_result;
	
#ifdef WIN32
	sscanf( a_buffer.getString(), "%I64x", &l_result );
#else
	sscanf( a_buffer.getString(), "%lx", (long unsigned int*)&l_result );
#endif

	return l_result;
}


/**

convert a int64 into a string

*/
static char * FFS_FASTCALL ffs_int64_to_string( mcint64 a_int, McString & a_buffer )
{
	a_buffer.setInt64( a_int );
	return a_buffer.getString();
}

/**

convert a unsigned int64 into a string

*/
static char * FFS_FASTCALL ffs_int64_to_string( mcuint64 a_int, McString & a_buffer )
{
	a_buffer.setInt64( a_int );
	return a_buffer.getString();
}

/**

convert a int64 into a hex string

*/
static char * FFS_FASTCALL ffs_int64_to_hex( mcint64 a_int, McString & a_buffer )
{
#ifdef WIN32
	a_buffer.printf( "%I64x", a_int );
#else
	a_buffer.printf( "%lx", a_int );
#endif

	return a_buffer.getString();
}

/**

convert a unsigned int64 into a string

*/
static char * FFS_FASTCALL ffs_int64_to_hex( mcuint64 a_int, McString & a_buffer )
{
#ifdef WIN32
	a_buffer.printf( "%I64x", a_int );
#else
	a_buffer.printf( "%lx", a_int );
#endif

	return a_buffer.getString();
}

/////////////////////////////////////////////////////////////////////////////
// Packet header identifier
enum FFS_packet_id
{
	eFFS_connectionInit = 0,
	eFFS_connectionInitResponse,
	eFFS_connect,	
	eFFS_disconnect,
	eFFS_dataRequest,
	eFFS_dataRequestResponse,
	eFFS_dataTransmit,
	eFFS_error,
	eFFS_connectResponse,
	eFFS_dataTransmitEnd,
};
/////////////////////////////////////////////////////////////////////////////




#endif


/// @}
