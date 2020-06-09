/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUBUFFERASYNCBASICPROPERTY_H
#define SOCPUBUFFERASYNCBASICPROPERTY_H

// LDM include
#include <LDM/tiles/SoCpuBufferBasicProperty.h>
#include <LDM/tiles/SoBufferPropertiesInterface.h>
#include <LDM/tiles/SoBufferAsyncInterface.h>

/**
* @LDMEXT LDM buffer object handling basic LDM tile information and implementing asynchronous buffer interface.
*
* @ingroup LDMTiles
*
* @DESCRIPTION
* This type of buffer represents a standard LDM tile.
*
* @SEE_ALSO
*    SoBufferAsyncInterface, SoBufferPropertiesInterface, SoCpuBufferObject,
*    SoCpuBufferUniform, SoCpuBufferCompressed
*/
class LDM_API SoCpuBufferAsyncBasicProperty: public SoCpuBufferBasicProperty, public SoBufferAsyncInterface
{
  SO_TYPED_CLASS_HEADER();

  // ----------------------- Public usage --------------------------------------
public:

  /** Default constructor. */
  SoCpuBufferAsyncBasicProperty();

  /** Destructor. */
  virtual ~SoCpuBufferAsyncBasicProperty();

  /** Return TRUE if the data attached to this buffer are not currently available */
  virtual bool isInMemory() { return false; }

  /** 
   * Ask to initiate an ansynchronous load of the data if not already in memory.
   *
   * Application must call LDMNodeFrontManager->resourceChangeNotify()
   * In order to let LDM know that some new data are available. 
   */
  virtual void requestRefetch(SoLDMNodeFrontManager* LDMNodeFrontManager, const double weight);
private:

};

#endif //SOCPUBUFFERASYNCBASICPROPERTY_H