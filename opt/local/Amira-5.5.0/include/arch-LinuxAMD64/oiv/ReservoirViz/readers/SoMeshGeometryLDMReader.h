/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J. Hummel (May 2006)
**=======================================================================*/
#ifndef  _SOMESHGEOMETRYLDMREADER_H
#define  _SOMESHGEOMETRYLDMREADER_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/STL/string>
#include <LDM/readers/SoLDMReader.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/STL/vector>
class SbThreadMutex;
class SiBitFile;


/**
 * @RVEXT ReservoirViz LDM file reader.
 *
 * @ingroup ReservoirVizReaders
 *
 * @DESCRIPTION
 *
 * @SEE_ALSO
 *    SoLDMReader
 *
 *
 */
class RESERVOIRVIZ_API SoMeshGeometryLDMReader : public SoLDMReader
{
  SO_FIELDCONTAINER_HEADER(SoMeshGeometryLDMReader);

 public:
  /** Default Constructor. */
  SoMeshGeometryLDMReader();

  /**
   * Returns the geometric bounding box of the specified tile.
   * The fileID is the sequential index of the tile in the LDM file.
   * Returns FALSE if not supported.
   */
  virtual SbBool getBbox(int fileId, SbBox3f& box);
  /**
   * Returns the logical center of the specified tile. The fileID is the sequential
   * index of the tile in the LDM file.
   * The logical center is the geometric center of the middle cell of the tile.
   * For instance, for a tile size = 32, returns the geometric center of the cell[16][16][16].
   * Returns FALSE if not supported.
   */
  virtual SbBool getCenter(int fileId, SbVec3f& center);

  SoINTERNAL public:
  /**
  * Returns true if the given tile does not contain faults.
  */
  virtual bool isTileShrinked(int tileId);

  /**
  * Returns true if the mesh contain dead cells.
  */
  virtual bool hasDeadCell() { return m_bHasDeadCell; }

  /**
  * Returns true if the given cell is marked as dead (inactive). Dead cells are not displayed.
  */
  virtual bool isDead(int i,int j,int k);

  /**
  * Returns true if the mesh contains faults.
  */
  virtual bool hasFaults() { return m_bHasFaults; }

  virtual uint8_t* getCellGridState() { return m_uiDeadCellGrid ; };

  virtual SoBufferObject* readTile(int index, const SbBox3i32& tilePosition);

  virtual uint64_t getTileSizeFromFid(int fileId);

  virtual bool doesTileHaveDeadCells(int i,int j,int k);

  /**
  * Should return TRUE if the reader is thread safe. @BR
  * This function is called by VolumeViz when using the multiIO mode (LDM only).
  * LDM multi-threaded data loading can only be used if this method returns TRUE.
  */
  virtual SbBool isThreadSafe() const;

protected:
  /** Destructor. */
  virtual ~SoMeshGeometryLDMReader();

  virtual int handleHeader(TiXmlElement *);
  void releaseHandler();
  virtual int getSpecificOffset(bool aligned = true);
  virtual bool isSpecificHeaderRead();
  virtual void readSpecificHeader(FILE* file);

  void buildTileDeadCellState();
  bool tileHasDeadCell(int tileI,int tileJ,int tileK);
  int ijk2i(int i, int j, int k);
  bool findDeadCellInTile(int indI,int indJ,int indK);

  int    m_numBBoxes;
  float *m_bBoxes;

private:

  // Use a map to store the state of each tile of the volume
  // bool = true  --> tile has been shrinked
  // bool = false --> tile is a TOI tile
  // The int is the tile Id
  typedef std::map<int, bool> t_tileStateList;
  typedef std::map<int, int64_t> t_tileSizeList;

  void internalInit();
  void buildTileStateGrid( uint8_t* tmp );
  void buildTileSizeGrid( uint8_t* tmp );
  int  getNumberOfTile();
  int getGridCellStateOffset();
  int getTileStateOffset();

  bool m_bHasDeadCell; // Volume contains dead cell or not
  int m_iReadOffset;   // Offset to read beyond the cell state grid
  bool m_bSpecificHeaderRead;
  uint8_t* m_uiDeadCellGrid;
  bool m_bHasFaults;
  t_tileStateList m_tileStateList;
  t_tileSizeList m_tileSizeList;
  std::vector<bool> m_tileHasDeadCell;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

inline int
SoMeshGeometryLDMReader::getSpecificOffset( bool aligned )
{
  if ( aligned )
    return SbMathHelper::alignToNextPowerOf2(m_iReadOffset, 9);

  return m_iReadOffset;
}

inline bool
SoMeshGeometryLDMReader::isSpecificHeaderRead()
{
  return m_bSpecificHeaderRead;
}

#endif // _SOMESHGEOMETRYLDMREADER_H

