/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LDM_SHAPE
#define  _SO_LDM_SHAPE

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoShape.h>
#include <LDM/actions/SoLdmValuationAction.h>

#include <LDM/SoLDMTileID.h>

class SoLDMNodeFrontManager;

/**
* @LDMEXT Abstract base class for LDM shape nodes.
*
* @ingroup LDMNodes
*
* @DESCRIPTION
* Interface for all rendering nodes using LDM
*
* @FILE_FORMAT_DEFAULT
*    LdmShape {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
*
* @SEE_ALSO
*    SoVolumeRender,
*    SoOrthoSlice,
*    SoObliqueSlice
*
* @ACTION_BEHAVIOR
* SoCallbackAction,
* SoGLRenderAction,
* SoGetBoundingBoxAction,
* SoPickAction,
* SoWriteAction
*
*
*/
class LDM_API SoLdmShape : public SoShape
{
  SO_NODE_ABSTRACT_HEADER(SoLdmShape);

public:
  /**
   * Returns true if the shape intersects the given tile. @BR
   * Default implementation always returns true.
   */
  virtual bool intersect(SoLDMNodeFrontManager* nfm, const SoLDMTileID& tileId);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  friend class SoLDMNodeFrontMgrOctree;

  /** Register ldm nodes */
  virtual void ldmAction(SoLdmValuationAction* action) = 0 ;

  SoLdmShape();
  virtual ~SoLdmShape();

  /** Return number of allowed 2D texture for this shape */
  virtual unsigned int getSumOfMaxTextures2D(SoLDMNodeFrontManager* nfm);

  friend class SoLdmValuationAction;
};

#endif // _SO_LDM_SHAPE
