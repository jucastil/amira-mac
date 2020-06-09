/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  SoEclipseBaseReader_H
#define  SoEclipseBaseReader_H

#include <Inventor/STL/string>

#include <LDM/readers/SoVolumeReader.h>

class SiBufferedFile;

/**
* @RVEXT Base class of the Eclipse file reader.
* 
* @DESCRIPTION
*   Base class of all the class used by the LDM converter to read 3 types
*   of Eclipse files : grid files, init files and restart files.
*  
* 
*/ 
class RESERVOIRVIZ_API SoEclipseBaseReader : public SoVolumeReader  
{
  SO_FIELDCONTAINER_HEADER(SoEclipseBaseReader);

  // ----------------------- Public usage --------------------------------------
public:
  enum DataType
  {
    INTE,
    REAL,
    LOGI,
    DOUB,
    STRING
  };

  /**
   * Constructor.
   */
  SoEclipseBaseReader();

  /**
   * Stores the filename. 
   */
  virtual int setFilename(const SbString& filename);

  /**
  * Specifes the size (in megabytes) of the buffer used to read in the Eclipse file.
  * If bufferSize = 0, no buffer is used.
  * 8 MB by default.
  */
  void setBufferSize(int bufferSize);

  /*
   *  Note: SoEclipseBaseReader does not implement these methods.
   */
  /** [OIV-WRAPPER-CUSTOM-CODE] */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim );
  /** [OIV-WRAPPER-CUSTOM-CODE] */
  void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

  /**
  * Reads and outputs each record of the specified file.
  */
  std::ostream& operator_out(std::ostream& os) const;

  // ----------------------- Protected usage -------------------------------------
protected:
  /**
   * Destructor.
   */
  virtual ~SoEclipseBaseReader();

  SiBufferedFile* getFileBuffer() const;

  SbString m_eclipseFilename;

  // dimension of the grid
  int32_t m_gridDimI;
  int32_t m_gridDimJ;
  int32_t m_gridDimK;

private:

  SiBufferedFile*   newFileBuffer() const;
  
  mutable SiBufferedFile*   m_fileBuffer;
  mutable void*             m_fileD;
  int                       m_bufferSize;

};


// ----------------------- inline definitions -------------------------------- 
inline int 
SoEclipseBaseReader::setFilename( const SbString& filename )
{
  m_eclipseFilename = filename;
  return 0;
}

inline void 
SoEclipseBaseReader::setBufferSize(int bufferSize)
{
  m_bufferSize = bufferSize;
}

inline SiBufferedFile* 
SoEclipseBaseReader::getFileBuffer() const
{
  if (m_fileBuffer == NULL)
    m_fileBuffer = newFileBuffer(); 
  return m_fileBuffer;
}


inline SoEclipseBaseReader::ReadError
SoEclipseBaseReader::getDataChar( SbBox3f &, SoDataSet::DataType &,  SbVec3i32 &)
{
  return RD_NO_ERROR;
}

inline void 
SoEclipseBaseReader::getSubSlice( const SbBox2i32& , int , void *)
{}

#endif // SoEclipseBaseReader_H
