/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_LDMRESOURCEPARAMETER_
#define  _SO_SF_LDMRESOURCEPARAMETER_

#include <Inventor/fields/SoSFFieldContainer.h>
#include <LDM/nodes/SoLDMResourceParameters.h>

/**
* Field containing an SoLDMResourceParameters object
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a pointer to an instance of SoLDMResourceParameters, correctly maintaining its
*   reference count.
* 
* @SEE_ALSO
*   SoDataSet
* 
*/ 

class LDM_API SoSFLDMResourceParameters : public SoSFFieldContainer
{
  SO_SFIELD_DERIVED_HEADER(SoSFLDMResourceParameters, SoLDMResourceParameters*, SoLDMResourceParameters*);

public:
  /** Return current value */
  SoLDMResourceParameters* getValue() const {
    evaluate();
    return (SoLDMResourceParameters*)value;
  }

SoINTERNAL public:

  static void initClass();
  static void exitClass();
};

#endif // _SO_SF_LDMRESOURCEPARAMETER_

/**/
