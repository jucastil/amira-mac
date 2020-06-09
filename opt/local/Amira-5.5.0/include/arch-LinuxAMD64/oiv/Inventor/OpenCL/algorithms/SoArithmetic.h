/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOOPENCLARITHMETIC_H
#define SOOPENCLARITHMETIC_H

#include <Inventor/SbString.h>
#include <Inventor/SbDataType.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/map>

#include <Inventor/algorithms/SoArithmetic.h>

#include <Inventor/OpenCL/algorithms/SoOpenCLAlgorithmsDefs.h>

class SoOpenCLHandle;
class SoOpenCLBufferObject;

/**
* @VSGEXT Arithmetic functions for OpenCL buffers
*
* @ingroup OpenCLAlgorithms
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

class INVENTOROPENCLALGORITHMS_API  SoOpenCLArithmetic : public SoArithmetic
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
  ~SoOpenCLArithmetic();

public:
  /**
   * Constructor
   */
  SoOpenCLArithmetic();

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
   * OpenCL input version.
   */
  int add(
    SoOpenCLBufferObject* inputBufferA, const SbDataType typeA,
    SoOpenCLBufferObject* inputBufferB, const SbDataType typeB,
    SoOpenCLBufferObject* outputBufferC, const SbDataType typeC
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
   * OpenCL input version.
   */
  int mult(
    SoOpenCLBufferObject* inputBufferA, const SbDataType typeA,
    SoOpenCLBufferObject* inputBufferB, const SbDataType typeB,
    SoOpenCLBufferObject* outputBufferC, const SbDataType typeC
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
   * OpenCL input version.
   */
  int scale(
    SoOpenCLBufferObject* inputBufferA, const SbDataType typeA,
    SoOpenCLBufferObject* outputBufferB, const SbDataType typeB,
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
   * OpenCL input version.
   */
  int shift(
    SoOpenCLBufferObject* inputBufferA, const SbDataType typeA,
    SoOpenCLBufferObject* outputBufferB, const SbDataType typeB,
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
   * OpenCL input version.
   */
  int madd(
    SoOpenCLBufferObject* inputBufferA, const SbDataType typeA,
    SoOpenCLBufferObject* inputBufferB, const SbDataType typeB,
    SoOpenCLBufferObject* outputBufferC, const SbDataType typeC,
    const float scaleValue
    );

private:

  // one kernel for each type
  std::map<SbDataType,SoOpenCLHandle*> m_addFunctionHandles;
  std::map<SbDataType,SoOpenCLHandle*> m_scaleFunctionHandles;
  std::map<SbDataType,SoOpenCLHandle*> m_multFunctionHandles;
  std::map<SbDataType,SoOpenCLHandle*> m_shiftFunctionHandles;
  std::map<SbDataType,SoOpenCLHandle*> m_madFunctionHandles;
};

#endif // SOOPENCLARITHMETIC_H

