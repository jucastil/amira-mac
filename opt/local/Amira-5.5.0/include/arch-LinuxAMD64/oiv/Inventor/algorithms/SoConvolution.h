/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCONVOLUTION_H
#define SOCONVOLUTION_H

#include <Inventor/sys/port.h>

#include <Inventor/SbDataType.h>

#include <Inventor/algorithms/SoAlgorithmsDefs.h>

class SoBufferObject;
class SoCpuBufferObject;

/**
* @VSGEXT Convolution functions for buffers
*
* @ingroup CpuAlgorithms
*
* @DESCRIPTION
*
* This module provides functions to perform convolution on 2D buffers.
*
* Examples:
* 
* @SEE_ALSO
*   SoAlgorithms, SoArithmetic, SoConversion, SoDataExtract, SoSeismic
*
*/

class INVENTORALGORITHMS_API  SoConvolution
{
SoINTERNAL public:
  /** SoConvolution destructor */
  virtual ~SoConvolution();

  /** Static initClass function to initialize the convolution module. */
  static void initClass();

  /** Static exitClass function to free the memory allocated by the conversion module. */
  static void exitClass();

public:
  /** SoConvolution constructor */
  SoConvolution();

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
                                       float* kernelData, int kernelSize, 
                                       int width, int height );


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
                                       float* kernelData, int kernelSize, 
                                       int width, int height );


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
                                        float* kernelData, int kernelSize, 
                                        int width, int height );


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
                                           float* kernelData, int kernelSize, 
                                           int width, int height );


  /**
   * Fast version for CPU buffers.
   * @BR
   * The general version maps the user buffers to CPU buffers and calls this function
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  int doSeparateConvolution1D( SoCpuBufferObject* sourceBufferObject, 
                               SoCpuBufferObject* targetBufferObject, 
                               float* kernelData, int kernelSize, 
                               int width, int height );


  /**
   * Fast version for CPU buffers.
   * @BR
   * The general version maps the user buffers to CPU buffers and calls this function
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  int doSeparateConvolution2D( SoCpuBufferObject* sourceBufferObject, 
                               SoCpuBufferObject* targetBufferObject, 
                               float* kernelData, int kernelSize, 
                               int width, int height );


  /**
   * Fast version for CPU buffers.
   * @BR
   * The general version maps the user buffers to CPU buffers and calls this function
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  int doSeparateConvolutionRow( SoCpuBufferObject* sourceBufferObject, 
                                SoCpuBufferObject* targetBufferObject, 
                                float* kernelData, int kernelSize, 
                                int width, int height );


  /**
   * Fast version for CPU buffers.
   * @BR
   * The general version maps the user buffers to CPU buffers and calls this function
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,NO_WRAP{(kernelData != nullptr? kernelData->Length: 0)},IN,IN]
   */
  int doSeparateConvolutionColumn( SoCpuBufferObject* sourceBufferObject, 
                                   SoCpuBufferObject* targetBufferObject, 
                                   float* kernelData, int kernelSize, 
                                   int width, int height );


};

#endif //SOCONVOLUTION_H

