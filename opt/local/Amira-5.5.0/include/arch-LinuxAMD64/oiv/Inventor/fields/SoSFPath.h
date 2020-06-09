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


#ifndef  _SO_SF_PATH_
#define  _SO_SF_PATH_

class SoPath;

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFPath subclass of SoSField. The field value is a pointer to an
//  SoPath. The field automatically maintains a reference to the path
//  it points to and propagates notification from the path.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Field containing a reference to an SoPath.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a reference to an SoPath instance.
*   
*   SoSFPaths are written to file as the path they point to. See the SoPath reference
*   page for a description of the file format for a path.
* 
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFPath,
*    SoPath
* 
* 
*/ 
#else
/**
* Field containing a pointer to an SoPath.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a pointer to an SoPath instance, correctly maintaining its
*   reference count.
*   
*   SoSFPaths are written to file as the path they point to. See the SoPath reference
*   page for a description of the file format for a path.
* 
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFPath,
*    SoPath
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoSFPath : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFPath, SoPath *, SoPath *);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

  // Propagates notification through field
  virtual void        notify(SoNotList *list);

  // Update a copied field to use node copies if the head node has
  // been copied
  virtual void        fixCopy(SbBool copyConnections);

  // Override this to also check the head of the stored path
  virtual SbBool      referencesCopy() const;

 private:
  SoNode              *head;          // Head node of path (needed
  // to track notification)

  // Override this to maintain write-references in path
  virtual void        countWriteRefs(SoOutput *out) const;

  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void                setVal(SoPath *newValue);

};

#endif /* _SO_SF_PATH_ */

