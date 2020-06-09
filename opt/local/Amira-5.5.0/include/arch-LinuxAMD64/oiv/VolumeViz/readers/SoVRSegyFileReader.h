/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G. SEGUIN (Oct 2001)
**=======================================================================*/
#ifndef  _SO_VR_SEGY_FILE_READER_
#define  _SO_VR_SEGY_FILE_READER_

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/readers/SoVRSegyReader.h>
#include <Inventor/STL/vector>
#include <VolumeViz/nodes/SoVolumeData.h>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#pragma warning(disable:4996)
#endif

/**
 * @VREXT SEGY file format reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * 
 * Reader for SEGY files (SEG Y revision 1).
 * The following data types are supported: unsigned or signed byte, short, int32,
 * and float.
 *
 * SEGY is a widely used format for storing seismic trace data, defined by
 * the Society of Exploration Geophysicists publication "Digital Tape
 * Standards" (http://www.seg.org). The VolumeViz reader supports
 * all sizes of integer and float data, and can correctly determine the number
 * of samples per trace in most cases.
 * 
 * The data will be mapped to the Open Inventor axes as follows:
 * - The trace length is mapped onto the Inventor X axis (trace).
 * - The number of trace sensors per line is mapped onto the Inventor Y axis (inlines).
 * - Z is the number of lines (crosslines).
 *
 * Although in most cases the SEGY reader can automatically detect if the
 * number of traces per line in a SEGY file is not uniform, in some cases it
 * cannot. You can set environment variable
 * IVVR_IRREGULAR_TRACE_NUM to request the use of a more sophisticated file parsing algorithm.
 * However, be aware that the initialization for file reading will take longer when
 * this environment variable is set.  Missing data is assigned the value zero.
 * 
 * Although in most cases the SEGY reader can automatically detect if the
 * length of traces in a SEGY data file is not uniform, in some cases it cannot.
 * You can set environment variable
 * IVVR_INCONSTANT_TRACE_LENGTH to request the use of a more sophisticated file parsing algorithm.
 * However, be aware that the initialization for file reading will take significantly
 * longer when this environment variable is set.  Missing data is assigned the value zero.
 *
 * In most cases the SEGY reader can automatically detect if the values in the
 * file need to be "byte swapped", for example if the data was written on a
 * "big-endian" machine (e.g., SPARC) and is being read on a "little-endian"
 * machine (e.g., Intel).  If necessary you can force byte swapping on or off
 * using the environment variable IVVR_SEGY_SWAPBYTES.
 *
 * A value of 1 in the format field of the SEGY header normally means that the data
 * values were written in IBM floating point format.  But in some cases the
 * values were actually written in IEEE floating point format (which should be
 * indicated by format = 5). Normally the SEGY reader is able to detect this,
 * but if necessary you can specify that float values are in IEEE format
 * by setting environment variable IVVR_SEGY_FLOATISIEEE.
 *
 * If the SEGY reader fails to read the file correctly, you can set the following environment
 * variables:
 * - IVVR_SEGY_DEBUG=1
 *   This outputs information of what the reader is actually doing.
 * - IVVR_SEGY_DUMP=filename
 *   This requests that some information of the file and trace headers be written 
 *   to the specified file while processing the SEGY data file.
 * All these information can be sent to the VSG support for assitance.
 *
 * Limitations:
 * In some circontances few first traces might be skipped, typically when the first line contains
 * only one trace (this trace might be skipped).
 * In such a case a message warns the application of how many traces are actually skipped (throught SoDebugError).
 *
 * See SoPreferences for information on using environment variables. 
 * 
 * 
 */
class VOLUMEVIZ_API SoVRSegyFileReader : public SoVolumeReader  
{
  SO_FIELDCONTAINER_HEADER(SoVRSegyFileReader);

 public:
  /**
   * Constructor. 
   */
  SoVRSegyFileReader();

  /**
   * Gets the characteristics (file header) of the data volume. See SoVolumeData.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,	SbVec3i32 &dim );

  #ifdef OIV_NET_DOC
 /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory referenced by @B data@b.
   * Slices will not always be read sequentially.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
 #else
  /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory pointed to by @B data@b.
   * Slices will not always be read sequentially.
   */
#endif
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

  /**
   * Sets whether or not the reader should automatically try to detect if the coordinate system
   * used is direct (right-handed) or not.
   * Default is FALSE.
   */
  virtual SbBool setDirectCoordSysAutoDetection(SbBool autoValue);
 
  /**
   * If TRUE, the volume size (bounds in world coordinates) is set to 0 to dimension-1
   * on each axis. Else the volume size is normalized to fit inside a unit cube centered
   * at the origin. In other words, the size will be -.5 to +.5 along the longest dimension. 
   * FALSE by default. The application can also set the volume size to whatever is appropriate
   * using SoVolumeData::setVolumeSize().
   */
  static void setVolumeSizeVoxels(SbBool flag);

  /**
   * Returns the reader type, in this case, the enum value SoVolumeReader::SEGY.
   */
  virtual ReaderType getReaderType ()
  {return SEGY;};


  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 0
  //

  /**
   * Specifies the path of the file. Returns 0 for success. Any other return
   * value indicates failure.
   */
  virtual int setFilename( const SbString& filename );

  /** SoSegyScanningCB return code */
  enum SegyScanningResp {
     SCAN_CONTINUE,
     SCAN_ABORT
  };

  /**
   * SoSegyScanningCB Callback type
   */
  typedef SegyScanningResp SoSegyScanningCB( void *data, float percent, SoVRSegyFileReader *reader );

  /**
   * Sets a progress callback when the SEGY file is scanned.
   * The SEGY file is scanned when:
   *  - 1 - The trace header or the trace data is requested, if the trace length is not constant
   *  - 2 - The Inline/Crossline/Z ranges are requested 
   *        (see #getInlineRange, #getCrosslineRange, #getZRange)
   *  - 3 - The P1, P2 and P3 coordinates are requested (see #getP1P2P3Coordinates)
   */
  void setScanningProgressCallback( SoSegyScanningCB *func, void *data );

  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 1
  //

  /**
   * Tells whether the textual header format is ASCII or not.
   * The default value is false, i.e., the textual header format is EBCDIC
   */
	virtual void setSegyTextHeaderAscii( bool ascii );

  /**
   * Retreives the textual header (the first 3200-bytes) of the SEGY file.
   */
	virtual SbString getSegyTextHeader();

  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 2
  //

  /** Segy byte order mode */
  enum SegyByteOrder { 
    /** Little endian */
    SEGY_LITTLE_ENDIAN,
    /** Big endian */
    SEGY_BIG_ENDIAN
  };
  /**
   * Sets the byte ordering to use when reading the SEGY file.
   * The default value is SEGY_LITTLE_ENDIAN. In most cases, even
   * when the SEGY file is big endian, the SEGY file reader is
   * able to detect this and read the file accordingly. This method
   * is for the very rare case when the automatic byte order detection
   * fails. 
   */
  virtual void setSegyByteOrder( SegyByteOrder byteOrder );
  /**
   * Gets the byte ordering to use when reading the SEGY file.
   */
  virtual SegyByteOrder getSegyByteOrder();

  /**
   * Specifies the header used to read the SEGY file. If this method is called,
   * the reader uses the binary file header you pass rather than the actual binary file header.
   * The following fields from the binary file header are used:
   * - formatRevisionNumber
   * - numTextHeaderExt
   * - format
   * - fixedLengthTraceFlag
   * - hns (number of samples per trace)
   *
   * Returns FALSE if the operation fails, for example, if SoVolumeReader::setFilename() 
   * was not called first. 
   */
  virtual SbBool setSegyFileHeader( const SoVRSegyFileHeader &fileHeader );

  /** 
   * Gets the SEGY file header.
   * If you use this class to read a SEGY file directly, you will have to call 
   * the method SoVolumeReader::setFilename() first.
   * Returns FALSE if the operation fails, for example, if SoVolumeReader::setFilename()
   * was not called first.
   * If readFile is true the file header is read from the file anyway, otherwise the value
   * set by setSegyFileHeader() is returned instead.
   * If readFile is false and setSegyFileHeader() never called, the file header is read from
   * the file anyway.
   */
  virtual SbBool getSegyFileHeader( SoVRSegyFileHeader& fileHeader, bool readFile = false );

  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 3
  //

  /**
   *  Tells the file reader where the fields are actually located (i.e., the byte positions)
   *  within the trace header. Only the field SEGY_CDP is used (Xline position).
   */
  virtual void setSegyTraceHeaderBytePosition( const SoVRSegyTraceHeaderBytePosition &traceHeaderBytePosition );
  /**
   *  Gets the byte positions within the trace header.
   */
  virtual SoVRSegyTraceHeaderBytePosition getSegyTraceHeaderBytePosition();

  /**
   * Returns the number of traces.
   * If the file is not regular (see isSegyRegular()), an approximate 
   * number (considering it as regular) is returned (to avoid   
   * scanning the whole file).
   */
  virtual int getNumTraces();

  /** 
   * Gets the SEGY trace header of the given trace @B traceNumber @b.
   * @B traceNumber @b can range from zero to the number of traces minus one.
   * If you use this class to read a SEGY file directly, you will have to call 
   * the method SoVolumeReader::setFilename() first.
   * Returns FALSE if the operation fails, for example, if SoVolumeReader::setFilename()
   * was not called first.
   */
  virtual SbBool getSegyTraceHeader( int traceNumber, SoVRSegyTraceIdHeader& traceHeader );

  /**
   * Sets the trace header of a specific trace used to read the SEGY file [OPTIONAL].
   */
  //void setSegyTraceHeader(int traceNumber, SoVRSegyTraceIdHeader &traceHeader)
  //{;}

  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 4
  //

  /**
   * Indicates if SEGY file is regular.
   * A file with the same number of traces in each inline and with the same number of samples 
   * for each trace is considered as regular.
   */
  virtual SbBool isSegyRegular();

  /**
   * Sets the crossline range.
   */
  virtual void setCrosslineRange( int from, int to, int step );
  /**
   * Sets the inline range.
   */
  virtual void setInlineRange( int from, int to, int step );
  /**
   * Sets the Z (time axis) range.
   */
  virtual void setZRange( int from, int to, int step );
  /**
   * Gets the crossline range. This method returns the actual values from the
   * file if the corresponding set method has not been called previously.
   * Otherwise, the values previously specified with #setCrosslineRange are
   * returned.
   */
  virtual void getCrosslineRange( int &from, int &to, int &step );
  /**
   * Gets the inline range. This method returns the actual values from the
   * file if the corresponding set method has not been called previously.
   * Otherwise, the values previously specified with #setInlineRange are
   * returned.  @BR @BR
   * NOTE: If the inline values are incorrect in the file, or are not retrieved
   * correctly for any reason, getInlineRange returns (1, numLines, 1).
   */
  virtual void getInlineRange( int &from, int &to, int &step );
  /**
   * Gets the Z (time axis range. This method returns the actual values from the
   * file if the corresponding set method has not been called previously.
   * Otherwise, the values previously specified with #setZRange are
   * returned.
   */
  virtual void getZRange( int &from, int &to, int &step );

  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 5
  //

  /**
   * Gets the P1, P2, P3 and P4 coordinates.
   * P1, P2 are on the corners corresponding to the first line.
   * P4, P3 are on the corners corresponding to the last line.
   * If these points do not exist, the crossline and inline values are used instead.
   * Returns TRUE for a right-handed coordinate system (Xline/Inline/Time).
   */
  virtual SbBool getP1P2P3Coordinates( SbVec2d &P1, SbVec2d &P2, SbVec2d &P3, SbVec2d &P4 );

  /**
   * Specifies if the coordinate system used is direct (right-handed) or not.
   * Default is TRUE.  If the coordinate system is direct, then samples are stored
   * in increasing order along the positive X axis, traces are stored in increasing
   * order along the positive Y axis, and lines are stored in increasing order along
   * the positive Z axis.  If the coordinate system in indirect, everything is the
   * same except that lines are stored in decreasing order along the positive Z axis.
   * NOTE: If you pass the value returned by getP1P2P3Coordinates(), the resulting LDM file
   * will be always right handed.
   */
  virtual SbBool setDirectCoorSys( SbBool directCoord );

  /** SegY axis order mode */
  enum SegyAxisOrder {
    /** XYZ_AS_SAMPLE_INLINE_CROSSLINE */
    XYZ_AS_SAMPLE_INLINE_CROSSLINE,
    /** XYZ_AS_INLINE_CROSSLINE_SAMPLE */
    XYZ_AS_INLINE_CROSSLINE_SAMPLE
  };

  /**
   * Sets/gets the storage order for X, Y, and Z axis. @BR
   * For example, XYZ_AS_INLINE_CROSSLINE_SAMPLE means inlines as X, crosslines as Y, and samples as Z.
   * The default value is XYZ_AS_SAMPLE_INLINE_CROSSLINE.
   */
  virtual void setSegyAxisOrder( SegyAxisOrder axisOrder );
  virtual SegyAxisOrder getSegyAxisOrder();

  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 6
  //

  /** 
   * Gets the SEGY trace data of the specified trace @B traceNumber@b.
   * @B traceNumber @b can range from zero to the number of traces minus one.
   * If you want to get a subset of the data, specify the @B start @b position in 
   * the trace and the number of data values (@B size @b).
   * The return value is the number of data values read, or 0, if the operation failed.
   * 
   * If you use this class to read a SEGY file directly, you will have to call 
   * the method SoVolumeReader::setFilename() first. Additionally your application will be
   * responsible for releasing the memory afterward. Otherwise,VolumeViz will
   * release the memory.
   * 
   * This returns a pointer to an internal buffer, so if you want to call this method twice in order
   * to get two traces, copy the first trace into your own buffer before calling this method
   * for the second trace.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual int getSegyTraceData( int traceNumber, void* &traceData, int start = 0, int size = -1 );

  /*
   * Return the (X,Y) coordinates of trace(i,j).
   */
  bool getTraceCoord(const int i, const int j, SbVec2d & P );

  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // Reader Settings - Step 7
  //

  /** 
   * Requests that the input be converted (if necessary) to the specified data type.
   * This allows, for instance, conversion of float data to unsigned byte.
   * If doChange is FALSE no type conversion is applied.
   * Always returns TRUE.
   */
  virtual SbBool setOutputDataType( SbBool doChange, SoDataSet::DataType type );

  /** 
   * Requests that the input be converted from the specified range to the range depending on
   * the output data type.
   * This allows, for instance, if the output data type is unsigned byte, conversion of float data
   * from range [min,max] to range [0,255].
   * If doChange is FALSE no range conversion is applied.
   * Always returns TRUE.
   */
  virtual SbBool setInputDataRange( SbBool doChange, double min, double max );

  //
  // End Reader Settings
  ////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////

SoINTERNAL public:

  /*
   * Converts numValues IBM float values in IEEE float values into the same in/out buffer.
   */
  static void ibm2ieee( int numValues, void* ibm2ieeeBuffer );

  
  ////////////////////////////////////////////////////////////////////////////////////////////////
  // deprecated methods
  //

  /** @deprecated No longer used. Use setInputDataRange( SbBool doChange, double min, double max )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual SbBool setOutputDataRange( SbBool doChange, double min, double max )
  {
    return setInputDataRange( doChange, min, max );
  };

  /** @deprecated No longer used. Use getDataChar( SbBox3f& , SoDataSet::DataType &, SbVec3i32& )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED void getDataChar( SbBox3f &size, SoDataSet::DataType &type, SbVec3s &dim )
  {
    SbVec3i32 dimI32;
    getDataChar( size, type, dimI32 );
    dim.setValue( (short)dimI32[0], (short)dimI32[1], (short)dimI32[2] );
  };

  /** @deprecated No longer used. Use getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual void getSubSlice( const SbBox2s& subSlice, int sliceNumber, void * data )
  {
    SbBox2i32 subSliceI32( subSlice.getMin()[0], subSlice.getMin()[1], subSlice.getMax()[0], subSlice.getMax()[1] );
    getSubSlice( subSliceI32, sliceNumber, data );
  };

  //
  // end deprecated methods
  ////////////////////////////////////////////////////////////////////////////////////////////////

 protected:
  // settings parameters - step 0
  SoSegyScanningCB *m_scanningCBfunc;
  void             *m_scanningCBdata;

  // settings parameters - step 1
  bool m_textHeaderAscii;

  // settings parameters - step 2
  SegyByteOrder      m_byteOrder;
  bool               m_byteOrderSet;
  bool               m_swapBytes;     // True if we need to swap the bytes of headers
  bool               m_swapBytesData; // True if we need to swap the bytes of the data samples. Equal to m_swapBytes most of the cases.
  SoVRSegyFileHeader m_binHeader;
  bool               m_binHeaderSet;

  // settings parameters - step 3
  SoVRSegyTraceHeaderBytePosition m_trHdrBytePos;
  bool m_trHdrBytePosSet;

  // settings parameters - step 4
  bool m_crosslineRangeSet;
  int  m_crosslineFrom, m_crosslineTo, m_crosslineStep;
  bool m_inlineRangeSet;
  int  m_inlineFrom, m_inlineTo, m_inlineStep;
  bool m_zRangeSet;
  int  m_zFrom, m_zTo, m_zStep;

  // settings parameters - step 5
  SegyAxisOrder m_axisOrder;

  // settings parameters - step 7
  bool m_changeFormat;
  SoDataSet::DataType m_typeOut;
  bool m_dataRangeSet;
  double m_dataRangeMin, m_dataRangeMax;

  // getDataChar1
  SoVolumeReader::ReadError getDataChar1();
  bool m_dataChar1;
  SoVRSegyFileHeader m_wkHeader;
  int m_headerSize;
  int m_format;
  SbString m_typeStr;
  SoDataSet::DataType m_type;
  int m_bytesPerVoxel;
  bool m_constantTraceLength;
  unsigned int m_numSamplesPerTrace;
  unsigned int m_numTracesPerLine;
  unsigned int m_numLines;
  int64_t m_numTraces;

  // getDataChar2
  SoVolumeReader::ReadError getDataChar2(int t = -1);
  bool m_dataChar2;
  std::vector<int64_t> m_traceOffset;
  std::vector<int> m_traceLength;
  //int64_t m_numTraces;
  //unsigned int m_numSamplesPerTrace;
  SbVec3i32 m_dim; // [0]

  // getDataChar3
  SoVolumeReader::ReadError getDataChar3();
  bool m_dataChar3;
  bool m_regularTraceNum;
  //unsigned int m_numTracesPerLine;
  //unsigned int m_numLines;
  //SbVec3i32 m_dim; // [1][2]
  std::vector<int> m_lineTraceStart;
  std::vector<int> m_lineTraceMin;
  std::vector<int> m_lineTraceMax;

 private:
  using SoVolumeReader::getDataChar;
  using SoVolumeReader::getSubSlice;

  // True if format=1 in the file header means IEEE float format.
  // Officially 1 means IBM float format and 5 means IEEE.
  SbBool m_floatIsIEEE;
  static bool m_isVolumeSizeVoxels ;

  int  getTraceNum( const int, const int );
  void resetObject();
  bool searchForPoint( const int which, int & i, int & j, SbVec2d & P );
  void extrapolatePoint( SbVec2d & P0, int & i0, int & j0,
                         const SbVec2d & Px, int ix, int jx,
                         const SbVec2d & Py, int iy, int jy,
                         int newi0, int newj0 );
  float evaluateValuesValidity( const int num_values, const float *values );
  float evaluateValuesCorrelation( const int trace, const int format1, const bool swap1, const int format2, const bool swap2 );

};

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif // _SO_VR_SEGY_FILE_READER_
