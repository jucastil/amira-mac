/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDA_H
#define SOCUDA_H

#include <Inventor/SbString.h>
#include <Inventor/STL/vector>
#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/cuda/SoCudaDefs.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoCuda,__INVCUDADLL)

class SoCudaHandle;

/**
* @VSGEXT Cuda module class
*
* @ingroup CudaDevice
*
* @DESCRIPTION
*
* The Open Inventor CUDA module provides a set of useful functions for CUDA development
* including memory management, module handling and device management functions.
*
* - Memory management is provided by the SoCudaBufferObject class.
* - Module handling is included in the SoCuda class.
* - Device management functions are provided by the classes SoCudaContext and SoCudaDevice.
*
* This module also provides built-in CUDA functions to quickly integrate in your application
* the CUDA functions useful to improve your computing performences.
*
* The integrated modules are organized in different topics:
* - Conversion
* - Volumes
* - ....
*
* @USAGE
*  After the initialization of OpenInventor the CUDA module must be initialized using the init function.
*  Before exiting the application the finish function must be called, in order to free all the memory 
*  allocated by the module.
*
* @NOTES
* After the initialization of the CUDA module there is no default CudaContext, so don't forget to create 
* a CUDA context before performing any CUDA operation. See the class SoCudaContext for more information.
*
* @EXAMPLE
*    This example shows how to call a specific CUDA function.
*
* \code
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
*        SoCudaApi::launch( pHandle, 10, 1 );
*        SoCudaApi::freeHandle( pHandle );
*      }
*      pContext->unbind();
*    }
*  }
*  SoCuda::finish();
*  \endcode
*
* @SEE_ALSO
*   SoCudaApi, SoCudaContext, SoCudaDevice, SoCudaBufferObject,
*   SoCudaArithmetic, SoCudaConversion, SoCudaConvolution, SoCudaSeismic
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTORCUDA_API  SoCuda
{
public:

  /**
   * This enum defines the possible errors returned by the Cuda API
   */
  enum SoCudaError
  {
    /**  No error, the operation is a success. */
    SO_CUDA_SUCCESS,

    /** Error: The specified module cannot be loaded. */
    SO_CUDA_MODULE_LOAD_ERROR,

    /** Error: The specified function cannot be loaded. */
    SO_CUDA_MODULE_FUNCTION_ERROR,

    /** Error: One of the specified paramaters is invalid. */
    SO_CUDA_INVALID_PARAMETER,

    /**
     * This error indicates that there is no valid CUDA context to perform the requested operation. @BR
     * See the SoCudaContext class to create a CUDA context.
     */
    SO_CUDA_INVALID_CONTEXT
  };


  /**
   * Initialize the CUDA module.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

  /**
   * Unload the CUDA module and free the data.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * This function indicates if CUDA is available on this platform.
   *
   * @returns True if at least one CUDA enabled device is available in the system.
   */
  static SbBool isAvailable();

  /**
   * This function loads a cubin file and register it in the list of modules.
   *
   * @param filename The cubin filename.
   * @param moduleName The name of the module linked to the file.
   *
   * @return An error code is returned on error, 0 means no error.
   */
  static SoCudaError loadBinaryModule( const SbString& filename, const SbString& moduleName );

  /**
   * This function loads a cubin from the specified buffer and register it in the list of modules.
   *
   * @param moduleData The cubin buffer.
   * @param dataSize The size in  bytes of the cubin buffer.
   * @param moduleName The name of the module linked to the file.
   *
   * @return An error code is returned on error, 0 means no error.
   */
  static SoCudaError loadBinaryModule( const void* moduleData, size_t dataSize, const SbString& moduleName );

  /**
   * This function resolves a specific function in a specified module.
   *
   * @param moduleName The name of the module which is supposed to contain the function.
   * @param functionName The name of the function to resolve.
   *
   * @return A CUDA handle on the function, or NULL if the function was not found!
   */
  static SoCudaHandle* findFunction( const SbString& moduleName, const SbString& functionName );


  /**
   * This function resolves a specific function in a specified module.
   *
   * @param handle The handle which is updated with the function pointer.
   * @param moduleName The name of the module which is supposed to contain the function.
   * @param functionName The name of the function to resolve.
   *
   * @return An error code.
   */
   static SoCudaError findFunction( SoCudaHandle* handle, const SbString& moduleName,
                                    const SbString& functionName );

SoINTERNAL public:

  /** Defines a CUDA module. */
 struct SoCudaModule
  {
    /** The module name */
    SbString name;

    /** Pointer to the data which contains the nvcc output */
    void* data;

    /** Indicates if the data variable was allocated, so when we free the memory we free or not this buffer. */
    bool allocated;
  };

  /**
   * This function registers a module in the list of modules.
   *
   * @param module The SoCudaModule to store in the list of modules.
   */
  static void registerModule( SoCudaModule* module );

  static void declareModule(const SbString& moduleName, const unsigned char* codeStr, bool isAllocated );

  /**
   * This function removes a module declared using the declareModule function.
   *
   * @param moduleName The name of the module to remove.
   */
  static void removeModule( const SbString& moduleName );

  /**
   * This function initializes the OpenGL interop.
   */
  static void initGLInterop();

private:

  static SbThreadMutex s_initThreadMutex;

  static int s_initRefCount;

  static bool s_glOpInitialized;
};

#endif //SOCUDA_H

