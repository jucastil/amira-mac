/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2001)
**=======================================================================*/

#ifndef SBTVIZTEXTURELIST_H
#define SBTVIZTEXTURELIST_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbPList.h>
#include <TerrainViz/SbTVizTexture.h>

class SiTVizTextureManager;

/**
 * @TVEXT Handles the quadtree of textures.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   The class handles a list of textures sorted to fit a quadtree. These textures
 *   are mapped on the mesh. The textures displayed are chosen according to the point
 *   of view. The textures are SbTVizTexture objects. The list of textures is to be
 *   used with an SoTVizRender node.
 *   
 *   Textures are organized in a quadtree. The level of the texture is the depth level
 *   in the texture quadtree. Level @B n @b has @B 2^(2n) @b textures. By
 *   default the texture tree depth is null.
 *   
 *   @IMAGE DTM_texturelevels.jpg 
 *   
 *   The position is specified as a pair of indices (@B i @b, @B j @b), where
 *   @B i @b is the row and and @B j @b is the column of the texture in a
 *   particular texture level. @B i @b and @B j @b range from @B 0 @b to
 *   @B 2^(n-1)@b. See figure above.
 *   
 *   It is not necessary to provide all textures. Some patches can be empty.
 * 
 * @SEE_ALSO
 *    SbTVizData,
 *    SbTVizRegularGridData,
 *    SbTVizTexture,
 *    SoTViz,
 *    SoTVizRender
 * 
 * 
 */ 

class TERRAINVIZ_API SbTVizTextureList : public SbPList {

  public :
  /**
   * Constructor.
   */
  SbTVizTextureList();

  /**
   *
   * Constructor by copy.
   */
  SbTVizTextureList(const SbTVizTextureList& texList);

  /**
   * Destructor.
   * 
   * Be aware that the destructor does not delete the SbTVizTexture objects referenced.
   * See deleteAllTextures() to perform this operation
   */
  virtual ~SbTVizTextureList();
        
  /**
   * Adds a texture to the list.
   */
  void addTexture(SbTVizTexture* tex);
  /**
   * Adds a texture to the list. Textures are organized in a quadtree. The level of
   * the texture is the depth level in the texture quadtree. Level @B n @b has
   * @B 2^(2n) @b textures. The position is specified as a pair of indices ( @B i @b,
   * @B j @b), where @B i @b is the row and and @B j @b is the column of the
   * texture in a particular texture level. @B i @b and @B j @b range from @B 0 @b
   * to @B 2^n-1@b. See figure above. Borders are the number of pixels used for texture 
   * continuity (overlapping) along X and Y.
   * 
   */
  void addTexture(const char* fileName, int level, const SbVec2s& position, const SbVec2s& borders = SbVec2s(0, 0));
  /**
   * 
   * Removes a texture (identified by filename) from the list. 
   * Returns the SbTVizTexture instance, or NULL if not found.
   * Does not delete the SbTVizTexture object.
   */
  const SbTVizTexture* removeTexture(const char* fileName);
  /**
   * 
   * Removes a texture (identified by level and position) from the list. 
   * Returns the SbTVizTexture instance, or NULL if not found.
   * Does not delete the SbTVizTexture object.
   */
  const SbTVizTexture* removeTexture(int level, const SbVec2s& position);
  /**
   * Returns the texture identified by filename.
   */
  const SbTVizTexture* getTexture(const char* fileName) const;
  /**
   * Returns the texture identified by level and position.
   */
  const SbTVizTexture* getTexture(int level, const SbVec2s& position) const;


  /**
   * 
   * Deletes all the SbTVizTexture objects referenced in the list.
   * Empties the list.
   */
   void deleteAllTextures();

 SoINTERNAL public:
  SbBool needUpdate;

};

#endif

