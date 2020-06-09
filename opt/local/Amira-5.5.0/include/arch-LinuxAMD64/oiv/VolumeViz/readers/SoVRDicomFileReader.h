/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : L.Taboni (Apr 2004)
**=======================================================================*/
#ifndef  _SO_VR_DICOM_FILE_READER_
#define  _SO_VR_DICOM_FILE_READER_

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <LDM/readers/SoVolumeReader.h>
#include <VolumeViz/readers/SoVRDicomData.h>
#include <VolumeViz/nodes/SoVolumeData.h>


SoINTERNAL class SiDicomSlice;
/**
 * @VREXT DICOM file reader.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * 
 *  Volume reader for DICOM file formats. 
 * 
 *  DICOM is a widely used format for storing medical image data (CT, MRI, etc),
 *  defined by the National Electrical Manufacturers Association (NEMA)
 *  (http://medical.nema.org).
 *
 *  Can load data from a single DICOM file or a list of DICOM files (see setFilename()).
 *
 *  Can optionally convert the input data to a different type, for example from
 *  float to unsigned byte (see setOutputDataType()).
 */ 

 class VOLUMEVIZ_API SoVRDicomFileReader : public SoVolumeReader  
 {

   SO_FIELDCONTAINER_HEADER(SoVRDicomFileReader);

 public:
  /** Constructor. */
  SoVRDicomFileReader ();

 /**
  * Specify the name of a DICOM file or a file containing the list of DICOM 
  * files to load, one filename per line.  If the filenames do not contain
  * any slash or backslash characters, the files are assumed to be in the
  * same directory as the list file.
  */
  virtual int setFilename( const SbString& filename );

  /**
   * Gets the characteristics (file header) of the data volume. See SoVolumeData.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual ReadError getDataChar (SbBox3f &size, SoDataSet::DataType &type, SbVec3i32 &dim);

  /** 
   * Requests that the input be converted (if necessary) to the specified data type.
   * This allows, for instance, conversion of float data to unsigned byte.
   * By default no conversion is done. If @I doChange@i is FALSE no type conversion is done.
   * Always returns TRUE.
   */
  virtual SbBool setOutputDataType( SbBool doChange, SoDataSet::DataType type );


  #ifdef OIV_NET_DOC
 /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory referenced by @B data@b.
   * Slices will not always be read sequentially.
   */
 #else
  /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory pointed to by @B data@b.
   * Slices will not always be read sequentially.
   */
#endif
  virtual void getSubSlice (const SbBox2i32 &subSlice, int sliceNumber, void *data);

  /** 
   * This method is optional. It returns the number of significant bits of the volume data.
   *
   * If it is not implemented, the default return value is 0, meaning the number of bits
   * depends on the data type. See the last parameter of SoVolumeData::setVolumeData().
   * This method is called immediately after #getDataChar().
   */
  int getNumSignificantBits();

  /**
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()
  {return DICOM;};

 protected:

  /** Destructor. */
  virtual ~SoVRDicomFileReader ();


private:

  void release();
  int extractFileList (const SbString& headFile);
  SbBool isSupported ();
  SbBool accept (SoVRDicomData &dicomData);
  void adjustHighBit (void *buffer, int highBit, int numElements);
  void adjustDataRange (void *buffer, int numElements);
  void extractSlices (SoVRDicomData &dicomData, int fileNumber, int &begin);
  void addSlice (SiDicomSlice *slice);
  

private:

  SbBox3f   m_size;
  SbVec3i32 m_dim;
  SoDataSet::DataType m_type;
   
  int m_sizeInBytes;
  int m_bytesPerVoxel;
  SbBool m_dataSigned;
  SbBool m_adjustData;
  float m_rescaleIntercept;
  float m_rescaleSlope;
  int m_highBit;
  std::vector<SbString> m_fileList;
  
  SoVRDicomData m_dicomDataRef;
  std::vector<SiDicomSlice *> m_slices;

  bool m_changeFormat;
  SoDataSet::DataType m_typeOut;
};

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif /* _SO_VR_DICOM_FILE_READER_ */
