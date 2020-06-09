/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDAARITHMETIC_H
#define SOCUDAARITHMETIC_H

#include <Inventor/SbString.h>
#include <Inventor/SbDataType.h>

#include <Inventor/STL/vector>

#include <Inventor/algorithms/SoArithmetic.h>

#include <Inventor/cuda/algorithms/SoCudaAlgorithmsDefs.h>

class SoCudaHandle;
class SoCudaBufferObject;

/**
* @VSGEXT Arithmetic functions for CUDA buffers
*
* @ingroup CudaAlgorithms
*
* @DESCRIPTION
*
* The Arithmetic module provides basic Add, Multiply, etc functions that operate on buffers.
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

class INVENTORCUDAALGORITHMS_API  SoCudaArithmetic : public SoArithmetic
{
SoINTERNAL public:
  /**
   * This function initializes the arithmetic module.
   */
  static void initClass();

  /**
   * This function unloads the arithmetic module and free the data.
   */
  static void exitClass();

  /**
   * Destructor
   */
  ~SoCudaArithmetic();

public:
  /**
   * Constructor
   */
  SoCudaArithmetic();

  /**
  * Add two buffers into a third one.
  * @BR
  * C = A + B
  * @BR
  * Note: C can be a reference to A or B.
  * @BR
  * @B Limitation: @b typeA and typeB must be the same as typeC.
  */
  virtual int add(
    SoBufferObject* inputBufferA, const SbDataType typeA,
    SoBufferObject* inputBufferB, const SbDataType typeB,
    SoBufferObject* outputBufferC, const SbDataType typeC );

  /**
   * Add two buffers into a third one.
   * @BR
   * Cuda input version.
   */
  int add(
    SoCudaBufferObject* inputBufferA, const SbDataType typeA,
    SoCudaBufferObject* inputBufferB, const SbDataType typeB,
    SoCudaBufferObject* outputBufferC, const SbDataType typeC
    );


  /**
  * Multiply two buffers into a third one.
  * @BR
  * C = A * B
  * Note: C can be a reference to A or B
  * @BR
  * @B Limitation: @b typeA and typeB must be the same as typeC
  */
   virtual int mult(
    SoBufferObject* intpuBufferA, const SbDataType typeA,
    SoBufferObject* intpuBufferB, const SbDataType typeB,
    SoBufferObject* outputBufferC, const SbDataType typeC
    );

  /**
   * Multiply two buffers into a third one.
   * @BR
   * Cuda input version.
   */
  int mult(
    SoCudaBufferObject* inputBufferA, const SbDataType typeA,
    SoCudaBufferObject* inputBufferB, const SbDataType typeB,
    SoCudaBufferObject* outputBufferC, const SbDataType typeC
    );

  /**
  * B = A * scaleFactor
  * @BR
  * Note: B can be a reference to A
  * @BR
  * @B Limitation: @b typeA must be the same as typeC
  */
  virtual int scale(
    SoBufferObject* inputBufferA, const SbDataType typeA,
    SoBufferObject* outputBufferB, const SbDataType typeB,
    const float scaleValue
    );

  /**
   * B = A * scaleFactor
   * @BR
   * Cuda input version.
   */
  int scale(
    SoCudaBufferObject* inputBufferA, const SbDataType typeA,
    SoCudaBufferObject* outputBufferB, const SbDataType typeB,
    const float scaleValue
    );

  /**
  * B = A + shiftFactor
  * @BR
  * Note: B can be a reference to A
  * @BR
  * @B Limitation: @b typeA must be the same as typeC
  */
  virtual int shift(
    SoBufferObject* inputBufferA, const SbDataType typeA,
    SoBufferObject* outputBufferB, const SbDataType typeB,
    const float shiftFactor
    );

  /**
   * B = A + shiftFactor
   * @BR
   * Cuda input version.
   */
  int shift(
    SoCudaBufferObject* inputBufferA, const SbDataType typeA,
    SoCudaBufferObject* outputBufferB, const SbDataType typeB,
    const float shiftFactor
    );

  /**
  * C = A * scale + B 
  * @BR
  * Note: C can be a reference to A or B
  * @BR
  * @B Limitation: @b typeA and typeB must be the same as typeC
  */
  virtual int madd(
    SoBufferObject* inputBufferA, const SbDataType typeA,
    SoBufferObject* inputBufferB, const SbDataType typeB,
    SoBufferObject* outputBufferC, const SbDataType typeC,
    const float scaleValue
    );

  /**
   * C = A * scale + B 
   * @BR
   * Cuda input version.
   */
  int madd(
    SoCudaBufferObject* inputBufferA, const SbDataType typeA,
    SoCudaBufferObject* inputBufferB, const SbDataType typeB,
    SoCudaBufferObject* outputBufferC, const SbDataType typeC,
    const float scaleValue
    );

private:

  SoCudaHandle* m_addFunctionHandle;

  SoCudaHandle* m_multFunctionHandle;

  SoCudaHandle* m_scaleFunctionHandle;

  SoCudaHandle* m_shiftFunctionHandle;

  SoCudaHandle* m_madFunctionHandle;
};

#endif // SOCUDAARITHMETIC_H

