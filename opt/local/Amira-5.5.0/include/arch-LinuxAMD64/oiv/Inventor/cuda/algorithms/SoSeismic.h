/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDASEISMIC_H
#define SOCUDASEISMIC_H

#include <Inventor/SbString.h>

#include <Inventor/STL/vector>

#include <Inventor/algorithms/SoSeismic.h>
#include <Inventor/cuda/algorithms/SoCudaAlgorithmsDefs.h>

class SoBufferObject;
class SoCudaBufferObject;
class SoCudaHandle;
class SoCudaConvolution;

/**
* @VSGEXT Seismic attribute functions for CUDA buffers
*
* @ingroup CudaAlgorithms
*
* @DESCRIPTION
* The Seismic module provides functions for computing seismic attributes.
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

class INVENTORCUDAALGORITHMS_API  SoCudaSeismic : public SoSeismic
{
SoINTERNAL public:
  /** This function init the Cuda module. */
  static void initClass();

  /** This function unload the Cuda module and free the data. */
  static void exitClass();

  /** Destructor */
  virtual ~SoCudaSeismic();

public:
  /** Constructor. */
  SoCudaSeismic();

  /**
   * Compute instantaneous phase attribute on a set of seismic traces. @BR
   *  phase(t) = arctan( im(t)/re(t))
   *
   * - Reimplements the SoSeismic version to check if input and output buffers are both of type 
   *   SoCudaBufferObject. If yes, then CUDA optimized version is used, else the CPU version is used.
   * - Data stored in buffers must be of type float.
   *
   * @param	sourceBufferObject Should contain the real part of the complex trace (original trace data).
   * @param targetBufferObject should contain the imaginary part of the complex trace (Hilbert transform of trace data). @BR
   *        @B Note: @b	targetBufferObject will be overwritten with the result values.
   * @param traceSize Number of samples in each trace (must be same for all traces).
   * @param numTrace  Number of traces.
   */
  virtual int computeInstPhase( SoBufferObject* sourceBufferObject, SoBufferObject* targetBufferObject,
                                    int traceSize, int numTrace );

  /**
   * Compute envelope (amplitude) attribute on a set of seismic traces. @BR
   *  amp(t) = sqrt( re^2(t) + im^2(t))
   *
   * - Reimplements the SoSeismic version to check if input and output buffers are both of type 
   *   SoCudaBufferObject. If yes, then CUDA optimized version is used, else the CPU version is used.
   * - Data stored in buffers must be of type float.
   *
   * @param	sourceBufferObject Should contain the real part of the complex trace (original trace data).
   * @param targetBufferObject should contain the imaginary part of the complex trace (Hilbert transform of trace data). @BR
   *        @B Note: @b	targetBufferObject will be overwritten with the result values.
   * @param traceSize Number of samples in each trace (must be same for all traces).
   * @param numTrace  Number of traces.
   */
  virtual int computeEnvelope( SoBufferObject* sourceBufferObject, SoBufferObject* targetBufferObject,
                                   int traceSize, int numTrace );

  /**
   * Compute Hilbert transform on a set of seismic traces. @BR
   * The Hilbert transform is computed by convolving sourceBufferObject with a
   * windowed (approximate) version of the ideal Hilbert transformer.
   * @BR
   * - Reimplements the SoSeismic version to check if input and output buffers are both of type 
   *   SoCudaBufferObject. If yes, then CUDA optimized version is used, else the CPU version is used.
   * - Data stored in buffers must be of type float.
   */
  virtual int computeHilbert( SoBufferObject* sourceBufferObject, SoBufferObject* targetBufferObject,
                                    int width, int height );

  /**
   * Compute instantaneous phase attribute on a set of seismic traces. @BR
   * CUDA optimized version.
   * - This function handles SoCudaBufferObject input output type only.
   * - Data stored in buffers must be of type float.
   */
  int computeInstPhase( SoCudaBufferObject* sourceBufferObject, SoCudaBufferObject* targetBufferObject,
                                    int traceSize, int numTrace );

  /**
   * Compute envelope (amplitude) attribute on a set of seismic traces. @BR
   * CUDA optimized version.
   * - This function handles SoCudaBufferObject input output type only.
   * - Data stored in buffers must be of type float.
   */
  int computeEnvelope( SoCudaBufferObject* sourceBufferObject, SoCudaBufferObject* targetBufferObject,
                                   int traceSize, int numTrace );

  /**
   * Compute Hilbert transform on a set of seismic traces. @BR
   * CUDA optimized version.
   * - This function handles SoCudaBufferObject input output type only.
   * - Data stored in buffers must be of type float.
   */
  int computeHilbert( SoCudaBufferObject* sourceBufferObject, SoCudaBufferObject* targetBufferObject,
                                    int width, int height );

private:

  /**
   * This function generates hilbert convolution kernel using Hamming window
   *
   * @param kernel  result, convolution kernel
   * @param k_radius  radius of the convolution kernel
   */
  static void genHilbert( float* kernel, unsigned int k_radius );

private:

  // handle on cuda kernel 
  SoCudaHandle* m_cuInstEnvelopeHandle;

  // handle on cuda kernel 
  SoCudaHandle* m_cuInstPhaseHandle;

  // reference on CUDA convolution module used.
  SoCudaConvolution *m_cudaConvolutionInterface;
};

#endif //SOCUDASEISMIC_H

