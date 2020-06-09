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


#ifndef  _SO_SF_NODE_
#define  _SO_SF_NODE_

class SoNode;

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFNode subclass of SoSField. The field value is a pointer to an
//  SoNode. The field automatically maintains a reference to the node
//  it points to and propagates notification from the node.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Field containing a reference to a node.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a reference to an SoNode instance.
*   
*   SoSFNodes are written to file as the node they are pointing to. For example:
*   
*   <PRE>
*    mySoSFNodeField Cube {}
*    </PRE>
*    is an SoSFNode field named 'mySoSFNodeField', pointing to an SoCube node.
*   If the node is used elsewhere, the regular DEF/USE instancing mechanism
*   applies:
*   
*   <PRE>
*    anotherSoSFNodeField USE topSeparator
*    </PRE>
*    is an SoSFNode field that points to a node named 'topSeparator' that was
*   DEF'ed earlier in the scene.
* 
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFNode,
*    SoNode
* 
* 
*/ 
#else
/**
* Field containing a pointer to a node.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a pointer to an SoNode instance, correctly maintaining its
*   reference count.
*   
*   SoSFNodes are written to file as the node they are pointing to. For example:
*   
*   <PRE>
*    mySoSFNodeField Cube {}
*    </PRE>
*    is an SoSFNode field named 'mySoSFNodeField', pointing to an SoCube node.
*   If the node is used elsewhere, the regular DEF/USE instancing mechanism
*   applies:
*   
*   <PRE>
*    anotherSoSFNodeField USE topSeparator
*    </PRE>
*    is an SoSFNode field that points to a node named 'topSeparator' that was
*   DEF'ed earlier in the scene.
* 
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFNode,
*    SoNode
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoSFNode : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFNode, SoNode *, SoNode *);

 public:
  /**
   * Gets the value of this field.
   *
   * The getEffectiveNode parameter is only used when the node in the
   * field is a VRML Proto.  In this case, if the parameter is true 
   * then for convenience it returns the first child of the proto 
   * (the node the proto is pretending to be).
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoNode *getValue(SbBool getEffectiveNode = FALSE); 

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Update a copied field to use the copy of the node if there is one
  virtual void fixCopy(SbBool copyConnections);

  // Override this to also check the stored node
  virtual SbBool referencesCopy() const;

 private:
  // Override this to maintain write-references in node
  virtual void countWriteRefs(SoOutput *out) const;

  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void setVal(SoNode *newValue);

};

#endif /* _SO_SF_NODE_ */

