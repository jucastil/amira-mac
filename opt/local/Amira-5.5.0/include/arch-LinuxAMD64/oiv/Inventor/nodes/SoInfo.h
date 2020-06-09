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


#ifndef  _SO_INFO_
#define  _SO_INFO_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoInfo
//
//  Node that holds application-specific information as a text string.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Node containing information text string.
* 
* @ingroup PropertyNodes
* 
* @DESCRIPTION
*   This class defines a information node in the scene graph. This node has no
*   effect during traversal. It is used to store information in the scene graph,
*   typically for application-specific purposes, copyright messages, or other
*   strings. 
* 
* @FILE_FORMAT_DEFAULT
*    Info {
*    @TABLE_FILE_FORMAT
*       @TR string   @TD "<Undefined info>"
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoLabel
* 
* 
*/ 
#else
/**
* Node containing information text string.
* 
* @ingroup PropertyNodes
* 
* @DESCRIPTION
*   This class defines a information node in the scene graph. This node has no
*   effect during traversal. It is used to store information in the scene graph,
*   typically for application-specific purposes, copyright messages, or other
*   strings. This node differs from the SoLabel node in that it stores its
*   information in an SbString instead of an SbName; the SbString is more efficient
*   for storing long strings that don't have to be accessed very often. Use an
*   SoLabel node for short strings that have to be accessed more often.
* 
* @FILE_FORMAT_DEFAULT
*    Info {
*    @TABLE_FILE_FORMAT
*       @TR string   @TD "<Undefined info>"
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SbString,
*    SoLabel
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoInfo : public SoNode {

  SO_NODE_HEADER(SoInfo);

 public:
  // Fields
  /**
   * Defines the info string.
   * 
   */
  SoSFString          string;

  /**
   * Creates an info node with default settings.
   */
  SoInfo();

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoInfo();

  // NOTE: No actions for this node. It's pretty passive.
};

#endif /* _SO_INFO_ */

