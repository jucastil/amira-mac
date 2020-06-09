/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOOPENCLCONVERTION_H
#define SOOPENCLCONVERTION_H

#include <Inventor/SbString.h>
#include <Inventor/SbDataType.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/map>

#include <Inventor/algorithms/SoConversion.h>

#include <Inventor/OpenCL/algorithms/SoOpenCLAlgorithmsDefs.h>

class SoOpenCLHandle;
class SoOpenCLBufferObject;

/**
* @VSGEXT Type conversion functions for OpenCL buffers
*
* @ingroup OpenCLAlgorithms
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

class INVENTOROPENCLALGORITHMS_API SoOpenCLConversion : public SoConversion
{
SoINTERNAL public:
  /** This function init the OpenCL module. */
  static void initClass();

  /** This function unload the OpenCL module and free the data. */
  static void exitClass();
 
  /** Destructor */
  ~SoOpenCLConversion();

public:
  /** Constructor */
  SoOpenCLConversion();

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
   * OpenCL input version.
   */
  int convertFloatToRGBA(
    SoOpenCLBufferObject* sourceBufferObject,
    SoOpenCLBufferObject* targetBufferObject,
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
   * OPENCL input version.
   */
  int convert(
    SoOpenCLBufferObject* sourceBufferObject, const SbDataType src_type,
    SoOpenCLBufferObject* targetBufferObject, const SbDataType dst_type,
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
    SoOpenCLBufferObject* sourceBufferObject, const SbDataType src_type,
    SoOpenCLBufferObject* targetBufferObject,
    const size_t size
    );
  /** used by ::convert */
  int convertToUChar(
    SoBufferObject* sourceBufferObject, SbDataType src_type,
    SoBufferObject* targetBufferObject,
    const size_t size );
  /** used by ::convert */
  int convertToUChar(
    SoOpenCLBufferObject* sourceBufferObject, SbDataType src_type,
    SoOpenCLBufferObject* targetBufferObject,
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
    SoOpenCLBufferObject *sourceBufferObject, const SbDataType src_type,
    SoOpenCLBufferObject *targetBufferObject, const SbDataType dst_type,
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
    SoOpenCLBufferObject *sourceBufferObject, const SbDataType src_type,
    SoOpenCLBufferObject *targetBufferObject, const SbDataType dst_type,
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
    SoOpenCLBufferObject *sourceBufferObject, const SbDataType src_type,
    SoOpenCLBufferObject *targetBufferObject, const SbDataType dst_type,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset,
    SoOpenCLBufferObject *rgbaBufferObject, const int numRgba
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
    SoOpenCLBufferObject *sourceBufferObject, const SbDataType src_type,
    SoOpenCLBufferObject *targetBufferObject, const SbDataType dst_type,
    const int numSigBits, const int shift, const int offset,
    SoOpenCLBufferObject *rgbaBufferObject, const int numRgba
    );

private:

  // one kernel for each type
  std::map<SbDataType,SoOpenCLHandle*> m_convertHandles;

  // others
  SoOpenCLHandle* m_floatToRGBAHandle;
  SoOpenCLHandle* m_floatToUCharHandle;
  SoOpenCLHandle* m_mapDataRangeToIndexHandle;
  SoOpenCLHandle* m_mapDataToIndexHandle;
  SoOpenCLHandle* m_mapDataToRgbaHandle;
  SoOpenCLHandle* m_mapDataRangeToRgbaHandle;
};

#endif //SOOPENCLCONVERTION_H

