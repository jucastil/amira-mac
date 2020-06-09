/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  SOECLIPSEGRIDREADER_H
#define  SOECLIPSEGRIDREADER_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <ReservoirViz/readers/SoEclipseBaseReader.h>

class SoEclipseRecord;

/**
 * @RVEXT Eclipse grid file reader.
 * 
 * @DESCRIPTION
 *
 * Reader of Eclipse grid file (extension ".grid").
 * This class is used by the geometry converter (see SoMeshGeometryConverter) to 
 * read the geometry of mesh defined in the Eclipse ".grid" file.
 * 
 * The class implements the virtual method getSubSlice by reading the 
 * COORDS records of the ".grid" file. 
 *  
 * 
 */
class RESERVOIRVIZ_API SoEclipseGridReader :
  public
  SoEclipseBaseReader
{

  SO_FIELDCONTAINER_HEADER(SoEclipseGridReader);

  // ----------------------- Public usage --------------------------------------
public:
  /**
   * Constructor.
   */
  SoEclipseGridReader();

  /**
   * Returns the characteristics of the .grid file
   */
  virtual ReadError getDataChar( SbBox3f& size, SoDataSet::DataType& type, SbVec3i32& dim );

  /**
   * Reads a subslice in the ".grid" file. Returns in the data argument a matrix of 
   * cell coordinates.
   */
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void* data );

  /**
   * Read and output each record of the given file.
   */
  friend std::ostream& operator <<(std::ostream& os, const SoEclipseGridReader& _this);

SoINTERNAL public:
  /*
   * Read and get coord of one corners.
   */
  const float* getCorner( int i, int j, int k ) const;

  /*
   * Seek the file for the position of COORD record which have index(i,j,k)
   */
  void seekFileToCoordRecord(int i, int j, int k ) const;

  /*
   * Retrieve the pointer to the cell state grid
   */
  virtual uint8_t* getCellGridState();

  /*
   * Retrieve the number of cell in the volume
   */
  virtual int getNbCell();

  // ----------------------- Protected usage -------------------------------------
protected:
  /**
   * Destructor.
   */
  virtual ~SoEclipseGridReader();

  // get the pos of cell ijk when the file' cell are ordered with i index increasing fastest
  int64_t getIjkIndex( int i, int j, int k ) const;
  // get the pos of cell ijk when the file' cell are ordered with j index increasing fastest
  int64_t getJkiIndex( int i, int j, int k ) const;
  // get the pos of cell ijk when the file' cell are ordered with k index increasing fastest
  int64_t getKijIndex( int i, int j, int k ) const;
  
  /*
   * Read and get coord of num_corner successive corners. 
   * Only 1 seek is done. 
   * Must be used when first index (i) of corners are increasing fastest.
   */
  void getCornerRowI(int ic, int jc, int kc, int numi, float *data) const;

  /*
   * Read and get coord of successive corners. 
   * Only 1 seek is done. 
   * Must be used when second index (j) of corners are increasing fastest.
   */
  void getCornerRowJ(int ic, int jc, int kc, int numj, int deltai, float *data) const;

  /*
   * Returns true if the volume contains at least one dead cell
   * false otherwise
  */
  virtual bool hasDeadCell();

  void setLastRecordNbData(int nbData) const;
  int getLastRecordNbData();

  // seek pos of the first record of type COORDS (keyword = COORDS)
  int64_t m_firstCoordRecordPos;
  // size of first record COORDS
  int64_t m_coordsRecordSize;
  // size of first record CORNERS
  int64_t m_cornersRecordSize;

  // define in which order the cell (corner) are ordered in the grid file
  // 0 : i-index increased first, then j-index, then k-index
  // 1 : j-index increased first, then k-index, then i-index
  // 2 : k-index increased first, then i-index, then j-index
  int m_cellOrder;

  mutable SoEclipseRecord* m_record;

  // FS_EclipseReader_DeadCell
  int m_iNbCell;                    // Nb cell in the volume
  uint8_t* m_cellStateGrid;         // Grid to store state of each cell (active/dead)
  mutable bool m_bHasDeadCell;      // global field to know if vol contains dead cell or not
  mutable int m_iIndexInStateGrid;
  mutable int m_iLastRecordNbData;

};

// ----------------------- inline definitions -------------------------------- 
inline int64_t
SoEclipseGridReader::getIjkIndex( int i, int j, int k ) const
{
  return int64_t(k) * (m_gridDimI * m_gridDimJ) + int64_t(j) * m_gridDimI + int64_t(i);
}

inline int64_t
SoEclipseGridReader::getJkiIndex( int i, int j, int k ) const
{
  return int64_t(i) * (m_gridDimJ * m_gridDimK) + int64_t(k) * m_gridDimJ + int64_t(j);
}

inline int64_t
SoEclipseGridReader::getKijIndex( int i, int j, int k ) const
{
  return int64_t(j) * (m_gridDimK * m_gridDimI) + int64_t(i) * m_gridDimK + int64_t(k);
}

inline bool
SoEclipseGridReader::hasDeadCell()
{
  return m_bHasDeadCell;
}

inline uint8_t*
SoEclipseGridReader::getCellGridState()
{
  return m_cellStateGrid;
}

inline int
SoEclipseGridReader::getNbCell()
{
  return m_iNbCell;
}

inline std::ostream& 
operator <<(std::ostream& os, const SoEclipseGridReader& _this)
{
  return _this.operator_out(os); 
}

inline void
SoEclipseGridReader::setLastRecordNbData(int nbData) const
{
  m_iLastRecordNbData = nbData; 
}
 
inline int
SoEclipseGridReader::getLastRecordNbData()
{
  return m_iLastRecordNbData; 
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SOECLIPSEGRIDREADER_H
