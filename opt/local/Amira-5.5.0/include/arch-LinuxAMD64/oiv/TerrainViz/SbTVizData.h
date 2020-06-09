/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2001)
**=======================================================================*/

#ifndef SBTVIZDATA_H
#define SBTVIZDATA_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>

typedef float ZType;
//typedef unsigned char ZType;

/**
 * @TVEXT Abstract base class for elevation data.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This is the top class for the TerrainViz elevation data handling classes.
 *   
 *   Elevations can be saved as a .DAT file, in ASCII or binary mode. 
 *   If binary, the encoding must be specified:
 *   BIG_ENDIAN or LITTLE_ENDIAN.
 *   
 *   Elevations can be shifted by an offset.
 *   All values are expressed in modeling coordinates, not physical units.
 * 
 *   This class is to be used with an SoTVizRender node.
 * 
 * @SEE_ALSO
 *    SbTVizRegularGridData,
 *    SbTVizTexture,
 *    SbTVizTextureList,
 *    SoTViz,
 *    SoTVizRender
 * 
 * 
 */ 

class TERRAINVIZ_API SbTVizData {

 public:

  enum OpenMode {
    /**
     *  Unknown (default). 
     */
    TVIZ_UNKNOWN = 0,
    /**
     *  File is ASCII.
     */
    TVIZ_ASCII,
    /**
     *  File is binary. 
     */
    TVIZ_BINARY
  };

  enum DataType {
    /**
     *  Unsigned char values (default). 
     */
    TVIZ_UCHAR = 0,
    /**
     *  Unsigned short values. 
     */
    TVIZ_USHORT,
    /**
     *  Unsigned int values. 
     */
    TVIZ_UINT32,
    /**
     *  Float values. 
     */
    TVIZ_FLOAT,
    /**
     *  Char values. 
     */
    TVIZ_CHAR,
    /**
     *  Short values. 
     */
    TVIZ_SHORT,
    /**
     *  Int values.
     */
    TVIZ_INT32
  };

  enum Encoding {
    /**
     *  File was written on a big endian machine. 
     */
    TVIZ_BIG_ENDIAN = 0,
    /**
     *  File was written on a little endian machine. 
     */
    TVIZ_LITTLE_ENDIAN
  };


  enum Condition {
	  /**
	   *  Value must be lower.
	   */
	  TVIZ_LOWER = 0,
	  /**
	   *  Value must be lower or equal.
	   */
	  TVIZ_LOWER_OR_EQUAL,
	  /**
	   *  Value must be equal.
	   */
	  TVIZ_EQUAL,
    /**
	   *  Value must be greater.
	   */
	  TVIZ_GREATER,
    /**
	   *  Value must be greater or equal.
	   */
	  TVIZ_GREATER_OR_EQUAL
  };



  /**
   * Destructor.
   */
  virtual ~SbTVizData(){};
  /**
   * Returns the altitude of the given 2D point (ground).
   */
  virtual float getValue(const SbVec2d& point) const = 0;
  /**
   * Returns the average altitude of the data.
   */
  virtual float getAvgValue() const = 0;
  /**
   * Returns the maximum altitude of the data.
   */
  virtual float getMaxValue() const = 0;
  /**
   * Returns the minimum altitude of the data.
   */
  virtual float getMinValue() const = 0;
  /**
   * Returns the file name.
   */
  const SbString& getFileName() const;
  /**
   * Returns the size in 3D coordinates.
   */
  const SbVec3d&  getSize() const;
  /**
   * Returns the offset in 3D coordinates. The offset is set in
   * the XML terrain file or using #SbTVizRegularGridData::loadDataFile.
   */
  const SbVec3d&  getOffset() const;

	/**
	 * Sets the value and condition to manage holes.
	 */
  void setHoleValue(float value, Condition cond);
	/**
	 * Gets the value and condition to manage holes.
	 */
  float getHoleValue(Condition& cond) const;

	/**
	 * Sets the precision factor used for hole contouring.
   * Factor ranges from 0. (very poor quality) to 1. for best quality.
   * Default value is 1.
	 */
  void setHoleEdgePrecision(float holeRez);
	/**
	 * Gets the precision factor used for hole contouring.
   * Factor ranges from 0. (very poor quality) to 1. for best quality.
   * Default value is 1.
	 */
  float getHoleEdgePrecision() const;

  /**
   * Returns the type of the data (UCHAR, USHORT, FLOAT,...).
   */
  DataType getDataType() const;
  /**
   * Returns the file open mode (UNKNOWN, ASCII, BINARY). Used only with XML files.
   */
  OpenMode getOpenMode() const;
  /**
   * Returns the file encoding (BIG_ENDIAN, LITTLE_ENDIAN). Used only with XML files.
   */
  Encoding getEncoding() const;
  /**
   * Writes altitude data to a .dat file (ASCII or BINARY)
   */
  virtual SbBool writeDataFile(const SbString& filename, OpenMode mode) = 0;

 SoINTERNAL public:
  float getRange() const;
  float getTypicalRange() const;
  float getTypicalMinHeight() const;
  float getTypicalMaxHeight() const;
  float getTypeRange() const;

  virtual SbBool isOfType(SbString& className) const = 0;

  virtual ZType getZValue(SbVec2i32 coord) const = 0;
  virtual float getModellingZValue(SbVec2i32 coord) const = 0;

  // Holes
  enum holeStatus {
    HOLE_OUT,
    HOLE_INTERSECT,
    HOLE_IN
  };

  SbBool      hasHoles() const {return holeFlag;}
  
  SbBool      isInHole(ZType v0) const;
  holeStatus  isInHole(ZType v0, ZType v1, ZType v2) const;

  SbVec2s& getStretchedSize() { return stretchedSize; }

 protected:
  SbTVizData(){};

  SbBool    holeFlag;
  float     avgValue;
  float     maxValue;
  float     minValue;
  SbString  fileName;
  SbVec3d   offset;
  Encoding  encoding;
  OpenMode  openMode;
  DataType  dataType;
  float     range;
  SbVec3d   size;
  float     holeValue;
  float     holeRez;
  Condition holeCondition;
  SbVec2s   stretchedSize;

  // Typical values are values covered by the data.
  float     typicalRange;
  float     typicalMinHeight;
  float     typicalMaxHeight;

  // typeRange is the range covered by the type (char, float...) 
  // of the data (rough value from the given file/array).
  float     typeRange;
  
};

#endif
