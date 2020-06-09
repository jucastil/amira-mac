/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Jan 2001)
** Modified by : R.ALBOU (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_CSG_GROUP_
#define  _SO_CSG_GROUP_

#include <SolidViz/SoSolidViz.h>

#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbViewportRegion.h>

#include <Inventor/sys/SoGLType.h>

class SoSeparator ;
class SoFieldSensor ;

/**
 * @SVEXT Group node for Constructive Solid Geometry rendering.
 * 
 * @ingroup SolidViz
 * 
 * @DESCRIPTION
 *   This group node performs a Constructive Solid Geometry (CSG) rendering. The
 *   children of this group define the solids that are involved in the CSG rendering.
 *   It is important to know that all children of this group are assumed to be solid
 *   (i.e., having a closed surface). Otherwise the results may be incorrect.

 *   An expression defines the operations between these solids. Possible
 *   operations are: 
 *   intersection (indicated as "." in the expression), union ("+"), and subtraction
 *   ("-"). A solid is identified by a letter (or a group of letters) in the expression 
 *   and corresponds to the child number as follows: 'A' corresponds to child 0, 'B' 
 *   corresponds to child 1, "AA" corresponds to child 26, "AZ" corresponds to child 51, 
 *   and so forth. The expression is not case sensitive. If you decide for example to 
 *   use "AA", you must have previously created children 0-25 (A through Z).
 *   
 *   A letter can be followed by a number to indicate the convexity of the solid. The
 *   convexity of a solid is defined as the maximum numbers of pairs of front and
 *   back surfaces. For instance, the convexity of a cube is 1 whereas the convexity
 *   of a torus is 2. The convexity of a solid is assumed to be 1 if no digit follows
 *   the corresponding letter in the expression. The maximum allowable convexity
 *   value is 128.
 *   
 *   The more complex the expression, the slower the performance. The same holds true
 *   for the convexity of an object - greater convexity implies slower performance.
 *   
 *   For best performance, the graphics accelerator should perform stencil buffer
 *   operations in hardware.
 *   
 *   Example of CSG Tree:
 *   
 *   @IMAGE CSGGroup_SceneGraph.jpg 
 *   
 *   In this example, "myShape1" is 'A', "Separator1" is B, and "Separator2" is C. A
 *   CSG expression could be: "A . B - C + A" and corresponds to the following CSG
 *   tree:
 *   
 *   @IMAGE CSGGroupTree.jpg 
 *   
 *   The CSG tree defined by #expression is assumed to be in normal form
 *   (normalized). A CSG tree is in normal form when all intersection and subtraction
 *   operators have a left subtree that contains no union operator and a right
 *   subtree that is simply a shape. For example, the tree shown above is in normal
 *   form.
 *   
 *   A CSG tree can be converted to normal form by repeatedly applying the following
 *   set of production rules to the tree and then its subtrees:
 *   @UL @LI @TABLE_0B
 *      @TR A - ( B + C )    @TD => @TD ( A - B ) - C 
 *      @TR A . ( B + C )    @TD => @TD ( A . B ) + ( A . C )
 *      @TR A - ( B . C )    @TD => @TD ( A - B ) + ( A - C )
 *      @TR A . ( B . C )    @TD => @TD ( A . B ) . C
 *      @TR A - ( B - C ) @TD => @TD ( A - B ) + ( A . C )
 *      @TR A . ( B - C ) @TD => @TD ( A . B ) - C
 *      @TR ( A - B ) . C @TD => @TD ( A . C ) - B
 *      @TR ( A + B ) - C    @TD => @TD ( A - C ) + ( B - C )
 *      @TR ( A + B ) . C    @TD => @TD ( A . C ) + ( B . C )
 *   @TABLE_END @li @ul
 *   
 *   If the CSG expression exceeds a certain length, a save/restore of the Z-Buffer is
 *   needed. This operation is time consuming. An environment variable,
 *   OIV_CSG_BUFFER_REGION [Win 32 only], allows the algorithm to use the OpenGL
 *   Buffer Region extension to speed up save/restore of Z-buffer task. Standard save
 *   and restore of the Z-buffer (glDrawPixels/glReadPixels) is used if this variable
 *   is not defined or the extension is not available.
 *   
 *   Because there are two Buffer Region extensions, the value of this environment
 *   variable can be:
 *   
 *   KTX_BUFFER_REGION: Uses the GL_KTX_buffer_region extension.
 *   
 *   ARB_BUFFER_REGION: Uses the WGL_ARB_buffer_region extension.
 * 
 * @FILE_FORMAT_DEFAULT
 *    CSGGroup {
 *    @TABLE_FILE_FORMAT
 *       @TR expression                @TD ""
 *       @TR isShapesBefore            @TD FALSE
 *       @TR isActive                  @TD TRUE
 *       @TR boundingBoxPruningEnabled @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoSolidViz
 * 
 * 
 */ 

class SOLIDVIZ_API SoCSGGroup : public SoGroup {
  SO_NODE_HEADER( SoCSGGroup );

 public:
  /**
   * Expression which defines the CSG tree.
   * 
   */
  SoSFString      expression; 

  /**
   * This flag indicates if there are any shapes before the @B CSGGroup @b in the
   * scene graph. For better performance, this group should not be preceded by any
   * shapes, otherwise it is necessary to save a backup of the Z-Buffer (which is
   * done when this flag is set to TRUE). If there are shapes preceding the group and
   * the value is set to FALSE, the resulting image may be incorrect.
   * 
   */
  SoSFBool        isShapesBefore;

  /**
   * Indicates if CSG rendering should be done. If this flag is set to FALSE, this
   * group works as an SoGroup.
   * 
   */
  SoSFBool        isActive ;

  /**
   * Indicates if the CSG tree is pruned by the following rules:
   * 
   * - A.B = 0 if BoundingBox(A) does not intersect BoundingBox(B).
   * 
   * - A-B = A if BoundingBox(A) does not intersect BoundingBox(B).
   * 
   * These rules can potentially speed up the rendering in case of 
   * a complex CSG expression by simplifying the CSG tree.
   *
   */
  SoSFBool    boundingBoxPruningEnabled ;

  /**
   * Constructor.
   */
  SoCSGGroup();
  /**
   * Constructor.
   */
  SoCSGGroup(int nChildren);

#ifndef HIDDEN_FROM_DOC
  // Return the geometric result of the CSG tree defined by the expression.
  SoNode* getGeometry() const ;
#endif

 SoEXTENDER public:
  // Implement actions
  virtual void GLRender(SoGLRenderAction *action);

  /*----------------------------------------------------------------------------*/

 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

 protected:
  virtual ~SoCSGGroup();

 private:
  struct SoCSGProduct {
    int       targetPrim ;
    SbBool    frontFace ;
    int       whichSurface ;
    int       targetConvexity ;
    SbIntList trimmingPrims ;
    SbIntList isComplemented ;
  };

  SbBool            m_isShapesBefore ;
  SbBool            m_isReinterpretExpression;
  SbBool            m_shouldInvalidateCache ;
  GLuint            m_viewportRegion[4] ;
  SoFieldSensor    *m_expressionSensor, *m_isActiveSensor ;
  SoGLRenderAction *m_action;
  SoState          *m_state ;
  GLint             m_stenSize;
  int               m_numProducts;
  GLfloat          *m_depthResults;
  int               m_sCountMask;
  int               m_sPMask;
  int               m_sPShift;
  
  SoCSGProduct     *m_products;
  SbBox3f          *m_solidBBoxList ;
  
  uint64_t          m_lastNodeId ;

  // To read the expression !
  void interpretExpression( void );

  // Compute the bounding box of each solid.
  void computeSolidsBBox(void) ;

  // Prunes CSG products accoding to bbox pruning rules.
  void pruneCSGProducts(void) ;

#ifdef _WIN32
  HANDLE m_bufferRegionHandle;
#endif

 private:
  void drawFarRect(void);
  void redrawCSG(void);
  void saveDepth(void);
  SbBool markProductPixels(int product, int accumBit);
  void restoreDepth(void);
  SbBool drawProduct(int product, int accumBit);
  SbBool renderPrimDepths(const SoCSGProduct *p);
  SbBool trimWithPrimitive(int trimPrim, int isComplemented);
  void pushOrthoView(float left, float right, float bottom, float top,float znear, float zfar) ;
  void popView(void);
  void drawPrim(int i);
  void commontInit(void) ;

  static unsigned char countNeededBits(unsigned char byte) ;

  static void parseExpressionError(int number) ;
  static void isActiveSensorCB(void *data, SoSensor *) ;
  static void expressionSensorCB(void *data, SoSensor *) ;

};
/*----------------------------------------------------------------------------*/
#endif // _SO_CSG_GROUP_

