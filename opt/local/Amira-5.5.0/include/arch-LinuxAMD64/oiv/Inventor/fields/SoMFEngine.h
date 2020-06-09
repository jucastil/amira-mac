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


#ifndef  _SO_MF_ENGINE_
#define  _SO_MF_ENGINE_

class SoEngine;

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFEngine subclass of SoMField. Each field value is a pointer to an
//  SoEngine. The field automatically maintains references to the engines
//  it points to and propagates notification from the engines.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Multiple-value field containing any number of references to engines.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a set of references to SoEngine instances, correctly
*   maintaining their reference counts.
*   
*   SoMFEngines are written to file as one or more engines. When more than one value
*   is present, all of the values are enclosed in square brackets and separated by
*   commas; for example:
*   
*   <PRE>
*    [ ElapsedTime , OneShot duration 2.0 , USE myCalculator ]
*    </PRE>
*    
* 
* 
*/ 
#else
/**
* Multiple-value field containing any number of pointers to engines.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a set of pointers to SoEngine instances, correctly
*   maintaining their reference counts.
*   
*   SoMFEngines are written to file as one or more engines. When more than one value
*   is present, all of the values are enclosed in square brackets and separated by
*   commas; for example:
*   
*   <PRE>
*    [ ElapsedTime , OneShot duration 2.0 , USE myCalculator ]
*    </PRE>
*    
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMFEngine : public SoMField {
  
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFEngine, SoEngine *, SoEngine *);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SoEngine *);
    
 SoINTERNAL public:
    static void initClass();
    static void exitClass();

  // Update a copied field to use the copy of each engine if there is one
  virtual void fixCopy(SbBool copyConnections);
  
  // Override this to also check the stored engines
  virtual SbBool referencesCopy() const;
  
 private:
  // Override this to maintain write-references in engines
  virtual void countWriteRefs(SoOutput *out) const;
  
  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void setVal(int index, SoEngine *newValue);

};

#endif /* _SO_MF_ENGINE_ */

