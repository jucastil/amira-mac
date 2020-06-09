/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LABEL_
#define  _SO_LABEL_

#include <Inventor/fields/SoSFName.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLabel
//
//  Node that holds labels for application-specific purposes.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Node containing label text string.
* 
* @ingroup PropertyNodes
* 
* @DESCRIPTION
*   This class defines a label node in the scene graph. This node has no effect
*   during traversal. It is used to store text labels in the scene graph, typically
*   for application-specific identification of subgraphs when node naming is not
*   appropriate.
* 
* @FILE_FORMAT_DEFAULT
*    Label {
*    @TABLE_FILE_FORMAT
*       @TR label   @TD "<Undefined label>"
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoInfo
* 
* 
*/ 
#else
/**
* Node containing label text string.
* 
* @ingroup PropertyNodes
* 
* @DESCRIPTION
*   This class defines a label node in the scene graph. This node has no effect
*   during traversal. It is used to store text labels in the scene graph, typically
*   for application-specific identification of subgraphs when node naming is not
*   appropriate.
* 
* @FILE_FORMAT_DEFAULT
*    Label {
*    @TABLE_FILE_FORMAT
*       @TR label   @TD "<Undefined label>"
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SbName,
*    SoInfo
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoLabel : public SoNode {

  SO_NODE_HEADER(SoLabel);

 public:
  // Fields
  /**
   * Defines the label string value.
   * 
   */
  SoSFName            label;

  /**
   * Creates a label node with default settings.
   */
  SoLabel();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoLabel();

  // NOTE: No actions for this node. It's pretty passive.
};

#endif /* _SO_LABEL_ */

