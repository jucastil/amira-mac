/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_SFBUFFEROBJECT_H_
#define _SO_SFBUFFEROBJECT_H_

#include <Inventor/devices/SoBufferObject.h>
#include <Inventor/fields/SoSubField.h> 
/*
class INVENTOR_API SoSFBufferObject : public SoSField
{
  // Use standard field stuff
  SO_SFIELD_HEADER( SoSFBufferObject, SoBufferObject*, SoBufferObject* );

 SoINTERNAL public:

  static void initClass();

  static void exitClass();

  void notify( SoNotList *list );
};
*/

class INVENTOR_API SoSFBufferObject : public SoSField
{
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFBufferObject, SoBufferObject *, SoBufferObject *);

 public:
  /**
   * Gets the value of this field.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoBufferObject *getValue(SbBool getEffectiveNode = FALSE); 

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
  void setVal(SoBufferObject *newValue);
};

#endif //_SO_SFBUFFEROBJECT_H_
