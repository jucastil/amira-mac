/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Lague (Jan 2010)
**=======================================================================*/


#ifndef _SO_TYPED_OBJECT_
#define _SO_TYPED_OBJECT_

#include <Inventor/SoType.h>

/**
 * Base class for object storing runtime type information.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * The SoTypedObject class keeps track of runtime type information in Open Inventor
 * using SoType.
 *
 * @SEE_ALSO
 * SoType,
 * SoAction,
 * SoBase,
 * SoDetail,
 * SoError,
 * SoEvent,
 * SoField
 * [OIV-WRAPPER-NO-WRAP]
 */
class INVENTORBASE_API SoTypedObject {
public:

  virtual ~SoTypedObject();

  /**
   * Returns the type identifier for a specific instance.
   */
  virtual SoType              getTypeId() const = 0; 

  /**
   * Returns TRUE if this object is of the type specified in type or is derived from
   * that type. Otherwise, it returns FALSE. For example,
   * 
   * <PRE> 
   *  objPtr->isOfType(SoGroup::getClassTypeId())
   *  </PRE>
   *  returns TRUE if objPtr is an instance of SoGroup or one of its
   * subclasses.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SbBool                      isOfType(const SoType &type) const;
};

#endif /* _SO_TYPED_OBJECT_ */
