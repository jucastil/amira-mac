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
#ifndef CLASS_VsFFSInfoFile_H
#define CLASS_VsFFSInfoFile_H

#include <stdio.h>
#include <mclib/McString.h>
#include <mclib/McStringTokenizer.h>
#include <mclib/McPrimType.h>
#include <vsvolren/VsFFSPacket.h>


#define SERVER_INFO_FILE "FFServer.dat"



class VsFFSInfoFile
{

public:


	VsFFSInfoFile( char * a_path = NULL );


	void clear();



	/**

	load a config file

	*/
	bool FFS_FASTCALL loadFile( char * a_file );


	/**

	save settings in a config file

	*/
	bool FFS_FASTCALL saveFile( char * a_file );



	/**

	set a new server key

	*/
	void FFS_FASTCALL setServerKey( mcuint64 & a_serverKey );


	/**

	get the actual Server key 

	*/
	void FFS_FASTCALL getServerKey( mcuint64 & a_serverKey );


	/**

	set a new Server port

	*/
	void		FFS_FASTCALL 	setServerPort( unsigned short a_serverPort );


	/**

	get the actual Server port

	*/
	unsigned short	getServerPort();


	/**

	get an ip

	*/
	unsigned int	FFS_FASTCALL getIp( unsigned int a_index );


	/**

	get number of ips

	*/
	unsigned int	getIpCount();

	/**

	adds a ip in numeric integer form

	*/
	void			FFS_FASTCALL addIp( unsigned int a_ip );

	/**

	adds a ip

	"a.b.c.d"  or  "bla.mc.com"

	*/
	void			FFS_FASTCALL addIp( char * a_ip );

private: 



	//////////////////////////////////////////////////////////////////////////////////
	unsigned short			m_version,
							m_port;
	mcint64					m_serverKey;
	McDArray<unsigned int>	m_ipAdresses;	
	//////////////////////////////////////////////////////////////////////////////////







	/**
	@c handle a line in the config file 
	*/
	bool FFS_FASTCALL handleConfigEntry( char * a_entry );



	/**
	@c parse the file
	*/
	bool FFS_FASTCALL parseFile( char * a_file );


};


#endif








/// @}
