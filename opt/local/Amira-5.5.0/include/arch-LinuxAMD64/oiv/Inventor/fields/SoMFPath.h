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


#ifndef  _SO_MF_PATH_
#define  _SO_MF_PATH_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFPath subclass of SoMField. Each field value is a pointer to an
//  SoPath. The field automatically maintains references to the paths
//  it points to and propagates notification from the paths.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of references to paths.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a set of references to SoPath instances, correctly
*   maintaining their reference counts.
*   
*   SoMFPaths are written to file as one or more paths (see the SoPath reference page
*   for a description of the file format for a path). When more than one value is
*   present, all of the values are enclosed in square brackets and separated by
*   commas.
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of pointers to paths.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a set of pointers to SoPath instances, correctly
*   maintaining their reference counts.
*   
*   SoMFPaths are written to file as one or more paths (see the SoPath reference page
*   for a description of the file format for a path). When more than one value is
*   present, all of the values are enclosed in square brackets and separated by
*   commas.
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFPath : public SoMField {
  
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFPath, SoPath *, SoPath *);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SoPath *);
    
 SoINTERNAL public:
    static void initClass();
    static void exitClass();

  // Propagates notification through field
  virtual void notify(SoNotList *list);
  
  // Update a copied field to use node copies if the head nodes have
  // been copied
  virtual void fixCopy(SbBool copyConnections);
  
  // Override this to also check the heads of the stored paths
  virtual SbBool referencesCopy() const;
  
 private:
  SoNode **heads;       // Head nodes of paths (needed
  // to track notification)
  
  // Override this to maintain write-references in paths
  virtual void countWriteRefs(SoOutput *out) const;
  
  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void setVal(int index, SoPath *newValue);
  
};

#endif /* _SO_MF_PATH_ */

