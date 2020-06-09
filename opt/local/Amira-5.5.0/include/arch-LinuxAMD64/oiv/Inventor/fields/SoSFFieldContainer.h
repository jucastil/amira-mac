/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_SF_FIELDCONTAINER_
#define  _SO_SF_FIELDCONTAINER_

class SoSFFieldContainer;

#include <Inventor/fields/SoSubField.h>

class INVENTOR_API SoSFFieldContainer : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFFieldContainer, SoFieldContainer*, SoFieldContainer*);

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
  void setVal(SoFieldContainer *newValue);

};

#endif // _SO_SF_FIELDCONTAINER_

/**/
