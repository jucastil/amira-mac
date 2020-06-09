/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T. DUFOUR (May 2005)
**=======================================================================*/

#ifndef  _SO_LDM_TOPO_OCTREE_
#define  _SO_LDM_TOPO_OCTREE_

#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <LDM/SoLDMTileID.h>

class SoLDMOctreeNode;


#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

// Note : this level will be never reached (at least this century!)
#define LEVEL_MAX 20

/**
 * @LDMEXT Octree topology queries
 *
 * @ingroup LDMKernel
 *
 * @DESCRIPTION
 *
 * The SoLDMTopoOctree class provides information about the hierarchy of
 * LDM tiles used for a given dataset, based on the dataset dimensions.
 *
 * For example you can query the total number of LDM tiles in the data set.
 * You can also query the ID of the tile that
 * contains a specified voxel/cell in the data set and conversely you can query
 * the extent of a specified tile in voxel/cell coordinates.
 *
 * In VolumeViz LDM every tile has both a tileID and a fileID.  The tileID is
 * the unique identifier of a tile in the (conceptual) complete, symmetrical
 * hierarchy.  The fileID is the index of a tile in a sequential numbering of
 * all the tiles that actually contain data.  The tileID is normally used to
 * identify tiles in an application, but the fileID is used, for example, when
 * calling the readTile method in an SoVolumeReader class.  In a cubical volume
 * (all three dimensions the same), there are equal numbers of tileIDs and
 * fileIDs, but in most volumes there are many fewer fileIDs than tileIDs.
 *
 * @SEE_ALSO
 * SoLDMTileID
 *
 *
 */

class LDM_API SoLDMTopoOctree
{

public:

  /**
   * Constructor.
   */
  SoLDMTopoOctree();

  /**
   * Initialize with the properties of the data set
   */
  void init( const SbVec3i32& dimension, const int tileDim, const int border );

  /**
   * Returns the bounding box, in voxel/cell coordinates, of the specified tile.
   */
  SbBox3i32 getTilePos( const SoLDMTileID& tileID )const;

  /**
   * Given the position of a voxel/cell (i,j,k) and the resolution level,
   * returns the tile ID of the corresponding tile.
   *
   * Note: When tile overlap > 0, overlap voxels are contained in more than one
   * tile.  For example if tile size is 64 and tile overlap is 1, then the first
   * tile contains voxels 0..63 and the second tile contains voxels 63..126 and
   * so on for each dimension.  The voxel at 63,0,0 is contained in both tiles.
   * To resolve the potential ambiguity, getTileID always returns the id of the
   * tile in which the specified voxel is closest to the tile's origin (its min
   * i,j,k).  So in this example getTileID would return the id of the second tile.
   * This is normally the most useful behavior.
   */
  SoLDMTileID getTileID( const SbVec3i32& cellPos, const int resolution )const;

  /**
   * Returns the number of fileIDs in the volume.  Effectively this is the
   * total number of tiles, including both full resolution and low resolution,
   * required to store the data set.
   */
  int getNumFileIDs()const;

  /**
   * Given a tileID, returns the corresponding fileID.
   */
  inline int getFileID( const SoLDMTileID& tileID )const;

  /**
   * Given a fileID, returns the corresponding tileID.
   */
  SoLDMTileID getTileID( const int fileID )const;

  /**
   * Returns false if the octree is empty.
   * Note: Octree must be initialized.
   */
  inline bool isEmpty() const
  { return (m_numFileIDs<=0); }

SoINTERNAL public:

  /**
   * Destructor.
   */
  ~SoLDMTopoOctree();

  SbVec3i32 getTileOrigin( const LDM_TILE_ID_TYPE tileID )const;

  LDM_TILE_ID_TYPE parent( const LDM_TILE_ID_TYPE index )const;
  inline LDM_TILE_ID_TYPE children( const LDM_TILE_ID_TYPE index )const;
  /** [OIV-WRAPPER VISIBILITY{Public}] */
  int level( const LDM_TILE_ID_TYPE index )const;
  inline int level( const SoLDMTileID& id )const;

  LDM_TILE_ID_TYPE getNumTilesAtDepth( const int level )const;
  LDM_TILE_ID_TYPE getSumTilesAtDepth( const int level )const;
  int getLevelMax()const;
  inline size_t getNumTileIDs()const;
  int getNumFileIDsAtDepth( const int level )const;
  int getSumFileIDsAtDepth( const int level )const;
  int sizeofTiles( const int numTile )const;

  inline bool hasChildren(const SoLDMTileID& tileId);

  /** Return tile dimension for given level*/
  inline const SbVec3i32& getTileDimAtLevel(int l) const;

  /** Return tile dimension at the tile's level */
  SbVec3i32 getTileDimAtLevel(const SoLDMTileID& id) const;

  /**
   * Return true if child is a child of parent
   */
  inline bool isChildOf(const SoLDMTileID& parent,
                        const SoLDMTileID& child) const;

  /**
   * Return true if child has parent in his family (father, grand-father, grand-grand-father...)
   */
  inline bool isInFamilyOf(const SoLDMTileID& parent, const SoLDMTileID& child) const;


  SoLDMOctreeNode* operator [](const LDM_TILE_ID_TYPE tileID)const;
  SoLDMOctreeNode* operator ()(const int fileID)const;

private:
  /** Compute tile dims for each levels */
  void fillTileDimAtLevel();

  /** Return tile's origin. Avoid a call to level if already computed */
  SbVec3i32 getTileOrigin( const LDM_TILE_ID_TYPE tileID, int tileLevel ) const;

  /**
   * Given a tileID, returns the corresponding fileID when m_fileIDs table
   * doesn't exist.
   */
  int getFileIDReverseTable( const SoLDMTileID& tileID )const;

  /**
   * Compute the octree level
   */
  static float computeLevelMax(unsigned int maxDim, unsigned int tileDim,
                               unsigned int border);

  static const int MAX_OCTREE_DEPTH;

  // precomputed data
  LDM_TILE_ID_TYPE  m_numTilesAtDepth[LEVEL_MAX+1];
  LDM_TILE_ID_TYPE  m_sumTilesAtDepth_[LEVEL_MAX+2];
  LDM_TILE_ID_TYPE* m_sumTilesAtDepth;

  // data depending on the volume dimension
  SbVec3i32         m_dimension;
  SbVec3i32         m_tileDim;
  int               m_border;
  int               m_levelMax;
  LDM_TILE_ID_TYPE  m_numTileIDs;
  int               m_numFileIDs;
  SoLDMOctreeNode  *m_tileIDs;
  int*              m_fileIDs;
  int               m_numFileIDsAtDepth[LEVEL_MAX+1];
  int               m_sumFileIDsAtDepth[LEVEL_MAX+1];
  bool              m_initIsDone;
  /** Tile's dimension (3D) */
  static const unsigned int TDimension;

  std::vector<SbVec3i32> m_tileDimAtLevel;
};

/******************************************************************************/
size_t
SoLDMTopoOctree::getNumTileIDs() const
{
  return (size_t)(m_numTileIDs);
}

/******************************************************************************/
bool
SoLDMTopoOctree::hasChildren(const SoLDMTileID& tileId)
{
  return children(tileId.getID()) < (LDM_TILE_ID_TYPE)getNumTileIDs() ;
}

/******************************************************************************/
int
SoLDMTopoOctree::level(const SoLDMTileID& id) const
{
  return level(id.getID());
}

/******************************************************************************/
bool
SoLDMTopoOctree::isChildOf(const SoLDMTileID& parent, const SoLDMTileID& child) const
{
  if ( child.getID() >= m_numTileIDs )
    return false;

  LDM_TILE_ID_TYPE firstChild = children(parent.getID());
  LDM_TILE_ID_TYPE childId = child.getID();
  return childId >= firstChild && childId < firstChild+8;
}

/******************************************************************************/
bool 
SoLDMTopoOctree::isInFamilyOf(const SoLDMTileID& _parent, const SoLDMTileID& child) const
{
  LDM_TILE_ID_TYPE childId = child.getID();
  LDM_TILE_ID_TYPE parentId = _parent.getID();
  if ( childId >= m_numTileIDs || childId < 0 )
    return false;
  else if ( childId == parentId)
    return true;
  else
  {
    LDM_TILE_ID_TYPE parentChildID = parent(childId);
    if ( parentChildID == parentId )
      return true;
    else
      return isInFamilyOf(_parent,parentChildID);
  }
  return false;
}

/******************************************************************************/
int
SoLDMTopoOctree::getFileID( const SoLDMTileID& tileID )const
{
  if ( tileID.getID()<0 || tileID.getID()>=m_numTileIDs)
    return -1;

  // if m_fileIDs exists, use it straight
  if ( m_fileIDs )
    return m_fileIDs[tileID.getID()] - 1;

  return getFileIDReverseTable(tileID);
}

/******************************************************************************/
LDM_TILE_ID_TYPE
SoLDMTopoOctree::children( const LDM_TILE_ID_TYPE index )const
{
  return (index << TDimension) + 1;
}

#ifdef WIN32
#pragma warning( pop )
#endif

#endif /* _SO_LDM_TOPO_OCTREE_ */
