/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (Apr 2003)
**=======================================================================*/

#ifndef  _SOMESHGEOMETRYCONVERTER_H
#define  _SOMESHGEOMETRYCONVERTER_H

#include <LDM/converters/SoConverter.h>
#include <LDM/converters/SoConverterParameters.h>

class SoVolumeReader;
class SoMeshToiTile;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * @RVEXT ReservoirViz geometry file converter.
 * 
 * @ingroup ReservoirVizConverters
 * 
 * @DESCRIPTION
 *   This class converts a file containing the geometry of a mesh into an LDM file.
 *   The resulting LDM file is used by ReservoirViz each time part 
 *   of the mesh geometry must be loaded (for rendering, picking ...).
 *   The path to the LDM file must be specified in the #filename field of 
 *   an SoMeshGeometry node.
 *
 *   The conversion process is done using the convert() method inherited from 
 *   SoConverter.
 *
 * @SEE_ALSO
 *    SoConverter
 * 
 * 
 */ 
class RESERVOIRVIZ_API SoMeshGeometryConverter : public SoConverter
{

public:
 /**
   * Constructor.
   */
  SoMeshGeometryConverter(SbBool isClient = FALSE);

  /**
   * Destructor.
   */
  virtual ~SoMeshGeometryConverter();

  /**
  * Called before reading the file. If the return value is NULL, a reader by default 
  * will be used according to the extension of the file. 
  *
  * Returns the custom reader associated with the specified filename and extension. 
  * Returns NULL by default, meaning that SoMeshGeometryConverter is configured to run
  * with a predefined reader, not a custom one. The method must be overridden in a 
  * derived class to return a user-defined custom reader.
  * @param filename part of the filename without extension.
  * @param fileExt part of the filename after the last '.'
  */
  virtual SoVolumeReader* getReader( const SbString& filename, const SbString& fileExt ); 


SoINTERNAL public:
  static SbBox3f computeTileGeomBbox(int num_data_per_cell, SbBox3i32 &subtile_logic_bounds, 
                                const SbVec3i32 &tile_dim, const float *first_coord);
  static SbVec3f computeTileCenter(int num_data_per_cell, SbBox3i32 &subtile_logic_bounds, const SbVec3i32 &tile_dim, 
                               const float *tile_coord);

  // Browse data to detect if the tile can be shrink
  // Note : ReservoirViz does not shrink all tile 
  // systematically since the fault support has been added
  virtual bool isTileShrinkable( int tileId, SbVec3i32 tileOrigin, void *data );

  // Use the internal map to tell if a tile is shrinkable or not
  bool isTileShrinkable(int tileId);

  // Translate all the data contained in one SoMeshToiTile into 
  // a void* pointer
  virtual void toiTileToRaw(int &neededSize, char* dataPtr = NULL );
 
  // Clean the list contained in the instanciated meshToiTile 
  virtual void cleanMeshToiTile();

  virtual void setUncompressedSize(int fileTileIndex, int64_t size);

  virtual int64_t getUncompressedSize(int fileTileIndex);

  // Retrieve the pointer on the ToiTile object
  SoMeshToiTile* getToiTile();

protected:
  /////////////////////// func to define /////////////////
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data ) ;
  virtual int getRange( double & rangeMin, double & rangeMax);

  // return the size of a shrinked tile
  virtual int getTileSize() const; 

  //error returned : 0 = ok, 1 = pb = return
  virtual SbBox3f getSize(int& error) ;
  virtual std::vector<SoDataSet::DatumElement> getDatum(int& error) ;
  virtual SbVec3i32 getDimension(int& error) ;
  
  virtual size_t shrinkTile(int dataSize, void *data); 
  void unShrinkTile(const void* shrinkTileData, std::vector<float>& unShrinkTileData);

  void sampleTile( const SbVec3i32& tileDim, int border, 
                   const void* const octantTile[8], 
                   const int octantExists[8], 
                   void *parentTile );


  void sampleShrinkedTile( const SbVec3i32& tileDim, int border,
                           const void* const octantTile[8], 
                           const int octantExists[8], 
                           void *parentTile );

  void sampleUnShrinkedTile( const SbVec3i32& tileDim, int border,
                             const void* const octantTile[8], 
                             const int octantExists[8], 
                             void *parentTile );

  virtual void  outputHeader( FILE* );
  virtual void  outputTileBefore( int fileTileIndex, int dataSize, void *data, bool dataInverted );
  virtual void  startConversion();
  virtual void  endConversion();

  virtual void outputDataType(FILE* headerFile);

  virtual bool updateDataFile();

  // Return the size of data added at the beginning of the file
  // by the specific need of this converter
  // Offset returned can be aligned (for SiFileManage compatibility) or not
  // (for array browsing for example)
  virtual int getSpecificOffset( bool aligned = true );

  //////////////////////////////////////////////////////

  // Simply return the status of the last read tile
  virtual bool isTileShrinkable() { return m_isLastTileShrinkable; }            

private:

  // Use a map to store the state of each tile of the volume
  // bool = true  --> tile has been shrinked
  // bool = false --> tile is a TOI tile
  // The int is the tile Id
  typedef std::map<int, bool> t_tileStateList;
  typedef std::map<int, int64_t> t_tileSizeList;


  void instanciateReader(SoConverter::ConverterError& error);
  int getVertexIdInUnshrinkCell( const int i , const int j , const int k ) const;
  int getVertexIdInShrinkCell( int cellVertex, const int i , const int j , const int k) const;
  int getGridCellStateOffset();
  int getTileStateOffset();
  int getTileSizeOffset();
  int getNumberOfTile();

  // return the number of float of a non-shrinked tile (8 vtx per cell)
  size_t getUnShrinkedTileSize();
  size_t getShrinkedTileSize();

  SoVolumeReader* m_reader;

  SbString m_bbxFilename;
  void *m_bbxFile;
  std::vector<float> m_tileCell8VtxBuffer; // buffer containing a not shrunk tile (8 vertex per cell)
  std::vector<float> m_tileBuffer; // buffer for either a shrink or a non shrink buffer
  std::vector<float> m_unShrinkedOctant[8];

  t_tileStateList m_tileStateList;
  t_tileSizeList m_tileSizeList;
  SoMeshToiTile* m_meshToiTile;
  bool m_isLastTileShrinkable;

};

//-----------------------------------------------------------------------------
inline size_t
SoMeshGeometryConverter::getUnShrinkedTileSize()
{
  return (m_parameters->getTileDim()[0]) * (m_parameters->getTileDim()[1]) * (m_parameters->getTileDim()[2]) * 8 * 3;
}

//-----------------------------------------------------------------------------
inline size_t
SoMeshGeometryConverter::getShrinkedTileSize()
{
  return (m_parameters->getTileDim()[0]+1) * (m_parameters->getTileDim()[1]+1) * (m_parameters->getTileDim()[2]+1) * 3;
}

//-----------------------------------------------------------------------------
inline int
SoMeshGeometryConverter::getRange( double & , double & ) 
{
  // return error as there is no meaning in resviz, (3 coord range...)
  return 1;
}

inline SoMeshToiTile*
SoMeshGeometryConverter::getToiTile()
{
  return m_meshToiTile;
}

inline void
SoMeshGeometryConverter::setUncompressedSize(int fileTileIndex, int64_t size)
{
  m_tileSizeList[fileTileIndex] = size;
}

inline int64_t
SoMeshGeometryConverter::getUncompressedSize(int fileTileIndex)
{
  return m_tileSizeList[fileTileIndex];
}


#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SOMESHGEOMETRYCONVERTER_H
