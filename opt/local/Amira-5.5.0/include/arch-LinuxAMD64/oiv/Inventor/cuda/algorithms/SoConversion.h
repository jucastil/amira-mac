/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDACONVERTION_H
#define SOCUDACONVERTION_H

#include <Inventor/SbString.h>
#include <Inventor/SbDataType.h>

#include <Inventor/STL/vector>

#include <Inventor/algorithms/SoConversion.h>

#include <Inventor/cuda/algorithms/SoCudaAlgorithmsDefs.h>

class SoCudaHandle;
class SoCudaBufferObject;

/**
* @VSGEXT Type conversion functions for CUDA buffers
*
* @ingroup CudaAlgorithms
*
* @DESCRIPTION
* This module provides data type conversions, like bytes to floats...
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

class INVENTORCUDAALGORITHMS_API SoCudaConversion : public SoConversion
{
SoINTERNAL public:
  /** This function init the Cuda module. */
  static void initClass();

  /** This function unload the Cuda module and free the data. */
  static void exitClass();
 
  /** Destructor */
  ~SoCudaConversion();

public:
  /** Constructor */
  SoCudaConversion();

  /**
   * Convert FLOAT data stored in a buffer to (grayscale) RGBA data.
   *
   * - The source and the target buffers can be the same.
   * - The algorithm maps float values between dataMin and dataMax to the range 0..255.
   * - The resulting values are clamped to 0..255.
   *
   * @param sourceBufferObject The source buffer object containing the FLOAT data.
   * @param targetBufferObject The target buffer object.
   * @param size The number of FLOAT values to convert.
   * @param dataMin The minimum value for the greyscale conversion.
   * @param dataMax The maximum value for the greyscale conversion.
   *
   * @return Returns 0 if there were no errors during the process. Returns 1
   *  if one or more buffers don't have the correct size. 
   */
  virtual int convertFloatToRGBA(
    SoBufferObject* sourceBufferObject,
    SoBufferObject* targetBufferObject,
    const size_t size, const float dataMin, const float dataMax
    );

  /**
   * Convert FLOAT data stored in a buffer to (grayscale) RGBA data. @BR
   * Cuda input version.
   */
  int convertFloatToRGBA(
    SoCudaBufferObject* sourceBufferObject,
    SoCudaBufferObject* targetBufferObject,
    const size_t size, const float dataMin, const float dataMax
    );

  /**
   * Convert the data in a buffer object from one data type to another one. @BR
   *
   * Notes:
   *  The destination buffer and the source buffers can be same.
   *
   * @B Limitations: @b
   *  This function only supports FLOAT and UNSIGNED_BYTE for dst_type.
   *
   * @param sourceBufferObject The source buffer object.
   * @param src_type The type of the data in the source buffer object.
   * @param targetBufferObject The destination buffer object.
   * @param dst_type The destination type.
   * @param size The number of elements in the source buffer object to convert.
   *
   * @return Returns 0 if there were no errors during the process. Returns 1
   *  if one or more buffers don't have the correct size. 
   */
  virtual int convert(
    SoBufferObject* sourceBufferObject, const SbDataType src_type,
    SoBufferObject* targetBufferObject, const SbDataType dst_type,
    const size_t size
    );

  /**
   * Convert the data in a buffer object from one data type to another one. @BR
   * CUDA input version.
   */
  int convert(
    SoCudaBufferObject* sourceBufferObject, const SbDataType src_type,
    SoCudaBufferObject* targetBufferObject, const SbDataType dst_type,
    const size_t size
    );

private:
  /** used by ::convert */
  int convertToFloat(
    SoBufferObject* sourceBufferObject, const SbDataType src_type,
    SoBufferObject* targetBufferObject,
    const size_t size
    );
  /** used by ::convert */
  int convertToFloat(
    SoCudaBufferObject* sourceBufferObject, const SbDataType src_type,
    SoCudaBufferObject* targetBufferObject,
    const size_t size
    );
  /** used by ::convert */
  int convertToUChar(
    SoBufferObject* sourceBufferObject, SbDataType src_type,
    SoBufferObject* targetBufferObject,
    const size_t size );
  /** used by ::convert */
  int convertToUChar(
    SoCudaBufferObject* sourceBufferObject, SbDataType src_type,
    SoCudaBufferObject* targetBufferObject,
    const size_t size );

SoINTERNAL public:
  /**
   * Used  by SoDataSet to convert data to index texture with a given range
   */
  void mapDataRangeToIndex(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset
    );

  /**
   * Used  by SoDataSet to convert data to index texture with a given range
   */
  void mapDataRangeToIndex(
    SoCudaBufferObject *sourceBufferObject, const SbDataType src_type,
    SoCudaBufferObject *targetBufferObject, const SbDataType dst_type,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset
    );

  /**
   * Used  by SoDataSet to convert data to indexed texture
   */
  void mapDataToIndex(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const int numSigBits, const int shift, const int offset
    );

  /**
   * Used  by SoDataSet to convert data to indexed texture
   */
  void mapDataToIndex(
    SoCudaBufferObject *sourceBufferObject, const SbDataType src_type,
    SoCudaBufferObject *targetBufferObject, const SbDataType dst_type,
    const int numSigBits, const int shift, const int offset
    );

  /**
   * Used  by SoDataSet to convert data to RGBA texture with a given range
   */
  void mapDataRangeToRgba(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset,
    SoBufferObject *rgbaBufferObject, const int numRgba
    );

  /**
   * Used  by SoDataSet to convert data to RGBA texture with a given range
   */
  void mapDataRangeToRgba(
    SoCudaBufferObject *sourceBufferObject, const SbDataType src_type,
    SoCudaBufferObject *targetBufferObject, const SbDataType dst_type,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset,
    SoCudaBufferObject *rgbaBufferObject, const int numRgba
    );

  /**
   * Used  by SoDataSet to convert data to RGBA texture
   */
  void mapDataToRgba(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const int numSigBits, const int shift, const int offset,
    SoBufferObject *rgbaBufferObject, const int numRgba
    );

  /**
   * Used  by SoDataSet to convert data to RGBA texture
   */
  void mapDataToRgba(
    SoCudaBufferObject *sourceBufferObject, const SbDataType src_type,
    SoCudaBufferObject *targetBufferObject, const SbDataType dst_type,
    const int numSigBits, const int shift, const int offset,
    SoCudaBufferObject *rgbaBufferObject, const int numRgba
    );

private:

  SoCudaHandle* m_floatToRGBAHandle;
  SoCudaHandle* m_convertHandles[ 6 ];
  SoCudaHandle* m_floatToUCharHandle;
  SoCudaHandle* m_mapDataRangeToIndexHandle;
  SoCudaHandle* m_mapDataToIndexHandle;
  SoCudaHandle* m_mapDataToRgbaHandle;
  SoCudaHandle* m_mapDataRangeToRgbaHandle;
};

#endif //SOCUDACONVERTION_H

