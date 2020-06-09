/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_DEPTH_BUFFER_H_
#define _SO_DEPTH_BUFFER_H_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/elements/SoDepthBufferElement.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2f.h>


class SoGLRenderAction;

/**
 * @VSGEXT Depth buffer parameters node.
 *
 * @ingroup PropertyNodes
 *
 * @DESCRIPTION
 *   This class specifies the depth buffer parameters used for rendering,
 * including:
 * - Depth buffer test enabled,
 * - Depth buffer writing enabled,
 * - Depth buffer range, and
 * - Depth comparison function.
 *
 * It can also be used to clear the depth buffer by setting the
 * #clearBuffer field to true.
 *
 * @FILE_FORMAT_DEFAULT
 *    DepthBuffer {
 *      @TABLE_FILE_FORMAT
 *       @TR test  @TD TRUE
 *       @TR write @TD TRUE
 *       @TR function @TD LESS
 *       @TR range @TD (0.0,1.0)
 *       @TR clearBuffer @TD FALSE
 *      @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction
 *
 * @SEE_ALSO
 *       SoPolygonOffset, SoDepthOffset, SoGLRenderAction
 *
 *
 */
class INVENTOR_API SoDepthBuffer : public SoNode
{
  SO_NODE_HEADER(SoDepthBuffer);

public:
  /**
   * Depth function mode as defined by OpenGL.
   */
  enum DepthWriteFunction {
    /** Never passes. */
    NEVER = SoDepthBufferElement::NEVER,
    /** Passes if the	incoming depth value is	less than the stored depth value. */
    LESS = SoDepthBufferElement::LESS ,
    /** Passes if the	incoming depth value is	equal to the stored depth value. */
    EQUAL = SoDepthBufferElement::EQUAL ,
    /** Passes if the	incoming depth value is	less than or equal	to the stored depth value. */
    LEQUAL = SoDepthBufferElement::LEQUAL,
    /** Passes if the	incoming depth value is greater than the stored depth	value. */
    GREATER = SoDepthBufferElement::GREATER,
    /** Passes if the	incoming depth value is	not equal	to the stored depth value. */
    NOTEQUAL = SoDepthBufferElement::NOTEQUAL,
    /** Passes if the	incoming depth value is greater than or equal	to the stored depth value. */
    GEQUAL = SoDepthBufferElement::GEQUAL,
    /** Always passes. */
    ALWAYS = SoDepthBufferElement::ALWAYS
  };

  /**
   * Enable depth buffer testing (glEnable). Default is TRUE.
   */
  SoSFBool test;

  /**
   * Enable depth buffer writing (glDepthMask). Default is TRUE.
   */
  SoSFBool write;

  /**
   * Depth comparison function to use (glDepthFunc). 
   * Use enum #DepthWriteFunction. Default is LESS.
   */
  SoSFEnum function;

  /**
   * Value range for the depth buffer (glDepthRange). Default is [0.0-1.0].
   * The range will be clamped to [0.0-1.0] by OpenGL.
   */
  SoSFVec2f range;

  /**
   * If true, the depth buffer is cleared when the node is traversed
   * (glClear(GL_DEPTH_BUFFER_BIT)). The extent of the buffer that is
   * actually cleared may be limited using an SoViewportClipping node.
   * Default is FALSE.
   *
   * @FIELD_SINCE_OIV 8.6
   */
  SoSFBool clearBuffer;

  /** Constructor */
  SoDepthBuffer();

  /**
   * @copydoc SoNode::setOverride.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * @copydoc SoNode::isOverride.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

SoEXTENDER public:

  /** default actions behavior */
  virtual void doAction(SoAction *action);

  /** @copydoc SoNode::callback */
  virtual void callback(SoCallbackAction* action);

  /** @copydoc SoNode::GLRender */
  virtual void GLRender(SoGLRenderAction * action);


SoINTERNAL public:
  /** @copydoc SoNode::initClass. */
  static void initClass();

  /** @copydoc SoNode::exitClass. */
  static void exitClass();

  SoSFBool override;

protected:
  /** Destructor */
  virtual ~SoDepthBuffer();
};

#endif /* _SO_DEPTH_BUFFER_H_ */
