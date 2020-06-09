/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R.ALBOU (May 2002)
**=======================================================================*/
#ifndef  _SO_SHADOW_STYLE_
#define  _SO_SHADOW_STYLE_


#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBitMask.h>


class SoGLShadowMapping ;

/**
 * @FXEXT Shadow style property node.
 *
 * @ingroup FXViz
 *
 * @DESCRIPTION
 * This node specifies the shadow style for all subsequent SoShadowGroup nodes.
 * The shadow style is used to determine if shapes cast a shadow
 * and/or can be shadowed.
 *
 * @FILE_FORMAT_DEFAULT
 *    ShadowStyle {
 *    @TABLE_FILE_FORMAT
 *               @TR style             @TD CASTS_SHADOW_AND_SHADOWED
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoFXViz, SoShadowGroup.
 *
 *
 */

class INVENTOR_API SoShadowStyle : public SoNode {
  SO_NODE_HEADER( SoShadowStyle );

 public:
  /**
   * Shadow style type
   */
  enum ShadowStyle {
    /**
     * Shapes neither cast a shadow nor can be shadowed.
     */
    NO_SHADOWING                  = 0x00,

    /**
     * Shapes cast a shadow (but can't be shadowed).
     */
    CASTS_SHADOW                  = 0x01,

    /**
     * Shapes can be shadowed (but don't cast a shadow).
     */
    SHADOWED                      = 0x02,

    /**
     * Shapes cast a shadow and can be shadowed.
     */
    CASTS_SHADOW_AND_SHADOWED     = 0x03
  } ;

  /**
   * Default constructor.
   */
  SoShadowStyle();

  /**
   * Shadow style. Bit flag combination of #ShadowStyle.
   */
  SoSFBitMask  style ;


 SoEXTENDER public:
  // Implement actions
  virtual void GLRender(SoGLRenderAction *action);

  /*----------------------------------------------------------------------------*/

 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

 protected:
  virtual ~SoShadowStyle();

};
/*----------------------------------------------------------------------------*/
#endif // _SO_SHADOW_STYLE_
