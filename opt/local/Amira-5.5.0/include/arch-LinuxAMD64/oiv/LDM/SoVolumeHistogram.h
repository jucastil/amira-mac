/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.DUFOUR (May 2004)
**=======================================================================*/

#ifndef  _SO_VOLUME_HISTOGRAM_
#define  _SO_VOLUME_HISTOGRAM_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#pragma warning(disable:4127)
#endif

#include <Inventor/SbDataType.h>
#include <Inventor/SbLinear.h>
#include <Inventor/helpers/SbDataTypeMacros.h>

#include <Inventor/STL/limits>
#include <Inventor/STL/vector>

class SoBufferObject;
class SoArithmetic;

/**
 * Volume Data Histogram.
 *
 * @ingroup VolumeRendering
 *
 * @DESCRIPTION
 *   This class allows building a histogram from a dataset or a portion of a dataset.
 *
 *   To implement the histogram computation, follow the steps below:
 *
 *   - Instanciate this class by passing the data type to the constructor.
 *
 *   - Pass the values by calling the method addValues() multiple times.
 *
 *   - Get the results using methods getHistoSize(), getHistogramme(), getNumValues(), getValue(),
 *     getMinValue, getMaxValue(), getNumSignificantBits().
 *
 *   - Delete the object.
 *
 * @SEE_ALSO
 *    SoDataSet
 *
 *
 */


class LDM_API SoVolumeHistogram
{
public:
  /**
  * Constructor
  */
  SoVolumeHistogram(const SbDataType &dataType);

  /**
   * Destructor
   */
  ~SoVolumeHistogram();

  /**
  * For floating data type, specifies the range the histogram has to be computed in.
  * Must be called before any call to addValues().
  * Default values are -20000. 20000.
  */
  void setInputValueRange( double rangeMin, double rangeMax );

  /**
   * Setup the undefined value to ignore when computing the histogram.
   */
  void setUndefinedValue( const double undefinedValue)
  { m_undefinedValue=undefinedValue; }

  /**
   * return the current undefined value.
   */
  double getUndefinedValue() const
  { return m_undefinedValue; };

  /**
  * Returns the size of the histogram
  */
  size_t getHistoSize();

  /**
  * Returns a 64 bit integer pointer to the histogram data, 
  * the size of the histogram array is getHistoSize()
  */
  int64_t* getHistogram();

  /**
  * Returns a 32 bit integer pointer to the histogram data, 
  * the size of the histogram array is getHistoSize()
  *
  * @B NOTE@b: This method is obsolete and only for VolumeViz 4.0 compatibility.
  * Use the #getHistogram() method.
  */
  int* getHistogram32();

  /**
  * Returns the histogram value corresponding to the entry.
  * Equivalent to getHistogram()[entry]
  */
  int64_t getNumValues(size_t entry);

  /**
  * Returns the value corresponding to the entry for integer data types
  */
  int64_t getValue(size_t entry);

  /**
  * Returns the value corresponding to the entry for floating data types
  */
  double getValueD(size_t entry);

  /**
  * Returns the min value of the dataset for integer data types
  */
  int64_t getMinValue();

  /**
  * Returns the max value of the dataset for integer data types
  */
  int64_t getMaxValue();

  /**
  * Returns the min value of the dataset for floating data types
  */
  double getMinValueD();

  /**
  * Returns the max value of the dataset for floating data types
  */
  double getMaxValueD();

  /**
   * Returns the max value of the dataset according to the specified data type
   */
  double getMax();

  /**
   * Returns the max value of the dataset according to the specified data type
   */
  double getMin();

  /**
  * Returns the number of significant bits for the dataset, only relevant for integer data types
  */
  int getNumSignificantBits();

  /**
  * Add to the histogram a 1D array of values.
  * NOTES: this API is limited to INT_MAX numValues to handle.
  */
  inline void addValues(SoBufferObject* values, const int numValues);

  /** 
   * Add to the histogram a 3D array of values.
   */
  inline void addValues(SoBufferObject* values, const SbVec3i32& arrayDim);

  /** 
   * Add to the histogram the values in the specified range inside the given array.
   */
  void addValues(SoBufferObject* values, const SbVec3i32& arrayDim, const SbBox3i32& range);

  /**
  * Set the histogram. Useful to get back scalar parameters such as min/max values and number of significant bits
  */
  void set(const std::vector<int64_t> & histo);

  /**
  * Set the histogram. Useful to get back scalar parameters such as min/max values and number of significant bits
  */
  void set(const std::vector<int64_t>& histo, const std::vector<double>& values);

  /**
   * Returns the histogram entry corresponding to the value.
   */
  template<typename T> inline size_t getEntry(T value) const;

  /**
   * Compute min max.
   */
  static void computeMinMax(
    SoBufferObject* valuesBuffer,
    const SbDataType& dataType,
    const SbVec3i32& arrayDim,
    const SbBox3i32& range,
    double& min,
    double& max
    );

  /**
   * Compute min max.
   */
  static void computeMinMaxWithUndefined(
    SoBufferObject* valuesBuffer,
    const double undefinedValue,
    const SbDataType& dataType,
    const SbVec3i32& arrayDim,
    const SbBox3i32& range,
    double& min,
    double& max
    );

  /**
   * Compute min max.
   */
  static void computeMinMax(
    void* valuesBuffer,
    const SbDataType& dataType,
    const SbVec3i32& arrayDim,
    SbVec2d& minMax);

  /**
   * Compute min max.
   */
  static void computeMinMaxWithUndefined(
    void* valuesBuffer,
    const double undefinedValue,
    const SbDataType& dataType,
    const SbVec3i32& arrayDim,
    SbVec2d& minMax
    );

SoINTERNAL public:
  /**
   * init/finish class. (Must be called before any Histogram creation)
   */
  static void initClass();
  static void exitClass();

private:
  /**
   * Returns the histogram entry corresponding to the value.
   */
  template<typename T> inline size_t getEntryInternal(T value) const;

  /**
   * Cast value according to m_dataType. This avoid ambiguity
   * like getEntry(5) which could be getEntry(int(5)) or
   * getEntry(unsigned int(5))
   */
  template<typename T> inline size_t getEntryCaster(T value) const;

private:
  size_t   m_histoSize;          // histogram size. 256 if dataSize = 1, 0x10000 otherwise.
  int64_t* m_histo;              // histogram
  int*     m_histo32;            // histogram 32 bits encoded built on demand only, for VolumeViz 4.0 compatibility only
  int64_t  m_valueMin;           // min integer value of the dataset for integer data types
  int64_t  m_valueMax;           // max integer value of the dataset for integer data types
  double   m_valueMinD;          // min integer value of the dataset for floating data types
  double   m_valueMaxD;          // max integer value of the dataset for floating data types
  unsigned int m_numSignificantBits; // number of significant bits, only relevant for integer data types
  bool     m_isScalarsComputed;  // indicates if the scalar values above are computed

  SbDataType m_dataType;     // data type
  double m_rangeMin;         // for floating data type.
  double m_rangeMax;         // for floating data type.
  double m_undefinedValue;   // undefined Value.

  void computeScalars();

  // makeStats template
  template <typename T>
  void makeStat(
    const void* values,
    const SbVec3i32& arrayDim,
    const SbBox3i32& range
    );

  static SoArithmetic* m_arithmeticInterface;
};

/*******************************************************************************/
void
SoVolumeHistogram::addValues(SoBufferObject* values, const int numValues)
{
  addValues(values, SbVec3i32(numValues, 1, 1), SbBox3i32(SbVec3i32(0, 0, 0), SbVec3i32(numValues, 1, 1)));
}

/*******************************************************************************/
void SoVolumeHistogram::addValues(SoBufferObject* values, const SbVec3i32& arrayDim)
{
  addValues(values, arrayDim, SbBox3i32(SbVec3i32(0,0,0),arrayDim));
}

/*******************************************************************************/
template<typename T> size_t
SoVolumeHistogram::getEntryInternal(T value) const
{
  assert(m_dataType.isInteger());
  assert(sizeof(T) <= 4);
  size_t offset = 0;
  size_t factor = 1;

  if ( std::numeric_limits<T>::is_signed )
    offset = (sizeof(T) >= 2) ? 0x8000 : 0x80;

  if ( sizeof(T) == 4 )
    factor = (size_t)0x10000;

  size_t entry = (size_t)(value/int64_t(factor)+int64_t(offset));

  return entry;
}

/*******************************************************************************/
template<typename T> size_t
SoVolumeHistogram::getEntryCaster(T value) const
{
  return getEntryInternal(T(value));
}

/*******************************************************************************/
template<typename T> size_t
SoVolumeHistogram::getEntry(T value) const
{
  size_t ret;
  SB_DATATYPE_CALL_ASSIGN(getEntryInternal, (value), ret, m_dataType);

  return ret;
}

/*******************************************************************************/
template<> inline size_t
SoVolumeHistogram::getEntryInternal<float>(float value) const
{
  assert(m_dataType == SbDataType::FLOAT);
  if ( m_rangeMax == m_rangeMin )
    return 0;
  double factorDouble = 0.0f;
  factorDouble = 0xffff / (m_rangeMax - m_rangeMin);
  size_t entry = (size_t)((value-m_rangeMin)*factorDouble);

  return SbMathHelper::Clamp(entry, (size_t)0, (size_t)0xffff);
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_VOLUME_HISTOGRAM_ */
