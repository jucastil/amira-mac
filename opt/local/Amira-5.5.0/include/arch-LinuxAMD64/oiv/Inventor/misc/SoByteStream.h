/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_BYTE_STREAM_
#define  _SO_BYTE_STREAM_

#include <Inventor/SbBasic.h>

class SoNode;
class SoPath;
class SoPathList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoByteStream
//
//  This class creates a byte stream representation of a scene graph,
//  using the SoWriteAction to write to an in memory buffer. Byte streams
//  are commonly used to transfer data, for instance during copy and paste.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Converts scene graph objects to character byte streams.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *   This class creates a byte stream representation of a scene graph, using an
 *   SoWriteAction to write path lists to an in-memory buffer. Byte streams are
 *   commonly used to transfer data in copy and paste operations. (The SoWinClipboard
 *   class passes SoByteStream data during copy and paste.)
 * 
 * @SEE_ALSO
 *    SoWinClipboard
 * 
 * 
 */ 

class INVENTOR_API SoByteStream {
 public:
  /**
   * Constructor.
   */
  SoByteStream();
  /**
   * Destructor.
   */
  ~SoByteStream();

  /**
   * Converts the passed scene graph object(s) into a byte stream. 
   * The object(s) are passed by node. The caller
   * may specify whether the byte stream is written in binary (TRUE) or ASCII (FALSE)
   * format.
   * The converted data can be accessed through getData() and getNumBytes().
   */
  void                convert(SoNode *node, SbBool binaryFormat = TRUE);
    
  /**
   * Converts the passed scene graph object(s) into a byte stream. 
   * The object(s) are passed by path. The caller
   * may specify whether the byte stream is written in binary (TRUE) or ASCII (FALSE)
   * format.
   * The converted data can be accessed through getData() and getNumBytes().
   */
  void                convert(SoPath *path, SbBool binaryFormat = TRUE);
    
  /**
   * Converts the passed scene graph object(s) into a byte stream.
   * The object(s) are passed by pathList. The caller
   * may specify whether the byte stream is written in binary (TRUE) or ASCII (FALSE)
   * format.
   * The converted data can be accessed through getData() and getNumBytes().
   */
  void                convert(SoPathList *pathList, SbBool binaryFormat = TRUE);

  /**
   * Returns the data from the last convert()
   * operation. This byte stream format is well suited to data transfers, like copy
   * and paste.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNumBytes()}]
   */
  void *              getData()       { return data; }
  /**
   * Returns the number of bytes from the last convert()
   * operation. This byte stream format is well suited to data transfers, like copy
   * and paste.
   * [OIV-WRAPPER-HIDDEN-FROM-DOC]
   */
  size_t/*uint32_t*/                  getNumBytes()   { return numBytes; }
    
  // Unconvert a byte stream back to a path list.
  // This static routine performs an SoDB::read on the data,
  // and returns a path list of the paths read in.
    
  /**
   * Takes byte stream data and unconverts it back to scene graph objects. The
   * objects are returned in a path list.
   */
  static SoPathList *unconvert(SoByteStream *byteStream);
  /**
   * Takes byte stream data and unconverts it back to scene graph objects. The
   * objects are returned in a path list.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static SoPathList *unconvert(void *data, size_t numBytes);
  
 SoEXTENDER public:
  // This allows apps to store raw data here without converting 
  // an Inventor node, path, or path list. This sets isRaw to TRUE,
  // and that data cannot be unconverted.
  void                copy(void *d, size_t len);
  SbBool              isRawData() const { return isRaw; }
     
 private:
  void                *data;
  size_t numBytes;
  SbBool              isRaw;

};

#endif // _SO_BYTE_STREAM_

