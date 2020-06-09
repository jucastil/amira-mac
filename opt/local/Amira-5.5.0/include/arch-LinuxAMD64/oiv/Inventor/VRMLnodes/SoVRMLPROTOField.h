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



#ifndef  _SO_VRMLPROTOFIELD_
#define  _SO_VRMLPROTOFIELD_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPROTOField
//
//  This class stores the PROTO definitions
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Contains the internal definition for one of a prototype's fields, exposedFields,
 * eventIns or eventOuts.
 * 
 * @ingroup OtherVRML2
 * 
 * @DESCRIPTION
 *   The interface to a prototype is through the public fields, exposedFields,
 *   eventIns and eventOuts of a prototype declaration. This class defines one of
 *   these interfaces. The list of SoVRMLPROTOField definitions is created when the
 *   prototype is read from a file or buffer and cannot be created programmatically.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLPROTOField : public SoBase {

 public: 
    /** Kind */
  enum Kind {
    /**
     *  Regular field 
     */
    PROTO_FIELD,
    /**
     *  Field with implied set_ and _changed eventIn and eventOut 
     */
    PROTO_EXPOSEDFIELD,
    /**
     *  eventIn 
     */
    PROTO_EVENTIN,
    /**
     *  eventOut 
     */
    PROTO_EVENTOUT
  };

  /**
   * Returns the kind of field this is.
   */
  Kind        getFieldKind() { return fieldKind;}
  /**
   * Returns the type of field this is.
   */
  SoType      getFieldType() {return fieldType;}
  /**
   * Returns the name of the field.
   */
  SbString    getFieldName() {return fieldName;}
  /**
   * Returns the field's default value. Only fields and exposedFields have default
   * values.
   */
  SbString    getFieldDefaultValue() {return defValue;}

  // Constructor
  SoVRMLPROTOField();

  // Returns type identifier for VRMLPROTOField instance
  virtual SoType      getTypeId() const;

  /**
   * Returns type identifier for this class.
   */
  static SoType       getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:
 
  Kind                fieldKind;       // field, eventIn, etc
  SoType              fieldType;       // Such as SFFloat
  SbString            fieldName;       // The name of the field, eventIn, etc.
  SbString            defValue;        // Default value of the field, etc.

  static void         initClass();
  static void         exitClass();

  // Returns new SoVRMLPROTOField; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

 protected:
  virtual ~SoVRMLPROTOField();

  // Reads stuff into instance of SoVRMLPROTOField. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

 private:
  static SoType      classTypeId;    // TypeId 
};

#endif /* _SO_VRMLPROTOFIELD_ */

