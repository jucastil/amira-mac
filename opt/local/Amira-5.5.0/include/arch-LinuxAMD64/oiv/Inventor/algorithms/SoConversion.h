/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCONVERSION_H
#define SOCONVERSION_H

#include <Inventor/SbString.h>
#include <Inventor/SbDataType.h>

#include <Inventor/STL/vector>

#include <Inventor/algorithms/SoAlgorithmsDefs.h>

#if defined(__i386__) || defined(__amd64__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_AMD64)
#	define HAS_SSE
#endif

#if ( __GNUC__ == 3 && __GNUC_MINOR__ == 2 )
#undef HAS_SSE
#endif

#ifdef HAS_SSE
#	include <mmintrin.h>
#	include <xmmintrin.h>
#	include <emmintrin.h>
#endif

class SoBufferObject;
class SoCpuBufferObject;

/**
* @VSGEXT Type conversion functions for buffers
*
* @ingroup CpuAlgorithms
*
* @DESCRIPTION
*
* This module provides data type conversions, like bytes to floats...
*
* Examples:
* 
* @SEE_ALSO
*   SoAlgorithms, SoArithmetic, SoConvolution, SoDataExtract, SoSeismic
*
*/

class INVENTORALGORITHMS_API  SoConversion
{
SoINTERNAL public:
  /** SoConversion destructor */
  virtual ~SoConversion();


  /** Static initClass function to initialize the conversion module. */
  static void initClass();


  /** Static exitClass function to free the memory allocated by the conversion module. */
  static void exitClass();

public:
  /** SoConversion constructor */
  SoConversion();

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
    SoBufferObject* targetBufferObject, const SbDataType dst_type, const size_t size );


  /**
   * Convert the data in a buffer object from one data type to another one.
   * @BR
   * Fast implementation for CPU buffers.
   */
  int convert(
    SoCpuBufferObject* sourceBufferObject, const SbDataType src_type,
    SoCpuBufferObject* targetBufferObject, const SbDataType dst_type, const size_t size );

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
    const size_t size, const float dataMin, const float dataMax );


  /**
   * Convert FLOAT data stored in a buffer to RGBA data.
   *
   * Fast implementation for CPU buffers.
   */
  int convertFloatToRGBA(
    SoCpuBufferObject* sourceBufferObject,
    SoCpuBufferObject* targetBufferObject,
    const size_t size, const float dataMin, const float dataMax );

private:
  /**
   * Convert the data in a buffer object from any data type to FLOAT.
   *
   * Notes:
   *  The destination buffer and the source buffers can be same according to the data types.
   *
   * @param sourceBufferObject The source buffer object.
   * @param src_type The type of the data in the source buffer object.
   * @param targetBufferObject The destination buffer object.
   * @param size The number of elements (not necessary bytes!) in the source buffer object to convert.
   *
   * @return Returns 0 if there were no errors during the process. Returns 1
   *  if one or more buffers don't have the correct size. 
   */
  int convertToFloat(
    SoBufferObject* sourceBufferObject, const SbDataType src_type,
    SoBufferObject* targetBufferObject, const size_t size );


  /**
   * Convert the data in a buffer object from any data type to FLOAT.
   *
   * Fast implementation for CPU buffers.
   */
  int convertToFloat(
    SoCpuBufferObject* sourceBufferObject, const SbDataType src_type,
    SoCpuBufferObject* targetBufferObject, const size_t size );


  /**
   * Convert the data in a buffer object from any data type to UNSIGNED CHAR.
   *
   * @param sourceBufferObject The source buffer object.
   * @param src_type The type of the data in the source buffer object.
   * @param targetBufferObject The destination buffer object.
   * @param size The number of elements (not necessary bytes!) in the source buffer object to convert.
   *
   * @return Returns 0 if there were no errors during the process. Returns 1
   *  if one or more buffers don't have the correct size. 
   */
  int convertToUChar(
    SoBufferObject* sourceBufferObject, SbDataType src_type,
    SoBufferObject* targetBufferObject, const size_t size );


  /**
   * Convert the data in a buffer object from any data type to UNSIGNED CHAR.
   *
   * Fast implementation for CPU buffers.
   */
  int convertToUChar(
    SoCpuBufferObject* sourceBufferObject, SbDataType src_type,
    SoCpuBufferObject* targetBufferObject, const size_t size );

SoINTERNAL public:

  /**
   * Used by SoDataSet to convert data to index texture with a given range
   */
  virtual void mapDataRangeToIndex(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset );


  /**
   * Used  by SoDataSet to convert data to indexed texture
   */
  virtual void mapDataToIndex(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const int numSigBits, const int shift, const int offset );


  /**
   * Used  by SoDataSet to convert data to RGBA texture with a given range
   */
  virtual void mapDataRangeToRgba(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset,
    SoBufferObject *rgbaBufferObject, const int numRgba );


  /**
   * Used  by SoDataSet to convert data to RGBA texture
   */
  virtual void mapDataToRgba(
    SoBufferObject *sourceBufferObject, const SbDataType src_type,
    SoBufferObject *targetBufferObject, const SbDataType dst_type,
    const int numSigBits, const int shift, const int offset,
    SoBufferObject *rgbaBufferObject, const int numRgba );

  /**
   * Convert the data in a buffer object from unpacked UNSIGNED CHAR bitset to packed bitset.
   *
   * Fast implementation for CPU buffers.
   * Nb: used by SoCpuBufferBitSet
   */
  static void convertByteToBitSet(SoCpuBufferObject* sourceBufferObject,SoCpuBufferObject* targetBufferObject);

  /**
   * Convert the data in a buffer object from packed bitset from to UNSIGNED CHAR.
   *
   * Fast implementation for CPU buffers.
   * Nb: used by SoCpuBufferBitSet
   */
  static void convertBitSetToByte(SoCpuBufferObject* sourceBufferObject,SoCpuBufferObject* targetBufferObject);

protected:

 // IN template CPU dataRangeToIndex version
  template <typename DataClassIn>
  static void cpuMapDataRangeToIndex(const void *srcData, void *dstData,
    const size_t bufferSize, const SbDataType::DataType dataTypeDst,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset
    );


  // IN/OUT template CPU version
  template <typename DataClassIn, typename DataClassOut>
  static void cpuMapDataRangeToIndexTempl(
    const void *src, void *dst, const size_t bufferSize,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset
    );

#ifdef HAS_SSE
  // IN/OUT template CPU SSE2 version
  template <typename DataClassIn, typename DataClassOut>
  static void cpuMapDataRangeToIndexTemplSSE(
    const void *src, void *dst, const size_t bufferSize,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset
    );

  template <typename DataClassIn>
  static void SSE_loadRegister( DataClassIn*& ptr, __m128& reg );

  template <typename DataClassOut>
  static void SSE_unloadRegister( __m128& regA, __m128& regB, DataClassOut*& ptr );
#endif

  // IN template CPU dataRangeToRgba version
  template <typename DataClassIn>
  static void cpuMapDataRangeToRgba(
    const void *src, void *dst, const size_t bufferSize,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset,
    const unsigned int *rgba, const int numRgba
    );


  // IN template CPU dataToIndex version
  template <typename DataClassIn>
  static void cpuMapDataToIndex(const void *srcData, void *dstData,
    const size_t bufferSize, const SbDataType::DataType dataTypeDst,
    const int numSigBits, const int shift, const int offset
    );


  // IN/OUT template CPU version
  template <typename DataClassIn, typename DataClassOut>
  static void cpuMapDataToIndexTempl(
    const void *src, void *dst, const size_t bufferSize,
    const int numSigBits, const int shift, const int offset
    );


  // IN template CPU dataToRgba version
  template <typename DataClassIn>
  static void cpuMapDataToRgba(
    const void *src, void *dst, const size_t bufferSize,
    const int numSigBits, const int shift, const int offset,
    const unsigned int *rgba, const int numRgba
    );

private:
#if defined(HAS_SSE)
  static void convertBitSetToByteSSE(unsigned char* packedTile, unsigned char* unpackedTile, uint64_t size);
#endif
  static void convertBitSetToByteStd(unsigned char* packedTile, unsigned char* unpackedTile, uint64_t size);


  static bool s_useSSE;

};

#endif //SOCONVERSION_H

