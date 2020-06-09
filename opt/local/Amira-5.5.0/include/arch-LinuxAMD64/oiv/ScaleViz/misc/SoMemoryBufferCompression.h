/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (MMM yyyy)
**=======================================================================*/


#ifndef SO_MEMORY_BUFFER_COMPRESSION_H
#define SO_MEMORY_BUFFER_COMPRESSION_H

#include <ScaleViz/SoScaleViz.h>

class SoMemoryBuffer;

SoEXTENDER class SCALEVIZ_API SoMemoryBufferCompression
{

public:
  // define the type of compression available
  typedef enum {
    /* No compression */
    NONE,
    /* Zip through zlib compression */
    ZLIB,
    /* bzip compression */
    BZIP2,
    /* per component bzip compression */
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
  SoMemoryBuffer* m_srcBuf;
  unsigned long m_srcOffset, m_srcSize;
  
  SoMemoryBuffer* m_dstBuf;
  unsigned long m_dstOffset, m_dstSize;

};

#endif // SO_MEMORY_BUFFER_COMPRESSION_H

/**/
