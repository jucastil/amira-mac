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

/// @addtogroup mclib mclib
/// @{
#ifndef MCCODER_H
#define MCCODER_H

#include "McWinDLLApi.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "McPrimType.h"

// typedef a 32 bit type
// typedef unsigned int mcuint32;

/* Data structure for MD5 (Message Digest) computation */
struct MD5_CTX
{
  mcuint32      i[2];       /* number of _bits_ handled mod 2^64 */
  mcuint32      buf[4];     /* scratch buffer */
  unsigned char in[64];     /* input buffer */
  unsigned char digest[16]; /* actual digest after MD5Final call */
};

/** This class provides methods for converting between binary data and
    ASCII strings (uuencode) as well as computing checksums (CRC). */

class MCLIB_API McCoder {

public:
    //char* uuencode(const char* input, int len);
    //char* uudecode(const char* input, int len);

    /** Encode @c len bytes of data into a string containing only letters
	[A-Z], result is returned, and must be @c freed by the
	caller. For convenience a 0-character is added to the end,
	which is not counted by outlen.*/
    static char* abcEncode(const unsigned char* input, int len, int& outlen) {
	outlen = len*2;
	char* result = (char*) malloc(outlen+1);
	for (int i=0 ; i<len ; i++) {
	    result[2*i]   = (input[i] >> 4) + 'A';
	    result[2*i+1] = (input[i] &0xf) + 'A';
	}
	result[outlen]=0;
	return result;
    }

    /** Decode @c len bytes of data previously encoded by abcEncode result is
	returned, and must be @c freed by the caller. For convenience a
	0-character is added to the end, which is not counted by
	outlen.*/
    static unsigned char* abcDecode(const char* input, int len, int& outlen) {
	outlen = len/2;
	unsigned char* result = (unsigned char*) malloc(outlen+1);
	for (int i=0 ; i<outlen ; i++) {
	    int c1 = input[2*i];
	    int c2 = input[2*i+1];
	    if (c1>='a') c1-='a'; else c1-='A';
	    if (c2>='a') c2-='a'; else c2-='A';
	    result[i]   = (c1 << 4) | c2;
	}
	result[outlen]=0;
	return result;
    }
    /** Compute a POSIX 1003,2 checksum from @c len bytes.*/
    static unsigned int crc(const unsigned char* input, int len);


    /** Init MD5 checksum computation. */
    void crcMD5Init();
    /** Append the next buffer to the MD5 checksum. */
    void crcMD5Update( const unsigned char * inInput, int inLen );
    /** Finalize the MD5 checksum computation. */
    void crcMD5Final();
    /** Get the MD5 checksum */
    void crcMD5Query( unsigned char outCrc[16] );

private:

    MD5_CTX _md5;
};

#endif

/// @}
