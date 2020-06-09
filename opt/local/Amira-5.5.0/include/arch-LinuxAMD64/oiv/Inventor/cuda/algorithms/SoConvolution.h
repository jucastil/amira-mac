/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDACONVOLUTION_H
#define SOCUDACONVOLUTION_H

#include <Inventor/SbString.h>

#include <Inventor/STL/vector>

#include <Inventor/cuda/algorithms/SoCudaAlgorithmsDefs.h>

#include <Inventor/algorithms/SoConvolution.h>

class SoConvolutionHandle;
class SoCudaBufferObject;

/**
* @VSGEXT Convolution functions for CUDA buffers
*
* @ingroup CudaAlgorithms
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

class INVENTORCUDAALGORITHMS_API  SoCudaConvolution : public SoConvolution
{
SoINTERNAL public:
  /** This function init the Cuda module. */
  static void initClass();

  /** This function unload the Cuda module and free the data. */
  static void exitClass();

  /** Destructor */
  virtual ~SoCudaConvolution();

public:
  /** Constructor */
  SoCudaConvolution();

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
   * CUDA buffer version
   *[OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolution1D( SoCudaBufferObject* sourceBufferObject,
      SoCudaBufferObject* targetBufferObject,
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
   * CUDA buffer version
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolution2D( SoCudaBufferObject* sourceBufferObject,
      SoCudaBufferObject* targetBufferObject,
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
   * CUDA buffer version
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolutionRow( SoCudaBufferObject* sourceBufferObject,
      SoCudaBufferObject* targetBufferObject,
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
   * CUDA buffer version
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN] 
   */
  int doSeparateConvolutionColumn( SoCudaBufferObject* sourceBufferObject,
      SoCudaBufferObject* targetBufferObject,
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

#endif //SOCUDACONVOLUTION_H
