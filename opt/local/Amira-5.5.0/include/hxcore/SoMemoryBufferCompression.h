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
#ifndef SOMEMORYBUFFERCOMPRESSION_H
#define SOMEMORYBUFFERCOMPRESSION_H

#include <hxcore/HxAmiraWinDLLApi.h>

class SoMemoryBuffer;


class HXCORE_API SoMemoryBufferCompression {
public:
  // define the type of compression available
  typedef enum {
    NONE,
    ZLIB,
    BZIP2,
    PBZIP2
  } CompressionMode;

public:
  // Constructor
  SoMemoryBufferCompression();

  //Destructor
  virtual ~SoMemoryBufferCompression();
  
  // setup the source buffer of the compression with the possibility
  // to limit the compression to a subset of the buffer with offset and size parameter 
  // if size is set to 0 then the buffer size will be taken minus the offset
  virtual void setSource(SoMemoryBuffer *src,const unsigned long offset=0,const unsigned long size=0);

  // setup the destination buffer of the compression with the possibilty to
  // set a destination offset, allowing the user to add specific infoon the header
  virtual void setDestination(SoMemoryBuffer *dst,const unsigned long offset=0);
  
  // apply a compression function on the defined source offset/size 
  // and put the results in destination at offset
  // return the size of the compressed results 
  // or -1 if error
  int compress(const CompressionMode mode);

  // apply uncompress function on the defined source offset/size 
  // and put the results in destination at offset
  // return the size of the compressed results 
  // or -1 if error
  int uncompress(const CompressionMode mode);

private:
  SoMemoryBuffer *m_srcBuf;
  unsigned long m_srcOffset, m_srcSize;
  
  SoMemoryBuffer *m_dstBuf;
  unsigned long m_dstOffset,m_dstSize;

};

#endif // SOMEMORYBUFFERCOMPRESSION_H

/// @}
