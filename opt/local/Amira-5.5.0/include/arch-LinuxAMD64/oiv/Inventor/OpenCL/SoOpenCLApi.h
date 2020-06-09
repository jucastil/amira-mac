/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined _SO_OPENCL_API_H_
#define _SO_OPENCL_API_H_

#include <Inventor/SbBasic.h>
#include <Inventor/SbVec.h>
#include <Inventor/OpenCL/SoOpenCL.h>

class SoOpenCLHandle;

/**
* @VSGEXT OpenCL access API
*
* @ingroup OpenCLDevice
*
* @DESCRIPTION
*
* The SoOpenCLApi class provides functions to perform specific OpenCL operations.
*
* Most of the functions setup SoOpenCLHandle parameters, like the function arguments,
* block size, etc.
* Those parameters are used when the OpenCL function is called.
*
* @USAGE
* You can call the provided functions with a valid handle created by the SoOpenCL class.
*
* @EXAMPLE
*
* \code
*  SoOpenCL::init();
*  SoOpenCLDevice*  mainDevice = SoOpenCLDevice::findFirstAvailableDevice();
*  SoOpenCLContext* context    = new SoOpenCLContext( mainDevice );
*  context->bind();
*  SoOpenCLHandle* handle = SoOpenCL::findFunction( "ModuleName", "FunctionName" );
*  if ( handle ) {
*    SoOpenCLApi::resetParameters( handle );
*    SoOpenCLApi::setParameter( handle, (unsigned int)input );
*    SoOpenCLApi::setParameter( handle, (unsigned int)output );
*    SoOpenCLApi::setParameter( handle, (size_t)inputSize );
*
*    SoOpenCLApi::launch( handle, inputSize / 64, 1 );
*    SoOpenCLApi::freeHandle( handle );
*  }
*  context->unbind();
*  SoOpenCL::finish();
* \endcode
*
* @SEE_ALSO
*
*   SoOpenCL,
*   SoOpenCLContext,
*   SoOpenCLDevice,
*   SoOpenCLBufferObject,
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTOROPENCL_API SoOpenCLApi
{

public:

  /**
   * This function adds a pointer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param pointer The pointer to add to the parameters stack.
   *
   * @return Operation result error code.
   * [OIV-WRAPPER-ARG IN,POINTER_VALUE]
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, const void* pointer );

  /**
   * This function adds a char parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, char value );


  /**
   * This function adds an unsigned char parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, unsigned char value );

  /**
   * This function adds a short parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, short value );

  /**
   * This function adds an unsigned short parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, unsigned short value );

  /**
   * This function adds a long parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, long value );

  /**
   * This function adds an unsigned integer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, unsigned long value );

  /**
   * This function adds an integer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, int value );

  /**
   * This function adds an unsigned integer parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, unsigned int value );

  /**
   * This function adds a float parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, float value );

  /**
   * This function adds a double parameter to the list of parameters sent to the kernel
   * by launch function.
   *
   * @param handle The function OPENCL handle.
   * @param value The value to add to the parameters stack.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError setParameter( SoOpenCLHandle* handle, double value );

  /**
   * This function resets the internal list of parameters for the specific list. @BR
   * This function should be called before each launch in order to reset the parameters,
   * then the setParameter* function can be called to update the parameters.
   *
   * @param handle The function OPENCL handle.
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError resetParameters( SoOpenCLHandle* handle );

  /**
   * Launch the specified kernel function.
   *
   * @param handle  The handle of the function to launch.
   * @param globalWorkSize The group work size.
   * @param localWorkSize The group item work size.
   *
   *
   * @return Operation result error code.
   */
  static SoOpenCL::SoOpenCLError launch( 
    SoOpenCLHandle* handle, 
    const SbVec3i32& globalWorkSize, 
    const SbVec3i32& localWorkSize
    );


SoINTERNAL public:


  /**
   * This function creates a OPENCL handle and returns it.
   *
   * @return Returns a new OPENCL handle.
   */
  static SoOpenCLHandle* createHandle();

  /**
   * This function frees a OPENCL handle allocated by the createHandle() function.
   *
   * @param handle The handle to free.
   */
  static void freeHandle( SoOpenCLHandle* handle );


  static SoOpenCL::SoOpenCLError loadFunction( SoOpenCLHandle* handle, const SbString& filename, const SbString& functionName );

  static SoOpenCL::SoOpenCLError findFunction( SoOpenCLHandle* handle, const void* moduleData, const SbString& functionName );

private:
  template<typename T> static SoOpenCL::SoOpenCLError setOpenCLParameter( SoOpenCLHandle* handle, T value );
};

#endif // _SO_OPENCL_API_H_
