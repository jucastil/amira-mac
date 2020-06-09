/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LABEL_HINTS_
#define  _PO_LABEL_HINTS_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>

#include <MeshViz/nodes/PoNode.h>

/**
 * @DTEXT  Node to define common label hints.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current hints to display label of all subsequent
 *    MeshViz representations inhering from PoChart.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoLabelHints {
 *    @TABLE_FILE_FORMAT
 *       @TR labelPath @TD DEPEND
 *       @TR justification @TD DEPEND
 *       @TR addString @TD ""
 *       @TR isLabelLineVisible @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoLabelHints : public PoNode {
  
  SO_NODE_HEADER(PoLabelHints) ;
  

 public:

  /**
   *  Label path type.
   */
  enum LabelPath {
    /**
     *  Writing labels from left to right.
     */
    PATH_RIGHT, 
    /**
     *  Writing labels from right to left.
     */
    PATH_LEFT,  
    /**
     *  Writing labels from bottom to top.
     */
    PATH_UP,    
    /**
     *  Writing labels from top to bottom.
     */
    PATH_DOWN,  
    /**
     *  Automatic choice of writing path depending on 
     */
    PATH_DEPEND 
    /**
     *  the representation type which uses this node.
     */
  } ;



  /**
   *  Label justification type.
   */
  enum Justification {
    /**
     *  Left edges of all labels are aligned.
     */
    LEFT,   
    /**
     *  Centers of all labels are aligned.
     */
    CENTER, 
    /**
     *  Right edges of all labels are aligned.
     */
    RIGHT,  
    /**
     *  Automatic choice of path depending on 
     */
    DEPEND  
    /**
     *  the representation type which uses this node.
     */
  } ;



  /* Fields */

  /**
   * Defines the path used to display label.
   */
  SoSFEnum labelPath ;

  /**
   * Defines the justification used to display label.
   */
  SoSFEnum justification ;

  /**
   * Defines a string to concat to the label to display.
   * If you want to ignore the string to concat, remember to
   * call the method setIgnored(TRUE) (method of SoField) on this field.
   */
  SoSFString addString ;

  /**
   * Defines the visibility of a line from the label and the part to be
   * annotated.
   */
  SoSFBool isLabelLineVisible ;

  /**
   * Constructor.
   */
  PoLabelHints() ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;
  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoLabelHints() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_LABEL_HINTS_ */

