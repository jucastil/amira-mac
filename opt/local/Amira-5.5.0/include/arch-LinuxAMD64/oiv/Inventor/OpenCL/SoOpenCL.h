/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SoOpenCL_H
#define SoOpenCL_H

#include <Inventor/SbString.h>
#include <Inventor/STL/vector>
#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/OpenCL/SoOpenCLDefs.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoOpenCL,__INVOPENCLDLL)

class SoOpenCLHandle;

/**
* @VSGEXT OpenCL module API
*
* @ingroup OpenCLDevice
*
* @DESCRIPTION
*
* The Inventor OpenCL module provides a set of useful functions for OpenCL development
* including memory managment, module handling and device managment functions.
*
* - Memory managment is provided by the SoOpenCLBufferObject class.
* - Module handling is included in the SoOpenCL class.
* - Device managment functions are provided by the classes SoOpenCLContext and SoOpenCLDevice.
*
* This module also provides built-in OpenCL functions to quickly integrate in your application
* the OpenCL functions useful to improve your computing performences.
*
* The integrated modules are organized in different topics:
* - Conversion
* - Volumes
* - ....
*
* @USAGE
*  After the initialization of OpenInventor the OpenCL module must be initialized using the init function.
*  Before exiting the application the finish function must be called, in order to free all the memory 
*  allocated by the module.
*
* @NOTES
* After the initialization of the OpenCL module there is no default OpenCLContext, so don't forget to create 
* an OpenCL context before performing any OpenCL operation. See the class SoOpenCLContext for more information.
*
* @EXAMPLE
*    This example shows how to call a specific OpenCL function.
*
* \code
*  // OpenInventor Initialization
*  ...
*
*  SoOpenCL::init();
*
*  SoOpenCLDevice* mainDevice = SoOpenCLDevice::findFirstAvailableDevice();
*
*  SoOpenCLContext* context = new SoOpenCLContext( mainDevice );
*
*  context->bind();
*  {
*    SoOpenCLHandle* handle = SoOpenCL::findFunction( "ModuleName", "FunctionName" );
*
*    if ( handle ) {
*      SoOpenCLApi::launch( handle, 10, 1 );
*      SoOpenCLApi::freeHandle( handle );
*    }
*  }
*  context->unbind();
*
*  SoOpenCL::finish();
*  \endcode
*
* @SEE_ALSO
*
*   SoOpenCLApi,
*   SoOpenCLContext,
*   SoOpenCLDevice,
*   SoOpenCLBufferObject,
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTOROPENCL_API  SoOpenCL
{
public:

  /**
   * This enum defines the possible errors returned by the OpenCL API
   */
  enum SoOpenCLError
  {
    /**  No error, the operation is a success. */
    SO_OPENCL_SUCCESS,

    /** Error: The specified module cannot be loaded. */
    SO_OPENCL_MODULE_LOAD_ERROR,

    /** Error: The specified function cannot be loaded. */
    SO_OPENCL_MODULE_FUNCTION_ERROR,

    /** Error: One of the specified paramaters is invalid. */
    SO_OPENCL_INVALID_PARAMETER,

    /**
     * This error indicates that there is no valid OpenCL context to perform the requested operation. @BR
     * See the SoOpenCLContext class to create a OpenCL context.
     */
    SO_OPENCL_INVALID_CONTEXT
  };


  /**
   * Initialize the OpenCL module.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

  /**
   * Unload the OpenCL module and free the data.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * This function indicates if OpenCL is available on this platform.
   *
   * @returns True if at least one OpenCL enabled device is available in the system.
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
  static SoOpenCLError loadSourceModule( const SbString& filename, const SbString& moduleName );

  /**
   * This function resolves a specific function in a specified module.
   *
   * @param moduleName The name of the module which is supposed to contain the function.
   * @param functionName The name of the function to resolve.
   *
   * @return A OpenCL handle on the function, or NULL if the function was not found!
   */
  static SoOpenCLHandle* findFunction( const SbString& moduleName, const SbString& functionName );


  /**
   * This function resolves a specific function in a specified module.
   *
   * @param handle The handle which is updated with the function pointer.
   * @param moduleName The name of the module which is supposed to contain the function.
   * @param functionName The name of the function to resolve.
   *
   * @return An error code.
   */
   static SoOpenCLError findFunction( SoOpenCLHandle* handle, const SbString& moduleName,
                                    const SbString& functionName );

SoINTERNAL public:

  /** Defines a OpenCL module. */
 struct SoOpenCLModule
  {
    /** The module name */
    SbString name;

    /** The list of functions included in this module */
    std::vector< SbString > functions;

    /** Pointer to the data which contains the nvcc output */
    void* data;

    /** Indicates if the data variable was allocated, so when we free the memory we free or not this buffer. */
    bool allocated;
  };

  /**
   * This function registers a module in the list of modules.
   *
   * @param module The SoOpenCLModule to store in the list of modules.
   */
  static void registerModule( SoOpenCLModule* module );

  /**
   * This function parses the nvcc output file in order to build a list of functions
   * provided by this module.
   *
   * @param module The module info structure which contains the list of found functions.
   * @param buffer The module buffer which contains the output of nvcc.
   */
  static void extractFunctionNames( SoOpenCLModule* module, const char* buffer );
  static void declareModule(const SbString& moduleName, const char* codeStr, bool isAllocated );

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

#endif //SoOpenCL_H

