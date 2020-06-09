/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOSEISMIC_H
#define SOSEISMIC_H

#include <Inventor/SbDataType.h>

#include <Inventor/algorithms/SoAlgorithmsDefs.h>

#define HILBERT_FILTER_RADIUS 30
#define HILBERT_KERNEL_SIZE (2 * HILBERT_FILTER_RADIUS + 1)

class SoBufferObject;
class SoCpuBufferObject;
class SoConvolution;

/**
* @VSGEXT Seismic attribute functions for buffers
*
* @ingroup CpuAlgorithms
*
* @DESCRIPTION
*
* The Seismic module provides functions for computing seismic attributes.
*
* Examples:
*
* @SEE_ALSO
*   SoAlgorithms, SoArithmetic, SoConversion, SoConvolution, SoDataExtract
*/

class INVENTORALGORITHMS_API  SoSeismic
{
SoINTERNAL public:
  /** 
   * Destructor 
   * [OIV-WRAPPER VISIBILITY{Internal}]
   */
  virtual ~SoSeismic();

  /** Init and register module. */
  static void initClass();

  /** unregister module. */
  static void exitClass();

public:
  /** Constructor. */
  SoSeismic();

  /**
   * Compute instantaneous phase attribute on a set of seismic traces. @BR
   *  phase(t) = arctan( im(t)/re(t))
   *
   * - This function can be redefined to support a different type of SoBufferObject.
   * - By default the SoCpuBufferObject CPU version will be used.
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
   * - This function can be redefined to support a different type of SoBufferObject.
   * - By default the SoCpuBufferObject CPU version will be used.
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
   * - This function can be redefined to support a different type of SoBufferObject.
   * - By default the SoCpuBufferObject CPU version will be used.
   * - Data stored in buffers must be of type float.
   */
  virtual int computeHilbert( SoBufferObject* sourceBufferObject, SoBufferObject* targetBufferObject,
                                    int width, int height );

  /**
   * Compute instantaneous phase attribute on a set of seismic traces.
   * - This function handles SoCpuBufferObject input output type only.
   * - Data stored in buffers must be of type float.
   */
  int computeInstPhase( SoCpuBufferObject* sourceBufferObject, SoCpuBufferObject* targetBufferObject,
                                    int traceSize, int numTrace );

  /**
   * Compute envelope (amplitude) attribute on a set of seismic traces.
   * - This function handles SoCpuBufferObject input output type only.
   * - Data stored in buffers must be of type float.
   */
  int computeEnvelope( SoCpuBufferObject* sourceBufferObject, SoCpuBufferObject* targetBufferObject,
                                   int traceSize, int numTrace );

  /**
   * Compute Hilbert transform on a set of seismic traces.
   * - This function handles SoCpuBufferObject input output type only.
   * - Data stored in buffers must be of type float.
   */
  int computeHilbert( SoCpuBufferObject* sourceBufferObject, SoCpuBufferObject* targetBufferObject,
                                    int width, int height );

protected:

  /**
   * Initialize kernel for hilbert
   */
  static void initKernel();

  /**
   * This function generates hilbert convolution kernel using Hamming window
   *
   * @param kernel  result, convolution kernel
   * @param k_radius  radius of the convolution kernel
   */
  static void genHilbert( float* kernel, unsigned int k_radius );

protected:

  // Hilbert kernel storage.
  static float s_hilbertKernel[ HILBERT_KERNEL_SIZE ];

private:
  // reference on convolution module used.
  SoConvolution* m_convolutionInterface;

};

#endif //SOSEISMIC_H
