/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Oct 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_ANNOT_TEXT3_PROPERTY_
#define  _SO_ANNOT_TEXT3_PROPERTY_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFNode.h>

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Annotation text property node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node sets the current annotation text properties in the state used by all
 *   subsequent SoAnnoText3 nodes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    AnnoText3Property {
 *    @TABLE_FILE_FORMAT
 *       @TR renderPrintType             @TD RENDER3D_PRINT_VECTOR
 *       @TR isCharOrientedRasterPrint   @TD TRUE
 *       @TR fontSizeHint                @TD FIT_VECTOR_TEXT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    Sets: SoAnnoText3CharOrientElement, SoAnnoText3FontSizeHintElement, SoAnnoText3RenderPrintElement
 * 
 * @SEE_ALSO
 *    SoAnnoText3
 * 
 * 
 */ 

class INVENTOR_API SoAnnoText3Property : public SoNode {

  SO_NODE_HEADER(SoAnnoText3Property) ;
  
 public:

   /** Render print type */
  enum RenderPrintType {
    /**
     *  Text is rendered in 3D (like SoText3). It is printed as vectors
     * when the Hard Copy Extension (formerly known as PlotMaster) is used. 
     */
    RENDER3D_PRINT_VECTOR,
    /**
     *  Text is rendered in 3D (like SoText3). It is printed as raster text 
     * using PostScript fonts when the Hard Copy Extension is used. 
     */
    RENDER3D_PRINT_RASTER,
    /**
     *  Text is rendered in 2D (like SoText2) but can be zoomed because the font size
     * is interpreted in the current units. It is printed as raster text 
     * using PostScript fonts when the Hard Copy Extension is used.
     *
     *  Note: if this render type is set, the text will not be exported by an SoToPDFAction.
     */
    RENDER2D_PRINT_RASTER
  } ;

  /** Font size hint */
  enum FontSizeHint {
    /**
     *  2D text maintains its nominal font size from any view angle. 
     */
    ANNOTATION,
    /**
     *  The font size of 2D text changes according to the view angle (it follows the
     * projection on the screen of 3D text). 
     */
    FIT_VECTOR_TEXT
  } ;

  /**
   * Constructor.
   */
  SoAnnoText3Property() ;

  /**
   * This flag specifies how annotation text should be rendered (as 3D text or 2D
   * text) and how it should be printed when the Hard Copy Extension is used (as 3D
   * vectors or 2D PostScript raster fonts).
   * Use enum #RenderPrintType. Default is RENDER3D_PRINT_VECTOR.
   */
  SoSFEnum renderPrintType ;
  /**
   * This flag is used when the field #renderPrintType is equal to
   * RENDER3D_PRINT_RASTER or RENDER2D_PRINT_RASTER. It specifies whether the text
   * should be oriented (or not) for printing when using the Hard Copy
   * Extension. Default is TRUE.
   */
  SoSFBool isCharOrientedRasterPrint ;
  /**
   * This flag is used when the field #renderPrintType is equal to
   * RENDER3D_PRINT_RASTER or RENDER2D_PRINT_RASTER. It specifies how the font size
   * for 2D text (whether rendered or raster) changes according to the view.
   * Use enum #FontSizeHint.  Default is FIT_VECTOR_TEXT.
   */
  SoSFEnum fontSizeHint ;

  /** 
   * Sets the maximum font size (in pixels) when #renderPrintType 
   * field is equal to RENDER2D_PRINT_RASTER.
   * The maximum font size can also be set using the OIV_MAX_ANNO_RENDER2D_SIZE
   * environment variable.
   */
  static void setMaxViewingFontSize( unsigned int size );

  /** 
   * Gets the maximum font size (in pixels) that can be used 
   * when #renderPrintType field is equal to RENDER2D_PRINT_RASTER.
   */
  static unsigned int getMaxViewingFontSize();

 SoEXTENDER public:

  virtual void  doAction(SoAction *action) ;
  virtual void  GLRender(SoGLRenderAction *action) ;
  virtual void  callback(SoCallbackAction *action) ;
  virtual void  pick(SoPickAction *action) ;
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action) ;
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action) ;

 
  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  // Init the class
  static void initClass() ;
  static void exitClass() ;

 protected:
  virtual ~SoAnnoText3Property() ;

 private:
} ;

/*----------------------------------------------------------------------------*/

#endif /* _SO_ANNOT_TEXT3_PROPERTY_  */

