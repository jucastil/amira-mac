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


#ifndef  _SO_MF_NODE_
#define  _SO_MF_NODE_

class SoNode;

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFNode subclass of SoMField. Each field value is a pointer to an
//  SoNode. The field automatically maintains references to the nodes
//  it points to and propagates notification from the nodes.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of references to nodes.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a set of references to SoNode instances, correctly
*   maintaining their reference counts.
*   
*   SoMFNodes are written to file as one or more nodes. When more than one value is
*   present, all of the values are enclosed in square brackets and separated by
*   commas; for example:
*   
*   <PRE>
*    [ Cube {} , Sphere { radius 2.0 }, USE myTranslation ]
*    </PRE>
*    
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of pointers to nodes.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a set of pointers to SoNode instances, correctly
*   maintaining their reference counts.
*   
*   SoMFNodes are written to file as one or more nodes. When more than one value is
*   present, all of the values are enclosed in square brackets and separated by
*   commas; for example:
*   
*   <PRE>
*    [ Cube {} , Sphere { radius 2.0 }, USE myTranslation ]
*    </PRE>
*    
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFNode : public SoMField {
  
  // Use standard field stuff
  SO_MFIELD_REQUIRED_HEADER(SoMFNode);
  SO_MFIELD_CONSTRUCTOR_HEADER(SoMFNode);
  SO_MFIELD_VALUE_HEADER(SoMFNode, SoNode *, SoNode *);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SoNode *);
 
    /**
     * Adds a node as last one in group.
	 * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
     */
    void addNode(SoNode *node);

  /**
   * Adds a node so that it becomes the one with the given index.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void insertNode(SoNode *node, int newNodeIndex);
  
#ifdef OIV_NET_DOC
  /**
  * Returns reference to nth node node.
  */

#else
  /**
  * Returns pointer to nth node node.
  */

#endif //OIV_NET_DOC
  SoNode *getNode(int index) const;
  
  /**
   * Finds index of given node within group.
   */
  int findNode(const SoNode *node) const;
  
  /**
   * Returns number of nodes.
   */
  int getNumNodes() const;
  
  /**
   * Removes node with given index from group.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void removeNode(int index);
  
  /**
   * Removes first instance of given node from group
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void removeNode(SoNode *node)
    { removeNode(findNode(node)); }
  
  /**
   * Removes all nodes from group.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void removeAllNodes();
  
  /**
   * Replaces node with given index with new node.
   */
  void replaceNode(int index, SoNode *newNode);
  
  /**
   * Replaces first instance of given node with new node
   */
  void replaceNode(SoNode *oldNode, SoNode *newNode)
    { replaceNode(findNode(oldNode), newNode); }
  
  /**
   * Returns a pointer to the internally maintained array that can be modified.
   * The values in the array may be changed, but values cannot be added or removed. It is illegal to call any other
   * editing methods between startEditing() and finishEditing() (e.g. set1Value(), setValue(), etc.).
   *
   * Fields, engines or sensors connected to this field and sensors are not notified that this field has changed until
   * finishEditing() is called. Calling finishEditing() always sets the isDefault() flag to FALSE and informs engines
   * and sensors that the field changed, even if none of the values actually were changed.
   * [OIVNET-WRAPPER-RETURN-TYPE ARRAY{GetNum()}]
   */
  SoNode** startEditing();

  /** Indicates that batch edits have finished. @see startEditing(). */
  void finishEditing();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Update a copied field to use the copy of each node if there is one
  virtual void fixCopy(SbBool copyConnections);
  
  // Override this to also check the stored nodes
  virtual SbBool referencesCopy() const;

private:
  // Override this to maintain write-references in nodes
  virtual void countWriteRefs(SoOutput *out) const;
  
  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void setVal(int index, SoNode *newValue);

  SoNode** m_oldValues;
  int m_oldNum;

};

#endif /* _SO_MF_NODE_ */

