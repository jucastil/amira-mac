/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (MMM yyyy)
**=======================================================================*/


#ifndef  _SO_MF_FIELDCONTAINER_
#define  _SO_MF_FIELDCONTAINER_

class SoFieldContainer;

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFFieldContainer subclass of SoMField. Each field value is a pointer to an
//  SoFieldContainer. The field automatically maintains references to the
//  fieldContainers it points to and propagates notification from the
//  fieldContainers.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of pointers to fieldContainers.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   This field maintains a set of pointers to SoFieldContainer instances, correctly
 *   maintaining their reference counts.
 *   
 *   SoMFFieldContainers are written to file as one or more fieldContainers. When more than one value is
 *   present, all of the values are enclosed in square brackets and separated by
 *   commas;
 */ 

class INVENTOR_API SoMFFieldContainer : public SoMField {
  
  // Use standard field stuff
  SO_MFIELD_REQUIRED_HEADER(SoMFFieldContainer);
  SO_MFIELD_CONSTRUCTOR_HEADER(SoMFFieldContainer);
  SO_MFIELD_VALUE_HEADER(SoMFFieldContainer, SoFieldContainer *, SoFieldContainer *);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SoFieldContainer *);

  /**
   * Adds a fieldContainer as last one in group.
   */
  void addFieldContainer(SoFieldContainer *fieldContainer);

  /**
   * Adds a fieldContainer so that it becomes the one with the given index.
   */
  void insertFieldContainer(SoFieldContainer *fieldContainer, int newFieldContainerIndex);
  
  /**
   * Returns pointer to nth fieldContainer.
   */
  SoFieldContainer *getFieldContainer(int index) const;
  
  /**
   * Finds index of given fieldContainer within group.
   */
  int findFieldContainer(const SoFieldContainer *fieldContainer) const;
  
  /**
   * Returns number of fieldContainers.
   */
  int getNumFieldContainers() const;
  
  /**
   * Removes fieldContainer with given index from group.
   */
  void removeFieldContainer(int index);
  
  /**
   * Removes first instance of given fieldContainer from group
   */
  void removeFieldContainer(SoFieldContainer *fieldContainer)
    { removeFieldContainer(findFieldContainer(fieldContainer)); }
  
  /**
   * Removes all fieldContainers from group.
   */
  void removeAllFieldContainers();
  
  /**
   * Replaces fieldContainer with given index with new fieldContainer.
   */
  void replaceFieldContainer(int index, SoFieldContainer *newFieldContainer);
  
  /**
   * Replaces first instance of given fieldContainer with new fieldContainer
   */
  void replaceFieldContainer(SoFieldContainer *oldFieldContainer, SoFieldContainer *newFieldContainer)
    { replaceFieldContainer(findFieldContainer(oldFieldContainer), newFieldContainer); }
  
  /**
   * Returns a pointer to the internally maintained array that can be modified.
   * The values in the array may be changed, but values cannot be added or removed. It is illegal to call any other
   * editing methods between startEditing() and finishEditing() (e.g. set1Value(), setValue(), etc.).
   *
   * Fields, engines or sensors connected to this field and sensors are not notified that this field has changed until
   * finishEditing() is called. Calling finishEditing() always sets the isDefault() flag to FALSE and informs engines
   * and sensors that the field changed, even if none of the values actually were changed.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNum()}]
   */
  SoFieldContainer** startEditing();

  /** Indicates that batch edits have finished. @see startEditing(). */
  void finishEditing();
  
  SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Update a copied field to use the copy of each fieldContainer if there is one
  virtual void fixCopy(SbBool copyConnections);
  
  // Override this to also check the stored fieldContainers
  virtual SbBool referencesCopy() const;

private:
  // Override this to maintain write-references in fieldContainers
  virtual void countWriteRefs(SoOutput *out) const;
  
  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void setVal(int index, SoFieldContainer *newValue);
  
  SoFieldContainer** m_oldValues;
  int m_oldNum;

};

#endif // _SO_MF_FIELDCONTAINER_

/**/
