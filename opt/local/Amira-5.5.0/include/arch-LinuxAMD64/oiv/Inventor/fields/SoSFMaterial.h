/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SOSFMATERIAL_H
#define SOSFMATERIAL_H

#include <Inventor/fields/SoSFFieldContainer.h>
#include <Inventor/nodes/SoMaterial.h>

/**
* Field containing an SoMaterial node
*
* @ingroup fields
*
* @DESCRIPTION
*   This field maintains a pointer to an instance of an SoMaterial node, 
*   correctly maintaining its reference count.  The same SoMaterial node
*   may be referenced in multiple SoSFMaterial fields.
*
* @SEE_ALSO
*   SoSFNode, SoVolumeDataDrawStyle
*/
class INVENTOR_API SoSFMaterial : public SoSFFieldContainer
{
  SO_SFIELD_DERIVED_HEADER(SoSFMaterial, SoMaterial*, SoMaterial*);

public:
  /** Return current value */
  SoMaterial* getValue() const {
    evaluate();
    return (SoMaterial*)value;
  }

SoINTERNAL public:

  static void initClass();
  static void exitClass();
};

#endif
