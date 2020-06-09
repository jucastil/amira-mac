/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOOPENCLCONVOLUTION_H
#define SOOPENCLCONVOLUTION_H

#include <Inventor/SbString.h>

#include <Inventor/STL/vector>

#include <Inventor/OpenCL/algorithms/SoOpenCLAlgorithmsDefs.h>

#include <Inventor/algorithms/SoConvolution.h>

class SoConvolutionHandle;
class SoOpenCLBufferObject;

/**
* @VSGEXT Convolution functions for OpenCL buffers
*
* @ingroup OpenCLAlgorithms
*
* @DESCRIPTION
* This module provides functions to perform convolution on 2D buffers.
*
* Examples:
*
*
*
*
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTOROPENCLALGORITHMS_API  SoOpenCLConvolution : public SoConvolution
{
SoINTERNAL public:
  /** This function init the OpenCL module. */
  static void initClass();

  /** This function unload the OpenCL module and free the data. */
  static void exitClass();

  /** Destructor */
  virtual ~SoOpenCLConvolution();

public:
  /** Constructor */
  SoOpenCLConvolution();

  /**
   * This function performs a 1D convolution on a two dimensional buffer using a 1D kernel.
   * 
   * - The data in the input buffer must contain floats. 
   * - The function puts float values in the output buffer.
   *
   * This convolution is equivalent to a row convolution.
   *
   * @param sourceBufferObject The input float buffer.
   * @param targetBufferObject The output float buffer.
   * @param kernelData The kernel values.
   * @param kernelSize The kernel size.
   * @param width The width of the two dimensional buffer.
   * @param height The height of the two dimensional buffer.
   *
   * @return Returns 0 if there is no error, 1 if one of the buffers is too small.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  virtual int doSeparateConvolution1D( SoBufferObject* sourceBufferObject,
      SoBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

  /**
   * This function performs a 1D convolution on a two dimensional buffer using a 1D kernel. @BR
   * OPENCL buffer version
   *[OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolution1D( SoOpenCLBufferObject* sourceBufferObject,
      SoOpenCLBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

  /**
   * This function performs a 2D convolution on a two dimensional buffer using a 1D kernel.
   * 
   * - The data in the input buffer must contain floats. 
   * - The function puts float values in the output buffer.
   *
   * The 2D convolution performs a row convolution followed by a column convolution 
   * using the same kernel for the two passes.
   *
   * To do a 2D convolution with two different 1D kernels use the row/column 
   * methods doSeparateConvolutionRow() and doSeparateConvolutionColumn().
   *
   * @param sourceBufferObject The input float buffer.
   * @param targetBufferObject The output float buffer.
   * @param kernelData The kernel values.
   * @param kernelSize The kernel size.
   * @param width The width of the two dimensional buffer.
   * @param height The height of the two dimensional buffer.
   *
   * @return Returns 0 if there is no error, 1 if one of the buffers is two small.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  virtual int doSeparateConvolution2D( SoBufferObject* sourceBufferObject,
      SoBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

  /** 
   * This function performs a 2D convolution on a two dimensional buffer using a 1D kernel. @BR
   * OPENCL buffer version
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolution2D( SoOpenCLBufferObject* sourceBufferObject,
      SoOpenCLBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

  /**
   * This function performs a row convolution on a two dimensional buffer using a 1D kernel.
   * 
   * - The data in the input buffer must contain floats. 
   * - The function puts float values in the output buffer.
   *
   * @param sourceBufferObject The input float buffer.
   * @param targetBufferObject The output float buffer.
   * @param kernelData The kernel values.
   * @param kernelSize The kernel size.
   * @param width The width of the two dimensional buffer.
   * @param height The height of the two dimensional buffer.
   *
   * @return Returns 0 if there is no error, 1 if one of the buffers is two small.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  virtual int doSeparateConvolutionRow( SoBufferObject* sourceBufferObject,
      SoBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

  /**
   * This function performs a row convolution on a two dimensional buffer using a 1D kernel. @BR
   * OPENCL buffer version
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolutionRow( SoOpenCLBufferObject* sourceBufferObject,
      SoOpenCLBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

  /**
   * This function performs a column convolution on a two dimensional buffe using a 1D kernel.
   * 
   * - The data in the input buffer must contain floats. 
   * - The function puts float values in the output buffer.
   *
   * @param sourceBufferObject The input float buffer.
   * @param targetBufferObject The output float buffer.
   * @param kernelData The kernel values.
   * @param kernelSize The kernel size.
   * @param width The width of the two dimensional buffer.
   * @param height The height of the two dimensional buffer.
   *
   * @return Returns 0 if there is no error, 1 if one of the buffers is two small.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  virtual int doSeparateConvolutionColumn( SoBufferObject* sourceBufferObject,
      SoBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

  /** 
   * This function performs a column convolution on a two dimensional buffe using a 1D kernel. @BR
   * OPENCL buffer version
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolutionColumn( SoOpenCLBufferObject* sourceBufferObject,
      SoOpenCLBufferObject* targetBufferObject,
      float* kernelData, int kernelSize, int width, int height );

 protected:
  /**
   * This functions sets a kernel for the convolutions.
   */
  void setKernel( int kernelSize, float* data );

  SoConvolutionHandle* createConvolutionHandle();

  void freeConvolutionHandle( SoConvolutionHandle* handle );

 private:

  SoConvolutionHandle* m_convolutionHandle;

};

#endif //SOOPENCLCONVOLUTION_H

