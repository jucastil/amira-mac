/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_LDMDATATRANSFORM_H_
#define  _SO_SF_LDMDATATRANSFORM_H_

#include <Inventor/fields/SoSFFieldContainer.h>

#include <LDM/nodes/SoLDMDataTransform.h>

/**
* Field containing an SoLDMDataTransform object
* 
* @ingroup fields
* 
* @DESCRIPTION
*   This field maintains a pointer to an instance of SoLDMDataTransform, correctly maintaining its
*   reference count.
* 
* @SEE_ALSO
*    SoLDMDataTransform, SoDataSet
* 
*/ 

class LDM_API SoSFLDMDataTransform : public SoSFFieldContainer
{
  SO_SFIELD_DERIVED_HEADER(SoSFLDMDataTransform, SoLDMDataTransform*, SoLDMDataTransform*);

public:
  /** Returns current value */
  SoLDMDataTransform* getValue() const {
    evaluate();
    return (SoLDMDataTransform*)value;
  }

SoINTERNAL public:

  static void initClass();
  static void exitClass();
};

#endif // _SO_SF_LDMDATATRANSFORM_H_

/**/
