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


#ifndef  _SO_SF_ENGINE_
#define  _SO_SF_ENGINE_

class SoEngine;

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFEngine subclass of SoSField. The field value is a pointer to an
//  SoEngine. The field automatically maintains a reference to the engine
//  it points to and propagates notification from the engine.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Field containing a reference to an engine.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a reference to an SoEngine instance, correctly maintaining
*   its reference count.
*   
*   SoSFEngines are written to file as the engine they are pointing to. For
*   example:
*   
*   <PRE>
*    mySoSFEngineField ElapsedTime 
*    </PRE>
*    is an SoSFEngine field named 'mySoSFEngineField', pointing to an
*   SoElapsedTime engine. If the engine is used elsewhere, the regular DEF/USE
*   instancing mechanism applies:
*   
*   <PRE>
*    anotherSoSFEngineField USE calculator
*    </PRE>
*    is an SoSFEngine field that points to a engine named 'calculator' that
*   was DEF'ed earlier in the scene.
* 
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFEngine,
*    SoEngine
* 
* 
*/ 
#else
/**
* Field containing a pointer to an engine.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a pointer to an SoEngine instance, correctly maintaining
*   its reference count.
*   
*   SoSFEngines are written to file as the engine they are pointing to. For
*   example:
*   
*   <PRE>
*    mySoSFEngineField ElapsedTime 
*    </PRE>
*    is an SoSFEngine field named 'mySoSFEngineField', pointing to an
*   SoElapsedTime engine. If the engine is used elsewhere, the regular DEF/USE
*   instancing mechanism applies:
*   
*   <PRE>
*    anotherSoSFEngineField USE calculator
*    </PRE>
*    is an SoSFEngine field that points to a engine named 'calculator' that
*   was DEF'ed earlier in the scene.
* 
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFEngine,
*    SoEngine
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoSFEngine : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFEngine, SoEngine *, SoEngine *);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

  // Update a copied field to use the copy of the engine if there is one
  virtual void        fixCopy(SbBool copyConnections);

  // Override this to also check the stored engine
  virtual SbBool      referencesCopy() const;

 private:
  // Override this to maintain write-references in engine
  virtual void        countWriteRefs(SoOutput *out) const;

  // Changes value in field without doing other notification stuff.
  // Keeps track of references and auditors.
  void                setVal(SoEngine *newValue);

};

#endif /* _SO_SF_ENGINE_ */

