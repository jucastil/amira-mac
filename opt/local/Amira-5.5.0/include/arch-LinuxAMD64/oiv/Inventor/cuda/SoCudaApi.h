/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDAAPI_H
#define SOCUDAAPI_H

#include <Inventor/SbBasic.h>

#include <Inventor/cuda/SoCuda.h>

class SoCudaHandle;
class SoCudaBufferObject;

/**
* @VSGEXT CUDA access API
*
* @ingroup CudaDevice
*
* @DESCRIPTION
*
* The SoCudaApi class provides functions to perform specific Cuda operations.
*
* Most of the functions setup SoCudaHandle parameters, like the function arguments,
* block size, etc...
* Those parameters are used when the CUDA function is called.
*
* @USAGE
* You can call the provided functions with a valid handle created by the SoCuda class.
*
*
* @EXAMPLE
*
*  \code
*  // OpenInventor Initialization
*  ...
*
*  SoCuda::init();
*  SoCudaDevice* pMainDevice = SoCudaDevice::findFirstAvailableDevice();
*  if ( pMainDevice ) {
*    SoCudaContext* pContext = new SoCudaContext( pMainDevice );
*    if ( pContext ) {
*      pContext->bind();
*      SoCudaHandle* pHandle = SoCuda::findFunction( "ModuleName", "FunctionName" );
*      if ( pHandle ) {
*        SoCudaApi::resetParameters( pHandle );
*
*        SoCudaApi::setParameter( pHandle, inputCudaBuffer );
*        SoCudaApi::setParameter( pHandle, outputCudaBuffer );
*        SoCudaApi::setParameter( pHandle, inputSize );
*
*        SoCudaApi::launch( pHandle, inputSize / 64, 1 );
*        SoCudaApi::freeHandle( pHandle );
*      }
*      pContext->unbind();
*    }
*  }
*  SoCuda::finish();
*  \endcode
*
* @SEE_ALSO
*
*   SoCuda, SoCudaContext, SoCudaDevice, SoCudaBufferObject
*
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
*
*/

class INVENTORCUDA_API SoCudaApi
{

public:

  /**
   * This function adds a SoCudaBufferObject parameter to the list of parameters sent to 
   * the kernel by launch function.
   *
   * @param handle The function CUDA handle.
   * @param pointer The pointer to add to the parameters stack.
   *
   * @return Operation result error code.
   * [OIV-WRAPPER-ARG IN,POINTER_VALUE]
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, SoCudaBufferObject* pointer );

  /**
   * This function specifies the thread blocks shape.
   *
   * See SoCudaDevice to know the max block size for a specific device.
   *
   * @param handle The Cuda handle of the function to set the block size for.
   * @param x X dimension of the the thread blocks.
   * @param y Y dimension of the the thread blocks.
   * @param z Z dimension of the the thread blocks.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setBlockShape( SoCudaHandle* handle, int x, int y, int z );


  /**
   * This function sets the size of the shared memory allocated for each thread block when
   * the kernel is launched.
   *
   * See SoCudaDevice to know the max size for a specific device.
   *
   * @param handle The Cuda handle of the function for which we setup the block size.
   * @param size The size in bytes.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setSharedMemorySize( SoCudaHandle* handle, int size );


  /**
   * This function adds a pointer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param pointer The pointer to add to the parameters stack.
   *
   * @return Operation result error code.
   * [OIV-WRAPPER-ARG IN,POINTER_VALUE]
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, const void* pointer );

  /**
   * This function adds a char parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, char value );


  /**
   * This function adds an unsigned char parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, unsigned char value );

  /**
   * This function adds a short parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, short value );

  /**
   * This function adds an unsigned short parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, unsigned short value );

  /**
   * This function adds a long parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, long value );

  /**
   * This function adds an unsigned integer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, unsigned long value );

  /**
   * This function adds an integer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, int value );

  /**
   * This function adds an unsigned integer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, unsigned int value );

  /**
   * This function adds a float parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, float value );

  /**
   * This function adds a double parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function CUDA handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError setParameter( SoCudaHandle* handle, double value );

  /**
   * This function resets the internal list of parameters for the specific list. @BR
   * This function should be called before each launch in order to reset the parameters,
   * then the setParameter* function can be called to update the parameters.
   *
   * @param handle The function CUDA handle.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError resetParameters( SoCudaHandle* handle );

  /**
   * Launch the specified kernel function.
   *
   * @param handle  The handle of the function to launch.
   * @param gridWidth The grid width.
   * @param gridHeight The grid height.
   *
   * @return Operation result error code.
   */
  static SoCuda::SoCudaError launch( SoCudaHandle* handle, int gridWidth, int gridHeight );


SoINTERNAL public:


  /**
   * This function creates a CUDA handle and returns it.
   *
   * @return Returns a new CUDA handle.
   */
  static SoCudaHandle* createHandle();

  /**
   * This function frees a CUDA handle allocated by the createHandle() function.
   *
   * @param handle The handle to free.
   */
  static void freeHandle( SoCudaHandle* handle );


  static SoCuda::SoCudaError loadFunction( SoCudaHandle* handle, const SbString& filename, const SbString& functionName );

  static SoCuda::SoCudaError findFunction( SoCudaHandle* handle, const void* moduleData, const SbString& functionName );

private:
  template<typename T> static int alignParameter(int baseOffset);
  template<typename T> static SoCuda::SoCudaError setCudaParameter( SoCudaHandle* handle, T value );
};

#endif // SOCUDAAPI_H
