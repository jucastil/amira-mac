/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SFIELD_
#define  _SO_SFIELD_

#include <Inventor/fields/SoField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSField
//
//  Field that always has only one value.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for all single-value fields.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   Each class derived from SoSField begins with an SoSF prefix and contains one
 *   value of a particular type. Each has setValue() and getValue()
 *   methods that are used to change or access this value. In addition, some field
 *   classes have extra convenience routines that allow values to be set or retrieved
 *   in other related formats (see below).
 *   
 *   In addition to setValue(), all single-value fields overload the "="
 *   assignment operator to set the field value from the correct datatype or from
 *   another field instance of the same type.
 *   
 *   The value of a single-value field is written to file in a format dependent on the
 *   field type; see the subclass reference pages for details.
 *   
 *   A field that is ignored has a tilde (~) either in place of the value (if the
 *   actual value is the default) or after it (otherwise).
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoMField
 * 
 * 
 */ 

class INVENTOR_API SoSField : public SoField {
 public:
  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoSField();
#endif // HIDDEN_FROM_DOC

  /**
   * Return the type identifier for this field class.
   */
  static SoType getClassTypeId();

 protected:
  // Constructor
  SoSField();
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  static void *createInstance(SoType* dynamicType = NULL);

  // Called by an instance to indicate that a value has changed. If
  // resetDefault is TRUE, this turns off default flag. Initiates
  // notification, if necessary.
  void valueChanged(SbBool resetDefault = TRUE)
    {valueChangedBasic(resetDefault);}

  // Reads value of field
  virtual SbBool readValue(SoInput *in) = 0;
  
  // Writes value of field
  virtual void writeValue(SoOutput *out) const = 0;

private:
  static SoType classTypeId;

};

#endif /* _SO_SFIELD_ */
