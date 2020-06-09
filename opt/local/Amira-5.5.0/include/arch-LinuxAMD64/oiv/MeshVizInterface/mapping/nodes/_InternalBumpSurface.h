#ifndef HIDDEN_FROM_DOC

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

/*=======================================================================

***********************INTERNAL USE ONLY*********************************

*********************** DO NOT USE **************************************

**=======================================================================*/

#ifndef _MO_MESHBUMPSURFACE_
#define _MO_MESHBUMPSURFACE_

#include <MeshVizInterface/mapping/nodes/MoMeshSurface.h>

class MdBumpMapping;
class MoSurfaceMesh;
/**
* @DTEXT  INTERNAL USE ONLY, Rendering node that displays a bump mapped surface.
* 
* @ingroup MeshIViz_Mapping_Representation
* 
* @DESCRIPTION
*  A bump mapped surface is based on an unstructured surface mesh. This surface is 
*  rendered using a bump mapping method, using a bump factor parameter to compute 
*  the bump value.
*
* @FILE_FORMAT_DEFAULT
*    MeshBumpSurface {
*    @TABLE_FILE_FORMAT
*       @TR colorScalarSetId           @TD 0
*       @TR bumpFactor                 @TD 10.0
*       @TR parallel                   @TD TRUE
*    @TABLE_END
*    }
*
* @SEE_ALSO
*  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial
* 
*/
class MESHIVIZDM_API MoMeshBumpSurface : public MoMeshSurface
{
  SO_NODE_HEADER( MoMeshBumpSurface );

public:

  /**
   * Constructor.
   */
  MoMeshBumpSurface();

  /**
   * The bumpFactor can be set to control bump mapping value.
   */
  SoSFFloat bumpFactor;

  /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  SoEXTENDER public:
  virtual void doAction(SoAction *action);

  /**
   * Modify the main color used in shader
   */
  void setColor( const SbVec4f& color );

protected:

  /**
   * Destructor.
   */
  virtual ~MoMeshBumpSurface();

  virtual void clear();

  void definePlaneUsedForTexture( const MbVec3d& minBds, const MbVec3d& maxBds, SbVec3f& planeNormal, float& planeDistance );

  virtual MoSurfaceMesh* getSurfaceMeshNode();

private:

  // get the cell filter from the state and check it is the good type
  template < typename _CellFilter >
  static const _CellFilter*   getCellFilter(SoState* state);

  /**
  * Update bump factor parameter in shader
  */
  void updateBumpFactor();

  MdBumpMapping* m_bumpMapping;
};

#endif

#endif //HIDDEN_FROM_DOC