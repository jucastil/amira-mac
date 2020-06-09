/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_V1CUSTOMNODE_
#define  _SO_V1CUSTOMNODE_

#include <Inventor/misc/upgraders/SoUpgrader.h>
#include <Inventor/fields/SoMFName.h>
#include <Inventor/fields/SoMFString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoV1CustomNode
//
//////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoV1CustomNode : public SoUpgrader {

  SO_NODE_HEADER(SoV1CustomNode);

 public:
  // Fields
  SoMFName            className;      // Names in custom subclass hierarchy
  SoMFString          fields;         // Field data strings, 1 per subclass
  SoMFString          customData;     // Custom data strings, 1 per subclass

  // Default constructor
  SoV1CustomNode();

  // There are 9 steps to reading in and upgrading a custom node;
  // happily, subclasses only have to worry about three virtual
  // methods:
  //   createNewNode()       -- MUST be implemented
  //   interpretCustomData() -- optional
  //   setUpNewNode()        -- also optional
  // See comments below for more info...
  virtual SbBool      upgrade(SoInput *in, const SbName &refName,
                              SoBase *&result);

 protected:
  // which is responsible for looking at the
  //   className field and creating an appropriate replacement node.

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // createNewNode should look at the className field and create an
  // appropriate replacement node.  The default method prints an
  // error message.  This is called after fields have been read, but
  // before children are read.
  virtual SoNode      *createNewNode();

  // This method is called to let subclass instances do whatever they
  // have to do based on the info in the customData field value with the
  // given index after the given instance has been read. The default
  // does nothing.  This is called after createNewNode, before
  // children have been read.
  virtual void        interpretCustomData(SoV1CustomNode *inst,
                                          int index) const;

  // This method is passed the new node (created by the
  // createNewNode method, above).  It must copy the fields from the
  // V1 upgrader instance into the new node, and must move the
  // children from the upgrader to the new node.  The default method
  // does nothing.
  virtual void        setUpNewNode(SoNode *newNode);

  virtual ~SoV1CustomNode();
};

// Note: use the generic SO_NODE_HEADER/etc macros instead of the
// SO_CUSTOM macros.

#endif /* _SO_V1CUSTOMNODE_ */
