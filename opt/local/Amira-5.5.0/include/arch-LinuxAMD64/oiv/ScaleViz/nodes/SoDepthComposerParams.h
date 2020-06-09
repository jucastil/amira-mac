/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Apr 2007)
**=======================================================================*/


#ifndef SO_DEPTH_COMPOSER_PARAM_H
#define SO_DEPTH_COMPOSER_PARAM_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>

/**
 * @SCVEXT Abstract base class for global depth compositing parameter setup.
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 *
 *  SoDepthComposerParams class is the abstract base class for global 
 *  depth compositing parameters setup.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DepthComposerParams {
 *    @TABLE_FILE_FORMAT
 *       @TR depthBits   @TD DEPTH_32
 *       @TR hullOptimization   @TD TRUE
 *    @TABLE_END
 *    }
 *
 */

class SCALEVIZ_API SoDepthComposerParams : public SoNode
{
  SO_NODE_HEADER(SoDepthComposerParams);

public :

  enum DepthBits {
    /**
     * Use the best mode depending on far and near clipping plane range.
     */
    AUTO,
    /**
     * 16-bit depth component precision.
     */
    DEPTH_16,
    /**
     * 32-bit depth component precision.
     */
    DEPTH_32
  };

  /**
   * Number of depth bits precision to use for depth composition. 
   * Use enum #DepthBits. Default is DEPTH_32.
   */
  SoSFEnum depthBits;

  /**
   * Enables hull optimization. 
   * Hull optimization specifies to send only the portion of the image 
   * that really contains graphics entities (non background pixels).
   * Default is TRUE.
   */
  SoSFBool hullOptimization;

SoINTERNAL public:

  static void initClass();
  static void exitClass();

  /**
   * Enables management of delayed objects. Default is TRUE, which allows
   * objects that do not have a depth component (e.g., transparent, annotation, ...) 
   * to be correctly composed and drawn.
   * If not enabled, then some rendering artifacts may appear with 
   * these kinds of objects.
   */
  SoSFBool manageDelayedObjects;

  /**
   * Enables console printing of statistics about the composition, Default is FALSE.
   */
  SoSFBool timing;

  /**
   * Enables hull display (for demo and/or debug purposes). 
   * Available only if #hullOptimization is set to TRUE. Default is FALSE.
   */
  SoSFBool hullShow;

  /**
   * Constructor.
   */
  SoDepthComposerParams();

protected:
  virtual ~SoDepthComposerParams();
};

#endif // SO_DEPTH_COMPOSER_PARAM_H

/**/
