/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_BUFFER_ASYNC_INTERFACE_H_
#define _SO_BUFFER_ASYNC_INTERFACE_H_

#include <Inventor/SbBase.h>
#include <Inventor/devices/SoBufferObject.h>

class SoLDMNodeFrontManager;

/**
* @LDMEXT LDM interface to optimize memory management of tiles .
*
* @ingroup LDMTiles
*
* @DESCRIPTION
* Specialized buffer object classes may implement this interface
* to provide additional information about the contents of the buffer.
*
* @SEE_ALSO
*    SoBufferObject
*    SoCpuBufferCompressed
*    SoCpuBufferUniform
*/
class LDM_API SoBufferAsyncInterface
{
public:

  /** Return TRUE if the data attached to this buffer are not currently available */
  virtual bool isInMemory() = 0;

  /** 
   * Ask to initiate an ansynchronous load of the data if not already in memory.
   *
   * Application must call LDMNodeFrontManager->resourceChangeNotify()
   * In order to let LDM know that some new data are available. 
   */
  virtual void requestRefetch(SoLDMNodeFrontManager* LDMNodeFrontManager, const double weight) = 0;

};

#endif //_SO_BUFFER_ASYNC_INTERFACE_H_
