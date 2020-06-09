/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOARITHMETIC_H
#define SOARITHMETIC_H

#include <Inventor/SbDataType.h>
#include <Inventor/SbLinear.h>

#include <Inventor/algorithms/SoAlgorithmsDefs.h>

class SoBufferObject;
class SoCpuBufferObject;

/**
* @VSGEXT Arithmetic functions for buffers
*
* @ingroup CpuAlgorithms
*
* @DESCRIPTION
*
* The Arithmetic module provides basic Add, Multiply, etc functions that operate on buffers.
*
* Examples:
*
* @SEE_ALSO
*   SoAlgorithms, SoConversion, SoConvolution, SoDataExtract, SoSeismic
*/

class INVENTORALGORITHMS_API  SoArithmetic
{
SoINTERNAL public:
  virtual ~SoArithmetic();

  /** Static initClass function to initialize the arithmetic module. */
  static void initClass();

  /** Static exitClass function to free the memory allocated by the arithmetic module. */
  static void exitClass();

public:
  /** Constructor */
  SoArithmetic();

  /**
  * Add two buffers into a third one.
  * @BR
  * C = A + B
  * @BR
  * Note: C can be a reference to A or B.
  * @BR
  * @B Limitation: @b typeA and typeB must be the same as typeC.
  */
  virtual int add( SoBufferObject* inputBufferA, const SbDataType typeA,
                   SoBufferObject* inputBufferB, const SbDataType typeB,
                   SoBufferObject* outputBufferC, const SbDataType typeC );
  /**
  * Add two buffers into a third one.
  * @BR
  * Fast version for Cpu buffers.
  */
  int add(
    SoCpuBufferObject* inputBufferA, const SbDataType typeA,
    SoCpuBufferObject* inputBufferB, const SbDataType typeB,
    SoCpuBufferObject* outputBufferC, const SbDataType typeC
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
    SoBufferObject* inputBufferA, const SbDataType typeA,
    SoBufferObject* inputBufferB, const SbDataType typeB,
    SoBufferObject* outputBufferC, const SbDataType typeC
    );

  /**
  * Multiply two buffers into a third one.
  * @BR
  * Fast version for Cpu buffers.
  */
  int mult(
    SoCpuBufferObject* inputBufferA, const SbDataType typeA,
    SoCpuBufferObject* inputBufferB, const SbDataType typeB,
    SoCpuBufferObject* outputBufferC, const SbDataType typeC
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
  * Fast version for Cpu buffers.
  */
  int scale(
    SoCpuBufferObject* inputBufferA, const SbDataType typeA,
    SoCpuBufferObject* outputBufferB, const SbDataType typeB,
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
  * Fast version for Cpu buffers.
  */
  int shift(
    SoCpuBufferObject* inputBufferA, const SbDataType typeA,
    SoCpuBufferObject* outputBufferB, const SbDataType typeB,
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
  * Fast version for Cpu buffers.
  */
  int madd(
    SoCpuBufferObject* inputBufferA, const SbDataType typeA,
    SoCpuBufferObject* inputBufferB, const SbDataType typeB,
    SoCpuBufferObject* outputBufferC, const SbDataType typeC,
    const float scaleValue
    );

  /**
   * Compute min max of all values contained in a buffer.
   * @BR
   *
   * @param inputBuffer The source buffer object.
   * @param dataType The type of the data in the source buffer object.
   * @param min, max Result values
   */
  virtual void computeMinMax(
    SoBufferObject* inputBuffer, const SbDataType dataType,
    double& min, double& max
    );

  /**
   * Compute min max of values contained in the specified range of the buffer.
   * @BR @BR
   * Assumes the buffer contains a 3D array of values. However 1D and
   * 2D arrays can be handled as degenerate cases.  For example, to use
   * a 1D array of length N and compute over the range I to J:
   * - Set arrayDim = N,1,1 (do not use 0 for any dimension)
   * - Set range = I,0,0,J,1,1 (be sure min and max for each axis are not the same)
   *
   * @param inputBuffer The source buffer object.
   * @param dataType The type of the data in the source buffer object.
   * @param arrayDim Dimensions of the array (can be degenerate, e.g. N,1,1)
   * @param range Subset of the array to consider
   * @param min, max Result values
   */

  virtual void computeMinMax(
    SoBufferObject* inputBuffer, const SbDataType dataType,
    const SbVec3i32& arrayDim, const SbBox3i32& range, 
    double& min, double& max
    );
    
  /**
   * Compute min max of values contained in the specified range of the buffer.
   * @BR
   * Fast version for Cpu buffers.
   */
  void computeMinMax(
    SoCpuBufferObject* inputBuffer, const SbDataType dataType,
    const SbVec3i32& arrayDim, const SbBox3i32& range, 
    double& min, double& max
    );

  /**
   * Compute min max of all values contained in a buffer that are not equal
   * to the specified undefined value.
   * @BR
   *
   * @param inputBuffer The source buffer object.
   * @param dataType The type of the data in the source buffer object.
   * @param undefinedValue ignored value
   * @param min, max Result values
   */
  virtual void computeMinMaxWithUndefinedValue(
    SoBufferObject* inputBuffer, const SbDataType dataType, const double undefinedValue,
    double& min, double& max
    );

  /**
   * Compute min max of values contained in the specified range of the buffer
   * that are not equal to the specified undefined value.
   * @BR @BR
   * Assumes the buffer contains a 3D array of values. However 1D and
   * 2D arrays can be handled as degenerate cases.  For example, to use
   * a 1D array of length N and compute over the range I to J:
   * - Set arrayDim = N,1,1 (do not use 0 for any dimension)
   * - Set range = I,0,0,J,1,1 (be sure min and max for each axis are not the same)
   *
   * @param inputBuffer The source buffer object.
   * @param dataType The type of the data in the source buffer object.
   * @param arrayDim Dimensions of the array (can be degenerate, e.g. N,1,1)
   * @param range Subset of the array to consider
   * @param undefinedValue ignored value
   * @param min, max Result values
   */

  virtual void computeMinMaxWithUndefinedValue(
    SoBufferObject* inputBuffer, const SbDataType dataType,
    const SbVec3i32& arrayDim, const SbBox3i32& range, const double undefinedValue,
    double& min, double& max
    );
    
  /**
   * Compute min max of values contained in the specified range of the buffer
   * that are not equal to the specified undefined value.
   * @BR
   * Fast version for Cpu buffers.
   */
  void computeMinMaxWithUndefinedValue(
    SoCpuBufferObject* inputBuffer, const SbDataType dataType,
    const SbVec3i32& arrayDim, const SbBox3i32& range, const double undefinedValue,
    double& min, double& max
    );

private:
  template<typename T>
  void computeMinMaxTemplate(
    SoCpuBufferObject* inputBuffer, 
    const SbVec3i32& arrayDim, 
    const SbBox3i32& range, 
    double& min, double& max);

  template<typename T>
  void computeMinMaxWithUndefinedValueTemplate(
    SoCpuBufferObject* inputBuffer, 
    const SbVec3i32& arrayDim, 
    const SbBox3i32& range,
    const double undefinedValue,
    double& min, double& max);

};

#endif // SOARITHMETIC_H

