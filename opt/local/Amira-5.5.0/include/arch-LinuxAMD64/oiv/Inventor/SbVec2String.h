/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Oct 2006)
**=======================================================================*/


#ifndef _SB_VEC2STRING_
#define _SB_VEC2STRING_

#include <Inventor/SbString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec2String
//
//  2D vector used to store two SbStrings.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 2D SbString vector class.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 *   2D SbString vector class used to store two SbStrings. This class is used
 *   throughout Open Inventor for arguments and return values.
 * 
 * @SEE_ALSO
 *    SbString
 * 
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 

class INVENTORBASE_API SbVec2String {
 public:

  /**
   * Default constructor.  The value is not initialized.
   */
  SbVec2String()    { }

  /**
   * Constructor given vector components.
   */
  SbVec2String(const SbString v[2])    { vec[0]=v[0]; vec[1]=v[1]; }

  /**
   * Constructor given two SbStrings.
   */
  SbVec2String(SbString x, SbString y)    { vec[0]=x; vec[1]=y; }

  /**
   * Returns vector components.
   */
  const SbString  *getValue() const  { return vec; }

  /**
   * Returns vector components.
   */
  void  getValue(SbString &x, SbString &y) const;

  /**
   * Sets the vector components.
   */
  SbVec2String &setValue(const SbString v[2]);

  /**
   * Sets the vector components.
   */
  SbVec2String &setValue(SbString x, SbString y);

  //@{
  /**
   * Accesses indexed component of vector.
   */
  SbString & operator [](int i) { return (vec[i]); }
  const SbString & operator [](int i) const   { return (vec[i]); }
  //@}

  /**
   * Equality comparison operator.
   */
  INVENTORBASE_API friend int operator ==(const SbVec2String &v1, const SbVec2String &v2);

  /**
   * Inequality comparison operator.
   */
  INVENTORBASE_API friend int operator !=(const SbVec2String &v1, const SbVec2String &v2)
  { return !(v1 == v2); }

 protected:
  SbString  vec[2];    // Storage for SbString vector components

};

#endif /* _SB_VEC2STRING_ */

