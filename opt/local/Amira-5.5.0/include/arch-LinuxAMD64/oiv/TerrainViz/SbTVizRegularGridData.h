/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2001)
**=======================================================================*/

#ifndef SBTVIZREGULARGRIDDATA_H
#define SBTVIZREGULARGRIDDATA_H

#include  <TerrainViz/SbTVizData.h>

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>


class Array2D;


/**
 * @TVEXT Regular grid data class.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class stores data provided as a regular grid sampling. Each data point
 *   represents an elevation.
 *   
 *   The step (space between two samples) must be specified.
 *   
 *   The terrain can be shifted by an offset.
 *   All values are expressed in modeling coordinates, not physical units.
 *   But if the data come from a preprocessing operation (using @B SoTVizDataPreprocessor@b), 
 *   the units are the units that were specified during the preprocessing.
 *   
 *   Data can be loaded from a file (loadDataFile()), or given through a method
 *   (setValues()).
 *   
 *   Here are the heads of two sample data files:
 *      @TABLE_0B
 *         @TR @B ASCII files - short - little endian @b     @TD @TD @TD @TD @TD @TD @TD @B Binary files - float - big endian @b
 *         @TR # TerrainViz V1.0 ascii                       @TD @TD @TD @TD @TD @TD @TD # TerrainViz V1.0 binary
 *         @TR # type ushort                                 @TD @TD @TD @TD @TD @TD @TD # type float
 *         @TR # size 256 256                                @TD @TD @TD @TD @TD @TD @TD # size 256 512
 *         @TR # encoding LITTLE_ENDIAN                      @TD @TD @TD @TD @TD @TD @TD # encoding BIG_ENDIAN
 *         @TR 3562 2541 2365 ...                            @TD @TD @TD @TD @TD @TD @TD 2125.5 3652.2 2155.6 ...
 *      @TABLE_END
 *   
 *   The data array is organized as following:
 *   
 *   @IMAGE DTM_data_org.jpg 
 *   
 *   - The default dataType is UCHAR.
 *   - The default openMode is UNKNOWN.
 *   - The default encoding is BIG_ENDIAN.
 * 
 * @SEE_ALSO
 *    SbTVizData,
 *    SbTVizTexture,
 *    SbTVizTextureList,
 *    SoTViz,
 *    SoTVizRender
 * 
 * 
 */ 

class TERRAINVIZ_API SbTVizRegularGridData : public SbTVizData {

 public:
  /**
   * Constructor.
   */
  SbTVizRegularGridData();

  /**
   * 
   * Constructor by copy.
   */
  SbTVizRegularGridData(const SbTVizRegularGridData& data);
  
  /**
   * Destructor.
   */
  virtual ~SbTVizRegularGridData();

  /**
   * Method to be used with the internal .dat format (specific header). Sets the
   * attributes and loads data from a regular grid data file (regular sampling, lines
   * * columns).
   * 
   * In this case, the file must include a header specifying the open mode (ASCII or
   * BINARY), the data type (listed by SbTVizData::DataType. Can be UCHAR, USHORT, 
   * FLOAT...), the size of the array, and
   * the encoding format (LITTLE_ENDIAN or BIG_ENDIAN). The data organization is
   * explained above.
   */
  SbBool loadDataFile(const SbString& fileName, const SbVec3d& step, const SbVec3d& offset);
  /**
   * Same as previous but to be used with rough data files, i.e., files that don't
   * contain a descriptive header. The following additional parameters must be
   * specified: data type (listed by SbTVizData::DataType. Can be UCHAR, USHORT, FLOAT...),
   * the open mode (ASCII or BINARY),
   * and the encoding format (LITTLE_ENDIAN or BIG_ENDIAN).
   */
  SbBool loadDataFile(const SbString& fileName, const SbVec2s numSamples, 
                      const SbVec3d& step,      const SbVec3d& offset, 
                      DataType dataType,  OpenMode openMode, 
                      Encoding encoding);

  /**
   * Returns the average altitude of the data.
   */
  float getAvgValue() const;
  /**
   * Returns the maximum altitude of the data.
   */
  float getMaxValue() const;
  /**
   * Returns the minimum altitude of the data.
   */
  float getMinValue() const;


  /**
   * Returns the altitude at the specified coordinate. If the input
   * value does not correspond exactly to a grid point on the terrain
   * data, the altitude of the nearest grid point is returned.
   * No interpolation is done. 
   */
  float getValue(const SbVec2d& point) const;
  /**
   * Returns the altitude at the specified index in the array.
   */
  float getValue(int idx) const;
        
  /**
   * 
   * Gets the altitude values between two given points, and returns the number of values.
   * @BR 
   * @BR 
   * Inputs: The coordinates of the line extremities (point0 and point1).
   *
   * Input/Output: 
   *   - A reference to the value array to be allocated and filled (values).
   *   - The sampling step along this line (lineStep). If 0, then it uses the grid resolution.
   *     This value may be adjusted by this method.
   *
   * Return value: The array length (number of samples).
   */
  int getLineValues(SbVec3f*& values, SbVec2d& point0, SbVec2d& point1, float& lineStep) const;


  /**
   * Sets the altitudes with all parameters. The data organization is explained
   * above.
   */
  void setValues(const void* data, const SbVec2s numSamples, const SbVec3d& step, 
                 const SbVec3d& offset, DataType dataType);

  /**
   * Returns the number of samples (x, y).
   */
  inline const SbVec2s&  getNumSamples() const {return numSamples;};
  /**
   * Returns the sampling step along the three dimensions.
   */
  inline const SbVec3d&  getSteps() const {return step;};

  /**
   * Writes data to a file (ASCII or BINARY). The default file extension is .dat.
   * The DataType (UCHAR, USHORT, etc.) is the DataType of the SbTVizData instance.
   * The Encoding (BIG_ENDIAN or LITTLE_ENDIAN) is
   * determined by the machine running the program. 
   */
  SbBool writeDataFile(const SbString& filename, OpenMode mode);


 SoINTERNAL public:
  SbBool isOfType(SbString& className) const;

  ZType getZValue(SbVec2i32 coord) const;
  float getModellingZValue(SbVec2i32 coord) const;

  // In internal coordinates (IC) 0-1 0-1
  float getAvgValueIC() const;
  float getMaxValueIC() const;
  float getMinValueIC() const;

  const Array2D* getArray2D() const {return m_data;};

 private:
  FILE* openFile(SbString& out_buf, SbString& mode);

  SbBool loadDataFile();
  SbBool readData(FILE* fd);
  void   adjustData();

  void uppercase(char* str);

  void endianConvertUShort(unsigned short* data);
  void endianConvertShort(short* data);
  void endianConvertFloat(float* data);
  void endianConvertUInt(uint32_t* data);
  void endianConvertInt(int32_t* data);

  void writeASCIIData(FILE* fd);


  SbVec2s numSamples;
  SbVec3d step;

  // Data array
  Array2D*   m_data;
  void* m_xmap;
  void* m_ymap;
};

#endif

